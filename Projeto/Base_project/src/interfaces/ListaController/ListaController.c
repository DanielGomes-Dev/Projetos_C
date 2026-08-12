#include "application/services/Lista/ListaService.h"

void iniciar_lista() {

    Lista lista;

    lista_init(&lista);

    lista_insert(&lista, 10);
    lista_insert(&lista, 20);
    lista_insert(&lista, 30);
    lista_print(&lista);


}