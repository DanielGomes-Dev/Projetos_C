#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q2) espelho de uma arvore: TAB* espelho (TAB *a);
 *
 * O que esta a esquerda na original fica a direita no espelho e
 * vice-versa. Gera uma arvore nova (TAB_cria) trocando esq <-> dir
 * recursivamente; a original permanece intacta.
 * ------------------------------------------------------------------ */

TAB *espelho(TAB *a) {
    if (!a)
        return NULL;
    return TAB_cria(a->info, espelho(a->dir), espelho(a->esq));
}

/*        1
 *       / \
 *      2   3
 *     /   / \
 *    4   5   6                                                       */
static TAB *exemplo(void) {
    return TAB_cria(1,
        TAB_cria(2, TAB_cria(4, NULL, NULL), NULL),
        TAB_cria(3, TAB_cria(5, NULL, NULL), TAB_cria(6, NULL, NULL)));
}

int main(void) {
    TAB *a = exemplo();
    TAB *e = espelho(a);

    printf("original (pre-ordem): ");  TAB_imp_pre(a);  printf("\n");
    printf("espelho  (pre-ordem): ");  TAB_imp_pre(e);  printf("\n\n");

    printf("original identado:\n");  TAB_imp_ident(a);  printf("\n");
    printf("espelho identado:\n");   TAB_imp_ident(e);

    TAB_libera(a);
    TAB_libera(e);
    return 0;
}
