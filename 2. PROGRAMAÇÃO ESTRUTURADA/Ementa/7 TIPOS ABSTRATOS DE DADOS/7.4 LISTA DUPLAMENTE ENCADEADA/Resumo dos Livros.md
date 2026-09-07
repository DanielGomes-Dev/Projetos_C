# Resumo dos Livros — 7.4 Lista Duplamente Encadeada

## Celes — Introdução a Estruturas de Dados (Cap. 10, "Listas encadeadas" — seção "Listas duplamente encadeadas")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção de capítulo: seção do Cap. 10 (não do capítulo 5) — mas a descrição geral do resumo anterior já estava no caminho certo. Motivação explícita do livro: a lista simples tem dois problemas — não dá para percorrer eficientemente de trás para frente, e remover um nó exige percorrer a lista inteira só para achar o nó **anterior** ao que se quer remover (mesmo já tendo o ponteiro do nó a remover).

**Nó**: `struct lista2 { int info; struct lista2* ant; struct lista2* prox; }; typedef struct lista2 Lista2;` — dois ponteiros por nó, `ant` e `prox`.

**Inserção no início** (`lst2_insere`): aloca o nó, `novo->prox = l; novo->ant = NULL;`, e — ponto que o livro destaca como o passo extra em relação à lista simples — se a lista não estava vazia, é preciso religar `l->ant = novo` no antigo primeiro elemento.

**Remoção** (`lst2_retira`) — o ganho concreto da estrutura, mostrado com a fórmula conceitual que o livro apresenta antes do código:
```
p->ant->prox = p->prox;
p->prox->ant = p->ant;
```
"o anterior passa a apontar para o próximo, e o próximo passa a apontar para o anterior" — sem precisar de nenhum percurso auxiliar para achar o nó anterior, ao contrário da lista simples ([[../7.3 LISTA SIMPLESMENTE ENCADEADA/Resumo dos Livros|7.3]], onde `lst_retira` precisa rastrear `ant` durante a busca). O livro é cuidadoso em apontar as **duas condições de contorno** que quebram essa fórmula direta: se `p` é o primeiro elemento, `p->ant` é `NULL` (não se pode escrever `p->ant->prox`) — e além disso a variável que representa a lista precisa ser atualizada; se `p` é o último, `p->prox` é `NULL` (não se pode escrever `p->prox->ant`).

**Lista circular duplamente encadeada**: seção final — combina os dois conceitos ([[../7.5 LISTA CIRCULAR/Resumo dos Livros|7.5]] + este), permitindo percorrer nos dois sentidos a partir de **qualquer** nó, sem precisar de ponteiro para "o primeiro" nem "o último" — usada mais adiante no livro como base da implementação de filas duplas (deque).

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Seção 2.7.4)

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Seção 2.7.4)
Szwarcfiter motiva a lista duplamente encadeada observando uma limitação das listas anteriores: o ponteiro `ant` usado durante o percurso "se mostrou sempre útil" para "rastrear" o nó anterior, mas às vezes isso não basta — quando se deseja percorrer a lista nos dois sentidos indiferentemente. Nesses casos, "o gasto de memória imposto por um novo campo de ponteiro pode ser justificado pela economia em não reprocessar praticamente a lista inteira". A estrutura resultante usa dois campos de ponteiro por nó, nomeados `ant` (nó anterior) e `post` (nó seguinte), tipicamente combinada com lista circular e nó-cabeça — embora o livro registre explicitamente que "listas não circulares e listas sem nó-cabeça também podem ser duplamente encadeadas".

Os três algoritmos centrais — busca (`busca-dup`), inserção e remoção — são apresentados para tabela ordenada. A busca retorna o nó procurado ou, se ausente, o nó que seria seu consecutivo (permitindo inserção imediata sem uma segunda busca). A inserção aloca um novo nó e ajusta quatro ponteiros (`anterior.post`, `pt.ant`, `pt.post`, `pont.ant`); a remoção religa diretamente `anterior.post` e `posterior.ant`, sem precisar do percurso auxiliar que uma lista simples exigiria para encontrar o nó anterior — essa é exatamente a economia mencionada na motivação da seção.

## Síntese
Szwarcfiter é o livro mais explícito sobre o *trade-off* central desta estrutura: gasto extra de memória por nó em troca de percurso bidirecional e remoção mais direta (sem precisar rastrear o nó anterior durante a busca). Celes reforça exatamente o mesmo ponto com código C real e cuidadoso nas condições de contorno (primeiro/último nó) que a fórmula geral de remoção não cobre sozinha.

## Exemplos em C

**TAD de lista duplamente encadeada — inserção no início e remoção, no espírito do Celes:**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct no2 {
    int info;
    struct no2 *ant;
    struct no2 *prox;
} No2;

No2* lst2_insere(No2 *l, int valor) {
    No2 *novo = malloc(sizeof(No2));
    novo->info = valor;
    novo->prox = l;
    novo->ant = NULL;
    if (l != NULL)
        l->ant = novo;      /* passo extra em relação à lista simples */
    return novo;
}

No2* lst2_busca(No2 *l, int valor) {
    No2 *p;
    for (p = l; p != NULL; p = p->prox)
        if (p->info == valor)
            return p;
    return NULL;
}

No2* lst2_retira(No2 *l, int valor) {
    No2 *p = lst2_busca(l, valor);
    if (p == NULL)
        return l;

    if (p == l)                    /* p é o primeiro elemento */
        l = p->prox;
    else
        p->ant->prox = p->prox;    /* religa o anterior ao próximo */

    if (p->prox != NULL)           /* p NÃO é o último elemento */
        p->prox->ant = p->ant;     /* religa o próximo ao anterior */

    free(p);
    return l;
}

void lst2_imprime(No2 *l) {
    for (No2 *p = l; p != NULL; p = p->prox)
        printf("%d ", p->info);
    printf("\n");
}

void lst2_imprime_reverso(No2 *l) {
    if (l == NULL) return;
    No2 *p = l;
    while (p->prox != NULL)   /* avança até o último nó */
        p = p->prox;
    while (p != NULL) {       /* e volta usando 'ant' — impossível numa lista simples */
        printf("%d ", p->info);
        p = p->ant;
    }
    printf("\n");
}

int main(void) {
    No2 *lista = NULL;
    lista = lst2_insere(lista, 10);
    lista = lst2_insere(lista, 20);
    lista = lst2_insere(lista, 30);

    lst2_imprime(lista);            /* 30 20 10 */
    lst2_imprime_reverso(lista);    /* 10 20 30 */

    lista = lst2_retira(lista, 20);
    lst2_imprime(lista);            /* 30 10 */

    return 0;
}
```
