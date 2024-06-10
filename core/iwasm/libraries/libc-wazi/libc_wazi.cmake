# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

set (LIBC_WAZI_DIR ${CMAKE_CURRENT_LIST_DIR})
#set (ARCH ${CMAKE_SYSTEM_PROCESSOR})

add_definitions (-DWASM_ENABLE_LIBC_WAZI=1)

#include_directories(${LIBC_WALI_DIR}/wali_arch/${ARCH})

# Compile flags
#add_compile_definitions(WALI_ENABLE_SYSCALL_PROFILE=0)
#add_compile_definitions(WALI_ENABLE_NATIVE_SYSCALL_PROFILE=0)

# Setup files to compile
#file (GLOB_RECURSE wali_arch_sources ${LIBC_WALI_DIR}/wali_arch/${ARCH}/*.s ${LIBC_WALI_DIR}/wali_arch/*.c)
set (WAZI_SOURCES ${LIBC_WAZI_DIR}/wazi.c) #${wali_arch_sources})

set (LIBC_WAZI_SOURCE ${WAZI_SOURCES})
