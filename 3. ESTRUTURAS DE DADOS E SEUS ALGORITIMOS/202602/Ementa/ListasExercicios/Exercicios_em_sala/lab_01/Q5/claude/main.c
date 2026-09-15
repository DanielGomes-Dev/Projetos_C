#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q5) Retorne o no de MAIOR NIVEL que e ancestral tanto de N quanto
 * de M (o "ancestral comum mais profundo" dos dois valores).
 *     Prototipo: TAB *maior_nivel(TAB *a, int N, int M).
 *
 * Como e uma arvore binaria QUALQUER (nao BST), nao ha como decidir
 * "vai para esquerda ou direita" olhando so os valores - precisa
 * achar os dois de verdade.
 *
 * ESTRATEGIA (comparar os dois caminhos raiz->no)
 *   1. Acho o caminho da raiz ate o no com valor N, guardando os
 *      ponteiros visitados numa pilha (vetor).
 *   2. Faco o mesmo para M, noutra pilha.
 *   3. Os dois caminhos comecam iguais na raiz. Ando pelas duas
 *      pilhas em paralelo enquanto os ponteiros forem iguais; o
 *      ULTIMO ponto em que ainda sao iguais e o ancestral comum mais
 *      fundo (de maior nivel) - exatamente o que se pede.
 *
 * CUSTO: O(n) para cada busca de caminho + O(altura) para comparar =
 * O(n) no total.
 * ------------------------------------------------------------------ */

static int caminho(TAB *a, int elem, TAB **pilha, int *topo) {
    if (!a) return 0;
    pilha[*topo] = a;
    (*topo)++;
    if (a->info == elem) return 1;
    if (caminho(a->esq, elem, pilha, topo)) return 1;
    if (caminho(a->dir, elem, pilha, topo)) return 1;
    (*topo)--;             /* nao achou por aqui: desfaz a entrada na pilha */
    return 0;
}

TAB *maior_nivel(TAB *a, int N, int M) {
    int alt = TAB_altura(a);
    if (alt < 0) return NULL;
    int tamMax = alt + 2;

    TAB **pilhaN = (TAB **) malloc(tamMax * sizeof(TAB *));
    TAB **pilhaM = (TAB **) malloc(tamMax * sizeof(TAB *));
    int topoN = 0, topoM = 0;

    TAB *resp = NULL;
    if (caminho(a, N, pilhaN, &topoN) && caminho(a, M, pilhaM, &topoM)) {
        int i = 0;
        while (i < topoN && i < topoM && pilhaN[i] == pilhaM[i]) {
            resp = pilhaN[i];
            i++;
        }
    }

    free(pilhaN);
    free(pilhaM);
    return resp;
}

/* ---- mesma arvore de exemplo da Q1/Q2 ------------------------------
 *              130
 *            /      \
 *          100       200
 *         /   \     /   \
 *       83    120  150  230
 * -------------------------------------------------------------------
 *   maior_nivel(a, 83, 120)  -> 100 (nivel 1: pai comum direto)
 *   maior_nivel(a, 83, 230)  -> 130 (raiz: ficam em ramos diferentes)
 *   maior_nivel(a, 100, 83)  -> 100 (83 e descendente de 100)
 * ------------------------------------------------------------------ */
static TAB *exemplo(void) {
    TAB *esq = TAB_cria(100, TAB_cria(83, NULL, NULL), TAB_cria(120, NULL, NULL));
    TAB *dir = TAB_cria(200, TAB_cria(150, NULL, NULL), TAB_cria(230, NULL, NULL));
    return TAB_cria(130, esq, dir);
}

int main(void) {
    TAB *a = exemplo();

    TAB *r1 = maior_nivel(a, 83, 120);
    printf("maior_nivel(a, 83, 120) = %d  (esperado: 100)\n", r1 ? r1->info : -1);

    TAB *r2 = maior_nivel(a, 83, 230);
    printf("maior_nivel(a, 83, 230) = %d  (esperado: 130)\n", r2 ? r2->info : -1);

    TAB *r3 = maior_nivel(a, 100, 83);
    printf("maior_nivel(a, 100, 83) = %d  (esperado: 100)\n", r3 ? r3->info : -1);

    TAB_libera(a);
    return 0;
}
