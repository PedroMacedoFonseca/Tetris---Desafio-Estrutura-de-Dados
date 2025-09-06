#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5    // Capacidade da fila circular
#define MAX_PILHA 3   // Capacidade da pilha de reserva

// Estrutura que representa uma peça
typedef struct {
    char tipo; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único da peça
} Peca;

// Fila circular de peças futuras
typedef struct {
    Peca fila[MAX_FILA];
    int frente;   // Índice da frente da fila
    int tras;     // Índice do final da fila
    int tamanho;  // Quantidade de peças atualmente na fila
} Fila;

// Pilha de peças reservadas
typedef struct {
    Peca pilha[MAX_PILHA];
    int topo; // Índice do topo da pilha (-1 se vazia)
} Pilha;

// Função que gera uma nova peça aleatória
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.tipo = tipos[rand() % 4]; // Escolhe tipo aleatório
    nova.id = id;                  // Atribui id único
    return nova;
}

// Inicializa a fila com peças aleatórias
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

// Exibe estado atual da fila
void exibirFila(Fila *f) {
    printf("Fila de peças:\n");
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

// Exibe estado atual da pilha
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
    if (f->tamanho == MAX_FILA) return; // Proteção contra overflow
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
    adicionarFila(f, proximoId); // Mantém a fila cheia
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

// Troca peça da frente da fila com topo da pilha
void trocarFrenteTopo(Fila *f, Pilha *p) {
    if (f->tamanho == 0 || p->topo == -1) {
        printf("Não há peças suficientes para realizar a troca.\n");
        return;
    }
    Peca temp = f->fila[f->frente];
    f->fila[f->frente] = p->pilha[p->topo];
    p->pilha[p->topo] = temp;
    printf("Troca realizada entre peça da frente da fila e topo da pilha.\n");
}

// Troca múltipla (3 primeiros da fila com 3 da pilha)
void trocaMultipla(Fila *f, Pilha *p) {
    if (f->tamanho < 3 || p->topo < 2) {
        printf("Não há peças suficientes para realizar a troca múltipla.\n");
        return;
    }
    for (int i = 0; i < 3; i++) {
        int idxFila = (f->frente + i) % MAX_FILA;
        int idxPilha = p->topo - i;
        Peca temp = f->fila[idxFila];
        f->fila[idxFila] = p->pilha[idxPilha];
        p->pilha[idxPilha] = temp;
    }
    printf("Troca múltipla realizada entre 3 primeiras peças da fila e 3 da pilha.\n");
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa gerador aleatório

    Fila fila;
    Pilha pilha;
    int proximoId = 0;

    // Inicializa estruturas
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    proximoId = MAX_FILA;

    int opcao;

    do {
        printf("\n=== Estado atual do jogo ===\n");
        exibirFila(&fila);
        exibirPilha(&pilha);

        // Menu de opções
        printf("\nOpções disponíveis:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para a pilha de reserva\n");
        printf("3 - Usar peça da pilha de reserva\n");
        printf("4 - Trocar peça da frente da fila com topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com 3 da pilha\n");
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
            case 4:
                trocarFrenteTopo(&fila, &pilha);
                break;
            case 5:
                trocaMultipla(&fila, &pilha);
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
