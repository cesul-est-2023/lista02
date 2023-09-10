#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct musica {
    char* titulo;
    char* artista;
    int duracao;
} Musica;

typedef struct Item {
    Musica valor;
    struct Item* proximo;
} Item;

typedef struct Lista {
    Item* inicio;
    Item* final;
    int tamanho;
} Lista;

Lista lista = { NULL, NULL, 0};

Musica criarReserva() {
    Musica musica;
    musica.titulo = malloc(50);
    musica.artista = malloc(50);

    printf("Informe o titulo da musica: ");
    scanf(" %[^\n]", musica.titulo);

    printf("Informe o nome do artista: ");
    scanf(" %[^\n]", musica.artista);

    printf("Informe a duração da musica: ");
    scanf("%d", &musica.duracao);

    return musica;
}

Item* criarItem() {
    Musica valor = criarReserva();

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
        Musica musica = item->valor;
        printf("Titulo: %s \n", musica.titulo);
        printf("Artista: %s \n", musica.artista);
        printf("Duracao: %d min. \n", musica.duracao);

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
        if (atual->proximo == NULL) { //indica que atual passou a ser o último da lista
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
    printf("1 - Adicionar Musica \n");
    printf("2 - Remover Musica \n");
    printf("3 - Listar Musicas \n");
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
