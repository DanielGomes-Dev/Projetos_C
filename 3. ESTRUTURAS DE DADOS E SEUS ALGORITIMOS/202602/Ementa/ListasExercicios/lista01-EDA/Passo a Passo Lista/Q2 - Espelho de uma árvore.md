# Q2 — Espelho de uma árvore

> **Origem:** `lista01-EDA.pdf`, item (Q2) · **Código resolvido:** [[../Q2/claude/main.c]]
> **Antes disto, veja:** [[../Q1/claude/main.c|Q1 - Cópia de uma árvore]] (mesma estrutura de recursão, só troca o que é copiado)

## 1. O que o exercício pede

> Espelho de uma árvore (o que está à esquerda na árvore original estará à direita no
> espelho, e vice-versa): `TAB* espelho (TAB *a);`

Ou seja: construir uma árvore nova onde, em **todo** nó, o que era subárvore esquerda vira
subárvore direita, e vice-versa — recursivamente, não só na raiz.

## 2. A ideia geral

Isso é quase idêntico a Q1 (cópia): a diferença é uma linha só. Em vez de
`TAB_cria(a->info, copia(a->esq), copia(a->dir))` (mesma ordem), aqui os argumentos de
`esq`/`dir` **trocam de lugar**: `TAB_cria(a->info, espelho(a->dir), espelho(a->esq))`.

> **Por que "recursivo" e não só "trocar a->esq com a->dir na raiz"?** Porque espelhar só a
> raiz deixaria as subárvores inteiras (com todos os seus próprios filhos) do jeito
> original — só a "casca de fora" mudaria. O espelho de verdade precisa inverter esquerda↔
> direita **em cada nível**, por isso a troca acontece dentro da chamada recursiva também.

## 3. Resolução passo a passo

### Passo 1 — a troca, lida devagar

```c
TAB *espelho(TAB *a) {
    if (!a)
        return NULL;
    return TAB_cria(a->info, espelho(a->dir), espelho(a->esq));
}
```

> 📖 **Lendo `TAB_cria(a->info, espelho(a->dir), espelho(a->esq))` de dentro pra fora:**
> 1. `espelho(a->dir)` — espelha a subárvore **direita** original...
> 2. ...e o resultado vira o **segundo** argumento de `TAB_cria`, que é o campo **`esq`**
>    do nó novo.
> 3. `espelho(a->esq)` — espelha a subárvore **esquerda** original, e o resultado vira o
>    campo **`dir`** do nó novo.
> 4. Ou seja: **o que era direita virou esquerda, e o que era esquerda virou direita** —
>    exatamente a definição do exercício, aplicada neste nó **e**, recursivamente, em
>    todos os nós abaixo dele.

### Passo 2 — conferindo com a árvore do exemplo

```
        1                    1
       / \                  / \
      2   3      →         3   2
     /   / \               / \   \
    4   5   6             6   5   4
```

| Nó original | Filhos originais (esq, dir) | Filhos no espelho (esq, dir) |
|---|---|---|
| `1` (raiz) | `2`, `3` | `espelho(3)`, `espelho(2)` |
| `2` | `4`, — | no espelho, sob o `2` (agora à direita): —, `espelho(4)` = `4` (folha, sem troca visível) |
| `3` | `5`, `6` | no espelho, sob o `3` (agora à esquerda): `espelho(6)`, `espelho(5)` = `6`, `5` |

**Pré-ordem original:** `1, 2, 4, 3, 5, 6`. **Pré-ordem do espelho:** `1, 3, 6, 5, 2, 4` —
repare que não é simplesmente a lista invertida (`6,5,3,4,2,1`); é a **estrutura** que
inverteu, o que muda a ordem de visita de um jeito mais sutil que só "de trás pra frente".

## 4. Resultado final

O `main` imprime `TAB_imp_ident` (impressão identada) do original e do espelho lado a lado
— é a forma mais fácil de **ver visualmente** que esquerda e direita trocaram em todos os
níveis, não só na raiz.

**Conferindo:** o espelho do espelho deveria devolver a árvore original (aplicar a troca
duas vezes desfaz a troca) — um bom teste extra seria `igual(a, espelho(espelho(a)))` (ver
Q5) dar `1`.

## 5. Habilidades necessárias

- [ ] Recursão sobre árvore binária, construindo uma árvore nova → [[../Q1/claude/main.c|Q1]]
- [ ] Ler uma chamada composta de dentro pra fora → [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 03 - Representando e construindo uma árvore binária em C|1.1 Teoria 03]]

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — espelhar um nó com um filho só

`espelho(TAB_cria(1, TAB_cria(2, NULL, NULL), NULL))`: o `1` tem filho esquerdo `2` e
nenhum filho direito. `espelho(a->dir) = espelho(NULL) = NULL` (vira o novo `esq`).
`espelho(a->esq) = espelho(2) = TAB_cria(2, NULL, NULL)` (vira o novo `dir`). Resultado:
`1` com filho **direito** `2` — o filho que era à esquerda passou pra direita.

### Aquecimento 2 — espelhar uma folha

`espelho(TAB_cria(5, NULL, NULL))`: ambos os filhos são `NULL`, então trocar `NULL` por
`NULL` não muda nada — o espelho de uma folha é ela mesma (com valor igual, nó diferente).
