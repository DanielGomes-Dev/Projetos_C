#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * (2) Faca uma funcao que verifique se uma arvore binaria e simetrica
 * (a subarvore esquerda e o ESPELHO da subarvore direita).
 *     Prototipo: int eh_simetrica(TAB *a);
 *
 * RACIOCINIO
 *   Uma arvore e simetrica quando, comparando a subarvore esquerda com
 *   a direita "de fora para dentro", cada par de nos espelhados tem o
 *   mesmo valor e seus filhos tambem sao espelhados entre si - so que
 *   TROCADOS: o esquerdo de um corresponde ao direito do outro.
 *
 *   Uma funcao auxiliar compara DOIS ponteiros que devem ser espelho
 *   um do outro:
 *     - ambos NULL -> espelhados (caso base ok)
 *     - so um NULL -> nao espelhados
 *     - valores diferentes -> nao espelhados
 *     - senao: (esq->esq espelha dir->dir) E (esq->dir espelha dir->esq)
 *
 * CUSTO: O(n) - cada no e visitado uma vez.
 * ------------------------------------------------------------------ */

static int espelhados(TAB *e, TAB *d) {
    if (!e && !d) return 1;
    if (!e || !d) return 0;
    if (e->info != d->info) return 0;
    return espelhados(e->esq, d->dir) && espelhados(e->dir, d->esq);
}

int eh_simetrica(TAB *a) {
    if (!a) return 1;                  /* arvore vazia e simetrica */
    return espelhados(a->esq, a->dir);
}

/* ---- exemplo do proprio enunciado (arvore simetrica) ----------------
 *              20
 *            /    \
 *          10      10
 *         /  \    /  \
 *        1    9  9    1
 * ------------------------------------------------------------------ */
static TAB *exemplo_simetrica(void) {
    TAB *esq = TAB_cria(10, TAB_cria(1, NULL, NULL), TAB_cria(9, NULL, NULL));
    TAB *dir = TAB_cria(10, TAB_cria(9, NULL, NULL), TAB_cria(1, NULL, NULL));
    return TAB_cria(20, esq, dir);
}

/* ---- variacao NAO simetrica (mesmos valores, filhos nao trocados) --- */
static TAB *exemplo_assimetrica(void) {
    TAB *esq = TAB_cria(10, TAB_cria(1, NULL, NULL), TAB_cria(9, NULL, NULL));
    TAB *dir = TAB_cria(10, TAB_cria(1, NULL, NULL), TAB_cria(9, NULL, NULL));
    return TAB_cria(20, esq, dir);
}

int main(void) {
    TAB *a = exemplo_simetrica();
    TAB *b = exemplo_assimetrica();

    printf("eh_simetrica(a) = %d  (esperado: 1)\n", eh_simetrica(a));
    printf("eh_simetrica(b) = %d  (esperado: 0)\n", eh_simetrica(b));
    printf("eh_simetrica(NULL) = %d  (esperado: 1)\n", eh_simetrica(NULL));

    TAB_libera(a);
    TAB_libera(b);
    return 0;
}
