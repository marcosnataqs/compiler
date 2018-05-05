#include <stdio.h>
#include "logs.h"

void log_error(char *msg) {
    printf("\n|ERROR|Line %d| %s\n\n",line_index, msg);
    exit(0);
}

void log_success(char *msg) {
    printf("\n|SUCCESS|Line %d| %s",line_index, msg);
}