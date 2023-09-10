#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct contato {
    char* nome;
    char* telefone;
    char* endereco;
} Contato;

typedef struct Item {
    Contato valor;
    struct Item* proximo;
} Item;

typedef struct Lista {
    Item* inicio;
    Item* final;
    int tamanho;
} Lista;

Lista lista = { NULL, NULL, 0};

Contato criarReserva() {
    Contato contato;
    contato.nome = malloc(50);
    contato.telefone = malloc(20);
    contato.endereco = malloc(100);

    printf("Informe o nome do contato: ");
    scanf(" %[^\n]", contato.nome);

    printf("Informe o telefone do contato: ");
    scanf(" %[^\n]", contato.telefone);

    printf("Informe o endereco do contato: ");
    scanf(" %[^\n]", contato.endereco);

    return contato;
}

Item* criarItem() {
    Contato valor = criarReserva();

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
        Contato contato = item->valor;
        printf("Nome: %s \n", contato.nome);
        printf("Telefone: %s \n", contato.telefone);
        printf("Endereco: %s \n", contato.endereco);
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

void editarItem() {
    int pos;

    printf("Informe a posicao para editar: ");
    scanf("%d", &pos);

    Item* itemEditar = obterItem(pos);
    Contato novosDados = criarReserva();

    itemEditar->valor = novosDados;
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
            editarItem();
            break;
        case 4:
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
    printf("1 - Adicionar Contato \n");
    printf("2 - Remover Contato \n");
    printf("3 - Editar Contato \n");
    printf("4 - Listar Contatos \n");
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
