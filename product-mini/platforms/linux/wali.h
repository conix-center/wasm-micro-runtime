#include "wasm_export.h"

/** Syscalls **/
int __syscall_SYS_write_wrapper (wasm_exec_env_t exec_env, int a1, int a2, int a3);

int __syscall_SYS_getcwd_wrapper (wasm_exec_env_t exec_env, int a1, int a2);

int __syscall_SYS_chdir_wrapper (wasm_exec_env_t exec_env, int a1);

int __syscall_SYS_myfork_wrapper (wasm_exec_env_t exec_env);

/** Auxillary **/
uintptr_t __get_tp_wrapper (wasm_exec_env_t exec_env);
void __wasm_call_dtors_wrapper();
int __wasi_proc_exit_wrapper();

