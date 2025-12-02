#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.



    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

// ---------------------------------------------
// ESTRUTURA DA ÁRVORE BINÁRIA
// ---------------------------------------------

typedef struct Sala {
    char nome[50];
    struct Sala* esq;
    struct Sala* dir;
} Sala;

// Função para criar uma sala da mansão
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

// Explorar a mansão
void explorarSalas(Sala* atual) {
    char opc;

    while (atual != NULL) {
        printf("\nVocê está em: %s\n", atual->nome);
        printf("Escolha um caminho:\n");
        printf("  (e) Esquerda\n");
        printf("  (d) Direita\n");
        printf("  (s) Sair da exploração\n");
        printf("→ ");
        scanf(" %c", &opc);

        if (opc == 'e') {
            atual = atual->esq;
        } else if (opc == 'd') {
            atual = atual->dir;
        } else if (opc == 's') {
            printf("\nSaindo da exploração...\n");
            return;
        } else {
            printf("\nOpção inválida!\n");
        }
    }

    printf("\nVocê chegou ao fim do caminho! (nó-folha)\n");
}

int main() {
    // Criação estática da árvore
    Sala* hall = criarSala("Hall de Entrada");
    hall->esq = criarSala("Sala de Estar");
    hall->dir = criarSala("Biblioteca");

    hall->esq->esq = criarSala("Cozinha");
    hall->esq->dir = criarSala("Sala de Música");

    hall->dir->esq = criarSala("Escritório");
    hall->dir->dir = criarSala("Jardim Interno");

    // Inicia o jogo
    explorarSalas(hall);

    return 0;
}