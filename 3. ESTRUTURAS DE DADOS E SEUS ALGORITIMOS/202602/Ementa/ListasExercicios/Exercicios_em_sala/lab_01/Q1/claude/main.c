#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q1) Some todos os elementos de nivel impar de uma arvore binaria
 * simples e subtraia todos os de nivel par.
 *     Prototipo: int misc1(TAB *a).
 *
 * CONVENCAO DE NIVEL (igual a Teoria 05 do subtopico 1.1): a raiz esta
 * no nivel 0 (par). Entao:
 *   resultado = (soma dos elementos em nivel impar) - (soma dos
 *               elementos em nivel par, incluindo a raiz)
 *
 * RACIOCINIO
 *   Percorro a arvore (pre-ordem, tanto faz a ordem) carregando o
 *   nivel atual como parametro extra. Em cada no, se o nivel for par
 *   subtraio a->info do total; se for impar, somo. Nivel do filho =
 *   nivel do pai + 1.
 *
 * CUSTO: O(n), visita cada no uma vez.
 * ------------------------------------------------------------------ */

static int misc1_aux(TAB *a, int nivel) {
    if (!a) return 0;
    int contrib = (nivel % 2 == 0) ? -a->info : a->info;
    return contrib + misc1_aux(a->esq, nivel + 1) + misc1_aux(a->dir, nivel + 1);
}

int misc1(TAB *a) {
    return misc1_aux(a, 0);
}

/* ---- arvore de exemplo (mesma da Teoria 05 - Percurso em largura) - *
 *              130
 *            /      \
 *          100       200
 *         /   \     /   \
 *       83    120  150  230
 * -------------------------------------------------------------------
 *   nivel 0 (par):   130                    -> soma = 130
 *   nivel 1 (impar): 100, 200                -> soma = 300
 *   nivel 2 (par):   83, 120, 150, 230       -> soma = 583
 *   misc1 = 300 - 130 - 583 = -413
 * ------------------------------------------------------------------ */
static TAB *exemplo(void) {
    TAB *esq = TAB_cria(100, TAB_cria(83, NULL, NULL), TAB_cria(120, NULL, NULL));
    TAB *dir = TAB_cria(200, TAB_cria(150, NULL, NULL), TAB_cria(230, NULL, NULL));
    return TAB_cria(130, esq, dir);
}

int main(void) {
    TAB *a = exemplo();

    printf("Arvore (identada):\n");
    TAB_imp_ident(a);

    printf("\nmisc1(a) = %d  (esperado: -413)\n", misc1(a));
    printf("misc1(NULL) = %d  (esperado: 0)\n", misc1(NULL));

    TAB_libera(a);
    return 0;
}
