#include <stdio.h>
#include <stdlib.h>
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * Q7) Refaca a Q6 alterando a lista passada como parametro.
 *     Prototipo: void i_p (TLSE *l).
 *
 * Calcula a sequencia desejada (impares depois pares, na ordem) numa
 * lista auxiliar e reescreve os campos info da lista recebida.
 * ------------------------------------------------------------------ */

static TLSE *cria_lista(const int *v, int n) {
    TLSE *l = TLSE_inicializa();
    for (int i = n - 1; i >= 0; i--)
        l = TLSE_insere(l, v[i]);
    return l;
}

static TLSE *anexa(TLSE *l, int elem) {
    TLSE *novo = TLSE_insere(NULL, elem);
    if (l == NULL)
        return novo;
    TLSE *p = l;
    while (p->prox != NULL)
        p = p->prox;
    p->prox = novo;
    return l;
}

void i_p(TLSE *l) {
    TLSE *aux = TLSE_inicializa();
    for (TLSE *p = l; p != NULL; p = p->prox)
        if (p->info % 2 != 0)
            aux = anexa(aux, p->info);
    for (TLSE *p = l; p != NULL; p = p->prox)
        if (p->info % 2 == 0)
            aux = anexa(aux, p->info);

    TLSE *q = aux;
    for (TLSE *p = l; p != NULL; p = p->prox, q = q->prox)
        p->info = q->info;

    TLSE_libera(aux);
}

int main(void) {
    int v[] = {1, 2, 3, 4, 5, 6};
    TLSE *l = cria_lista(v, 6);

    printf("antes : ");  TLSE_imprime(l);  printf("\n");
    i_p(l);
    printf("depois: ");  TLSE_imprime(l);  printf("\n");

    TLSE_libera(l);
    return 0;
}
