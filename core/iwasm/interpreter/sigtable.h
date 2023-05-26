#ifndef _WALI_SIGTABLE_H_
#define _WALI_SIGTABLE_H_

#include <signal.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>

#include "wasm_export.h"

typedef struct {
  wasm_function_inst_t function;
  uint32_t func_table_idx;
} wali_sigentry;

extern pthread_mutex_t sigtable_mut;
extern wali_sigentry wali_sigtable[];

extern pthread_mutex_t sigpending_mut;
extern uint64_t wali_sigpending;

/* Return -1 if no pending signal, else signal index */
int get_pending_signal(void);

#endif
