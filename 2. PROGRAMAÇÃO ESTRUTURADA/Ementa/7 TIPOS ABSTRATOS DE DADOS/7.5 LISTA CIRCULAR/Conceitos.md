# Conceitos — Lista Circular

## A ideia em uma frase

É uma lista encadeada em que o último nó, em vez de apontar para `NULL`, aponta de volta
para o primeiro — formando um ciclo sem "começo" nem "fim".

## O conceito

Serve para coisas naturalmente cíclicas: as arestas de um polígono, jogadores em roda,
um carrossel de músicas.

```
      +--------------------------------+
      v                                |
   +----+---+   +----+---+   +----+----+
   | 10 | *-+-->| 20 | *-+-->| 30 | *--+
   +----+---+   +----+---+   +----+----+
```

- A lista é representada por um ponteiro para **um** nó qualquer (não faz sentido falar
  "o primeiro").
- **O critério de parada `p != NULL` não funciona** — nunca vira falso. O critério passa a
  ser "voltei ao ponto de partida".
- Por isso o percurso usa `do-while`: avança pelo menos uma vez e para quando
  `p == inicio` de novo.
- A lista vazia (`NULL`) precisa ser tratada à parte, senão o `do-while` executa uma vez
  sobre nada.

## Exemplos passo a passo

### Exemplo 1 — lista circular: inserir e percorrer

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct no { int info; struct no *prox; } No;

// insere logo após o nó apontado por 'l'; devolve um ponteiro para a lista
No *lc_insere(No *l, int v) {
    No *novo = malloc(sizeof(No));
    novo->info = v;
    if (l == NULL) {
        novo->prox = novo;         // 1 elemento: aponta para si mesmo
        return novo;
    }
    novo->prox = l->prox;
    l->prox = novo;
    return l;
}

void lc_imprime(No *l) {
    if (l == NULL) { printf("(vazia)\n"); return; }   // caso especial
    No *p = l;
    do {
        printf("%d ", p->info);
        p = p->prox;
    } while (p != l);              // para ao voltar ao ponto de partida
    printf("\n");
}

void lc_libera(No *l) {
    if (l == NULL) return;
    No *p = l->prox;
    while (p != l) { No *prox = p->prox; free(p); p = prox; }
    free(l);
}

int main(void) {
    No *lista = NULL;
    lista = lc_insere(lista, 10);
    lista = lc_insere(lista, 20);
    lista = lc_insere(lista, 30);
    lc_imprime(lista);            // 10 30 20  (cada insere entra logo após 'l')
    lc_libera(lista);
    return 0;
}
```

**Passo a passo do percurso `lc_imprime` (partindo de `l` = nó 10):**

```
p = [10]   imprime 10   p = [30]
p = [30]   imprime 30   p = [20]
p = [20]   imprime 20   p = [10]
p == l  -> para
```

Com `while (p != NULL)` esse laço nunca terminaria: não há nó com `prox == NULL`.

### Exemplo 2 — por que `do-while` e não `while`

```c
// ERRADO numa lista circular:
while (p != l) { ... p = p->prox; }   // se começa com p = l, nem entra no laço
```

O primeiro nó seria pulado, porque `p != l` já é falso na entrada. O `do-while` garante
que o corpo roda uma vez antes do teste — exatamente o que queremos: visitar o nó de
partida e só parar quando voltarmos a ele.

### Exemplo 3 — aplicação: problema de Josephus

`n` pessoas em roda; conta-se de `k` em `k` e elimina-se essa pessoa; repete até sobrar
uma.

```c
int josephus(No *l, int k) {         // l: qualquer nó da roda cheia
    No *atual = l;
    while (atual->prox != atual) {    // enquanto sobrar mais de 1
        for (int i = 1; i < k; i++)   // anda k-1 passos: 'atual' fica ANTES do eliminado
            atual = atual->prox;
        No *elim = atual->prox;
        atual->prox = elim->prox;     // tira 'elim' do círculo
        free(elim);
        atual = atual->prox;          // recomeça a contagem do próximo
    }
    int vencedor = atual->info;
    free(atual);
    return vencedor;
}
```

**O que observar:** a estrutura circular é o que torna isso natural — a contagem
"dá a volta" sem nenhum tratamento especial de borda.

## Erros comuns / pegadinhas

- **Percorrer com `while (p != NULL)`** — loop infinito. Use `do-while` até `p == inicio`.
- **Não tratar a lista vazia** — o `do-while` roda uma vez sobre `NULL` e trava.
- **`lc_libera` percorrendo com `p != l` e depois esquecendo de liberar o próprio `l`.**
- **Inserir sem fechar o ciclo** — o primeiro nó de uma lista de 1 elemento tem que
  apontar para si mesmo (`novo->prox = novo`).
- **Guardar "o último" e "o primeiro" separados** e deixá-los inconsistentes — numa
  circular, um ponteiro só já basta.

## Resumo / checklist

- [ ] Sei que o último nó aponta para o primeiro (ciclo)
- [ ] Sei que `p != NULL` não serve de critério de parada
- [ ] Sei percorrer com `do-while` até voltar ao ponto de partida
- [ ] Trato a lista vazia como caso especial
- [ ] Sei fechar o ciclo ao inserir o primeiro nó
