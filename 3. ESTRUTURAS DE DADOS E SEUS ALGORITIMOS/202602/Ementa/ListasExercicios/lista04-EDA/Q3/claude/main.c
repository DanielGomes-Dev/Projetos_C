#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------------------ *
 * Q3) Suponha que a estrutura de grafo tivesse um campo "int cor".
 *     Teste se nos VIZINHOS nao tem a mesma cor.
 *     Retorna 1 se NENHUM par de vizinhos compartilha a cor
 *     (coloracao valida) e 0 caso contrario.
 *          int nao_tem_mesma_cor(TG *g);
 *
 * POR QUE ESTE ARQUIVO NAO USA ../../TG/TG.h ?
 *   O TG.h do repositorio NAO possui o campo 'cor'. Como o enunciado
 *   pede "SE a estrutura tivesse um campo cor", redefino aqui uma
 *   versao da estrutura com esse campo extra, para a questao ficar
 *   auto-contida e compilavel de forma isolada.
 *
 * ------------------------------------------------------------------ *
 * ESTRUTURA (identica a original + campo cor no no)
 * ------------------------------------------------------------------ */
typedef struct viz {
    int id_viz;
    struct viz *prox_viz;
} TVIZ;

typedef struct grafo {
    int id_no;
    int cor;                 /* <<< campo novo pedido no enunciado    */
    TVIZ *prim_viz;
    struct grafo *prox_no;
} TG;

/* busca o no de id x (necessaria para descobrir a cor de um vizinho) */
static TG *busca_no(TG *g, int x) {
    while (g && g->id_no != x)
        g = g->prox_no;
    return g;
}

/* ------------------------------------------------------------------ *
 * RACIOCINIO
 *   Uma coloracao e valida quando, para toda aresta {u,v}, temos
 *   cor(u) != cor(v).
 *
 *   Como a lista e de adjacencia dupla, basta varrer:
 *     para cada no u:
 *        para cada vizinho v de u:
 *           - localizo o no v na lista de nos (busca_no) para
 *             conhecer a cor dele;
 *           - se cor(u) == cor(v)  ->  achei um conflito, retorno 0.
 *   Se terminei a varredura sem conflitos, retorno 1.
 *
 *   (Cada aresta e checada duas vezes, u->v e v->u; isso nao muda o
 *    resultado, apenas o custo.)
 *
 * CUSTO: O(V * E) por causa da busca_no dentro do laco. Daria para
 *        baixar a O(V + E) guardando as cores num vetor indexado
 *        pelo id, mas mantive a versao direta por clareza.
 * ------------------------------------------------------------------ */
int nao_tem_mesma_cor(TG *g) {
    for (TG *u = g; u != NULL; u = u->prox_no) {
        for (TVIZ *v = u->prim_viz; v != NULL; v = v->prox_viz) {
            TG *pv = busca_no(g, v->id_viz);
            if (pv && pv->cor == u->cor)
                return 0;              /* vizinhos com a mesma cor     */
        }
    }
    return 1;                          /* coloracao valida             */
}

/* ---- helpers minimos so para montar os exemplos ----------------- */
static TG *ins_no(TG *g, int id, int cor) {
    TG *p = malloc(sizeof(TG));
    p->id_no = id;
    p->cor = cor;
    p->prim_viz = NULL;
    p->prox_no = g;
    return p;
}
static void liga(TG *g, int a, int b) {   /* aresta nao-direcionada   */
    TG *pa = busca_no(g, a), *pb = busca_no(g, b);
    TVIZ *x = malloc(sizeof(TVIZ)); x->id_viz = b; x->prox_viz = pa->prim_viz; pa->prim_viz = x;
    TVIZ *y = malloc(sizeof(TVIZ)); y->id_viz = a; y->prox_viz = pb->prim_viz; pb->prim_viz = y;
}
static void libera(TG *g) {
    while (g) {
        TVIZ *v = g->prim_viz;
        while (v) { TVIZ *t = v; v = v->prox_viz; free(t); }
        TG *t = g; g = g->prox_no; free(t);
    }
}

int main(void) {
    /* EXEMPLO 1 - coloracao VALIDA
     *   triangulo 1-2-3 com 3 cores distintas
     *   1(cor 0) -- 2(cor 1) -- 3(cor 2) -- 1
     */
    TG *g1 = NULL;
    g1 = ins_no(g1, 1, 0);
    g1 = ins_no(g1, 2, 1);
    g1 = ins_no(g1, 3, 2);
    liga(g1, 1, 2);
    liga(g1, 2, 3);
    liga(g1, 1, 3);
    printf("Exemplo 1 (3 cores no triangulo): nao_tem_mesma_cor = %d  (esperado: 1)\n",
           nao_tem_mesma_cor(g1));

    /* EXEMPLO 2 - coloracao INVALIDA
     *   mesmo triangulo, mas 1 e 2 com a cor 0
     */
    TG *g2 = NULL;
    g2 = ins_no(g2, 1, 0);
    g2 = ins_no(g2, 2, 0);      /* conflito com o vizinho 1           */
    g2 = ins_no(g2, 3, 1);
    liga(g2, 1, 2);
    liga(g2, 2, 3);
    liga(g2, 1, 3);
    printf("Exemplo 2 (1 e 2 com a cor 0):    nao_tem_mesma_cor = %d  (esperado: 0)\n",
           nao_tem_mesma_cor(g2));

    libera(g1);
    libera(g2);
    return 0;
}
