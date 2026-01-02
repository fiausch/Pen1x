#include "fs/file.h"
#include "config.h"
#include "kernel.h"
#include "memory/heap/kheap.h"
#include "memory/memory.h"
#include "status.h"

struct filesystem* filesystems[PEN1X_MAX_FILESYSTEMS];
struct file_descriptor* file_descriptors[PEN1X_MAX_FILE_DESCRIPTORS];

static struct filesystem** fs_get_free_filesystem(){
    int i = 0;
    for(i = 0; i < PEN1X_MAX_FILESYSTEMS; ++i){
        if(filesystems[i] == 0){
            return &filesystems[i];
        }
    }

    return 0x00;
}

void fs_insert_filesystem(struct filesystem* filesystem){
    struct filesystem** fs;
    if(filesystem == 0){
        //Panic not yet impl. just a loop for now
        print("Problem finding filesystem");
        while(1){}
    }
    fs = fs_get_free_filesystem();
    if(!fs){
        //Panic not yet impl. just a loop for now
        print("Problem inserting filesystem");
        while(1){}
    }

    *fs = filesystem;
}

static void fs_static_load(){
    //fs_insert_filesystem(fat16_init());

}

void fs_load(){
    memset(filesystems, 0, sizeof(filesystems));
    fs_static_load();
}

void fs_init(){
    memset(file_descriptors, 0, sizeof(file_descriptors));
    fs_load();
}

static int file_new_descriptor(struct file_descriptor** descriptor_out){
    int res = -ENOMEM;
    for(int i = 0; i < PEN1X_MAX_FILE_DESCRIPTORS; ++i){
        if(file_descriptors[i] == 0){
            struct file_descriptor* desc = kzalloc(sizeof(struct file_descriptor));
            // Descriptors start at 1 not 0
            desc->index = i + 1;
            file_descriptors[i] = desc;
            *descriptor_out = desc;
            res = 0;
            break;
        }
    }

    return res;
}

static struct file_descriptor* file_get_descriptor(int fd){
    if(fd <= 0 || fd >= PEN1X_MAX_FILE_DESCRIPTORS){
        return 0;
    }
    //descriptors start at 1
    int index = fd-1;
    return file_descriptors[index];

}

struct filesystem* fs_resolve(struct disk* disk){
    struct filesystem* fs = 0;
    for(int i = 0; i < PEN1X_MAX_FILESYSTEMS; ++i){
        if(filesystems[i] != 0 && filesystems[i]->resolve(disk) == 0){
            fs = filesystems[i];
            break;
        }
    }
    return fs;
}

int fopen(const char* filename, const char* mode){
    return -EIO;
}