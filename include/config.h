#ifndef CONFIG_H
#define CONFIG_H

//dont touch
#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10


#define PEN1X_TOTAL_INTERRUPTS 512 //max amount of interrupts btw

#define PEN1X_HEAP_SIZE_BYTES 104857600 // 100MiB heap size, bad implementation, obv, it's static and doesn't check RAM. also only 100 megs but whatever man :/
#define PEN1X_HEAP_BLOCK_SIZE 4096
#define PEN1X_HEAP_ADDRESS 0x01000000
#define PEN1X_HEAP_TABLE_ADRESS 0x00007E00

#define PEN1X_SECTOR_SIZE 512
#endif