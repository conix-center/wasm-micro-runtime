#!/bin/bash

BP=${1%.*}
wat2wasm $BP.wat -o prog.wasm
xxd -i prog.wasm > src/prog_wasm.h
