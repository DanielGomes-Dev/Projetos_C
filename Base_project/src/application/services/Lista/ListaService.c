#include "application/services/Lista/ListaService.h"

void criar_lista(Lista* lista) {
    lista_init(lista);
}

void adicionar_valor(Lista* lista, int valor) {
    lista_insert(lista, valor);
}