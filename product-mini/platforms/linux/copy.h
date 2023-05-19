#ifndef WALI_COPY_H
#define WALI_COPY_H

#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <signal.h>
#include <setjmp.h>

#include "wali.h"

#define RD_FIELD(ptr, ty) ({  \
  ty val; \
  memcpy(&val, ptr, sizeof(ty));  \
  ptr += sizeof(ty);  \
  val;  \
})

#define RD_FIELD_ADDR(ptr) ({ \
  uint32_t field = RD_FIELD(ptr, uint32_t); \
  MADDR (field);  \
})

#define RD_FIELD_ARRAY(dest, ptr, ty, num) ({ \
  memcpy(&dest, ptr, sizeof(ty) * num);  \
  ptr += (sizeof(ty) * num);  \
})

#define PRINT_BYTES(var, num) { \
  printf(#var " bytes: "); \
  char* v = (char*) var;  \
  for (int i = 0; i < num; i++) { \
    printf("%02X ", v[i]);  \
  } \
  printf("\n"); \
}

/* Copy iovec structure */
struct iovec* copy_iovec(wasm_exec_env_t exec_env, Addr wasm_iov, int iov_cnt) {
  struct iovec *new_iov = (struct iovec*) malloc(iov_cnt * sizeof(struct iovec));
  for (int i = 0; i < iov_cnt; i++) {
    new_iov[i].iov_base = RD_FIELD_ADDR(wasm_iov);
    new_iov[i].iov_len = RD_FIELD(wasm_iov, int32_t);
  }
  return new_iov;
}


// 0 = SIG_DFL; -1: SIG_ERR; -2: SIG_IGN
#define WASM_SIG_DFL (0)
#define WASM_SIG_ERR (-1)
#define WASM_SIG_IGN (-2)

// ASM restorer function '__libc_restore_rt'.
extern void __libc_restore_rt();
/* Copy Sigaction structure: Function pointers are padded */
struct k_sigaction* copy_ksigaction (wasm_exec_env_t exec_env, Addr wasm_act, 
    struct k_sigaction *act, void (*common_handler)(int), 
    wasm_function_inst_t *target_handler) {
  if (wasm_act == NULL) { return NULL; }

  uint32_t wasm_handler = RD_FIELD(wasm_act, uint32_t);
  if ( wasm_handler == (uint32_t)(WASM_SIG_DFL) ) {
    act->handler = SIG_DFL;
  } else if (wasm_handler == (uint32_t)(WASM_SIG_IGN)) {
    act->handler = SIG_IGN;
  } else {
    printf("Wasm Handler: %u\n", wasm_handler);
    /* Setup target and common handler */
    wasm_module_inst_t module_inst = get_module_inst(exec_env);
    act->handler = common_handler;
    *target_handler = wasm_runtime_get_indirect_function(
                          module_inst, 0, wasm_handler);
  }

  act->flags = RD_FIELD(wasm_act, unsigned long);
  
  RD_FIELD_ADDR(wasm_act);
  act->restorer = __libc_restore_rt;

  RD_FIELD_ARRAY(act->mask, wasm_act, unsigned, 2);
  return act;
}

/* Copy sigstack structure */
stack_t* copy_sigstack (wasm_exec_env_t exec_env, Addr wasm_sigstack,
    stack_t* ss) {
  if (!wasm_sigstack) { return NULL; }
  ss->ss_sp = RD_FIELD_ADDR(wasm_sigstack);
  ss->ss_flags = RD_FIELD(wasm_sigstack, int);
  ss->ss_size = RD_FIELD(wasm_sigstack, uint32_t);
  return ss;
}

/* Copy array of strings (strings are not malloced)*/
char** copy_stringarr (wasm_exec_env_t exec_env, Addr wasm_arr) {
  if (!wasm_arr) { return NULL; }
  int num_strings = 0;
  /* Find num elems */
  Addr arr_it = wasm_arr;
  char *str;
  while ((str = (char*)RD_FIELD_ADDR(arr_it))) { num_strings++; }
  /* Set stringarr */
  char **stringarr = (char**) malloc(num_strings * sizeof(char*));
  for (int i = 0; i < num_strings; i++) {
    stringarr[i] = (char*)RD_FIELD_ADDR(wasm_arr);
  }
  stringarr[num_strings] = NULL;
  return stringarr;
}


extern _Noreturn void __libc_longjmp_asm(__libc_sigjmp_buf, int);
extern int __libc_sigsetjmp_asm(__libc_sigjmp_buf, int);
#define __libc_siglongjmp __libc_longjmp_asm

struct __libc_jmp_buf_tag* copy_jmp_buf (wasm_exec_env_t exec_env, Addr wasm_jmp_buf) {
  if (!wasm_jmp_buf) { return NULL; }
  struct __libc_jmp_buf_tag* buf = (struct __libc_jmp_buf_tag *) malloc(sizeof(struct __libc_jmp_buf_tag));
  RD_FIELD_ARRAY(buf->__jb, wasm_jmp_buf, unsigned long, 8);
  buf->__fl = RD_FIELD(wasm_jmp_buf, unsigned long);
  RD_FIELD_ARRAY(buf->__ss, wasm_jmp_buf, unsigned long, (128/sizeof(long)));
  return buf;
}


#endif
