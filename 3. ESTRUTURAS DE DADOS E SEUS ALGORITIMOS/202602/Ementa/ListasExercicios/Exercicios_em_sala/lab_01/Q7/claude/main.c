#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q7) Retorne uma arvore binaria a partir de uma string com sua
 * representacao textual, conforme investigado em sala de aula.
 *     Prototipo: TAB *str2ab(char *str).
 *
 * NOTACAO (Teoria 02 - Arvore binaria, definicao e notacao):
 *   <Raiz SAE SAD>   -- no com subarvore esquerda SAE e direita SAD
 *   <>               -- arvore vazia
 *   <X>              -- forma abreviada de <X <> <>>, ou seja, folha
 *
 *   Ex.: <1 <2 <> <>> <3 <> <>>>  ==  <1 <2> <3>>  (mesma arvore:
 *   raiz 1, filho esquerdo 2 (folha), filho direito 3 (folha)).
 *
 * ESTRATEGIA (parser recursivo descendente)
 *   Uma funcao auxiliar recebe um PONTEIRO PARA O PONTEIRO de leitura
 *   (char **s), para que cada chamada recursiva "andar" na string seja
 *   vista pelas chamadas seguintes (mesmo estilo de TLSE_insere_void:
 *   passar o endereco para poder alterar o que o chamador enxerga).
 *
 *   parse(s):
 *     1. pula espacos, espera '<' e consome.
 *     2. se o proximo caractere for '>': e o caso <>, consome '>' e
 *        devolve NULL (arvore vazia).
 *     3. senao, le um inteiro (com sinal opcional) = valor da raiz.
 *     4. se o proximo (ignorando espacos) for '>': forma abreviada
 *        <X>, consome '>' e devolve um no-folha (TAB_cria(valor,
 *        NULL, NULL)).
 *     5. senao, ha duas subarvores completas: chama parse(s) para a
 *        esquerda, depois parse(s) de novo para a direita, consome o
 *        '>' final e devolve TAB_cria(valor, esq, dir).
 *
 * CUSTO: O(tamanho da string), cada caractere e lido uma vez.
 * ------------------------------------------------------------------ */

static void pula_espacos(char **s) {
    while (**s == ' ') (*s)++;
}

static TAB *parse(char **s) {
    pula_espacos(s);
    (*s)++;                         /* consome '<' */
    pula_espacos(s);

    if (**s == '>') {               /* caso <> : arvore vazia */
        (*s)++;
        return NULL;
    }

    int sinal = 1;
    if (**s == '-') { sinal = -1; (*s)++; }
    int valor = 0;
    while (isdigit((unsigned char) **s)) {
        valor = valor * 10 + (**s - '0');
        (*s)++;
    }
    valor *= sinal;

    pula_espacos(s);
    if (**s == '>') {               /* forma abreviada <X> : folha */
        (*s)++;
        return TAB_cria(valor, NULL, NULL);
    }

    TAB *esq = parse(s);
    pula_espacos(s);
    TAB *dir = parse(s);
    pula_espacos(s);
    if (**s == '>') (*s)++;         /* fecha o no atual */

    return TAB_cria(valor, esq, dir);
}

TAB *str2ab(char *str) {
    char *p = str;
    return parse(&p);
}

int main(void) {
    /* Exercicio 1 da Teoria 02: raiz 1, esq = folha 2, dir = folha 3,
       na forma completa (sem abreviacao) */
    TAB *a1 = str2ab("<1 <2 <> <>> <3 <> <>>>");
    printf("str2ab(\"<1 <2 <> <>> <3 <> <>>>\") em-ordem: ");
    TAB_imp_sim(a1);
    printf(" (esperado: 2 1 3)\n");

    /* mesma arvore, usando a forma abreviada <X> para as folhas */
    TAB *a2 = str2ab("<1 <2> <3>>");
    printf("str2ab(\"<1 <2> <3>>\")            em-ordem: ");
    TAB_imp_sim(a2);
    printf(" (esperado: 2 1 3)\n");

    /* arvore maior, misturando forma completa e abreviada, com
       numeros negativos */
    TAB *a3 = str2ab("<1 <2> <3 <-4> <5>>>");
    printf("str2ab(\"<1 <2> <3 <-4> <5>>>\")   pre-ordem: ");
    TAB_imp_pre(a3);
    printf(" (esperado: 1 2 3 -4 5)\n");

    /* arvore vazia */
    TAB *a4 = str2ab("<>");
    printf("str2ab(\"<>\") == NULL ? %s  (esperado: sim)\n", a4 == NULL ? "sim" : "nao");

    TAB_libera(a1);
    TAB_libera(a2);
    TAB_libera(a3);
    return 0;
}
