#include <stdio.h>
#include <string.h>


char encrypt_letter(char letter, int key, int mode){
    int index=-1;
    int letter_case;
    char alfabeto[2][26] = {
        {"abcdefghijklmnopqrstuvwxyz"},
        {"ABCDEFGHIJKLMNOPQRSTUVWXYV"}};

    // Checando qual o índice da letra recebida
    // e se ela é maiúscul ou minúscula
    for(int i=0; i<2; i++){
        for(int j=0; j<26; j++){
            if(alfabeto[i][j]==letter){
                index = j;
                letter_case = i;
            }
        } 
    }
    // Caso não seja uma letra, a cifra não se aplica e retorna o próprio caractére
    if(index == -1){
        return letter;
    }

    // Checando condições de borda (casos que ultrapassam os limites inferior e superior do vetor) e 'shiftando' a letra
    switch (mode){
        case 1:
            if(index+key >= 26)
                return alfabeto[letter_case][26 - index + key];
            else
                return alfabeto[letter_case][index+key];
            break;

        case 2:
            if(index-key < 0)
                return alfabeto[letter_case][26 + (index - key)];
            else
                return alfabeto[letter_case][index-key];           
            break;

        default:
            break;
    }

    // Retorno fora do condicional para o compilador não reclamar
    return 0;
}

int main(){
    char message[100];
    int mode, key;
    char letter;

    // Garantindo que a sting vai conter os espaços 
    scanf("%d %d %[^\n]%*c", &mode, &key, message);
    
    for(int i=0; i<strlen(message); i++){
        letter = encrypt_letter(message[i], key, mode);
        printf("%c", letter);
    }
    printf("\n");

    return 0;
}
