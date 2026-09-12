# Q6 — Retirar todos os elementos pares da árvore

> **Origem:** `lista01-EDA.pdf`, item (Q6) · **Código resolvido:** [[../Q6/claude/main.c]]
> **Antes disto, veja:** [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 04 - Percursos em profundidade (pré-ordem, em-ordem, pós-ordem)|1.1 Teoria 04]] (por que processar os filhos antes do pai é útil pra liberar memória)

## 1. O que o exercício pede

> Uma função que, dada uma árvore binária qualquer, retire todos os elementos pares da
> árvore original: `TAB* retira_pares (TAB* arv);`

É o exercício mais delicado da lista: não é só "achar e apagar" — quando um nó par é
removido, os filhos dele **não podem sumir junto**; eles precisam ser realocados em algum
lugar da árvore que sobra.

## 2. A ideia geral (o mapa antes da viagem)

Como a árvore **não** tem propriedade de busca (é binária qualquer, não BST), não existe
"substituir pelo sucessor" como se faria numa BST (1.2) — a ordem entre os valores não
importa aqui, só a forma da árvore precisa continuar válida (todo nó com no máximo 2
filhos). A estratégia adotada:

1. Resolve **primeiro** as subárvores esquerda e direita (pós-ordem — 1.1 Teoria 04) — assim,
   quando chegar a vez do nó atual, seus filhos já estão "limpos" (sem pares).
2. Se o nó atual é par, ele é removido, e seus dois filhos (já limpos) precisam ser
   religados em algum lugar: a subárvore direita é **pendurada** no descendente mais à
   direita da subárvore esquerda (ou, se não houver subárvore esquerda, a direita simplesmente
   toma o lugar do nó removido).

## 3. Resolução passo a passo

### Passo 1 — a função auxiliar `anexa_a_direita`

```c
static TAB *anexa_a_direita(TAB *raiz, TAB *sub) {
    if (!raiz)
        return sub;
    TAB *p = raiz;
    while (p->dir)
        p = p->dir;
    p->dir = sub;
    return raiz;
}
```

> 📖 **Lendo devagar:** esta função pendura `sub` no **descendente mais à direita** de
> `raiz`. `while (p->dir) p = p->dir;` desce por `dir` até achar o nó que **não tem** filho
> direito (o "fim da fila" à direita) — aí, `p->dir = sub` prega a subárvore ali. Se `raiz`
> for `NULL` (não havia subárvore esquerda pra receber), a função simplesmente devolve
> `sub` — a subárvore direita vira "a árvore inteira" que sobra.

### Passo 2 — a função principal, lida devagar

```c
TAB *retira_pares(TAB *arv) {
    if (!arv)
        return NULL;

    arv->esq = retira_pares(arv->esq);
    arv->dir = retira_pares(arv->dir);

    if (arv->info % 2 == 0) {
        TAB *e = arv->esq, *d = arv->dir;
        free(arv);
        return anexa_a_direita(e, d);
    }
    return arv;
}
```

> 📖 **Lendo devagar:**
> 1. `arv->esq = retira_pares(arv->esq)` — resolve a subárvore esquerda **primeiro**, e já
>    substitui `arv->esq` pelo resultado (que pode ter menos nós, ou até virar `NULL`).
> 2. `arv->dir = retira_pares(arv->dir)` — mesma coisa à direita. **Depois destas duas
>    linhas, os filhos de `arv` já estão sem nenhum número par.**
> 3. `if (arv->info % 2 == 0)` — só agora verifica **o próprio nó**. Fazer isso depois dos
>    filhos (não antes) é o que garante que `e` e `d`, guardados a seguir, já estão limpos.
> 4. `TAB *e = arv->esq, *d = arv->dir; free(arv);` — guarda os ponteiros dos filhos (já
>    limpos) **antes** de liberar `arv`, porque depois do `free` esses campos não existem
>    mais.
> 5. `return anexa_a_direita(e, d);` — pendura a subárvore direita (`d`) no fim-à-direita da
>    esquerda (`e`), e devolve isso no lugar do nó `arv` que acabou de ser removido.

### Passo 3 — conferindo com a árvore do exemplo

```
        4
       / \
      2   7
     / \   \
    1  3    8
            /
           5
```

**Trace (pós-ordem — resolve de baixo pra cima):**

| Nó processado | Par? | O que acontece |
|---|---|---|
| `1` (folha) | não | permanece |
| `3` (folha) | não | permanece |
| `2` | **sim** | `e=1`, `d=3`; remove `2`; `anexa_a_direita(1, 3)` → pendura `3` no fim-à-direita de `1` (que não tem filho direito) → resultado: `1` com filho direito `3` |
| `5` (folha) | não | permanece |
| `8` | **sim** | `e=5`, `d=NULL`; remove `8`; `anexa_a_direita(5, NULL)` → `5` já não tem `dir`, pendurar `NULL` não muda nada → resultado: só `5` |
| `7` | não | `arv->dir` agora é o resultado acima (`5`) — `7` permanece, com filho direito `5` |
| `4` (raiz) | **sim** | `e` = (resultado da esquerda: `1` com filho direito `3`), `d` = (resultado da direita: `7` com filho direito `5`); remove `4`; `anexa_a_direita(e, d)` desce por `e->dir` até `3` (que não tem `dir`) e pendura `d` ali |

**Árvore final:**
```
      1
       \
        3
         \
          7
           \
            5
```

Todos ímpares (`1, 3, 7, 5`), nenhum par restou. ✔

## 4. Resultado final

O `main` imprime em pré-ordem e em-ordem depois da remoção — ambas devem mostrar só
números ímpares.

**Conferindo:** o total de nós depois deve ser igual ao total de nós ímpares antes (aqui:
`1,3,7,5` = 4 nós ímpares de 7 originais, batendo com o resultado).

## 5. Habilidades necessárias

- [ ] Pós-ordem: resolver filhos antes do nó atual → [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 04 - Percursos em profundidade (pré-ordem, em-ordem, pós-ordem)|1.1 Teoria 04]]
- [ ] Guardar ponteiros antes de `free` → `KR`, cap. 5 (cuidado clássico com `malloc`/`free`).

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — remover a raiz par, sem filho esquerdo

Árvore: `4` (raiz, par) com filho direito `7` (folha), sem filho esquerdo. `e = NULL`,
`d = 7`. `anexa_a_direita(NULL, 7)` → como `raiz` é `NULL`, devolve `7` direto. Resultado:
árvore vira só `7`.

### Aquecimento 2 — nenhum par na árvore

Árvore `1` com filhos `3` e `5` (todos ímpares): nenhum `if (arv->info % 2 == 0)` dispara
em lugar nenhum — a árvore volta exatamente igual, sem nenhum `anexa_a_direita` chamado.
