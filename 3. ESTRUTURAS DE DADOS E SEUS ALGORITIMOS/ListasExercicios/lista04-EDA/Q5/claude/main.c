#include <stdio.h>
#include <stdlib.h>
#include "../../TG/TG.h"

/* ------------------------------------------------------------------ *
 * Q5) testar se dois grafos sao IGUAIS: int ig(TG *g1, TG *g2);
 *
 * O QUE SIGNIFICA "IGUAIS" AQUI
 *   Nao e isomorfismo (problema dificil). E igualdade "rotulada":
 *   os dois grafos tem exatamente o MESMO conjunto de ids de nos e,
 *   para cada no, exatamente o MESMO conjunto de vizinhos.
 *   A ORDEM em que nos e vizinhos aparecem nas listas NAO importa
 *   (as funcoes de insercao poem no inicio da lista, entao dois
 *   grafos "iguais" podem ter listas em ordens diferentes).
 *
 * ESTRATEGIA (dupla inclusao, usando o tamanho para fechar)
 *   1. Se o numero de nos difere -> nao sao iguais (0).
 *   2. Para cada no u de g1:
 *        a. procuro em g2 um no com o mesmo id (TG_busca_no).
 *           Se nao existe -> 0.
 *        b. para cada vizinho w de u, verifico que a aresta {u,w}
 *           tambem existe em g2 (TG_busca_aresta). Se falta uma -> 0.
 *        c. comparo os GRAUS dos dois nos. Como todo vizinho de u ja
 *           foi confirmado em g2, se os graus sao iguais entao os
 *           conjuntos de vizinhos sao identicos.
 *   3. Passo 1 garante |V(g1)| == |V(g2)|, e o passo 2 garante
 *      V(g1) subconjunto de V(g2); juntos => os conjuntos de nos
 *      sao iguais. Retorno 1.
 *
 * CUSTO: O(V1 * (V2 + E2)) por causa das buscas; suficiente para a
 *        escala destes exercicios.
 * ------------------------------------------------------------------ */

static int nn(TG *g) {
    int n = 0;
    for (; g; g = g->prox_no) n++;
    return n;
}

static int grau(TG *no) {
    int d = 0;
    for (TVIZ *v = no->prim_viz; v; v = v->prox_viz) d++;
    return d;
}

int ig(TG *g1, TG *g2) {
    if (nn(g1) != nn(g2))                       /* passo 1            */
        return 0;

    for (TG *u = g1; u != NULL; u = u->prox_no) {
        TG *u2 = TG_busca_no(g2, u->id_no);     /* passo 2a          */
        if (!u2)
            return 0;

        for (TVIZ *w = u->prim_viz; w != NULL; w = w->prox_viz)
            if (!TG_busca_aresta(g2, u->id_no, w->id_viz))  /* 2b    */
                return 0;

        if (grau(u) != grau(u2))               /* passo 2c          */
            return 0;
    }
    return 1;
}

/* ---- monta um grafo a partir de listas de nos e de arestas ------ */
static TG *monta(const int *nos, int qn, const int arestas[][2], int qa) {
    TG *g = TG_inicializa();
    for (int i = 0; i < qn; i++)
        g = TG_ins_no(g, nos[i]);
    for (int i = 0; i < qa; i++)
        TG_ins_aresta(g, arestas[i][0], arestas[i][1]);
    return g;
}

int main(void) {
    int nos[]        = {1, 2, 3, 4};
    int arestasA[][2] = {{1, 2}, {2, 3}, {3, 4}};
    int arestasB[][2] = {{3, 4}, {1, 2}, {2, 3}};   /* mesmas arestas, outra ordem */
    int arestasC[][2] = {{1, 2}, {2, 3}, {3, 4}, {1, 4}}; /* uma aresta a mais */

    TG *A = monta(nos, 4, arestasA, 3);
    TG *B = monta(nos, 4, arestasB, 3);
    TG *C = monta(nos, 4, arestasC, 4);

    printf("Grafo A:\n"); TG_imprime(A);
    printf("\nGrafo B (mesmas arestas de A, inseridas noutra ordem):\n"); TG_imprime(B);
    printf("\nGrafo C (uma aresta a mais que A):\n"); TG_imprime(C);

    printf("\nig(A, B) = %d  (esperado: 1)\n", ig(A, B));
    printf("ig(A, C) = %d  (esperado: 0)\n", ig(A, C));
    printf("ig(A, A) = %d  (esperado: 1)\n", ig(A, A));

    TG_libera(A);
    TG_libera(B);
    TG_libera(C);
    return 0;
}
