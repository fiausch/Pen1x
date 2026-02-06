#ifndef PROCESS_H
#define PROCESS_H
#include "config.h"
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
};

int process_load_for_slot(const char* filename, struct process** process, int process_slot);

#endif