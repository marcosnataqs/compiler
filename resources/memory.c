#include <stdio.h>
#include "memory.h"

unsigned long max_alloc = 0;
unsigned long allocated = 0;
unsigned long max_allocated = 0;

void control_memory(size_t size) {
    if (size <= 0) {
        allocated -= size;
    } else {
        allocated += size;
    }

    if (allocated > max_allocated) {
        max_allocated = allocated;
    }
}