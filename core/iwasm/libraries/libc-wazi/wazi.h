#ifndef _WAZI_H_
#define _WAZI_H_

#include <zephyr/sys/libc-hooks.h>
#include <stdio.h>

#include "wasm_export.h"
#include "bh_platform.h"
#include "wazi_defs.h"

#if !__arm__
#error "Unsupported architecture for WAZI -- Only supports [arm]"
#endif

#define VB(fmt, ...) LOG_VERBOSE("WAZI: " fmt, gettid(), ## __VA_ARGS__)
#define WARN(fmt, ...)  LOG_WARNING("WAZI: " fmt, ## __VA_ARGS__)
#define ERR(fmt, ...) LOG_ERROR("WAZI: " fmt, ## __VA_ARGS__)

/** Memory defines/translations **/
typedef uint8_t* Addr;
typedef uint32_t FuncPtr_t;

#define BASE_ADDR() ({  \
  (Addr) wasm_runtime_addr_app_to_native(get_module_inst(exec_env), 0); \
})

#define MADDR(wasm_addr) ({  \
  Addr addr = wasm_addr ? (Addr) wasm_runtime_addr_app_to_native(get_module_inst(exec_env), wasm_addr) : NULL;  \
  if (addr == NULL) { }  \
  addr; \
})

#define WADDR(mem_addr) ({  \
  wasm_runtime_addr_native_to_app(get_module_inst(exec_env), mem_addr); \
})
/** **/


/** Syscalls **/
long wazi_syscall_zephyr_fputc(wasm_exec_env_t exec_env, int c, uintptr_t stream);

#endif
