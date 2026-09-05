#include <stdio.h>
#include <stdlib.h>
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * Q4) Implemente uma funcao que copie uma lista. A lista original
 * deve permanecer inalterada.
 *     Prototipo: TLSE *copia (TLSE *l).
 *
 * Percorre a lista original criando um no novo para cada elemento
 * (TLSE_insere) e anexando ao final da copia, preservando a ordem.
 * ------------------------------------------------------------------ */

static TLSE *cria_lista(const int *v, int n) {
    TLSE *l = TLSE_inicializa();
    for (int i = n - 1; i >= 0; i--)
        l = TLSE_insere(l, v[i]);
    return l;
}

TLSE *copia(TLSE *l) {
    if (l == NULL)
        return NULL;

    TLSE *nova = TLSE_insere(NULL, l->info);
    TLSE *fim = nova;
    for (TLSE *p = l->prox; p != NULL; p = p->prox) {
        fim->prox = TLSE_insere(NULL, p->info);
        fim = fim->prox;
    }
    return nova;
}

int main(void) {
    int v[] = {1, 2, 3, 4, 5, 6};
    TLSE *l = cria_lista(v, 6);
    TLSE *c = copia(l);

    l->info = 99;                     /* mostra que a copia e independente */

    printf("original: ");  TLSE_imprime(l);  printf("\n");
    printf("copia   : ");  TLSE_imprime(c);  printf("\n");

    TLSE_libera(l);
    TLSE_libera(c);
    return 0;
}
