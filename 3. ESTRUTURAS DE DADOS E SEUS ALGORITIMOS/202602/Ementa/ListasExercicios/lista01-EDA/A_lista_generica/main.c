#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/* ------------------------------------------------------------------ *
 * Demonstra a lista generica com dois tipos diferentes de dado
 * (int e string), reutilizando o mesmo TAD.
 * ------------------------------------------------------------------ */

/* ---- callbacks para int ---- */
static void imprime_int(const void *x) {
    printf("%d", *(const int *) x);
}
static int compara_int(const void *a, const void *b) {
    return *(const int *) a - *(const int *) b;
}

/* ---- callbacks para string ---- */
static void imprime_str(const void *s) {
    printf("\"%s\"", (const char *) s);
}
static int compara_str(const void *a, const void *b) {
    return strcmp((const char *) a, (const char *) b);
}

int main(void) {
    /* ---- lista de inteiros ---- */
    int valores[] = {10, 20, 30, 40};
    Lista *li = lista_cria();
    for (int i = 0; i < 4; i++)
        lista_insere_fim(li, &valores[i]);
    lista_insere_inicio(li, &(int){5});

    printf("lista de int   : ");
    lista_imprime(li, imprime_int);
    printf("tamanho        : %d\n", lista_tamanho(li));

    int chave = 30;
    int *achou = lista_busca(li, &chave, compara_int);
    printf("busca 30       : %s\n", achou ? "encontrado" : "nao encontrado");

    int *removido = lista_remove_inicio(li);
    printf("removeu inicio : %d\n", *removido);
    printf("apos remocao   : ");
    lista_imprime(li, imprime_int);
    lista_libera(li, NULL);           /* dados sao de vetor local: nao libera */

    /* ---- lista de strings ---- */
    Lista *ls = lista_cria();
    lista_insere_fim(ls, "banana");
    lista_insere_fim(ls, "maca");
    lista_insere_fim(ls, "uva");

    printf("\nlista de string: ");
    lista_imprime(ls, imprime_str);

    char *s = lista_busca(ls, "maca", compara_str);
    printf("busca \"maca\"   : %s\n", s ? "encontrado" : "nao encontrado");

    lista_libera(ls, NULL);           /* literais de string: nao libera */
    return 0;
}
