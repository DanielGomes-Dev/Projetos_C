#include <stdio.h>
#include <stdlib.h>
#include "../../TG/TG.h"
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * (2) Dados um grafo e dois nos (x e y), retorne um caminho arbitrario
 * entre x e y. Se nao houver caminho, o retorno e NULL.
 *     Prototipo: TLSE *caminho(TG *g, int x, int y).
 *
 * RACIOCINIO
 *   Busca em profundidade (DFS) a partir de x. Preciso lembrar quem ja
 *   visitei para nao entrar em loop revisitando o mesmo no - guardo os
 *   visitados numa TLSE.
 *
 *   DETALHE IMPORTANTE: a lista de visitados precisa ser COMPARTILHADA
 *   entre TODAS as chamadas recursivas da mesma busca (se o ramo A
 *   visitou o no 7, o ramo B nao pode visitar 7 de novo). Por isso uso
 *   TLSE_insere_void(TLSE **l, int elem), que MODIFICA a lista pelo
 *   ponteiro (em vez de TLSE_insere, que so devolveria uma cabeca nova
 *   local aquela chamada) - exatamente o motivo dessa funcao existir
 *   pronta em TLSE.h.
 *
 *   Quando acho y, "desenrolo" a recursao devolvendo uma TLSE com o
 *   caminho: cada nivel da recursao gruda o SEU no no INICIO da lista
 *   que a chamada de baixo devolveu (TLSE_insere insere no inicio),
 *   entao o caminho sai na ordem certa: x, ..., y.
 *
 * CUSTO: O(V + E), como qualquer DFS.
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

TLSE *caminho(TG *g, int x, int y) {
    if ((!TG_busca_no(g, x)) || (!TG_busca_no(g, y))) return NULL;

    TLSE *visitados = TLSE_inicializa();
    TLSE *resp = dfs(g, x, y, &visitados);
    TLSE_libera(visitados);
    return resp;
}

/* ---- grafo de exemplo (mesmo da lista04-EDA, Q1) --------------------
 *   Nos: 1, 2, 3, 4, 5   Arestas: 1-2, 1-3, 2-3, 3-4, 4-5
 * ------------------------------------------------------------------ */
static TG *exemplo(void) {
    TG *g = TG_inicializa();
    for (int i = 5; i >= 1; i--) g = TG_ins_no(g, i);
    TG_ins_aresta(g, 1, 2);
    TG_ins_aresta(g, 1, 3);
    TG_ins_aresta(g, 2, 3);
    TG_ins_aresta(g, 3, 4);
    TG_ins_aresta(g, 4, 5);
    return g;
}

int main(void) {
    TG *g = exemplo();
    printf("Grafo:\n");
    TG_imprime(g);

    TLSE *c = caminho(g, 1, 5);
    printf("\ncaminho(g, 1, 5) = ");
    TLSE_imprime(c);
    printf(" (um caminho valido; ligando as arestas dadas)\n");
    TLSE_libera(c);

    TLSE *c2 = caminho(g, 1, 1);
    printf("caminho(g, 1, 1) = ");
    TLSE_imprime(c2);
    printf(" (esperado: soh o 1)\n");
    TLSE_libera(c2);

    TLSE *c3 = caminho(g, 1, 99);
    printf("caminho(g, 1, 99) [99 nao existe em g] = %s  (esperado: NULL)\n",
           c3 ? "NAO-NULL (erro)" : "NULL");

    TG_libera(g);
    return 0;
}
