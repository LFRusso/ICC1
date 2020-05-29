#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Leitura de linha do arquivo
char* readLine(FILE *input){
    char *str = (char*) malloc(sizeof(char));
    char ch;

    ch = getc(input);
    while(ch != '\n' && ch != EOF){
        // Condição feita por conta do carriage return em algumas linhas dos arquivos de entrada
        if(ch != 13){
            str = realloc(str, strlen(str)*sizeof(char)+sizeof(char)+1);
            strncat(str, &ch, 1);
        }
        ch = getc(input); 
    }
    // Finalizando string
    strncat(str, "\0", 1);
    
    return str;
}

int main(){
    char *str;

    str = readLine(stdin);
    for(int i=0; str[0] != 0; i++){
        printf("%s\n", str);
        
        str = readLine(stdin);
    }

    free(str);
    return 0;
}
