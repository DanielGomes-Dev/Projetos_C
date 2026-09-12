# Q5 — Testando se dois grafos são iguais

> **Origem:** `lista04-EDA.pdf`, questão 5 · **Código resolvido:** [[../Q5/claude/main.c]]
> **Antes disto, veja:** [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 04 - Testando se dois grafos são iguais|2.2 Teoria 04]]

## 1. O que o exercício pede

> Testar se dois grafos são **iguais**: `int ig(TG *g1, TG *g2);` — não é isomorfismo
> (problema difícil), é igualdade "rotulada": os dois grafos têm exatamente o **mesmo
> conjunto de ids de nós** e, para cada nó, exatamente o **mesmo conjunto de vizinhos**. A
> **ordem** em que nós e vizinhos aparecem nas listas não importa.

## 2. A ideia geral

"Mesmo conjunto" (não "mesma lista", que se importaria com ordem) pede uma estratégia de
**dupla inclusão**: para provar que dois conjuntos são iguais, basta mostrar que um está
contido no outro **e** que eles têm o mesmo tamanho (o que fecha a inclusão no sentido
contrário sem precisar checar de novo). O código aplica essa ideia em dois níveis: uma vez
para o conjunto de **vértices**, outra vez, dentro de cada vértice, para o conjunto de
**vizinhos**.

## 3. Resolução passo a passo

### Passo 1 — descartar rápido pelo tamanho

```c
if (nn(g1) != nn(g2))
    return 0;
```

Se o número de vértices já é diferente, os grafos não podem ser iguais — nem vale a pena
comparar o resto. `nn` é a mesma função de [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 01 - Contando vértices e arestas|Teoria 01]], reimplementada aqui localmente (`static int nn(TG *g)`).

### Passo 2 — para cada vértice de g1, confirmar presença e vizinhança em g2

```c
for (TG *u = g1; u != NULL; u = u->prox_no) {
    TG *u2 = TG_busca_no(g2, u->id_no);
    if (!u2) return 0;

    for (TVIZ *w = u->prim_viz; w != NULL; w = w->prox_viz)
        if (!TG_busca_aresta(g2, u->id_no, w->id_viz))
            return 0;

    if (grau(u) != grau(u2)) return 0;
}
```

- `TG_busca_no(g2, u->id_no)` — o vértice `u` de `g1` **precisa existir** em `g2` (mesmo id).
  Se não existir, os grafos já diferem.
- laço interno (`for (w)`) — para **cada vizinho** `w` de `u` (em `g1`), confirma que a
  aresta `{u, w}` **também existe** em `g2` (`TG_busca_aresta`). Isso garante que todo
  vizinho de `u` em `g1` também é vizinho dele em `g2` (uma direção da dupla inclusão, ao
  nível de vizinhança).
- `if (grau(u) != grau(u2)) return 0;` — o **truque** que evita ter que checar a inclusão
  no sentido contrário (vizinhos de `u2` em `g2` que talvez não estejam em `g1`): se os
  graus batem, e já confirmamos que todo vizinho de `g1` está em `g2`, então **não sobra
  espaço** para `g2` ter um vizinho a mais — os dois conjuntos de vizinhos são idênticos.

### Passo 3 — conferindo com os grafos A e B do código (mesmas arestas, ordem diferente)

`A`: vértices `{1,2,3,4}`, arestas inseridas na ordem `{1,2},{2,3},{3,4}`.
`B`: mesmos vértices, arestas inseridas na ordem `{3,4},{1,2},{2,3}` (mesmo conjunto, ordem
diferente de inserção).

| `u` (de A) | vizinhos de `u` em A | existe em B? | grau(u) vs grau(u2) |
|---|---|---|---|
| `4` | `3` | `TG_busca_aresta(B,4,3)` existe ✔ | grau 1 = grau 1 ✔ |
| `3` | `2, 4` | ambas existem em B ✔ | grau 2 = grau 2 ✔ |
| `2` | `1, 3` | ambas existem em B ✔ | grau 2 = grau 2 ✔ |
| `1` | `2` | existe em B ✔ | grau 1 = grau 1 ✔ |

(ordem de percurso `4,3,2,1` porque `TG_ins_no` insere no início, e os vértices foram
inseridos na ordem `1,2,3,4` dentro de `monta`.)

Nenhum retorno `0` ao longo do laço → `ig(A,B) = 1`. ✔ (bate com `esperado: 1` do código —
confirma que a ordem de inserção não afeta o resultado.)

### Passo 4 — conferindo com A e C (C tem uma aresta a mais: `{1,4}`)

Ao processar `u=1` (ou `u=4`, dependendo de qual é visitado antes — `1` tem vizinho extra
em C, mas o laço percorre os vizinhos **de A**, não de C): `nn(A)=nn(C)=4` (passo 1 não
descarta, mesmo número de vértices). No laço, para `u=1` (vizinhos em A: só `2`) —
`TG_busca_aresta(C,1,2)` existe ✔; mas `grau(1) em A = 1`, enquanto `grau(1) em C = 2`
(ganhou o vizinho `4`) → **`grau(u) != grau(u2)`** → retorna `0`.

**Isso mostra por que o passo do grau é necessário**: sem ele, o laço só confirma que "todo
vizinho de `A` está em `C`" — o que é verdade! (`C` é um superconjunto de arestas de `A`.)
Sem comparar os graus, a função erraria e diria que são iguais. A comparação de grau é o
que detecta que `C` tem uma aresta **a mais** que `A` não tem.

## 4. Resultado final

`ig(A,B)=1`, `ig(A,C)=0`, `ig(A,A)=1` — conforme os comentários do código.

**Conferindo `ig(A,A)`:** comparar um grafo consigo mesmo sempre dá `1` nesta função —
`nn` bate trivialmente, todo vértice se acha a si mesmo em `TG_busca_no`, toda aresta se
acha a si mesma, e todo grau é igual a ele mesmo.

## 5. Habilidades necessárias

- [ ] Busca de vértice e de aresta em lista de adjacência → [[../../../02 - Grafos/2.1 Conceitos e Representações de Grafos/Teoria - passo a passo/Teoria 06 - Representando um grafo em C|2.1 Teoria 06]]
- [ ] Contar vértices e grau de um nó → [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 01 - Contando vértices e arestas|2.2 Teoria 01]]
- [ ] Estratégia de dupla inclusão para provar igualdade de conjuntos → [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 04 - Testando se dois grafos são iguais|2.2 Teoria 04]]

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — dois grafos idênticos com 1 vértice, sem arestas

`g1 = {1}` (sem arestas), `g2 = {1}` (sem arestas). `nn` bate (1=1). Laço: `u=1`, existe em
`g2` ✔, sem vizinhos para checar, `grau(1)=0` nos dois ✔. Retorna `1`.

### Aquecimento 2 — mesmo número de vértices, ids diferentes

`g1 = {1,2}` com aresta `{1,2}`; `g2 = {1,3}` com aresta `{1,3}`. `nn` bate (2=2). Laço:
`u=1` (de g1), existe em g2 ✔ (mesmo id `1`); vizinho de `1` em g1 é `2` —
`TG_busca_aresta(g2, 1, 2)`? Não existe (g2 só tem aresta `{1,3}`) → retorna `0`.
