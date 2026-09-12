#include <stdio.h>
#include <stdlib.h>
#include "../../TG/TG.h"

/* ------------------------------------------------------------------ *
 * Q2) ache a quantidade de arestas: int na(TG *g);
 *
 * IDEIA CENTRAL
 *   Este grafo e NAO-DIRECIONADO e armazenado com lista de
 *   adjacencia DUPLA: a aresta {u,v} aparece duas vezes,
 *   uma como vizinho v na lista de u e outra como vizinho u na
 *   lista de v (ver TG_ins_aresta em TG.c, que chama
 *   TG_ins_um_sentido nos dois sentidos).
 *
 *   Logo, se eu somar o GRAU de todos os nos (ou seja, o total de
 *   elementos em todas as listas de vizinhos), cada aresta e
 *   contada exatamente 2 vezes.
 *
 *          soma_dos_graus
 *   na  =  --------------
 *                2
 *
 * RACIOCINIO PASSO A PASSO
 *   1. Para cada no da lista de nos...
 *   2. ...percorro a sua lista de vizinhos incrementando 'soma'.
 *   3. No fim divido 'soma' por 2 (divisao inteira; a soma dos
 *      graus e sempre par num grafo nao-direcionado).
 *
 * CUSTO: O(V + E).
 * ------------------------------------------------------------------ */

int na(TG *g) {
    int soma = 0;
    for (TG *no = g; no != NULL; no = no->prox_no) {
        for (TVIZ *v = no->prim_viz; v != NULL; v = v->prox_viz)
            soma++;                 /* conta cada "meia-aresta"        */
    }
    return soma / 2;                /* cada aresta foi contada 2 vezes */
}

/* ---- grafo de exemplo (mesmo da Q1) ------------------------------ *
 *   Arestas: 1-2, 1-3, 2-3, 3-4, 4-5  ->  5 arestas
 * ---------------------------------------------------------------- */
static TG *exemplo(void) {
    TG *g = TG_inicializa();
    for (int i = 5; i >= 1; i--)
        g = TG_ins_no(g, i);
    TG_ins_aresta(g, 1, 2);
    TG_ins_aresta(g, 1, 3);
    TG_ins_aresta(g, 2, 3);
    TG_ins_aresta(g, 3, 4);
    TG_ins_aresta(g, 4, 5);
    return g;
}

int main(void) {
    TG *g = exemplo();

    printf("Lista de adjacencia do grafo:\n");
    TG_imprime(g);

    printf("\nQuantidade de arestas (na) = %d  (esperado: 5)\n", na(g));
    printf("na(grafo vazio)            = %d  (esperado: 0)\n", na(NULL));

    /* depois de retirar a aresta 2-3 devem sobrar 4 */
    TG_retira_aresta(g, 2, 3);
    printf("apos retirar aresta 2-3    = %d  (esperado: 4)\n", na(g));

    TG_libera(g);
    return 0;
}
