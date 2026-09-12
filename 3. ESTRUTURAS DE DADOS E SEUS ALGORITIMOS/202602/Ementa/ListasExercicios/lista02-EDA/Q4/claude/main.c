#include <stdio.h>
#include <stdlib.h>
#include "../../TABB/TABB.h"

/* ------------------------------------------------------------------ *
 * Q4) retorne, num vetor, todos os elementos menores que N:
 *     int* mN (TABB* a, int N);
 *
 * Convencao do vetor devolvido: a posicao [0] guarda a QUANTIDADE de
 * elementos; as posicoes seguintes guardam os elementos < N em ordem
 * crescente (percurso simetrico). O chamador deve dar free() no
 * vetor.
 *
 * Poda: se o no >= N, nao adianta olhar a sub-arvore direita.
 * ------------------------------------------------------------------ */

static int conta(TABB *a) {
    return a ? 1 + conta(a->esq) + conta(a->dir) : 0;
}

static int coleta_menores(TABB *a, int N, int *v, int i) {
    if (!a)
        return i;
    i = coleta_menores(a->esq, N, v, i);
    if (a->info < N) {
        v[i++] = a->info;
        i = coleta_menores(a->dir, N, v, i);
    }
    return i;
}

int *mN(TABB *a, int N) {
    int n = conta(a);
    int *v = malloc(sizeof(int) * (n + 1));
    int k = coleta_menores(a, N, v + 1, 0);
    v[0] = k;
    return v;
}

static TABB *exemplo(void) {
    int v[] = {50, 30, 70, 20, 40, 60, 80, 25, 35, 45};
    TABB *a = TABB_inicializa();
    for (int i = 0; i < 10; i++)
        a = TABB_insere(a, v[i]);
    return a;
}

int main(void) {
    TABB *a = exemplo();
    int N = 42;

    printf("arvore (simetrico): ");  TABB_imp_sim(a);  printf("\n");

    int *r = mN(a, N);
    printf("elementos < %d (%d): ", N, r[0]);
    for (int i = 1; i <= r[0]; i++)
        printf("%d ", r[i]);
    printf("\n");

    free(r);
    TABB_libera(a);
    return 0;
}
