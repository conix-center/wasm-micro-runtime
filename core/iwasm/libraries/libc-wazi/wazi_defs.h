#ifndef _WALI_DEFS_H_
#define _WALI_DEFS_H_

/** Architecture **/
#if !__arm__
#error "Unsupported architecture for WAZI -- Only supports [arm]"
#endif

/** Memory defines **/
#define WASM_PAGESIZE 65536

#endif
