#include <stdio.h>
#include <stdlib.h>
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * Q1) Escreva uma funcao em C que, dada uma lista l qualquer, inverta
 * os elementos de l.
 *     Prototipo: void inverte (TLSE* l).
 *
 * Como o prototipo e void e o ponteiro chega por valor, nao da para
 * trocar a cabeca vista pelo chamador. Entao invertemos os campos
 * info dos nos: monta-se uma lista auxiliar invertida (com
 * TLSE_insere, que insere no inicio) e copiam-se os valores de volta.
 * ------------------------------------------------------------------ */

static TLSE *cria_lista(const int *v, int n) {
    TLSE *l = TLSE_inicializa();
    for (int i = n - 1; i >= 0; i--)
        l = TLSE_insere(l, v[i]);
    return l;
}

void inverte(TLSE *l) {
    TLSE *aux = TLSE_inicializa();
    for (TLSE *p = l; p != NULL; p = p->prox)   /* aux fica invertida */
        aux = TLSE_insere(aux, p->info);

    TLSE *q = aux;
    for (TLSE *p = l; p != NULL; p = p->prox, q = q->prox)
        p->info = q->info;

    TLSE_libera(aux);
}

int main(void) {
    int v[] = {1, 2, 3, 4, 5, 6};
    TLSE *l = cria_lista(v, 6);

    printf("original : ");  TLSE_imprime(l);  printf("\n");
    inverte(l);
    printf("invertida: ");  TLSE_imprime(l);  printf("\n");

    TLSE_libera(l);
    return 0;
}
