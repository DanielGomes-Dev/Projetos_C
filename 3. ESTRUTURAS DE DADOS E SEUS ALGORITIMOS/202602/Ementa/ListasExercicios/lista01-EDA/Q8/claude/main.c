#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q8) quantidade de nos internos: int ni (TAB *a);
 *
 * No interno = no que tem pelo menos um filho (nao e folha nem
 * vazio). A raiz conta se tiver filhos.
 * ------------------------------------------------------------------ */

int ni(TAB *a) {
    if (!a)
        return 0;
    int este = (a->esq || a->dir) ? 1 : 0;
    return este + ni(a->esq) + ni(a->dir);
}

/*        4
 *       / \
 *      2   6
 *     / \   \
 *    1  3    7      -> internos: 4, 2, 6  => 3                        */
static TAB *exemplo(void) {
    return TAB_cria(4,
        TAB_cria(2, TAB_cria(1, NULL, NULL), TAB_cria(3, NULL, NULL)),
        TAB_cria(6, NULL, TAB_cria(7, NULL, NULL)));
}

int main(void) {
    TAB *a = exemplo();

    printf("arvore (pre-ordem): ");  TAB_imp_pre(a);  printf("\n");
    printf("nos internos      : %d\n", ni(a));

    TAB_libera(a);
    return 0;
}
