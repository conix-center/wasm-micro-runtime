/* 
  MIT License

  Copyright (c) [2024] [Arjun Ramesh]

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef _WAZI_COPY_H_
#define _WAZI_COPY_H_

#include <zephyr/net/net_ip.h>
#include "wazi.h"

/** Memory Copy Macros **/
#define WR_FIELD(wptr, val, ty) ({ \
  memcpy(wptr, &val, sizeof(ty)); \
  wptr += sizeof(ty); \
})

#define WR_FIELD_ADDR(wptr, nptr) ({  \
  uint32_t wasm_addr = WADDR(nptr);  \
  if (!wasm_addr) { VB("NULL Wasm Address generated"); }  \
  WR_FIELD(wptr, wasm_addr, uint32_t);  \
})

#define WR_FIELD_ARRAY(wptr, narr, ty, num) ({  \
  memcpy(wptr, narr, sizeof(ty) * num); \
  wptr += (sizeof(ty) * num); \
})

#define RD_FIELD(ptr, ty) ({  \
  ty val; \
  memcpy(&val, ptr, sizeof(ty));  \
  ptr += sizeof(ty);  \
  val;  \
})

#define RD_FIELD_ADDR(ptr) ({ \
  uint32_t field = RD_FIELD(ptr, uint32_t); \
  MADDR (field);  \
})

#define RD_FIELD_ARRAY(dest, ptr, ty, num) ({ \
  memcpy(&dest, ptr, sizeof(ty) * num);  \
  ptr += (sizeof(ty) * num);  \
})
/** **/

/* Copy iovec structure */
extern inline struct iovec* copy_iovec(wasm_exec_env_t exec_env, Addr wasm_iov, int iov_cnt) {
  if (wasm_iov == NULL) { return NULL; }
  struct iovec *new_iov = (struct iovec*) malloc(iov_cnt * sizeof(struct iovec));
  for (int i = 0; i < iov_cnt; i++) {
    new_iov[i].iov_base = RD_FIELD_ADDR(wasm_iov);
    new_iov[i].iov_len = RD_FIELD(wasm_iov, int32_t);
  }
  return new_iov;
}

/* Copy msghdr structure */
extern inline struct msghdr* copy_msghdr(wasm_exec_env_t exec_env, Addr wasm_msghdr) {
  if (wasm_msghdr == NULL) { return NULL; }
  struct msghdr *msg = (struct msghdr*) malloc(sizeof(struct msghdr));
  msg->msg_name = RD_FIELD_ADDR(wasm_msghdr);
  msg->msg_namelen = RD_FIELD(wasm_msghdr, unsigned);

  Addr wasm_iov = RD_FIELD_ADDR(wasm_msghdr);
  msg->msg_iovlen = RD_FIELD(wasm_msghdr, int);

  RD_FIELD(wasm_msghdr, int); // pad1
  
  msg->msg_control = RD_FIELD_ADDR(wasm_msghdr);
  msg->msg_controllen = RD_FIELD(wasm_msghdr, unsigned);

  RD_FIELD(wasm_msghdr, int); // pad2
  msg->msg_flags = RD_FIELD(wasm_msghdr, int);

  msg->msg_iov =  copy_iovec(exec_env, wasm_iov, msg->msg_iovlen);
  return msg;
}

#endif
