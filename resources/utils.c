#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define CODE_DIR "/home/marcosnqs/Projects/compiler/codes/tests.txt"

const char *reserved_words[] = 
{
    "principal",
    "funcao",
    "leitura",
    "escrita",
    "se",
    "senao",
    "para",
    "inteiro",
    "caractere",
    "decimal"
};

char *file_array;

int char_index = 0;

int char_count = 0;

char *scope;

int line_index = 1;

unsigned long allocated = 0;

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
};

void control_memory(size_t size) {
    if (size <= 0) {
        allocated -= size;
    } else {
        allocated += size;
    }
}