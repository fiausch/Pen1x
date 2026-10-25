#     kernelSamNeVemImenaSe
## this is easily my best work which is a shame since it really isn't that good



![gnu-and-penguin-color-300x276](https://github.com/user-attachments/assets/62cf698c-6448-4a4b-9474-3f1a0109c9ce)

## Makefile instructions:

DEPRECATED, need target and prefix exporting, manual intervention is neeed for make all to work, change the compiler to clang and the flags to clang flags in order for this to work:
make (all): compile the bootloader, the 32 bit protected mode kernel and the user programs 

make clean: removes the compiled binaries, object files and user programs

make mkdir: creates the build folders (and the folders where the final bianry is stored) - I didnt user .keep but probably should



./bitch.sh: compiles the bootloader and kernel and needed object/binary files
note: i do not use the name build.sh since build is already a directory and i like the speed bitch enables


## requirements (arch linux idk should be similar on other distros):
```
sudo pacman -S clang gcc make base-devel qemu-full gdb nasm pax-utils
``` 
## reccomended for development:
```
yay -S ndisasm bless
```

## setup:
```
git clone https://codeberg.org/fiausch/Pen1X.git
``` 


Svaki čovjek ima svoj blues
