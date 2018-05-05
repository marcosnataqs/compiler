#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define CODE_DIR "/home/marcosnqs/Projects/compiler/codes/tests.txt"

const char *reserved_words[] = 
{
    "principal",
    "funcao",
    "leia",
    "escrita",
    "se",
    "senao",
    "para",
    "inteiro",
    "caractere",
    "decimal"
};

enum Variable_Type
{
    INTEIRO,
    DECIMAL,
    CARACTERE
};

char *file_array;

int char_index = 0;

int char_count = 0;

char *scope;

int scope_state = 0;

int line_index = 1;

void file_to_array() 
{
    char url[] = CODE_DIR;
    char ch;
    FILE *arq;

    arq = fopen(url, "r");
    if (arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo!\n");
    else
        count_file();
        while ( (ch = fgetc(arq)) != EOF) 
        {
            file_array[char_index] = ch;
            char_index++;
        }
    fclose(arq);
};

void count_file() 
{
    char url[] = CODE_DIR;
    char ch;
    FILE *arq;

    arq = fopen(url, "r");
    if (arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo!\n");
    else
        while ( (ch = fgetc(arq)) != EOF)
            char_count++;

    fclose(arq);

    file_array = (char *) malloc(char_count * sizeof(char));
    control_memory(sizeof(file_array));
};

void next_wout_space() {
    int ascii = 128;

    char_index++;
    ascii = (int)file_array[char_index];

    if (ascii == 00 || ascii == 10 || ascii == 32)
    {
        next_wout_space();
    }
}