#include <stdio.h>
#include <stdlib.h>
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * Q3) Dada uma lista l qualquer, desloque uma vez os elementos de l
 * de acordo com n:
 *   - n impar: o elemento da ultima posicao passa a ser o primeiro.
 *   - n par  : o elemento da primeira posicao passa a ser o ultimo.
 *     Prototipo: TLSE* desloca (TLSE* l, int n).
 * ------------------------------------------------------------------ */

static TLSE *cria_lista(const int *v, int n) {
    TLSE *l = TLSE_inicializa();
    for (int i = n - 1; i >= 0; i--)
        l = TLSE_insere(l, v[i]);
    return l;
}

TLSE *desloca(TLSE *l, int n) {
    if (l == NULL || l->prox == NULL)
        return l;

    if (n % 2 != 0) {                 /* impar: ultimo -> inicio */
        TLSE *ant = NULL, *p = l;
        while (p->prox != NULL) {
            ant = p;
            p = p->prox;
        }
        ant->prox = NULL;
        p->prox = l;
        return p;
    } else {                          /* par: primeiro -> fim */
        TLSE *nova_cabeca = l->prox;
        TLSE *p = l;
        while (p->prox != NULL)
            p = p->prox;
        p->prox = l;
        l->prox = NULL;
        return nova_cabeca;
    }
}

int main(void) {
    int v[] = {1, 2, 3, 4, 5, 6};

    TLSE *l = cria_lista(v, 6);
    printf("original      : ");  TLSE_imprime(l);  printf("\n");

    l = desloca(l, 3);               /* n impar */
    printf("desloca(l, 3) : ");  TLSE_imprime(l);  printf("\n");

    l = desloca(l, 4);               /* n par */
    printf("desloca(l, 4) : ");  TLSE_imprime(l);  printf("\n");

    TLSE_libera(l);
    return 0;
}
