#include "bh_platform.h"
#include <stdlib.h>
#include <sys/syscall.h>

#include "wali.h"

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


#define PW(f)  LOG_VERBOSE("WALI: " # f)
#define SC(f)  LOG_VERBOSE("WALI: SC | " # f)
#define ERRSC(f,...) { \
  LOG_ERROR("WALI: SC \"" # f "\" not implemented correctly yet! " __VA_ARGS__);  \
  return -1;  \
}

uint32 psize;
typedef uint8_t* Addr;
#define MADDR(wasm_addr) ({  \
  wasm_runtime_get_memory_ptr(get_module_inst(exec_env), &psize) + wasm_addr; \
})

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
	ERRSC(stat, "Use statx instead");
	return __syscall2(SYS_stat, MADDR(a1), MADDR(a2));
}

// 5
long wali_syscall_fstat (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(fstat);
	ERRSC(fstat, "Use statx instead");
	return __syscall2(SYS_fstat, a1, MADDR(a2));
}

// 6
long wali_syscall_lstat (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(lstat);
	ERRSC(lstat, "Use statx instead");
	return __syscall2(SYS_lstat, MADDR(a1), MADDR(a2));
}

// 7
long wali_syscall_poll (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(poll);
	ERRSC(poll);
	return __syscall3(SYS_poll, MADDR(a1), a2, a3);
}

// 8
long wali_syscall_lseek (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(lseek);
	ERRSC(lseek);
	return __syscall3(SYS_lseek, a1, a2, a3);
}

// 9
/*
long wali_syscall_mmap2 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5, long a6) {
	SC(mmap2);
	ERRSC(mmap2);
	return __syscall6(SYS_mmap2, MADDR(a1), a2, a3, a4, a5, a6);
}*/

// 10
long wali_syscall_mprotect (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(mprotect);
	ERRSC(mprotect);
	return __syscall3(SYS_mprotect, MADDR(a1), a2, a3);
}

// 11
long wali_syscall_munmap (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(munmap);
	ERRSC(munmap);
	return __syscall2(SYS_munmap, MADDR(a1), a2);
}

// 12
long wali_syscall_brk (wasm_exec_env_t exec_env, long a1) {
	SC(brk);
	ERRSC(brk);
	return __syscall1(SYS_brk, MADDR(a1));
}

// 13
long wali_syscall_rt_sigaction (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(rt_sigaction);
	ERRSC(rt_sigaction);
	return __syscall4(SYS_rt_sigaction, a1, MADDR(a2), MADDR(a3), a4);
}

// 14
long wali_syscall_rt_sigprocmask (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(rt_sigprocmask);
	ERRSC(rt_sigprocmask);
	return __syscall4(SYS_rt_sigprocmask, a1, MADDR(a2), MADDR(a3), a4);
}

// 15
long wali_syscall_rt_sigreturn (wasm_exec_env_t exec_env, long a1) {
	SC(rt_sigreturn);
	ERRSC(rt_sigreturn);
	return __syscall1(SYS_rt_sigreturn, a1);
}

// 16
long wali_syscall_ioctl (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(ioctl);
	ERRSC(ioctl);
	return __syscall3(SYS_ioctl, a1, a2, a3);
}

// 17
long wali_syscall_pread64 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(pread64);
	ERRSC(pread64);
	return __syscall4(SYS_pread64, a1, MADDR(a2), a3, a4);
}

// 18
long wali_syscall_pwrite64 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(pwrite64);
	ERRSC(pwrite64);
	return __syscall4(SYS_pwrite64, a1, MADDR(a2), a3, a4);
}

// 19
long wali_syscall_readv (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(readv);
	ERRSC(readv);
	return __syscall3(SYS_readv, a1, MADDR(a2), a3);
}

// 20
long wali_syscall_writev (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(writev);
	ERRSC(writev);
	return __syscall3(SYS_writev, a1, MADDR(a2), a3);
}

// 21
long wali_syscall_access (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(access);
	ERRSC(access);
	return __syscall2(SYS_access, MADDR(a1), a2);
}

// 22
long wali_syscall_pipe (wasm_exec_env_t exec_env, long a1) {
	SC(pipe);
	ERRSC(pipe);
	return __syscall1(SYS_pipe, MADDR(a1));
}

// 23
long wali_syscall_select (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(select);
	ERRSC(select);
	return __syscall5(SYS_select, a1, MADDR(a2), MADDR(a3), MADDR(a4), MADDR(a5));
}

// 24
long wali_syscall_sched_yield (wasm_exec_env_t exec_env) {
	SC(sched_yield);
	ERRSC(sched_yield);
	return __syscall0(SYS_sched_yield);
}

// 25
long wali_syscall_mremap (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(mremap);
	ERRSC(mremap);
	return __syscall5(SYS_mremap, MADDR(a1), a2, a3, a4, a5);
}

// 26
long wali_syscall_msync (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(msync);
	ERRSC(msync);
	return __syscall3(SYS_msync, MADDR(a1), a2, a3);
}

// 28
long wali_syscall_madvise (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(madvise);
	ERRSC(madvise);
	return __syscall3(SYS_madvise, MADDR(a1), a2, a3);
}

// 32
long wali_syscall_dup (wasm_exec_env_t exec_env, long a1) {
	SC(dup);
	ERRSC(dup);
	return __syscall1(SYS_dup, a1);
}

// 33
long wali_syscall_dup2 (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(dup2);
	ERRSC(dup2);
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
	ERRSC(alarm);
	return __syscall1(SYS_alarm, a1);
}

// 39
long wali_syscall_getpid (wasm_exec_env_t exec_env) {
	SC(getpid);
	ERRSC(getpid);
	return __syscall0(SYS_getpid);
}

// 41
long wali_syscall_socket (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(socket);
	ERRSC(socket);
	return __syscall3(SYS_socket, a1, a2, a3);
}

// 42
long wali_syscall_connect (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(connect);
	ERRSC(connect);
	return __syscall3(SYS_connect, a1, MADDR(a2), a3);
}

// 43
long wali_syscall_accept (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(accept);
	ERRSC(accept);
	return __syscall3(SYS_accept, a1, MADDR(a2), a3);
}

// 44
long wali_syscall_sendto (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(sendto);
	ERRSC(sendto);
	return __syscall4(SYS_sendto, a1, MADDR(a2), a3, a4);
}

// 45
long wali_syscall_recvfrom (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5, long a6) {
	SC(recvfrom);
	ERRSC(recvfrom);
	return __syscall6(SYS_recvfrom, a1, MADDR(a2), a3, a4, MADDR(a5), MADDR(a6));
}

// 46
long wali_syscall_sendmsg (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(sendmsg);
	ERRSC(sendmsg);
	return __syscall3(SYS_sendmsg, a1, MADDR(a2), a3);
}

// 47
long wali_syscall_recvmsg (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(recvmsg);
	ERRSC(recvmsg);
	return __syscall3(SYS_recvmsg, a1, MADDR(a2), a3);
}

// 48
long wali_syscall_shutdown (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(shutdown);
	ERRSC(shutdown);
	return __syscall2(SYS_shutdown, a1, a2);
}

// 49
long wali_syscall_bind (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(bind);
	ERRSC(bind);
	return __syscall3(SYS_bind, a1, MADDR(a2), a3);
}

// 50
long wali_syscall_listen (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(listen);
	ERRSC(listen);
	return __syscall2(SYS_listen, a1, a2);
}

// 51
long wali_syscall_getsockname (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(getsockname);
	ERRSC(getsockname);
	return __syscall3(SYS_getsockname, a1, MADDR(a2), MADDR(a3));
}

// 52
long wali_syscall_getpeername (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(getpeername);
	ERRSC(getpeername);
	return __syscall3(SYS_getpeername, a1, MADDR(a2), MADDR(a3));
}

// 54
long wali_syscall_setsockopt (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(setsockopt);
	ERRSC(setsockopt);
	return __syscall5(SYS_setsockopt, a1, a2, a3, MADDR(a4), a5);
}

// 55
long wali_syscall_getsockopt (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(getsockopt);
	ERRSC(getsockopt);
	return __syscall5(SYS_getsockopt, a1, a2, a3, MADDR(a4), MADDR(a5));
}

// 57
long wali_syscall_fork (wasm_exec_env_t exec_env) {
	SC(fork);
	return __syscall0(SYS_fork);
}

// 61
long wali_syscall_wait4 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(wait4);
	ERRSC(wait4);
	return __syscall4(SYS_wait4, a1, MADDR(a2), a3, MADDR(a4));
}

// 62
long wali_syscall_kill (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(kill);
	ERRSC(kill);
	return __syscall2(SYS_kill, a1, a2);
}

// 63
long wali_syscall_uname (wasm_exec_env_t exec_env, long a1) {
	SC(uname);
	ERRSC(uname);
	return __syscall1(SYS_uname, MADDR(a1));
}

// 72
long wali_syscall_fcntl (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(fcntl);
	ERRSC(fcntl);
	return __syscall3(SYS_fcntl, a1, a2, a3);
}

// 73
long wali_syscall_flock (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(flock);
	ERRSC(flock);
	return __syscall2(SYS_flock, a1, a2);
}

// 74
long wali_syscall_fsync (wasm_exec_env_t exec_env, long a1) {
	SC(fsync);
	ERRSC(fsync);
	return __syscall1(SYS_fsync, a1);
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

// 83
long wali_syscall_mkdir (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(mkdir);
	return __syscall2(SYS_mkdir, MADDR(a1), a2);
}

// 84
long wali_syscall_rmdir (wasm_exec_env_t exec_env, long a1) {
	SC(rmdir);
	ERRSC(rmdir);
	return __syscall1(SYS_rmdir, MADDR(a1));
}

// 86
long wali_syscall_link (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(link);
	ERRSC(link);
	return __syscall2(SYS_link, MADDR(a1), MADDR(a2));
}

// 87
long wali_syscall_unlink (wasm_exec_env_t exec_env, long a1) {
	SC(unlink);
	ERRSC(unlink);
	return __syscall1(SYS_unlink, MADDR(a1));
}

// 88
long wali_syscall_symlink (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(symlink);
	ERRSC(symlink);
	return __syscall2(SYS_symlink, MADDR(a1), MADDR(a2));
}

// 89
long wali_syscall_readlink (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(readlink);
	ERRSC(readlink);
	return __syscall3(SYS_readlink, MADDR(a1), MADDR(a2), a3);
}

// 90
long wali_syscall_chmod (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(chmod);
	ERRSC(chmod);
	return __syscall2(SYS_chmod, MADDR(a1), a2);
}

// 91
long wali_syscall_fchmod (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(fchmod);
	ERRSC(fchmod);
	return __syscall2(SYS_fchmod, a1, a2);
}

// 92
long wali_syscall_chown (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(chown);
	ERRSC(chown);
	return __syscall3(SYS_chown, MADDR(a1), a2, a3);
}

// 93
long wali_syscall_fchown (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(fchown);
	ERRSC(fchown);
	return __syscall3(SYS_fchown, a1, a2, a3);
}

// 95
long wali_syscall_umask (wasm_exec_env_t exec_env, long a1) {
	SC(umask);
	ERRSC(umask);
	return __syscall1(SYS_umask, a1);
}

// 132
long wali_syscall_utime (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(utime);
	ERRSC(utime);
	return __syscall2(SYS_utime, MADDR(a1), MADDR(a2));
}

// 137
long wali_syscall_statfs (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(statfs);
	ERRSC(statfs);
	return __syscall2(SYS_statfs, MADDR(a1), MADDR(a2));
}

// 138
long wali_syscall_fstatfs (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(fstatfs);
	ERRSC(fstatfs);
	return __syscall2(SYS_fstatfs, a1, MADDR(a2));
}

// 217
long wali_syscall_getdents64 (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(getdents64);
	ERRSC(getdents64);
	return __syscall3(SYS_getdents64, a1, MADDR(a2), a3);
}

// 221
/*
long wali_syscall_fadvise (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(fadvise);
	ERRSC(fadvise);
	return __syscall4(SYS_fadvise, a1, a2, a3, a4);
}*/

// 257
long wali_syscall_openat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(openat);
	ERRSC(openat);
	return __syscall4(SYS_openat, a1, MADDR(a2), a3, a4);
}

// 263
long wali_syscall_unlinkat (wasm_exec_env_t exec_env, long a1, long a2, long a3) {
	SC(unlinkat);
	ERRSC(unlinkat);
	return __syscall3(SYS_unlinkat, a1, MADDR(a2), a3);
}

// 269
long wali_syscall_faccessat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(faccessat);
	ERRSC(faccessat);
	return __syscall4(SYS_faccessat, a1, MADDR(a2), a3, a4);
}

// 280
long wali_syscall_utimensat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4) {
	SC(utimensat);
	ERRSC(utimensat);
	return __syscall4(SYS_utimensat, a1, MADDR(a2), MADDR(a3), a4);
}

// 284
long wali_syscall_eventfd (wasm_exec_env_t exec_env, long a1) {
	SC(eventfd);
	ERRSC(eventfd);
	return __syscall1(SYS_eventfd, a1);
}

// 290
long wali_syscall_eventfd2 (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(eventfd2);
	ERRSC(eventfd2);
	return __syscall2(SYS_eventfd2, a1, a2);
}

// 293
long wali_syscall_pipe2 (wasm_exec_env_t exec_env, long a1, long a2) {
	SC(pipe2);
	ERRSC(pipe2);
	return __syscall2(SYS_pipe2, MADDR(a1), a2);
}

// 332
long wali_syscall_statx (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5) {
	SC(statx);
	return __syscall5(SYS_statx, a1, MADDR(a2), a3, a4, MADDR(a5));
}


/***** Non-syscall methods *****/
uintptr_t wali__get_tp (wasm_exec_env_t exec_env) {
  uintptr_t tp;
	__asm__ ("mov %%fs:0,%0" : "=r" (tp) );
  PW(get_tp);
	return tp;
}

void wali__wasm_call_dtors(wasm_exec_env_t exec_env) {
  PW(wasm_call_dtors);
}

void wali__wasi_proc_exit(wasm_exec_env_t exec_env, long v) {
  PW(exit);
  exit(1);
}

/*************************/







