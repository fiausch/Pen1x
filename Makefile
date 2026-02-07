FILES =  ./build/kernel.asm.o ./build/kernel.o ./build/idt/idt.asm.o  ./build/idt/idt.o ./build/memory/memory.o ./build/io/io.asm.o ./build/memory/heap/heap.o ./build/task/task.o ./build/memory/heap/kheap.o ./build/memory/paging/paging.o ./build/memory/paging/paging.asm.o ./build/task/tss.asm.o  ./build/disk/disk.o ./build/fs/pparser.o ./build/string/string.o ./build/disk/streamer.o ./build/fs/file.o  ./build/fs/fat/fat16.o  ./build/gdt/gdt.asm.o ./build/gdt/gdt.o  ./build/task/process.o ./build/task/task.asm.o
INCLUDES = -I./include
FLAGS-GCC = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc
FLAGS-CLANG = -g  -target i686 -O0 -nostdlib -ffreestanding  -Wall 
CC-GCC = i686-elf-gcc $(FLAGS-GCC)
CC-CLANG = clang $(FLAGS-CLANG)
CC = $(CC-CLANG) 
LINKER = ld.lld
 

all: ./bin/boot.bin ./bin/kernel.bin user_programs
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=1048576 count=16 >> ./bin/os.bin
	sudo mkdir -p /mnt/d
	sudo mount -t vfat ./bin/os.bin /mnt/d
	# Copy a file over
	sudo cp ./hello.txt /mnt/d
	# copy binary user program
	sudo cp ./programs/blank/blank.bin /mnt/d
	ls /mnt/d
	sudo umount /mnt/d
	qemu-system-i386 -hda ./bin/os.bin

./bin/kernel.bin: $(FILES)
	$(LINKER) -g -relocatable $(FILES) -o ./build/kernelfull.o
	$(CC) $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o

./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin


./build/kernel.asm.o: ./src/kernel.asm
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o

./build/kernel.o: ./src/kernel.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/kernel.c -o ./build/kernel.o

./build/idt/idt.asm.o: ./src/idt/idt.asm
	nasm -f elf -g ./src/idt/idt.asm -o ./build/idt/idt.asm.o

./build/gdt/gdt.asm.o: ./src/gdt/gdt.asm
	nasm -f elf -g ./src/gdt/gdt.asm -o ./build/gdt/gdt.asm.o

./build/idt/idt.o: ./src/idt/idt.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/idt/idt.c -o ./build/idt/idt.o

./build/memory/memory.o: ./src/memory/memory.c
	$(CC) $(INCLUDES)  $(FLAGS) -std=gnu99 -c ./src/memory/memory.c -o ./build/memory/memory.o

./build/io/io.asm.o: ./src/io/io.asm
	nasm -f elf -g ./src/io/io.asm -o ./build/io/io.asm.o

./build/memory/heap/heap.o: ./src/memory/heap/heap.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/memory/heap/heap.c -o ./build/memory/heap/heap.o

./build/memory/heap/kheap.o: ./src/memory/heap/kheap.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/memory/heap/kheap.c -o ./build/memory/heap/kheap.o

./build/memory/paging/paging.o: ./src/memory/paging/paging.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/memory/paging/paging.c -o ./build/memory/paging/paging.o

./build/memory/paging/paging.asm.o: ./src/memory/paging/paging.asm
	nasm -f elf -g ./src/memory/paging/paging.asm -o ./build/memory/paging/paging.asm.o

./build/task/tss.asm.o: ./src/task/tss.asm
	nasm -f elf -g ./src/task/tss.asm -o ./build/task/tss.asm.o

./build/task/task.asm.o: ./src/task/task.asm
	nasm -f elf -g ./src/task/task.asm -o ./build/task/task.asm.o

./build/disk/disk.o: ./src/disk/disk.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/disk/disk.c -o ./build/disk/disk.o

./build/string/string.o: ./src/string/string.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/string/string.c -o ./build/string/string.o

./build/fs/pparser.o: ./src/fs/pparser.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/fs/pparser.c -o ./build/fs/pparser.o

./build/disk/streamer.o: ./src/disk/streamer.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/disk/streamer.c -o ./build/disk/streamer.o

./build/fs/file.o: ./src/fs/file.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/fs/file.c -o ./build/fs/file.o

./build/fs/fat/fat16.o: ./src/fs/fat/fat16.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/fs/fat/fat16.c -o ./build/fs/fat/fat16.o

./build/gdt/gdt.o: ./src/gdt/gdt.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/gdt/gdt.c -o ./build/gdt/gdt.o

./build/task/task.o: ./src/task/task.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/task/task.c -o ./build/task/task.o

./build/task/process.o: ./src/task/process.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/task/process.c -o ./build/task/process.o

./build/keyboard/keyboard.o: ./src/keyboard/keyboard.c
	$(CC) $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/keyboard/keyboard.c -o ./build/keyboard/keyboard.o

mkdir: user_programs_mkdir
	mkdir -p ./bin
	mkdir -p ./build
	mkdir -p ./build/disk
	mkdir -p ./build/fs
	mkdir -p ./build/fs/fat
	mkdir -p ./build/gdt
	mkdir -p ./build/idt
	mkdir -p ./build/io
	mkdir -p ./build/memory
	mkdir -p ./build/memory/heap
	mkdir -p ./build/memory/paging
	mkdir -p ./build/string
	mkdir -p ./build/task
	mkdir -p ./programs/
	mkdir -p ./programs/blank

user_programs:
	cd ./programs/blank && $(MAKE) all

user_programs_clean:
	cd ./programs/blank && $(MAKE) clean

user_programs_mkdir:
	cd ./programs/blank && $(MAKE) mkdir

clean: user_programs_clean
	find ./bin/ -maxdepth 1 -type f -delete
	find ./build/ -maxdepth 3 -type f -delete
