#include <stdio.h>
#include <stdlib.h>

int main(){
    char* n = (char*)malloc(sizeof(char));

    for(int i=0; i<26; i++){
        n[i] = 'a';
        printf("%c\n", n[i]);
    
    }

    n = (char*)realloc(n, 1);
    printf("%s\n", n);
    return 0;
}
