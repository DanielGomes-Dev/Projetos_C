#include <stdio.h>
#include <stdlib.h>
#include "../../TG/TG.h"

/* ------------------------------------------------------------------ *
 * Q4) verificar se o grafo possui TODOS os nos com grau igual a k:
 *          int testek(TG *g, int k);
 *     (um grafo em que todo vertice tem o mesmo grau k e chamado de
 *      grafo k-REGULAR)
 *
 * O QUE E "GRAU DE UM NO"
 *   E o numero de arestas incidentes nele. Nesta representacao de
 *   lista de adjacencia, o grau do no e simplesmente o COMPRIMENTO
 *   da sua lista de vizinhos (prim_viz -> prox_viz -> ...).
 *
 * RACIOCINIO PASSO A PASSO
 *   1. Para cada no da lista de nos:
 *        a. conto quantos vizinhos ele tem  (grau);
 *        b. se esse grau for diferente de k, ja posso PARAR e
 *           devolver 0 (encontrei um contra-exemplo).
 *   2. Se percorri todos os nos sem achar divergencia, devolvo 1.
 *
 * DECISAO DE PROJETO PARA O GRAFO VAZIO
 *   Se g == NULL nao existe no que viole a condicao, entao
 *   testek(NULL, k) retorna 1 (verdadeiro por vacuidade).
 *
 * CUSTO: O(V + E).
 * ------------------------------------------------------------------ */

int testek(TG *g, int k) {
    for (TG *no = g; no != NULL; no = no->prox_no) {
        int grau = 0;
        for (TVIZ *v = no->prim_viz; v != NULL; v = v->prox_viz)
            grau++;
        if (grau != k)          /* achei um no fora do padrao         */
            return 0;
    }
    return 1;                    /* todos os nos tem grau k            */
}

/* ---- exemplo A: ciclo 1-2-3-4-1  -> 2-regular -------------------- *
 *        1 --- 2
 *        |     |
 *        4 --- 3
 * ---------------------------------------------------------------- */
static TG *ciclo4(void) {
    TG *g = TG_inicializa();
    for (int i = 4; i >= 1; i--)
        g = TG_ins_no(g, i);
    TG_ins_aresta(g, 1, 2);
    TG_ins_aresta(g, 2, 3);
    TG_ins_aresta(g, 3, 4);
    TG_ins_aresta(g, 4, 1);
    return g;
}

int main(void) {
    TG *g = ciclo4();

    printf("Grafo (ciclo de 4 nos):\n");
    TG_imprime(g);

    printf("\ntestek(g, 2) = %d  (esperado: 1  -> todos tem grau 2)\n", testek(g, 2));
    printf("testek(g, 3) = %d  (esperado: 0)\n", testek(g, 3));

    /* ao adicionar a diagonal 1-3, os nos 1 e 3 passam a grau 3 e os
     * nos 2 e 4 continuam com grau 2 -> deixa de ser regular         */
    TG_ins_aresta(g, 1, 3);
    printf("\napos adicionar aresta 1-3 (grafo deixa de ser regular):\n");
    printf("testek(g, 2) = %d  (esperado: 0)\n", testek(g, 2));
    printf("testek(g, 3) = %d  (esperado: 0)\n", testek(g, 3));

    printf("\ntestek(grafo vazio, 0) = %d  (esperado: 1, por vacuidade)\n", testek(NULL, 0));

    TG_libera(g);
    return 0;
}
