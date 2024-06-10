#!/bin/bash

west build -b nucleo_l433rc_p . -p always -- \
           -DWAMR_BUILD_TARGET=THUMBV7 -DWAMR_BUILD_AOT=0 \
           -DWAMR_BUILD_LIBC_WAZI=1 -DLOG_VERBOSITY=$1
west flash
