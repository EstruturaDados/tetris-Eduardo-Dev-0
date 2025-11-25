#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <string.h>



#define TAM_FILA 5   // Tamanho máximo da fila de peças


typedef struct {

    char nome; // Tipo da peça: I, O, T, L, J, S, Z

    int id;    // Identificador único da peça

} Peca;


typedef struct {

    Peca fila[TAM_FILA]; // Vetor de peças

    int inicio;          // Índice do primeiro elemento da fila

    int fim;             // Índice do próximo espaço livre

    int tamanho;         // Quantidade de peças na fila

    int contadorID;      // Contador para gerar IDs únicos

} Fila;

char tiposPecas[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};

Peca gerarPeca(int* contadorID) {

    Peca nova;

    nova.nome = tiposPecas[rand() % 7]; // Escolhe aleatoriamente entre I, O, T, L, J, S, Z

    nova.id = (*contadorID)++;          // Incrementa o ID da peça

    return nova;

}

void inicializarFila(Fila* f) {

    f->inicio = 0;

    f->fim = 0;

    f->tamanho = 0;

    f->contadorID = 1;



    for(int i=0; i<TAM_FILA; i++){

        f->fila[i] = gerarPeca(&(f->contadorID));

        f->fim = (f->fim + 1) % TAM_FILA; // Avança circularmente

        f->tamanho++;

    }

}

void mostrarFila(Fila* f){

    printf("Fila: ");

    int i = f->inicio;

    for(int c=0; c<f->tamanho; c++){

        printf("[%c%d] ", f->fila[i].nome, f->fila[i].id);

        i = (i + 1) % TAM_FILA; // Move circularmente pelo vetor

    }

    printf("\n");

}

Peca jogarPeca(Fila* f){

    if(f->tamanho==0){

        printf("Fila vazia!\n");

        return (Peca){'-',0};

    }

    Peca p = f->fila[f->inicio];          // Pega a peça da frente

    f->inicio = (f->inicio+1)%TAM_FILA;   // Avança início circularmente

    f->tamanho--;                         // Remove da contagem da fila



    // Inserir nova peça automaticamente no fim

    f->fila[f->fim] = gerarPeca(&(f->contadorID));

    f->fim = (f->fim+1)%TAM_FILA;         // Avança fim circularmente

    f->tamanho++;



    return p;

}

int main() {
     Fila fila;

    inicializarFila(&fila);



    int opcao;

    do{

        printf("\n=== TETRIS STACK - NÍVEL NOVATO ===\n");

        mostrarFila(&fila);

        printf("1. Jogar Peça\n");

        printf("0. Sair...\n");

        scanf("%d",&opcao);

        getchar();



        switch(opcao){

            case 1:

                {

                    Peca p = jogarPeca(&fila);

                    printf("Você Jogou [%c%d]\n",p.nome,p.id);

                }

                break;

            case 0:

                printf("Saindo...\n");

                break;

            default:

                printf("Opção inválida!\n");

        }



    }while(opcao!=0);
}