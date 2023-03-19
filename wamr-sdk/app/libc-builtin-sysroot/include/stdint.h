/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#ifndef _WAMR_LIBC_STDINT_H
#define _WAMR_LIBC_STDINT_H

#ifdef __cplusplus
extern "C" {
#endif

/* clang-format off */
/* The word size of platform */
#ifdef __wasm64__
#define __WORDSIZE 64
#else
#define __WORDSIZE 32
#endif

typedef char            int8_t;
typedef short int       int16_t;
typedef int             int32_t;
typedef long long int   int64_t;

/* Unsigned.  */
typedef unsigned char	        uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int	        uint32_t;
typedef unsigned long long int  uint64_t;

/* For atomics */
typedef int8_t int_fast8_t;
typedef int64_t int_fast64_t;

typedef int8_t  int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;

typedef uint8_t uint_fast8_t;
typedef uint64_t uint_fast64_t;

typedef uint8_t  uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;

typedef int64_t intmax_t;
typedef uint64_t uintmax_t;

#define INT_FAST16_MIN  INT16_MIN
#define INT_FAST32_MIN  INT32_MIN

#define INT_FAST16_MAX  INT16_MAX
#define INT_FAST32_MAX  INT32_MAX

#define UINT_FAST16_MAX UINT16_MAX
#define UINT_FAST32_MAX UINT32_MAX

#define PTRDIFF_MIN     INT32_MIN
#define PTRDIFF_MAX     INT32_MAX



typedef __INTPTR_TYPE__		intptr_t;
typedef __UINTPTR_TYPE__	uintptr_t;

/* Signed and unsigned  */
#if __WORDSIZE == 64
#define INT64_C(c) c ## L
#define UINT64_C(c) c ## UL
#define INTMAX_C(c)  c ## L
#define UINTMAX_C(c) c ## UL
#else
#define INT64_C(c) c ## LL
#define UINT64_C(c) c ## ULL
#define INTMAX_C(c)  c ## LL
#define UINTMAX_C(c) c ## ULL
#endif


/* Minimum of signed integral types.  */
# define INT8_MIN		(-128)
# define INT16_MIN		(-32767-1)
# define INT32_MIN		(-2147483647-1)
# define INT64_MIN		(-INT64_C(9223372036854775807)-1)

/* Maximum of signed integral types.  */
# define INT8_MAX		(127)
# define INT16_MAX		(32767)
# define INT32_MAX		(2147483647)
# define INT64_MAX		(INT64_C(9223372036854775807))

/* Maximum of unsigned integral types.  */
# define UINT8_MAX		(255)
# define UINT16_MAX		(65535)
# define UINT32_MAX		(4294967295U)
# define UINT64_MAX		(UINT64_C(18446744073709551615))

/* Values to test for integral types holding `void *' pointer.  */
#if __WORDSIZE == 64
#define INTPTR_MIN      INT64_MIN
#define INTPTR_MAX      INT64_MAX
#define UINTPTR_MAX     UINT64_MAX
#else
#define INTPTR_MIN      INT32_MIN
#define INTPTR_MAX      INT32_MAX
#define UINTPTR_MAX     UINT32_MAX
#endif

/* Limit of `size_t' type.  */
#if __WORDSIZE == 64
#define SIZE_MAX        UINT64_MAX
#else
#define SIZE_MAX        UINT32_MAX
#endif

#define INT_FAST8_MIN   INT8_MIN
#define INT_FAST64_MIN  INT64_MIN

#define INT_LEAST8_MIN   INT8_MIN
#define INT_LEAST16_MIN  INT16_MIN
#define INT_LEAST32_MIN  INT32_MIN
#define INT_LEAST64_MIN  INT64_MIN

#define INT_FAST8_MAX   INT8_MAX
#define INT_FAST64_MAX  INT64_MAX

#define INT_LEAST8_MAX   INT8_MAX
#define INT_LEAST16_MAX  INT16_MAX
#define INT_LEAST32_MAX  INT32_MAX
#define INT_LEAST64_MAX  INT64_MAX

#define UINT_FAST8_MAX  UINT8_MAX
#define UINT_FAST64_MAX UINT64_MAX

#define UINT_LEAST8_MAX  UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX


/* clang-format on */

#ifdef __cplusplus
}
#endif

#endif
