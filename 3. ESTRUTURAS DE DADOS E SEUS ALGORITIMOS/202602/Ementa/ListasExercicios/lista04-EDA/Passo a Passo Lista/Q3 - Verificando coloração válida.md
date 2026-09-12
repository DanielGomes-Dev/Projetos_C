# Q3 — Verificando se uma coloração de grafo é válida

> **Origem:** `lista04-EDA.pdf`, questão 3 · **Código resolvido:** [[../Q3/claude/main.c]]
> **Antes disto, veja:** [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 03 - Verificando uma coloração válida|2.2 Teoria 03]]

## 1. O que o exercício pede

> Suponha que a estrutura de grafo tivesse um campo `int cor`. Teste se nós **vizinhos**
> não têm a mesma cor. Retorna 1 se **nenhum** par de vizinhos compartilha a cor (coloração
> válida) e 0 caso contrário: `int nao_tem_mesma_cor(TG *g);`

Ou seja: para toda aresta `{u,v}` do grafo, seria preciso que `cor(u) ≠ cor(v)` — a função
verifica se essa condição vale para **todas** as arestas de uma vez.

## 2. A ideia geral

Isso é o problema de **coloração de grafos** (usado, por exemplo, em alocação de registrador
em compiladores, ou em montagem de horários sem conflito): pintar cada vértice com uma cor,
de forma que vizinhos nunca compartilhem cor. Aqui não é para **encontrar** uma coloração —
é só **verificar** se uma coloração já dada é válida, o que é bem mais simples: basta olhar
cada aresta uma vez (ou duas, ver seção 3) e comparar as cores das duas pontas.

**Detalhe de implementação:** o `TG.h` do curso não tem campo `cor` — o enunciado pede "se a
estrutura *tivesse*". A solução resolve isso redefinindo uma versão local da struct com o
campo extra (`typedef struct grafo { ...; int cor; ...} TG;`), deixando o arquivo
autocontido e compilável sozinho, sem mexer no `TG.h` original (que outras questões usam).

## 3. Resolução passo a passo

### Passo 1 — percorrer cada nó e cada vizinho, comparando cores

```c
int nao_tem_mesma_cor(TG *g) {
    for (TG *u = g; u != NULL; u = u->prox_no) {
        for (TVIZ *v = u->prim_viz; v != NULL; v = v->prox_viz) {
            TG *pv = busca_no(g, v->id_viz);
            if (pv && pv->cor == u->cor)
                return 0;
        }
    }
    return 1;
}
```

- Ponteiro mudou? Sim: `busca_no(g, v->id_viz)` percorre a lista de vértices **de novo**,
  a partir do início (`g`), para achar o nó vizinho `v` e conhecer sua cor — a lista de
  adjacência só guarda o **id** do vizinho (`v->id_viz`), não um ponteiro direto para ele.
- Loop duplo: `for (u)` anda pela lista de vértices; `for (v)` anda pela lista de vizinhos
  de `u`. É a mesma estrutura de dois laços encaixados de [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 01 - Contando vértices e arestas|Teoria 01]] (contar arestas).
- `if (pv && pv->cor == u->cor) return 0;` — assim que **um** par de vizinhos com cor igual
  aparece, a função para imediatamente (não precisa terminar de olhar o resto do grafo).

### Passo 2 — traçando com o Exemplo 1 do código (triângulo com 3 cores)

Grafo: vértices `1`(cor 0), `2`(cor 1), `3`(cor 2); arestas `{1,2}, {2,3}, {1,3}`
(não-orientado — cada aresta em ambas as listas).

| `u` | vizinhos de `u` | cores comparadas | conflito? |
|---|---|---|---|
| `1` (cor 0) | `2, 3` | `cor(2)=1≠0` ✔; `cor(3)=2≠0` ✔ | não |
| `2` (cor 1) | `1, 3` | `cor(1)=0≠1` ✔; `cor(3)=2≠1` ✔ | não |
| `3` (cor 2) | `1, 2` | `cor(1)=0≠2` ✔; `cor(2)=1≠2` ✔ | não |

Nenhum conflito encontrado em nenhuma das 6 comparações (cada aresta checada 2 vezes, uma
por extremidade) → retorna `1`. Bate com o comentário do código (`esperado: 1`).

### Passo 3 — traçando com o Exemplo 2 (conflito: 1 e 2 com a mesma cor)

Mesmo triângulo, mas `1`(cor 0) e `2`(cor 0) — mesma cor.

| `u` | vizinho examinado | comparação | conflito? |
|---|---|---|---|
| `1` (cor 0) | `2` (primeiro da lista de vizinhos de `1`) | `cor(2)=0 == cor(1)=0` | **sim — para aqui** |

A função retorna `0` já na **primeira** comparação (não precisa nem olhar o vizinho `3` de
`1`, nem os outros nós) — bate com o comentário (`esperado: 0`).

## 4. Resultado final

`nao_tem_mesma_cor(g1) = 1` (coloração válida) e `nao_tem_mesma_cor(g2) = 0` (inválida) —
exatamente o que o `main` imprime.

**Conferindo:** para o grafo 1, é possível verificar manualmente que 3 cores distintas
aplicadas a um triângulo (onde os 3 vértices são todos vizinhos entre si) sempre formam uma
coloração válida — é o caso mínimo de coloração de um triângulo (precisa de pelo menos 3
cores, nunca menos, porque os 3 vértices são mutuamente vizinhos).

## 5. Habilidades necessárias

- [ ] Representação de grafo em lista de adjacência dupla (não-orientado) → [[../../../02 - Grafos/2.1 Conceitos e Representações de Grafos/Teoria - passo a passo/Teoria 06 - Representando um grafo em C|2.1 Teoria 06]]
- [ ] Percorrer todos os vértices e, para cada um, todos os vizinhos (laço duplo) → [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 01 - Contando vértices e arestas|2.2 Teoria 01]]

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — dois vértices, cores diferentes

Grafo: `1`(cor 0) `— 2`(cor 1), uma aresta. `nao_tem_mesma_cor`: `u=1`, vizinho `2`,
`cor(2)=1 ≠ cor(1)=0` ✔. `u=2`, vizinho `1`, `cor(1)=0 ≠ cor(2)=1` ✔. Sem conflito →
retorna `1`.

### Aquecimento 2 — dois vértices, mesma cor

Mesmo grafo, mas os dois com cor `5`. `u=1`, vizinho `2`, `cor(2)=5 == cor(1)=5` → conflito,
retorna `0` imediatamente.
