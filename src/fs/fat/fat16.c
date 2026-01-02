#include "fs/fat/fat16.h"
#include "fs/file.h"
#include "status.h"
#include "string/string.h"

int fat16_resolve(struct disk* disk);
void* fat16_open(struct disk* disk, struct path_part* part, FILE_MODE mode);

struct filesystem fat16fs = {
    .resolve = fat16_resolve,
    .open = fat16_open
};

struct filesystem* fat16_init(){
    strcpy(fat16fs.name, "FAT16");
    return &fat16fs;
};


int fat16_resolve(struct disk* disk){
    return -EIO; 
}

void* fat16_open(struct disk* disk, struct path_part* part, FILE_MODE mode){
    return 0x00;
}