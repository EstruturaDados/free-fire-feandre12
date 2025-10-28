#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constantes
#define MAX_COMPONENTES 20
#define CHAVE_BUSCA "chip central" // O componente-chave para a busca

// 1. Criação de structs
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Protótipos das funções
void cadastrarComponentes(Componente componentes[], int *tamanho);
void mostrarComponentes(Componente componentes[], int tamanho);

// 3. Opções de ordenação
void bubbleSortNome(Componente componentes[], int tamanho, long long *comparacoes);
void insertionSortTipo(Componente componentes[], int tamanho, long long *comparacoes);
void selectionSortPrioridade(Componente componentes[], int tamanho, long long *comparacoes);
void trocarComponente(Componente *a, Componente *b); // Função auxiliar para as trocas

// 4. Busca binária
int buscaBinariaPorNome(Componente componentes[], int tamanho, const char chave[], long long *comparacoes);

// Função principal (Main)
int main() {
    Componente componentes[MAX_COMPONENTES];
    int tamanho = 0;
    int opcao;
    
    // Configuração para medição de tempo
    clock_t inicio, fim;
    double tempo_execucao;
    long long comparacoes = 0;

    // Cabeçalho e Introdução
    printf("Desafio Final: Modulo Avancado de Organizacao de Componentes\n");
    printf("=================================================================\n");
    printf("Bem-vindo, Sobrevivente! O destino da fuga depende da sua estrategia.\n");
    printf("Voce deve priorizar e ordenar os componentes da Torre de Resgate.\n\n");

    // 2. Entrada dos dados
    cadastrarComponentes(componentes, &tamanho);

    // Menu Interativo
    do {
        printf("\n--- MENU ESTRATEGICO DE ORDENACAO E BUSCA ---\n");
        printf("1. Ordenar por NOME (Bubble Sort) e realizar Busca Binaria\n");
        printf("2. Ordenar por TIPO (Insertion Sort)\n");
        printf("3. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("4. Sair e Montar a Torre (Encerrar Programa)\n");
        printf("Escolha sua estrategia (1-4): ");
        if (scanf("%d", &opcao) != 1) {
            // Limpar o buffer em caso de entrada não numérica
            while (getchar() != '\n');
            opcao = 0;
        }
        
        // Limpar o buffer após a leitura de inteiros
        while (getchar() != '\n');
        
        comparacoes = 0; // Reinicia a contagem de comparações para cada nova operação
        
        // Cópia dos dados originais para não impactar medições futuras
        Componente tempComponentes[MAX_COMPONENTES];
        memcpy(tempComponentes, componentes, tamanho * sizeof(Componente));

        switch (opcao) {
            case 1:
                printf("\n>>> Estrategia Escolhida: Ordenacao por NOME (Bubble Sort)\n");
                inicio = clock();
                bubbleSortNome(tempComponentes, tamanho, &comparacoes);
                fim = clock();
                tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

                // 5. Medição de desempenho
                printf("--- Desempenho (Bubble Sort) ---\n");
                printf("Numero de Comparacoes: %lld\n", comparacoes);
                printf("Tempo de Execucao: %.6f segundos\n", tempo_execucao);
                
                // 6. Montagem final (Exibição dos Componentes Ordenados)
                printf("\nComponentes Ordenados por NOME:\n");
                mostrarComponentes(tempComponentes, tamanho);

                // 4. Busca binária
                printf("\n>>> Iniciando Busca Binaria Otimizada pelo Componente-Chave: \"%s\"...\n", CHAVE_BUSCA);
                int indiceChave = buscaBinariaPorNome(tempComponentes, tamanho, CHAVE_BUSCA, &comparacoes);
                
                printf("--- Desempenho (Busca Binaria) ---\n");
                printf("Numero de Comparacoes Adicionais: %lld\n", comparacoes);

                if (indiceChave != -1) {
                    printf("\nCHAVE ENCONTRADA! O componente \"%s\" esta na posicao %d.\n", CHAVE_BUSCA, indiceChave + 1);
                    printf("  Tipo: %s, Prioridade: %d\n", tempComponentes[indiceChave].tipo, tempComponentes[indiceChave].prioridade);
                    printf("Ativacao da torre desbloqueada!\n");
                } else {
                    printf("\nComponente-Chave \"%s\" NAO ENCONTRADO! Fuga Impossivel.\n", CHAVE_BUSCA);
                }
                break;
            case 2:
                printf("\n>>> Estrategia Escolhida: Ordenacao por TIPO (Insertion Sort)\n");
                inicio = clock();
                insertionSortTipo(tempComponentes, tamanho, &comparacoes);
                fim = clock();
                tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

                // 5. Medição de desempenho
                printf("--- Desempenho (Insertion Sort) ---\n");
                printf("Numero de Comparacoes: %lld\n", comparacoes);
                printf("Tempo de Execucao: %.6f segundos\n", tempo_execucao);
                
                // 6. Montagem final
                printf("\nComponentes Ordenados por TIPO:\n");
                mostrarComponentes(tempComponentes, tamanho);
                break;
            case 3:
                printf("\n>>> Estrategia Escolhida: Ordenacao por PRIORIDADE (Selection Sort)\n");
                inicio = clock();
                selectionSortPrioridade(tempComponentes, tamanho, &comparacoes);
                fim = clock();
                tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

                // 5. Medição de desempenho
                printf("--- Desempenho (Selection Sort) ---\n");
                printf("Numero de Comparacoes: %lld\n", comparacoes);
                printf("Tempo de Execucao: %.6f segundos\n", tempo_execucao);
                
                // 6. Montagem final
                printf("\nComponentes Ordenados por PRIORIDADE (Menor e Mais Prioritario):\n");
                mostrarComponentes(tempComponentes, tamanho);
                break;
            case 4:
                printf("\nFuga Encerrada. Obrigado por jogar!\n");
                break;
            default:
                printf("\nOpcao invalida! Escolha um numero entre 1 e 4.\n");
        }
    } while (opcao != 4);

    return 0;
}

// 2. Entrada dos dados
void cadastrarComponentes(Componente componentes[], int *tamanho) {
    int i = 0;
    char continuar[4];

    printf("--- Cadastro de Componentes ---\n");
    do {
        // Verifica se atingiu o limite
        if (i >= MAX_COMPONENTES) {
            printf("\nLimite maximo de %d componentes atingido.\n", MAX_COMPONENTES);
            break;
        }

        printf("\nComponente %d:\n", i + 1);

        // Captura o NOME do componente
        printf("Nome (ex: chip central): ");
        if (fgets(componentes[i].nome, sizeof(componentes[i].nome), stdin) == NULL) continue;
        // Remove a quebra de linha (newline)
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = 0;
        
        // Verifica se o nome foi inserido (para interromper o cadastro)
        if (strlen(componentes[i].nome) == 0) break;

        // Captura o TIPO do componente
        printf("Tipo (ex: controle, suporte): ");
        if (fgets(componentes[i].tipo, sizeof(componentes[i].tipo), stdin) == NULL) continue;
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = 0;

        // Captura a PRIORIDADE
        printf("Prioridade (1 a 10, sendo 1 mais alto): ");
        if (scanf("%d", &componentes[i].prioridade) != 1 || componentes[i].prioridade < 1 || componentes[i].prioridade > 10) {
            printf("Prioridade invalida. Componente descartado.\n");
            // Limpar o buffer
            while (getchar() != '\n');
            continue;
        }
        
        // Limpar o buffer
        while (getchar() != '\n');

        i++;

        // Pergunta se deseja continuar
        printf("Deseja cadastrar mais um componente? (s/n): ");
        if (fgets(continuar, sizeof(continuar), stdin) == NULL || (continuar[0] != 's' && continuar[0] != 'S')) {
            break;
        }

    } while (1);

    *tamanho = i; // Atualiza o tamanho real
    printf("\nCadastro finalizado! Total de %d componentes prontos.\n", *tamanho);
}


// Função Auxiliar para Troca
void trocarComponente(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// 3. Opções de ordenação
// Bubble sort: ordenar por nome (string)
void bubbleSortNome(Componente componentes[], int tamanho, long long *comparacoes) {
    int i, j;
    int trocou;
    for (i = 0; i < tamanho - 1; i++) {
        trocou = 0;
        for (j = 0; j < tamanho - 1 - i; j++) {
            (*comparacoes)++; // Contagem da comparação de string
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                trocarComponente(&componentes[j], &componentes[j + 1]);
                trocou = 1;
            }
        }
        // Otimização: se não houve troca na passagem, o array está ordenado
        if (trocou == 0) break;
    }
}

// Insertion sort: ordenar por tipo (string)
void insertionSortTipo(Componente componentes[], int tamanho, long long *comparacoes) {
    int i, j;
    Componente chave;
    for (i = 1; i < tamanho; i++) {
        chave = componentes[i];
        j = i - 1;

        // Move os elementos de componentes[0..i-1] que são maiores/depois lexicograficamente 
        // que a chave, para uma posição à frente de sua posição atual
        while (j >= 0) {
            (*comparacoes)++; // Contagem da comparação de string
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j = j - 1;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
}

// Selection sort: ordenar por prioridade (int)
void selectionSortPrioridade(Componente componentes[], int tamanho, long long *comparacoes) {
    int i, j, indice_minimo;

    // Um por um move a fronteira do sub-array não ordenado
    for (i = 0; i < tamanho - 1; i++) {
        // Encontra o elemento mínimo no array não ordenado
        indice_minimo = i;
        for (j = i + 1; j < tamanho; j++) {
            (*comparacoes)++; // Contagem da comparação de inteiro
            if (componentes[j].prioridade < componentes[indice_minimo].prioridade) {
                indice_minimo = j;
            }
        }

        // Troca o elemento mínimo encontrado com o primeiro elemento
        trocarComponente(&componentes[indice_minimo], &componentes[i]);
    }
}

// 4. Busca binária
int buscaBinariaPorNome(Componente componentes[], int tamanho, const char chave[], long long *comparacoes) {
    int esquerda = 0;
    int direita = tamanho - 1;
    int resultado_comparacao;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2; // Evita overflow
        
        (*comparacoes)++; // Contagem da comparação de string
        resultado_comparacao = strcmp(componentes[meio].nome, chave);

        // Verifica se a chave está no meio
        if (resultado_comparacao == 0) {
            return meio;
        }

        // Se o nome do componente[meio] é "menor" (vem antes) que a chave, ignora a metade esquerda
        if (resultado_comparacao < 0) {
            esquerda = meio + 1;
        }
        // Se o nome do componente[meio] é "maior" (vem depois) que a chave, ignora a metade direita
        else {
            direita = meio - 1;
        }
    }

    // Se a chave não estiver presente
    return -1;
}

// 5. Montagem final
void mostrarComponentes(Componente componentes[], int tamanho) {
    if (tamanho == 0) {
        printf("Nenhum componente cadastrado para exibicao.\n");
        return;
    }
    printf("+------------------------------+--------------------+--------------+\n");
    printf("| Nome do Componente           | Tipo               | Prioridade   |\n");
    printf("+------------------------------+--------------------+--------------+\n");
    for (int i = 0; i < tamanho; i++) {
        printf("| %-28s | %-18s | %-12d |\n", 
               componentes[i].nome, 
               componentes[i].tipo, 
               componentes[i].prioridade);
    }
    printf("+------------------------------+--------------------+--------------+\n");
}