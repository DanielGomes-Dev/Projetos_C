#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q5) testa se duas arvores sao iguais: int igual (TAB* a1, TAB* a2);
 *
 * Retorna 1 se tem a mesma forma e os mesmos valores nas mesmas
 * posicoes; 0 caso contrario. Compara raiz a raiz e desce nos dois
 * lados.
 * ------------------------------------------------------------------ */

int igual(TAB *a1, TAB *a2) {
    if (!a1 && !a2)
        return 1;
    if (!a1 || !a2)
        return 0;
    return a1->info == a2->info
        && igual(a1->esq, a2->esq)
        && igual(a1->dir, a2->dir);
}

static TAB *arvore(int r) {
    return TAB_cria(r,
        TAB_cria(2, TAB_cria(1, NULL, NULL), NULL),
        TAB_cria(3, NULL, TAB_cria(4, NULL, NULL)));
}

int main(void) {
    TAB *a = arvore(10);
    TAB *b = arvore(10);            /* identica a "a" */
    TAB *c = arvore(99);            /* raiz diferente */
    TAB *d = TAB_cria(10, NULL, NULL);   /* forma diferente */

    printf("igual(a, b) = %d\n", igual(a, b));   /* 1 */
    printf("igual(a, c) = %d\n", igual(a, c));   /* 0 */
    printf("igual(a, d) = %d\n", igual(a, d));   /* 0 */

    TAB_libera(a);
    TAB_libera(b);
    TAB_libera(c);
    TAB_libera(d);
    return 0;
}
