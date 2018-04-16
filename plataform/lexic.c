#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexic.h"

void lexic() {
    char_index = 1;

    if ((int)file_array[char_index] == 112) { //p
        verify_reserved_words((int)file_array[char_index]);
    }
};

void verify_reserved_words(int ch) {
    char *builded_word;
    builded_word = (char *) malloc(sizeof(char));

    for (int i = 0; i < strlen(reserved_words[0]); i++) {
        if(ch == (int)reserved_words[0][i]) {
            builded_word[i] = (char)ch;
        }
    }

    printf("%c", builded_word[0]);
};