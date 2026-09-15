#include <stdio.h>
#include <stdlib.h>
#include "../../TG/TG.h"
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * (3) Dado um grafo CONECTADO, verifique se ele pode ser transformado
 * numa arvore binaria. Se puder, retorne 1; senao, retorne 0.
 *     Prototipo: int teste(TG *g).   (DICA do enunciado: use TLSE)
 *
 * QUANDO UM GRAFO CONECTADO "VIRA" ARVORE BINARIA?
 *   1. Primeiro, ele precisa SER uma arvore: conectado (dado) e sem
 *      ciclos. Para um grafo nao-direcionado, isso equivale a
 *      #arestas == #nos - 1 (com conexo garantido).
 *   2. Sendo uma arvore, para conseguir ESCOLHER UMA RAIZ e distribuir
 *      cada vizinho como "filho esquerdo" ou "filho direito", cada no
 *      pode ter NO MAXIMO 3 vizinhos no total (1 pai + 2 filhos). Uma
 *      arvore com n>=2 nos sempre tem pelo menos uma folha (grau 1)
 *      para virar raiz (raiz so precisa de <=2 filhos, e grau 1 <= 2),
 *      entao a unica restricao real e: grau de TODO no <= 3.
 *
 * COMO USO A TLSE (conforme a dica)
 *   Para verificar a conectividade "na unha" (sem confiar cegamente no
 *   enunciado), faço uma busca em profundidade a partir de um no
 *   qualquer, guardando os nos alcançados numa TLSE (com
 *   TLSE_insere_void, pelo mesmo motivo da Q2: a lista tem que ser
 *   compartilhada entre as chamadas recursivas). Se o tamanho da TLSE
 *   no final bater com o numero total de nos, o grafo e conexo.
 *
 * CUSTO: O(V + E) para a soma de graus + a DFS de conectividade.
 * ------------------------------------------------------------------ */

static int grau(TG *no) {
    int d = 0;
    for (TVIZ *v = no->prim_viz; v; v = v->prox_viz) d++;
    return d;
}

static int conta_nos(TG *g) {
    int n = 0;
    for (; g; g = g->prox_no) n++;
    return n;
}

static int tam_lista(TLSE *l) {
    int n = 0;
    for (; l; l = l->prox) n++;
    return n;
}

static void dfs_alcance(TG *g, int atual, TLSE **visitados) {
    if (TLSE_busca(*visitados, atual)) return;
    TLSE_insere_void(visitados, atual);
    TG *no = TG_busca_no(g, atual);
    for (TVIZ *v = no->prim_viz; v; v = v->prox_viz)
        dfs_alcance(g, v->id_viz, visitados);
}

int teste(TG *g) {
    if (!g) return 0;

    int nn = conta_nos(g);
    int soma_grau = 0;
    for (TG *p = g; p; p = p->prox_no) {
        int d = grau(p);
        if (d > 3) return 0;             /* no com grau > 3: impossivel virar binaria */
        soma_grau += d;
    }
    int ne = soma_grau / 2;              /* grafo nao-direcionado: soma dos graus = 2*arestas */

    TLSE *visitados = TLSE_inicializa();
    dfs_alcance(g, g->id_no, &visitados);
    int alcancados = tam_lista(visitados);
    TLSE_libera(visitados);

    if (alcancados != nn) return 0;      /* nao esta conectado */
    if (ne != nn - 1) return 0;          /* tem ciclo (conexo com arestas demais) */
    return 1;
}

/* ---- grafos de exemplo ---------------------------------------------
 * A: arvore valida (todo grau <= 3)
 *        1
 *       / \
 *      2   3
 *     / \   \
 *    4   5   6
 *
 * B: A + uma aresta extra (4-5) -> vira ciclo, deixa de ser arvore
 *
 * C: estrela com centro de grau 4 -> nenhuma raiz serviria (centro
 *    precisaria de 4 filhos, e nenhuma folha vira raiz porque o
 *    centro continuaria com grau 4)
 * ------------------------------------------------------------------ */
static TG *grafoA(void) {
    TG *g = TG_inicializa();
    for (int i = 6; i >= 1; i--) g = TG_ins_no(g, i);
    TG_ins_aresta(g, 1, 2);
    TG_ins_aresta(g, 1, 3);
    TG_ins_aresta(g, 2, 4);
    TG_ins_aresta(g, 2, 5);
    TG_ins_aresta(g, 3, 6);
    return g;
}

static TG *grafoB(void) {
    TG *g = grafoA();
    TG_ins_aresta(g, 4, 5);   /* fecha um ciclo: 2-4-5-2 */
    return g;
}

static TG *grafoC(void) {
    TG *g = TG_inicializa();
    for (int i = 5; i >= 1; i--) g = TG_ins_no(g, i);
    TG_ins_aresta(g, 1, 2);
    TG_ins_aresta(g, 1, 3);
    TG_ins_aresta(g, 1, 4);
    TG_ins_aresta(g, 1, 5);   /* no 1 tem grau 4 */
    return g;
}

int main(void) {
    TG *a = grafoA(), *b = grafoB(), *c = grafoC();

    printf("teste(A) = %d  (esperado: 1 - arvore, todos os graus <= 3)\n", teste(a));
    printf("teste(B) = %d  (esperado: 0 - tem ciclo)\n", teste(b));
    printf("teste(C) = %d  (esperado: 0 - no de grau 4)\n", teste(c));

    TG_libera(a);
    TG_libera(b);
    TG_libera(c);
    return 0;
}
