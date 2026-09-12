# Q4 — Menor elemento da árvore

> **Origem:** `lista01-EDA.pdf`, item (Q4) · **Código resolvido:** [[../Q4/claude/main.c]]
> **Antes disto, veja:** [[../Q3/claude/main.c|Q3 - Maior elemento da árvore]] (mesmo algoritmo, só troca o sentido da comparação)

## 1. O que o exercício pede

> Menor elemento da árvore: `TAB* menor(TAB *a);`

Igual a Q3, mas procurando o **menor** valor em vez do maior.

## 2. A ideia geral

Exatamente a mesma estratégia de Q3 (a árvore é binária qualquer, sem ordenação — força
bruta, olhando todos os nós). A única mudança no código é o **sentido dos dois `if`**:

```c
if (e && e->info < m->info) m = e;   // era > em Q3, agora é <
if (d && d->info < m->info) m = d;
```

## 3. Resolução passo a passo

### Conferindo com a mesma árvore de Q3

```
        7
       / \
     20   3
     / \   \
    5  11   9
```

| Chamada | `e` | `d` | `m` inicial | `m` final |
|---|---|---|---|---|
| `menor(5)` (folha) | — | — | `5` | `5` |
| `menor(11)` (folha) | — | — | `11` | `11` |
| `menor(20)` | `5` | `11` | `20` | `5` (`5<20`) |
| `menor(9)` (folha) | — | — | `9` | `9` |
| `menor(3)` | `NULL` | `9` | `3` | `3` (`9` não é `< 3`) |
| `menor(7)` (raiz) | `5` | `3` | `7` | `3` (`5<7`, depois `3<5`) |

**Resultado:** o nó `3`. ✔ É de fato o menor valor da árvore.

## 4. Resultado final

`m ? m->info : 0` imprime `3`.

**Conferindo:** some `maior(a)->info` (Q3, resultado `20`) e `menor(a)->info` (`3`) — os
dois precisam necessariamente aparecer em algum percurso da árvore (1.1, Teoria 04); se
algum deles não bater com uma inspeção visual da árvore desenhada, há bug numa das duas
funções.

## 5. Habilidades necessárias

- [ ] Percorrer árvore binária sem propriedade de busca (força bruta) → [[../Q3/claude/main.c|Q3]]

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — árvore com um nó só

`menor(TAB_cria(42, NULL, NULL))`: `e = d = NULL`, nenhum `if` dispara, `m` permanece o
próprio `42`.

### Aquecimento 2 — menor está numa folha à esquerda

Árvore `10` com filho esquerdo `2` (folha) e filho direito `15` (folha): `e->info=2 < 10` →
`m=2`; depois `d->info=15`, `15 < 2`? Não — `m` continua `2`. Resultado: `2`.
