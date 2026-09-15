#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../TGP/TGP.h"

/* ------------------------------------------------------------------ *
 * (1) Grafo de seguidores do Instagram. Cada pessoa tem nome (id do
 * vertice) e idade. Aresta (v1, v2) = "v1 segue v2".
 *
 * 1. int numero_seguidos(TGrafo *g, char *nome)  -- quantas pessoas
 *    'nome' segue.
 * 2. int seguidores(TGrafo *vertice, char *nome, int imprime) --
 *    quantos seguem 'nome' (e imprime os nomes, se imprime==1).
 * 3. TGrafo *mais_popular(TGrafo *g) -- quem tem mais seguidores.
 * 4. int segue_mais_velho(TGrafo *g, int imprime) -- quantas pessoas
 *    so seguem gente mais velha que elas (e imprime, se pedido).
 *
 * (No enunciado o tipo aparece como "TGrafo" - aqui ele e o TGP
 * definido em TGP.h/TGP.c, seguindo a mesma logica de TG mas com
 * nome+idade por vertice e aresta DIRECIONADA, ja que seguir no
 * Instagram nao e reciproco.)
 * ------------------------------------------------------------------ */

/* 1) numero_seguidos: e so o tamanho da lista de vizinhos (prim_viz)
   do proprio no - cada elemento dela e alguem que ele segue. */
int numero_seguidos(TGP *g, char *nome) {
    TGP *p = TGP_busca_no(g, nome);
    if (!p) return 0;
    int cont = 0;
    for (TVIZP *v = p->prim_viz; v; v = v->prox_viz) cont++;
    return cont;
}

/* 2) seguidores: como a aresta e direcionada e cada no so "sabe" quem
   ELE segue (nao quem o segue), a unica forma e VARRER todos os
   outros nos e perguntar, para cada um, "voce segue 'nome'?" (olhando
   a lista de vizinhos dele). */
int seguidores(TGP *g, char *nome, int imprime) {
    int cont = 0;
    for (TGP *p = g; p; p = p->prox_no) {
        for (TVIZP *v = p->prim_viz; v; v = v->prox_viz) {
            if (strcmp(v->nome_viz, nome) == 0) {
                if (imprime) printf("  %s\n", p->nome);
                cont++;
                break;                 /* ja contei este seguidor, proximo no */
            }
        }
    }
    return cont;
}

/* 3) mais_popular: chama seguidores(...) para cada no e fica com o
   maior. Em caso de empate, fica com o primeiro encontrado ao
   percorrer a lista de nos. */
TGP *mais_popular(TGP *g) {
    TGP *melhor = NULL;
    int melhor_qtd = -1;
    for (TGP *p = g; p; p = p->prox_no) {
        int qtd = seguidores(g, p->nome, 0);
        if (qtd > melhor_qtd) {
            melhor_qtd = qtd;
            melhor = p;
        }
    }
    return melhor;
}

/* 4) segue_mais_velho: uma pessoa "so segue gente mais velha" se ela
   segue PELO MENOS UMA pessoa (quem nao segue ninguem nao entra na
   conta) e TODAS as que ela segue tem idade maior que a dela. */
int segue_mais_velho(TGP *g, int imprime) {
    int cont = 0;
    for (TGP *p = g; p; p = p->prox_no) {
        if (!p->prim_viz) continue;             /* nao segue ninguem */
        int ok = 1;
        for (TVIZP *v = p->prim_viz; v && ok; v = v->prox_viz) {
            TGP *alvo = TGP_busca_no(g, v->nome_viz);
            if (alvo->idade <= p->idade) ok = 0;
        }
        if (ok) {
            if (imprime) printf("  %s (%d anos)\n", p->nome, p->idade);
            cont++;
        }
    }
    return cont;
}

/* ---- grafo de exemplo (mesmo do slide, image.png) ------------------
 *   Ana(23) -> Joao        Marcos(19) -> Felipe    Bruna(23) -> Marcos
 *   Jane(30) -> Joao       Felipe(20) -> Renata     Bruna(23) -> Renata
 *   Jane(30) -> Marcos     Joao(25)  -> Caio
 *   Pedro(20) -> Caio, Jane, Marcos, Renata
 * ------------------------------------------------------------------ */
static TGP *exemplo(void) {
    TGP *g = TGP_inicializa();
    g = TGP_ins_no(g, "Joao", 25);
    g = TGP_ins_no(g, "Ana", 23);
    g = TGP_ins_no(g, "Jane", 30);
    g = TGP_ins_no(g, "Marcos", 19);
    g = TGP_ins_no(g, "Felipe", 20);
    g = TGP_ins_no(g, "Caio", 20);
    g = TGP_ins_no(g, "Pedro", 20);
    g = TGP_ins_no(g, "Bruna", 23);
    g = TGP_ins_no(g, "Renata", 35);

    TGP_ins_aresta(g, "Ana", "Joao");
    TGP_ins_aresta(g, "Jane", "Joao");
    TGP_ins_aresta(g, "Jane", "Marcos");
    TGP_ins_aresta(g, "Marcos", "Felipe");
    TGP_ins_aresta(g, "Felipe", "Renata");
    TGP_ins_aresta(g, "Joao", "Caio");
    TGP_ins_aresta(g, "Pedro", "Caio");
    TGP_ins_aresta(g, "Pedro", "Jane");
    TGP_ins_aresta(g, "Pedro", "Marcos");
    TGP_ins_aresta(g, "Pedro", "Renata");
    TGP_ins_aresta(g, "Bruna", "Marcos");
    TGP_ins_aresta(g, "Bruna", "Renata");
    return g;
}

int main(void) {
    TGP *g = exemplo();

    printf("Grafo:\n");
    TGP_imprime(g);

    printf("\nnumero_seguidos(Pedro) = %d  (esperado: 4)\n", numero_seguidos(g, "Pedro"));
    printf("numero_seguidos(Caio)  = %d  (esperado: 0)\n", numero_seguidos(g, "Caio"));

    printf("\nseguidores de Marcos (imprime=1):\n");
    int qm = seguidores(g, "Marcos", 1);
    printf("total = %d  (esperado: 3 - Jane, Pedro, Bruna)\n", qm);

    printf("\nseguidores de Renata (imprime=1):\n");
    int qr = seguidores(g, "Renata", 1);
    printf("total = %d  (esperado: 3 - Felipe, Pedro, Bruna)\n", qr);

    TGP *pop = mais_popular(g);
    printf("\nmais_popular = %s  (esperado: Marcos ou Renata, empate em 3 seguidores;\n"
           "  aqui vence quem aparece primeiro na lista de nos)\n", pop->nome);

    printf("\nsegue_mais_velho (imprime=1):\n");
    int qv = segue_mais_velho(g, 1);
    printf("total = %d  (esperado: 3 - Ana, Marcos, Felipe)\n", qv);

    TGP_libera(g);
    return 0;
}
