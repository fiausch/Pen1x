gdb && c && target remote | qemu-system-i386 -hda ./bin/os.bin -S -gdb stdio
#this doesnt work idk how to shell with gdb
#target remote | qemu-system-i386 -hda ./os.bin -S -gdb stdio