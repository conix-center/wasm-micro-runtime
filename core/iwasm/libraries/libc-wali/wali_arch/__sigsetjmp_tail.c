#include "../wali.h"
#include <sys/syscall.h>

__attribute__ ((visibility("hidden")))
int __libc_sigsetjmp_tail(__libc_sigjmp_buf jb, int ret) {
  void *p = jb->__ss;
  syscall(SYS_rt_sigprocmask, SIG_SETMASK, ret?p:0, ret?0:p, _NSIG/8);
  return ret;
}
