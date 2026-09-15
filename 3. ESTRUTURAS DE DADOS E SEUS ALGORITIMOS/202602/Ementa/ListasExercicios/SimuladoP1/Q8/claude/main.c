#include <stdio.h>
#include <stdlib.h>
#include "../../TG/TG.h"
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * (8) Faca uma funcao que encontre o MENOR caminho (menos arestas)
 * entre dois vertices de um grafo.
 *     Prototipo: TLSE* menor_caminho(TG *g, int origem, int destino);
 *
 * POR QUE BFS (busca em LARGURA) E NAO DFS
 *   BFS explora o grafo "em ondas": primeiro todos os vizinhos diretos
 *   da origem, depois os vizinhos DESSES, etc. Como cada onda avanca
 *   exatamente 1 aresta por vez, a PRIMEIRA vez que o destino aparece
 *   numa onda, e garantido que foi pelo caminho com MENOS arestas -
 *   diferente de DFS (Q6), que pode achar um caminho bem mais longo
 *   primeiro, so por causa da ordem em que os vizinhos sao visitados.
 *
 * COMO RECONSTRUIR O CAMINHO
 *   Durante o BFS, cada vez que alcanco um vertice novo, guardo QUEM
 *   me levou ate ele (seu "predecessor"). No final, ando de tras pra
 *   frente a partir do destino, seguindo os predecessores ate voltar
 *   na origem - isso da o caminho, so que ao contrario; vou colando
 *   cada vertice no INICIO de uma TLSE (TLSE_insere) para sair na
 *   ordem certa (origem -> ... -> destino).
 *
 * ESTRUTURAS AUXILIARES
 *   Os ids dos vertices sao arbitrarios (nao necessariamente 0..n-1),
 *   entao nao da pra usar direto como indice de array. Primeiro
 *   monto um vetor 'ids[]' com todos os vertices do grafo (na ordem
 *   da lista de nos) e uso busca linear (indice_de) para achar a
 *   posicao de um id - suficiente para o tamanho destes exercicios.
 *   A fila do BFS e um vetor simples com dois indices (inicio, fim).
 *
 * CUSTO: O(V + E) para o BFS, + O(V) por busca linear em indice_de
 * (O(V^2) no total, aceitavel pra escala do exercicio).
 * ------------------------------------------------------------------ */

static int conta_nos(TG *g) {
    int n = 0;
    for (; g; g = g->prox_no) n++;
    return n;
}

static int indice_de(int *ids, int n, int id) {
    for (int i = 0; i < n; i++) if (ids[i] == id) return i;
    return -1;
}

TLSE *menor_caminho(TG *g, int origem, int destino) {
    if ((!TG_busca_no(g, origem)) || (!TG_busca_no(g, destino))) return NULL;

    int n = conta_nos(g);
    int *ids = (int *) malloc(n * sizeof(int));
    int i = 0;
    for (TG *p = g; p; p = p->prox_no) ids[i++] = p->id_no;

    int *visitado = (int *) calloc(n, sizeof(int));
    int *pred = (int *) malloc(n * sizeof(int));
    for (i = 0; i < n; i++) pred[i] = -1;

    int *fila = (int *) malloc(n * sizeof(int));
    int ini = 0, fim = 0;

    int io = indice_de(ids, n, origem);
    fila[fim++] = io;
    visitado[io] = 1;

    int achou = 0;
    while (ini < fim && !achou) {
        int u = fila[ini++];
        if (ids[u] == destino) { achou = 1; break; }

        TG *no = TG_busca_no(g, ids[u]);
        for (TVIZ *v = no->prim_viz; v; v = v->prox_viz) {
            int iv = indice_de(ids, n, v->id_viz);
            if (!visitado[iv]) {
                visitado[iv] = 1;
                pred[iv] = u;
                fila[fim++] = iv;
            }
        }
    }

    TLSE *resp = NULL;
    if (achou) {
        resp = TLSE_inicializa();
        for (int atual = indice_de(ids, n, destino); atual != -1; atual = pred[atual])
            resp = TLSE_insere(resp, ids[atual]);
    }

    free(ids);
    free(visitado);
    free(pred);
    free(fila);
    return resp;
}

/* ---- grafo de exemplo (mesmo do Q7, com atalho 1-2) ------------------
 *   0 -- 1        arestas: 0-1, 0-2, 1-2, 1-3, 2-3
 *   |  / |
 *   2 -- 3
 * -------------------------------------------------------------------
 *   menor_caminho(0,3): DFS (Q6) poderia achar 0-1-2-3 (3 arestas);
 *   BFS garante o de 2 arestas: 0-1-3 ou 0-2-3.
 * ------------------------------------------------------------------ */
static TG *exemplo(void) {
    TG *g = TG_inicializa();
    for (int i = 3; i >= 0; i--) g = TG_ins_no(g, i);
    TG_ins_aresta(g, 0, 1);
    TG_ins_aresta(g, 0, 2);
    TG_ins_aresta(g, 1, 2);
    TG_ins_aresta(g, 1, 3);
    TG_ins_aresta(g, 2, 3);
    return g;
}

static int tam_lista(TLSE *l) { int n = 0; for (; l; l = l->prox) n++; return n; }

int main(void) {
    TG *g = exemplo();
    printf("Grafo:\n");
    TG_imprime(g);

    TLSE *m = menor_caminho(g, 0, 3);
    printf("\nmenor_caminho(g, 0, 3) = ");
    TLSE_imprime(m);
    printf(" (tamanho = %d vertices, esperado: 2 arestas / 3 vertices)\n", tam_lista(m));
    TLSE_libera(m);

    TLSE *m2 = menor_caminho(g, 0, 99);
    printf("menor_caminho(g, 0, 99) [99 nao existe] = %s  (esperado: NULL)\n",
           m2 ? "NAO-NULL (erro)" : "NULL");

    TG_libera(g);
    return 0;
}
