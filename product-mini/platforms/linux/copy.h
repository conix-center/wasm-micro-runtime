#ifndef WALI_COPY_H
#define WALI_COPY_H

#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/mman.h>

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



/* Copy Sigaction structure: Function pointers are padded */
struct k_sigaction* copy_ksigaction (wasm_exec_env_t exec_env, Addr wasm_act, 
    struct k_sigaction *act, void (*handler)(int), void(*restorer)(void)) {
  if (wasm_act == NULL) { return NULL; }

  if ( (void (*)(int))(RD_FIELD_ADDR(wasm_act)) == SIG_DFL) {
    act->handler = SIG_DFL;
  } else {
    act->handler = handler;
  }

  act->flags = RD_FIELD(wasm_act, unsigned long);
  
  RD_FIELD_ADDR(wasm_act);
  act->restorer = restorer;

  RD_FIELD_ARRAY(act->mask, wasm_act, unsigned, 2);
  return act;
}

#endif
