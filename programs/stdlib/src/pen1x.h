#ifndef pen1x_H
#define pen1x_H
#include <stddef.h>
#include <stdbool.h>

void print(const char* filename);
int getkey();

void* pen1x_malloc(size_t size);
void pen1x_free(void* ptr);
void pen1x_putchar(char c);
int pen1x_getkeyblock();
void pen1x_terminal_readline(char* out, int max, bool output_while_typing);
void pen1x_process_load_start(const char* filename);

#endif