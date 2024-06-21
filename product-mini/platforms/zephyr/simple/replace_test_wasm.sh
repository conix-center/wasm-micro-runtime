#!/bin/bash

BP=${1%.*}
wat2wasm --enable-threads --debug-names $BP.wat -o prog.wasm
op=$(xxd -i prog.wasm)
mod_op="const ${op}" 
echo "$mod_op" > src/prog_wasm.h
