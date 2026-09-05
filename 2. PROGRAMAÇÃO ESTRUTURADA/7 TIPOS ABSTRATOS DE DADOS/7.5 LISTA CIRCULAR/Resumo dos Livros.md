# Resumo dos Livros — 7.5 Lista Circular

## Celes — Introdução a Estruturas de Dados (Cap. 10, "Listas encadeadas" — seção "Listas circulares")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção de capítulo: seção do Cap. 10 (não capítulo 5). Motivação do livro: conjuntos naturalmente cíclicos (exemplo dado: as arestas que delimitam uma face numa aplicação de geometria) — em uma lista circular, o **último elemento aponta de volta para o primeiro**, formando um ciclo, e "a rigor... não faz sentido falar em primeiro ou último elemento" — a lista é representada por um ponteiro para **um** elemento inicial qualquer, não necessariamente "o primeiro".

Ponto prático central que o livro destaca: percorrer uma lista circular **não pode** usar o teste `p != NULL` (nunca seria falso) — o critério de parada precisa ser "voltei ao ponto de partida". Por isso o percurso usa `do-while` em vez de `while`, testando a condição de parada **depois** de já ter avançado pelo menos uma vez:
```c
Lista* p = l;
if (p) do {
    printf("%d\n", p->info);
    p = p->prox;
} while (p != l);     /* para quando voltar ao ponto de partida, não quando p==NULL */
```
O `if (p)` trata a lista vazia (`l == NULL`) como caso especial — sem ele, o `do-while` executaria pelo menos uma vez mesmo numa lista vazia.

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Seção 2.7.3)

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Seção 2.7.3)
Szwarcfiter apresenta a lista circular como resposta direta a uma ineficiência da busca em lista encadeada com nó-cabeça vista na seção anterior (2.7.1): "obrigar o último nó da lista a apontar para o nó-cabeça, criando assim uma lista circular encadeada [...]. Dessa forma, o teste de fim de lista nunca é satisfeito." A vantagem prática é eliminar um dos dois testes do laço de busca (não é mais preciso checar se o percurso chegou ao fim, só se a chave foi encontrada) — mas isso exige um critério de parada alternativo: o livro resolve colocando a própria chave procurada no nó-cabeça antes da busca, de forma que uma correspondência positiva seja sempre garantida ao final do percurso, funcionando como uma **sentinela**.

O `Algoritmo 2.23` (`busca-cir`) ilustra a técnica: percorre a lista comparando chaves até encontrar uma ≥ x; como o nó-cabeça foi "envenenado" com a chave x, o laço sempre termina, e a checagem final (`pont ≠ ptlista e pont.chave = x`) distingue sucesso de insucesso. O livro nota que o mesmo princípio se aplica a listas não ordenadas, com adaptações. A lista circular também é a base estrutural usada mais tarde para a lista circular *duplamente* encadeada (Seção 2.7.4).

## Síntese
Ambos os livros tratam a circularidade como uma otimização de engenharia sobre a lista encadeada básica, não uma estrutura conceitualmente nova, e ambos param no mesmo ponto prático: o critério de parada de "fim de lista" deixa de existir e precisa ser substituído por outra coisa — Celes resolve isso trocando `while (p != NULL)` por `do-while (p != inicio)`; Szwarcfiter, de forma mais sofisticada, usa a própria chave buscada como sentinela no nó-cabeça para eliminar um teste inteiro do laço de busca.

## Exemplos em C

**Lista circular simples — criação, inserção e percurso com `do-while` (o padrão do Celes):**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no *prox;
} No;

/* insere no início de uma lista circular; l é o ponteiro para "um" elemento (o mais recente) */
No* lcirc_insere(No *l, int valor) {
    No *novo = malloc(sizeof(No));
    novo->info = valor;
    if (l == NULL) {
        novo->prox = novo;      /* lista com 1 elemento aponta para si mesma */
    } else {
        novo->prox = l->prox;
        l->prox = novo;
    }
    return novo;
}

void lcirc_imprime(No *l) {
    No *p = l;
    if (p == NULL) { printf("(vazia)\n"); return; }
    do {
        printf("%d ", p->info);
        p = p->prox;
    } while (p != l);      /* NUNCA use p != NULL aqui — nunca seria verdadeiro */
    printf("\n");
}

int main(void) {
    No *lista = NULL;
    lista = lcirc_insere(lista, 10);
    lista = lcirc_insere(lista, 20);
    lista = lcirc_insere(lista, 30);
    lcirc_imprime(lista);
    return 0;
}
```

**Aplicação clássica de lista circular: o Problema de Josephus (eliminação a cada k-ésimo elemento em roda):**
```c
/* n pessoas em círculo, elimina a cada k-ésima, até sobrar 1 — usa a MESMA lista circular acima */
void josephus(No **l, int k) {
    No *atual = *l;
    while (atual->prox != atual) {          /* enquanto sobrar mais de 1 */
        No *ant = atual;
        for (int i = 1; i < k; i++)
            ant = ant->prox;
        No *eliminado = ant->prox;
        printf("Elimina: %d\n", eliminado->info);
        ant->prox = eliminado->prox;
        atual = ant->prox;
        free(eliminado);
    }
    *l = atual;
    printf("Sobrevivente: %d\n", atual->info);
}
```
