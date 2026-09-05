#include <stdio.h>
#include <stdlib.h>
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * Q12) Refaca a Q11 alterando a lista passada como parametro.
 *     Prototipo: void ordena (TLSE *l).
 *
 * Ordena a propria lista trocando os campos info (selection/bubble
 * sort sobre os nos existentes) - a estrutura de nos nao muda.
 * ------------------------------------------------------------------ */

static TLSE *cria_lista(const int *v, int n) {
    TLSE *l = TLSE_inicializa();
    for (int i = n - 1; i >= 0; i--)
        l = TLSE_insere(l, v[i]);
    return l;
}

void ordena(TLSE *l) {
    for (TLSE *i = l; i != NULL; i = i->prox)
        for (TLSE *j = i->prox; j != NULL; j = j->prox)
            if (j->info < i->info) {
                int t = i->info;
                i->info = j->info;
                j->info = t;
            }
}

int main(void) {
    int v[] = {4, 1, 7, 3, 9, 2};
    TLSE *l = cria_lista(v, 6);

    printf("antes : ");  TLSE_imprime(l);  printf("\n");
    ordena(l);
    printf("depois: ");  TLSE_imprime(l);  printf("\n");

    TLSE_libera(l);
    return 0;
}
