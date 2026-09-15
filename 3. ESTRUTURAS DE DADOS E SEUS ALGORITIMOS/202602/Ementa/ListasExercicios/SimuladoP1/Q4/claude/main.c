#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * (4) Faca uma funcao que verifique se uma arvore binaria de busca
 * segue o padrao AVL.
 *     Prototipo: int eh_avl(TAB *a);
 *
 * REGRA AVL: para TODO no da arvore, o FATOR DE BALANCEAMENTO (FB) =
 * altura(esq) - altura(dir) tem que estar em {-1, 0, 1}.
 *
 * RACIOCINIO (uma so passada, sem recalcular altura repetidas vezes)
 *   Se eu calculasse a altura de cada no chamando TAB_altura (que ja
 *   existe pronta) separadamente para cada no, o custo total seria
 *   O(n^2) (a altura de cada no percorre a subarvore inteira de novo).
 *
 *   Em vez disso, uma unica funcao recursiva devolve DUAS informacoes
 *   ao mesmo tempo: "esta subarvore e AVL?" e "qual a altura dela?".
 *   Uso um "codigo de erro" (-2) na propria altura para propagar o
 *   "nao e AVL" para cima sem precisar de uma struct/par de retorno:
 *   assim que UM no viola a regra, a resposta -2 sobe e contamina
 *   todos os niveis acima (que so repassam -2 adiante, sem mais
 *   checar nada).
 *
 * CUSTO: O(n) - cada no e visitado uma unica vez.
 * ------------------------------------------------------------------ */

static int maior(int x, int y) { return (x >= y) ? x : y; }

static int altura_ou_erro(TAB *a) {
    if (!a) return -1;                  /* mesma convencao de TAB_altura */

    int alt_esq = altura_ou_erro(a->esq);
    int alt_dir = altura_ou_erro(a->dir);
    if (alt_esq == -2 || alt_dir == -2) return -2;   /* erro ja veio de baixo */

    int fb = alt_esq - alt_dir;
    if (fb > 1 || fb < -1) return -2;   /* este no viola a regra AVL */

    return 1 + maior(alt_esq, alt_dir);
}

int eh_avl(TAB *a) {
    return altura_ou_erro(a) != -2;
}

/* ---- exemplo 1: balanceada (esperado: 1) ----------------------------
 *              20
 *            /    \
 *          10      30
 *         /  \
 *        5   15
 * ------------------------------------------------------------------ */
static TAB *exemplo_avl(void) {
    TAB *esq = TAB_cria(10, TAB_cria(5, NULL, NULL), TAB_cria(15, NULL, NULL));
    TAB *dir = TAB_cria(30, NULL, NULL);
    return TAB_cria(20, esq, dir);
}

/* ---- exemplo 2: degenerada em lista, FB(20) = 2 (esperado: 0) ------
 *      20
 *     /
 *    10
 *   /
 *  5
 * ------------------------------------------------------------------ */
static TAB *exemplo_nao_avl(void) {
    TAB *n10 = TAB_cria(10, TAB_cria(5, NULL, NULL), NULL);
    return TAB_cria(20, n10, NULL);
}

int main(void) {
    TAB *a = exemplo_avl();
    TAB *b = exemplo_nao_avl();

    printf("eh_avl(a) = %d  (esperado: 1)\n", eh_avl(a));
    printf("eh_avl(b) = %d  (esperado: 0)\n", eh_avl(b));
    printf("eh_avl(NULL) = %d  (esperado: 1)\n", eh_avl(NULL));

    TAB_libera(a);
    TAB_libera(b);
    return 0;
}
