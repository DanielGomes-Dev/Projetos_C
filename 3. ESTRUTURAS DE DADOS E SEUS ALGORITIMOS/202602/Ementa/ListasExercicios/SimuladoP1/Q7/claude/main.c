#include <stdio.h>
#include <stdlib.h>
#include "../../TG/TG.h"
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * (7) Faca uma funcao que encontre TODOS os caminhos (simples, sem
 * repetir vertice) entre dois vertices de um grafo.
 *     Prototipo: TLSE** caminhos(TG *g, int origem, int destino);
 *
 * DIFERENCA PARA O Q6
 *   La, a busca PARAVA no primeiro caminho achado. Aqui, ao achar o
 *   destino, preciso GUARDAR aquele caminho e CONTINUAR explorando os
 *   outros vizinhos (nao dar return).
 *
 *   Tambem preciso "desfazer" a marca de visitado ao voltar
 *   (backtrack de verdade) - senao um no usado num caminho ficaria
 *   bloqueado para os demais caminhos que tambem podem passar por ele
 *   (so nao pode repetir DENTRO do mesmo caminho).
 *
 * ESTRATEGIA (mesmo par vals[]/VetorListas do Q5, adaptado pra grafo)
 *   - 'no_caminho_atual' (TLSE) guarda quem ja esta no caminho sendo
 *     construido agora (evita ciclos dentro do MESMO caminho); e
 *     desfeita com TLSE_retira ao sair do no (backtrack real, diferente
 *     do Q2/Q6 onde os visitados nunca sao desfeitos).
 *   - 'vals[]' guarda a sequencia de vertices do caminho atual, na
 *     ordem; quando chega no destino, vira uma TLSE nova em 'res'.
 *
 * CUSTO: exponencial no pior caso (grafo denso pode ter
 * exponencialmente muitos caminhos simples entre dois vertices).
 * ------------------------------------------------------------------ */

typedef struct {
    TLSE **itens;
    int tam, cap;
} VetorListas;

static void guarda(VetorListas *v, TLSE *l) {
    if (v->tam == v->cap) {
        v->cap = v->cap ? v->cap * 2 : 4;
        v->itens = (TLSE **) realloc(v->itens, v->cap * sizeof(TLSE *));
    }
    v->itens[v->tam++] = l;
}

static TLSE *monta_lista(int *vals, int tam) {
    TLSE *l = TLSE_inicializa();
    for (int i = tam - 1; i >= 0; i--) l = TLSE_insere(l, vals[i]);
    return l;
}

static int conta_nos(TG *g) {
    int n = 0;
    for (; g; g = g->prox_no) n++;
    return n;
}

static void desce(TG *g, int atual, int destino, TLSE **no_caminho,
                   int *vals, int *tam, VetorListas *res) {
    TLSE_insere_void(no_caminho, atual);
    vals[*tam] = atual;
    (*tam)++;

    if (atual == destino) {
        guarda(res, monta_lista(vals, *tam));
    } else {
        TG *no = TG_busca_no(g, atual);
        for (TVIZ *v = no->prim_viz; v; v = v->prox_viz)
            if (!TLSE_busca(*no_caminho, v->id_viz))
                desce(g, v->id_viz, destino, no_caminho, vals, tam, res);
    }

    (*tam)--;
    *no_caminho = TLSE_retira(*no_caminho, atual);   /* backtrack de verdade */
}

TLSE **caminhos(TG *g, int origem, int destino) {
    VetorListas res = {NULL, 0, 0};

    if (TG_busca_no(g, origem) && TG_busca_no(g, destino)) {
        int n = conta_nos(g);
        int *vals = (int *) malloc(n * sizeof(int));
        TLSE *no_caminho = TLSE_inicializa();
        int tam = 0;

        desce(g, origem, destino, &no_caminho, vals, &tam, &res);

        TLSE_libera(no_caminho);
        free(vals);
    }

    guarda(&res, NULL);            /* sentinela do vetor */
    return res.itens;
}

/* ---- grafo de exemplo -------------------------------------------- *
 *   0 -- 1
 *   |  / |
 *   | /  |
 *   2 -- 3
 *   arestas: 0-1, 0-2, 1-2, 1-3, 2-3
 *   caminhos simples de 0 a 3: 0-1-3, 0-1-2-3, 0-2-3, 0-2-1-3  (4 no total)
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

int main(void) {
    TG *g = exemplo();
    printf("Grafo:\n");
    TG_imprime(g);

    TLSE **res = caminhos(g, 0, 3);
    printf("\ncaminhos(g, 0, 3):\n");
    int i;
    for (i = 0; res[i] != NULL; i++) {
        printf("  [%d] ", i);
        TLSE_imprime(res[i]);
        printf("\n");
    }
    printf("total = %d  (esperado: 4)\n", i);

    for (int j = 0; res[j] != NULL; j++) TLSE_libera(res[j]);
    free(res);

    TG_libera(g);
    return 0;
}
