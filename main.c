#include <stdio.h>
#include <stdlib.h>

#include "plataform/lexic.c"
#include "resources/utils.c"

int main(void) {

    /*Transfer codes to array*/
    file_to_array();

    /*Lexic Analyse*/
    lexic();

    return 0;
}