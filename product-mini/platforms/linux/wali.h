#ifndef WALI_H
#define WALI_H

#include "wasm_export.h"
#include "bh_platform.h"
#include "aot_export.h"

/* Architecture defines */
#ifndef __riscv64__
#if __riscv
  #if __riscv_xlen == 64
    #define __riscv64__ 1
  #endif
#endif
#endif

#if !__x86_64__ && !__aarch64__ && !__riscv64__
#error "Unsupported architecture for WALI -- Only supports [x86_64, aarch64, riscv64]"
#endif


#define WASM_PAGESIZE 65536

typedef uint8_t* Addr;
typedef uint32_t FuncPtr_t;

#define BASE_ADDR() ({  \
  (Addr) wasm_runtime_addr_app_to_native(get_module_inst(exec_env), 0); \
})

#define MADDR(wasm_addr) ({  \
  Addr addr = wasm_addr ? (Addr) wasm_runtime_addr_app_to_native(get_module_inst(exec_env), wasm_addr) : NULL;  \
  if (addr == NULL) { ERR("NULL ADDRESS!\n"); } \
  addr; \
})

#define WADDR(mem_addr) ({  \
  wasm_runtime_addr_native_to_app(get_module_inst(exec_env), mem_addr); \
})

#define ERR(fmt, ...) LOG_VERBOSE("[%d] WALI: " fmt, gettid(), ## __VA_ARGS__)


#define FUNC_IDX(func) ({ wasm_runtime_get_function_idx(module_inst, func); })

/* Needs to be called only for AoT when using wasm_runtime_get_indirect_function */
#define FUNC_FREE(func) { \
  if (func && (get_module_inst(exec_env)->module_type == Wasm_Module_AoT)) { \
      wasm_runtime_free(func);  \
  } \
}

/* 0 = SIG_DFL; */
#define WASM_SIG_DFL (0)
#define WASM_SIG_ERR (-1)
#define WASM_SIG_IGN (-2)
/** Some internal structs for syscalls **/

/* This is the structure used for the rt_sigaction syscall on most archs,
 * but it can be overridden by a file with the same name in the top-level
 * arch dir for a given arch, if necessary. */
struct k_sigaction {
	void (*handler)(int);
	unsigned long flags;
	void (*restorer)(void);
	unsigned mask[2];
};

/* Setjmp/longjmp with signal handling */
typedef unsigned long __libc_jmp_buf_internal[8];

typedef struct __libc_jmp_buf_tag {
  __libc_jmp_buf_internal __jb;
  unsigned long __fl;
  unsigned long __ss[128/sizeof(long)];
} __libc_jmp_buf[1];

typedef __libc_jmp_buf __libc_sigjmp_buf;

/** **/

/** Init function **/
void wali_init_native ();

/** Syscalls **/
long wali_syscall_read (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_write (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_open (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_close (wasm_exec_env_t exec_env, long a1);
long wali_syscall_stat (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_fstat (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_lstat (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_poll (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_lseek (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_mmap (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5, long a6);
long wali_syscall_mprotect (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_munmap (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_brk (wasm_exec_env_t exec_env, long a1);
long wali_syscall_rt_sigaction (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_rt_sigprocmask (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_rt_sigreturn (wasm_exec_env_t exec_env, long a1);
long wali_syscall_ioctl (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_pread64 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_pwrite64 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_readv (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_writev (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_access (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_pipe (wasm_exec_env_t exec_env, long a1);
long wali_syscall_select (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5);
long wali_syscall_sched_yield (wasm_exec_env_t exec_env);
long wali_syscall_mremap (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5);
long wali_syscall_msync (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_mincore (wasm_exec_env_t exec_env);
long wali_syscall_madvise (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_shmget (wasm_exec_env_t exec_env);
long wali_syscall_shmat (wasm_exec_env_t exec_env);
long wali_syscall_shmctl (wasm_exec_env_t exec_env);
long wali_syscall_dup (wasm_exec_env_t exec_env, long a1);
long wali_syscall_dup2 (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_pause (wasm_exec_env_t exec_env);
long wali_syscall_nanosleep (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_getitimer (wasm_exec_env_t exec_env);
long wali_syscall_alarm (wasm_exec_env_t exec_env, long a1);
long wali_syscall_setitimer (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_getpid (wasm_exec_env_t exec_env);
long wali_syscall_sendfile (wasm_exec_env_t exec_env);
long wali_syscall_socket (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_connect (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_accept (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_sendto (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5, long a6);
long wali_syscall_recvfrom (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5, long a6);
long wali_syscall_sendmsg (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_recvmsg (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_shutdown (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_bind (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_listen (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_getsockname (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_getpeername (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_socketpair (wasm_exec_env_t exec_env);
long wali_syscall_setsockopt (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5);
long wali_syscall_getsockopt (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5);
long wali_syscall_clone (wasm_exec_env_t exec_env);
long wali_syscall_fork (wasm_exec_env_t exec_env);
long wali_syscall_vfork (wasm_exec_env_t exec_env);
long wali_syscall_execve (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_exit (wasm_exec_env_t exec_env, long a1);
long wali_syscall_wait4 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_kill (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_uname (wasm_exec_env_t exec_env, long a1);
long wali_syscall_semget (wasm_exec_env_t exec_env);
long wali_syscall_semop (wasm_exec_env_t exec_env);
long wali_syscall_semctl (wasm_exec_env_t exec_env);
long wali_syscall_shmdt (wasm_exec_env_t exec_env);
long wali_syscall_msgget (wasm_exec_env_t exec_env);
long wali_syscall_msgsnd (wasm_exec_env_t exec_env);
long wali_syscall_msgrcv (wasm_exec_env_t exec_env);
long wali_syscall_msgctl (wasm_exec_env_t exec_env);
long wali_syscall_fcntl (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_flock (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_fsync (wasm_exec_env_t exec_env, long a1);
long wali_syscall_fdatasync (wasm_exec_env_t exec_env);
long wali_syscall_truncate (wasm_exec_env_t exec_env);
long wali_syscall_ftruncate (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_getdents (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_getcwd (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_chdir (wasm_exec_env_t exec_env, long a1);
long wali_syscall_fchdir (wasm_exec_env_t exec_env);
long wali_syscall_rename (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_mkdir (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_rmdir (wasm_exec_env_t exec_env, long a1);
long wali_syscall_creat (wasm_exec_env_t exec_env);
long wali_syscall_link (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_unlink (wasm_exec_env_t exec_env, long a1);
long wali_syscall_symlink (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_readlink (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_chmod (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_fchmod (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_chown (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_fchown (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_lchown (wasm_exec_env_t exec_env);
long wali_syscall_umask (wasm_exec_env_t exec_env, long a1);
long wali_syscall_gettimeofday (wasm_exec_env_t exec_env);
long wali_syscall_getrlimit (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_getrusage (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_sysinfo (wasm_exec_env_t exec_env, long a1);
long wali_syscall_times (wasm_exec_env_t exec_env);
long wali_syscall_ptrace (wasm_exec_env_t exec_env);
long wali_syscall_getuid (wasm_exec_env_t exec_env);
long wali_syscall_syslog (wasm_exec_env_t exec_env);
long wali_syscall_getgid (wasm_exec_env_t exec_env);
long wali_syscall_setuid (wasm_exec_env_t exec_env);
long wali_syscall_setgid (wasm_exec_env_t exec_env);
long wali_syscall_geteuid (wasm_exec_env_t exec_env);
long wali_syscall_getegid (wasm_exec_env_t exec_env);
long wali_syscall_setpgid (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_getppid (wasm_exec_env_t exec_env);
long wali_syscall_getpgrp (wasm_exec_env_t exec_env);
long wali_syscall_setsid (wasm_exec_env_t exec_env);
long wali_syscall_setreuid (wasm_exec_env_t exec_env);
long wali_syscall_setregid (wasm_exec_env_t exec_env);
long wali_syscall_getgroups (wasm_exec_env_t exec_env);
long wali_syscall_setgroups (wasm_exec_env_t exec_env);
long wali_syscall_setresuid (wasm_exec_env_t exec_env);
long wali_syscall_getresuid (wasm_exec_env_t exec_env);
long wali_syscall_setresgid (wasm_exec_env_t exec_env);
long wali_syscall_getresgid (wasm_exec_env_t exec_env);
long wali_syscall_getpgid (wasm_exec_env_t exec_env, long a1);
long wali_syscall_setfsuid (wasm_exec_env_t exec_env);
long wali_syscall_setfsgid (wasm_exec_env_t exec_env);
long wali_syscall_getsid (wasm_exec_env_t exec_env, long a1);
long wali_syscall_capget (wasm_exec_env_t exec_env);
long wali_syscall_capset (wasm_exec_env_t exec_env);
long wali_syscall_rt_sigpending (wasm_exec_env_t exec_env);
long wali_syscall_rt_sigtimedwait (wasm_exec_env_t exec_env);
long wali_syscall_rt_sigqueueinfo (wasm_exec_env_t exec_env);
long wali_syscall_rt_sigsuspend (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_sigaltstack (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_utime (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_mknod (wasm_exec_env_t exec_env);
long wali_syscall_uselib (wasm_exec_env_t exec_env);
long wali_syscall_personality (wasm_exec_env_t exec_env);
long wali_syscall_ustat (wasm_exec_env_t exec_env);
long wali_syscall_statfs (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_fstatfs (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_sysfs (wasm_exec_env_t exec_env);
long wali_syscall_getpriority (wasm_exec_env_t exec_env);
long wali_syscall_setpriority (wasm_exec_env_t exec_env);
long wali_syscall_sched_setparam (wasm_exec_env_t exec_env);
long wali_syscall_sched_getparam (wasm_exec_env_t exec_env);
long wali_syscall_sched_setscheduler (wasm_exec_env_t exec_env);
long wali_syscall_sched_getscheduler (wasm_exec_env_t exec_env);
long wali_syscall_sched_get_priority_max (wasm_exec_env_t exec_env);
long wali_syscall_sched_get_priority_min (wasm_exec_env_t exec_env);
long wali_syscall_sched_rr_get_interval (wasm_exec_env_t exec_env);
long wali_syscall_mlock (wasm_exec_env_t exec_env);
long wali_syscall_munlock (wasm_exec_env_t exec_env);
long wali_syscall_mlockall (wasm_exec_env_t exec_env);
long wali_syscall_munlockall (wasm_exec_env_t exec_env);
long wali_syscall_vhangup (wasm_exec_env_t exec_env);
long wali_syscall_modify_ldt (wasm_exec_env_t exec_env);
long wali_syscall_pivot_root (wasm_exec_env_t exec_env);
long wali_syscall__sysctl (wasm_exec_env_t exec_env);
long wali_syscall_prctl (wasm_exec_env_t exec_env);
long wali_syscall_arch_prctl (wasm_exec_env_t exec_env);
long wali_syscall_adjtimex (wasm_exec_env_t exec_env);
long wali_syscall_setrlimit (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_chroot (wasm_exec_env_t exec_env);
long wali_syscall_sync (wasm_exec_env_t exec_env);
long wali_syscall_acct (wasm_exec_env_t exec_env);
long wali_syscall_settimeofday (wasm_exec_env_t exec_env);
long wali_syscall_mount (wasm_exec_env_t exec_env);
long wali_syscall_umount2 (wasm_exec_env_t exec_env);
long wali_syscall_swapon (wasm_exec_env_t exec_env);
long wali_syscall_swapoff (wasm_exec_env_t exec_env);
long wali_syscall_reboot (wasm_exec_env_t exec_env);
long wali_syscall_sethostname (wasm_exec_env_t exec_env);
long wali_syscall_setdomainname (wasm_exec_env_t exec_env);
long wali_syscall_iopl (wasm_exec_env_t exec_env);
long wali_syscall_ioperm (wasm_exec_env_t exec_env);
long wali_syscall_create_module (wasm_exec_env_t exec_env);
long wali_syscall_init_module (wasm_exec_env_t exec_env);
long wali_syscall_delete_module (wasm_exec_env_t exec_env);
long wali_syscall_get_kernel_syms (wasm_exec_env_t exec_env);
long wali_syscall_query_module (wasm_exec_env_t exec_env);
long wali_syscall_quotactl (wasm_exec_env_t exec_env);
long wali_syscall_nfsservctl (wasm_exec_env_t exec_env);
long wali_syscall_getpmsg (wasm_exec_env_t exec_env);
long wali_syscall_putpmsg (wasm_exec_env_t exec_env);
long wali_syscall_afs_syscall (wasm_exec_env_t exec_env);
long wali_syscall_tuxcall (wasm_exec_env_t exec_env);
long wali_syscall_security (wasm_exec_env_t exec_env);
long wali_syscall_gettid (wasm_exec_env_t exec_env);
long wali_syscall_readahead (wasm_exec_env_t exec_env);
long wali_syscall_setxattr (wasm_exec_env_t exec_env);
long wali_syscall_lsetxattr (wasm_exec_env_t exec_env);
long wali_syscall_fsetxattr (wasm_exec_env_t exec_env);
long wali_syscall_getxattr (wasm_exec_env_t exec_env);
long wali_syscall_lgetxattr (wasm_exec_env_t exec_env);
long wali_syscall_fgetxattr (wasm_exec_env_t exec_env);
long wali_syscall_listxattr (wasm_exec_env_t exec_env);
long wali_syscall_llistxattr (wasm_exec_env_t exec_env);
long wali_syscall_flistxattr (wasm_exec_env_t exec_env);
long wali_syscall_removexattr (wasm_exec_env_t exec_env);
long wali_syscall_lremovexattr (wasm_exec_env_t exec_env);
long wali_syscall_fremovexattr (wasm_exec_env_t exec_env);
long wali_syscall_tkill (wasm_exec_env_t exec_env);
long wali_syscall_time (wasm_exec_env_t exec_env);
long wali_syscall_futex (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5, long a6);
long wali_syscall_sched_setaffinity (wasm_exec_env_t exec_env);
long wali_syscall_sched_getaffinity (wasm_exec_env_t exec_env);
long wali_syscall_set_thread_area (wasm_exec_env_t exec_env);
long wali_syscall_io_setup (wasm_exec_env_t exec_env);
long wali_syscall_io_destroy (wasm_exec_env_t exec_env);
long wali_syscall_io_getevents (wasm_exec_env_t exec_env);
long wali_syscall_io_submit (wasm_exec_env_t exec_env);
long wali_syscall_io_cancel (wasm_exec_env_t exec_env);
long wali_syscall_get_thread_area (wasm_exec_env_t exec_env);
long wali_syscall_lookup_dcookie (wasm_exec_env_t exec_env);
long wali_syscall_epoll_create (wasm_exec_env_t exec_env);
long wali_syscall_epoll_ctl_old (wasm_exec_env_t exec_env);
long wali_syscall_epoll_wait_old (wasm_exec_env_t exec_env);
long wali_syscall_remap_file_pages (wasm_exec_env_t exec_env);
long wali_syscall_getdents64 (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_set_tid_address (wasm_exec_env_t exec_env, long a1);
long wali_syscall_restart_syscall (wasm_exec_env_t exec_env);
long wali_syscall_semtimedop (wasm_exec_env_t exec_env);
long wali_syscall_fadvise (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_timer_create (wasm_exec_env_t exec_env);
long wali_syscall_timer_settime (wasm_exec_env_t exec_env);
long wali_syscall_timer_gettime (wasm_exec_env_t exec_env);
long wali_syscall_timer_getoverrun (wasm_exec_env_t exec_env);
long wali_syscall_timer_delete (wasm_exec_env_t exec_env);
long wali_syscall_clock_settime (wasm_exec_env_t exec_env);
long wali_syscall_clock_gettime (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_clock_getres (wasm_exec_env_t exec_env);
long wali_syscall_clock_nanosleep (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_exit_group (wasm_exec_env_t exec_env, long a1);
long wali_syscall_epoll_wait (wasm_exec_env_t exec_env);
long wali_syscall_epoll_ctl (wasm_exec_env_t exec_env);
long wali_syscall_tgkill (wasm_exec_env_t exec_env);
long wali_syscall_utimes (wasm_exec_env_t exec_env);
long wali_syscall_vserver (wasm_exec_env_t exec_env);
long wali_syscall_mbind (wasm_exec_env_t exec_env);
long wali_syscall_set_mempolicy (wasm_exec_env_t exec_env);
long wali_syscall_get_mempolicy (wasm_exec_env_t exec_env);
long wali_syscall_mq_open (wasm_exec_env_t exec_env);
long wali_syscall_mq_unlink (wasm_exec_env_t exec_env);
long wali_syscall_mq_timedsend (wasm_exec_env_t exec_env);
long wali_syscall_mq_timedreceive (wasm_exec_env_t exec_env);
long wali_syscall_mq_notify (wasm_exec_env_t exec_env);
long wali_syscall_mq_getsetattr (wasm_exec_env_t exec_env);
long wali_syscall_kexec_load (wasm_exec_env_t exec_env);
long wali_syscall_waitid (wasm_exec_env_t exec_env);
long wali_syscall_add_key (wasm_exec_env_t exec_env);
long wali_syscall_request_key (wasm_exec_env_t exec_env);
long wali_syscall_keyctl (wasm_exec_env_t exec_env);
long wali_syscall_ioprio_set (wasm_exec_env_t exec_env);
long wali_syscall_ioprio_get (wasm_exec_env_t exec_env);
long wali_syscall_inotify_init (wasm_exec_env_t exec_env);
long wali_syscall_inotify_add_watch (wasm_exec_env_t exec_env);
long wali_syscall_inotify_rm_watch (wasm_exec_env_t exec_env);
long wali_syscall_migrate_pages (wasm_exec_env_t exec_env);
long wali_syscall_openat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_mkdirat (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_mknodat (wasm_exec_env_t exec_env);
long wali_syscall_fchownat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5);
long wali_syscall_futimesat (wasm_exec_env_t exec_env);
long wali_syscall_fstatat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_unlinkat (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_renameat (wasm_exec_env_t exec_env);
long wali_syscall_linkat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5);
long wali_syscall_symlinkat (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_readlinkat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_fchmodat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_faccessat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_pselect6 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5, long a6);
long wali_syscall_ppoll (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5);
long wali_syscall_unshare (wasm_exec_env_t exec_env);
long wali_syscall_set_robust_list (wasm_exec_env_t exec_env);
long wali_syscall_get_robust_list (wasm_exec_env_t exec_env);
long wali_syscall_splice (wasm_exec_env_t exec_env);
long wali_syscall_tee (wasm_exec_env_t exec_env);
long wali_syscall_sync_file_range (wasm_exec_env_t exec_env);
long wali_syscall_vmsplice (wasm_exec_env_t exec_env);
long wali_syscall_move_pages (wasm_exec_env_t exec_env);
long wali_syscall_utimensat (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_epoll_pwait (wasm_exec_env_t exec_env);
long wali_syscall_signalfd (wasm_exec_env_t exec_env);
long wali_syscall_timerfd_create (wasm_exec_env_t exec_env);
long wali_syscall_eventfd (wasm_exec_env_t exec_env, long a1);
long wali_syscall_fallocate (wasm_exec_env_t exec_env);
long wali_syscall_timerfd_settime (wasm_exec_env_t exec_env);
long wali_syscall_timerfd_gettime (wasm_exec_env_t exec_env);
long wali_syscall_accept4 (wasm_exec_env_t exec_env);
long wali_syscall_signalfd4 (wasm_exec_env_t exec_env);
long wali_syscall_eventfd2 (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_epoll_create1 (wasm_exec_env_t exec_env);
long wali_syscall_dup3 (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_pipe2 (wasm_exec_env_t exec_env, long a1, long a2);
long wali_syscall_inotify_init1 (wasm_exec_env_t exec_env);
long wali_syscall_preadv (wasm_exec_env_t exec_env);
long wali_syscall_pwritev (wasm_exec_env_t exec_env);
long wali_syscall_rt_tgsigqueueinfo (wasm_exec_env_t exec_env);
long wali_syscall_perf_event_open (wasm_exec_env_t exec_env);
long wali_syscall_recvmmsg (wasm_exec_env_t exec_env);
long wali_syscall_fanotify_init (wasm_exec_env_t exec_env);
long wali_syscall_fanotify_mark (wasm_exec_env_t exec_env);
long wali_syscall_prlimit64 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);
long wali_syscall_name_to_handle_at (wasm_exec_env_t exec_env);
long wali_syscall_open_by_handle_at (wasm_exec_env_t exec_env);
long wali_syscall_clock_adjtime (wasm_exec_env_t exec_env);
long wali_syscall_syncfs (wasm_exec_env_t exec_env);
long wali_syscall_sendmmsg (wasm_exec_env_t exec_env);
long wali_syscall_setns (wasm_exec_env_t exec_env);
long wali_syscall_getcpu (wasm_exec_env_t exec_env);
long wali_syscall_process_vm_readv (wasm_exec_env_t exec_env);
long wali_syscall_process_vm_writev (wasm_exec_env_t exec_env);
long wali_syscall_kcmp (wasm_exec_env_t exec_env);
long wali_syscall_finit_module (wasm_exec_env_t exec_env);
long wali_syscall_sched_setattr (wasm_exec_env_t exec_env);
long wali_syscall_sched_getattr (wasm_exec_env_t exec_env);
long wali_syscall_renameat2 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5);
long wali_syscall_seccomp (wasm_exec_env_t exec_env);
long wali_syscall_getrandom (wasm_exec_env_t exec_env, long a1, long a2, long a3);
long wali_syscall_memfd_create (wasm_exec_env_t exec_env);
long wali_syscall_kexec_file_load (wasm_exec_env_t exec_env);
long wali_syscall_bpf (wasm_exec_env_t exec_env);
long wali_syscall_execveat (wasm_exec_env_t exec_env);
long wali_syscall_userfaultfd (wasm_exec_env_t exec_env);
long wali_syscall_membarrier (wasm_exec_env_t exec_env);
long wali_syscall_mlock2 (wasm_exec_env_t exec_env);
long wali_syscall_copy_file_range (wasm_exec_env_t exec_env);
long wali_syscall_preadv2 (wasm_exec_env_t exec_env);
long wali_syscall_pwritev2 (wasm_exec_env_t exec_env);
long wali_syscall_pkey_mprotect (wasm_exec_env_t exec_env);
long wali_syscall_pkey_alloc (wasm_exec_env_t exec_env);
long wali_syscall_pkey_free (wasm_exec_env_t exec_env);
long wali_syscall_statx (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5);
long wali_syscall_io_pgetevents (wasm_exec_env_t exec_env);
long wali_syscall_rseq (wasm_exec_env_t exec_env);
long wali_syscall_faccessat2 (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4);

/* Alias calls */
long wali_syscall_ppoll_aliased (wasm_exec_env_t exec_env, long a1, long a2, long a3, long a4, long a5);

/** Auxillary **/
int wali_sigsetjmp (wasm_exec_env_t exec_env, int sigjmp_buf_addr, int savesigs);
void wali_siglongjmp (wasm_exec_env_t exec_env, int sigjmp_buf_addr, int val);

/***** Startup *****/
void wali_call_ctors (wasm_exec_env_t exec_env);
void wali_call_dtors (wasm_exec_env_t exec_env);
void wali_proc_exit (wasm_exec_env_t exec_env, long v);
int wali_cl_get_argc (wasm_exec_env_t exec_env);
int wali_cl_get_argv_len (wasm_exec_env_t exec_env, int arg_idx);
int wali_cl_copy_argv (wasm_exec_env_t exec_env, int argv_addr, int arg_idx);

/***** Threads *****/
int wali_wasm_thread_spawn (wasm_exec_env_t exec_env, int setup_fnptr, int arg_wasm);

#endif
