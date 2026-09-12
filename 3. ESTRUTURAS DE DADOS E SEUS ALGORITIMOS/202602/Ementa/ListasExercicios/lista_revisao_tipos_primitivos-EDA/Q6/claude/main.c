#include <stdio.h>
#include <stdlib.h>
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * Q6) Dada uma lista l qualquer, retorne, numa lista de saida, os
 * elementos impares e depois os pares, cada grupo na ordem em que
 * aparecem em l. A lista l continua com os seus elementos.
 *     Prototipo: TLSE* i_p (TLSE *l).
 *
 * "anexa" cria um no com TLSE_insere e o coloca no fim, mantendo a
 * ordem de aparicao. Faz-se uma passada pelos impares e outra pelos
 * pares.
 * ------------------------------------------------------------------ */

static TLSE *cria_lista(const int *v, int n) {
    TLSE *l = TLSE_inicializa();
    for (int i = n - 1; i >= 0; i--)
        l = TLSE_insere(l, v[i]);
    return l;
}

static TLSE *anexa(TLSE *l, int elem) {
    TLSE *novo = TLSE_insere(NULL, elem);
    if (l == NULL)
        return novo;
    TLSE *p = l;
    while (p->prox != NULL)
        p = p->prox;
    p->prox = novo;
    return l;
}

TLSE *i_p(TLSE *l) {
    TLSE *saida = TLSE_inicializa();
    for (TLSE *p = l; p != NULL; p = p->prox)
        if (p->info % 2 != 0)
            saida = anexa(saida, p->info);
    for (TLSE *p = l; p != NULL; p = p->prox)
        if (p->info % 2 == 0)
            saida = anexa(saida, p->info);
    return saida;
}

int main(void) {
    int v[] = {1, 2, 3, 4, 5, 6};
    TLSE *l = cria_lista(v, 6);
    TLSE *s = i_p(l);

    printf("entrada    : ");  TLSE_imprime(l);  printf("\n");
    printf("i_p (saida): ");  TLSE_imprime(s);  printf("\n");

    TLSE_libera(l);
    TLSE_libera(s);
    return 0;
}
