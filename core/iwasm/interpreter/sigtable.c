#include "sigtable.h"

pthread_mutex_t sigtable_mut = PTHREAD_MUTEX_INITIALIZER;
wali_sigentry wali_sigtable[NSIG] = {0};

pthread_mutex_t sigpending_mut = PTHREAD_MUTEX_INITIALIZER;
uint64_t wali_sigpending = 0;

/* Return -1 if no pending signal, else signal index */
int get_pending_signal(void) {
  pthread_mutex_lock(&sigpending_mut);
  int idx = __builtin_ffsll(wali_sigpending);
  wali_sigpending &= ~(((uint64_t)1 << idx) - 1);
  pthread_mutex_unlock(&sigpending_mut);
  return idx - 1;
}

