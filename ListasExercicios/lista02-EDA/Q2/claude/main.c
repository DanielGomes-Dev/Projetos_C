#include <stdio.h>
#include <stdlib.h>
#include "../../TABB/TABB.h"

/* ------------------------------------------------------------------ *
 * Q2) menor elemento da arvore: TABB* menor (TABB *a);
 *
 * Numa arvore binaria de BUSCA o menor elemento e o no mais a
 * esquerda: desce sempre por a->esq ate o fim.
 * ------------------------------------------------------------------ */

TABB *menor(TABB *a) {
    if (!a)
        return NULL;
    while (a->esq)
        a = a->esq;
    return a;
}

static TABB *exemplo(void) {
    int v[] = {50, 30, 70, 20, 40, 60, 80, 15};
    TABB *a = TABB_inicializa();
    for (int i = 0; i < 8; i++)
        a = TABB_insere(a, v[i]);
    return a;
}

int main(void) {
    TABB *a = exemplo();
    TABB *m = menor(a);

    printf("arvore (simetrico): ");  TABB_imp_sim(a);  printf("\n");
    printf("menor elemento    : %d\n", m ? m->info : 0);

    TABB_libera(a);
    return 0;
}
