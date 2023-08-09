/* WALI compilation support for signal polling */

#include "aot_emit_sigpoll.h"
#include "../aot/aot_runtime.h"

#define CREATE_BLOCK(new_llvm_block, name)                      \
    do {                                                        \
        if (!(new_llvm_block = LLVMAppendBasicBlockInContext(   \
                  comp_ctx->context, func_ctx->func, name))) {  \
            aot_set_last_error("add LLVM basic block failed."); \
            return false;                                          \
        }                                                       \
    } while (0)

#define CURR_BLOCK() LLVMGetInsertBlock(comp_ctx->builder)

#define MOVE_BLOCK_AFTER(llvm_block, llvm_block_after) \
    LLVMMoveBasicBlockAfter(llvm_block, llvm_block_after)

#define MOVE_BLOCK_AFTER_CURR(llvm_block) \
    LLVMMoveBasicBlockAfter(llvm_block, CURR_BLOCK())

#define SET_BUILDER_POS(llvm_block) \
    LLVMPositionBuilderAtEnd(comp_ctx->builder, llvm_block)

#define BUILD_COND_BR(value_if, block_then, block_else)               \
    do {                                                              \
        if (!LLVMBuildCondBr(comp_ctx->builder, value_if, block_then, \
                             block_else)) {                           \
            aot_set_last_error("llvm build cond br failed.");         \
            return false;                                                \
        }                                                             \
    } while (0)

#define BUILD_BR(llvm_block)                               \
    do {                                                   \
        if (!LLVMBuildBr(comp_ctx->builder, llvm_block)) { \
            aot_set_last_error("llvm build br failed.");   \
            return false;                                     \
        }                                                  \
    } while (0)

#define BUILD_ICMP(op, left, right, res, name)                                \
    do {                                                                      \
        if (!(res =                                                           \
                  LLVMBuildICmp(comp_ctx->builder, op, left, right, name))) { \
            aot_set_last_error("llvm build icmp failed.");                    \
            return false;                                                        \
        }                                                                     \
    } while (0)

bool
aot_emit_sigpoll(AOTCompContext *comp_ctx, AOTFuncContext *func_ctx) {
#if WALI_ENABLE_SIGNAL_HANDLING
    /* For WALI Signal Poll handling */
    LLVMValueRef func;
    LLVMTypeRef func_type, ret_type, param_types[1];
    LLVMValueRef param_values[1];

    LLVMValueRef sigpoll_value, take_sigpoll;
    LLVMBasicBlockRef sigpoll_block, contpoll_block;

    /* Get sigpoll_value */
    if (!(sigpoll_value =
              LLVMBuildLoad2(comp_ctx->builder, I64_TYPE, func_ctx->sigpoll_ptr,
                             "sigpoll_value"))) {
        aot_set_last_error("llvm build LOAD failed");
        return false;
    }

    CREATE_BLOCK(sigpoll_block, "sigpoll_block");
    MOVE_BLOCK_AFTER_CURR(sigpoll_block);

    CREATE_BLOCK(contpoll_block, "contpoll");
    MOVE_BLOCK_AFTER_CURR(contpoll_block);

    /* Test whether to invoke call or continue */
    BUILD_ICMP(LLVMIntEQ, sigpoll_value, I64_ZERO, take_sigpoll, "sigpoll_flag");
    BUILD_COND_BR(take_sigpoll, contpoll_block, sigpoll_block);

    /* Sigpolling */
    SET_BUILDER_POS(sigpoll_block);

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

    BUILD_BR(contpoll_block);

    SET_BUILDER_POS(contpoll_block);
#endif /* WALI_ENABLE_SIGNAL_HANDLING */
    return true;
}
