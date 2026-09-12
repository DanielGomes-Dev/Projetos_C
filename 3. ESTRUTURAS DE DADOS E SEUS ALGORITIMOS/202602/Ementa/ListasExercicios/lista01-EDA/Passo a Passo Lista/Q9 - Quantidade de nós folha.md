# Q9 — Quantidade de nós folha

> **Origem:** `lista01-EDA.pdf`, item (Q9) · **Código resolvido:** [[../Q9/claude/main.c]]
> **Antes disto, veja:** [[../Q8/claude/main.c|Q8 - Quantidade de nós internos]] (a mesma árvore, a pergunta complementar)

## 1. O que o exercício pede

> Ache a quantidade de nós folha: `int nf(TAB *a);`

Folha (1.1, Teoria 01) = nó **sem nenhum filho** (grau zero).

## 2. A ideia geral

Espelho exato de Q8: em vez de contar quem **tem** filho, conta quem **não tem nenhum**.

## 3. Resolução passo a passo

```c
int nf(TAB *a) {
    if (!a)
        return 0;
    if (!a->esq && !a->dir)
        return 1;
    return nf(a->esq) + nf(a->dir);
}
```

> 📖 **Lendo devagar:**
> 1. `if (!a) return 0;` — árvore vazia não tem folha pra contar.
> 2. `if (!a->esq && !a->dir) return 1;` — **os dois** filhos são nulos → é folha, conta 1
>    e **para aqui** (não desce mais, porque não há mais nada abaixo de uma folha).
> 3. `return nf(a->esq) + nf(a->dir);` — se não é folha, a contagem vem só das subárvores
>    (o nó atual, sendo interno, **não soma 1** aqui — diferente de Q8, onde o nó interno
>    somava 1 para si mesmo).

**Conferindo com a mesma árvore de Q8:**

```
        4
       / \
      2   6
     / \   \
    1  3    7
```

| Nó | Os dois filhos são `NULL`? | Conta como folha? |
|---|---|---|
| `1`, `3`, `7` | sim | sim |
| `4`, `2`, `6` | não | não |

Total: `3` (os nós `1`, `3`, `7`). ✔ Bate com o comentário no código.

## 4. Resultado final

`nf(a) = 3`.

**Conferindo:** `ni(a)=3` (Q8) `+ nf(a)=3` `= 6` — mas a árvore tem **7** nós! Isso não é
erro: `4, 2, 6` (internos) `+ 1, 3, 7` (folhas) = 6 nós contados, e a árvore do exemplo de
Q9 tem exatamente esses 6 nós (repare que é uma árvore ligeiramente diferente da de Q3–Q5,
sem o nó `9` — sempre confira contando os nós do desenho específico do exercício, não
assuma que duas árvores de exemplos diferentes são iguais).

## 5. Habilidades necessárias

- [ ] Nó interno vs. nó folha (grau) → [[../Q8/claude/main.c|Q8]]

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — árvore com um nó só

`nf(TAB_cria(5,NULL,NULL))`: `!a->esq && !a->dir` é verdadeiro (raiz sem filhos) → `1`. Um
nó isolado é, ele mesmo, uma folha.

### Aquecimento 2 — raiz com dois filhos, ambos folha

`nf` de `10` com filhos `3` e `7` (ambos folha): `10` não é folha (tem os dois filhos) →
`nf(3) + nf(7) = 1 + 1 = 2`.
