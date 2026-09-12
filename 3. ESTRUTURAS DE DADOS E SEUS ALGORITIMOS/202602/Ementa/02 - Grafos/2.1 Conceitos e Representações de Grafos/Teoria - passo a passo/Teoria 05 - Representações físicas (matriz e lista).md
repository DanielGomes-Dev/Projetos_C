# Teoria 05 — As quatro representações físicas de um grafo

> **Onde isto entra:** até aqui, grafo era conjunto matemático (V, E). Aqui é: como guardar
> isso na memória do computador. Existem 4 formas clássicas — este arquivo mostra as 4 no
> **mesmo grafo**, pra dar pra comparar direto.
> **Antes:** [[Teoria 04 - Caminho, conectividade e ciclo]].
> **Fonte:** `lista04-EDA/07_Grafos_2026_09_01.pdf`, págs. 38–53 (slides da Profa. Vanessa
> Braganholo).

## 1. A ideia em uma frase

Existem 4 formas físicas clássicas de guardar um grafo: **matriz de adjacência**, **matriz
de incidência**, **lista de adjacência** e **lista de incidência** — todas guardam a
**mesma informação** (quem se liga a quem), só organizadas de formas diferentes, com
trade-offs diferentes de espaço e velocidade.

## 2. Matriz de adjacência — lida devagar

O PDF (pág. 4) define: matriz `A(n×n)` de um grafo de ordem `n`, onde `aij = 1` se existe
aresta entre `vi` e `vj`, e `0` caso contrário. Para grafo não orientado, `aij = aji`
sempre (matriz **simétrica**).

### Conferindo com o grafo do slide (pág. 5, digrafo com 6 vértices)

```
       1 2 3 4 5 6
    1  0 1 0 1 0 1
    2  0 0 1 1 0 0
    3  0 0 0 0 0 0
    4  0 0 1 0 1 0
    5  0 0 0 1 0 1
    6  0 1 0 1 0 0
```

> **Lendo a linha 1:** `a[1][2]=1` → existe aresta `(1,2)`. `a[1][4]=1` → existe `(1,4)`.
> `a[1][6]=1` → existe `(1,6)`. As outras posições da linha são 0 (sem aresta). Note:
> `a[2][1]=0` — não existe `(2,1)` — a matriz **não é simétrica** aqui porque o grafo é
> **orientado** (compare com a versão não orientada abaixo).

### Versão não orientada (pág. 6-7) — a matriz vira simétrica

```
       1 2 3 4
    1  0 1 1 0
    2  1 0 1 1
    3  1 1 0 1
    4  0 1 1 0
```

**Conferindo a simetria:** `a[1][2] = 1` e `a[2][1] = 1` — os dois lados da diagonal
concordam. É por isso que o slide (pág. 7) mostra a matriz "cortada pela metade" (só
preenche acima da diagonal) — a metade de baixo é **redundante**, sempre igual à de cima.

### Grafo valorado (pág. 8) — a matriz vira "pesos" em vez de 1/0

`aij = k` (o peso) se existe aresta com peso `k`; `aij = *` (um símbolo sentinela, "sem
aresta") caso contrário. Mesma ideia, só troca o "1" por um número real.

## 3. Matriz de incidência — lida devagar

O PDF (pág. 11) define: matriz `B(n×m)`, `n` = número de vértices, `m` = número de
arestas: `bij = -1` se o vértice `i` é a **origem** da aresta `j`; `bij = 1` se `i` é o
**término** de `j`; `bij = 0` se a aresta `j` não toca o vértice `i`.

```
      a1 a2 a3 a4 a5
   1  -1 -1  0  0  0
   2   1  0 -1 -1  0
   3   0  1  1  0 -1
   4   0  0  0  1  1
```

> **Lendo a coluna `a1`:** `-1` na linha 1, `1` na linha 2 → a aresta `a1` **sai do vértice
> 1 e entra no vértice 2**. Cada coluna tem exatamente um `-1` e um `1` (cada aresta liga
> exatamente 2 vértices) — o resto da coluna é 0.

**Diferença chave vs. matriz de adjacência:** aqui as **linhas são vértices** mas as
**colunas são arestas** — a matriz de adjacência relaciona vértice×vértice; a de
incidência relaciona vértice×aresta.

## 4. Lista de adjacência — lida devagar

O PDF (pág. 13) define: para cada vértice `v`, guarda-se a lista de vértices `u` tais que
existe aresta `(v,u)`. A forma de armazenamento recomendada (pág. 13) é **lista
encadeada**, por dois motivos: uso racional de espaço (só guarda o que existe, nada de
zeros) e flexibilidade (fácil inserir/remover).

```
1 → 2 → 3 /
2 → 3 → 4 /
3 → 4 /
4 → 1 /
```

> **Lendo a linha do vértice 1:** a lista começa em `1` e contém `2, 3` — ou seja, existem
> arestas `(1,2)` e `(1,3)`. A `/` no fim marca "fim da lista" (equivalente a `NULL` em C).

## 5. Lista de incidência — lida devagar

O PDF (pág. 16) mostra uma variação: em vez de uma lista por vértice, é **uma lista única**
de todas as arestas, cada uma guardando seus dois vértices extremos:

```
G → [1,2] → [1,3] → [2,3] → [2,4] → [3,4] /
```

Repare que aqui **cada aresta aparece uma única vez** (diferente da lista de adjacência,
onde cada aresta aparece duas vezes — uma em cada extremidade).

## 6. As duas mais usadas, lado a lado, no MESMO grafo

Os slides mostram cada representação num grafo diferente — o que dificulta comparar. Aqui
vai o **mesmo** grafo pequeno (construído para este arquivo, não é do PDF) nas duas
representações que o curso realmente usa: matriz de adjacência e lista de adjacência.

Grafo não orientado, 5 vértices, 6 arestas: `{0,1}, {0,2}, {1,2}, {1,3}, {2,3}, {3,4}`.

```
     0 --- 1
      \   /|
       \ / |
        2  |
         \ |
          \|
           3 --- 4
```

**Matriz de adjacência** (5×5, simétrica — repare `M[i][j] = M[j][i]` em todo par):

```
     0  1  2  3  4
  0  0  1  1  0  0
  1  1  0  1  1  0
  2  1  1  0  1  0
  3  0  1  1  0  1
  4  0  0  0  1  0
```

**Lista de adjacência** (5 listas, uma por vértice — mesma informação, outra organização):

```
0 → 1 → 2 /
1 → 0 → 2 → 3 /
2 → 0 → 1 → 3 /
3 → 1 → 2 → 4 /
4 → 3 /
```

> **Conferindo que é a mesma informação:** olhe o vértice `1`. Na matriz, a linha `1` tem
> `1` nas colunas `0, 2, 3` — três vizinhos. Na lista, a linha do vértice `1` é `0 → 2 → 3` —
> os mesmos três vizinhos, só que sem nenhum zero escrito. **Isso é o trade-off inteiro
> resumido num exemplo**: a matriz gasta 25 células (a maioria zero) para dizer a mesma
> coisa que a lista diz com só 12 entradas (2 por aresta × 6 arestas).
>
> **Checando `{0,4}` (não existe aresta):** na matriz, olho direto `M[0][4] = 0` — **O(1)**,
> resposta imediata. Na lista, preciso percorrer a lista do vértice `0` (`1 → 2 /`) inteira
> até não achar `4` — **O(grau(0)) = O(2)** aqui, mas em geral O(n) no pior caso (vértice
> com muitos vizinhos).

## 7. Comparando as quatro — trade-offs (pág. 9, 53)

| Representação | Espaço | Checar se `(u,v)` existe | Achar vizinhos de `v` | Inserir vértice novo | Inserir aresta |
|---|---|---|---|---|---|
| Matriz de adjacência | O(n²) | O(1) | O(n) | **muito difícil** (precisa redimensionar a matriz inteira) | fácil |
| Matriz de incidência | O(n·m) | precisa varrer colunas | precisa varrer colunas | difícil | precisa nova coluna |
| Lista de adjacência | O(n + m) | O(grau) | O(grau) — já vem pronta | fácil (novo nó na lista de nós) | fácil |
| Lista de incidência | O(m) | precisa varrer | precisa varrer todas as arestas | fácil | fácil, mas não identifica vértices isolados de cara |

O slide (pág. 53) resume por que **lista de adjacência é a escolha da disciplina**: é
flexível para inserções/remoções (ao contrário das matrizes) e facilita identificar os
vértices do grafo (ao contrário da lista de incidência, que só lista arestas).

## 7. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| escolher matriz de adjacência | troco espaço (O(n²), inclusive zeros) por velocidade de consulta O(1) |
| escolher lista de adjacência | troco velocidade de consulta "existe aresta?" (agora O(grau)) por espaço proporcional só ao que existe de fato |
| montar a matriz vértice×aresta (incidência) | represento a estrutura de forma que cada **aresta individual** seja um objeto identificável, não só uma marca 0/1 |

## 8. Exercícios de fixação

1. Um grafo tem 100 vértices e só 5 arestas (bem esparso). Estimando espaço, qual
   representação gasta menos memória: matriz ou lista de adjacência?
2. Na matriz de adjacência do digrafo da seção 2, existe aresta `(3, x)` para algum `x`?
   O que isso te diz sobre o vértice 3?
3. Por que a matriz de adjacência de um grafo **não orientado** é sempre simétrica, mas a
   de um digrafo, em geral, não é?
4. Entre lista de adjacência e lista de incidência, qual delas repete a informação de cada
   aresta (guarda ela "duas vezes")?

### Gabarito

1. Lista de adjacência — matriz gastaria `100² = 10.000` células mesmo só existindo 5
   arestas; a lista gastaria algo proporcional a `n + m = 100 + 5 = 105` (ordem de
   grandeza muito menor).
2. A linha 3 da matriz é toda zero (`0 0 0 0 0 0`) — não existe nenhuma aresta saindo de 3.
   O vértice 3 tem grau de saída 0 (mas pode ter arestas **entrando** — de fato,
   `a[1][3]` é 0 mas `a[2][3]=1` e `a[4][3]=1`, então 3 recebe arestas de 2 e de 4).
3. Porque não orientado significa que a relação vale nos dois sentidos por definição — se
   existe `{i,j}`, ela conta igual para `a[i][j]` e `a[j][i]`. Num digrafo, `(i,j)` e
   `(j,i)` são arestas **independentes**, uma pode existir sem a outra.
4. Lista de adjacência — a aresta `{u,v}` aparece na lista de `u` (como vizinho `v`) **e**
   na lista de `v` (como vizinho `u`), duas entradas para a mesma aresta. Lista de
   incidência guarda cada aresta **uma única vez**, numa lista só.

## Resumo

- 4 representações: matriz de adjacência (vértice×vértice), matriz de incidência
  (vértice×aresta), lista de adjacência (uma lista de vizinhos por vértice), lista de
  incidência (uma lista única de arestas).
- Trade-off central: matriz = espaço fixo O(n²)/O(n·m), consulta rápida; lista = espaço
  proporcional ao que existe, mais flexível para inserir/remover.
- Este curso usa **lista de adjacência** (ver [[Teoria 06 - Representando um grafo em C]]).

**Próximo:** [[Teoria 06 - Representando um grafo em C]].
