#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * (3) Faca uma funcao que verifique se TODAS as folhas de uma arvore
 * binaria estao no mesmo nivel.
 *     Prototipo: int mesmo_nivel(TAB *a);
 *
 * RACIOCINIO
 *   Percorro a arvore carregando o nivel atual. Toda vez que acho uma
 *   FOLHA (esq e dir ambos NULL), comparo o nivel dela com o nivel da
 *   PRIMEIRA folha encontrada:
 *     - se e a primeira folha, s so guardo o nivel dela como
 *       referencia;
 *     - se ja tinha uma folha de referencia, comparo - se for
 *       diferente, a resposta final e "nao" (0), nao importa o resto.
 *   Uso duas variaveis passadas por endereco (mesmo estilo de
 *   TLSE_insere_void: alterar o que o chamador enxerga) para levar
 *   esse estado por toda a recursao: 'nivel_ref' (nivel da 1a folha,
 *   -1 se ainda nao achei nenhuma) e 'ok' (vira 0 assim que acho uma
 *   folha em nivel diferente).
 *
 * CUSTO: O(n).
 * ------------------------------------------------------------------ */

static void verifica(TAB *a, int nivel, int *nivel_ref, int *ok) {
    if (!a || !(*ok)) return;
    if (!a->esq && !a->dir) {          /* e folha */
        if (*nivel_ref == -1) *nivel_ref = nivel;
        else if (*nivel_ref != nivel) *ok = 0;
        return;
    }
    verifica(a->esq, nivel + 1, nivel_ref, ok);
    verifica(a->dir, nivel + 1, nivel_ref, ok);
}

int mesmo_nivel(TAB *a) {
    int nivel_ref = -1, ok = 1;
    verifica(a, 0, &nivel_ref, &ok);
    return ok;
}

/* ---- exemplo 1: todas as folhas no nivel 2 (esperado: 1) ------------
 *              20
 *            /    \
 *          10      30
 *         /  \    /  \
 *        5   15  25   35
 * ------------------------------------------------------------------ */
static TAB *exemplo_ok(void) {
    TAB *esq = TAB_cria(10, TAB_cria(5, NULL, NULL), TAB_cria(15, NULL, NULL));
    TAB *dir = TAB_cria(30, TAB_cria(25, NULL, NULL), TAB_cria(35, NULL, NULL));
    return TAB_cria(20, esq, dir);
}

/* ---- exemplo 2: 30 e folha no nivel 1, o resto no nivel 2 (esperado: 0)
 *              20
 *            /    \
 *          10      30
 *         /  \
 *        5   15
 * ------------------------------------------------------------------ */
static TAB *exemplo_nok(void) {
    TAB *esq = TAB_cria(10, TAB_cria(5, NULL, NULL), TAB_cria(15, NULL, NULL));
    TAB *dir = TAB_cria(30, NULL, NULL);
    return TAB_cria(20, esq, dir);
}

int main(void) {
    TAB *a = exemplo_ok();
    TAB *b = exemplo_nok();

    printf("mesmo_nivel(a) = %d  (esperado: 1)\n", mesmo_nivel(a));
    printf("mesmo_nivel(b) = %d  (esperado: 0)\n", mesmo_nivel(b));
    printf("mesmo_nivel(NULL) = %d  (esperado: 1 - vacuosamente verdadeiro)\n", mesmo_nivel(NULL));

    TAB_libera(a);
    TAB_libera(b);
    return 0;
}
