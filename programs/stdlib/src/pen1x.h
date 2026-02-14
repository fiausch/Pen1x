#ifndef pen1x_H
#define pen1x_H
#include <stddef.h>

void print(const char* filename);
int getkey();

void* pen1x_malloc(size_t size);
void pen1x_free(void* ptr);

#endif