#ifndef _AOT_EMIT_SIGPOLL_H_
#define _AOT_EMIT_SIGPOLL_H_

#include "aot_compiler.h"


#if WALI_ENABLE_SIGNAL_HANDLING

#if WALI_ENABLE_ALL_SIGPOLL
#undef WALI_ENABLE_LOOP_SIGPOLL
#undef WALI_ENABLE_FUNC_SIGPOLL

#elif WALI_ENABLE_FUNC_SIGPOLL
#undef WALI_ENABLE_LOOP_SIGPOLL

#elif !WALI_ENABLE_LOOP_SIGPOLL
#ifndef WALI_ENABLE_LOOP_SIGPOLL
#define WALI_ENABLE_LOOP_SIGPOLL 1 /* default */
#endif
#endif

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
