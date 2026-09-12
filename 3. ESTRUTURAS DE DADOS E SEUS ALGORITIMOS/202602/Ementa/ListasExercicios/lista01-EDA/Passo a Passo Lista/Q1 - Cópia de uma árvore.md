# Q1 — Cópia de uma árvore

> **Origem:** `lista01-EDA.pdf`, item (Q1) · **Código resolvido:** [[../Q1/claude/main.c]]
> **Antes disto, veja:** [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 03 - Representando e construindo uma árvore binária em C|1.1 Teoria 03]] (como `TAB_cria` monta um nó a partir de subárvores já prontas)

## 1. O que o exercício pede

> Escreva a função: `TAB* copia (TAB *a);`

Ou seja: dada uma árvore `a`, construir uma **árvore nova**, com a mesma forma e os mesmos
valores, mas feita de nós **diferentes** (nenhum ponteiro compartilhado com `a`) — mudar a
cópia depois não pode afetar o original.

## 2. A ideia geral (o mapa antes da viagem)

Isso é um problema de **construção recursiva**: para copiar uma árvore, basta copiar a
raiz e "colar" nela as cópias das duas subárvores — que são, elas mesmas, árvores menores,
copiadas do mesmo jeito. É a definição recursiva de árvore binária (1.1, Teoria 02)
aplicada diretamente: "árvore vazia" → copia é vazia; "nó com SAE e SAD" → copia é um nó
novo com as cópias de SAE e SAD.

## 3. Resolução passo a passo

### Passo 1 — o caso base

```c
TAB *copia(TAB *a) {
    if (!a)
        return NULL;
```

Árvore vazia (`a == NULL`) tem cópia vazia — não há nada pra copiar.

### Passo 2 — o caso recursivo

```c
    return TAB_cria(a->info, copia(a->esq), copia(a->dir));
}
```

`TAB_cria` (1.1, Teoria 03) recebe um valor e **duas subárvores já prontas**. Aqui, as
subárvores "já prontas" são exatamente `copia(a->esq)` e `copia(a->dir)` — cópias
recursivas, construídas **antes** de `TAB_cria` alocar o nó novo (`malloc` acontece dentro
de `TAB_cria`, então cada chamada recursiva de `copia` cria um nó físico diferente).

**Trace com a árvore de exemplo do código:**

```
        4
       / \
      2   6
     / \ / \
    1  3 5  7
```

| Chamada | O que faz |
|---|---|
| `copia(4)` | chama `copia(2)` e `copia(6)` antes de criar o `4` novo |
| `copia(2)` | chama `copia(1)` e `copia(3)` antes de criar o `2` novo |
| `copia(1)`, `copia(3)` | `1` e `3` são folhas — cada uma vira `TAB_cria(x, NULL, NULL)`, um nó novo |
| `copia(6)` | mesma lógica: `copia(5)`, `copia(7)`, depois cria o `6` novo |

Resultado: uma árvore idêntica em forma e valores, mas **nenhum nó compartilhado** com a
original — os `malloc`s dentro de cada `TAB_cria` garantem endereços de memória diferentes.

## 4. Resultado final

O `main` prova a independência: depois de copiar, muda `a->info = 99` (só na raiz do
original) e imprime as duas em-ordem — a cópia continua mostrando `4` no lugar da raiz,
porque é um `int` **copiado por valor**, guardado num nó **diferente**.

**Conferindo:** se `copia` compartilhasse nós (bug comum: `return a;` em vez de criar novo),
mudar `a->info` também mudaria a cópia — o teste do `main` existe exatamente para pegar esse
erro.

## 5. Habilidades necessárias

- [ ] Recursão sobre árvore binária (construir de baixo para cima) → [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 03 - Representando e construindo uma árvore binária em C|1.1 Teoria 03]]
- [ ] Diferença entre copiar um ponteiro e copiar o dado apontado → `KR`, cap. 5 (Ponteiros e Arrays), se precisar revisar.

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — copiar um único nó (folha)

`copia(TAB_cria(9, NULL, NULL))`: `a->esq` e `a->dir` são `NULL`, então `copia(a->esq) =
NULL` e `copia(a->dir) = NULL`. Resultado: `TAB_cria(9, NULL, NULL)` — um nó novo, valor 9,
sem filhos. Um `malloc` só.

### Aquecimento 2 — copiar `NULL` (árvore vazia)

`copia(NULL)`: cai direto no `if (!a) return NULL;` — devolve `NULL` sem alocar nada. É o
caso que garante que a recursão sempre para.
