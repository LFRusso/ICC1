#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    int *matrix;
    int det;
    
    scanf("%d %d", &n, &m);
    
    // Alocando memória do tamanho necessário
    matrix = (int*) malloc(m*n*sizeof(int));
    
    if(n != m){
        printf("A matriz de entrada nao possui determinante!\n");
    } else if( (m > 3) | (n > 3) | (m <= 0) ) { 
        printf("Entradas invalidas!");
    } else {
        switch(m){
            case(1):
                scanf("%d\n", &matrix[0]);
                det = matrix[0];

                break;

            case(2):
                // Lendo matriz de entrada
                for(int i=0; i<m; i++){
                    for(int j=0; j<n; j++){
                        scanf("%d", &matrix[i*m+j]);
                    }
                }
                
                det = matrix[0*m + 0]*matrix[ 1*m + 1 ] - matrix[ 0*m + 1 ]*matrix[ 1*m + 0  ];
                break;

            case(3):
                // Lendo matriz de entrada
                for(int i=0; i<m; i++){
                    for(int j=0; j<n; j++){
                        scanf("%d", &matrix[i*m+j]);
                    }
                }

                // Somando partes positivas do determinante
                det = matrix[ 0*m + 0 ]*matrix[ 1*m + 1 ]*matrix[ 2*m + 2 ];
                det += matrix[ 0*m + 1 ]*matrix[ 1*m + 2 ]*matrix[ 2*m + 0 ];
                det += matrix[ 0*m + 2 ]*matrix[ 1*m + 0 ]*matrix[ 2*m + 1 ];
                
                // Subtraindo partes negativas do determinante
                det -= matrix[ 0*m + 2 ]*matrix[ 1*m + 1 ]*matrix[ 2*m + 0 ];
                det -= matrix[ 0*m + 1 ]*matrix[ 1*m + 0 ]*matrix[ 2*m + 2 ];
                det -= matrix[ 0*m + 0 ]*matrix[ 1*m + 2 ]*matrix[ 2*m + 1 ];
                break;
        }
    
        printf("O determinante da matriz de entrada equivale a %d e tem ordem %d\n", det, m);
    }
    
    return 0;
}
