#include <stdio.h>
#include <stdlib.h>

#include "resources/memory.c"
#include "resources/utils.c"
#include "resources/logs.c"
#include "resources/symbtab.c"
#include "plataform/lexic.c"

int main(void) 
{
    printf("\nIniciando leitura do arquivo...");

    /*Transfer codes to array*/
    file_to_array();

    printf("\nIniciando analise do arquivo...");

    /*Lexic Parsing*/
    lexic();

    printf("\nAnalise realizada com sucesso!\n");

    print_symbtab();

    printf("\n\nAllocated Memory: %zu bytes\n\n", allocated);

    return 0;
}