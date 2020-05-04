#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void estruturaJogo(char** matriz){
	system("cls");
	printf("  %c  |%c   |%c   |\n ",matriz[0][0],matriz[0][1],matriz[0][2]);
	printf("----+----+-----\n");
	printf("  %c  |%c   |%c   |\n ",matriz[1][0],matriz[1][1],matriz[1][2]);
	printf("----+----+-----\n");
	printf("  %c  |%c   |%c   |\n ",matriz[2][0],matriz[2][1],matriz[2][2]);
	printf("----+----+-----\n");
	printf("\nJogo da Velha!\n");
}
char** criarTabuleiro(){
	char** tabuleiro = (char**) malloc(9*sizeof(char));

	int k = 0;
	for (int i = 0; i < 3; ++i) {
		tabuleiro[i]= (char*) malloc(9*sizeof(char));

		for (int j = 0; j < 3; ++j) {
			tabuleiro[i][j] = '1' + k;
			k++;
		}
	}
	return tabuleiro;
}
void funcionaJogo(char** matriz){
	int contadorJogadas = 0;
	int casa;
    //====================
    // Transformei simbolo em um char (vai ser X ou O). Antes ele tava fazendo a mesma coisa que o contador
    char simbolo;
	//====================

	//====================
    int jogadavalida; 
	//====================


	do{
	//====================
        // Checo qual o símbolo
        if(contadorJogadas%2 == 0){									//simbolo como número par = 'X'
            simbolo = 'X';
        }else{
            simbolo = 'O';
        }
	//====================
		
        estruturaJogo(matriz);
        
	//====================
        // Ja coloco o simbolo aqui
		printf("Escolha um número para jogar, jogador %c!\n", simbolo);
	
        // Começo assumindo que a jogada não foi válida
        jogadavalida = 0;
    //====================
        do{       
            scanf("%d",&casa);
            if(casa < 1 || casa > 9){                                                                  //para numeros invalidos
                printf("Jogada inválida! Escolha outra casa.\n");		
        //====================
            // Antes tava *matriz[casa - 1] != ' ' na condição pra ver se é ocupada, por isso tava dando td invalido (tem os numeros dentro)
            // Também tinha o problema que matriz é 2d mas vc tava acessando como se fosse 1d
            } else if(matriz[(casa-1)/3][(casa-1)%3]  == 'X' || matriz[(casa-1)/3][(casa-1)%3] == 'O'){                                  //casas ocupadas
        //====================
                printf("Jogada inválida! Escolha outra casa.\n");		
            } else {	
                // OBS: Antes tava "*matriz[casa - 1] == 'O';", mas "==" é só para comparação
                matriz[(casa-1)/3][(casa-1)%3]  = simbolo;
                jogadavalida=1;
            }
    	}while(!jogadavalida); 
	
        // Mudei o contador de jogadas pra ca pq já garanti que ele vai ser incrementado caso a entrada tenha sido validada
        contadorJogadas++;								
	}while(contadorJogadas <= 9);
}

int main(int argc, char *argv[]) {
	
	char** matriz = criarTabuleiro();
	
	setlocale(LC_ALL, "Portuguese");
	
	estruturaJogo(matriz);
	funcionaJogo(matriz);
	
	return 0;
}
