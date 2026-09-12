#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q4) menor elemento da arvore: TAB* menor (TAB *a);
 *
 * Analogo a Q3: arvore binaria qualquer, varre os dois lados e
 * retorna o ponteiro para o no de menor info.
 * ------------------------------------------------------------------ */

TAB *menor(TAB *a) {
    if (!a)
        return NULL;

    TAB *m = a;
    TAB *e = menor(a->esq);
    TAB *d = menor(a->dir);

    if (e && e->info < m->info) m = e;
    if (d && d->info < m->info) m = d;
    return m;
}

/*        7
 *       / \
 *     20   3
 *     / \   \
 *    5  11   9                                                       */
static TAB *exemplo(void) {
    return TAB_cria(7,
        TAB_cria(20, TAB_cria(5, NULL, NULL), TAB_cria(11, NULL, NULL)),
        TAB_cria(3, NULL, TAB_cria(9, NULL, NULL)));
}

int main(void) {
    TAB *a = exemplo();
    TAB *m = menor(a);

    printf("arvore (pre-ordem): ");  TAB_imp_pre(a);  printf("\n");
    printf("menor elemento    : %d\n", m ? m->info : 0);

    TAB_libera(a);
    return 0;
}
