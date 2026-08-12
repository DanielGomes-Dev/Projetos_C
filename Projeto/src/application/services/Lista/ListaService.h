#ifndef LISTA_H
#define LISTA_H

typedef struct Node {
    int valor;
    struct Node* proximo;
} Node;

typedef struct {
    Node* inicio;
    int tamanho;
} Lista;

void lista_init(Lista* lista);

void lista_insert(Lista* lista, int valor);
void lista_remove(Lista* lista, int valor);
Node* lista_search(Lista* lista, int valor);
void lista_print(Lista* lista);

#endif