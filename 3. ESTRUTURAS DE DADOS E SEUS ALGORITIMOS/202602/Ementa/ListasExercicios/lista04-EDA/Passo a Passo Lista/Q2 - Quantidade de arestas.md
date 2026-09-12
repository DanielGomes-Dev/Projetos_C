# Q2 — Quantidade de arestas (`na`)

> **Origem:** `lista04-EDA.pdf`, questão 2 · **Código resolvido:** [[../Q2/claude/main.c]]
> **Antes disto, veja:** [[Q1 - Quantidade de nós]] · [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 01 - Contando vértices e arestas|2.2 Teoria 01]]

## 1. O que o exercício pede

> "ache a quantidade de arestas: `int na(TG *g);`"

## 2. A ideia geral

- Diferente de Q1 (percurso simples de uma lista), aqui é preciso somar **duas listas
  aninhadas**: a de vértices e, para cada um, a de vizinhos.
- Estratégia: somar o grau (comprimento da lista de vizinhos) de todo vértice, depois
  **dividir por 2** — porque a representação não-orientada do curso guarda cada aresta
  duas vezes (uma em cada extremidade; ver 2.1 Teoria 06).
- Por quê funciona: cada aresta real contribui exatamente 2 unidades pra soma bruta (uma
  contagem em cada ponta) — dividir por 2 desfaz essa duplicação.

## 3. Resolução passo a passo

### Passo 1 — somar todas as listas de vizinhos

```c
int na(TG *g) {
    int soma = 0;
    for (TG *no = g; no != NULL; no = no->prox_no) {
        for (TVIZ *v = no->prim_viz; v != NULL; v = v->prox_viz)
            soma++;
    }
    return soma / 2;
}
```

### Passo 2 — trace na entrada de teste (mesmo grafo de Q1: vértices 1-5, arestas
`1-2,1-3,2-3,3-4,4-5`)

| Vértice | Lista de vizinhos (após as inserções) | Contribuição pra `soma` |
|---|---|---|
| 1 | `[3, 2]` | 2 |
| 2 | `[3, 1]` | 2 |
| 3 | `[4, 2, 1]` | 3 |
| 4 | `[5, 3]` | 2 |
| 5 | `[4]` | 1 |

`soma = 2+2+3+2+1 = 10`. `na = 10 / 2 = 5`. ✔ Bate com as 5 arestas inseridas.

### Passo 3 — o teste também remove uma aresta e confere de novo

```c
TG_retira_aresta(g, 2, 3);
printf("apos retirar aresta 2-3    = %d  (esperado: 4)\n", na(g));
```

**Conferindo:** remover `{2,3}` tira `3` da lista de `2` **e** `2` da lista de `3` — a soma
bruta cai de 10 para 8 (perde uma unidade de cada lado), `8/2 = 4`. Bate com "5 arestas
menos 1 removida = 4".

## 4. Resultado final

`na(g) = 5` antes da remoção, `4` depois. `na(NULL) = 0` (o laço de fora nunca executa).

## 5. Habilidades necessárias

- [ ] Somar comprimento de listas de vizinhos → [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 01 - Contando vértices e arestas|Teoria 01]]
- [ ] Por que cada aresta aparece duas vezes na representação → [[../../../02 - Grafos/2.1 Conceitos e Representações de Grafos/Teoria - passo a passo/Teoria 06 - Representando um grafo em C|2.1 Teoria 06]]

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — uma única aresta

Grafo `1-2` (só essa aresta). Lista de `1`: `[2]` (1 elemento). Lista de `2`: `[1]` (1
elemento). `soma = 1+1 = 2`. `na = 2/2 = 1`. ✔

### Aquecimento 2 — grafo com vértices, sem arestas

Vértices `1,2,3`, nenhuma aresta. Todas as listas de vizinhos são `NULL` (grau 0).
`soma = 0`. `na = 0/2 = 0`.
