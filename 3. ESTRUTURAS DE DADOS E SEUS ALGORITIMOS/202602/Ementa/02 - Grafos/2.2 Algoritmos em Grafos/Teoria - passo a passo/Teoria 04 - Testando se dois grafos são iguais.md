# Teoria 04 — Testando se dois grafos são iguais

> **Onde isto entra:** o algoritmo mais elaborado deste subtópico — combina os padrões das
> Teorias 01–03 (contar, testar propriedade em todo vértice, buscar) num único algoritmo
> de comparação.
> **Antes:** [[Teoria 03 - Verificando uma coloração válida]].
> **Fonte:** exercício da lista04-EDA (Q5), representação `TG`/`TVIZ` do curso.

## 1. A ideia em uma frase

Dois grafos são "iguais" (aqui, **igualdade rotulada** — não confundir com isomorfismo)
quando têm exatamente o **mesmo conjunto de vértices** e, para cada vértice, exatamente o
**mesmo conjunto de vizinhos** — não importa a ordem em que estão guardados nas listas.

## 2. Por que "mesma ordem nas listas" não pode ser exigido

`TG_ins_no` e `TG_ins_aresta` sempre inserem **no início** da lista (Teoria 06 de 2.1) —
então o mesmo grafo, construído inserindo vértices/arestas em ordens diferentes, pode
ficar com listas em ordens **diferentes**, mesmo representando exatamente a mesma
estrutura. Comparar "campo a campo, na mesma posição" daria falso-negativo. O algoritmo
precisa comparar **conjuntos**, não sequências.

## 3. A estratégia (motivação antes do código)

Para provar que dois conjuntos são iguais, uma forma clássica é a **dupla inclusão**: A é
subconjunto de B, B é subconjunto de A, logo A = B. Aqui, adaptado: primeiro confere que
o número de vértices bate (atalho rápido); depois, para cada vértice de `g1`, confere que
ele existe em `g2` **com exatamente os mesmos vizinhos**.

## 4. O algoritmo — lido devagar

```c
int ig(TG *g1, TG *g2) {
    if (nn(g1) != nn(g2))
        return 0;

    for (TG *u = g1; u != NULL; u = u->prox_no) {
        TG *u2 = TG_busca_no(g2, u->id_no);
        if (!u2)
            return 0;

        for (TVIZ *w = u->prim_viz; w != NULL; w = w->prox_viz)
            if (!TG_busca_aresta(g2, u->id_no, w->id_viz))
                return 0;

        if (grau(u) != grau(u2))
            return 0;
    }
    return 1;
}
```

> 📖 **Lendo devagar, passo a passo:**
> 1. `if (nn(g1) != nn(g2)) return 0;` — **atalho barato primeiro**: se o número de
>    vértices já é diferente, não tem como serem iguais — corta sem nem olhar arestas
>    (reaproveita `nn` da Teoria 01).
> 2. Laço de fora: para cada vértice `u` de `g1`...
> 3. `TG_busca_no(g2, u->id_no)` — existe um vértice com o **mesmo id** em `g2`? Se não
>    existir (`!u2`), os conjuntos de vértices já diferem → `return 0`.
> 4. Laço de dentro: para cada vizinho `w` de `u` (em `g1`)...
> 5. `TG_busca_aresta(g2, u->id_no, w->id_viz)` — será que **essa mesma aresta** também
>    existe em `g2`? Se não, `g1` tem uma conexão que `g2` não tem → `return 0`.
> 6. `if (grau(u) != grau(u2)) return 0;` — **o motivo desta linha existir:** o passo 5 só
>    provou que **todo vizinho de `u` em `g1` também é vizinho em `g2`** — isso garante que
>    o conjunto de vizinhos de `g1` está **contido** no de `g2`, mas não impede que `g2`
>    tenha vizinhos **a mais**. Comparar os graus fecha essa lacuna: se os tamanhos batem
>    e um conjunto já está contido no outro, eles são **exatamente iguais**.

## 5. Conferindo com número concreto

`g1`: vértices `{1,2,3,4}`, arestas `{1,2},{2,3},{3,4}`.
`g2` (mesmas arestas, inseridas em ordem diferente): `{3,4},{1,2},{2,3}`.

> **Trace:** `nn(g1) = nn(g2) = 4` → passa o atalho. Para `u=1` (grau 1, vizinho `[2]`):
> acha `u2` em `g2` com `id=1`; vizinho `2` de `1` — existe aresta `{1,2}` em `g2`? Sim.
> Grau de `1` em `g1` = 1, grau de `1` em `g2` = 1 → bate. Repete para `2, 3, 4` — todos
> batem → devolve **1** (iguais), mesmo as listas internas estando em ordens diferentes.

`g3` (uma aresta a mais: `{1,2},{2,3},{3,4},{1,4}`): `ig(g1, g3)` — em algum momento, ao
checar o vértice `1` de `g3` (não de `g1`!) contra `g1`... **espera**: a função só percorre
`g1`, então o vizinho extra `{1,4}` de `g3` nunca é visitado a partir de `g1`. É exatamente
por isso que o passo 6 (comparar graus) é necessário: ao chegar em `u=1` de `g1` (grau 1),
comparamos com o grau de `1` em `g3`, que é **2** (tem vizinhos `2` e `4`) — `1 ≠ 2` →
`return 0`. Sem essa checagem de grau, o algoritmo erraria (diria "iguais" quando não são).

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| checar `nn(g1) != nn(g2)` primeiro | uso o teste mais barato pra eliminar casos óbvios de desigualdade antes de qualquer busca cara |
| confirmar cada vizinho de `u` existe em `g2` | provo que vizinhos(u, g1) ⊆ vizinhos(u2, g2) |
| comparar os graus no final | fecho a "dupla inclusão" — sem isso, só provaria "subconjunto", não "igual" |

## 7. Exercícios de fixação

1. Por que checar `nn(g1) != nn(g2)` **antes** de entrar no laço principal é uma boa
   ideia de desempenho, mesmo sendo logicamente dispensável (o laço acabaria detectando a
   diferença de qualquer jeito, eventualmente)?
2. Dê um exemplo de dois grafos com o **mesmo número** de vértices e arestas, mas que
   `ig` corretamente identificaria como diferentes.
3. Por que a checagem de grau usa `grau(u2)` (o vértice encontrado em `g2`) e não
   `grau(u)` duas vezes?
4. `ig(g1, g1)` (comparar um grafo com ele mesmo) sempre devolve 1? Por quê?

### Gabarito

1. Porque, sem esse atalho, o algoritmo ainda percorreria todos os vértices de `g1`
   tentando achar correspondência em `g2` antes de eventualmente notar a diferença (via
   grau ou vértice ausente) — o atalho corta isso com uma checagem O(V) simples logo de
   cara.
2. Exemplo: `g1` com arestas `{1,2},{3,4}` (dois pares separados) e `g2` com arestas
   `{1,3},{2,4}` — mesmo número de vértices (4) e arestas (2), mas conjuntos de arestas
   diferentes. `TG_busca_aresta(g2, 1, 2)` não encontraria nada → `return 0`.
3. Porque o objetivo é comparar "o grau de `u` em `g1`" contra "o grau do **mesmo
   vértice** em `g2`" — `grau(u)` já é o de `g1`; `grau(u2)` é o do vértice correspondente
   em `g2`. Comparar `grau(u)` consigo mesmo não diria nada.
4. Sim — todo vértice de `g1` obviamente existe em `g1` com os mesmos vizinhos e mesmo
   grau (é o mesmo grafo). Serve como teste de sanidade básico do algoritmo.

## Resumo

- Igualdade rotulada: mesmo conjunto de vértices, e para cada um, mesmo conjunto de
  vizinhos — independente da ordem nas listas.
- Estratégia: atalho por contagem de vértices, depois dupla inclusão (todo vizinho de
  `g1` existe em `g2`) fechada pela comparação de graus.
- Sem comparar os graus no final, o algoritmo só provaria "subconjunto", não "igual".

---

Isso fecha a teoria de 2.2 com o material disponível até agora (contagem, k-regularidade,
coloração, igualdade). **Nota:** os PDFs de aula e a lista04-EDA ainda não cobrem BFS, DFS,
árvore geradora mínima nem caminhos mínimos — ver aviso no `README.md` deste subtópico.
Para a explicação passo a passo de cada questão da lista, veja
`Ementa/ListasExercicios/lista04-EDA/Passo a Passo Lista/`.
