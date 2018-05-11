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

//TODO: Verificar
void free_all_memory() {
    // control_memory(-sizeof(file_array));
    // free(file_array);

    // for (int i = 0; i < symbtab_index; i++)
    // {
    //     control_memory(-sizeof(SymbolsTable[i].token));
    //     free(SymbolsTable[i].token);
    //     control_memory(-sizeof(SymbolsTable[i].type));
    //     free(SymbolsTable[i].type);
    //     control_memory(-sizeof(SymbolsTable[i].value));
    //     free(SymbolsTable[i].value);
    //     control_memory(-sizeof(SymbolsTable[i].scope));
    //     free(SymbolsTable[i].scope);
    //     control_memory(-sizeof(SymbolsTable));
    //     free(SymbolsTable);
    // }
}