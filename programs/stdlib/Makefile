FILES=./build/start.o ./build/pen1x.asm.o ./build/pen1x.o ./build/stdlib.o ./build/stdio.o
INCLUDES=-I./src
FLAGS-GCC = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc
FLAGS-CLANG = -g  -target i686 -O0 -nostdlib -ffreestanding  -Wall 
CC-GCC = i686-elf-gcc $(FLAGS-GCC)
CC-CLANG = clang $(FLAGS-CLANG)
LINKER-CLANG = ld.lld 
LINKER-GCC = i686-elf-ld

LINKER= $(LINKER-CLANG)
CC = $(CC-CLANG) 
all: ${FILES}
	$(LINKER) -relocatable ${FILES} -o ./stdlib.elf

./build/start.o: ./src/start.asm
	nasm -f elf ./src/start.asm -o ./build/start.o

./build/pen1x.asm.o: ./src/pen1x.asm
	nasm -f elf ./src/pen1x.asm -o ./build/pen1x.asm.o

./build/pen1x.o: ./src/pen1x.c
	$(CC) ${INCLUDES} $(FLAGS) -std=gnu99 -c ./src/pen1x.c -o ./build/pen1x.o

./build/stdlib.o: ./src/stdlib.c
	$(CC)  ${INCLUDES} $(FLAGS) -std=gnu99 -c ./src/stdlib.c -o ./build/stdlib.o

./build/stdio.o: ./src/stdio.c
	$(CC)  ${INCLUDES} $(FLAGS) -std=gnu99 -c ./src/stdio.c -o ./build/stdio.o


clean:
	rm -rf ${FILES}
	rm ./stdlib.elf