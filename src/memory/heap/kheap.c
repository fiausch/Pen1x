#include "memory/heap/kheap.h"
#include "config.h"
#include "kernel.h"
#include "memory/heap/heap.h"
#include "memory/memory.h"
#include <stddef.h>

struct heap kernel_heap;

struct heap_table kernel_heap_table;

void kheap_init(){
    int total_table_entries = PEN1X_HEAP_SIZE_BYTES / PEN1X_HEAP_BLOCK_SIZE; //25600 (for now ?)
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY*)(PEN1X_HEAP_TABLE_ADRESS);
    kernel_heap_table.total = total_table_entries;

    void* end = (void*)(PEN1X_HEAP_ADDRESS + PEN1X_HEAP_SIZE_BYTES);
    int res = heap_create(&kernel_heap, (void*)PEN1X_HEAP_ADDRESS, end, &kernel_heap_table);
    if(res < 0){
        print("Failed to create heap\n");
        while (1) {
        
        }
    }else{
        print("heap successfully created\n");
    }
}

void* kzalloc(size_t size){
    void* ptr = kmalloc(size);
    if(!ptr){
        return 0;
    }
    memset(ptr, 0x00, size);
    return ptr;
}

void* kmalloc(size_t size){
    return heap_malloc(&kernel_heap, size);
}

void kfree(void* ptr){
    heap_free(&kernel_heap, ptr);
}

