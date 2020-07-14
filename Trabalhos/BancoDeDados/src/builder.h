// Constroi o arquivo de registros a partir dos metadados
#ifndef _BUILDER_H_
#define _BUILDER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <locale.h>

#include "readline.h"

typedef enum {
    CHAR,
    INT,
    FLOAT,
    DOUBLE
} dtype;

// struct referente à um campo do registro
typedef struct register_field {
    char* name;
    dtype type; 
    int size;
} register_field;

// struct referente à informação de uma inserção
typedef struct insertion_info {
    int index;
    int position;
} insertion_info;


register_field* builder(FILE* metafile, int* no_field, char** regfile_name);

int checkPattern(char* str, char* pattern);

#endif
