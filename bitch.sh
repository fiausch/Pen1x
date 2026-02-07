#!/bin/bash
#target remote | qemu-system-i386 -hda ./bin/os.bin -S -gdb stdio
export PREFIX="/usr/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
clear
make clean
make all -j
