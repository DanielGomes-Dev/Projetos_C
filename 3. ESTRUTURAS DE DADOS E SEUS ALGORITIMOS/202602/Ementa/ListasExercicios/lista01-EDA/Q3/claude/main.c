#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q3) maior elemento da arvore: TAB* maior (TAB *a);
 *
 * A arvore e binaria qualquer (NAO e de busca), entao e preciso
 * varrer os dois lados. Retorna o ponteiro para o no de maior info.
 * ------------------------------------------------------------------ */

TAB *maior(TAB *a) {
    if (!a)
        return NULL;

    TAB *m = a;
    TAB *e = maior(a->esq);
    TAB *d = maior(a->dir);

    if (e && e->info > m->info) m = e;
    if (d && d->info > m->info) m = d;
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
    TAB *m = maior(a);

    printf("arvore (pre-ordem): ");  TAB_imp_pre(a);  printf("\n");
    printf("maior elemento    : %d\n", m ? m->info : 0);

    TAB_libera(a);
    return 0;
}
