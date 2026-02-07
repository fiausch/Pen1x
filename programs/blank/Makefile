CC-CLANG = clang -m32 -g -T ./linker.ld
CC-GCC = i686-elf-gcc -g -T ./linker.ld 

all:
	nasm -f elf ./src/blank.asm -o ./build/blank.o
	$(CC-CLANG) -o ./blank.bin -ffreestanding -O0 -nostdlib -fpic -g ./build/blank.o

clean:
	rm -rf ./build/blank.o
	rm -rf ./blank.bin

mkdir:
	mkdir -p ./src
	mkdir -p ./build