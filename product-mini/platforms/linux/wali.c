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




/***** WALI Methods *******/
int __syscall_SYS_write_wrapper (wasm_exec_env_t exec_env, int a1, int a2, int a3) {
  LOG_WARNING("Wrapper: SYS_write");
  uint32_t size;
  uint8_t* base_addr = wasm_runtime_get_memory_ptr(get_module_inst(exec_env), &size);
  uint8_t* addr2 = a2 + base_addr;
  return __syscall3(SYS_write, a1, addr2, a3);
}

int __syscall_SYS_getcwd_wrapper (wasm_exec_env_t exec_env, int a1, int a2) {
  LOG_WARNING("Wrapper: SYS_getcwd");
  uint32_t size;
  uint8_t* base_addr = wasm_runtime_get_memory_ptr(get_module_inst(exec_env), &size);
  uint8_t* addr1 = a1 + base_addr;
  return __syscall2(SYS_getcwd, addr1, a2);
}

int __syscall_SYS_chdir_wrapper (wasm_exec_env_t exec_env, int a1) {
  LOG_WARNING("Wrapper: SYS_chdir");
  uint32_t size;
  uint8_t* base_addr = wasm_runtime_get_memory_ptr(get_module_inst(exec_env), &size);
  uint8_t* addr1 = a1 + base_addr;
  return __syscall1(SYS_chdir, addr1);
}

int __syscall_SYS_myfork_wrapper (wasm_exec_env_t exec_env) {
  LOG_WARNING("Wrapper: SYS_myfork");
  return __syscall0(SYS_fork);
}

/*************************/

/***** Non-syscall methods *****/
uintptr_t __get_tp_wrapper (wasm_exec_env_t exec_env) {
  uintptr_t tp;
	__asm__ ("mov %%fs:0,%0" : "=r" (tp) );
  LOG_WARNING("Wrapper: get_tp (%ld)", tp);
	return tp;
}

void __wasm_call_dtors_wrapper() {
  LOG_WARNING("Wrapper: wasm-call_dtors");
}

int __wasi_proc_exit_wrapper() {
  LOG_WARNING("Wrapper: exit");
  exit(1);
}






