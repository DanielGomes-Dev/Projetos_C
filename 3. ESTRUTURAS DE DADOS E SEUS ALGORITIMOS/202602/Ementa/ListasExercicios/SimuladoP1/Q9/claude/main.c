#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------------------ *
 * (9) A estrutura de arvore binaria tem um campo extra 'prox', que
 * aponta para o no "ao lado". Crie uma funcao que recebe a arvore e
 * ENCADEIA cada no ao PROXIMO no do MESMO NIVEL (da esquerda pra
 * direita), com o ultimo de cada nivel apontando para NULL - exatamente
 * a Figura B do enunciado.
 *     Prototipo: TAB* encadeador(TAB* a);
 *
 * struct do proprio enunciado:
 *   typedef struct arv { int info; struct arv *esq, *dir, *prox; } TAB;
 *
 * (Essa struct tem um campo a mais que a TAB "padrao" do resto do
 * curso - por isso este exercicio define sua PROPRIA TAB local, em vez
 * de incluir TAB.h; nao daria pra reaproveitar a de outros exercicios
 * sem esse campo extra.)
 *
 * RACIOCINIO
 *   "Ligar cada no ao proximo do mesmo nivel" e exatamente a ordem de
 *   visita de um PERCURSO EM LARGURA (Teoria 05 do subtopico 1.1),
 *   processado NIVEL POR NIVEL: dentro de um mesmo nivel, o no i aponta
 *   pro no i+1 da fila; o ultimo do nivel aponta pra NULL.
 *
 *   Uso uma fila simples (vetor com indices 'ini'/'fim') com todos os
 *   n nos - o mesmo espirito da TFILA da Teoria 05, so que sem
 *   depender de uma biblioteca de fila pronta (nao existe uma no
 *   repo). Processo a fila em BLOCOS: a cada passada do while, o
 *   "tamanho do nivel atual" e quantos nos ja estao esperando na fila
 *   (fim - ini) NAQUELE INSTANTE - todo mundo que entrar depois (os
 *   filhos) pertence ao PROXIMO nivel.
 *
 * CUSTO: O(n) tempo e O(n) memoria (fila do tamanho da arvore).
 * ------------------------------------------------------------------ */

typedef struct arv {
    int info;
    struct arv *esq, *dir, *prox;
} TAB;

static TAB *cria(int info, TAB *esq, TAB *dir) {
    TAB *novo = (TAB *) malloc(sizeof(TAB));
    novo->info = info;
    novo->esq = esq;
    novo->dir = dir;
    novo->prox = NULL;
    return novo;
}

static int conta_nos(TAB *a) {
    if (!a) return 0;
    return 1 + conta_nos(a->esq) + conta_nos(a->dir);
}

TAB *encadeador(TAB *a) {
    if (!a) return a;

    int n = conta_nos(a);
    TAB **fila = (TAB **) malloc(n * sizeof(TAB *));
    int ini = 0, fim = 0;
    fila[fim++] = a;

    while (ini < fim) {
        int tam_nivel = fim - ini;          /* quantos nos tem NESTE nivel */

        for (int i = 0; i < tam_nivel; i++) {
            TAB *no = fila[ini + i];
            no->prox = (i == tam_nivel - 1) ? NULL : fila[ini + i + 1];

            if (no->esq) fila[fim++] = no->esq;   /* filhos vao pro PROXIMO nivel */
            if (no->dir) fila[fim++] = no->dir;
        }
        ini += tam_nivel;
    }

    free(fila);
    return a;
}

static void libera(TAB *a) {
    if (a) { libera(a->esq); libera(a->dir); free(a); }
}

/* ---- exemplo do proprio enunciado (Figura A) ------------------------
 *              1
 *            /    \
 *           2       3
 *          / \     / \
 *         4   5   6   7
 * -------------------------------------------------------------------
 *   Depois de encadeador (Figura B):
 *     1 -> NULL
 *     2 -> 3 -> NULL
 *     4 -> 5 -> 6 -> 7 -> NULL
 * ------------------------------------------------------------------ */
static TAB *exemplo(void) {
    TAB *n2 = cria(2, cria(4, NULL, NULL), cria(5, NULL, NULL));
    TAB *n3 = cria(3, cria(6, NULL, NULL), cria(7, NULL, NULL));
    return cria(1, n2, n3);
}

/* imprime cada nivel seguindo 'prox', a partir do no mais a esquerda
   de cada nivel (achado descendo sempre por 'esq') */
static void imprime_por_nivel(TAB *a) {
    for (TAB *inicio_nivel = a; inicio_nivel; inicio_nivel = inicio_nivel->esq) {
        for (TAB *p = inicio_nivel; p; p = p->prox)
            printf("%d ", p->info);
        printf("-> NULL\n");
    }
}

int main(void) {
    TAB *a = exemplo();
    encadeador(a);

    printf("Encadeamento por nivel:\n");
    imprime_por_nivel(a);
    printf("(esperado: \"1 -> NULL\", \"2 3 -> NULL\", \"4 5 6 7 -> NULL\")\n");

    libera(a);
    return 0;
}
