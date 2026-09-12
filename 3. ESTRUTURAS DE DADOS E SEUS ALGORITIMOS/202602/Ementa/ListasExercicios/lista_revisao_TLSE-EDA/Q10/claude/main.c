#include <stdio.h>
#include <stdlib.h>
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * Q10) Dadas duas listas l1 e l2 encadeadas, verifique se l1 e a
 * inversao de l2. As listas devem permanecer inalteradas. Retorna 1
 * se estao invertidas, 0 caso contrario.
 *     Prototipo: int Contrario (TLSE *l1, TLSE *l2).
 *
 * Gera a inversao de l2 numa lista nova e compara com l1.
 * ------------------------------------------------------------------ */

static TLSE *cria_lista(const int *v, int n) {
    TLSE *l = TLSE_inicializa();
    for (int i = n - 1; i >= 0; i--)
        l = TLSE_insere(l, v[i]);
    return l;
}

static TLSE *inverte_out(TLSE *l) {
    TLSE *saida = TLSE_inicializa();
    for (TLSE *p = l; p != NULL; p = p->prox)
        saida = TLSE_insere(saida, p->info);
    return saida;
}

static int igual(TLSE *l1, TLSE *l2) {
    while (l1 != NULL && l2 != NULL) {
        if (l1->info != l2->info)
            return 0;
        l1 = l1->prox;
        l2 = l2->prox;
    }
    return (l1 == NULL && l2 == NULL);
}

int Contrario(TLSE *l1, TLSE *l2) {
    TLSE *rev = inverte_out(l2);
    int r = igual(l1, rev);
    TLSE_libera(rev);
    return r;
}

int main(void) {
    int ve[] = {1, 2, 3, 4, 5, 6};
    int vf[] = {6, 5, 4, 3, 2, 1};
    int vg[] = {1, 2, 3};

    TLSE *e = cria_lista(ve, 6);
    TLSE *f = cria_lista(vf, 6);
    TLSE *g = cria_lista(vg, 3);

    printf("Contrario(f, e) = %d\n", Contrario(f, e));   /* 1 */
    printf("Contrario(g, e) = %d\n", Contrario(g, e));   /* 0 */

    TLSE_libera(e);
    TLSE_libera(f);
    TLSE_libera(g);
    return 0;
}
