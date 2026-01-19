#!/bin/bash
export PREFIX="/usr/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
clear
make clean
make all -j
