# Resumo dos Livros — 7.3 Lista Simplesmente Encadeada

## Celes — Introdução a Estruturas de Dados (Cap. 10, "Listas encadeadas")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção de capítulo: é o **Cap. 10** (abre a Parte II), não uma "segunda metade" de um capítulo de vetores — listas encadeadas têm capítulo próprio inteiro, com um TAD completo desenvolvido do zero ao fim (`Lista` de inteiros).

**Nó**: `struct lista { int info; struct lista* prox; }; typedef struct lista Lista;` — o livro chama explicitamente a atenção para ser uma **estrutura autorreferenciada**. A lista inteira é representada só pelo ponteiro para o primeiro nó (`Lista*`); lista vazia = `NULL`; o último nó tem `prox == NULL`.

**Convenção de nomenclatura**: todas as funções são prefixadas com `lst_` (ex. `lst_cria`, `lst_insere`), seguindo a mesma convenção de TAD apresentada no Cap. 9 ([[../7.1 CONCEITOS/Resumo dos Livros|7.1]]).

**Inserção no início** — a operação mais barata (não precisa percorrer a lista): aloca o novo nó, aponta `novo->prox` para o antigo primeiro elemento, e **retorna o novo primeiro elemento** (`Lista* lst_insere(Lista* l, int i)`). O livro chama atenção explícita para o erro mais comum de iniciantes: esquecer de reatribuir o retorno (`l = lst_insere(l, 23);`) — se a chamada for feita sem capturar o retorno, a lista "perde" o novo elemento na próxima operação. Como alternativa, mostra a versão com ponteiro-para-ponteiro (`Lista** l`, escrevendo através de `*l`), mas declara preferir a versão com retorno por ser "a forma mais natural de programar em C".

**Percorrer** (`lst_imprime`): idioma canônico — `for (p = l; p != NULL; p = p->prox) ...` — o livro compara diretamente com o `for` de índice inteiro usado em vetores, destacando que aqui a variável de percurso é um **ponteiro**, não um índice.

**Busca** (`lst_busca`): mesma travessia, retorna o ponteiro do nó encontrado ou `NULL`.

**Remoção** (`lst_retira`): a mais complexa — precisa rastrear o nó **anterior** ao que será removido (`ant`), pois é o `prox` do anterior que precisa ser realinhado. Dois casos: remover o primeiro nó (`ant == NULL`, atualiza o ponteiro da lista) ou remover do meio/fim (`ant->prox = p->prox`). O livro nota que remover o último elemento é só um caso particular de "remover do meio" — não precisa de tratamento especial.

**Liberar a lista inteira** (`lst_libera`): alerta específico e importante — é preciso **guardar o ponteiro para o próximo nó antes de dar `free` no atual**, senão o encadeamento é perdido (acessar `p->prox` depois de `free(p)` é acessar memória já liberada).

**Lista ordenada**: o livro observa que inserção no início é O(1) mas embaralha a ordem de inserção; para manter ordem crescente, `lst_insere_ordenado` precisa percorrer a lista até achar a posição correta — o mesmo trade-off (inserção rápida e desordenada vs. inserção posicionada e mais cara) que Szwarcfiter e Cormen tratam a seguir de forma mais teórica.

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Seção 2.7.1)
Antes de chegar à 2.7.1, a Seção 2.6 justifica a alocação encadeada: quando o desempenho da alocação sequencial "pode ser bastante fraco" ou quando se usa mais de uma lista simultaneamente, "se justifica a utilização da alocação encadeada [...] uma vez que posições de memória são alocadas (ou desalocadas) na medida em que são necessárias". Cada nó ganha um campo adicional apontando para o próximo. O livro também introduz a **Lista de Espaço Disponível (LED)** — a estrutura que gerencia quais posições de memória estão livres — e mostra as duas formas de implementá-la: um vetor simulando a memória (`ocupar`/`desocupar` manipulando um ponteiro `vago`) ou delegando a rotinas nativas da linguagem (`new`/`dispose` em Pascal).

Na Seção 2.7.1 propriamente, o livro resolve um problema prático da alocação encadeada: a existência de um ponteiro para o primeiro nó obriga os algoritmos de inserção/remoção a tratar como caso especial "o nó é o primeiro da lista". A solução apresentada é o **nó-cabeça**: um nó especial, nunca removido, que passa a ser sempre o nó apontado pelo início da lista, eliminando esse teste especial. Os algoritmos de busca (2.15), inserção (2.16) e remoção (2.17) em lista ordenada com nó-cabeça são então apresentados de forma direta, cada um em tempo O(n) para a busca (percurso sequencial pelos ponteiros) e O(1) para a inserção/remoção uma vez localizada a posição.

## Cormen — Algoritmos: Teoria e Prática (Seção 10.2)
Cormen define lista ligada como "uma estrutura de dados na qual os objetos estão organizados em ordem linear [...] determinada por um ponteiro em cada objeto", e generaliza logo de início as variantes possíveis: "simplesmente ligada ou duplamente ligada [...] ordenada ou não [...] circular ou não" — se simplesmente ligada, "omitimos o ponteiro anterior em cada elemento". O tratamento padrão do capítulo assume duplamente ligada; a versão simplesmente encadeada é a mesma estrutura sem o campo `anterior`.

As três operações centrais são apresentadas com análise de tempo explícita: `LIST-SEARCH(L, k)` faz "uma busca linear simples" e "demora o tempo Θ(n) no pior caso, já que talvez tenha de pesquisar a lista inteira"; `LIST-INSERT` "emenda x à frente da lista ligada" em tempo O(1); `LIST-DELETE` remove um nó dado um ponteiro para ele, também em O(1) — mas se a remoção for por chave, é preciso chamar `LIST-SEARCH` antes, tornando o custo total Θ(n) no pior caso.

## Síntese
Os três livros descrevem a mesma estrutura fundamental — nó com dado + ponteiro para o próximo — e concordam na análise de custo: busca é O(n)/Θ(n), inserção e remoção (dado o ponteiro do nó) são O(1). A diferença de foco: Szwarcfiter dá atenção extra ao problema de gerência de memória (a LED) e à técnica do nó-cabeça para simplificar o código; Cormen situa a lista simplesmente encadeada como caso particular de uma estrutura duplamente ligada tratada de forma mais unificada; Celes é o único a dar uma implementação C completa, compilável, do início ao fim (TAD `Lista` com `lst_cria`/`lst_insere`/`lst_busca`/`lst_retira`/`lst_libera`), com o alerta prático mais valioso: sempre recapturar o retorno de `lst_insere`/`lst_retira`, e sempre salvar `p->prox` antes de `free(p)` ao destruir a lista.

## Exemplos em C

**TAD completo de lista encadeada de inteiros (adaptado do exemplo do Celes, self-contido num arquivo):**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no *prox;
} No;

No* lst_cria(void) {
    return NULL;                 /* lista vazia = ponteiro NULL */
}

No* lst_insere(No *l, int valor) {          /* insere no INÍCIO — O(1) */
    No *novo = malloc(sizeof(No));
    novo->info = valor;
    novo->prox = l;
    return novo;                              /* NUNCA esquecer de recapturar: l = lst_insere(l, x); */
}

No* lst_busca(No *l, int valor) {
    No *p;
    for (p = l; p != NULL; p = p->prox)
        if (p->info == valor)
            return p;
    return NULL;
}

No* lst_retira(No *l, int valor) {
    No *ant = NULL, *p = l;
    while (p != NULL && p->info != valor) {
        ant = p;
        p = p->prox;
    }
    if (p == NULL)
        return l;                             /* não achou: lista não muda */

    if (ant == NULL)
        l = p->prox;                          /* removendo o primeiro nó */
    else
        ant->prox = p->prox;                  /* removendo do meio/fim */

    free(p);
    return l;
}

void lst_imprime(No *l) {
    No *p;
    for (p = l; p != NULL; p = p->prox)
        printf("%d ", p->info);
    printf("\n");
}

void lst_libera(No *l) {
    No *p = l;
    while (p != NULL) {
        No *prox = p->prox;   /* guarda ANTES de liberar — senão perde o encadeamento */
        free(p);
        p = prox;
    }
}

int main(void) {
    No *lista = lst_cria();
    lista = lst_insere(lista, 23);
    lista = lst_insere(lista, 45);
    lista = lst_insere(lista, 78);
    lst_imprime(lista);              /* 78 45 23 (inserção no início inverte a ordem) */

    lista = lst_retira(lista, 45);
    lst_imprime(lista);              /* 78 23 */

    lst_libera(lista);
    return 0;
}
```

**Inserção mantendo a lista ordenada (o refinamento que o Celes propõe em seguida):**
```c
No* lst_insere_ordenado(No *l, int valor) {
    No *novo = malloc(sizeof(No));
    novo->info = valor;

    if (l == NULL || valor < l->info) {   /* insere no início */
        novo->prox = l;
        return novo;
    }

    No *p = l;
    while (p->prox != NULL && p->prox->info < valor)
        p = p->prox;

    novo->prox = p->prox;
    p->prox = novo;
    return l;                              /* a cabeça só muda no caso acima */
}
```
