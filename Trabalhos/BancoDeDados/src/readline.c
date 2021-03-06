// Função readline para obter entradas
#include "readline.h"

char *readline(FILE *input){
    char *str = calloc(1, sizeof(char));
    char ch;

    ch = getc(input);
    while (ch != '\n' && ch != EOF)
    {
        if(ch != '\r'){
            str = realloc(str, (strlen(str)+1)*sizeof(char) + sizeof(char));
            strncat(str, &ch, 1);
        }
        ch = getc(input);
    }
    // Finalizando string
    strncat(str, "\0", 1);

    return str;
}
