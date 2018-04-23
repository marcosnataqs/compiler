#include <stdio.h>
#include <stdlib.h>

#include "plataform/lexic.c"
#include "resources/utils.c"

int main(void) 
{
    /*Transfer codes to array*/
    file_to_array();

    /*Lexic Parsing*/
    lexic();

    printf("\nAllocated Memory: %zu bytes\n\n", allocated);

    return 0;
}