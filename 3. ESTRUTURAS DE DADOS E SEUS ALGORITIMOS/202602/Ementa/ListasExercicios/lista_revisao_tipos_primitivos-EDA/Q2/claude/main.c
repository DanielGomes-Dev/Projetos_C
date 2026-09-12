#include <stdio.h>
#include <stdlib.h>
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * Q2) Refaca a Q1 invertendo os elementos de l em uma OUTRA lista de
 * saida. A lista de entrada nao pode ser alterada.
 *     Prototipo: TLSE* inverte (TLSE* l).
 *
 * Basta percorrer l do inicio ao fim inserindo sempre no inicio da
 * lista de saida (TLSE_insere), o que ja produz a lista invertida.
 * ------------------------------------------------------------------ */

static TLSE *cria_lista(const int *v, int n) {
    TLSE *l = TLSE_inicializa();
    for (int i = n - 1; i >= 0; i--)
        l = TLSE_insere(l, v[i]);
    return l;
}

TLSE *inverte(TLSE *l) {
    TLSE *saida = TLSE_inicializa();
    for (TLSE *p = l; p != NULL; p = p->prox)
        saida = TLSE_insere(saida, p->info);
    return saida;
}

int main(void) {
    int v[] = {1, 2, 3, 4, 5, 6};
    TLSE *l = cria_lista(v, 6);
    TLSE *s = inverte(l);

    printf("entrada: ");  TLSE_imprime(l);  printf("\n");
    printf("saida  : ");  TLSE_imprime(s);  printf("\n");

    TLSE_libera(l);
    TLSE_libera(s);
    return 0;
}
