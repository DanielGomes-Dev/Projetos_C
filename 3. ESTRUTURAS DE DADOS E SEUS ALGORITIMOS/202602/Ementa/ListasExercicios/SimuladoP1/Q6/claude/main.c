#include <stdio.h>
#include <stdlib.h>
#include "../../TG/TG.h"
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * (6) Faca uma funcao que encontre UM caminho entre dois vertices de
 * um grafo.
 *     Prototipo: TLSE* caminho(TG *g, int origem, int destino);
 *
 * Identico ao Q2 do lab_02 (Exercicios_em_sala): DFS guardando os
 * visitados numa TLSE compartilhada via TLSE_insere_void (precisa ser
 * compartilhada entre chamadas irmãs, senao um ramo pode revisitar no
 * que outro ramo ja visitou). Ao achar o destino, "desenrola" a
 * recursao colando cada no no INICIO da lista que a chamada de baixo
 * devolveu - assim o caminho final sai na ordem origem -> ... -> destino.
 *
 * CUSTO: O(V + E).
 * ------------------------------------------------------------------ */

static TLSE *dfs(TG *g, int atual, int destino, TLSE **visitados) {
    if (atual == destino)
        return TLSE_insere(TLSE_inicializa(), atual);

    TLSE_insere_void(visitados, atual);

    TG *no = TG_busca_no(g, atual);
    for (TVIZ *v = no->prim_viz; v; v = v->prox_viz) {
        if (!TLSE_busca(*visitados, v->id_viz)) {
            TLSE *resto = dfs(g, v->id_viz, destino, visitados);
            if (resto) return TLSE_insere(resto, atual);
        }
    }
    return NULL;
}

TLSE *caminho(TG *g, int origem, int destino) {
    if ((!TG_busca_no(g, origem)) || (!TG_busca_no(g, destino))) return NULL;

    TLSE *visitados = TLSE_inicializa();
    TLSE *resp = dfs(g, origem, destino, &visitados);
    TLSE_libera(visitados);
    return resp;
}

/* ---- grafo de exemplo -------------------------------------------- *
 *   0 -- 1
 *   |    |
 *   2 -- 3
 * ------------------------------------------------------------------ */
static TG *exemplo(void) {
    TG *g = TG_inicializa();
    for (int i = 3; i >= 0; i--) g = TG_ins_no(g, i);
    TG_ins_aresta(g, 0, 1);
    TG_ins_aresta(g, 0, 2);
    TG_ins_aresta(g, 1, 3);
    TG_ins_aresta(g, 2, 3);
    return g;
}

int main(void) {
    TG *g = exemplo();
    printf("Grafo:\n");
    TG_imprime(g);

    TLSE *c = caminho(g, 0, 3);
    printf("\ncaminho(g, 0, 3) = ");
    TLSE_imprime(c);
    printf(" (um caminho valido de 0 a 3)\n");
    TLSE_libera(c);

    TLSE *c2 = caminho(g, 0, 99);
    printf("caminho(g, 0, 99) [99 nao existe] = %s  (esperado: NULL)\n",
           c2 ? "NAO-NULL (erro)" : "NULL");

    TG_libera(g);
    return 0;
}
