/* WALI compilation support for signal polling */

#include "aot_emit_sigpoll.h"
#include "../aot/aot_runtime.h"

bool
aot_emit_sigpoll(AOTCompContext *comp_ctx, AOTFuncContext *func_ctx) {
#if WALI_ENABLE_SIGNAL_HANDLING
    /* For WALI Signal Poll handling */
    LLVMValueRef func;
    LLVMTypeRef func_type, ret_type, param_types[1];
    LLVMValueRef param_values[1];

    /* Create sigpoll function type */
    ret_type = VOID_TYPE;
    param_types[0] = comp_ctx->exec_env_type;
    if (!(func_type = LLVMFunctionType(ret_type, param_types, 1, false))) {
        aot_set_last_error("create LLVM function type failed.");
        return false;
    }

    /* External function pointer to 'aot_poll_pending_signal' */
    if (!(func = LLVMGetNamedFunction(func_ctx->module,
                                      "aot_poll_pending_signal"))
        && !(func = LLVMAddFunction(func_ctx->module,
                                    "aot_poll_pending_signal",
                                    func_type))) {
        aot_set_last_error("add LLVM function failed.");
        return false;
    }

    param_values[0] = func_ctx->exec_env;
    if (!LLVMBuildCall2(comp_ctx->builder, func_type, func, param_values, 1, "")) {
        aot_set_last_error("llvm build call failed.");
        return false;
    }
#endif /* WALI_ENABLE_SIGNAL_HANDLING */
    return true;
}
