#ifndef PROCESS_H
#define PROCESS_H
#include "config.h"
#include "keyboard/keyboard.h"
#include "task/task.h"
#include <stdint.h>

struct process{
    // the process ID (PID)
    uint16_t id;

    char filename[PEN1X_MAX_PATH];

    //this will be the main process task
    struct task* task;

    //the memory (malloc) allocations of the process
    void* allocations[PEN1X_MAX_PROGRAM_ALLOCATIONS];

    //physical pointer to the process memory
    void* ptr;

    //The physical pointer to the stack memory
    void* stack;

    //sizeof the data pointed to by "ptr"
    uint32_t size;

    struct keyboard_buffer{
        char buffer[PEN1X_KEYBOARD_BUFFER_SIZE];
        int head;
        int tail;
    }keyboard;
};

int process_load_for_slot(const char* filename, struct process** process, int process_slot);
int process_load(const char* filename, struct process** process);
struct process* process_current();
int process_switch(struct process* process);
int process_load_switch(const char* filename, struct process** process);
#endif