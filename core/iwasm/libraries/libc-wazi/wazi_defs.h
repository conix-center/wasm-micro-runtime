#ifndef _WALI_DEFS_H_
#define _WALI_DEFS_H_

/** Architecture **/
#if !__arm__ && !__aarch64__
#error "Unsupported architecture for WAZI -- Only supports [arm, aarch64]"
#endif

/** Memory defines **/
#define WASM_PAGESIZE 65536

#endif
