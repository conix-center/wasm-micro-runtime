# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

set (LIBC_WALI_DIR ${CMAKE_CURRENT_LIST_DIR})

add_definitions (-DWASM_ENABLE_LIBC_WALI=1)

include_directories(${LIBC_WALI_DIR}/sandboxed-system-primitives/include
                    ${LIBC_WALI_DIR}/sandboxed-system-primitives/src)

# Compile flags
add_compile_definitions(WALI_ENABLE_SYSCALL_PROFILE=0)
add_compile_definitions(WALI_ENABLE_NATIVE_SYSCALL_PROFILE=0)
add_compile_definitions(WALI_ENABLE_SIGNAL_HANDLING=1)

# Setup files to compile
file (COPY ${CMAKE_CURRENT_LIST_DIR}/wali_arch/${CMAKE_SYSTEM_PROCESSOR}/syscall.h DESTINATION ${CMAKE_CURRENT_LIST_DIR})
file (RENAME ${CMAKE_CURRENT_LIST_DIR}/syscall.h ${CMAKE_CURRENT_LIST_DIR}/syscall_arch.h)
file (GLOB_RECURSE wali_arch_sources ${CMAKE_CURRENT_LIST_DIR}/wali_arch/${CMAKE_SYSTEM_PROCESSOR}/*.s ${CMAKE_CURRENT_LIST_DIR}/wali_arch/*.c)
set (WALI_SOURCES ${CMAKE_CURRENT_LIST_DIR}/wali.c ${wali_arch_sources})

set (LIBC_WALI_SOURCE ${WALI_SOURCES})
