#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct filme {
    char* titulo;
    char* genero;
    int classificacao;
} Filme;

typedef struct Item {
    Filme valor;
    struct Item* proximo;
} Item;

typedef struct Lista {
    Item* inicio;
    Item* final;
    int tamanho;
} Lista;

Lista lista = { NULL, NULL, 0};

Filme criarFilme() {
    Filme filme;
    filme.titulo = malloc(50);
    filme.genero = malloc(20);

    printf("Informe o titulo do filme: ");
    scanf(" %[^\n]", filme.titulo);

    printf("Informe a genero do filme: ");
    scanf(" %[^\n]", filme.genero);

    printf("Informe a classificacao: ");
    scanf("%d", &filme.classificacao);

    return filme;
}

Item* criarItem() {
    Filme valor = criarFilme();

    Item* novoItem = malloc(sizeof(Item));
    novoItem->valor = valor;
    novoItem->proximo = NULL;

    return novoItem;
}

void adicionarItem() {
    Item* novoItem = criarItem();

    if (lista.inicio == NULL) {
        lista.inicio = novoItem;
        lista.final = novoItem;
    } else {
        lista.final->proximo = novoItem;
        lista.final = novoItem;
    }

    lista.tamanho ++;
}

void exibirLista() {
    Item* item = lista.inicio;
    while (item != NULL) {
        Filme filme = item->valor;
        printf("Filme: %s \n", filme.titulo);
        printf("Genero: %s \n", filme.genero);
        printf("Classificacao: %d \n", filme.classificacao);
        printf("------\n");

        item = item->proximo;
    }
}

Item* obterItem(int pos) {
    Item* item = lista.inicio;
    int i = 0;

    while (i < pos && item != NULL) {
        item = item->proximo;
        i ++;
    }

    return item;
}

void removerItem() {
    int pos;

    printf("Informe a posicao para remover da lista: ");
    scanf("%d", &pos);

    Item* atual = lista.inicio;

    if (pos == 0) {
        lista.inicio = atual->proximo;

        if (lista.inicio == NULL) {
            lista.final = NULL;
        }

        free(atual);
        lista.tamanho --;
        return;
    }

    atual = obterItem(pos - 1);

    if (atual != NULL) {
        Item* itemRemover = atual->proximo;
        Item* novoProximo = itemRemover->proximo;

        atual->proximo = novoProximo;
        if (atual->proximo == NULL) {
            lista.final = atual;
        }

        free(itemRemover);
        lista.tamanho --;
    }
}

void tratarOpcaoMenu(int opcao) {
    switch (opcao) {
        case 1:
            adicionarItem();
            break;
        case 2:
            removerItem();
            break;
        case 3:
            exibirLista();
            break;
        default:
            printf("** Opcao invalida! **");
            break;
    }
}

void exibirMenu() {
    int opcao;

    printf("*** Opcoes ***\n");
    printf("1 - Adicionar Filme \n");
    printf("2 - Remover Filme \n");
    printf("3 - Listar Filmes \n");
    printf("==> ");

    scanf("%d", &opcao);

    tratarOpcaoMenu(opcao);
}

int main() {
    char continuar = 'N';

    do {
        exibirMenu();

        printf("Deseja continuar? (S/N) ");
        scanf(" %c", &continuar);
    } while (toupper(continuar) == 'S');

    return 0;
}
