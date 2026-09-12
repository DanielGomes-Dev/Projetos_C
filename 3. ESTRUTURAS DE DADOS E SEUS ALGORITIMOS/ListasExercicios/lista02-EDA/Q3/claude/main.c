#include <stdio.h>
#include <stdlib.h>
#include "../../TABB/TABB.h"

/* ------------------------------------------------------------------ *
 * Q3) retire todos os elementos impares da arvore original:
 *     TABB* retira_impares (TABB* a);
 *
 * Como remover durante a travessia bagunca a arvore, primeiro
 * coletamos os valores impares num vetor (percurso simetrico) e
 * depois chamamos TABB_retira para cada um deles.
 * ------------------------------------------------------------------ */

static int conta(TABB *a) {
    return a ? 1 + conta(a->esq) + conta(a->dir) : 0;
}

static int coleta_impares(TABB *a, int *v, int i) {
    if (!a)
        return i;
    i = coleta_impares(a->esq, v, i);
    if (a->info % 2 != 0)
        v[i++] = a->info;
    i = coleta_impares(a->dir, v, i);
    return i;
}

TABB *retira_impares(TABB *a) {
    int n = conta(a);
    if (n == 0)
        return a;

    int *v = malloc(sizeof(int) * n);
    int k = coleta_impares(a, v, 0);
    for (int j = 0; j < k; j++)
        a = TABB_retira(a, v[j]);
    free(v);
    return a;
}

static TABB *exemplo(void) {
    int v[] = {50, 31, 70, 20, 45, 63, 80, 12, 27};
    TABB *a = TABB_inicializa();
    for (int i = 0; i < 9; i++)
        a = TABB_insere(a, v[i]);
    return a;
}

int main(void) {
    TABB *a = exemplo();

    printf("antes  (simetrico): ");  TABB_imp_sim(a);  printf("\n");
    a = retira_impares(a);
    printf("depois (simetrico): ");  TABB_imp_sim(a);  printf("\n");

    TABB_libera(a);
    return 0;
}
