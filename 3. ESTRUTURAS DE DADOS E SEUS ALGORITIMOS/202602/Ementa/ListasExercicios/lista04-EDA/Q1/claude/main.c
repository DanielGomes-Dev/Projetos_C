#include <stdio.h>
#include <stdlib.h>
#include "../../TG/TG.h"

/* ------------------------------------------------------------------ *
 * Q1) descubra a quantidade de nos: int nn(TG *g);
 *
 * REPRESENTACAO (ver TG.h)
 *   O grafo e uma LISTA LIGADA de nos (TG). Cada no aponta para o
 *   proximo no por 'prox_no' e para a sua lista de vizinhos por
 *   'prim_viz'. Portanto "contar os nos" e simplesmente contar
 *   quantos elementos existem na lista encadeada de nos.
 *
 * RACIOCINIO
 *   - Comeco com um contador em zero.
 *   - Enquanto o ponteiro 'g' nao for NULL, somo 1 e avanco para
 *     g->prox_no.
 *   - Quando 'g' chega a NULL percorri todos os nos: devolvo a soma.
 *
 * CUSTO: O(V), onde V e o numero de nos. Nao olho as arestas.
 * ------------------------------------------------------------------ */

int nn(TG *g) {
    int total = 0;
    while (g) {          /* enquanto houver no na lista de nos          */
        total++;        /* conta o no atual                            */
        g = g->prox_no; /* caminha para o proximo no                   */
    }
    return total;
}

/* ---- grafo de exemplo -------------------------------------------- *
 *   Nos: 1, 2, 3, 4, 5   (5 nos)
 *   Arestas: 1-2, 1-3, 2-3, 3-4, 4-5
 *
 *        1 --- 2
 *         \   /
 *          \ /
 *           3 --- 4 --- 5
 * ---------------------------------------------------------------- */
static TG *exemplo(void) {
    TG *g = TG_inicializa();
    for (int i = 5; i >= 1; i--)     /* insere 5,4,3,2,1 (ordem livre) */
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

    printf("\nQuantidade de nos (nn) = %d  (esperado: 5)\n", nn(g));

    /* casos-limite */
    printf("nn(grafo vazio)        = %d  (esperado: 0)\n", nn(NULL));

    TG_libera(g);
    return 0;
}
