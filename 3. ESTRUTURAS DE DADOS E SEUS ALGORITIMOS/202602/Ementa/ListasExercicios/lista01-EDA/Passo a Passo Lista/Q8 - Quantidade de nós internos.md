# Q8 — Quantidade de nós internos

> **Origem:** `lista01-EDA.pdf`, item (Q8) · **Código resolvido:** [[../Q8/claude/main.c]]
> **Antes disto, veja:** [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 01 - O que é uma árvore (terminologia)|1.1 Teoria 01]] (definição de nó interno: grau > 0)

## 1. O que o exercício pede

> Descubra a quantidade de nós internos: `int ni(TAB *a);`

Nó interno (1.1, Teoria 01) = nó com **pelo menos um filho** (grau maior que zero).

## 2. A ideia geral

Percorrer a árvore inteira (não importa a ordem — 1.1, Teoria 04) contando 1 para cada nó
que tem `esq` ou `dir` não-nulo, e somando essa contagem com o total das duas subárvores.

## 3. Resolução passo a passo

```c
int ni(TAB *a) {
    if (!a)
        return 0;
    int este = (a->esq || a->dir) ? 1 : 0;
    return este + ni(a->esq) + ni(a->dir);
}
```

> 📖 **Lendo devagar:**
> 1. `if (!a) return 0;` — árvore vazia não tem nó nenhum pra contar.
> 2. `este = (a->esq || a->dir) ? 1 : 0` — `1` se **pelo menos um** dos dois filhos existe
>    (é exatamente a definição de "grau > 0"), `0` caso contrário (nó é folha).
> 3. `este + ni(a->esq) + ni(a->dir)` — soma "este nó conta ou não" com a contagem
>    recursiva de cada subárvore. Repare que **não importa qual percurso** isso implementa
>    (não há `printf` em ordem específica) — é só uma soma acumulada.

**Conferindo com a árvore do exemplo:**

```
        4
       / \
      2   6
     / \   \
    1  3    7
```

| Nó | Tem filho? | Conta como interno? |
|---|---|---|
| `4` | sim (`2`, `6`) | sim |
| `2` | sim (`1`, `3`) | sim |
| `6` | sim (`7`, sem esq.) | sim |
| `1`, `3`, `7` | não | não (são folhas) |

Total: `3` (os nós `4`, `2`, `6`). ✔ Bate com o comentário no código.

## 4. Resultado final

`ni(a) = 3`.

**Conferindo:** `ni(a) + nf(a)` (Q9) deve ser igual ao **total de nós** da árvore — todo nó
é interno **ou** folha, nunca as duas coisas, nunca nenhuma.

## 5. Habilidades necessárias

- [ ] Nó interno vs. nó folha (grau) → [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 01 - O que é uma árvore (terminologia)|1.1 Teoria 01]]

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — árvore com um nó só

`ni(TAB_cria(5,NULL,NULL))`: `este = 0` (sem filhos) + `ni(NULL)=0` + `ni(NULL)=0` = `0`.
Um nó isolado é folha, não interno.

### Aquecimento 2 — raiz com um filho só

`ni` de `10` com filho esquerdo `3` (folha): `10` tem `esq` não-nulo → `este=1`.
`ni(esq)=ni(3)=0`. `ni(dir)=ni(NULL)=0`. Total: `1`.
