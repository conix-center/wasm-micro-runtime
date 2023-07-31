#ifndef _AOT_EMIT_SIGPOLL_H_
#define _AOT_EMIT_SIGPOLL_H_

#include "aot_compiler.h"

#define WALI_ENABLE_SIGNAL_HANDLING 1
#if WALI_ENABLE_SIGNAL_HANDLING
#define WALI_ENABLE_LOOP_SIGPOLL 1
#define WALI_ENABLE_ALL_SIGPOLL 0
#define WALI_ENABLE_FUNCTION_SIGPOLL 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

bool
aot_emit_sigpoll(AOTCompContext *comp_ctx, AOTFuncContext *func_ctx);

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* end of _AOT_EMIT_SIGPOLL_H_ */
