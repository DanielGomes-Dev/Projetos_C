#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------------------ *
 * Q7) Se a estrutura TAB tivesse um campo "int cor", defina
 *     void colore (TAB* arv);
 * que recebe uma arvore SEM cor e TOTALMENTE BALANCEADA (mesma
 * distancia da raiz a qualquer folha) e a devolve colorida so de
 * vermelho e preto, de forma que um no NUNCA tenha a mesma cor de
 * seus filhos.
 *
 * Como a arvore e totalmente balanceada, basta colorir pela paridade
 * da profundidade: raiz PRETO, nivel seguinte VERMELHO, e assim por
 * diante. Assim pai e filhos sempre tem cores diferentes.
 *
 * Aqui redefinimos TAB localmente (com o campo cor) porque o TAB.h
 * fornecido nao possui esse campo.
 * ------------------------------------------------------------------ */

#define VERMELHO 0
#define PRETO    1

typedef struct ab {
    int info;
    struct ab *esq, *dir;
    int cor;
} TAB;

static TAB *cria(int v, TAB *e, TAB *d) {
    TAB *n = malloc(sizeof(TAB));
    n->info = v;
    n->esq = e;
    n->dir = d;
    n->cor = -1;                      /* "sem cor" */
    return n;
}

static void colore_aux(TAB *arv, int cor) {
    if (!arv)
        return;
    arv->cor = cor;
    colore_aux(arv->esq, !cor);
    colore_aux(arv->dir, !cor);
}

void colore(TAB *arv) {
    colore_aux(arv, PRETO);          /* raiz preta */
}

static const char *nome_cor(int c) {
    return c == PRETO ? "PRETO" : c == VERMELHO ? "VERMELHO" : "sem cor";
}

static void imp_sim(TAB *a) {
    if (!a)
        return;
    imp_sim(a->esq);
    printf("%d[%s] ", a->info, nome_cor(a->cor));
    imp_sim(a->dir);
}

/* arvore totalmente balanceada de altura 2 (7 nos) */
static TAB *exemplo(void) {
    return cria(4,
        cria(2, cria(1, NULL, NULL), cria(3, NULL, NULL)),
        cria(6, cria(5, NULL, NULL), cria(7, NULL, NULL)));
}

static void libera(TAB *a) {
    if (a) { libera(a->esq); libera(a->dir); free(a); }
}

int main(void) {
    TAB *a = exemplo();

    colore(a);

    printf("em ordem simetrica (valor[cor]):\n");
    imp_sim(a);
    printf("\n");

    libera(a);
    return 0;
}
