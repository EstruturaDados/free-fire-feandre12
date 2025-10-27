#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10  // Capacidade máxima da mochila

// Estrutura que representa cada item do inventário
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// --- PROTÓTIPOS DAS FUNÇÕES ---
void inserirItem(struct Item mochila[], int *contador);
void removerItem(struct Item mochila[], int *contador);
void listarItens(struct Item mochila[], int contador);
void buscarItem(struct Item mochila[], int contador);
int buscarIndice(struct Item mochila[], int contador, char nomeBusca[]);

int main() {
    struct Item mochila[MAX_ITENS]; // Vetor que representa a mochila
    int contador = 0;               // Quantos itens estão cadastrados
    int opcao;

    do {
        // Menu principal
        printf("\n=== SISTEMA DE INVENTÁRIO - MOCHILA DE LOOT ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o '\n' deixado pelo scanf

        switch (opcao) {
            case 1:
                inserirItem(mochila, &contador);
                listarItens(mochila, contador);
                break;

            case 2:
                removerItem(mochila, &contador);
                listarItens(mochila, contador);
                break;

            case 3:
                listarItens(mochila, contador);
                break;

            case 4:
                buscarItem(mochila, contador);
                break;

            case 0:
                printf("\nSaindo do inventário...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// --- FUNÇÃO: Inserir novo item ---
void inserirItem(struct Item mochila[], int *contador) {
    if (*contador >= MAX_ITENS) {
        printf("A mochila está cheia. Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome do item: ");
    fgets(mochila[*contador].nome, 30, stdin);
    mochila[*contador].nome[strcspn(mochila[*contador].nome, "\n")] = '\0'; // remove '\n'

    printf("Tipo do item (arma, munição, cura...): ");
    fgets(mochila[*contador].tipo, 20, stdin);
    mochila[*contador].tipo[strcspn(mochila[*contador].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*contador].quantidade);
    getchar();

    (*contador)++;
    int restantes = MAX_ITENS - *contador;

    printf("Item adicionado com sucesso.\n");
    printf("Slots restantes no inventário: %d de %d.\n", restantes, MAX_ITENS);
}

// --- FUNÇÃO: Remover item pelo nome ---
void removerItem(struct Item mochila[], int *contador) {
    if (*contador == 0) {
        printf("Nenhum item para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\n--- Remover Item ---\n");
    printf("Informe o nome do item a ser removido: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int indice = buscarIndice(mochila, *contador, nomeRemover);

    if (indice == -1) {
        printf("Item não encontrado.\n");
    } else {
        mochila[indice] = mochila[*contador - 1]; // substitui o removido pelo último
        (*contador)--;
        printf("Item '%s' removido da mochila.\n", nomeRemover);
        printf("Slots disponíveis agora: %d de %d.\n", MAX_ITENS - *contador, MAX_ITENS);
    }
}

// --- FUNÇÃO: Listar todos os itens ---
void listarItens(struct Item mochila[], int contador) {
    if (contador == 0) {
        printf("\nMochila vazia. Nenhum item cadastrado.\n");
        return;
    }

    printf("\n--- Itens da Mochila ---\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("---------------------------------------------\n");

    for (int i = 0; i < contador; i++) {
        printf("%-20s %-15s %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }

    printf("\nTotal de itens: %d | Slots livres: %d\n", contador, MAX_ITENS - contador);
}

// --- FUNÇÃO: Buscar item pelo nome (busca sequencial) ---
void buscarItem(struct Item mochila[], int contador) {
    if (contador == 0) {
        printf("Nenhum item na mochila.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Buscar Item ---\n");
    printf("Digite o nome do item que deseja localizar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int indice = buscarIndice(mochila, contador, nomeBusca);

    if (indice == -1) {
        printf("Item '%s' não encontrado.\n", nomeBusca);
    } else {
        printf("\nItem encontrado:\n");
        printf("Nome: %s\n", mochila[indice].nome);
        printf("Tipo: %s\n", mochila[indice].tipo);
        printf("Quantidade: %d\n", mochila[indice].quantidade);
    }
}

// --- FUNÇÃO AUXILIAR: Retorna índice do item pelo nome ou -1 se não encontrado ---
int buscarIndice(struct Item mochila[], int contador, char nomeBusca[]) {
    for (int i = 0; i < contador; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i; // item encontrado
        }
    }
    return -1; // não encontrado
}