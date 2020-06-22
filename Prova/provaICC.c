// Luiz Fernando S. E. Santos
// No USP 10892680

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <locale.h>

char* readline(FILE* input){
    char* str = calloc(1, sizeof(char));
    char ch;
    
    ch = getc(input);
    while (ch != '\n' && ch != EOF){
        str = realloc(str, strlen(str)*sizeof(char) + 2*sizeof(char));
        strncat(str, &ch, 1);
        ch = getc(input);
    }
    // Finalizando string
    strncat(str, "\0", 1);

    return str;
}

// Recebe uma string e um padrão e checa ocorrência
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

// Recebe uma string e retorna sua versão de trás para frente
char* invertStr(char* str){
    char* inverted = calloc(strlen(str), sizeof(char));
    for (int i=0; i<(int)strlen(str); i++){
        inverted[strlen(str)-i-1] = str[i];
    }

    return inverted;
}

// Recebe uma string e checa se é um palíndrome
int checkPalindrome(char* str){
    char* inverted_str;
    
    inverted_str = invertStr(str);
    if(strcmp(inverted_str, str) == 0){
        free(inverted_str);
        return 1;
    } 
    free(inverted_str);
    return 0;
}

// Checa similaridade entre duas palavras
float checkSim(char* str1, char* str2){
    char* conv = strlen(str1) < strlen(str2) ? str1 : str2;
    char* str = strlen(str1) < strlen(str2) ? str2 : str1;
    float weight = 0.10;
    float L = 0;
    float Li = 0;
   
    for (int i=0; i<= (int)strlen(str)-(int)strlen(conv); i++){
        Li = 0;
        for (int j=0; j <(int)strlen(conv); j++){
           Li = conv[j] == str[i+j] ? Li+3 : Li-1;
        }
        L = Li > L ? Li : L; 
    }
    
    // Punição por tamanho diferente de caraceres
    L -= (strlen(str) - strlen(conv))*weight;
    return L;
}

// Função auxiliar para o qsort
int compare_str(const void *a, const void *b){
    const char *str1 = *(const char**)a;
    const char *str2 = *(const char**)b;
    return strcmp(str1, str2);
}

int main(){
    FILE* file;
    char* filename;
    char* P1;
    char* P2;
    char* P3;
    char* W;
    char* line;

    char* shortest_wrd;
    char* longest_wrd;
    int P1_count=0;
    int palindrome_count=0;
    char* P2_longest = calloc(1, sizeof(char));
    char** P3_wordlist = calloc(1, sizeof(char*));
    int P3_count=0;
    char* W_closest = calloc(1, sizeof(char));

    filename = readline(stdin);
    file = fopen(filename, "r");
    if (file == NULL){
        printf("Selecione um arquivo!\n");
        exit(1);
    } 

    //Obtendo expressões regulares
    P1 = readline(stdin);
    P2 = readline(stdin);
    P3 = readline(stdin);
    W = readline(stdin);

    // Obtendo palavras do arquivo
    line = readline(file);
    longest_wrd = line;
    shortest_wrd = line;
    W_closest = line;
    int N=0;
    for (N =0; line[0] != '\0'; N++){
        // Checando se palavra é nova mais curta
        shortest_wrd = strlen(line) < strlen(shortest_wrd) ? line : shortest_wrd;
        // Checando se palavra é nova mais longa
        longest_wrd = strlen(line) > strlen(longest_wrd) ? line : longest_wrd;
       
        // Checando padrão P1
        if (checkPattern(line, P1)){
            P1_count++;
        }
        // Checando se é palíndromo
        if (checkPalindrome(line)){
            palindrome_count++;
        }
        // Checando prefixo P2
        if (checkPattern(line, P2)){
            // Checando se palabra é nova mais longa com prefixo P2
            P2_longest = strlen(line) > strlen(P2_longest) ? line : P2_longest;
        }
        if (checkPattern(line, P3)){
            P3_wordlist = realloc(P3_wordlist, P3_count*sizeof(char*) + sizeof(char*));
            P3_wordlist[P3_count] = line;
            P3_count++;
        }
        // Checando distancia da palavra com W
        W_closest = checkSim(W, line) > checkSim(W, W_closest) ? line : W_closest;
        
        //printf("%s\n", line);
        line = readline(file);
    }
    // Ordenando lista de palavras com padrão P3 em ordem alfabética
    qsort(P3_wordlist, P3_count, sizeof(char*), compare_str);
    
    
    // Imprimindo resultados
    printf("%d\n", N);
    printf("%s\n", shortest_wrd);
    printf("%s\n", longest_wrd);
    printf("%d\n", P1_count);
    printf("%d\n", palindrome_count);
    printf("%s\n", P2_longest);
    for (int i=0; i<P3_count; i++){
        printf("%s\n", P3_wordlist[i]);
    }
    printf("%s\n", W_closest);
    // =============
    


    fclose(file); 
    // Liberando memória
    free(filename);
    free(P1);
    free(P2);
    free(P3);
    free(W);
    for(int i=0; i<P3_count; i++){
        free(P3_wordlist[i]);
    }
    free(P3_wordlist);
    free(line);
    free(P2_longest);
    return 0;
}
