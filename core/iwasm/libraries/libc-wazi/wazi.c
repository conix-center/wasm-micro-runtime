/*
  MIT License

  Copyright (c) [2023] [Arjun Ramesh]

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "wazi.h"
#include "wazi_conversions.h"

#define SC(nr, f)   LOG_VERBOSE("WAZI: SC | " # f);
#define RETURN(v)   return v;

#define ERRSC(f,...) { \
  LOG_ERROR("WAZI: SC \"" # f "\" not implemented correctly yet! " __VA_ARGS__);  \
}
#define FATALSC(f,...) { \
  LOG_FATAL("WAZI: SC \"" # f "\" fatal error! " __VA_ARGS__);  \
}
#define MISSC(f,...) { \
  LOG_FATAL("WAZI: SC \"" # f "\" fatal error! No such syscall on platform");  \
}

/***** WAZI Methods *******/

// 491
long wazi_syscall_zephyr_fputc(wasm_exec_env_t exec_env, int c, uintptr_t stream) {
  FILE *mstream = MADDR_FILE(stream);
  SC(491,zephyr_fputc);
  RETURN(zephyr_fputc(c, mstream));
}

/* Native WAZI Symbols */
#define NSYMBOL(symbol, fn, sign) \
  { #symbol, (void*)fn, sign, NULL }

static NativeSymbol wazi_native_symbols[] = {
  // Syscalls
  NSYMBOL ( SYS_zephyr_fputc, wazi_syscall_zephyr_fputc, "(ii)i" )
};

uint32
get_libc_wazi_export_apis(NativeSymbol **p_libc_wazi_apis)
{
    *p_libc_wazi_apis = wazi_native_symbols;
    return sizeof(wazi_native_symbols) / sizeof(NativeSymbol);
}


