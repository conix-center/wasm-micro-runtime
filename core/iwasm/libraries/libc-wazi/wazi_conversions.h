#ifndef _WAZI_CONVERSIONS_H_
#define _WAZI_CONVERSIONS_H_

#include "wazi.h"

/* In accordance with stdout/stdin/stderr for minimal libc in Zephyr */
#define MADDR_FILE(wasm_ptr) ({ \
  bool no_convert = (wasm_ptr == (uintptr_t) stdout || \
      wasm_ptr == (uintptr_t) stderr || wasm_ptr == (uintptr_t) stdin); \
  no_convert ? (FILE*) wasm_ptr : (FILE*) MADDR(wasm_ptr); \
})

#endif
