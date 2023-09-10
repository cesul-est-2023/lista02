#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct reserva {
    char* hospede;
    char* checkIn;
    char* checkOut;
    int quarto;
} Reserva;

typedef struct Item {
    Reserva valor;
    struct Item* proximo;
} Item;

typedef struct Lista {
    Item* inicio;
    Item* final;
    int tamanho;
} Lista;

Lista lista = { NULL, NULL, 0};

Reserva criarReserva() {
    Reserva reserva;
    reserva.hospede = malloc(50);
    reserva.checkIn = malloc(10);
    reserva.checkOut = malloc(10);

    printf("Informe o nome do hospede: ");
    scanf(" %[^\n]", reserva.hospede);

    printf("Informe a data do check in: ");
    scanf(" %[^\n]", reserva.checkIn);

    printf("Informe o data do check out: ");
    scanf(" %[^\n]", reserva.checkOut);

    printf("Informe o numero do quarto: ");
    scanf("%d", &reserva.quarto);

    return reserva;
}

Item* criarItem() {
    Reserva valor = criarReserva();

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
        Reserva reserva = item->valor;
        printf("Hospede: %s \n", reserva.hospede);
        printf("Quarto: %d \n", reserva.quarto);
        printf("Check in: %s \n", reserva.checkIn);
        printf("Check out: %s \n", reserva.checkOut);
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
    printf("1 - Adicionar Reserva \n");
    printf("2 - Remover Reserva \n");
    printf("3 - Listar Reservas \n");
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
