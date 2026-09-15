#include <stdio.h>
#include <stdlib.h>
#include "../../TABB/TABB.h"

/* ------------------------------------------------------------------ *
 * Q3) Encontre todos os elementos MAIORES que N numa ABB e retorne-os
 * num vetor ordenado; NAO utilize nenhum algoritmo de ordenacao.
 *     Prototipo: int *maioresN(TABB *a, int N, int *tam_vet).
 *
 * O TRUQUE (por que nao precisa ordenar)
 *   Numa arvore binaria de busca (TABB), o percurso EM-ORDEM
 *   (esquerda, no, direita) ja visita os elementos em ordem
 *   CRESCENTE - essa e a propriedade central da BST. Entao basta
 *   fazer um percurso em-ordem e, ao visitar cada no, so guardar o
 *   valor no vetor de resposta se ele for > N. Como a visita ja e
 *   crescente, o vetor de saida sai ordenado de graca.
 *
 * RACIOCINIO
 *   - Vetor de resposta cresce dinamicamente (malloc/realloc), porque
 *     nao sei de antemao quantos elementos sao > N.
 *   - Percurso em-ordem: esquerda toda primeiro (valores menores),
 *     depois o proprio no, depois a direita (valores maiores).
 *
 * CUSTO: O(n) - visita cada no da BST uma vez.
 * ------------------------------------------------------------------ */

static void aux_maiores(TABB *a, int N, int **vet, int *tam, int *cap) {
    if (!a) return;
    aux_maiores(a->esq, N, vet, tam, cap);
    if (a->info > N) {
        if (*tam == *cap) {
            *cap *= 2;
            *vet = (int *) realloc(*vet, (*cap) * sizeof(int));
        }
        (*vet)[(*tam)++] = a->info;
    }
    aux_maiores(a->dir, N, vet, tam, cap);
}

int *maioresN(TABB *a, int N, int *tam_vet) {
    int cap = 4, tam = 0;
    int *vet = (int *) malloc(cap * sizeof(int));
    aux_maiores(a, N, &vet, &tam, &cap);
    *tam_vet = tam;
    return vet;
}

/* ---- BST de exemplo -----------------------------------------------
 *                 50
 *              /      \
 *            30        70
 *           /  \      /  \
 *         20    40   60   80
 * -------------------------------------------------------------------
 *   maioresN(a, 50) -> 60, 70, 80 (ja em ordem crescente)
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

    int *vet = maioresN(a, 50, &tam);
    printf("maioresN(a, 50) = ");
    for (int i = 0; i < tam; i++) printf("%d ", vet[i]);
    printf(" (esperado: 60 70 80)\n");
    free(vet);

    vet = maioresN(a, 100, &tam);
    printf("maioresN(a, 100) [nenhum] -> tam = %d  (esperado: 0)\n", tam);
    free(vet);

    TABB_libera(a);
    return 0;
}
