#include <stdio.h>
#include <stdlib.h>
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * Q11) Dada uma lista l qualquer, ordene os elementos de l em uma
 * OUTRA lista de saida. A lista de entrada nao pode ser alterada.
 *     Prototipo: TLSE * ordena (TLSE* l).
 *
 * Insercao ordenada: cada valor de l e inserido na posicao correta
 * da lista de saida (insere_ordenado, apoiada em TLSE_insere).
 * ------------------------------------------------------------------ */

static TLSE *cria_lista(const int *v, int n) {
    TLSE *l = TLSE_inicializa();
    for (int i = n - 1; i >= 0; i--)
        l = TLSE_insere(l, v[i]);
    return l;
}

static TLSE *insere_ordenado(TLSE *l, int elem) {
    if (l == NULL || elem <= l->info)
        return TLSE_insere(l, elem);
    l->prox = insere_ordenado(l->prox, elem);
    return l;
}

TLSE *ordena(TLSE *l) {
    TLSE *saida = TLSE_inicializa();
    for (TLSE *p = l; p != NULL; p = p->prox)
        saida = insere_ordenado(saida, p->info);
    return saida;
}

int main(void) {
    int v[] = {4, 1, 7, 3, 9, 2};
    TLSE *l = cria_lista(v, 6);
    TLSE *s = ordena(l);

    printf("entrada : ");  TLSE_imprime(l);  printf("\n");
    printf("ordenada: ");  TLSE_imprime(s);  printf("\n");

    TLSE_libera(l);
    TLSE_libera(s);
    return 0;
}
