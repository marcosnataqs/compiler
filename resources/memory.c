#include <stdio.h>
#include "memory.h"

unsigned long allocated = 0;

void control_memory(size_t size) {
    if (size <= 0) {
        allocated -= size;
    } else {
        allocated += size;
    }
}