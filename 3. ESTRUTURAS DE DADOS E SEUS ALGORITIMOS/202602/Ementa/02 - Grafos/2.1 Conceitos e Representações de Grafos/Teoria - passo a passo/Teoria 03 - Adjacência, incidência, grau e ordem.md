# Teoria 03 — Adjacência, incidência, grau e ordem

> **Onde isto entra:** vocabulário usado o módulo inteiro pra descrever "o quanto" um vértice
> está conectado — é exatamente esse vocabulário que a lista04 (Q4, `testek`) cobra.
> **Antes:** [[Teoria 02 - Grafo orientado (digrafo) vs. não orientado]].
> **Fonte:** `lista04-EDA/07_Grafos_2026_08_27.pdf`, págs. 23–28.

## 1. A ideia em uma frase

**Grau** de um vértice é quantas arestas tocam nele. **Ordem** do grafo é quantos vértices
ele tem. Os dois são só formas de **contar**, cada um contando uma coisa diferente.

## 2. Grau — lido devagar, com o exemplo do slide (pág. 26-27)

O PDF define: "o grau de um vértice é o número de arestas que nele/dele incidem." Grafo de
exemplo (8 vértices):

```
        v1
       /  \
     v2 -- v3 -- v4
     | \  /|\   /|
     |  \/ | \ / |
     v5-v6-+--v7 (v8 isolado, sem nenhuma aresta)
```

(o slide desenha `v1-v2, v1-v4, v2-v3, v2-v5, v2-v6, v3-v4, v3-v5, v3-v6, v3-v7, v4-v6,
v4-v7, v5-v6, v6-v7`, com `v8` solto.)

> **Contando o grau de `v1`:** quantas arestas tocam `v1`? `{v1,v2}` e `{v1,v4}` — **2**
> arestas. Grau de `v1` = 2.
> **Contando o grau de `v8`:** nenhuma aresta toca `v8` — grau = **0**.

O PDF já resolve todos: `v1`→2, `v2`→4, `v3`→4, `v4`→4, `v5`→3, `v6`→4, `v7`→3, `v8`→0.

> **Vértice isolado** (pág. 27): grau 0 — nenhuma conexão. `v8` é isolado.

## 3. Ordem — lido devagar

O PDF (pág. 28): "a ordem de um grafo é o número de vértices que ele possui: `ordem(G) =
|V|`." No mesmo grafo, `V = {v1,...,v8}`, então `ordem(G) = 8` — **mesmo v8 sendo isolado,
ele conta para a ordem** (ordem é sobre vértices, não sobre conexões).

## 4. Adjacência e incidência — lidas devagar

> 📖 **Adjacente** (pág. 24): `v1` é adjacente a `v2` se existe aresta ligando os dois. Em
> não orientado, isso é automaticamente **simétrico** (v2 também é adjacente a v1). Em
> orientado, só vale no sentido da seta (ver Teoria 02).

> 📖 **Incidente** (pág. 25): a aresta `{v1,v2}` é incidente **em** v1 **e** em v2 (mesmo
> papel dos dois lados, em grafo não orientado). Em digrafo, a aresta `(v1,v2)` é incidente
> **de** v1 (sai de v1) e incidente **a** v2 (entra em v2) — papéis diferentes.

> **Ligando os três conceitos:** o grau de um vértice é literalmente **"quantas arestas são
> incidentes nele"** — contar o grau é contar as incidências.

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| contar arestas tocando um vértice | meço o grau **daquele vértice específico** |
| contar `|V|` | meço a ordem **do grafo inteiro** — não depende de nenhuma aresta |
| achar grau 0 | identifico um vértice **isolado** (existe no grafo, mas sem conexão nenhuma) |

## 6. Exercícios de fixação

Usando o grafo do slide (seção 2, 8 vértices, `v8` isolado):

1. Qual o grau de `v5`? (confira contando as arestas que tocam `v5` na lista do slide.)
2. Se eu adicionar um vértice novo `v9` sem nenhuma aresta, o que acontece com a ordem do
   grafo? E com o grau de `v9`?
3. Um grafo tem ordem 5 e todos os vértices com grau 0. Quantas arestas ele tem?
4. Por que "grau" nunca pode ser maior que `|V| - 1` num grafo **sem laço nem aresta
   repetida** (grafo simples)?

### Gabarito

1. Arestas tocando `v5`: `{v2,v5}`, `{v3,v5}`, `{v5,v6}` → grau 3 (confere com o valor já
   anotado pelo slide).
2. Ordem passa de 8 para 9 (`|V|` aumentou em 1). Grau de `v9` = 0 (nenhuma aresta o toca
   ainda — é um vértice isolado, igual `v8`).
3. Zero arestas — se todo grau é 0, nenhuma aresta toca nenhum vértice, e toda aresta
   precisa tocar 2 vértices, então não pode haver nenhuma.
4. Porque, num grafo simples, um vértice só pode ter **no máximo uma** aresta para cada um
   dos outros vértices (sem repetir, sem se ligar a si mesmo) — e existem `|V| - 1` outros
   vértices possíveis para se conectar.

## Resumo

- **Grau** de um vértice = número de arestas que o tocam (incidem nele).
- **Ordem** do grafo = `|V|`, número total de vértices (conta até os isolados).
- Vértice **isolado** = grau 0.
- Adjacência descreve uma relação entre **dois vértices**; incidência descreve a relação
  entre **uma aresta e o(s) vértice(s) que ela toca**.

**Próximo:** [[Teoria 04 - Caminho, conectividade e ciclo]].
