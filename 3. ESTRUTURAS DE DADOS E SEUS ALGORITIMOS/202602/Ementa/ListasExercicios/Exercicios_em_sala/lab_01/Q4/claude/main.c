#include <stdio.h>
#include <stdlib.h>
#include "../../TABB/TABB.h"

/* ------------------------------------------------------------------ *
 * Q4) Encontre todos os elementos MENORES que N numa ABB e retorne-os
 * num vetor ordenado; NAO utilize nenhum algoritmo de ordenacao.
 *     Prototipo: int *menoresN(TABB *a, int N, int *tam_vet).
 *
 * Espelho exato da Q3: mesmo truque (em-ordem de BST ja sai
 * crescente), so muda o filtro para a->info < N.
 * ------------------------------------------------------------------ */

static void aux_menores(TABB *a, int N, int **vet, int *tam, int *cap) {
    if (!a) return;
    aux_menores(a->esq, N, vet, tam, cap);
    if (a->info < N) {
        if (*tam == *cap) {
            *cap *= 2;
            *vet = (int *) realloc(*vet, (*cap) * sizeof(int));
        }
        (*vet)[(*tam)++] = a->info;
    }
    aux_menores(a->dir, N, vet, tam, cap);
}

int *menoresN(TABB *a, int N, int *tam_vet) {
    int cap = 4, tam = 0;
    int *vet = (int *) malloc(cap * sizeof(int));
    aux_menores(a, N, &vet, &tam, &cap);
    *tam_vet = tam;
    return vet;
}

/* ---- mesma BST de exemplo da Q3 -----------------------------------
 *   menoresN(a, 50) -> 20, 30, 40 (ja em ordem crescente)
 * ------------------------------------------------------------------ */
static TABB *exemplo(void) {
    TABB *a = TABB_inicializa();
    int v[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) a = TABB_insere(a, v[i]);
    return a;
}

int main(void) {
    TABB *a = exemplo();
    int tam;

    int *vet = menoresN(a, 50, &tam);
    printf("menoresN(a, 50) = ");
    for (int i = 0; i < tam; i++) printf("%d ", vet[i]);
    printf(" (esperado: 20 30 40)\n");
    free(vet);

    vet = menoresN(a, 0, &tam);
    printf("menoresN(a, 0) [nenhum] -> tam = %d  (esperado: 0)\n", tam);
    free(vet);

    TABB_libera(a);
    return 0;
}
