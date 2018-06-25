#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyzer.h"

void analyzer() {
    char_index = 0;

    check_balance();
    check_finisher();

    for (char_index; char_index <= strlen(file_array); char_index++) 
    {
        switch (((int)file_array[char_index]))
        {
            case 10: // LF
                line_index++;
                break;
            case 123: // {
                scope_state = 1;
                break;
            case 125: // }
                scope_state = 0;
                break;
            case 112: // p
                verify_principal();
                break;
            case 105: // i
                verify_inteiro();
                break;
            case 100: // d
                verify_decimal();
                break;
            case 99: // c
                verify_caractere();
                break;
            case 102: // f
                verify_funcao();
                break;
            case 38: // &
                check_expression();
                break;
            case 101: // e
                verify_escrita();
                break;
            case 108: // l
                verify_leia();
                break;
            case 115: // s
                verify_se();
                break;
            case 34:
                check_aspas();
                break;
        }
    }

    exist_principal();
};

void verify_principal() {
    int i;
    int mem = 1;
    int pos_ant = 0;
    int count_virg = 0;
    char *word;

    // Catch the first word's caracter
    char_index--;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    pos_ant = char_index;

    for (i = 0; i < strlen(reserved_words[0]); i++, mem++) // principal
    {
        next_wout_space();
        word[i] = file_array[char_index];
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }

    // String final "\0"
    word[mem-1] = 00;

    if(strncmp(word, reserved_words[0], strlen(reserved_words[0])) == 0) // principal
    {
        scope = malloc(strlen(reserved_words[0]) * sizeof(char));
        strcpy(scope, reserved_words[0]);
    } else {
        control_memory(-sizeof(word));
        free(word);
        word = malloc(mem * sizeof(char));
        control_memory(sizeof(word));
        char_index = pos_ant;
        mem = 1;
        
        for (i = 0; i < strlen(reserved_words[6]); i++, mem++) // para
        {
            next_wout_space();
            word[i] = file_array[char_index];
            word = (char *) realloc(word, mem * sizeof(char));
            control_memory(sizeof(word));
        }

        // String final "\0"
        word[mem-1] = 00;

        if(strncmp(word, reserved_words[6], strlen(reserved_words[6])) != 0) // para
        {
            log_error("Erro Palavra Reservada"); 
        }
        else
        {
            next_wout_space();
            if( (int)file_array[char_index] == 40 ) // (
            {
                next_wout_space();
                while( (int)file_array[char_index] != 41 ) // )
                {
                    if( (int)file_array[char_index] == 59 ) // vírgula
                    {
                        count_virg++;
                    }
                    next_wout_space();
                }
            }

            if( count_virg != 2 )
            {
                log_error("Laço de repetição: Para");
            }
        }
    }

    control_memory(-sizeof(word));
    free(word);
};

void verify_inteiro() {
    int i;
    int mem = 1;
    char *word;

    // Catch the first word's caracter
    char_index--;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    for (i = 0; i < strlen(reserved_words[7]); i++, mem++) // inteiro
    {
        next_wout_space();

        word[i] = file_array[char_index];
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }

    // String final "\0"
    word[mem-1] = 00;

    if(strncmp(word, reserved_words[7], strlen(reserved_words[7])) == 0) // inteiro
    {
        next_wout_space();
        if ((int)file_array[char_index] == 38) // &
        {
            validate_variable(INTEIRO);
        }
        else
        {
            log_error("Declaracao de Variavel");
        }
    } else {
        log_error(strcat(word, " Erro Palavra Reservada"));
    }

    control_memory(-sizeof(word));
    free(word);
}

void verify_decimal() {
    int i;
    int mem = 1;
    char *word;

    // Catch the first word's caracter
    char_index--;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    for (i = 0; i < strlen(reserved_words[9]); i++, mem++) // decimal
    {
        next_wout_space();

        word[i] = file_array[char_index];
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }

    // String final "\0"
    word[mem-1] = 00;

    if(strncmp(word, reserved_words[9], strlen(reserved_words[9])) == 0) // decimal
    {
        next_wout_space();
        if ((int)file_array[char_index] == 38) // &
        {
            validate_variable(DECIMAL);
        }
        else
        {
            log_error("Declaracao de Variavel");
        }
    } else {
        log_error(strcat(word, " Erro Palavra Reservada"));
    }

    control_memory(-sizeof(word));
    free(word);
}

void verify_caractere() {
    int i;
    int mem = 1;
    char *word;

    // Catch the first word's caracter
    char_index--;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    for (i = 0; i < strlen(reserved_words[8]); i++, mem++) // caractere
    {
        next_wout_space();

        word[i] = file_array[char_index];
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }

    // String final "\0"
    word[mem-1] = 00;

    if(strncmp(word, reserved_words[8], strlen(reserved_words[8])) == 0) // caractere
    {
        next_wout_space();
        if ((int)file_array[char_index] == 38) // &
        {
            validate_variable(CARACTERE);
        }
        else
        {
            log_error("Declaracao de Variavel");
        }
    } else {
        log_error(strcat(word, " Erro Palavra Reservada"));
    }

    control_memory(-sizeof(word));
    free(word);
}

void validate_variable(int type) {
    int mem = 1;
    char *word;

    word = malloc((mem*2) * sizeof(char));
    control_memory(sizeof(word));

    next_wout_space();
    if ((int)file_array[char_index] >= 97 && (int)file_array[char_index] <= 122) // a..z
    {
        word[mem-1] = file_array[char_index-1]; // &
        word[mem] = file_array[char_index];
        next_wout_space();
        while ((int)file_array[char_index] != 59 
                && (int)file_array[char_index] != 44 
                && (int)file_array[char_index] != 91
                && (int)file_array[char_index] != 41) // ; ou , ou [ ou )
        {
            mem++;
            word = (char *) realloc(word, mem * sizeof(char));
            control_memory(sizeof(word));

            if (
                (int)file_array[char_index] >= 97 && (int)file_array[char_index] <= 122 // a..z
                ||
                (int)file_array[char_index] >= 65 && (int)file_array[char_index] <= 90 // A..Z
                ||
                (int)file_array[char_index] >= 48 && (int)file_array[char_index] <= 57 // 0..9
                )
            {
                word[mem] = file_array[char_index];
            }
            else
            {
                log_error("Variavel: Caractere Invalido");
            }
            
            next_wout_space();
        }

        // String final "\0"
        word[mem+1] = 00;

        if (type == CARACTERE || type == DECIMAL) {
            check_data_length(type);
        }

        if ( exist_variable(word) == 1 )
        {
            log_error("Variável já declarada");
        }
        else
        {
            save_to_symbtab(word, type, NULL, scope);
        }

        if (scope_state) { // Inside a scope
            if ((int)file_array[char_index] == 44) // ,
            {
                next_wout_space();
                if ((int)file_array[char_index] == 38) // &
                {
                    validate_variable(type);
                }
                else
                {
                    log_error("Declaracao de Variavel");
                }
            }
            else if ((int)file_array[char_index] != 59) // ;
            {
                log_error("Finalizacao de linha ';'");
            }
        }
        else // Outside a scope
        {
            if ((int)file_array[char_index] == 44) // ,
            {
                next_wout_space();
                check_parameters();
            }
        }
    }
    else
    {
        log_error("Variavel: caractere Inicial Nao Esta Entre a..z");
    }
}

void check_data_length(int type) {
    if ((int)file_array[char_index] == 91) { // [
        next_wout_space();
        while ((int)file_array[char_index] >= 48 && (int)file_array[char_index] <= 57) // 0..9
        {
            next_wout_space();
        }

        if (type == DECIMAL) {
            if ((int)file_array[char_index] != 46) // ponto
            {
                log_error("Variavel: Informe o Separador de Casas Decimais");
            }
            else
            {
                next_wout_space();
            }

            while ((int)file_array[char_index] >= 48 && (int)file_array[char_index] <= 57) // 0..9
            {
                next_wout_space();
            }    
        }

        if ((int)file_array[char_index] != 93) { // ]
            log_error("Variavel: Falta Caractere ']' na Declaracao");
        }
        else
        {
            next_wout_space();
        }
    }
    else
    {
        log_error("Variavel: Falta Caractere '[' na Declaracao");
    }
}

void verify_funcao() {
    int i;
    int mem = 1;
    char *word;

    // Catch the first word's caracter
    char_index--;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    for (i = 0; i < strlen(reserved_words[1]); i++, mem++) // funcao
    {
        next_wout_space();
        word[i] = file_array[char_index];
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }

    // String final "\0"
    word[mem-1] = 00;

    if(strncmp(word, reserved_words[1], strlen(reserved_words[1])) == 0) // funcao
    {
        next_wout_space();
        if ((int)file_array[char_index] == 102) // f
        {
            check_func_name();       
        }
        else
        {
            log_error("Funcao Deve Iniciar com Caractere 'f'");
        }
    } else {
        log_error(word);
    }

    control_memory(-sizeof(word));
    free(word);
}

void check_func_name() {
    int mem = 1;
    char *word;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    while (
            (int)file_array[char_index] >= 97 && (int)file_array[char_index] <= 122 // a..z
            ||
            (int)file_array[char_index] >= 65 && (int)file_array[char_index] <= 90 // A..Z
            ||
            (int)file_array[char_index] >= 48 && (int)file_array[char_index] <= 57 // 0..9
        )
    {
        word[mem-1] = file_array[char_index];
        mem++;
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
        next_wout_space();
    }
    
    // String final "\0"
    word[mem-1] = 00;

    // If principal function not in the begininng
    if (char_index <= 20) {
        scope = malloc(sizeof(char));
    }

    if (scope_state == 0 && strcmp(word, scope) != 0) { // Scope change
        scope = malloc(strlen(word) * sizeof(char));
        strcpy(scope, word);
    }

    if ((int)file_array[char_index] == 40) // (
    {
        if (scope_state)
        {
            while ((int)file_array[char_index] != 59) // ;
            {
                next_wout_space();
            }
        }
        else
        {
            next_wout_space();
            check_parameters();

            if ((int)file_array[char_index] != 41) // )
            {
                log_error("Funcao: Falta Caractere ')'");
            }
        }
    }
    else
    {
        log_error("Funcao: Falta Caractere '('");
    }
}

void check_parameters() {
    if ((int)file_array[char_index] != 41) // )
    {
        if ((int)file_array[char_index] >= 105) // i
        {
            verify_inteiro();
        }
        else if ((int)file_array[char_index] >= 100) // d
        {
            verify_decimal();
        }
        else if ((int)file_array[char_index] >= 99) // c
        {
            verify_caractere();
        }
        else
        {
            log_error("Tipo de Dados Invalido");
        }
    }
}

void check_expression() {
    next_wout_space();
    if ((int)file_array[char_index] >= 97 && (int)file_array[char_index] <= 122) // a..z
    {
        //TODO: Validar atribuições e expressões
    }
    else
    {
        log_error("Variavel: caractere Inicial Nao Esta Entre a..z");
    }
}

void verify_escrita() {
    int i;
    int mem = 1;
    char *word;

    // Catch the first word's caracter
    char_index--;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    for (i = 0; i < strlen(reserved_words[3]); i++, mem++) // escrita
    {
        next_wout_space();
        word[i] = file_array[char_index];
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }

    // String final "\0"
    word[mem-1] = 00;

    if(strncmp(word, reserved_words[3], strlen(reserved_words[3])) != 0) // escrita
    {
        log_error(strcat(word, " Erro Palavra Reservada"));
    }

    control_memory(-sizeof(word));
    free(word);

    next_wout_space();
    if( (int)file_array[char_index] == 40 ) // (
    {
        do
        {
            next_wout_space();
            if( (int)file_array[char_index] == 38 ) // &
            {
                mem = 1;
                word = malloc(mem * sizeof(char));
                control_memory(sizeof(word));

                word[mem-1] = file_array[char_index];

                next_wout_space();

                while (
                    (int)file_array[char_index] >= 97 && (int)file_array[char_index] <= 122 // a..z
                    ||
                    (int)file_array[char_index] >= 65 && (int)file_array[char_index] <= 90 // A..Z
                    ||
                    (int)file_array[char_index] >= 48 && (int)file_array[char_index] <= 57 // 0..9
                    )
                {
                    mem++;
                    word = (char *) realloc(word, mem * sizeof(char));
                    control_memory(sizeof(word));
                    word[mem-1] = file_array[char_index];
                    next_wout_space();
                }

                // String final "\0"
                word[mem] = 00;

                if ( exist_variable(word) == 0 )
                {
                    log_error("Variável não declarada anteriormente");
                }

                control_memory(-sizeof(word));
                free(word);
            }
            else if( (int)file_array[char_index] == 34 ) // aspas
            {
                check_aspas();
                next_wout_space();
            }
        } while( (int)file_array[char_index] == 44 || (int)file_array[char_index] == 43 ); // vírgula, Mais
    }
}

void verify_leia() {
    int i;
    int mem = 1;
    char *word;

    // Catch the first word's caracter
    char_index--;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    for (i = 0; i < strlen(reserved_words[2]); i++, mem++) // leia
    {
        next_wout_space();
        word[i] = file_array[char_index];
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }

    // String final "\0"
    word[mem-1] = 00;

    if(strncmp(word, reserved_words[2], strlen(reserved_words[2])) != 0) // leia
    {
        log_error(strcat(word, " Erro Palavra Reservada"));
    }

    control_memory(-sizeof(word));
    free(word);

    next_wout_space();
    if( (int)file_array[char_index] == 40 ) // (
    {
        do
        {
            next_wout_space();
            if( (int)file_array[char_index] == 38 ) // &
            {
                mem = 1;
                word = malloc(mem * sizeof(char));
                control_memory(sizeof(word));

                word[mem-1] = file_array[char_index];

                next_wout_space();

                while (
                    (int)file_array[char_index] >= 97 && (int)file_array[char_index] <= 122 // a..z
                    ||
                    (int)file_array[char_index] >= 65 && (int)file_array[char_index] <= 90 // A..Z
                    ||
                    (int)file_array[char_index] >= 48 && (int)file_array[char_index] <= 57 // 0..9
                    )
                {
                    mem++;
                    word = (char *) realloc(word, mem * sizeof(char));
                    control_memory(sizeof(word));
                    word[mem-1] = file_array[char_index];
                    next_wout_space();
                }

                // String final "\0"
                word[mem] = 00;

                if ( exist_variable(word) == 0 )
                {
                    log_error("Variável não declarada anteriormente");
                }

                control_memory(-sizeof(word));
                free(word);
            }   
        } while( (int)file_array[char_index] == 44 ); // vírgula
    }
}

void exist_principal() {
    int i;
    int exist = 0;

    for (i = 0; i < symbtab_index; i++)
    {
        if(strncmp(SymbolsTable[i].scope, reserved_words[0], strlen(reserved_words[0])) == 0) // principal
        {
            exist = 1;
        }
    }

    if (exist != 1)
    {
        log_error("Nao Existe Funcao Principal Declarada");
    }
}

void verify_se() {
    int i;
    int mem = 1;
    int pos_ant = 0;
    char *word;

    // Catch the first word's caracter
    char_index--;

    pos_ant = char_index;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    for (i = 0; i < strlen(reserved_words[4]); i++, mem++) // se
    {
        next_wout_space();
        word[i] = file_array[char_index];
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }

    // String final "\0"
    word[mem-1] = 00;

    if(strncmp(word, reserved_words[4], strlen(reserved_words[4])) != 0) // se
    {
        log_error(strcat(word, " Erro Palavra Reservada"));
    }
    
    next_wout_space();

    if ((int)file_array[char_index] != 40) // (
    {
        control_memory(-sizeof(word));
        free(word);
        word = malloc(mem * sizeof(char));
        control_memory(sizeof(word));
        char_index = pos_ant;
        mem = 1;
        
        for (i = 0; i < strlen(reserved_words[5]); i++, mem++) // senao
        {
            next_wout_space();
            word[i] = file_array[char_index];
            word = (char *) realloc(word, mem * sizeof(char));
            control_memory(sizeof(word));
        }

        // String final "\0"
        word[mem-1] = 00;

        if(strncmp(word, reserved_words[5], strlen(reserved_words[5])) != 0) // senao
        {
            log_error(strcat(word, " Erro Palavra Reservada")); 
        }
    }

    control_memory(-sizeof(word));
    free(word);
}

void check_balance()
{
    int i;
    int abre = 0;
    int fecha = 0;
    int counter = 0;

    for(i = 0; i <= strlen(file_array); i++)
    {
        if((int)file_array[i] == 40) // (
        {
            abre++;
        }
    }

    for(i = 0; i <= strlen(file_array); i++)
    {
        if((int)file_array[i] == 41) // )
        {
            fecha++;
        }
    }

    if (abre != fecha)
    {
        printf("\n|ERROR| Duplo Balanceamento: Parenteses\n\n");
        exit(0);
    }

    abre = fecha = 0;

    for(i = 0; i <= strlen(file_array); i++)
    {
        if((int)file_array[i] == 123) // {
        {
            abre++;
        }
    }

    for(i = 0; i <= strlen(file_array); i++)
    {
        if((int)file_array[i] == 125) // }
        {
            fecha++;
        }
    }

    if (abre != fecha)
    {
        printf("\n|ERROR| Duplo Balanceamento: Chaves\n\n");
        exit(0);
    }

    abre = fecha = 0;

    for(i = 0; i <= strlen(file_array); i++)
    {
        if((int)file_array[i] == 91) // [
        {
            abre++;
        }
    }

    for(i = 0; i <= strlen(file_array); i++)
    {
        if((int)file_array[i] == 93) // ]
        {
            fecha++;
        }
    }

    if (abre != fecha)
    {
        printf("\n|ERROR| Duplo Balanceamento: Colchetes\n\n");
        exit(0);
    }

    for(i = 0; i <= strlen(file_array); i++)
    {
        if((int)file_array[i] == 39) // '
        {
            counter++;
        }
    }

    if (counter % 2 != 0)
    {
        printf("\n|ERROR| Duplo Balanceamento: Aspas Simples\n\n");
        exit(0);
    }

    counter = 0;

    for(i = 0; i <= strlen(file_array); i++)
    {
        if((int)file_array[i] == 34) // "
        {
            counter++;
        }
    }

    if (counter % 2 != 0)
    {
        printf("\n|ERROR| Duplo Balanceamento: Aspas Duplas\n\n");
        exit(0);
    }

}

void check_finisher()
{
    int i;
    int back;

    for(i = 0; i <= strlen(file_array); i++)
    {
        if((int)file_array[i] == 10) // LF
        {
            back = i;

            while( (int)file_array[i] == 00 || (int)file_array[i] == 32 || (int)file_array[i] == 10 )
            {
                i--;
            }

            if( (int)file_array[i] != 59 && (int)file_array[i] != 123 && (int)file_array[i] != 125 )
            {
                printf("\n|ERROR| Finalização de linha\n\n");
                exit(0);
            }

            i = back;
        }
    }
}

void check_aspas()
{
    next_wout_space();
    while((int)file_array[char_index] != 34) // aspas
    {
        next_wout_space();
    }
}

int exist_variable(char *word)
{
    int i;
    int exist = 0;

    for (i = 0; i < symbtab_index; i++)
    {
        if(strncmp(SymbolsTable[i].token, word, strlen(word)) == 0)
        {
            exist = 1;
        }
    }

    return exist;
}