#!/bin/bash
export PREFIX="/usr/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
make clean
make all-gcc -j
./launchKernelQEMU.sh