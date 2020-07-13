#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "src/readline.h"
#include "src/builder.h"
#include "src/inputhandler.h"
#include "src/insert.h"
#include "src/search.h"

int main(){
    char* meta_name;
    FILE* metafile;
    char* regfile_name;
    register_field* fields;
    int no_fields;      // Número de campos contidos em cada entrada
   
    // Obtendo arquivo contendo metadados
    meta_name = readline(stdin);
    metafile = fopen(meta_name, "r");
    if(!metafile){
        printf("Arquivo com metadados não encontrado\n");
        free(meta_name);
        exit(1);
    }

    // Construindo lista de campos descritas nos metadados
    fields = builder(metafile, &no_fields, &regfile_name);

    // Recebendo entradas do usuário
    handleInput(regfile_name, fields, no_fields);
    
    // fechando arquivos e liberando memória
    fclose(metafile);
    free(meta_name);
    for(int i=0; i<no_fields; i++){
        free(fields[i].name);
    }
    free(fields);
    free(regfile_name);
    return 0;
}
