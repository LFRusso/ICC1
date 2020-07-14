// Lê e salva as informações do BD de acordo com os metadados
#include "builder.h"

/*
*   Recebe uma string e um padrão e checa ocorrência
*/ 
int checkPattern(char* str, char* pattern){
    regex_t regex;
    int status;

    regcomp(&regex, pattern, REG_EXTENDED|REG_NOSUB);
    status = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    
    if(status != 0){
        return 0;
    }
    return 1;
}


/*
*  Recebe uma linha do arquivo dos metadados, a interpretando 
*       e salvando informações na lista de campos
*/
void parseLine(char* line, register_field* fields, int* no_fields){
    char* temp;
    int idx = *no_fields;

    if(checkPattern(line, "^field-name") || checkPattern(line, "^key-name")){
        temp = strrchr(line, ' ')+1;
        fields[idx].name = calloc(strlen(temp) + 1, sizeof(char));
        strcpy(fields[idx].name, temp);
    }

    if(checkPattern(line, "^field-type") || checkPattern(line, "^key-type")){
        temp = strrchr(line, ' ')+1;
        
        // Obtendo tipo de variável

        if(checkPattern(temp, "char")){
            // Checando se é uma string ou char
            if(checkPattern(temp, "]$")){
                // Obtendo tamanho máximo da string specificada
                char* aux = strtok(temp, "]");
                temp = strrchr(aux, '[')+1;
                fields[idx].size = sizeof(char) * atoi(temp);
            } else {
                fields[idx].size = sizeof(char);
            }
            
            fields[idx].type = CHAR;
        }

        if(checkPattern(temp, "int")){
            fields[idx].type = INT;
            fields[idx].size = sizeof(int);
        }

        if(checkPattern(temp, "double")){
            fields[idx].type = DOUBLE;
            fields[idx].size = sizeof(double);
        }
        
        if(checkPattern(temp, "float")){
            fields[idx].type = FLOAT;
            fields[idx].size = sizeof(float);
        }

        // Especifica que campo atual está completo
        *no_fields += 1;
    }
    
    return;
}

/*
*   Função principal: recebe arquivo com metadados, um int e um aquivo por
*       referência.
*   Retorna um array com as structs contendo os dados parseados e atualiza os
*       valores passados por referência
*/
register_field* builder(FILE* metafile, int* no_fields, char** regfile_name){
    char* line;
    char* temp;
    FILE* regfile;
    register_field* fields = calloc(1, sizeof(register_field));
    *no_fields = 0;
    
    line = readline(metafile);
    // Obtendo arquivo dos registros
    if(checkPattern(line, "filename")){
        // Obtendo nome do arquivo
        temp = strrchr(line, ' ')+1;
        *regfile_name = calloc(strlen(temp)+1, sizeof(char));
        strcpy(*regfile_name, temp);
        
        // Definindo arquivo
        regfile = fopen(*regfile_name, "w+");
    } else {
        printf("Arquivo de registros não especificado!\n");
        free(line);
        return fields;
    }

    // Lendo demais linhas do arquivo de metadados
    for(int N=0; line[0]; N++){
        parseLine(line, fields, &(*no_fields));
        fields = realloc(fields, sizeof(register_field) * N + sizeof(register_field));

        free(line);
        line = readline(metafile);
    }

    fclose(regfile);
    free(line);
    return fields;
}
