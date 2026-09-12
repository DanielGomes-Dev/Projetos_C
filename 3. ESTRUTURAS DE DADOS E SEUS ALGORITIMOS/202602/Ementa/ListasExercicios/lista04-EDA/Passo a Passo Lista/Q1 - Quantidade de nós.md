# Q1 — Quantidade de nós (`nn`)

> **Origem:** `lista04-EDA.pdf`, questão 1 · **Código resolvido:** [[../Q1/claude/main.c]]
> **Antes disto, veja:** [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 01 - Contando vértices e arestas|2.2 Teoria 01 - Contando vértices e arestas]]

## 1. O que o exercício pede

> "Dada a seguinte representação de grafos [`TG`/`TVIZ`, lista de adjacência]: descubra a
> quantidade de nós: `int nn(TG *g);`"

Ou seja: escrever uma função que recebe um grafo (no formato usado no curso) e devolve
quantos vértices ele tem.

## 2. A ideia geral

- Que tipo de problema é este? É um percurso simples sobre uma **lista encadeada** — o
  grafo (Teoria 06 de 2.1) é literalmente uma lista ligada de vértices (`TG`), então
  "contar vértices" é o mesmo problema de "contar nós de uma lista encadeada".
- Estratégia: percorrer a lista de `prox_no` em `prox_no`, incrementando um contador, até
  chegar em `NULL`.
- Por que funciona: cada `TG_ins_no` bem-sucedido cria exatamente um nó novo na lista —
  contar os nós da lista é contar os vértices do grafo, por construção.

## 3. Resolução passo a passo

### Passo 1 — percorrer a lista de vértices contando

```c
int nn(TG *g) {
    int total = 0;
    while (g) {
        total++;
        g = g->prox_no;
    }
    return total;
}
```

Nada aqui olha `prim_viz` (a lista de vizinhos) — a função é "cega" para arestas, só
enxerga a cadeia de vértices.

### Passo 2 — a entrada usada no teste (`exemplo()`, dentro do `main`)

```c
static TG *exemplo(void) {
    TG *g = TG_inicializa();
    for (int i = 5; i >= 1; i--)
        g = TG_ins_no(g, i);
    TG_ins_aresta(g, 1, 2);
    TG_ins_aresta(g, 1, 3);
    TG_ins_aresta(g, 2, 3);
    TG_ins_aresta(g, 3, 4);
    TG_ins_aresta(g, 4, 5);
    return g;
}
```

**Trace do laço `for (int i = 5; i >= 1; i--) g = TG_ins_no(g, i);`:**

| Iteração | `i` | Lista de vértices depois (da frente pro fim) |
|---|---|---|
| 1 | 5 | `5` |
| 2 | 4 | `4 → 5` |
| 3 | 3 | `3 → 4 → 5` |
| 4 | 2 | `2 → 3 → 4 → 5` |
| 5 | 1 | `1 → 2 → 3 → 4 → 5` |

(`TG_ins_no` sempre insere no início — por isso inserir `5,4,3,2,1` nessa ordem resulta em
`1` na frente.) As 5 arestas depois não mudam a **quantidade** de vértices, só preenchem
as listas de vizinhos.

## 4. Resultado final

`nn(g) = 5`. O teste confere isso e mais um caso-limite:

```c
printf("Quantidade de nos (nn) = %d  (esperado: 5)\n", nn(g));
printf("nn(grafo vazio)        = %d  (esperado: 0)\n", nn(NULL));
```

**Conferindo:** `nn(NULL)` — o `while (g)` nunca executa (`g` já é `NULL`), `total`
permanece `0` — bate com "grafo vazio tem 0 vértices".

## 5. Habilidades necessárias

- [ ] Percorrer lista encadeada contando elementos → [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 01 - Contando vértices e arestas|Teoria 01]]
- [ ] Struct `TG`/`TVIZ` e como o grafo é montado → [[../../../02 - Grafos/2.1 Conceitos e Representações de Grafos/Teoria - passo a passo/Teoria 06 - Representando um grafo em C|2.1 Teoria 06]]

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — grafo com 1 vértice, sem aresta

```c
TG *g = TG_ins_no(TG_inicializa(), 7);
```

Trace: `total=0, g=nó7` → `total=1, g=NULL` → devolve `1`.

### Aquecimento 2 — grafo vazio

`nn(NULL)`: o `while` nunca roda, devolve `0` direto.
