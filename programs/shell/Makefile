FILES=./build/shell.o
INCLUDES= -I../stdlib/src
FLAGS= -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

FLAGS-GCC = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc
FLAGS-CLANG = -g  -target i686 -O0 -nostdlib -ffreestanding  -Wall 
CC-GCC = i686-elf-gcc $(FLAGS-GCC)
CC-CLANG = clang $(FLAGS-CLANG)
LINKER-CLANG = ld.lld 
LINKER-GCC = i686-elf-ld

LINKER= $(LINKER-CLANG)
CC = $(CC-CLANG) 

all: ${FILES}
	$(CC) -g -T ./linker.ld -o ./shell.elf -ffreestanding -O0 -nostdlib -fpic -g ${FILES} ../stdlib/stdlib.elf

./build/shell.o: ./src/shell.c
	$(CC) ${INCLUDES} -I./ -std=gnu99 -c ./src/shell.c -o ./build/shell.o

clean:
	rm -rf ${FILES}
	rm ./shell.elf