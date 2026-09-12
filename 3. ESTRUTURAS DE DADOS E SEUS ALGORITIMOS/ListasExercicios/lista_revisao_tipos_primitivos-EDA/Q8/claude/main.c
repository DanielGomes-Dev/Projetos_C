#include <stdio.h>
#include <stdlib.h>
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * Q8) Dadas duas listas l1 e l2 encadeadas, verifique se sao iguais.
 * As listas devem permanecer inalteradas. Retorna 1 se iguais, 0
 * caso contrario.
 *     Prototipo: int igual (TLSE *l1, TLSE *l2).
 * ------------------------------------------------------------------ */

static TLSE *cria_lista(const int *v, int n) {
    TLSE *l = TLSE_inicializa();
    for (int i = n - 1; i >= 0; i--)
        l = TLSE_insere(l, v[i]);
    return l;
}

int igual(TLSE *l1, TLSE *l2) {
    while (l1 != NULL && l2 != NULL) {
        if (l1->info != l2->info)
            return 0;
        l1 = l1->prox;
        l2 = l2->prox;
    }
    return (l1 == NULL && l2 == NULL);
}

int main(void) {
    int va[] = {1, 2, 3, 4};
    int vb[] = {1, 2, 3, 4};
    int vc[] = {1, 2, 9, 4};
    int vd[] = {1, 2, 3};

    TLSE *a = cria_lista(va, 4);
    TLSE *b = cria_lista(vb, 4);
    TLSE *c = cria_lista(vc, 4);
    TLSE *d = cria_lista(vd, 3);

    printf("igual(a, b) = %d\n", igual(a, b));   /* 1 */
    printf("igual(a, c) = %d\n", igual(a, c));   /* 0 */
    printf("igual(a, d) = %d\n", igual(a, d));   /* 0 */

    TLSE_libera(a);
    TLSE_libera(b);
    TLSE_libera(c);
    TLSE_libera(d);
    return 0;
}
