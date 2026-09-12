#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q9) quantidade de nos folha: int nf (TAB *a);
 *
 * Folha = no sem nenhum filho.
 * ------------------------------------------------------------------ */

int nf(TAB *a) {
    if (!a)
        return 0;
    if (!a->esq && !a->dir)
        return 1;
    return nf(a->esq) + nf(a->dir);
}

/*        4
 *       / \
 *      2   6
 *     / \   \
 *    1  3    7      -> folhas: 1, 3, 7  => 3                          */
static TAB *exemplo(void) {
    return TAB_cria(4,
        TAB_cria(2, TAB_cria(1, NULL, NULL), TAB_cria(3, NULL, NULL)),
        TAB_cria(6, NULL, TAB_cria(7, NULL, NULL)));
}

int main(void) {
    TAB *a = exemplo();

    printf("arvore (pre-ordem): ");  TAB_imp_pre(a);  printf("\n");
    printf("nos folha         : %d\n", nf(a));

    TAB_libera(a);
    return 0;
}
