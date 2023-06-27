#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/mman.h>

#include "wali.h"
#include "copy.h"
#include "../interpreter/wasm_runtime.h"

#if !__x86_64__ && !__aarch64__ && !__riscv64__
#error "Unsupported architecture for WALI -- Only supports [x86_64, aarch64, riscv64]"
#endif

#include "syscall_arch.h"

extern int app_argc;
extern char **app_argv;

/* Get page aligned address after memory to mmap; since base is mapped it's already aligned, 
* and memory data size is a multiple of 64kB but rounding added for safety */
#define PA_ALIGN_MMAP_ADDR() ({ \
  Addr base = BASE_ADDR(); \
  Addr punalign = base + wasm_runtime_get_base_memory_size(get_module_inst(exec_env));  \
  long pageoff = (long)(punalign) & (NATIVE_PAGESIZE - 1); \
  Addr palign = punalign - pageoff; \
  if (pageoff) { palign += NATIVE_PAGESIZE; } \
  palign; \
})


uint32_t NATIVE_PAGESIZE = 0;
int MMAP_PAGELEN = 0;
int WASM_PAGELEN = 0;
int WASM_TO_NATIVE_PAGE = 0;
uint32_t BASE_MEMSIZE = 0;
uint32_t THREAD_ID = 0;

void wali_init_native() {
  NATIVE_PAGESIZE = sysconf(_SC_PAGE_SIZE);
  MMAP_PAGELEN = 0;
  WASM_PAGELEN = 0;
  WASM_TO_NATIVE_PAGE = WASM_PAGESIZE / NATIVE_PAGESIZE;
  // Set in mmap
  BASE_MEMSIZE = 0;
  THREAD_ID = 1;
}


#define __syscall1(n, a1) __syscall1(n, (long)a1)
#define __syscall2(n, a1, a2) __syscall2(n, (long)a1, (long)a2)
#define __syscall3(n, a1, a2, a3) __syscall3(n, (long)a1, (long)a2, (long)a3)
#define __syscall4(n, a1, a2, a3, a4) __syscall4(n, (long)a1, (long)a2, (long)a3, (long)a4)
#define __syscall5(n, a1, a2, a3, a4, a5) __syscall5(n, (long)a1, (long)a2, (long)a3, (long)a4, (long)a5)
#define __syscall6(n, a1, a2, a3, a4, a5, a6) __syscall6(n, (long)a1, (long)a2, (long)a3, (long)a4, (long)a5, (long)a6)


#define ATOM(f) LOG_VERBOSE("[%d] WALI: Atomic (use with care) | " # f, gettid())
#define PC(f)  LOG_VERBOSE("[%d] WALI: | " # f, gettid())
#define SC(f)  LOG_VERBOSE("[%d] WALI: SC | " # f, gettid())
#define ERRSC(f,...) { \
  LOG_ERROR("[%d] WALI: SC \"" # f "\" not implemented correctly yet! " __VA_ARGS__, gettid());  \
}
#define FATALSC(f,...) { \
  LOG_FATAL("[%d] WALI: SC \"" # f "\" fatal error! " __VA_ARGS__, gettid());  \
}
#define MISSC(f,...) { \
  LOG_FATAL("[%d] WALI: SC \"" # f "\" fatal error! No such syscall on platform", gettid());  \
}

  #if __x86_64__
  #elif __aarch64__ || __riscv64__
  #endif

/***** WALI Methods *******/
// 0
long wali_syscall_read (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(read);
	return __syscall3(SYS_read, a1, MADDR(a2), a3);
}

// 1
long wali_syscall_write (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(write);
	return __syscall3(SYS_write, a1, MADDR(a2), a3);
}

// 2
long wali_syscall_open (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(open);
  #if __x86_64__
	  return __syscall3(SYS_open, MADDR(a1), a2, a3);
  #elif __aarch64__
    return wali_syscall_openat(exec_env, AT_FDCWD, a1, a2, a3);
  #elif __riscv64__
    return wali_syscall_openat(exec_env, AT_FDCWD, a1, a2, a3);
  #endif
}

// 3
long wali_syscall_close (wasm_exec_env_t exec_env, long a1) {
	SC(close);
	return __syscall1(SYS_close, a1);
}

// 4 
long wali_syscall_stat (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(stat);
  #if __x86_64__
	  return __syscall2(SYS_stat, MADDR(a1), MADDR(a2));
  #elif __aarch64__ || __riscv64__
    return wali_syscall_fstatat(exec_env, AT_FDCWD, a1, a2, 0);
  #endif
}

// 5 
long wali_syscall_fstat (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(fstat);
	return __syscall2(SYS_fstat, a1, MADDR(a2));
}

// 6 
long wali_syscall_lstat (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(lstat);
  #if __x86_64__
	  return __syscall2(SYS_lstat, MADDR(a1), MADDR(a2));
  #elif __aarch64__ || __riscv64__
    return wali_syscall_fstatat (exec_env, AT_FDCWD, a1, a2, AT_SYMLINK_NOFOLLOW);
  #endif
}

#define CONV_TIME_TO_TS(x) ( (x>=0) ? &((struct timespec){.tv_sec = x/1000, .tv_nsec = (x%1000)*1000000}) : 0 )
// 7 
long wali_syscall_poll (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(poll);
  #if __x86_64__
	  return __syscall3(SYS_poll, MADDR(a1), a2, a3);
  #elif __aarch64__ || __riscv64__
    return wali_syscall_ppoll_aliased(exec_env, a1, a2, (long)CONV_TIME_TO_TS(a3), 0, _NSIG/8);
  #endif
}

// 8 
long wali_syscall_lseek (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(lseek);
	return __syscall3(SYS_lseek, a1, a2, a3);
}


// 9 
long wali_syscall_mmap (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5, long a6) {
	SC(mmap);
  ERR("mmap args | a1: %ld, a2: 0x%x, a3: %ld, a4: %ld, a5: %ld, a6: %ld | MMAP_PAGELEN: %d", a1, a2, a3, a4, a5, a6, MMAP_PAGELEN);
  Addr base_addr = BASE_ADDR();
  Addr pa_aligned_addr = PA_ALIGN_MMAP_ADDR();
  Addr mmap_addr = pa_aligned_addr + MMAP_PAGELEN * NATIVE_PAGESIZE;

  uint32 mem_size = wasm_runtime_get_memory_size(get_module_inst(exec_env)); 
  ERR("Mem Base: %p | Mem End: %p | Mem Size: 0x%x | Mmap Addr: %p", base_addr, base_addr + mem_size, mem_size, mmap_addr);

  Addr mem_addr = (Addr) __syscall6(SYS_mmap, mmap_addr, a2, a3, MAP_FIXED|a4, a5, a6);
  /* Sometimes mmap returns -9 instead of MAP_FAILED? */
  if ((mem_addr == MAP_FAILED) || (mem_addr == (void*)(-9))) {
    FATALSC(mmap, "Failed to mmap!\n");
    return (long) MAP_FAILED;
  }
  /* On success */
  else {
    int num_pages = ((a2 + NATIVE_PAGESIZE - 1) / NATIVE_PAGESIZE);
    MMAP_PAGELEN += num_pages;
    /* Expand wasm memory if needed */
    if (MMAP_PAGELEN > WASM_PAGELEN * WASM_TO_NATIVE_PAGE) {
      int new_wasm_pagelen = ((MMAP_PAGELEN + WASM_TO_NATIVE_PAGE - 1) / WASM_TO_NATIVE_PAGE);
      int inc_wasm_pages = new_wasm_pagelen - WASM_PAGELEN;
      wasm_module_inst_t module = get_module_inst(exec_env);
      wasm_enlarge_memory((WASMModuleInstance*)module, inc_wasm_pages, true);
      WASM_PAGELEN += inc_wasm_pages;
    }
  }
  long retval =  WADDR(mem_addr);
  ERR("Retval: 0x%x", retval);
  return retval;
}

// 10
long wali_syscall_mprotect (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(mprotect);
	return __syscall3(SYS_mprotect, MADDR(a1), a2, a3);
}

// 11 
long wali_syscall_munmap (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(munmap);
  Addr mmap_addr = MADDR(a1);
  Addr mmap_addr_end = (Addr)(mmap_addr + a2);
  /* Reclaim some mmap space if end region is unmapped */
  Addr pa_aligned_addr = PA_ALIGN_MMAP_ADDR();
  int end_page = (mmap_addr_end - pa_aligned_addr + NATIVE_PAGESIZE - 1) / NATIVE_PAGESIZE;
  ERR("End page: %d | MMAP_PAGELEN: %d", end_page, MMAP_PAGELEN);
  if (end_page == MMAP_PAGELEN) {
    MMAP_PAGELEN -= ((a2 + NATIVE_PAGESIZE - 1) / NATIVE_PAGESIZE);
    ERR("End page unmapped | New MMAP_PAGELEN: %d", MMAP_PAGELEN);
  }
	return __syscall2(SYS_munmap, mmap_addr, a2);
}

// 12 TODO
long wali_syscall_brk (wasm_exec_env_t exec_env, long a1) {
	SC(brk);
  ERR("brk syscall is a NOP in WASM right now");
	return 0; 
  //__syscall1(SYS_brk, MADDR(a1));
}


void sa_handler_wali(int signo) {
  /* Mark pending signal */
  pthread_mutex_lock(&sigpending_mut);
  wali_sigpending |= ((uint64_t)1 << signo);
  pthread_mutex_unlock(&sigpending_mut);
}
// 13 
long wali_syscall_rt_sigaction (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(rt_sigaction);
  ERR("rt_sigaction args | a1: %ld, a2: %ld, a3: %ld, a4: %ld", a1, a2, a3, a4);
  wasm_module_inst_t module_inst = get_module_inst(exec_env);
  int signo = a1;
  Addr wasm_act  = MADDR(a2);
  Addr wasm_oldact = MADDR(a3);
  struct k_sigaction act = {0};
  struct k_sigaction oldact = {0};

  /* Block signal manipulation while setting up synchronized wali table */
  pthread_mutex_lock(&sigtable_mut);
  FuncPtr_t target_wasm_funcptr = 0;
  char sigtype[30];

  /* Prepare for native signal syscall */
  struct k_sigaction *act_pt = 
    copy_ksigaction(exec_env, wasm_act, &act, sa_handler_wali, &target_wasm_funcptr, sigtype);
  struct k_sigaction *oldact_pt = 
    wasm_oldact ? &oldact : NULL;
  long retval = __syscall4(SYS_rt_sigaction, a1, act_pt, oldact_pt, a4);

  ERR("Signal Registration -- \'%s\' | Sigtype: %s", strsignal(a1), sigtype);

  /* Register virtual signal in WALI sigtable 
  * ---------------------------------------------------------------
  * | Handler value | WALI sigtable (set)     | Old Action (get)  |
  * ---------------------------------------------------------------
  * | SIG_DFL       | No register             | WASM_SIG_DFL      |
  * | SIG_IGN       | No register             | WASM_SIG_IGN      |
  * | SIG_ERR       |     -                   | WASM_SIG_ERR      |
  * | FuncPtr_t     | Table[FuncPtr_t]        | Table[FuncPtr_t]  |
  * ---------------------------------------------------------------
  * */
  if (!retval && (signo < NSIG)) {
    /* Save old sigaction to WASM */
    if (oldact_pt) {
      copy2wasm_old_ksigaction (signo, wasm_oldact, oldact_pt);
    }
    /* Set WALI table */
    if (act_pt && (act_pt->handler != SIG_DFL) && (act_pt->handler != SIG_IGN)) {
      wasm_function_inst_t target_wasm_handler = wasm_runtime_get_indirect_function(
                                                  module_inst, 0, target_wasm_funcptr);
      uint32_t old_fn_idx = wali_sigtable[signo].function ? FUNC_IDX(wali_sigtable[signo].function) : 0;
      uint32_t new_fn_idx = target_wasm_handler ? FUNC_IDX(target_wasm_handler) : 0;
      ERR("Replacing target handler: Fn[%u] -> Fn[%u]\n", old_fn_idx, new_fn_idx);
      wali_sigtable[signo].function = target_wasm_handler;
      wali_sigtable[signo].func_table_idx = target_wasm_funcptr;
    }
  }
  /* Reset block signals */
  pthread_mutex_unlock(&sigtable_mut);

  return retval;
}

// 14 
long wali_syscall_rt_sigprocmask (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(rt_sigprocmask);
	return __syscall4(SYS_rt_sigprocmask, a1, MADDR(a2), MADDR(a3), a4);
}

// 15: Never directly called; __libc_restore_rt is called by OS
long wali_syscall_rt_sigreturn (wasm_exec_env_t exec_env, long a1) {
	SC(rt_sigreturn);
	ERRSC(rt_sigreturn, "rt_sigreturn should never be called by the user!");
	return -1;
}

// 16 
long wali_syscall_ioctl (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(ioctl);
	return __syscall3(SYS_ioctl, a1, a2, MADDR(a3));
}

// 17 TODO
long wali_syscall_pread64 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(pread64);
	ERRSC(pread64);
	return __syscall4(SYS_pread64, a1, MADDR(a2), a3, a4);
}

// 18 TODO
long wali_syscall_pwrite64 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(pwrite64);
	ERRSC(pwrite64);
	return __syscall4(SYS_pwrite64, a1, MADDR(a2), a3, a4);
}

// 19 TODO
long wali_syscall_readv (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(readv);
	//ERRSC(readv);
  Addr wasm_iov = MADDR(a2);
  int iov_cnt = a3;
  
  struct iovec *native_iov = copy_iovec(exec_env, wasm_iov, iov_cnt);
	long retval = __syscall3(SYS_readv, a1, native_iov, a3);
  free(native_iov);

	return retval;
}

// 20 
long wali_syscall_writev (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(writev);
  Addr wasm_iov = MADDR(a2);
  int iov_cnt = a3;
  
  struct iovec *native_iov = copy_iovec(exec_env, wasm_iov, iov_cnt);
	long retval = __syscall3(SYS_writev, a1, native_iov, a3);
  free(native_iov);
  return retval;
}

// 21 
long wali_syscall_access (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(access);
  #if __x86_64__
	  return __syscall2(SYS_access, MADDR(a1), a2);
  #elif __aarch64__ || __riscv64__
    return wali_syscall_faccessat(exec_env, AT_FDCWD, a1, a2, 0);
  #endif
}

// 22 
long wali_syscall_pipe (wasm_exec_env_t exec_env, long a1) {
	SC(pipe);
  #if __x86_64__
	  return __syscall1(SYS_pipe, MADDR(a1));
  #elif __aarch64__ || __riscv64__
    return wali_syscall_pipe2(exec_env, a1, 0);
  #endif
}

// 23 TODO
long wali_syscall_select (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(select);
	ERRSC(select);
  #if __x86_64__
	  return __syscall5(SYS_select, a1, MADDR(a2), MADDR(a3), MADDR(a4), MADDR(a5));
  #elif __aarch64__ || __riscv64__
    return wali_syscall_pselect6(exec_env, a1, a2, a3, a4, a5, (long)((long[]){0, _NSIG/8}));
  #endif
}

// 24 
long wali_syscall_sched_yield (wasm_exec_env_t exec_env) {
	SC(sched_yield);
	return __syscall0(SYS_sched_yield);
}

// 25 TODO
long wali_syscall_mremap (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(mremap);
	ERRSC(mremap);
	return __syscall5(SYS_mremap, MADDR(a1), a2, a3, a4, MADDR(a5));
}

// 26 
long wali_syscall_msync (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(msync);
	return __syscall3(SYS_msync, MADDR(a1), a2, a3);
}

// 28 
long wali_syscall_madvise (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(madvise);
	return __syscall3(SYS_madvise, MADDR(a1), a2, a3);
}

// 32 
long wali_syscall_dup (wasm_exec_env_t exec_env, long a1) {
	SC(dup);
	return __syscall1(SYS_dup, a1);
}

// 33 
long wali_syscall_dup2 (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(dup2);
  #if __x86_64__
	  return __syscall2(SYS_dup2, a1, a2);
  #elif __aarch64__ || __riscv64__
    /* Dup2 returns newfd while dup3 throws error, handle with case below */
    if (a1 == a2) {
      long r = wali_syscall_fcntl(exec_env, a1, F_GETFD, 0);
      return (r >= 0) ? a2 : r;
    } else {
      return wali_syscall_dup3(exec_env, a1, a2, 0);
    }
  #endif
}

// 35
long wali_syscall_nanosleep (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(nanosleep);
	return __syscall2(SYS_nanosleep, MADDR(a1), MADDR(a2));
}

// 37 
long wali_syscall_alarm (wasm_exec_env_t exec_env, long a1) {
	SC(alarm);
  #if __x86_64__
	  return __syscall1(SYS_alarm, a1);
  #elif __aarch64__ || __riscv64__
    MISSC(alarm);
  #endif
  exit(1);
}

// 38 TODO
long wali_syscall_setitimer (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(setitimer);
	return __syscall3(SYS_setitimer, a1, MADDR(a2), MADDR(a3));
}

// 39 
long wali_syscall_getpid (wasm_exec_env_t exec_env) {
	SC(getpid);
	return __syscall0(SYS_getpid);
}

// 41 
long wali_syscall_socket (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(socket);
	return __syscall3(SYS_socket, a1, a2, a3);
}

// 42 
long wali_syscall_connect (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(connect);
	return __syscall3(SYS_connect, a1, MADDR(a2), a3);
}

// 43 
long wali_syscall_accept (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(accept);
	return __syscall3(SYS_accept, a1, MADDR(a2), MADDR(a3));
}

// 44 
long wali_syscall_sendto (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5, long a6) {
	SC(sendto);
	return __syscall6(SYS_sendto, a1, MADDR(a2), a3, a4, MADDR(a5), a6);
}

// 45 
long wali_syscall_recvfrom (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5, long a6) {
	SC(recvfrom);
	return __syscall6(SYS_recvfrom, a1, MADDR(a2), a3, a4, MADDR(a5), MADDR(a6));
}

// 46 
long wali_syscall_sendmsg (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(sendmsg);
	return __syscall3(SYS_sendmsg, a1, MADDR(a2), a3);
}

// 47 
long wali_syscall_recvmsg (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(recvmsg);
	return __syscall3(SYS_recvmsg, a1, MADDR(a2), a3);
}

// 48 
long wali_syscall_shutdown (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(shutdown);
	return __syscall2(SYS_shutdown, a1, a2);
}

// 49 
long wali_syscall_bind (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(bind);
	return __syscall3(SYS_bind, a1, MADDR(a2), a3);
}

// 50 
long wali_syscall_listen (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(listen);
	return __syscall2(SYS_listen, a1, a2);
}

// 51 
long wali_syscall_getsockname (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(getsockname);
	return __syscall3(SYS_getsockname, a1, MADDR(a2), MADDR(a3));
}

// 52 
long wali_syscall_getpeername (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(getpeername);
	return __syscall3(SYS_getpeername, a1, MADDR(a2), MADDR(a3));
}

// 54 
long wali_syscall_setsockopt (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(setsockopt);
	return __syscall5(SYS_setsockopt, a1, a2, a3, MADDR(a4), a5);
}

// 55 
long wali_syscall_getsockopt (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(getsockopt);
	return __syscall5(SYS_getsockopt, a1, a2, a3, MADDR(a4), MADDR(a5));
}

// 57
long wali_syscall_fork (wasm_exec_env_t exec_env) {
	SC(fork);
  #if __x86_64__
	  return __syscall0(SYS_fork);
  #elif __aarch64__ || __riscv64__
    return __syscall2(SYS_clone, SIGCHLD, 0);
  #endif
}

// 59 
long wali_syscall_execve (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(execve);
  printf("Execve string: %s\n", MADDR(a1));
  char** argv = copy_stringarr (exec_env, MADDR(a2));
  char** envp = copy_stringarr (exec_env, MADDR(a3));
	long retval = __syscall3(SYS_execve, MADDR(a1), argv, envp);
  free(argv);
  free(envp);
  return retval;
}

// 60 TODO
long wali_syscall_exit (wasm_exec_env_t exec_env, long a1) {
	SC(exit);
  ERRSC(exit);
  return __syscall1(SYS_exit, a1);
}

// 61 TODO
long wali_syscall_wait4 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(wait4);
	ERRSC(wait4);
	return __syscall4(SYS_wait4, a1, MADDR(a2), a3, MADDR(a4));
}

// 62 
long wali_syscall_kill (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(kill);
	return __syscall2(SYS_kill, a1, a2);
}

// 63 
long wali_syscall_uname (wasm_exec_env_t exec_env, long a1) {
	SC(uname);
	return __syscall1(SYS_uname, MADDR(a1));
}

// 72 
long wali_syscall_fcntl (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(fcntl);
  /* Swap open flags only on F_GETFL and F_SETFL mode for aarch64 */
  #if __aarch64__
    switch (a2) {
      case F_GETFL: return swap_open_flags(__syscall3(SYS_fcntl, a1, a2, a3)); break;
      case F_SETFL: return __syscall3(SYS_fcntl, a1, a2, swap_open_flags(a3)); break;
      default: return __syscall3(SYS_fcntl, a1, a2, a3);
    }
  #else
	  return __syscall3(SYS_fcntl, a1, a2, a3);
  #endif
}

// 73 TODO
long wali_syscall_flock (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(flock);
	ERRSC(flock);
	return __syscall2(SYS_flock, a1, a2);
}

// 74 
long wali_syscall_fsync (wasm_exec_env_t exec_env, long a1) {
	SC(fsync);
	return __syscall1(SYS_fsync, a1);
}

// 77 
long wali_syscall_ftruncate (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(ftruncate);
	return __syscall2(SYS_ftruncate, a1, a2);
}

// 78 TODO
long wali_syscall_getdents (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(getdents);
	FATALSC(getdents, "Not going to support this legacy call; use getdents64");
  #if __x86_64__
	  return __syscall3(SYS_getdents, a1, MADDR(a2), a3);
  #elif __aarch64__ || __riscv64__
    return -1;
  #endif
}

// 79
long wali_syscall_getcwd (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(getcwd);
	return __syscall2(SYS_getcwd, MADDR(a1), a2);
}

// 80
long wali_syscall_chdir (wasm_exec_env_t exec_env, long a1) {
	SC(chdir);
	return __syscall1(SYS_chdir, MADDR(a1));
}

// 82
long wali_syscall_rename (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(rename);
  #if __x86_64__
	  return __syscall2(SYS_rename, MADDR(a1), MADDR(a2));
  #elif __aarch64__ || __riscv64__
    return wali_syscall_renameat2(exec_env, AT_FDCWD, a1, AT_FDCWD, a2, 0);
  #endif
}

// 83
long wali_syscall_mkdir (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(mkdir);
  #if __x86_64__
	  return __syscall2(SYS_mkdir, MADDR(a1), a2);
  #elif __aarch64__ || __riscv64__
    return wali_syscall_mkdirat(exec_env, AT_FDCWD, a1, a2);
  #endif
}

// 84 
long wali_syscall_rmdir (wasm_exec_env_t exec_env, long a1) {
	SC(rmdir);
  #if __x86_64__
	  return __syscall1(SYS_rmdir, MADDR(a1));
  #elif __aarch64__ || __riscv64__
    return wali_syscall_unlinkat(exec_env, AT_FDCWD, a1, AT_REMOVEDIR);
  #endif
}

// 86 
long wali_syscall_link (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(link);
  #if __x86_64__
	  return __syscall2(SYS_link, MADDR(a1), MADDR(a2));
  #elif __aarch64__ || __riscv64__
    return wali_syscall_linkat(exec_env, AT_FDCWD, a1, AT_FDCWD, a2, 0);
  #endif
}

// 87 
long wali_syscall_unlink (wasm_exec_env_t exec_env, long a1) {
	SC(unlink);
  #if __x86_64__
	  return __syscall1(SYS_unlink, MADDR(a1));
  #elif __aarch64__ || __riscv64__
    return wali_syscall_unlinkat(exec_env, AT_FDCWD, a1, 0);
  #endif
}

// 88 
long wali_syscall_symlink (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(symlink);
  #if __x86_64__
	  return __syscall2(SYS_symlink, MADDR(a1), MADDR(a2));
  #elif __aarch64__ || __riscv64__
    return wali_syscall_symlinkat(exec_env, a1, AT_FDCWD, a2);
  #endif
}

// 89 
long wali_syscall_readlink (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(readlink);
  #if __x86_64__
	  return __syscall3(SYS_readlink, MADDR(a1), MADDR(a2), a3);
  #elif __aarch64__ || __riscv64__
    return wali_syscall_readlinkat(exec_env, AT_FDCWD, a1, a2, a3);
  #endif
}

// 90 
long wali_syscall_chmod (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(chmod);
  #if __x86_64__
	  return __syscall2(SYS_chmod, MADDR(a1), a2);
  #elif __aarch64__ || __riscv64__
    return wali_syscall_fchmodat(exec_env, AT_FDCWD, a1, a2, 0);
  #endif
}

// 91 
long wali_syscall_fchmod (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(fchmod);
	return __syscall2(SYS_fchmod, a1, a2);
}

// 92 
long wali_syscall_chown (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(chown);
  #if __x86_64__
	  return __syscall3(SYS_chown, MADDR(a1), a2, a3);
  #elif __aarch64__ || __riscv64__
    return wali_syscall_fchownat(exec_env, AT_FDCWD, a1, a2, a3, 0);
  #endif
}

// 93 
long wali_syscall_fchown (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(fchown);
	return __syscall3(SYS_fchown, a1, a2, a3);
}

// 95 
long wali_syscall_umask (wasm_exec_env_t exec_env, long a1) {
	SC(umask);
	return __syscall1(SYS_umask, a1);
}

// 97 
long wali_syscall_getrlimit (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(getrlimit);
	return __syscall2(SYS_getrlimit, a1, MADDR(a2));
}

// 98 
long wali_syscall_getrusage (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(getrusage);
	return __syscall2(SYS_getrusage, a1, MADDR(a2));
}

// 99 
long wali_syscall_sysinfo (wasm_exec_env_t exec_env, long a1) {
	SC(sysinfo);
	return __syscall1(SYS_sysinfo, MADDR(a1));
}

// 102 
long wali_syscall_getuid (wasm_exec_env_t exec_env) {
	SC(getuid);
	return __syscall0(SYS_getuid);
}

// 104 
long wali_syscall_getgid (wasm_exec_env_t exec_env) {
	SC(getgid);
	return __syscall0(SYS_getgid);
}

// 107 
long wali_syscall_geteuid (wasm_exec_env_t exec_env) {
	SC(geteuid);
	return __syscall0(SYS_geteuid);
}

// 108 
long wali_syscall_getegid (wasm_exec_env_t exec_env) {
	SC(getegid);
	return __syscall0(SYS_getegid);
}

// 109 
long wali_syscall_setpgid (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(setpgid);
	return __syscall2(SYS_setpgid, a1, a2);
}

// 110 
long wali_syscall_getppid (wasm_exec_env_t exec_env) {
	SC(getppid);
	return __syscall0(SYS_getppid);
}

// 112 
long wali_syscall_setsid (wasm_exec_env_t exec_env) {
	SC(setsid);
	return __syscall0(SYS_setsid);
}

// 121 
long wali_syscall_getpgid (wasm_exec_env_t exec_env, long a1) {
	SC(getpgid);
	return __syscall1(SYS_getpgid, a1);
}

// 124 
long wali_syscall_getsid (wasm_exec_env_t exec_env, long a1) {
	SC(getsid);
	return __syscall1(SYS_getsid, a1);
}

// 130 
long wali_syscall_rt_sigsuspend (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(rt_sigsuspend);
	return __syscall2(SYS_rt_sigsuspend, MADDR(a1), a2);
}

// 131 
long wali_syscall_sigaltstack (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(sigaltstack);
  Addr wasm_ss = MADDR(a1), wasm_old_ss = MADDR(a2);
  
  stack_t ss = {0}, old_ss = {0};
  stack_t* ss_ptr = copy_sigstack(exec_env, wasm_ss, &ss);
  stack_t* old_ss_ptr = copy_sigstack(exec_env, wasm_old_ss, &old_ss);

	return __syscall2(SYS_sigaltstack, ss_ptr, old_ss_ptr);
}

// 132 
long wali_syscall_utime (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(utime);
  FATALSC(utime, "Obsolete -- Use \'utimesnsat\' instead");
  #if __x86_64__
  #elif __aarch64__ || __riscv64__
  #endif
  return -1;
}

// 137 
long wali_syscall_statfs (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(statfs);
	return __syscall2(SYS_statfs, MADDR(a1), MADDR(a2));
}

// 138 
long wali_syscall_fstatfs (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(fstatfs);
	return __syscall2(SYS_fstatfs, a1, MADDR(a2));
}

// 160 
long wali_syscall_setrlimit (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(setrlimit);
	return __syscall2(SYS_setrlimit, a1, MADDR(a2));
}

// 186
long wali_syscall_gettid (wasm_exec_env_t exec_env) {
  SC(gettid);
  return __syscall0(SYS_gettid);
}

// 202 
long wali_syscall_futex (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5, long a6) {
	SC(futex);
	return __syscall6(SYS_futex, MADDR(a1), a2, a3, MADDR(a4), MADDR(a5), a6);
}

// 217 
long wali_syscall_getdents64 (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(getdents64);
	return __syscall3(SYS_getdents64, a1, MADDR(a2), a3);
}

// 218 
long wali_syscall_set_tid_address (wasm_exec_env_t exec_env, long a1) {
  SC(set_tid_address);
  return __syscall1(SYS_set_tid_address, MADDR(a1));
}

// 221 TODO
long wali_syscall_fadvise (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(fadvise);
	ERRSC(fadvise);
	return __syscall4(SYS_fadvise64, a1, a2, a3, a4);
}

// 228 
long wali_syscall_clock_gettime (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(clock_gettime);
	return __syscall2(SYS_clock_gettime, a1, MADDR(a2));
}

// 230 
long wali_syscall_clock_nanosleep (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(clock_nanosleep);
	return __syscall4(SYS_clock_nanosleep, a1, a2, MADDR(a3), MADDR(a4));
}

// 231 TODO
long wali_syscall_exit_group (wasm_exec_env_t exec_env, long a1) {
	SC(exit_group);
  ERRSC(exit_group);
  wali_proc_exit(exec_env, a1);
  return -1;
}

// 257 
long wali_syscall_openat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(openat);
  #if __aarch64__
	  return __syscall4(SYS_openat, a1, MADDR(a2), swap_open_flags(a3), a4);
  #else
	  return __syscall4(SYS_openat, a1, MADDR(a2), a3, a4);
  #endif
}

// 258 
long wali_syscall_mkdirat (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(mkdirat);
	return __syscall3(SYS_mkdirat, a1, MADDR(a2), a3);
}

// 260 
long wali_syscall_fchownat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(fchownat);
	return __syscall5(SYS_fchownat, a1, MADDR(a2), a3, a4, a5);
}

// 262 
long wali_syscall_fstatat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(fstatat);
  #if __x86_64__
	  return __syscall4(SYS_newfstatat, a1, MADDR(a2), MADDR(a3), a4);
  #elif __aarch64__ || __riscv64__
    Addr wasm_stat = MADDR(a3);
    struct stat sb;
    long retval = __syscall4(SYS_newfstatat, a1, MADDR(a2), &sb, a4);
    copy2wasm_stat_struct (exec_env, wasm_stat, &sb);
    return retval;
  #endif
}

// 263 
long wali_syscall_unlinkat (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(unlinkat);
	return __syscall3(SYS_unlinkat, a1, MADDR(a2), a3);
}

// 265 
long wali_syscall_linkat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(linkat);
	return __syscall5(SYS_linkat, a1, MADDR(a2), a3, MADDR(a4), a5);
}

// 266 
long wali_syscall_symlinkat (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(symlinkat);
	return __syscall3(SYS_symlinkat, MADDR(a1), a2, MADDR(a3));
}

// 267 
long wali_syscall_readlinkat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(readlinkat);
	return __syscall4(SYS_readlinkat, a1, MADDR(a2), MADDR(a3), a4);
}

// 268 
long wali_syscall_fchmodat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(fchmodat);
	return __syscall4(SYS_fchmodat, a1, MADDR(a2), a3, a4);
}

// 269 
long wali_syscall_faccessat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(faccessat);
	return __syscall4(SYS_faccessat, a1, MADDR(a2), a3, a4);
}

// 270 
long wali_syscall_pselect6 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5, long a6) {
	SC(pselect6);
  ERR("pselect args | a1: %ld, a2: %ld, a3: %ld, a4: %ld, a5: %ld, a6: %ld", a1, a2, a3, a4, a5, a6);
  Addr wasm_psel_sm = MADDR(a6);
  long sm_struct[2];
  long* sm_struct_ptr = copy_pselect6_sigmask(exec_env, wasm_psel_sm, sm_struct);
	return __syscall6(SYS_pselect6, a1, MADDR(a2), MADDR(a3), MADDR(a4), MADDR(a5), sm_struct_ptr);
}

// 271 
long wali_syscall_ppoll (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(ppoll);
	return __syscall5(SYS_ppoll, MADDR(a1), a2, MADDR(a3), MADDR(a4), a5);
}
/* Since poll needs a time conversion on pointer, need to use a different alias call */
long wali_syscall_ppoll_aliased (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(ppoll-alias);
	return __syscall5(SYS_ppoll, MADDR(a1), a2, a3, MADDR(a4), a5);
}

// 280 
long wali_syscall_utimensat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(utimensat);
	return __syscall4(SYS_utimensat, a1, MADDR(a2), MADDR(a3), a4);
}

// 284 
long wali_syscall_eventfd (wasm_exec_env_t exec_env, long a1) {
	SC(eventfd);
  #if __x86_64__
	  return __syscall1(SYS_eventfd, a1);
  #elif __aarch64__ || __riscv64__
    return wali_syscall_eventfd2(exec_env, a1, 0);
  #endif
}

// 290 TODO
long wali_syscall_eventfd2 (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(eventfd2);
	ERRSC(eventfd2);
	return __syscall2(SYS_eventfd2, a1, a2);
}

// 292 
long wali_syscall_dup3 (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(dup3);
  #if __aarch64__
	  return __syscall3(SYS_dup3, a1, a2, swap_open_flags(a3));
  #else
	  return __syscall3(SYS_dup3, a1, a2, a3);
  #endif
}

// 293 
long wali_syscall_pipe2 (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(pipe2);
  #if __aarch64__
	  return __syscall2(SYS_pipe2, MADDR(a1), swap_open_flags(a2));
  #else
	  return __syscall2(SYS_pipe2, MADDR(a1), a2);
  #endif
}

// 302 
long wali_syscall_prlimit64 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(prlimit64);
	return __syscall4(SYS_prlimit64, a1, a2, MADDR(a3), MADDR(a4));
}

// 316 
long wali_syscall_renameat2 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(renameat2);
	return __syscall5(SYS_renameat2, a1, MADDR(a2), a3, MADDR(a4), a5);
}

// 318 
long wali_syscall_getrandom (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(getrandom);
	return __syscall3(SYS_getrandom, MADDR(a1), a2, a3);
}

// 332
long wali_syscall_statx (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(statx);
	return __syscall5(SYS_statx, a1, MADDR(a2), a3, a4, MADDR(a5));
}

// 439 
long wali_syscall_faccessat2 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(faccessat2);
	return __syscall4(439, a1, MADDR(a2), a3, a4);
}

/***** Non-syscall methods *****/
int wali_sigsetjmp (wasm_exec_env_t exec_env, int sigjmp_buf_addr, int savesigs) {
  PC(sigsetjmp);
  Addr wasm_sigjmp_buf = MADDR(sigjmp_buf_addr);
  struct __libc_jmp_buf_tag* env = copy_jmp_buf(exec_env, wasm_sigjmp_buf);
  int retval = __libc_sigsetjmp_asm(env, savesigs);
  ERRSC(sigsetjmp, "Unsupported in WALI right now, continuing execution with "
   "flag on siglongjmp");
  if (retval == 0) {
    copy2wasm_jmp_buf(exec_env, wasm_sigjmp_buf, env);
    free(env);
  }
  return retval;
}

_Noreturn void wali_siglongjmp (wasm_exec_env_t exec_env, int sigjmp_buf_addr, int val) {
  PC(siglongjmp);
  struct __libc_jmp_buf_tag* env = copy_jmp_buf(exec_env, MADDR(sigjmp_buf_addr));
  FATALSC(siglongjmp, "Not supported in WALI yet, exiting code...");
  exit(0);
  //__libc_siglongjmp(env, val);
}


/***** Startup *****/
void wali_call_ctors(wasm_exec_env_t exec_env) {
  PC(wali_call_ctors);
}

void wali_call_dtors(wasm_exec_env_t exec_env) {
  PC(wali_call_dtors);
}

void wali_proc_exit(wasm_exec_env_t exec_env, long v) {
  PC(exit);
  exit(v);
}

int wali_cl_get_argc (wasm_exec_env_t exec_env) {
  PC(cl_get_argc);
  return app_argc;
}

int wali_cl_get_argv_len (wasm_exec_env_t exec_env, int arg_idx) {
  PC(cl_get_argc_len);
  return strlen(app_argv[arg_idx]);
}

int wali_cl_copy_argv (wasm_exec_env_t exec_env, int argv_addr, int arg_idx) {
  PC(cl_copy_argv);
  Addr argv = MADDR(argv_addr);
  strcpy((char*)argv, app_argv[arg_idx]);
  return 0;
}


/***** Threads *****/
typedef struct {
  /* Initial function */
  wasm_function_inst_t start_fn;
  /* Wasm address for args */
  int arg;
  /* Wasm Thread ID */
  int tid;
} WasmThreadStartArg;

/* Thread dispatcher function calls into WASM  */
static void*
wali_dispatch_thread_libc(void *exec_env_ptr) {
  wasm_exec_env_t exec_env = (wasm_exec_env_t) exec_env_ptr;
  WasmThreadStartArg *thread_arg = (WasmThreadStartArg*) exec_env->thread_arg;
  
  wasm_exec_env_set_thread_info(exec_env);
  /* Libc start fn: (int thread_id, void *arg) */
  uint32_t wasm_argv[2];
  // Dispatcher is part of child thread; can get tid using syscall
  wasm_argv[0] = thread_arg->tid;
  wasm_argv[1] = thread_arg->arg;

  ERR("Dispatcher | Thread ID: %d\n", wasm_argv[0]);

  if (!wasm_runtime_call_wasm(exec_env, thread_arg->start_fn, 2, wasm_argv)) {
    /* Execption has already been spread during throwing */
  }

  ERR("================ Thread [%d] exiting ==============\n", gettid());
  // Cleanup
  wasm_runtime_free(thread_arg);
  exec_env->thread_arg = NULL;
  
  return NULL;
}

int wali_wasm_thread_spawn (wasm_exec_env_t exec_env, int setup_fnptr, int arg_wasm) {
  SC(wasm_thread_spawn (clone));
  wasm_module_inst_t module_inst = get_module_inst(exec_env);
  wasm_module_t module = wasm_runtime_get_module(module_inst);
  bh_assert(module);
  bh_assert(module_inst);

  wasm_module_inst_t new_module_inst = NULL;
  WasmThreadStartArg *thread_start_arg = NULL;
  uint32_t stack_size = 8192;
  int thread_id = -1;
  int ret = -1;

  /* Table 0 is only supported currently */
  wasm_function_inst_t setup_wasm_fn = 
      wasm_runtime_get_indirect_function(module_inst, 0, setup_fnptr);


  stack_size = ((WASMModuleInstance *)module_inst)->default_wasm_stack_size;

  /* New module instance -- custom data, import function registration, etc. */
  if (!(new_module_inst = wasm_runtime_instantiate_internal(
            module, true, exec_env, stack_size, 0, NULL, 0)))
      return -1;

  wasm_runtime_set_custom_data_internal(
      new_module_inst, wasm_runtime_get_custom_data(module_inst));

  if (!(wasm_cluster_dup_c_api_imports(new_module_inst, module_inst)))
      goto thread_spawn_fail;
  /** **/

  /** Setup args to pass to startup dispatcher **/
  if (!(thread_start_arg = wasm_runtime_malloc(sizeof(WasmThreadStartArg)))) {
      FATALSC(wasm_thread_spawn, "Runtime args allocation failed");
      goto thread_spawn_fail;
  }

  thread_start_arg->tid = thread_id = THREAD_ID++;

  thread_start_arg->start_fn = setup_wasm_fn;
  thread_start_arg->arg = arg_wasm;
  /** **/

  /** Create and dispatch the thread (language-independent: currently just C); 
  * Thread ID of the created thread is sent back to parent */
  ret = wasm_cluster_create_thread(exec_env, new_module_inst, false,
                                   wali_dispatch_thread_libc, thread_start_arg);
  if (ret != 0) {
      FATALSC(wasm_thread_spawn, "Failed to spawn a new thread");
      goto thread_spawn_fail;
  }

  ERR("Parent of Dispatcher | Thread ID: %d\n", thread_id);
  return thread_id;

thread_spawn_fail:
  if (new_module_inst)
      wasm_runtime_deinstantiate_internal(new_module_inst, true);
  if (thread_start_arg)
      wasm_runtime_free(thread_start_arg);

  return -1;
}




