# Q3 — Maior elemento da árvore

> **Origem:** `lista01-EDA.pdf`, item (Q3) · **Código resolvido:** [[../Q3/claude/main.c]]
> **Antes disto, veja:** [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 05 - Percurso em largura, busca e altura|1.1 Teoria 05]] (busca por força bruta — mesmo espírito)

## 1. O que o exercício pede

> Maior elemento da árvore: `TAB* maior(TAB *a);`

Encontrar o **nó** com o maior valor `info` em toda a árvore, e devolver o ponteiro para
ele.

## 2. A ideia geral (o mapa antes da viagem)

**Isso não é uma BST** (1.2) — é uma árvore binária qualquer, sem propriedade de ordenação.
Isso significa: **não dá pra "descer só de um lado"** como se faria numa BST para achar o
máximo. Aqui, o maior valor pode estar em **qualquer** folha ou nó interno, então a única
estratégia correta é **olhar todo mundo**: percorrer a árvore inteira e ir guardando "o
maior que já vi até agora".

## 3. Resolução passo a passo

### Passo 1 — o caso base

```c
TAB *maior(TAB *a) {
    if (!a)
        return NULL;
```

Árvore vazia não tem maior elemento — devolve `NULL`.

### Passo 2 — comparar os três candidatos

```c
    TAB *m = a;
    TAB *e = maior(a->esq);
    TAB *d = maior(a->dir);

    if (e && e->info > m->info) m = e;
    if (d && d->info > m->info) m = d;
    return m;
}
```

> 📖 **Lendo devagar:** em cada nó `a`, existem **três candidatos** a "maior desta
> subárvore": o próprio `a` (`m = a`, o palpite inicial), o maior da subárvore esquerda
> (`e = maior(a->esq)`) e o maior da subárvore direita (`d = maior(a->dir)`). Os dois `if`
> comparam `m` com `e` e depois com `d`, atualizando `m` sempre que encontra algo maior.
> `e && e->info > m->info` — o `e &&` é necessário porque `e` pode ser `NULL` (subárvore
> vazia); sem essa checagem, `e->info` acessaria um ponteiro nulo.

### Passo 3 — conferindo com a árvore do exemplo

```
        7
       / \
     20   3
     / \   \
    5  11   9
```

**Trace (pós-ordem, porque as chamadas recursivas terminam antes das comparações no nó
pai):**

| Chamada | `e` (maior à esq.) | `d` (maior à dir.) | `m` inicial (`a`) | `m` final |
|---|---|---|---|---|
| `maior(5)` (folha) | — | — | `5` | `5` |
| `maior(11)` (folha) | — | — | `11` | `11` |
| `maior(20)` | `5` | `11` | `20` | `20` (`5<20`, `11<20`) |
| `maior(9)` (folha) | — | — | `9` | `9` |
| `maior(3)` | `NULL` | `9` | `3` | `9` (`9>3`) |
| `maior(7)` (raiz) | `20` | `9` | `7` | `20` (`20>7`, `9<20`) |

**Resultado:** o nó `20`. ✔ Bate com o esperado — `20` é de fato o maior valor na árvore.

## 4. Resultado final

`m ? m->info : 0` imprime `20`. O `?:` trata o caso (impossível aqui, mas defensivo) de
`a` ser `NULL` desde o início.

**Conferindo (quando fizer sentido):** percorra a árvore com qualquer percurso (pré, em ou
pós-ordem, 1.1 Teoria 04) e confirme visualmente que nenhum valor impresso é maior que 20.

## 5. Habilidades necessárias

- [ ] Percorrer árvore binária sem propriedade de busca (força bruta) → [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 05 - Percurso em largura, busca e altura|1.1 Teoria 05]]
- [ ] Comparar com ponteiro possivelmente `NULL` antes de desreferenciar → `KR`, cap. 5.

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — árvore com um nó só

`maior(TAB_cria(42, NULL, NULL))`: `e = maior(NULL) = NULL`, `d = maior(NULL) = NULL`.
Nenhum `if` dispara (ambos `NULL`). `m` continua sendo `a` (o próprio `42`). Resultado: `42`.

### Aquecimento 2 — maior está na raiz

Árvore `10` com filhos `3` e `7`: `e->info=3 < 10`, `d->info=7 < 10` — nenhuma atualização,
`m` continua `10`. Mostra que o algoritmo não assume "o maior está numa folha" — ele
compara **todos** os candidatos, incluindo o próprio nó atual.
