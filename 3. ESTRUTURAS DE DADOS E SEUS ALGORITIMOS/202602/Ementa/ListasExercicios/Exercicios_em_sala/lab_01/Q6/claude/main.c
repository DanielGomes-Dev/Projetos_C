#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q6) Retorne o numero de caminhos que somam N numa arvore binaria
 * simples.
 *     Prototipo: int quant_caminhos(TAB *a, int N).
 *
 * INTERPRETACAO ADOTADA (o enunciado nao restringe raiz/folha)
 *   "Caminho" = qualquer sequencia de nos que desce de um no ate um
 *   descendente dele (pode comecar em QUALQUER no, nao so na raiz, e
 *   terminar em QUALQUER descendente, nao so numa folha). Um no
 *   sozinho tambem conta como caminho (de tamanho 1).
 *
 * ESTRATEGIA (duas funcoes, uma dentro da outra)
 *   - conta_a_partir(no, alvo): conta quantos caminhos que COMECAM
 *     exatamente em 'no' e descem daquele ponto somam 'alvo'. Vai
 *     subtraindo o valor do no do alvo a cada nivel que desce.
 *   - quant_caminhos(a, N): soma conta_a_partir(no, N) para TODO no
 *     da arvore (ou seja, tenta cada no como possivel inicio de
 *     caminho), percorrendo a arvore inteira.
 *
 * CUSTO: O(n^2) no pior caso (arvore degenerada em lista), porque para
 * cada no chamo conta_a_partir que desce ate o fim da arvore.
 * ------------------------------------------------------------------ */

static int conta_a_partir(TAB *a, int alvo) {
    if (!a) return 0;
    int conta = (a->info == alvo) ? 1 : 0;
    conta += conta_a_partir(a->esq, alvo - a->info);
    conta += conta_a_partir(a->dir, alvo - a->info);
    return conta;
}

int quant_caminhos(TAB *a, int N) {
    if (!a) return 0;
    return conta_a_partir(a, N)
         + quant_caminhos(a->esq, N)
         + quant_caminhos(a->dir, N);
}

/* ---- arvore de exemplo ---------------------------------------------
 *                10
 *              /    \
 *             5      -3
 *           /   \       \
 *          3     2       11
 *         / \      \
 *        3  -2      1
 * -------------------------------------------------------------------
 *   Caminhos que somam 8:
 *     5 -> 3            (5+3=8)
 *     5 -> 2 -> 1        (5+2+1=8)
 *     -3 -> 11           (-3+11=8)
 *   Total esperado: 3
 * ------------------------------------------------------------------ */
static TAB *exemplo(void) {
    TAB *n3a = TAB_cria(3, NULL, NULL);
    TAB *n_menos2 = TAB_cria(-2, NULL, NULL);
    TAB *n3b = TAB_cria(3, n3a, n_menos2);

    TAB *n1 = TAB_cria(1, NULL, NULL);
    TAB *n2 = TAB_cria(2, NULL, n1);

    TAB *n5 = TAB_cria(5, n3b, n2);

    TAB *n11 = TAB_cria(11, NULL, NULL);
    TAB *n_menos3 = TAB_cria(-3, NULL, n11);

    return TAB_cria(10, n5, n_menos3);
}

int main(void) {
    TAB *a = exemplo();

    printf("Arvore (identada):\n");
    TAB_imp_ident(a);

    printf("\nquant_caminhos(a, 8) = %d  (esperado: 3)\n", quant_caminhos(a, 8));
    printf("quant_caminhos(a, 100) = %d  (esperado: 0)\n", quant_caminhos(a, 100));

    TAB_libera(a);
    return 0;
}
