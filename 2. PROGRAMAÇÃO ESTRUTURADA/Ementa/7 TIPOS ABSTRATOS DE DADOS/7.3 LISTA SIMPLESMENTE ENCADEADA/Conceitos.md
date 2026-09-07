# Conceitos — Lista Simplesmente Encadeada

## A ideia em uma frase

Uma lista encadeada é uma corrente de nós espalhados pela memória: cada nó guarda um dado
e o **endereço do próximo** nó; o último aponta para `NULL`.

## O conceito

Diferente do vetor, os elementos **não** ficam em posições contíguas. Cada nó é alocado
por conta própria com `malloc`, e o encadeamento é feito por ponteiros:

```
lista
  |
  v
+----+----+   +----+----+   +----+------+
| 78 |  *-+-->| 45 |  *-+-->| 23 | NULL |
+----+----+   +----+----+   +----+------+
```

- **A lista inteira é representada só pelo ponteiro para o primeiro nó.**
- **Lista vazia** = ponteiro `NULL`.
- **Inserir no início:** O(1) — cria o nó, aponta seu `prox` para o antigo primeiro,
  retorna o novo primeiro.
- **Buscar / percorrer:** O(n) — segue os ponteiros um a um. Não existe "ir direto ao
  5º elemento".
- **Remover:** O(1) *depois* de achar o nó (mas achar é O(n)); precisa saber quem é o nó
  **anterior** para religar o `prox` dele.

Troca em relação ao [[../7.2 LISTA LINEAR SEQUENCIAL (VETORES)/Conceitos|vetor]]: ganha
inserção/remoção sem deslocamento (O(1)), perde o acesso direto por índice.

## Sintaxe / ferramentas

```c
typedef struct no {
    int info;
    struct no *prox;     // estrutura autorreferenciada: aponta para outro 'struct no'
} No;
```

Idioma de percurso: `for (No *p = l; p != NULL; p = p->prox) { ... }`.

## Exemplos passo a passo

### Exemplo 1 — TAD completo (num arquivo só, para estudo)

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct no { int info; struct no *prox; } No;

No *lst_cria(void) { return NULL; }             // lista vazia

No *lst_insere(No *l, int v) {                  // insere no INÍCIO — O(1)
    No *novo = malloc(sizeof(No));
    novo->info = v;
    novo->prox = l;                             // novo aponta para o antigo primeiro
    return novo;                                // <- recapture: l = lst_insere(l, v);
}

No *lst_busca(No *l, int v) {
    for (No *p = l; p != NULL; p = p->prox)
        if (p->info == v) return p;
    return NULL;
}

No *lst_retira(No *l, int v) {
    No *ant = NULL, *p = l;
    while (p != NULL && p->info != v) {         // procura v, guardando o anterior
        ant = p;
        p = p->prox;
    }
    if (p == NULL) return l;                    // não achou
    if (ant == NULL) l = p->prox;               // era o primeiro
    else             ant->prox = p->prox;       // era do meio/fim
    free(p);
    return l;
}

void lst_imprime(No *l) {
    for (No *p = l; p != NULL; p = p->prox) printf("%d ", p->info);
    printf("\n");
}

void lst_libera(No *l) {
    No *p = l;
    while (p != NULL) {
        No *prox = p->prox;                     // guarda ANTES do free
        free(p);
        p = prox;
    }
}

int main(void) {
    No *lista = lst_cria();
    lista = lst_insere(lista, 23);
    lista = lst_insere(lista, 45);
    lista = lst_insere(lista, 78);
    lst_imprime(lista);                         // 78 45 23

    lista = lst_retira(lista, 45);
    lst_imprime(lista);                         // 78 23

    lst_libera(lista);
    return 0;
}
```

### Exemplo 2 — o que acontece em `lst_insere(lista, 78)`

Estado antes: `lista -> [45|*] -> [23|NULL]`.

1. `malloc` cria `novo` num endereço qualquer; `novo->info = 78`.
2. `novo->prox = l` → `novo` aponta para o nó `45` (o antigo primeiro).
3. `return novo` → quem chamou faz `lista = novo`.

Estado depois: `lista -> [78|*] -> [45|*] -> [23|NULL]`.

**Por que recapturar o retorno:** a variável `lista` de `main` só passa a apontar para o
nó novo por causa do `lista = lst_insere(...)`. Se você escrever só `lst_insere(lista, 78)`,
o nó `78` é criado mas ninguém aponta para ele — vazamento, e a lista não cresce.

### Exemplo 3 — remover o nó `45` de `78 -> 45 -> 23`

```
ant = NULL, p = [78]      78 != 45 -> ant = [78], p = [45]
p->info == 45             para o laço
ant != NULL               ant->prox = p->prox
                          [78].prox = [23]   ->  78 -> 23
free([45])
```

**O que observar:** sem o ponteiro `ant`, seria impossível religar — numa lista simples
não há como "voltar" do nó `45` para o `78`.

### Exemplo 4 — liberar a lista sem perder o encadeamento

```c
while (p != NULL) {
    No *prox = p->prox;   // 1. guarda o endereço do próximo
    free(p);              // 2. libera o atual
    p = prox;             // 3. avança usando a cópia guardada
}
```

Se você fizesse `free(p); p = p->prox;`, o `p->prox` leria memória já liberada —
comportamento indefinido.

## Erros comuns / pegadinhas

- **Não recapturar o retorno** de `lst_insere` / `lst_retira` — a cabeça da lista não
  atualiza.
- **`free(p)` antes de guardar `p->prox`** — perde o resto da lista.
- **Esquecer o caso "é o primeiro nó"** na remoção (`ant == NULL`).
- **Não checar `malloc`** retornando `NULL`.
- **Percorrer com índice** — não existe; use ponteiro (`p = p->prox`).
- **Acessar `p->info` sem checar `p != NULL`** — deref de `NULL` trava.

## Resumo / checklist

- [ ] Sei desenhar a lista como nós ligados por ponteiros, terminando em `NULL`
- [ ] Sei que a lista "é" o ponteiro para o primeiro nó, e vazia = `NULL`
- [ ] Sei inserir no início em O(1) e por que recapturar o retorno
- [ ] Sei por que a remoção precisa do nó anterior
- [ ] Libero a lista guardando `prox` antes de cada `free`
- [ ] Sei o trade-off vs. vetor (O(1) para inserir/remover, sem acesso por índice)
