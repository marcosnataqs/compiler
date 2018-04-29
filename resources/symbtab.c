#include <stdio.h>
#include "symbtab.h"

struct SymbolsTable
{
    char *token;
    char *type;
    char *value;
    char *scope;
};

struct SymbolsTable *SymbolsTable;

int symbtab_index = 0;

void new_symbtab() {
    if (symbtab_index == 0) 
    {
        SymbolsTable = malloc(sizeof(struct SymbolsTable));
        control_memory(sizeof(SymbolsTable));
    }
    else
    {
        SymbolsTable = realloc(SymbolsTable, (symbtab_index+1) * sizeof(struct SymbolsTable));
        control_memory(sizeof(SymbolsTable));
    }
    symbtab_index++; 
}

void save_to_symbtab(char *token, char *type, char *value, char *scope) {
    new_symbtab();

    SymbolsTable[symbtab_index-1].token = malloc(sizeof(char*));
    control_memory(sizeof(SymbolsTable[symbtab_index-1].token));
    SymbolsTable[symbtab_index-1].token = token;

    SymbolsTable[symbtab_index-1].type = malloc(sizeof(char*));
    control_memory(sizeof(SymbolsTable[symbtab_index-1].type));
    SymbolsTable[symbtab_index-1].type = type;

    SymbolsTable[symbtab_index-1].value = malloc(sizeof(char*));
    control_memory(sizeof(SymbolsTable[symbtab_index-1].value));
    SymbolsTable[symbtab_index-1].value = value;

    SymbolsTable[symbtab_index-1].scope = malloc(sizeof(char*));
    control_memory(sizeof(SymbolsTable[symbtab_index-1].scope));
    SymbolsTable[symbtab_index-1].scope = scope;
}

void print_symbtab() {
    for (int i = 0; i < symbtab_index; i++)
    {
        printf("\n|%s|%s|%s|%s|", 
        SymbolsTable[i].token,
        SymbolsTable[i].type, 
        SymbolsTable[i].value, 
        SymbolsTable[i].scope);
    }
}