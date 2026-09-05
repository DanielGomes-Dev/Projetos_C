#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q6) retire todos os elementos pares da arvore original:
 *     TAB* retira_pares (TAB* arv);
 *
 * Processa primeiro as sub-arvores (assim, quando um no par e
 * removido, seus filhos ja estao limpos). Ao remover um no par:
 *   - sem filho esquerdo  -> sobe o filho direito;
 *   - com filho esquerdo  -> pendura a sub-arvore direita como
 *     descendente mais a direita da esquerda e sobe a esquerda.
 * Como a arvore e binaria qualquer, a ordem relativa nao importa.
 * ------------------------------------------------------------------ */

static TAB *anexa_a_direita(TAB *raiz, TAB *sub) {
    if (!raiz)
        return sub;
    TAB *p = raiz;
    while (p->dir)
        p = p->dir;
    p->dir = sub;
    return raiz;
}

TAB *retira_pares(TAB *arv) {
    if (!arv)
        return NULL;

    arv->esq = retira_pares(arv->esq);
    arv->dir = retira_pares(arv->dir);

    if (arv->info % 2 == 0) {
        TAB *e = arv->esq, *d = arv->dir;
        free(arv);
        return anexa_a_direita(e, d);
    }
    return arv;
}

/*        4
 *       / \
 *      2   7
 *     / \   \
 *    1  3    8
 *           /
 *          5                                                         */
static TAB *exemplo(void) {
    return TAB_cria(4,
        TAB_cria(2, TAB_cria(1, NULL, NULL), TAB_cria(3, NULL, NULL)),
        TAB_cria(7, NULL, TAB_cria(8, TAB_cria(5, NULL, NULL), NULL)));
}

int main(void) {
    TAB *a = exemplo();

    printf("antes  (pre-ordem): ");  TAB_imp_pre(a);  printf("\n");
    a = retira_pares(a);
    printf("depois (pre-ordem): ");  TAB_imp_pre(a);  printf("\n");
    printf("depois (simetrico): ");  TAB_imp_sim(a);  printf("\n");

    TAB_libera(a);
    return 0;
}
