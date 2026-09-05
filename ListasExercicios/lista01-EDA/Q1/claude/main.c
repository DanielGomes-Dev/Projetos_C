#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q1) copia de uma arvore: TAB* copia (TAB *a);
 *
 * Percorre em pre-ordem criando, com TAB_cria, um no novo para cada
 * no da original e ligando as copias das sub-arvores. A arvore
 * recebida nao e modificada.
 * ------------------------------------------------------------------ */

TAB *copia(TAB *a) {
    if (!a)
        return NULL;
    return TAB_cria(a->info, copia(a->esq), copia(a->dir));
}

/*        4
 *       / \
 *      2   6
 *     / \ / \
 *    1  3 5  7                                                       */
static TAB *exemplo(void) {
    return TAB_cria(4,
        TAB_cria(2, TAB_cria(1, NULL, NULL), TAB_cria(3, NULL, NULL)),
        TAB_cria(6, TAB_cria(5, NULL, NULL), TAB_cria(7, NULL, NULL)));
}

int main(void) {
    TAB *a = exemplo();
    TAB *c = copia(a);

    a->info = 99;                     /* mostra que a copia e independente */

    printf("original (simetrico): ");  TAB_imp_sim(a);  printf("\n");
    printf("copia    (simetrico): ");  TAB_imp_sim(c);  printf("\n");

    TAB_libera(a);
    TAB_libera(c);
    return 0;
}
