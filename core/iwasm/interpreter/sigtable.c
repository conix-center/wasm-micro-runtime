#include "sigtable.h"

pthread_mutex_t sigtable_mut = PTHREAD_MUTEX_INITIALIZER;
wali_sigentry wali_sigtable[NSIG] = {0};

pthread_mutex_t sigpending_mut = PTHREAD_MUTEX_INITIALIZER;
uint64_t wali_sigpending = 0;

