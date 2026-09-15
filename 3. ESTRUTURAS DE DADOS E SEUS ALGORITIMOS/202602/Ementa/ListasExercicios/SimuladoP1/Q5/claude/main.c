#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"
#include "../../TLSE/TLSE.h"

/* ------------------------------------------------------------------ *
 * (5) Faca uma funcao que retorne todos os caminhos que somam n em
 * uma arvore binaria de busca. Use a biblioteca de lista encadeada e
 * retorne um vetor com todas as listas de caminhos.
 *     Prototipo: TLSE** caminhos(TAB *a, int n);
 *
 * INTERPRETACAO ADOTADA (mesma do exercicio Q6 do lab_01: nao ha
 * restricao explicita a raiz/folha)
 *   "Caminho" = qualquer sequencia que desce de um no ATE um
 *   descendente dele (comeca em QUALQUER no, nao so na raiz). Cada
 *   no da arvore e testado como possivel INICIO de caminho.
 *
 * FORMATO DE SAIDA
 *   O prototipo nao recebe nenhum "tam_vet" de saida - entao o vetor
 *   devolvido termina com um ponteiro NULL de sentinela (o chamador
 *   percorre ate achar NULL, como uma string termina em '\0').
 *
 * ESTRATEGIA (DFS com backtracking, guardando o caminho num vetor
 * auxiliar de ints e so convertendo pra TLSE quando a soma bate)
 *   - desce(no, alvo, vals, tam, soma, resultados): desce a partir de
 *     'no', empilhando no->info em vals[] e somando. Cada vez que a
 *     soma acumulada bate com 'alvo', o trecho vals[0..tam-1] e um
 *     caminho valido - vira uma TLSE nova, guardada em 'resultados'.
 *     Depois de tentar os dois filhos, desempilha (backtrack) antes
 *     de voltar - assim o vals[] fica limpo para o proximo ramo.
 *   - para_cada_no(a, alvo, ...): chama desce(a, ...) e depois se
 *     chama recursivamente para a->esq e a->dir, tratando CADA no da
 *     arvore como um novo possivel inicio de caminho.
 *
 * CUSTO: O(n^2) no pior caso (mesma ordem de grandeza do Q6 do lab_01).
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
    for (int i = tam - 1; i >= 0; i--)      /* insere do fim pro comeco: */
        l = TLSE_insere(l, vals[i]);        /* TLSE_insere poe na cabeca */
    return l;                               /* -> sobra na ordem certa  */
}

static void desce(TAB *no, int alvo, int *vals, int *tam, int soma, VetorListas *res) {
    if (!no) return;

    vals[*tam] = no->info;
    (*tam)++;
    soma += no->info;

    if (soma == alvo)
        guarda(res, monta_lista(vals, *tam));

    desce(no->esq, alvo, vals, tam, soma, res);
    desce(no->dir, alvo, vals, tam, soma, res);

    (*tam)--;                               /* backtrack: tira o ultimo */
}

static void para_cada_no(TAB *a, int alvo, int *vals, VetorListas *res) {
    if (!a) return;
    int tam = 0;
    desce(a, alvo, vals, &tam, 0, res);
    para_cada_no(a->esq, alvo, vals, res);
    para_cada_no(a->dir, alvo, vals, res);
}

TLSE **caminhos(TAB *a, int n) {
    VetorListas res = {NULL, 0, 0};
    int alt = TAB_altura(a);
    int cap_vals = (alt < 0 ? 0 : alt + 1) + 1;    /* maior caminho possivel */
    int *vals = (int *) malloc(cap_vals * sizeof(int));

    para_cada_no(a, n, vals, &res);
    guarda(&res, NULL);                            /* sentinela do vetor */

    free(vals);
    return res.itens;
}

/* ---- arvore de exemplo (mesma do Q6 do lab_01) ----------------------
 *                10
 *              /    \
 *             5      -3
 *           /   \       \
 *          3     2       11
 *         / \      \
 *        3  -2      1
 * -------------------------------------------------------------------
 *   Caminhos que somam 8:  5->3 ; 5->2->1 ; -3->11   (3 caminhos)
 * ------------------------------------------------------------------ */
static TAB *exemplo(void) {
    TAB *n3a = TAB_cria(3, NULL, NULL);
    TAB *n_menos2 = TAB_cria(-2, NULL, NULL);
    TAB *n3b = TAB_cria(3, n3a, n_menos2);

    TAB *n1 = TAB_cria(1, NULL, NULL);
    TAB *n2 = TAB_cria(2, NULL, n1);

    TAB *n5 = TAB_cria(5, n3b, n2);

    TAB *n11 = TAB_cria(11, NULL, NULL);
    TAB *n_menos3 = TAB_cria(-3, NULL, n11);

    return TAB_cria(10, n5, n_menos3);
}

int main(void) {
    TAB *a = exemplo();

    TLSE **res = caminhos(a, 8);
    printf("caminhos(a, 8):\n");
    int i;
    for (i = 0; res[i] != NULL; i++) {
        printf("  [%d] ", i);
        TLSE_imprime(res[i]);
        printf("\n");
    }
    printf("total = %d  (esperado: 3)\n", i);

    for (int j = 0; res[j] != NULL; j++) TLSE_libera(res[j]);
    free(res);

    TLSE **vazio = caminhos(a, 999);
    printf("\ncaminhos(a, 999) total = %d  (esperado: 0)\n", vazio[0] == NULL ? 0 : -1);
    free(vazio);

    TAB_libera(a);
    return 0;
}
