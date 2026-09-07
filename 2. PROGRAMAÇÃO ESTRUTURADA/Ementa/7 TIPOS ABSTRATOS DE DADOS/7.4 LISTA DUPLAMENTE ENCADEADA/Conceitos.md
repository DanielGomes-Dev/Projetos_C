# Conceitos — Lista Duplamente Encadeada

## A ideia em uma frase

É uma lista encadeada em que cada nó guarda **dois** ponteiros — para o próximo e para o
anterior — o que permite andar nos dois sentidos e remover um nó sem procurar quem vem
antes dele.

## O conceito

A [[../7.3 LISTA SIMPLESMENTE ENCADEADA/Conceitos|lista simples]] tem dois incômodos:

1. só dá para percorrer de frente para trás;
2. para remover um nó, é preciso ter o nó **anterior** — o que obriga a percorrer a lista.

A lista dupla resolve os dois adicionando o campo `ant`:

```
NULL <-+    +----------+    +----------+
       |    |          |    |          |
  +----+----+---+  +----+---+---+  +----+----+------+
  | 30 | ant|prox|->| 20 |ant|prox|->| 10 |ant| NULL|
  +---------+---+<-+---------+---+<-+----+----+------+
```

- Cada nó: `ant` aponta para o nó de trás, `prox` para o da frente.
- Custo do campo extra: mais memória por nó.
- Ganho: percurso reverso em O(n) partindo do fim, e **remoção direta** dado o ponteiro do
  nó (sem percorrer para achar o anterior).

Fórmula da remoção (o coração da estrutura):

```
p->ant->prox = p->prox;    // quem vinha antes pula o p
p->prox->ant = p->ant;     // quem vinha depois pula o p
```

com **duas condições de contorno**: se `p` é o primeiro, `p->ant` é `NULL` (e a cabeça da
lista muda); se `p` é o último, `p->prox` é `NULL`.

## Exemplos passo a passo

### Exemplo 1 — TAD de lista dupla (inserção, remoção, percurso reverso)

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct no2 { int info; struct no2 *ant, *prox; } No2;

No2 *ld_insere(No2 *l, int v) {           // insere no início
    No2 *novo = malloc(sizeof(No2));
    novo->info = v;
    novo->ant  = NULL;
    novo->prox = l;
    if (l != NULL) l->ant = novo;         // passo extra: religar o antigo primeiro
    return novo;
}

No2 *ld_busca(No2 *l, int v) {
    for (No2 *p = l; p != NULL; p = p->prox)
        if (p->info == v) return p;
    return NULL;
}

No2 *ld_retira(No2 *l, int v) {
    No2 *p = ld_busca(l, v);
    if (p == NULL) return l;

    if (p->ant == NULL) l = p->prox;          // p era o primeiro -> cabeça muda
    else                p->ant->prox = p->prox;

    if (p->prox != NULL) p->prox->ant = p->ant;  // p não era o último

    free(p);
    return l;
}

void ld_imprime(No2 *l) {
    for (No2 *p = l; p != NULL; p = p->prox) printf("%d ", p->info);
    printf("\n");
}

void ld_imprime_reverso(No2 *l) {
    if (l == NULL) { printf("\n"); return; }
    No2 *p = l;
    while (p->prox != NULL) p = p->prox;      // vai até o último
    for (; p != NULL; p = p->ant) printf("%d ", p->info);  // volta pelo 'ant'
    printf("\n");
}

void ld_libera(No2 *l) {
    while (l != NULL) { No2 *prox = l->prox; free(l); l = prox; }
}

int main(void) {
    No2 *lista = NULL;
    lista = ld_insere(lista, 10);
    lista = ld_insere(lista, 20);
    lista = ld_insere(lista, 30);

    ld_imprime(lista);            // 30 20 10
    ld_imprime_reverso(lista);    // 10 20 30

    lista = ld_retira(lista, 20);
    ld_imprime(lista);            // 30 10

    ld_libera(lista);
    return 0;
}
```

### Exemplo 2 — remover o nó `20` de `30 <-> 20 <-> 10`

`ld_busca` devolve `p` = nó `20`.

```
p->ant  = [30]   (não é NULL, então não é o primeiro)
p->prox = [10]   (não é NULL, então não é o último)

p->ant->prox = p->prox   ->  [30].prox = [10]
p->prox->ant = p->ant    ->  [10].ant  = [30]
free([20])
```

Resultado: `30 <-> 10`. **Não houve percurso auxiliar** — a lista simples precisaria
varrer de novo desde a cabeça só para achar o `30`.

### Exemplo 3 — por que o percurso reverso funciona

Em `ld_imprime_reverso`, primeiro andamos até o último nó pelo `prox`. Depois voltamos
seguindo `p = p->ant` até chegar a `NULL` (que é o `ant` do primeiro nó). Numa lista
simples não há campo `ant`, então isso seria impossível sem uma pilha auxiliar ou
recursão.

## Erros comuns / pegadinhas

- **Aplicar `p->ant->prox = ...` quando `p` é o primeiro** — `p->ant` é `NULL`, deref
  trava. Trate as duas bordas.
- **Esquecer de religar `l->ant = novo`** ao inserir no início com a lista não vazia — o
  percurso reverso quebra.
- **Atualizar só um dos dois ponteiros** na remoção — a lista fica inconsistente.
- **Não atualizar a cabeça** quando remove o primeiro nó.
- **`free(p)` antes de ler `p->ant`/`p->prox`** — mesma armadilha da lista simples.

## Resumo / checklist

- [ ] Sei que cada nó tem `ant` e `prox`
- [ ] Sei a fórmula de remoção e as duas condições de contorno (primeiro / último)
- [ ] Sei fazer percurso nos dois sentidos
- [ ] Sei o passo extra da inserção (`l->ant = novo`)
- [ ] Entendo o trade-off: mais memória por nó, remoção e percurso reverso diretos
