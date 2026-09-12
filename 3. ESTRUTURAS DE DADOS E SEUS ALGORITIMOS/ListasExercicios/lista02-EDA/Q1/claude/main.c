#include <stdio.h>
#include <stdlib.h>
#include "../../TABB/TABB.h"

/* ------------------------------------------------------------------ *
 * Q1) maior elemento da arvore: TABB* maior (TABB *a);
 *
 * Numa arvore binaria de BUSCA o maior elemento e o no mais a
 * direita: desce sempre por a->dir ate o fim.
 * ------------------------------------------------------------------ */

TABB *maior(TABB *a) {
    if (!a)
        return NULL;
    while (a->dir)
        a = a->dir;
    return a;
}

static TABB *exemplo(void) {
    int v[] = {50, 30, 70, 20, 40, 60, 80, 65};
    TABB *a = TABB_inicializa();
    for (int i = 0; i < 8; i++)
        a = TABB_insere(a, v[i]);
    return a;
}

int main(void) {
    TABB *a = exemplo();
    TABB *m = maior(a);

    printf("arvore (simetrico): ");  TABB_imp_sim(a);  printf("\n");
    printf("maior elemento    : %d\n", m ? m->info : 0);

    TABB_libera(a);
    return 0;
}
