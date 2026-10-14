#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_STRG_ITENS 50 //define o tamanho de caracteres dentro da string
#define TAM_MAX 10 //define o número máximo de itens na struct

typedef struct {
    char nome [TAM_STRG_ITENS];
    char tipo [TAM_STRG_ITENS];
    int quantidade;
    int prioridade;
} Item;


void adicionarItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItem(Item mochila[], int total);
void buscarItem(Item mochila[], int total);
void organizarMochila (Item mochila [], int total, int *ordenadoPorNome);
void bubbleSortNome(Item mochila [], int total);
void insertionSortTipo(Item mochila [], int total);
void selectionSortPrioridade (Item mochila [], int total);
void buscaBinaria(Item mochila[], int total);

int main () {
    Item mochila[TAM_MAX];
    int totalItens = 0;
    int opcao;
    int ordenadoPorNome = 0;

    do {
        printf("\n============================================================================\n");
        printf("MOCHILA DE SOBREVIVÊNCIA\n");
        printf("===================================================================================\n");
        printf("\nItens da Mochila: %d/%d\n", totalItens, TAM_MAX);
        printf("\n1. Adicionar Item (loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens da Mochila\n");
        printf("4. Buscar item na Mochila (sequencial)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("6. Organizar Mochila\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                adicionarItem(mochila, &totalItens);
                ordenadoPorNome = 0;
                break;
            case 2: 
                removerItem(mochila, &totalItens);
                break;
            case 3: 
                listarItem(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 5:
                if (!ordenadoPorNome) {
                    printf("A busca binária exige que os itens estejam ordenados por nome!\n");
                    printf("Vá na opção organizar e execute a ordenação por nome\n");
                } else {
                    buscaBinaria(mochila, totalItens);
                }
                break;
            case 6:
                organizarMochila(mochila, totalItens, &ordenadoPorNome);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao Invalida!\n");
        }

    } while (opcao != 0);

return 0;

}

// Função para adicionar novos itens na mochila
void adicionarItem(Item mochila[], int *total ) {
    if (*total >= TAM_MAX) {
        printf("Não é possível adicionar mais itens, pois a Mochila já está cheia.");
        return;
    }
    printf("\n---ADICIONAR NOVO ITEM---\n\n");

    printf("Nome do item: ");
    scanf(" %49[^\n]", mochila[*total].nome);

    printf("Tipo do item: ");
    scanf(" %49[^\n]", mochila[*total].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &mochila[*total].prioridade);

(*total)++;
}

//função para remover item pelo nome
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("Erro! Não existem itens para serem removidos.");
        return;
    }
    
    char nomeBusca[TAM_STRG_ITENS];
    printf("\n--- REMOVER ITEM ---\n\n");
    printf("\nDigite o nome do item que deseja remover:\n");
    scanf(" %49[^\n]", nomeBusca);

    int indiceEncontrado = -1; 

    for (int i = 0; i <*total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) ==0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("\nItem \"%s\" não encontrado na mochila\n", nomeBusca);
        return;
    }

    for (int i = indiceEncontrado; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*total)--;

    printf("\nItem \"%s\" removido com sucesso!", nomeBusca);
}

//função para listar itens
void listarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila esta vazia\n");
        return;
    }

    printf("\n=================== ITENS NA MOCHILA ========================\n");
    for (int i = 0; i < total; i++) {
        printf("[%d] Nome: %-15s │ Tipo: %-15s │ Quantidade: %-15d | Prioridade: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("=============================================================\n");
}

void buscarItem(Item mochila[], int total) {
    if (total == 0 ) {
        printf("A mochila não possui itens!");
        return;
    }

    char nomeBusca[TAM_STRG_ITENS];
    printf("\n--- BUSCAR ITEM ---\n");
    printf("Digite o nome do item que você procura:\n");
    scanf(" %49[^\n]", nomeBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Posição: %d │ Nome: %s │ Tipo: %s │ Quantidade: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("\nItem \"%s\" não encontrado na mochila!\n", nomeBusca);
 
}

void bubbleSortNome(Item mochila[], int total) {
    Item temp;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            //se mochila[j].nome for maior em ordem alfabetica que o proximo
            if(strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }   
        }
    }
}

void insertionSortTipo(Item mochila[], int total) {
    for (int i = 1; i < total; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        //Descola os elementos maiores que 'chave' uma posicao a frente
        while (j >= 0 && strcmp(mochila[j].tipo, chave.tipo) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
}

void selectionSortPrioridade(Item mochila[], int total) {
    for (int i = 0; i < total - 1; i++) {
        int indiceMenor = i;

        for (int j = i + 1; j < total; j++) {
            if (mochila[j].prioridade < mochila[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }
        //troca a posiçao atual com a menor encontrada
        if (indiceMenor != i) {
            Item temp = mochila[i];
            mochila[i] = mochila[indiceMenor];
            mochila[indiceMenor] = temp;
        }
    }
}


void organizarMochila (Item mochila [], int total, int *ordenadoPorNome) {
    if (total == 0) {
        printf("A Mochila não possui itens");
        return;
    }

    int escolha;
    printf("\n--- Estratégia de Organização ---\n");
    printf("Como deseja ordenar os itens?\n");
    printf("1. Por nome (ordem alfabetica).\n");
    printf("2. Por Tipo.\n");
    printf("3. Por prioridade de montagem.\n");
    printf("0. Cancelar.\n\n");
    printf("Digite a sua escolha: ");
    scanf("%d", &escolha);


    switch (escolha) {
        case 1:
            bubbleSortNome(mochila, total);
            *ordenadoPorNome = 1;
            printf("\nItens organizados por nome com sucesso!\n");
            listarItem(mochila, total);  
            break;
        case 2:
            insertionSortTipo(mochila, total);
            *ordenadoPorNome = 0;
            printf("Itens organizados por Tipo com sucesso!\n");
            listarItem(mochila, total);
            break;
        case 3:
            selectionSortPrioridade(mochila, total);
            *ordenadoPorNome= 0;
            printf("Itens organizados por prioridade com sucesso!\n");
            listarItem(mochila, total);
            break;
        case 0:
            printf("Organização cancelada\n");
        default:
            printf("Opção invalida!\n");
    }
}

void buscaBinaria (Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeBusca[TAM_STRG_ITENS];
    printf("\n--- Busca Binária por nome ---");
    printf("Digite o nome do item que procura: ");
    scanf(" %49[^\n]", nomeBusca);

    int inicio = 0;
    int fim = total - 1;
    int encontrado = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        int comparacao = strcmp(mochila[meio].nome, nomeBusca);

        if (comparacao == 0) {
            printf("\nItem encontrado via Busca Binaria!\n");
            printf("Posição: %d | Nome: %s | Tipo: %s | Quantidade: %d | Prioridade: %d\n", meio + 1, mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            encontrado = 1;
            break;
    } else if (comparacao < 0) {
        //o item do meio vem antes alfabeticamente, busca na metade direita
        inicio = meio + 1;
    } else {
        //O item do meio vem depois alfabeticamente, busca na metade esquerda
        fim = meio - 1;
    }
}

    if (!encontrado) {
        printf("\nItem \"%s\" não foi encontrado na mochila.\n", nomeBusca);
    }
}

