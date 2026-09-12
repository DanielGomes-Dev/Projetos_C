# Q2 — Menor elemento de uma árvore binária de busca

> **Origem:** `lista02-EDA.pdf`, item (Q2) · **Código resolvido:** [[../Q2/claude/main.c]]
> **Antes disto, veja:** [[../Q1/claude/main.c|Q1 - Maior elemento numa BST]] (mesmo algoritmo, sentido oposto)

## 1. O que o exercício pede

> Menor elemento da árvore: `TABB* menor(TABB *a);`

Espelho de Q1: agora o **menor** valor.

## 2. A ideia geral

Mesma lógica de Q1, invertida: pela propriedade de BST (1.2, Teoria 01), o menor elemento
está sempre no fim do caminho mais à **esquerda**.

## 3. Resolução passo a passo

```c
TABB *menor(TABB *a) {
    if (!a)
        return NULL;
    while (a->esq)
        a = a->esq;
    return a;
}
```

Idêntico a `maior` (Q1), trocando `dir` por `esq`.

### Conferindo com a árvore do exemplo

Inserindo `50, 30, 70, 20, 40, 60, 80, 15`:

```
              50
           /      \
         30        70
        /  \       /  \
      20   40    60    80
      /
    15
```

**Trace:** `50 → 30 → 20 → 15`. `15->esq = NULL` → para. Resultado: `15`.

## 4. Resultado final

`m->info = 15`. Também precisou de só 3 passos, não 8.

**Conferindo:** este `menor` também é usado dentro de `TABB_retira` (a função de remoção
que você vai ver em [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 04 - Remoção numa BST (os três casos)|1.2 Teoria 04]]) — lá, ao remover um nó
com dois filhos, procura-se o **sucessor** (o menor da subárvore direita), que é
exatamente esta mesma ideia de "descer sempre por um lado até acabar".

## 5. Habilidades necessárias

- [ ] Propriedade de BST → [[../Q1/claude/main.c|Q1]]

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — árvore com um nó só

`menor` de um nó isolado: devolve o próprio nó (o `while` nem roda).

### Aquecimento 2 — árvore "torta" para a esquerda

`50 → 40 → 30 → 20` (cada inserção menor que a anterior): degenera numa fila de `esq`.
`menor` ainda acha `20` corretamente, mas visitando todos os 4 nós — pior caso.
