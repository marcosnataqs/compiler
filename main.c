#include <stdio.h>
#include <stdlib.h>

#include "resources/memory.c"
#include "resources/utils.c"
#include "resources/logs.c"
#include "resources/symbtab.c"
#include "plataform/lexic.c"

int main(void) 
{
    /*Transfer codes to array*/
    file_to_array();

    /*Lexic Parsing*/
    lexic();

    printf("\n\nAllocated Memory: %zu bytes\n\n", allocated);

    return 0;
}