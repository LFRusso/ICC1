// Procura dada chave passada pelo usuário dentro do arquivo de regístros
#include "search.h"

/*
*   Obtém o offset referente à dada chave de uma informação de insert dentro do arquivo .idx
*/
int getOffset(int query_key, insertion_info* inserts, int no_inserts){
    for(int i=0; i<no_inserts; i++){
        if(inserts[i].index == query_key){
            return inserts[i].position;
        }
    }
    return -1;
}

/*
*  Responde à query do usuário, lendo o arquivo de registro no local contendo
*   a informação requisitada e imprimindo seus campos na tela
*/
void answerQuery(char* regfile_name, int offset, register_field* fields, int no_fields){
    FILE* regfile = fopen(regfile_name, "r");
    fseek(regfile, offset, 0);
    
    char* char_data;
    int int_data;
    float float_data;
    double double_data;

    // Percorrendo campos e lendo arquivo de registros de acordo com as suas informações
    for(int i=0; i<no_fields; i++){
        printf("%s: ", fields[i].name);
        switch(fields[i].type){
            case 0:
                // Char
                char_data = calloc(fields[i].size, sizeof(char));
                fread(char_data, fields[i].size, sizeof(char), regfile);
                printf("%s\n", char_data);
                free(char_data);
                break;

            case 1:
                // Int
                fread(&int_data, 1, fields[i].size, regfile);
                printf("%d\n", int_data);
                break;

            case 2:
                // Float
                fread(&float_data, 1, fields[i].size, regfile);
                printf("%.2f\n", float_data);
                break;

            case 3:
                // Double
                fread(&double_data, 1, fields[i].size, regfile);
                printf("%.2f\n", double_data);
                break;
            
            default:
                break;
        }
    }
    printf("\n");

    fclose(regfile);
    return;
}

/*
*   Função principal: recebe um índice buscado pelo usuário bem como as informações
*       dos registros. Faz a busca pelo offset dessa informação através do arquivo index
*       e imprime cada campo referente ao índice na tela
*/
void search(char* query, char* regfile_name, register_field* fields, int no_fields){
    char* filename = getFilename(regfile_name);
    insertion_info* inserts = calloc(1, sizeof(register_field));
    int offset;
    int no_inserts=0;

    idxread(filename, &inserts, &no_inserts);

    // Obtendo offset do registro
    offset = getOffset(atoi(query), inserts, no_inserts);
    if(offset != -1){
        // Buscando informação dentro do arquivo de registros
        answerQuery(regfile_name, offset, fields, no_fields);
    }
    
    free(inserts);
    free(filename);
    return;
}
