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


#define TAM_HASH 10  

// ==========================================================
// ====================== NÍVEL MESTRE ======================
// =============== TABELA HASH (PISTA -> SUSPEITO) ==========
// ==========================================================

typedef struct HashNode {
    char pista[50];
    char suspeito[50];
    struct HashNode* prox;
} HashNode;

HashNode* tabela[TAM_HASH];

// Função hash simples
int hashFunction(const char* str) {
    int soma = 0;
    for (int i = 0; str[i] != '\0'; i++)
        soma += str[i];
    return soma % TAM_HASH;
}

void inserirNaHash(const char* pista, const char* suspeito) {
    int indice = hashFunction(pista);

    HashNode* novo = (HashNode*)malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);

    novo->prox = tabela[indice];
    tabela[indice] = novo;
}

void exibirHash() {
    printf("\n===== Tabela de Suspeitos =====\n");

    for (int i = 0; i < TAM_HASH; i++) {
        HashNode* aux = tabela[i];

        while (aux != NULL) {
            printf("Pista: %-20s → Suspeito: %s\n", 
                   aux->pista, aux->suspeito);
            aux = aux->prox;
        }
    }
}

// Verifica o suspeito mais citado
void suspeitoMaisCitado() {
    char nomes[20][50];
    int cont[20] = {0};
    int qtd = 0;

    for (int i = 0; i < TAM_HASH; i++) {
        HashNode* aux = tabela[i];

        while (aux != NULL) {

            // Se já existe no array de contagem
            int existe = -1;
            for (int j = 0; j < qtd; j++) {
                if (strcmp(nomes[j], aux->suspeito) == 0) {
                    existe = j;
                    break;
                }
            }

            if (existe == -1) {
                strcpy(nomes[qtd], aux->suspeito);
                cont[qtd]++;
                qtd++;
            } else {
                cont[existe]++;
            }

            aux = aux->prox;
        }
    }

    // Acha o maior
    int maior = 0;
    for (int i = 1; i < qtd; i++)
        if (cont[i] > cont[maior])
            maior = i;

    printf("\nSuspeito mais associado às pistas: **%s**\n", nomes[maior]);
}

// ==========================================================
// ==================== NÍVEL NOVATO ========================
// ================ ÁRVORE BINÁRIA DE SALAS =================
// ==========================================================

typedef struct Sala {
    char nome[50];
    struct Sala* esq;
    struct Sala* dir;

    // Nível Aventureiro / Mestre
    char pista[50]; // pista encontrada nesta sala (se houver)
    char suspeito[50];
} Sala;

// Função para criar uma sala da mansão
Sala* criarSala(const char* nome, const char* pista, const char* suspeito) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
   
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista ? pista : "");
    strcpy(nova->suspeito, suspeito ? suspeito : "");

    nova->esq = NULL;
    nova->dir = NULL;

    return nova;
}

// ==========================================================
// ================== NÍVEL AVENTUREIRO =====================
// =============== ÁRVORE DE BUSCA (PISTAS) =================
// ==========================================================
typedef struct NodeBST {
    char pista[50];
    struct NodeBST* esq;
    struct NodeBST* dir;
} NodeBST;

// Inserção na BST
NodeBST* inserirBST(NodeBST* raiz, const char* pista) {
    if (raiz == NULL) {
        NodeBST* novo = (NodeBST*)malloc(sizeof(NodeBST));
        strcpy(novo->pista, pista);

        novo->esq = NULL;
        novo->dir = NULL;

        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserirBST(raiz->esq, pista);
    else
        raiz->dir = inserirBST(raiz->dir, pista);

    return raiz;
}

// Listagem em ordem
void emOrdem(NodeBST* raiz) {
    if (raiz == NULL) return;

    emOrdem(raiz->esq);
    printf("• %s\n", raiz->pista);
    emOrdem(raiz->dir);
}

// ==========================================================
// ========== EXPLORAÇÃO DAS SALAS (TODOS OS NÍVEIS) ========
// ==========================================================

void explorarSalas(Sala* atual, NodeBST** arvorePistas) {
    char opc;

    while (atual != NULL) {
       
        printf("\n===========================\n");
        printf("Você está em: %s\n", atual->nome);
        printf("===========================\n");

        // Coleta de pista
        if (strlen(atual->pista) > 0) {
            printf("Você encontrou uma pista: %s\n", atual->pista);
            printf("Suspeito associado: %s\n", atual->suspeito);

            *arvorePistas = inserirBST(*arvorePistas, atual->pista);
            inserirNaHash(atual->pista, atual->suspeito);
        }

        
        printf("Escolha uma opção:\n");
        printf("e - Ir para a esquerda\n");
        printf("d - Ir para a direita\n");
        printf("p - Listar pistas (em ordem)\n");
        printf("h - Ver tabela hash (pista → suspeito)\n");
        printf("m - Ver suspeito mais citado\n");
        printf("s - Sair da exploração\n");
        printf("→ ");

        scanf(" %c", &opc);

        switch (opc) {
            case 'e': atual = atual->esq; break;
            case 'd': atual = atual->dir; break;
            case 'p': 
                printf("\n===== Pistas Encontradas =====\n");
                emOrdem(*arvorePistas);
                break;
            case 'h': exibirHash(); break;
            case 'm': suspeitoMaisCitado(); break;
            case 's': return;
            default: printf("\nOpção inválida!\n");
        }
    }
}

// ==========================================================
// =========================== MAIN =========================
// ==========================================================
       
int main() {
    NodeBST* arvorePistas = NULL;

    Sala* hall = criarSala("Hall de Entrada", "", "");
    hall->esq = criarSala("Sala de Estar", "Pegada de sapato", "Jardineiro");
    hall->dir = criarSala("Biblioteca", "", "");

    hall->esq->esq = criarSala("Cozinha", "Copo Quebrado", "Cozinheira");
    hall->esq->dir = criarSala("Sala de Música", "", "");

    hall->dir->esq = criarSala("Escritório", "Papel Rasgado", "Secretário");
    hall->dir->dir = criarSala("Jardim Interno", "Perfume Forte", "Socialite");

    explorarSalas(hall, &arvorePistas);

    return 0;
}