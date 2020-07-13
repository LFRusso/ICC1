#include "readline.h"

// Função readline para obter entradas
char *readline(FILE *input){
    char *str = calloc(1, sizeof(char));
    char ch;

    ch = getc(input);
    while (ch != '\n' && ch != '\r' && ch != EOF)
    {
        str = realloc(str, (strlen(str)+1)*sizeof(char) + sizeof(char));
        strncat(str, &ch, 1);
        ch = getc(input);
    }
    // Finalizando string
    strncat(str, "\0", 1);

    return str;
}
