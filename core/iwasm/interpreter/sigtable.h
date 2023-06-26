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
static inline int get_pending_signal(void) {
  /* Don't need an atomic read here on the outermost check since 
  * inconsistent reads are filtered by the mutex inside
  * This allows signal-free code to run significantly faster
  */
  if (wali_sigpending) {
    pthread_mutex_lock(&sigpending_mut);
    int idx = __builtin_ffsll(wali_sigpending);
    wali_sigpending &= ~(((uint64_t)1 << idx) - 1);
    pthread_mutex_unlock(&sigpending_mut);
    return idx - 1;
  } else {
    return -1;
  }
}

#endif
