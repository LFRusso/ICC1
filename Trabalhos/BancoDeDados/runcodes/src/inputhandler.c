#include "inputhandler.h"

/*
*   Recebe uma entrada do usuário e checa qual a ação correspondente
*/
int getAction(char* str){
    if(checkPattern(str, "insert")){
        return 1;
    }
    
    if(checkPattern(str, "index")){
        return 2;
    }

    if(checkPattern(str, "search")){
        return 3;
    }
    
    if(checkPattern(str, "exit")){
        return 4;
    }

    return 0;
}

/*
*   Obtém conteúdo do insert do usuário
*/
char* getContent(char* str){
    char* temp;
    char* aux;
    char* content;

    temp = strtok(str, " ");
    aux = str + (strlen(temp)+1);

    content = calloc(strlen(aux)+1, sizeof(char));
    strcpy(content, aux);

    return content;
}


/*
*   Função principal: recebe e trata entradas do usuário para serem processadas
*/
void handleInput(char* regfile_name, register_field* fields, int no_fields){
    char* line;
    char* content;
    insertion_info* inserts = calloc(1, sizeof(struct insertion_info));
    int no_inserts=0;   // Número de inserções

    line = readline(stdin);
    for(int i=0; line[0] != 0; i++){
        switch(getAction(line)){
            case 1:
                // insert

                //  Aqui vai a função de inserção dos dados \o/
                content = getContent(line);
                inserts[no_inserts] = insert(regfile_name, content, fields, no_fields);
                
                no_inserts++;
                inserts = realloc(inserts, sizeof(insertion_info) * no_inserts + sizeof(insertion_info));
                //

                free(content);
                break;
            
            case 2:
                // index 
                inserts = idx(regfile_name, inserts, &no_inserts);
                //
                //  Aqui vai a função para gerar o index
                //
                
                break;

            case 3:
                // search
                inserts = idx(regfile_name, inserts, &no_inserts);
                content = getContent(line);
                search(content, regfile_name, fields, no_fields);
                free(content);
                //
                //  Aqui vai a fução de busca de index
                
                break;

            case 4:
                // exit
                
                free(line);
                free(inserts);
                return;
                break;

            default:
                printf("Ação inválida\n");
                break;
        }
        
        free(line);
        line = readline(stdin);
    }    

    free(inserts);
    free(line);
    return;
}
