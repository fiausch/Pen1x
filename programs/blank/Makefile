CC-CLANG = clang -m32 -g -T ./linker.ld
CC-GCC = i686-elf-gcc -g -T ./linker.ld 
CC = ${CC-CLANG}
FILES=./build/blank.o
INCLUDES= ../stdlib/src

all: ${FILES}
	${CC} -o ./build/blank.elf -ffreestanding -O0 -nostdlib -fpic -g ${FILES} ../stdlib/stdlib.elf

./build/blank.o: ./src/blank.c
	${CC} ${INCLUDES}  -I./$(FLAGS) -std=gnu99 -c ./src/blank.c -o ./build/blank.o

clean:
	rm -rf ./build/blank.o
	rm -rf ${FILES}
	rm ./build/blank.elf