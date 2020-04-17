#include <stdio.h>
#include <string.h>
#include <math.h>

int main()  {
    int sum, bit;
    char binary[] = "000000000000000000000000000000"; 
    
    scanf("%s", binary);

    /*
     Usando a o fato de que para converter um binário
     _________________
     |b_k|...|b_1|b_0|
     |___|___|___|___|

        em que cada b_i é um bit 
     para a base decimal usamos 

     n = \sum_{i=0}^{k} b_i 2^i
     */

    sum = 0;
    for (int i=0; i<strlen(binary); i++){
        //Convertendo char para int  
        bit = binary[strlen(binary)-(i+1)] - '0';
        
        sum += bit*pow(2,i);
    } 

    printf("%d\n", sum);
    
    return 0;
}
