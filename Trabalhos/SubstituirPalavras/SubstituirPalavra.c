#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 2

// Lê um texto de entrada pelo stdin e retorna o texto com as palavras alteradas de acordo com word1 e word2
char* replaceInputWords(char* word1, char* word2){
    char *new_text = (char*)calloc(1, sizeof(char));       // texto com as palavras trocadas
    char *wordfinder = (char*)calloc(1, sizeof(char));     // Separador de palavras do texto  
    char buffer[BUFFERSIZE]; 
    
    // Incremento o texto de caractere por vez até encontrar uma quebra de linha (condição de parada)
    // OBS: achei que essa parte ficaria melhor fazendo while(*buffer != '\n' && fgets(buffer, BUFFERSIZE, stdin)), já
    // que isso permitiria eu tirar aquela parte que adiciona a "sobra" do wordfinder no final. Mas por algum motivo
    // embora isso funcione na minha máquina e em qualquer compilador online, dava problema no caso 1 do run.codes
    while( fgets(buffer, BUFFERSIZE, stdin) && *buffer != '\n'){ 

        // Condição para determinar o fim de uma palavra: chegou em algum caractere fora do alfabeto upper
        // ou lower case (determinado pelos intervalos na tabela ASCII) 
        if( !((*buffer>=64 && *buffer<=90) || (*buffer>=97 && *buffer<=122)) )
        {
            // Checa se a palavra é a que desejamos substituir    
            if(strcmp(wordfinder,word1)==0){
                // Caso seja, no lugar dela colocamos a substituta no texto (+1 no final por conta do \0)
                new_text = (char*)realloc(new_text, strlen(new_text) + strlen(word2) + 1);
                new_text = strcat(new_text, word2);
            } else {
                // Caso não seja, adicionamos a palavra do texto original (armazenada em wordfinder)
                new_text = (char*)realloc(new_text, strlen(new_text) + strlen(wordfinder) + 1);
                new_text = strcat(new_text,wordfinder);
            }

            // Reseto o wordfinder para voltar a armazenar os caracteres do início
            memset(wordfinder, 0, strlen(wordfinder));

            // Acrescento o que ficou no buffer e não entrou no wordfinder (caracteres especiais, pontuação...)
            new_text = (char*)realloc(new_text, strlen(new_text) + strlen(buffer) + 1);
            new_text = strcat(new_text, buffer);
        }
        else 
        {
            // Caso ainda não tenha atingido o fim de uma palavra, acrescento o caractere do Buffer ao wordfinder
            wordfinder = (char*)realloc(wordfinder, strlen(wordfinder) + strlen(buffer) + 1);
            wordfinder = strcat(wordfinder, buffer);
        }
    }

    // Acrescenta o que "sobrou" no wordfinder
    if(strcmp(wordfinder,word1)==0){
        // Caso seja, no lugar dela colocamos a substituta no texto (+1 no final por conta do \0)
        new_text = (char*)realloc(new_text, strlen(new_text) + strlen(word2) + 1);
        new_text = strcat(new_text, word2);
    } else {
        // Caso não seja, adicionamos a palavra do texto original (armazenada em wordfinder)
        new_text = (char*)realloc(new_text, strlen(new_text) + strlen(wordfinder) + 1);
        new_text = strcat(new_text,wordfinder);
    }


    free(wordfinder);
    return new_text;
}

int main() {
    char *word1 = (char*)calloc(1,sizeof(char));    // palavra a ser substituida
    char *word2 = (char*)calloc(1, sizeof(char));    // nova palavra
    char *text_replaced;

    scanf("%s ", word1);
    scanf("%s ", word2);
    word1 = (char*)realloc(word1, strlen(word1) + 1);
    word2 = (char*)realloc(word2, strlen(word2) + 1);
    
    text_replaced = replaceInputWords(word1, word2);
    printf("%s", text_replaced);
    
    free(text_replaced);
    free(word1);
    free(word2);
    return 0;
}
