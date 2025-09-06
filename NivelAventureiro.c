#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5      // Tamanho da fila de peças futuras
#define MAX_PILHA 3     // Tamanho máximo da pilha de reserva

// Struct que representa uma peça
typedef struct {
    char tipo; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único da peça
} Peca;

// Fila circular de peças futuras
typedef struct {
    Peca fila[MAX_FILA];
    int frente;   // Índice da frente da fila
    int tras;     // Índice do final da fila
    int tamanho;  // Quantidade de peças na fila
} Fila;

// Pilha de peças reservadas
typedef struct {
    Peca pilha[MAX_PILHA];
    int topo; // Índice do topo da pilha
} Pilha;

// Função que gera uma nova peça aleatória
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.tipo = tipos[rand() % 4]; // Escolhe tipo aleatoriamente
    nova.id = id;                  // Atribui id único
    return nova;
}

// Inicializa a fila com peças geradas automaticamente
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->tamanho = 0;
    for (int i = 0; i < MAX_FILA; i++) {
        f->fila[f->tras] = gerarPeca(i);
        f->tras = (f->tras + 1) % MAX_FILA;
        f->tamanho++;
    }
}

// Inicializa a pilha de reserva
void inicializarPilha(Pilha *p) {
    p->topo = -1; // Pilha vazia
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    printf("Fila de peças futuras:\n");
    if (f->tamanho == 0) {
        printf("  Fila vazia!\n");
        return;
    }
    int count = f->tamanho;
    int index = f->frente;
    while (count > 0) {
        printf("[%c %d] ", f->fila[index].tipo, f->fila[index].id);
        index = (index + 1) % MAX_FILA;
        count--;
    }
    printf("\n");
}

// Exibe o estado atual da pilha
void exibirPilha(Pilha *p) {
    printf("Pilha de reserva (Topo -> Base):\n");
    if (p->topo == -1) {
        printf("  Pilha vazia!\n");
        return;
    }
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->pilha[i].tipo, p->pilha[i].id);
    }
    printf("\n");
}

// Remove peça da frente da fila (jogar peça)
Peca jogarPeca(Fila *f) {
    Peca removida = f->fila[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    return removida;
}

// Adiciona nova peça ao final da fila
void adicionarFila(Fila *f, int id) {
    if (f->tamanho == MAX_FILA) return; // Proteção
    f->fila[f->tras] = gerarPeca(id);
    f->tras = (f->tras + 1) % MAX_FILA;
    f->tamanho++;
}

// Move peça da frente da fila para o topo da pilha (reservar)
void reservarPeca(Fila *f, Pilha *p, int proximoId) {
    if (p->topo >= MAX_PILHA - 1) {
        printf("Pilha cheia! Não é possível reservar peça.\n");
        return;
    }
    Peca aReservar = jogarPeca(f);
    p->topo++;
    p->pilha[p->topo] = aReservar;
    printf("Peça reservada: [%c %d]\n", aReservar.tipo, aReservar.id);
    adicionarFila(f, proximoId);
}

// Usa a peça do topo da pilha
void usarPecaReservada(Pilha *p) {
    if (p->topo == -1) {
        printf("Pilha vazia! Nenhuma peça reservada para usar.\n");
        return;
    }
    Peca usada = p->pilha[p->topo];
    p->topo--;
    printf("Peça usada da reserva: [%c %d]\n", usada.tipo, usada.id);
}

int main() {
    srand(time(NULL)); // Inicializa gerador aleatório

    Fila fila;
    Pilha pilha;
    int proximoId = 0;

    // Inicialização das estruturas
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    proximoId = MAX_FILA; // Próximo id para peças novas

    int opcao;

    do {
        printf("\n=== Estado atual do jogo ===\n");
        exibirFila(&fila);
        exibirPilha(&pilha);

        // Menu de opções
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                Peca jogada = jogarPeca(&fila);
                printf("Peça jogada: [%c %d]\n", jogada.tipo, jogada.id);
                adicionarFila(&fila, proximoId);
                proximoId++;
                break;
            }
            case 2:
                reservarPeca(&fila, &pilha, proximoId);
                proximoId++;
                break;
            case 3:
                usarPecaReservada(&pilha);
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
