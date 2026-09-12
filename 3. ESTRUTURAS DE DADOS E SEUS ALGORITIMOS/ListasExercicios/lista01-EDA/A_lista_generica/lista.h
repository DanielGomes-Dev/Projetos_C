#ifndef LISTA_GENERICA_H
#define LISTA_GENERICA_H

/* ------------------------------------------------------------------ *
 * (a) TAD lista simplesmente encadeada generica usando void *.
 *
 * A lista guarda apenas ponteiros void * para os dados; quem usa
 * decide o tipo. Funcoes de callback (imprime, compara, libera)
 * recebem esses ponteiros e sabem interpreta-los.
 * ------------------------------------------------------------------ */

typedef struct no {
    void *info;
    struct no *prox;
} No;

typedef struct lista {
    No *inicio;
    int tam;
} Lista;

Lista *lista_cria(void);
void   lista_insere_inicio(Lista *l, void *info);
void   lista_insere_fim(Lista *l, void *info);
void  *lista_remove_inicio(Lista *l);              /* devolve o dado */
void  *lista_busca(Lista *l, void *chave,
                   int (*compara)(const void *, const void *));
int    lista_vazia(Lista *l);
int    lista_tamanho(Lista *l);
void   lista_imprime(Lista *l, void (*imprime)(const void *));
void   lista_libera(Lista *l, void (*libera_info)(void *));

#endif
