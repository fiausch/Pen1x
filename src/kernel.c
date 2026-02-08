#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "config.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "isr80h/isr80h.h"
#include "keyboard/keyboard.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "memory/memory.h"
#include "status.h"
#include "string/string.h"
#include "fs/file.h"
#include "task/task.h"
#include "task/process.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "disk/streamer.h"
#include "gdt/gdt.h"
#include "task/tss.h"

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_writechar(char c, char colour)
{
    if (c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }

    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}
void terminal_initialize()
{
    video_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }   
}



void print(const char* str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}

static struct paging_4gb_chunk* kernel_chunk = 0;

void panic(const char* msg){
    print(msg);
    while(1);
}

void kernel_page(){
    kernel_registers();
    paging_switch(kernel_chunk);
}


struct tss tss;
struct gdt gdt_real[PEN1X_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[ ] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00},                //NULL Segment
    {.base = 0x00, .limit = 0xFFFFFFFF, .type = 0x9A},          //Kernel code segment
    {.base = 0x00, .limit = 0xFFFFFFFF, . type = 0x92},         //Kernel data segment
    {.base = 0x00, .limit = 0xFFFFFFFF, .type = 0xF8},          //User code segment 
    {.base = 0x00, .limit = 0xFFFFFFFF, .type = 0xF2},          //User data segment
    {.base = (uint32_t)&tss, .limit=sizeof(tss), .type = 0xE9}      // TSS Segment
//gotta add user segment but whatever

};
void kernel_main()
{
    terminal_initialize();

    memset(gdt_real, 0x00, sizeof(gdt_real));
    
    gdt_structured_to_gdt(gdt_real, gdt_structured, PEN1X_TOTAL_GDT_SEGMENTS);
    
    //load the GDT
    gdt_load(gdt_real, sizeof(gdt_real));
    // Initialize the heap
    kheap_init();

    // Initialize filesystems
    fs_init();

    // Search and initialize the disks
    disk_search_and_init();

    // Initialize the interrupt descriptor table
    idt_init();
    // Setup TSS
    memset(&tss, 0x00, sizeof(tss));
    tss.esp0 = 0x600000;
    tss.ss0 = KERNEL_DATA_SELECTOR;

    //Load TSS
    tss_load(0x28); //0x28 is the offset

    // Setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    
    // Switch to kernel paging chunk
    paging_switch(kernel_chunk);

    // Enable paging
    enable_paging();

    //register kernel commands
    isr80h_register_commands();


    keyboard_init();

    struct process* process = 0;
    int res = process_load("0:/blank.bin", &process);
    if(res != PEN1X_ALL_OK){
        panic("failed to load blank.bin");
    }
    print("successfully loaded");

    task_run_first_ever_task();

}
/*
FUNCIOTNALITY:

    01: PAGING:

    char* ptr = kzalloc(4096);
    paging_set(paging_4gb_chunk_get_directory(kernel_chunk), (void*)0x1000, (uint32_t)ptr |PAGING_ACCESS_FROM_ALL | PAGING_IS_PRESENT | PAGING_IS_WRITEABLE);
  
    //enable paging
    enable_paging();

    char* ptr2 = (char*)0x1000;
    ptr2[0] = 'A';
    ptr2[1] = 'B';
    print(ptr2);
    print(ptr);

    0x1000 points to 0x1000000
    0x1000000 points to 0x1000000

    02: READING FROM DISK: 
    char buf[512];




    03: PATH PARSING:
    struct path_root* root_path = pathparser_parse("0:/bin/shell.exe", NULL);
    

    04: DISK STREAM READING:
    struct disk_stream* stream = diskstreamer_new(0);
    diskstreamer_seek(stream, 0x21C);
    char c = 0;
    diskstreamer_read(stream, &c,1);

    05:STRINGS:
    05.01 STRING COPY:
    char buf[20];
    strcpy(buf, "hello!");
    print(buf);


    06:FAT16 OPENING FILES:
    int fd = fopen("0:/hello.txt", "r");
    if (fd)
    {
        print("We opened hello.txt\n");
    }
    while(1) {}

    06:FAT16 READING FILES (FAT16 SEEK):
    int fd = fopen("0:/hello.txt", "r");
    if (fd)
    {
        print("We opened hello.txt\n");
        char buf[14];
        fseek(fd, 2, SEEK_SET);
        fread(buf, 11, 1,fd);
        print(buf);
    }
    06:FAT16 CLOSING FILES:

        int fd = fopen("0:/hello.txt","r");
    if(fd){
        struct file_stat s;
        fstat(fd, &s);
        fclose(fd);
        print("const char *str");
    }
    07:process laoding:
    
    struct process* process = 0;
    int res = process_load("0:/blank.bin", &process);
    if(res != PEN1X_ALL_OK){
        panic("failed to load blank.bin");
    }
    print("successfully loaded");

    task_run_first_ever_task();


*/