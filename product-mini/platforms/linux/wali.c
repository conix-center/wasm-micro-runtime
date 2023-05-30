#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/mman.h>

#include "wali.h"
#include "copy.h"
#include "../interpreter/sigtable.h"

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

void wali_init_native() {
  NATIVE_PAGESIZE = sysconf(_SC_PAGE_SIZE);
  MMAP_PAGELEN = 0;
  WASM_PAGELEN = 0;
  WASM_TO_NATIVE_PAGE = WASM_PAGESIZE / NATIVE_PAGESIZE;
  // Set in mmap
  BASE_MEMSIZE = 0;
}

static __inline long __syscall0(long n)
{
	unsigned long ret;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall1(long n, long a1)
{
	unsigned long ret;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall2(long n, long a1, long a2)
{
	unsigned long ret;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2)
						  : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall3(long n, long a1, long a2, long a3)
{
	unsigned long ret;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall4(long n, long a1, long a2, long a3, long a4)
{
	unsigned long ret;
	register long r10 __asm__("r10") = a4;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10): "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall5(long n, long a1, long a2, long a3, long a4, long a5)
{
	unsigned long ret;
	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10), "r"(r8) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	unsigned long ret;
	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	register long r9 __asm__("r9") = a6;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10), "r"(r8), "r"(r9) : "rcx", "r11", "memory");
	return ret;
}

#define __syscall1(n, a1) __syscall1(n, (long)a1)
#define __syscall2(n, a1, a2) __syscall2(n, (long)a1, (long)a2)
#define __syscall3(n, a1, a2, a3) __syscall3(n, (long)a1, (long)a2, (long)a3)
#define __syscall4(n, a1, a2, a3, a4) __syscall4(n, (long)a1, (long)a2, (long)a3, (long)a4)
#define __syscall5(n, a1, a2, a3, a4, a5) __syscall5(n, (long)a1, (long)a2, (long)a3, (long)a4, (long)a5)
#define __syscall6(n, a1, a2, a3, a4, a5, a6) __syscall6(n, (long)a1, (long)a2, (long)a3, (long)a4, (long)a5, (long)a6)


#define ATOM(f) LOG_VERBOSE("WALI: Atomic (use with care) | " # f)
#define PW(f)  LOG_VERBOSE("WALI: " # f)
#define SC(f)  LOG_VERBOSE("WALI: SC | " # f)
#define ERRSC(f,...) { \
  LOG_WARNING("WALI: SC \"" # f "\" not implemented correctly yet! " __VA_ARGS__);  \
}



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
	return __syscall3(SYS_open, MADDR(a1), a2, a3);
}

// 3
long wali_syscall_close (wasm_exec_env_t exec_env, long a1) {
	SC(close);
	return __syscall1(SYS_close, a1);
}

// 4 
long wali_syscall_stat (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(stat);
	return __syscall2(SYS_stat, MADDR(a1), MADDR(a2));
}

// 5 
long wali_syscall_fstat (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(fstat);
	return __syscall2(SYS_fstat, a1, MADDR(a2));
}

// 6 
long wali_syscall_lstat (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(lstat);
	return __syscall2(SYS_lstat, MADDR(a1), MADDR(a2));
}

// 7 TODO
long wali_syscall_poll (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(poll);
	ERRSC(poll);
	return __syscall3(SYS_poll, MADDR(a1), a2, a3);
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

  Addr mem_addr = (Addr) __syscall6(SYS_mmap, mmap_addr, a2, a3, MAP_FIXED|a4, (int)a5, a6);
  if (mem_addr == MAP_FAILED) {
    LOG_ERROR("Failed to mmap!\n");
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
      wasm_enlarge_memory(module, inc_wasm_pages, true);
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
	ERRSC(brk, "brk syscall is nop in WASM right now");
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
	ERRSC(readv);
	return __syscall3(SYS_readv, a1, MADDR(a2), a3);
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
	return __syscall2(SYS_access, MADDR(a1), a2);
}

// 22 
long wali_syscall_pipe (wasm_exec_env_t exec_env, long a1) {
	SC(pipe);
	return __syscall1(SYS_pipe, MADDR(a1));
}

// 23 TODO
long wali_syscall_select (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(select);
	ERRSC(select);
	return __syscall5(SYS_select, a1, MADDR(a2), MADDR(a3), MADDR(a4), MADDR(a5));
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
	return __syscall5(SYS_mremap, MADDR(a1), a2, a3, a4, a5);
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
	return __syscall2(SYS_dup2, a1, a2);
}

// 35
long wali_syscall_nanosleep (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(nanosleep);
	return __syscall2(SYS_nanosleep, MADDR(a1), MADDR(a2));
}

// 37 
long wali_syscall_alarm (wasm_exec_env_t exec_env, long a1) {
	SC(alarm);
	return __syscall1(SYS_alarm, a1);
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
long wali_syscall_sendto (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(sendto);
	return __syscall4(SYS_sendto, a1, MADDR(a2), a3, a4);
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
	return __syscall0(SYS_fork);
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
	return __syscall3(SYS_fcntl, a1, a2, a3);
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
	ERRSC(getdents, "Not going to support this yet; use getdents64");
	return __syscall3(SYS_getdents, a1, MADDR(a2), a3);
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
	return __syscall2(SYS_rename, MADDR(a1), MADDR(a2));
}

// 83
long wali_syscall_mkdir (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(mkdir);
	return __syscall2(SYS_mkdir, MADDR(a1), a2);
}

// 84 
long wali_syscall_rmdir (wasm_exec_env_t exec_env, long a1) {
	SC(rmdir);
	return __syscall1(SYS_rmdir, MADDR(a1));
}

// 86 
long wali_syscall_link (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(link);
	return __syscall2(SYS_link, MADDR(a1), MADDR(a2));
}

// 87 
long wali_syscall_unlink (wasm_exec_env_t exec_env, long a1) {
	SC(unlink);
	return __syscall1(SYS_unlink, MADDR(a1));
}

// 88 
long wali_syscall_symlink (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(symlink);
	return __syscall2(SYS_symlink, MADDR(a1), MADDR(a2));
}

// 89 
long wali_syscall_readlink (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(readlink);
	return __syscall3(SYS_readlink, MADDR(a1), MADDR(a2), a3);
}

// 90 
long wali_syscall_chmod (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(chmod);
	return __syscall2(SYS_chmod, MADDR(a1), a2);
}

// 91 
long wali_syscall_fchmod (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(fchmod);
	return __syscall2(SYS_fchmod, a1, a2);
}

// 92 
long wali_syscall_chown (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(chown);
	return __syscall3(SYS_chown, MADDR(a1), a2, a3);
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
	return __syscall2(SYS_utime, MADDR(a1), MADDR(a2));
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

// 217 
long wali_syscall_getdents64 (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(getdents64);
	return __syscall3(SYS_getdents64, a1, MADDR(a2), a3);
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
	return __syscall4(SYS_openat, a1, MADDR(a2), a3, a4);
}

// 263 
long wali_syscall_unlinkat (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(unlinkat);
	return __syscall3(SYS_unlinkat, a1, MADDR(a2), a3);
}

// 269 
long wali_syscall_faccessat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(faccessat);
	return __syscall4(SYS_faccessat, a1, MADDR(a2), a3, a4);
}

// 280 
long wali_syscall_utimensat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(utimensat);
	return __syscall4(SYS_utimensat, a1, MADDR(a2), MADDR(a3), a4);
}

// 284 
long wali_syscall_eventfd (wasm_exec_env_t exec_env, long a1) {
	SC(eventfd);
	return __syscall1(SYS_eventfd, a1);
}

// 290 TODO
long wali_syscall_eventfd2 (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(eventfd2);
	ERRSC(eventfd2);
	return __syscall2(SYS_eventfd2, a1, a2);
}

// 293 
long wali_syscall_pipe2 (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(pipe2);
	return __syscall2(SYS_pipe2, MADDR(a1), a2);
}

// 302 
long wali_syscall_prlimit64 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(prlimit64);
	return __syscall4(SYS_prlimit64, a1, a2, MADDR(a3), MADDR(a4));
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
uintptr_t wali__get_tp (wasm_exec_env_t exec_env) {
  uintptr_t tp;
	__asm__ ("mov %%fs:0,%0" : "=r" (tp) );
  PW(get_tp);
	return tp;
}

int wali_sigsetjmp (wasm_exec_env_t exec_env, int sigjmp_buf_addr, int savesigs) {
  PW(sigsetjmp);
  Addr wasm_sigjmp_buf = MADDR(sigjmp_buf_addr);
  struct __libc_jmp_buf_tag* env = copy_jmp_buf(exec_env, wasm_sigjmp_buf);
  int retval = __libc_sigsetjmp_asm(env, savesigs);
  ERRSC(sigsetjmp, "sigsetjmp is UNSTABLE in WASM right now");
  if (retval == 0) {
    copy2wasm_jmp_buf(exec_env, wasm_sigjmp_buf, env);
    free(env);
  }
  return retval;
}

_Noreturn void wali_siglongjmp (wasm_exec_env_t exec_env, int sigjmp_buf_addr, int val) {
  PW(siglongjmp);
  struct __libc_jmp_buf_tag* env = copy_jmp_buf(exec_env, MADDR(sigjmp_buf_addr));
  ERRSC(siglongjmp, "siglongjmp is UNSTABLE in WASM right now");
  __libc_siglongjmp(env, val);
}


/***** Startup *****/
void wali_call_ctors(wasm_exec_env_t exec_env) {
  PW(wali_call_ctors);
}

void wali_call_dtors(wasm_exec_env_t exec_env) {
  PW(wali_call_dtors);
}

void wali_proc_exit(wasm_exec_env_t exec_env, long v) {
  PW(exit);
  exit(v);
}

int wali_cl_get_argc (wasm_exec_env_t exec_env) {
  PW(cl_get_argc);
  return app_argc;
}

int wali_cl_get_argv_len (wasm_exec_env_t exec_env, int arg_idx) {
  PW(cl_get_argc_len);
  return strlen(app_argv[arg_idx]);
}

int wali_cl_copy_argv (wasm_exec_env_t exec_env, int argv_addr, int arg_idx) {
  PW(cl_copy_argv);
  Addr argv = MADDR(argv_addr);
  strcpy(argv, app_argv[arg_idx]);
  return 0;
}


/***** Atomics *****/
int wali_a_cas (wasm_exec_env_t exec_env, long p, int t, int s) {
  ATOM(a_cas);
	__asm__ __volatile__ (
		"lock ; cmpxchg %3, %1"
		: "=a"(t), "=m"(*MADDR(p)) : "a"(t), "r"(s) : "memory" );
	return t;

}

void* wali_a_cas_p (wasm_exec_env_t exec_env, long p, long t, long s) {
  ATOM(a_cas_p);
  Addr tm = MADDR(t);
	__asm__( "lock ; cmpxchg %3, %1"
		: "=a"(tm), "=m"(*(void *volatile *)MADDR(p))
		: "a"(tm), "r"(MADDR(s)) : "memory" );
	return tm;
}

int wali_a_swap (wasm_exec_env_t exec_env, long p, int v) {
  ATOM(a_swap);
	__asm__ __volatile__(
		"xchg %0, %1"
		: "=r"(v), "=m"(*MADDR(p)) : "0"(v) : "memory" );
	return v;
}

int wali_a_fetch_add (wasm_exec_env_t exec_env, long p, int v) {
  ATOM(a_fetch_add);
	__asm__ __volatile__(
		"lock ; xadd %0, %1"
		: "=r"(v), "=m"(*MADDR(p)) : "0"(v) : "memory" );
	return v;
}

void wali_a_and (wasm_exec_env_t exec_env, long p, int v) {
  ATOM(a_and);
	__asm__ __volatile__(
		"lock ; and %1, %0"
		: "=m"(*MADDR(p)) : "r"(v) : "memory" );
}

void wali_a_or (wasm_exec_env_t exec_env, long p, int v) {
  ATOM(a_or);
	__asm__ __volatile__(
		"lock ; or %1, %0"
		: "=m"(*MADDR(p)) : "r"(v) : "memory" );
}

void wali_a_and_64 (wasm_exec_env_t exec_env, long p, long v) {
  ATOM(a_and_64);
	__asm__ __volatile(
		"lock ; and %1, %0"
		 : "=m"(*MADDR(p)) : "r"(v) : "memory" );
}

void wali_a_or_64 (wasm_exec_env_t exec_env, long p, long v) {
  ATOM(a_or_64);
	__asm__ __volatile__(
		"lock ; or %1, %0"
		 : "=m"(*MADDR(p)) : "r"(v) : "memory" );
}

void wali_a_inc (wasm_exec_env_t exec_env, long p) {
  ATOM(a_inc);
  Addr pm = MADDR(p);
	__asm__ __volatile__(
		"lock ; incl %0"
		: "=m"(*pm) : "m"(*pm) : "memory" );
}

void wali_a_dec (wasm_exec_env_t exec_env, long p) {
  ATOM(a_dec);
  Addr pm = MADDR(p);
	__asm__ __volatile__(
		"lock ; decl %0"
		: "=m"(*pm) : "m"(*pm) : "memory" );
}

void wali_a_store (wasm_exec_env_t exec_env, long p, int x) {
  ATOM(a_store);
	__asm__ __volatile__(
		"mov %1, %0 ; lock ; orl $0,(%%rsp)"
		: "=m"(*MADDR(p)) : "r"(x) : "memory" );
}

void wali_a_barrier (wasm_exec_env_t exec_env) {
  ATOM(a_barrier);
	__asm__ __volatile__( "" : : : "memory" );
}

void wali_a_spin (wasm_exec_env_t exec_env) {
  ATOM(a_spin);
	__asm__ __volatile__( "pause" : : : "memory" );
}

void wali_a_crash (wasm_exec_env_t exec_env) {
  ATOM(a_crash);
	__asm__ __volatile__( "hlt" : : : "memory" );
}

int wali_a_ctz_64 (wasm_exec_env_t exec_env, long x) {
  ATOM(a_ctz_64);
	__asm__( "bsf %1,%0" : "=r"(x) : "r"(x) );
	return x;
}

int wali_a_clz_64 (wasm_exec_env_t exec_env, long x) {
  ATOM(a_clz_64);
	__asm__( "bsr %1,%0 ; xor $63,%0" : "=r"(x) : "r"(x) );
	return x;
}

/*************************/







