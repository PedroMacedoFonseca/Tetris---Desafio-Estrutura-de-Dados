# Projeto de Estruturas de Dados: Fila e Pilha em C

Este repositório contém um projeto acadêmico desenvolvido para a disciplina de Estrutura de Dados, demonstrando a implementação e o uso de filas e pilhas em C. A aplicação simula um sistema de gerenciamento de peças de um jogo, como o Tetris, com complexidade crescente em três níveis.

## Visão Geral do Projeto

O objetivo é aplicar os conceitos de **Fila (Queue)** e **Pilha (Stack)** de forma prática e interativa. Cada nível introduz novas funcionalidades e interações entre as estruturas de dados, representando uma evolução no domínio do conteúdo.

-   **Nível Novato:** Foco exclusivo na implementação de uma **fila circular** para gerenciar a sequência de peças futuras.
-   **Nível Aventureiro:** Introdução de uma **pilha** como um "espaço de reserva", permitindo ao jogador guardar uma peça para uso posterior.
-   **Nível Mestre:** Expansão das interações, com operações avançadas de troca de peças entre a fila e a pilha.

---

## Níveis de Dificuldade

### 🎒 Nível Novato (`NivelNovato.c`)

O ponto de partida da jornada. Este nível implementa um sistema básico de gerenciamento de peças usando uma **fila circular**. A peça na frente da fila é a próxima a ser jogada.

**Estrutura Utilizada:**
* **Fila (Queue):** Implementada com um array e controle de índices (`frente`, `tras`) para simular o comportamento circular. Segue o princípio **FIFO** (First-In, First-Out).

**Funcionalidades:**
* `inicializarFila`: Preenche a fila com 5 peças geradas aleatoriamente.
* `jogarPeca` (Dequeue): Remove a peça da frente da fila.
* `adicionarPeca` (Enqueue): Adiciona uma nova peça gerada ao final da fila.
* `exibirFila`: Mostra o estado atual de todas as peças na fila.

### 🗺️ Nível Aventureiro (`NivelAventureiro.c`)

Neste nível, o jogador ganha uma nova habilidade estratégica: uma área de reserva. O código introduz uma **pilha** para armazenar temporariamente uma peça.

**Estruturas Utilizadas:**
* **Fila (Queue):** Gerencia as peças futuras.
* **Pilha (Stack):** Funciona como um "hold" ou reserva, seguindo o princípio **LIFO** (Last-In, First-Out).

**Funcionalidades Adicionais:**
* `reservarPeca`: Move a peça da frente da fila para o topo da pilha de reserva.
* `usarPecaReservada`: Usa a peça que está no topo da pilha, que se torna a peça ativa.

### 🧙 Nível Mestre (`NivelMestre.c`)

O nível final, que aprofunda a manipulação das estruturas de dados, permitindo interações mais complexas e estratégicas entre a fila de peças e a reserva.

**Estruturas Utilizadas:**
* Fila (Queue) e Pilha (Stack).

**Funcionalidades Avançadas:**
* `trocarFrenteTopo`: Realiza a troca (swap) entre a peça na frente da fila e a peça no topo da pilha.
* `trocaMultipla`: Executa uma troca em bloco das 3 primeiras peças da fila com as 3 peças no topo da pilha.
