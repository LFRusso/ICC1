#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/* OBS: um modo que eu poderia ter feito para deixar mais "compato" é no lugar da readLine, usar 
 * uma função para percorrer até encontrar um caráctere '1', '2', '-' e etc e salvar o resto como 
 * inteiro usando scanf().
 * Acabei optando por fazer da maneia que fiz porque acredito que fica mais "geral" e não daria
 * problema se eu tivesse por exemplo alguma entrada em que tem um número no nome 
 */

struct registro{
    char *name;
    int year;
};

// Leitura de linha do arquivo
char *readLine(FILE *input)
{
    char *str = (char *)malloc(sizeof(char));
    char ch;

    ch = getc(input);
    while (ch != '\n' && ch != EOF)
    {
        // Condição feita por conta do carriage return em algumas linhas dos arquivos de entrada
        if (ch != 13)
        {
            str = realloc(str, strlen(str) * sizeof(char) + sizeof(char) + 1);
            strncat(str, &ch, 1);
        }
        ch = getc(input);
    }
    // Finalizando string
    strncat(str, "\0", 1);
    return str;
}

// Função recebe uma cadeia de caractéries e converte para inteiro, de forma que '1' (ascii 49) -> 1 
int toInt(char *str){
    int int_str = 0;
    int signal;
    int no_order = strlen(str);

    // Checa se a cadeia começa com um char '-', indicando que se trata de um negativo
    signal = str[0] == '-' ? -1 : 1;

    if (signal == 1){
        // Caso o número seja posivito, posso percorre-lo normalmente 
        for (int i = 0; i < no_order; i++){
            // Subtraindo valor na tabela ascii do caractere '1'
            int_str += (str[i] - 48) * pow(10, no_order - i - 1);
        }
    }
    else{
        // Caso seja negativo, preciso começar um índice depois 
        for (int i = 1; i < no_order; i++){
            // Subtraindo valor na tabela ascii do caractere '1'
            int_str += (str[i] - 48) * pow(10, no_order - i - 1);
        }
    }

    // Retorno o valor absoluto multiplicado pelo sinal
    return signal * int_str;
}


// Procedimento recebe a linha de entrada e separa o nome do número no final, e salva no rigistro
void registerInfo(char *str, struct registro *registro){
    int idx = 0;
    char *year;

    // Buscando última ocorrência de um espaço (ascii 32)
    for (int i = 0; i < strlen(str); i++){
        idx = str[i] == 32 && i != strlen(str) - 1 ? i : idx;
    }

    // Obtendo nome na linha de entrada
    // Percorre a str até o índice determinado acima como separador do nome e do número
    registro->name = (char *)malloc(sizeof(char) * (idx) + 1);
    for (int i = 0; i < idx; i++){
        registro->name[i] = str[i];
    }
    // Finalizando string
    registro->name[idx] = '\0';
    
    // Obtendo número na linha de entrada
    // Começa um índice após o encontrado (para não considerar o caractére do espaço em si)
    year = (char *)malloc(sizeof(char) * (strlen(str) - idx) + 1);
    for (int i = idx + 1; i <= strlen(str) && str[i] != 32; i++){
        year[i - (idx + 1)] = str[i];
    }
    // Finalizando string
    year[strlen(str) - idx] = '\0';
   
    // Converte string do ano para inteiro e cadastra no registro
    registro->year =  toInt(year);
    free(year);
    return;
}

// Funções que serão usadas pelo qsort() para fazer a comparação de inteiros OU strings, para podemos ordenar por ordem de ano ou alfabética
// ===============
int compare_words(const void *a, const void *b){
    struct registro *registroA = (struct registro *)a;
    struct registro *registroB = (struct registro *)b;

    return -strcmp(registroB->name, registroA->name);
}

int compare_int(const void *a, const void *b){
    struct registro *registroA = (struct registro *)a;
    struct registro *registroB = (struct registro *)b;

    return -(registroB->year - registroA->year);
}
//===============

// Procedimento para realizar a ordenação dos registros de acordo com o modo selecionado
void sort(struct registro *registros, int mode, int no_elements){
    switch (mode)
    {
        case 1:
            qsort(registros, no_elements, sizeof(struct registro), compare_words);
            break;

        case 2:
            qsort(registros, no_elements, sizeof(struct registro), compare_int);
            break;

        default:
            break;
    }

    return;
}

int main(){
    struct registro *registros = (struct registro *)malloc(10000 * sizeof(struct registro));
    char *str = (char *)malloc(sizeof(char));
    int mode;
    int i = 0;

    // Obtendo modo de ordenação
    // obs: o getc() é usado para tirar o \n do buffer após o uso do scanf()
    // Isso estava atrapalhando na readline
    scanf("%d", &mode);
    getc(stdin);

    // Cadastrando cada registro
    str = readLine(stdin);
    for (; str[0] != 0; i++){
        registerInfo(str, &registros[i]);

        str = readLine(stdin);
    }
    sort(registros, mode, i);

    // Escrevendo lista dos registros ordenados
    for (int j = 0; j < i; j++){
        printf("%d\t%s\n", registros[j].year, registros[j].name);
        // Já aproveitando para liberar a memória
        free(registros[j].name);
    }

    free(str);
    free(registros);
    return 0;
}
