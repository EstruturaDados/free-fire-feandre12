#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// ---------------------------
// STRUCTS
// ---------------------------

// Representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ---------------------------
// PROTÓTIPOS – VERSÃO VETOR
// ---------------------------
void inserirItemVetor(Item mochila[], int *contador);
void removerItemVetor(Item mochila[], int *contador);
void listarItensVetor(Item mochila[], int contador);
int buscarSequencialVetor(Item mochila[], int contador, char nome[], int *comparacoes);
void ordenarVetor(Item mochila[], int contador);
int buscarBinariaVetor(Item mochila[], int contador, char nome[], int *comparacoes);

// ---------------------------
// PROTÓTIPOS – VERSÃO LISTA
// ---------------------------
void inserirItemLista(No **inicio);
void removerItemLista(No **inicio);
void listarItensLista(No *inicio);
int buscarSequencialLista(No *inicio, char nome[], int *comparacoes);

// ---------------------------
// FUNÇÃO PRINCIPAL
// ---------------------------
int main() {
    Item mochilaVetor[MAX_ITENS];
    int contadorVetor = 0;
    No *mochilaLista = NULL;
    int opcaoPrincipal, opcaoEstrutura;

    do {
        printf("\n=== SISTEMA DE INVENTÁRIO AVANÇADO ===\n");
        printf("1. Usar mochila (vetor)\n");
        printf("2. Usar mochila (lista encadeada)\n");
        printf("0. Sair\n");
        printf("Escolha o tipo de estrutura: ");
        scanf("%d", &opcaoPrincipal);
        getchar();

        switch (opcaoPrincipal) {
            case 1:
                do {
                    printf("\n--- Mochila com Vetor ---\n");
                    printf("1. Inserir item\n");
                    printf("2. Remover item\n");
                    printf("3. Listar itens\n");
                    printf("4. Ordenar itens por nome\n");
                    printf("5. Buscar item (sequencial)\n");
                    printf("6. Buscar item (binária)\n");
                    printf("0. Voltar ao menu principal\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcaoEstrutura);
                    getchar();

                    if (opcaoEstrutura == 1) inserirItemVetor(mochilaVetor, &contadorVetor);
                    else if (opcaoEstrutura == 2) removerItemVetor(mochilaVetor, &contadorVetor);
                    else if (opcaoEstrutura == 3) listarItensVetor(mochilaVetor, contadorVetor);
                    else if (opcaoEstrutura == 4) ordenarVetor(mochilaVetor, contadorVetor);
                    else if (opcaoEstrutura == 5) {
                        char nome[30];
                        int comparacoes = 0;
                        printf("Nome do item: ");
                        fgets(nome, 30, stdin);
                        nome[strcspn(nome, "\n")] = '\0';
                        int pos = buscarSequencialVetor(mochilaVetor, contadorVetor, nome, &comparacoes);
                        if (pos != -1)
                            printf("Item encontrado (posição %d). Comparações: %d\n", pos, comparacoes);
                        else
                            printf("Item não encontrado. Comparações: %d\n", comparacoes);
                    }
                    else if (opcaoEstrutura == 6) {
                        char nome[30];
                        int comparacoes = 0;
                        printf("Nome do item: ");
                        fgets(nome, 30, stdin);
                        nome[strcspn(nome, "\n")] = '\0';
                        int pos = buscarBinariaVetor(mochilaVetor, contadorVetor, nome, &comparacoes);
                        if (pos != -1)
                            printf("Item encontrado (posição %d). Comparações: %d\n", pos, comparacoes);
                        else
                            printf("Item não encontrado. Comparações: %d\n", comparacoes);
                    }

                } while (opcaoEstrutura != 0);
                break;

            case 2:
                do {
                    printf("\n--- Mochila com Lista Encadeada ---\n");
                    printf("1. Inserir item\n");
                    printf("2. Remover item\n");
                    printf("3. Listar itens\n");
                    printf("4. Buscar item (sequencial)\n");
                    printf("0. Voltar ao menu principal\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcaoEstrutura);
                    getchar();

                    if (opcaoEstrutura == 1) inserirItemLista(&mochilaLista);
                    else if (opcaoEstrutura == 2) removerItemLista(&mochilaLista);
                    else if (opcaoEstrutura == 3) listarItensLista(mochilaLista);
                    else if (opcaoEstrutura == 4) {
                        char nome[30];
                        int comparacoes = 0;
                        printf("Nome do item: ");
                        fgets(nome, 30, stdin);
                        nome[strcspn(nome, "\n")] = '\0';
                        int encontrado = buscarSequencialLista(mochilaLista, nome, &comparacoes);
                        if (encontrado)
                            printf("Item encontrado. Comparações: %d\n", comparacoes);
                        else
                            printf("Item não encontrado. Comparações: %d\n", comparacoes);
                    }

                } while (opcaoEstrutura != 0);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcaoPrincipal != 0);

    return 0;
}

// ---------------------------
// IMPLEMENTAÇÃO – VETOR
// ---------------------------
void inserirItemVetor(Item mochila[], int *contador) {
    if (*contador >= MAX_ITENS) {
        printf("Mochila cheia.\n");
        return;
    }

    printf("Nome: ");
    fgets(mochila[*contador].nome, 30, stdin);
    mochila[*contador].nome[strcspn(mochila[*contador].nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(mochila[*contador].tipo, 20, stdin);
    mochila[*contador].tipo[strcspn(mochila[*contador].tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &mochila[*contador].quantidade);
    getchar();

    (*contador)++;
    printf("Item adicionado com sucesso. Total: %d itens.\n", *contador);
}

void removerItemVetor(Item mochila[], int *contador) {
    if (*contador == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int i, encontrado = 0;
    for (i = 0; i < *contador; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            mochila[i] = mochila[*contador - 1];
            (*contador)--;
            encontrado = 1;
            break;
        }
    }
    if (encontrado) printf("Item removido.\n");
    else printf("Item não encontrado.\n");
}

void listarItensVetor(Item mochila[], int contador) {
    if (contador == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    printf("\n--- Itens no Vetor ---\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("---------------------------------------------\n");
    for (int i = 0; i < contador; i++)
        printf("%-20s %-15s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
}

int buscarSequencialVetor(Item mochila[], int contador, char nome[], int *comparacoes) {
    for (int i = 0; i < contador; i++) {
        (*comparacoes)++;
        if (strcmp(mochila[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

void ordenarVetor(Item mochila[], int contador) {
    for (int i = 0; i < contador - 1; i++) {
        for (int j = i + 1; j < contador; j++) {
            if (strcmp(mochila[i].nome, mochila[j].nome) > 0) {
                Item temp = mochila[i];
                mochila[i] = mochila[j];
                mochila[j] = temp;
            }
        }
    }
    printf("Itens ordenados por nome.\n");
}

int buscarBinariaVetor(Item mochila[], int contador, char nome[], int *comparacoes) {
    int inicio = 0, fim = contador - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(nome, mochila[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}

// ---------------------------
// IMPLEMENTAÇÃO – LISTA ENCADEADA
// ---------------------------
void inserirItemLista(No **inicio) {
    No *novo = (No *) malloc(sizeof(No));
    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = *inicio;
    *inicio = novo;

    printf("Item adicionado na lista encadeada.\n");
}

void removerItemLista(No **inicio) {
    if (*inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = *inicio, *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item não encontrado.\n");
        return;
    }

    if (anterior == NULL)
        *inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("Item removido da lista.\n");
}

void listarItensLista(No *inicio) {
    if (inicio == NULL) {
        printf("Nenhum item na lista.\n");
        return;
    }

    printf("\n--- Itens na Lista Encadeada ---\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("---------------------------------------------\n");

    No *atual = inicio;
    while (atual != NULL) {
        printf("%-20s %-15s %-10d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
}

int buscarSequencialLista(No *inicio, char nome[], int *comparacoes) {
    No *atual = inicio;
    while (atual != NULL) {
        (*comparacoes)++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return 1;
        atual = atual->proximo;
    }
    return 0;
}