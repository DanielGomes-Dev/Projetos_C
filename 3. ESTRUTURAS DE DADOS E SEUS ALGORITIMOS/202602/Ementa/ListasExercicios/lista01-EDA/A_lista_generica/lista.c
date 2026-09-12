#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Lista *lista_cria(void) {
    Lista *l = malloc(sizeof(Lista));
    l->inicio = NULL;
    l->tam = 0;
    return l;
}

void lista_insere_inicio(Lista *l, void *info) {
    No *novo = malloc(sizeof(No));
    novo->info = info;
    novo->prox = l->inicio;
    l->inicio = novo;
    l->tam++;
}

void lista_insere_fim(Lista *l, void *info) {
    No *novo = malloc(sizeof(No));
    novo->info = info;
    novo->prox = NULL;

    if (!l->inicio) {
        l->inicio = novo;
    } else {
        No *p = l->inicio;
        while (p->prox)
            p = p->prox;
        p->prox = novo;
    }
    l->tam++;
}

void *lista_remove_inicio(Lista *l) {
    if (!l->inicio)
        return NULL;
    No *p = l->inicio;
    void *info = p->info;
    l->inicio = p->prox;
    free(p);
    l->tam--;
    return info;
}

void *lista_busca(Lista *l, void *chave,
                  int (*compara)(const void *, const void *)) {
    for (No *p = l->inicio; p; p = p->prox)
        if (compara(p->info, chave) == 0)
            return p->info;
    return NULL;
}

int lista_vazia(Lista *l) {
    return l->inicio == NULL;
}

int lista_tamanho(Lista *l) {
    return l->tam;
}

void lista_imprime(Lista *l, void (*imprime)(const void *)) {
    for (No *p = l->inicio; p; p = p->prox) {
        imprime(p->info);
        printf(" ");
    }
    printf("\n");
}

void lista_libera(Lista *l, void (*libera_info)(void *)) {
    No *p = l->inicio;
    while (p) {
        No *q = p;
        p = p->prox;
        if (libera_info)
            libera_info(q->info);
        free(q);
    }
    free(l);
}
