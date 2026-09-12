#include <stdio.h>
#include <stdlib.h>
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * Q9) Dadas duas listas, faca a concatenacao das mesmas ao final de
 * l1.
 *     Prototipo: TLSE* junta_listas (TLSE* l1, TLSE* l2).
 *
 * Se l1 for vazia, o resultado e l2. Senao, liga o ultimo no de l1
 * em l2.
 * ------------------------------------------------------------------ */

static TLSE *cria_lista(const int *v, int n) {
    TLSE *l = TLSE_inicializa();
    for (int i = n - 1; i >= 0; i--)
        l = TLSE_insere(l, v[i]);
    return l;
}

TLSE *junta_listas(TLSE *l1, TLSE *l2) {
    if (l1 == NULL)
        return l2;
    TLSE *p = l1;
    while (p->prox != NULL)
        p = p->prox;
    p->prox = l2;
    return l1;
}

int main(void) {
    int va[] = {1, 2, 3};
    int vb[] = {4, 5, 6};

    TLSE *l1 = cria_lista(va, 3);
    TLSE *l2 = cria_lista(vb, 3);

    printf("l1: ");  TLSE_imprime(l1);  printf("\n");
    printf("l2: ");  TLSE_imprime(l2);  printf("\n");

    l1 = junta_listas(l1, l2);
    printf("junta_listas(l1, l2): ");  TLSE_imprime(l1);  printf("\n");

    TLSE_libera(l1);                  /* libera l1 e l2 (agora encadeadas) */
    return 0;
}
