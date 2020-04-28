#include <stdio.h>
#include <stdlib.h>

void gameLoop(char *game_table);
void buildGame(char *game_table);
void draw(char *game_table);
int checkState(char *game_table, char player);
void handleInput(char *game_table, char player);


int main(){
    char *game_table;
    game_table = (char*)malloc(9*sizeof(char));
    buildGame(game_table);
    gameLoop(game_table);
    return 0;
}

// Construo o estado inicial do tabuleiro
void buildGame(char *game_table){
    for(int i=0; i<=8; i++){
        *(game_table + i) = (i+1)+'0';
    }
    return;
}

// Loop principal do jogo
void gameLoop(char *game_table){
    int playing = 1;
    char *players = "XO"; // Armazenei os jogadores assim para evitar muita repetição e estruturas condicionais
    
    draw(game_table);
    printf("Jogo da velha!\n");

    for(int i=0; playing; i++){

        printf("Escolha um número para jogar, jogador %c!\n", players[i%2]);  
        handleInput(game_table, players[i%2]); 

        draw(game_table);

        playing = checkState(game_table, players[i%2]); 
        
        // Caso tenha acabado a nona jogada e não haja vencedor, deu velha
        if(i == 8 && playing){
            playing = 0;
            printf("Deu velha!\n");
        }
    }
    return;
}


// Desenha o tabuleiro na tela
void draw(char *game_table){
    printf("%c   |%c   |%c   |\n", game_table[0], game_table[1], game_table[2]);
    printf("----+----+-----\n");
    printf("%c   |%c   |%c   |\n", game_table[3], game_table[4], game_table[5]);
    printf("----+----+-----\n");
    printf("%c   |%c   |%c   |\n", game_table[6], game_table[7], game_table[8]);
    printf("----+----+-----\n");
    return;
}


// Recebe input do jogador e atualiza a tabela baseada nele
void handleInput(char *game_table, char player){
    int done = 0;       // Determina se a jogada já foi computada
    int tile;

    scanf("%d", &tile);
    while(!done){
        if(game_table[tile-1] == 'X' || game_table[tile-1] == 'O' || tile < 1 || tile > 9){
            printf("Jogada inválida! Escolha outra casa.\n");
            scanf("%d", &tile);
        } else {
            game_table[tile-1] = player;
            done = 1;
        }
    }
    return;
}


// Checa se o jogador ganhou e diz se o jogo continua ou não baseado nisso
int checkState(char *game_table, char player){
    int checks_h;  // Caso o jogador receba 3 checks (3 casas preenchidas em dada configuração) ele vence
    int checks_v;        // Faço os checks na horiziontal e vertial (h e v)
  
  // Checando na horizontal e vertical
  for(int i=0; i<3; i++){
      checks_h=0;
      checks_v=0;
      for(int j=0; j<3; j++){
        checks_h = game_table[3*i + j]==player ? checks_h+1 : checks_h;
        checks_v = game_table[i + 3*j]==player ? checks_v+1 : checks_v;
      }
      if(checks_h == 3 || checks_v == 3){
          printf("Fim do jogo! O jogador %c venceu!\n", player);
          return 0;  
      }
  }

  // Checando diagonal principal
  if( (game_table[0] == game_table[4]) && (game_table[4] == game_table[8]) ){
          printf("Fim do jogo! O jogador %c venceu!\n", player);
          return 0;  
  }

  // Checando diagonal secundária
  if( (game_table[2] == game_table[4]) && (game_table[4] == game_table[6]) ){
          printf("Fim do jogo! O jogador %c venceu!\n", player);
          return 0;  
  }

  // Caso não tenha retornado nada até aqui, o jogo continua
  return 1;
}
