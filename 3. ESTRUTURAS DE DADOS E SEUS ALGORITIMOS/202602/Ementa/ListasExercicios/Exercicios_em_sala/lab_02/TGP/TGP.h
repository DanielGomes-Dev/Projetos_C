#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------ *
 * TGP - Grafo de Pessoas.
 *
 * MESMA LOGICA de TG.h (lista de nos, cada no com sua propria lista de
 * vizinhos), com duas diferencas exigidas pelo exercicio do Instagram:
 *   1. o "id" do vertice e um NOME (string), nao um int; cada pessoa
 *      tambem guarda a IDADE.
 *   2. a aresta e DIRECIONADA: (v1, v2) significa "v1 segue v2", o que
 *      NAO implica "v2 segue v1". Por isso TGP_ins_aresta insere so
 *      num sentido (TG_ins_aresta original insere nos dois, porque la
 *      a aresta era simetrica).
 * ------------------------------------------------------------------ */

#define TGP_NOME_MAX 30

typedef struct vizp {
    char nome_viz[TGP_NOME_MAX];
    struct vizp *prox_viz;
} TVIZP;

typedef struct grafop {
    char nome[TGP_NOME_MAX];
    int idade;
    TVIZP *prim_viz;             /* pessoas que este no SEGUE */
    struct grafop *prox_no;
} TGP;

TGP *TGP_inicializa(void);
TGP *TGP_busca_no(TGP *g, char *nome);
TGP *TGP_ins_no(TGP *g, char *nome, int idade);
void TGP_ins_aresta(TGP *g, char *segue, char *seguido);
void TGP_imprime(TGP *g);
void TGP_libera(TGP *g);
