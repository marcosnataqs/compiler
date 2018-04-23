#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexic.h"

void lexic() {
    char *word;
    int mem = 1;
    
    char_index = 0;
    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));
    SymbolTable = malloc(sizeof(struct SymbolTables));
    control_memory(sizeof(SymbolTable));

    for (char_index; char_index <= strlen(file_array); char_index++) 
    {
        switch (((int)file_array[char_index]))
        {
            case 32: // espaço
                break;
            case 40: // (
                verify_word(word);
                break;
            case 10: // LF
                line_index++;
                break;
            default:
                word[char_index] = file_array[char_index];
                break;
        }
        mem++;
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }
};

void verify_word(char *word) {
    if(strncmp(word, reserved_words[0], strlen(reserved_words[0])) == 0) // principal
    {
        scope = malloc(strlen(reserved_words[0]) * sizeof(char));
        strcpy(scope, reserved_words[0]);
        printf("%s", scope);
    }
};