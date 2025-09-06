#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILAS 5 // Tamanho máximo da fila de peças futuras

// Definição de struct para representar uma peça
typedef struct {
    char tipo; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único da peça
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca fila[MAX_FILAS]; // Array que armazena as peças
    int frente;           // Índice da frente da fila
    int tras;             // Índice do fim da fila
    int tamanho;          // Quantidade de peças atualmente na fila
} Fila;

// Função que gera uma nova peça automaticamente
Peca gerarPeca(int id) {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'}; // Tipos possíveis
    novaPeca.tipo = tipos[rand() % 4];    // Escolhe tipo aleatoriamente
    novaPeca.id = id;                     // Define id único
    return novaPeca;
}

// Inicializa a fila com peças aleatórias
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->tamanho = 0;

    for (int i = 0; i < MAX_FILAS; i++) {
        f->fila[f->tras] = gerarPeca(i);
        f->tras = (f->tras + 1) % MAX_FILAS;
        f->tamanho++;
    }
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    printf("\nFila de peças:\n");
    if (f->tamanho == 0) {
        printf("Fila vazia!\n");
        return;
    }
    int count = f->tamanho;
    int index = f->frente;
    while (count > 0) {
        printf("[%c %d] ", f->fila[index].tipo, f->fila[index].id);
        index = (index + 1) % MAX_FILAS;
        count--;
    }
    printf("\n");
}

// Remove a peça da frente da fila (dequeue)
void jogarPeca(Fila *f) {
    if (f->tamanho == 0) {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca jogada = f->fila[f->frente];
    printf("Peça jogada: [%c %d]\n", jogada.tipo, jogada.id);
    f->frente = (f->frente + 1) % MAX_FILAS;
    f->tamanho--;
}

// Insere nova peça no final da fila (enqueue)
void adicionarPeca(Fila *f, int proximoId) {
    if (f->tamanho == MAX_FILAS) {
        printf("Fila cheia! Não é possível adicionar nova peça.\n");
        return;
    }
    f->fila[f->tras] = gerarPeca(proximoId);
    f->tras = (f->tras + 1) % MAX_FILAS;
    f->tamanho++;
    printf("Nova peça adicionada: [%c %d]\n", f->fila[(f->tras - 1 + MAX_FILAS) % MAX_FILAS].tipo, proximoId);
}

// Função principal com menu de ações
int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios
    Fila fila;
    int proximoId = 0; // Próximo id para gerar nova peça
    inicializarFila(&fila);
    proximoId = MAX_FILAS; // Próximo id após inicialização

    int opcao;

    do {
        exibirFila(&fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                adicionarPeca(&fila, proximoId);
                proximoId++;
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
