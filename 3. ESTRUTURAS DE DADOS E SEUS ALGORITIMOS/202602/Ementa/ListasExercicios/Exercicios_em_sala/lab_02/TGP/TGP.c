#include "TGP.h"

TGP *TGP_inicializa(void) {
    return NULL;
}

TGP *TGP_busca_no(TGP *g, char *nome) {
    if ((!g) || (strcmp(g->nome, nome) == 0)) return g;
    return TGP_busca_no(g->prox_no, nome);
}

TGP *TGP_ins_no(TGP *g, char *nome, int idade) {
    TGP *p = TGP_busca_no(g, nome);
    if (!p) {
        p = (TGP *) malloc(sizeof(TGP));
        strncpy(p->nome, nome, TGP_NOME_MAX - 1);
        p->nome[TGP_NOME_MAX - 1] = '\0';
        p->idade = idade;
        p->prim_viz = NULL;
        p->prox_no = g;
        g = p;
    }
    return g;
}

void TGP_ins_aresta(TGP *g, char *segue, char *seguido) {
    TGP *p = TGP_busca_no(g, segue);
    if (!p) return;
    TVIZP *nova = (TVIZP *) malloc(sizeof(TVIZP));
    strncpy(nova->nome_viz, seguido, TGP_NOME_MAX - 1);
    nova->nome_viz[TGP_NOME_MAX - 1] = '\0';
    nova->prox_viz = p->prim_viz;
    p->prim_viz = nova;
}

void TGP_imprime(TGP *g) {
    while (g) {
        printf("%s (%d anos) segue:", g->nome, g->idade);
        TVIZP *v = g->prim_viz;
        while (v) {
            printf(" %s", v->nome_viz);
            v = v->prox_viz;
        }
        printf("\n");
        g = g->prox_no;
    }
}

static void TGP_libera_viz(TVIZP *v) {
    while (v) {
        TVIZP *temp = v;
        v = v->prox_viz;
        free(temp);
    }
}

void TGP_libera(TGP *g) {
    while (g) {
        TGP_libera_viz(g->prim_viz);
        TGP *temp = g;
        g = g->prox_no;
        free(temp);
    }
}
