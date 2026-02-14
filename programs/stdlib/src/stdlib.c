#include "stdlib.h"
#include "pen1x.h"

void* malloc(size_t size)
{
    return pen1x_malloc(size);
}

void free(void* ptr)
{
    pen1x_free(ptr);
}