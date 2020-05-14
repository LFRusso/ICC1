#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Usuario{
    struct Livro** livros;
    int no_livros;
};

struct Livro{
    char *nome;
    int prazo;
    int alugado;
};

// Leitura de linha do arquivo
char* readLine(FILE *input){
    char *str = (char*) malloc(sizeof(char));
    char ch;

    ch = getc(input);
    while(ch != '\n' && ch != EOF){
        // Condição feita por conta do carriage return em algumas linhas dos arquivos de entrada
        if(ch != 13){
            str = realloc(str, strlen(str)*sizeof(char)+sizeof(char)+1);
            strncat(str, &ch, 1);
        }
        ch = getc(input); 
    }
    // Finalizando string
    strncat(str, "\0", 1);
    
    return str;
}

// Cadastra n livros e retorna um ponteiro para onde estão armazenados
struct Livro* cadastrarLivros(int n){
    struct Livro *livros;
    livros = (struct Livro*) malloc(sizeof(struct Livro)*n);
    
    // Cadastro dos livros
    for(int i =0; i<n; i++){
        
        // Cadastra nome do livro
        (livros + i)->nome = readLine(stdin);

        // Cadastra prazo de devolução (quantos dias pode ser alugado)
        scanf("%d ", &(livros + i)->prazo);

        // Livro é cadastrado como disponível
        (livros + i)->alugado = 0;
    }

    return livros;
}


// Operação 1: aluguel de livro
void alugaLivro(struct Livro *livros,struct Usuario *usuario, int n){
    char* nome;

    printf("Digite o livro que voce procura:\n");
    nome = readLine(stdin);
    
    for(int i=0; i<n; i++){
        if(strcmp((livros+i)->nome, nome) == 0){
            if( usuario->no_livros >= 10){
                printf("Voce ja tem 10 livros alugados\n");
                return;
            } else {
                if((livros+i)->alugado) {
                    printf("Livro ja alugado\n");
                    return;
                } else {
                    (livros+i)->alugado = 1;
                    usuario->no_livros++;
                    usuario->livros = realloc(usuario->livros, sizeof(struct Livro*)*(usuario->no_livros) + sizeof(struct Livro*));
                    (usuario->livros)[usuario->no_livros - 1] = (livros+i);
                    printf("%s alugado com sucesso\n", (livros+i)->nome);
                    return;
                }
            }
        }
    }
   
    // Caso a função ainda não tenha retornado, significa que o livro não está na biblioteca
    printf("Livro nao encontrado na biblioteca\n");
    return;
}

// Operação 2: mostra livros alugados
void mostrarLivros(struct Usuario *usuario){
    if(usuario->no_livros == 0){
        printf("Voce nao tem livros alugados\n");
        return;
    } else {
        printf("Voce tem %d livro(s) alugado(s)\n", usuario->no_livros);
        for(int i=0; i<usuario->no_livros; i++){
            printf("Livro nome: %s\n", (usuario->livros)[i]->nome);
            printf("Devolve-lo daqui %d dias\n", (usuario->livros)[i]->prazo);
        }
    }
    return;
}

// Operação 3: devolver livro
void devolveLivro(struct Usuario *usuario){
    char* str;
    printf("Digite o livro que deseja devolver:\n");
    str = readLine(stdin);

    for (int i=0; i<usuario->no_livros; i++){
        if(strcmp((usuario->livros)[i]->nome, str) == 0){
            (usuario->livros)[i]->alugado = 0;
            
            printf("Livro %s foi devolvido com sucesso\n", (usuario->livros)[i]->nome );
          
            // Removendo livro ao sobrescrever a memória dele com os próximos 
            memmove((usuario->livros)+i, (usuario->livros)+i+1, sizeof(struct Livro*)*(usuario->no_livros - i));
            usuario->no_livros--;
            usuario->livros = realloc(usuario->livros, sizeof(struct Livro*)*(usuario->no_livros));
            
            return;
        }
    }
    printf("Voce nao possui esse livro\n");
    return;
}

// Operação 4: só fiz ela como função para ficar igual as outras (e para caso mais alguma coisa precisasse ser feita na finalização, em um programa real)
void finaliza(){
    printf("Programa finalizado\n");
    return;
}

int main(){
    int rodando=1;
    char opcao;
    int n;
    struct Livro *livros;
    struct Usuario usuario;
    usuario.no_livros = 0;
    usuario.livros = (struct Livro**) malloc(sizeof(struct Livro));

    //Cadastra os n livros
    scanf("%d ", &n);
    livros = cadastrarLivros(n);
  

    while(rodando){
        
        opcao = readLine(stdin)[0];
        switch(opcao){
            case '1':
                alugaLivro(livros, &usuario, n);
                break;
            
            case '2':

                mostrarLivros(&usuario);
                break;

            case '3':
                devolveLivro(&usuario);
                break;

            case '4':
                finaliza();
                rodando=0;
                break;
        }
    }   

    free(livros);
    free(usuario.livros);
    livros = NULL;
    usuario.livros = NULL;
    return 0;
}
