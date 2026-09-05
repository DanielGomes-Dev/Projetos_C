#include <stdio.h>
#include <stdlib.h>
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * Q5) Crie uma funcao em C que remova todas as ocorrencias de um
 * elemento numa lista.
 *     Prototipo: TLSE* rto (TLSE* l, int elem).
 *
 * Enquanto TLSE_busca ainda encontrar o elemento, chama TLSE_retira
 * (que remove a primeira ocorrencia).
 * ------------------------------------------------------------------ */

static TLSE *cria_lista(const int *v, int n) {
    TLSE *l = TLSE_inicializa();
    for (int i = n - 1; i >= 0; i--)
        l = TLSE_insere(l, v[i]);
    return l;
}

TLSE *rto(TLSE *l, int elem) {
    while (TLSE_busca(l, elem) != NULL)
        l = TLSE_retira(l, elem);
    return l;
}

int main(void) {
    int v[] = {1, 7, 3, 7, 7, 2, 7};
    TLSE *l = cria_lista(v, 7);

    printf("antes : ");  TLSE_imprime(l);  printf("\n");
    l = rto(l, 7);
    printf("depois: ");  TLSE_imprime(l);  printf("\n");

    TLSE_libera(l);
    return 0;
}
