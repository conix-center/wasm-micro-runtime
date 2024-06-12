#ifndef _WAZI_CONVERSIONS_H_
#define _WAZI_CONVERSIONS_H_

#include "wazi.h"

/* In accordance with stdout/stdin/stderr for minimal libc in Zephyr */
#define MADDR_FILE(wasm_ptr) ({ \
  bool no_convert = (wasm_ptr == (uintptr_t) stdout || \
      wasm_ptr == (uintptr_t) stderr || wasm_ptr == (uintptr_t) stdin); \
  no_convert ? (FILE*) wasm_ptr : (FILE*) MADDR(wasm_ptr); \
})

/* Assigning to a log_msg_desc 32-bit bitfield struct */
#define LOG_MSG_DESC_INIT(v) ({ \
  struct log_msg_desc res;  \
  memcpy(&res, &v, sizeof(uint32_t)); \
  res; \
})

/* Assigning to a va_list: Not supported currently */
#define VA_LIST_INIT(v) ({ \
  va_list c;  \
  c; \
})

#endif
