#include "insert.h"

/*
*   Recebe uma string e retorna uma lista de strings que estão
*       divididas por um dado delimitador. Usado para separar os
*       campos na entrada do usuário
*/
char** split(char* str, char* delimiter){
    char** splitted = calloc(1, sizeof(char*));
    char* word;
    int N;

    // Dividindo string de entrada nos delimitadores
    word = strstr(str, delimiter);
    for(N=0; word; N++){
        splitted = realloc(splitted, N*sizeof(char*) + sizeof(char*));
        *word = '\0';
        splitted[N] = str;
        str = word+1;
        word = strstr(str, delimiter);
    }
    splitted = realloc(splitted, N*sizeof(char*) + sizeof(char*));
    splitted[N] = str;

    return splitted;
}

/*
*   Cadastra dada entrada de dado tipo no arquivo de registros
*/
void compute(FILE* regfile, char* input, register_field field){
    char* str_input;
    char* temp;
    int int_input;
    float float_input;
    double double_input;
    
    switch(field.type){
        // Cadastrando tipo char
        case 0:
            temp = strstr(input, "\"")+1;
            temp = strtok(temp, "\"");
            str_input = calloc(field.size, sizeof(char));
            strcpy(str_input, temp);
            fwrite(str_input, 1, field.size, regfile);
            free(str_input);
            break;
        
        // Cadastrando tipo int
        case 1:
            int_input = atoi(input);
            fwrite(&int_input, 1, field.size, regfile);
            break;

        // Cadastrando tipo float
        case 2:
            float_input = (float) atof(input);
            fwrite(&float_input, 1, field.size, regfile);
            break;

        // Cadastrando tipo double
        case 3:
            double_input = atof(input);
            fwrite(&double_input, 1, field.size, regfile);
            break;

        default:
            break;
    }
    return;
}

/*
*   Função principal: recebe o nome do arquivo de registros definido nos metadados
*       bem como o dado dos campos de entrada. Processa a inserção do usuário e salva
*       com base nesses campos, retornando as informações referentes à essa insertção
*/
insertion_info insert(char* regfile_name, char* insertion, register_field* fields, int no_fields){
    struct insertion_info insertion_info;
    char** splitted;
    FILE* regfile = fopen(regfile_name, "a");
   
    // Dividindo string de entrada
    splitted = split(insertion, ",");
    
    // Obtendo índice do registro inserido e sua posição no arquivo de registros
    insertion_info.index = atoi(splitted[0]);
    insertion_info.position = ftell(regfile);

    // Cadastrando demais campos
    for(int i=0; i<no_fields; i++){
       compute(regfile, splitted[i], fields[i]); 
    }
  
    fclose(regfile);
    free(splitted);
    return insertion_info;
}
