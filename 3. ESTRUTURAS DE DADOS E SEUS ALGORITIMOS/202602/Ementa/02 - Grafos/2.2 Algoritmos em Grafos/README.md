# 2.2 Algoritmos em Grafos

## Objetivo de aprendizagem

- Implementar e analisar BFS e DFS, e saber quando usar cada um.
- Calcular árvore geradora mínima com Kruskal e com Prim, e justificar a diferença de complexidade entre eles conforme a estrutura de dados auxiliar.
- Calcular caminhos mínimos com Dijkstra, Bellman-Ford e Floyd-Warshall, e saber em qual situação cada algoritmo é o correto (pesos negativos, single-source vs. all-pairs).

## Roteiro de leitura

- **SZ (livro-base):** capítulo de "Grafos" / percursos e algoritmos em grafos — cobre buscas (BFS/DFS) e normalmente uma introdução a árvore geradora mínima e caminhos mínimos (conferir página exata; a profundidade de Kruskal/Prim/Dijkstra pode ser mais resumida que no Cormen).
- **CO (Cormen) — referência mais completa deste módulo:**
  - Cap. 22 "Algoritmos Elementares de Grafos" — seção 22.2 BFS, seção 22.3 DFS, seção 22.4 ordenação topológica, seção 22.5 componentes fortemente conexas (conferir página exata).
  - Cap. 23 "Árvores Geradoras Mínimas" — algoritmo genérico, Kruskal (seção 23.2) e Prim (seção 23.2) (conferir página exata).
  - Cap. 24 "Caminhos Mínimos de Origem Única" — Bellman-Ford (seção 24.1) e Dijkstra (seção 24.3) (conferir página exata).
  - Cap. 25 "Caminhos Mínimos entre Todos os Pares" — Floyd-Warshall (seção 25.2) (conferir página exata).
- **CE (Celes):** não cobre algoritmos de grafos.
- **KR:** não se aplica.

## Notas de estudo elaboradas

### Busca em largura (BFS) e busca em profundidade (DFS)

Ambos visitam todo vértice alcançável a partir de uma origem, em **O(V + E)** com lista de adjacência (O(V²) com matriz).

- **BFS** usa fila (FIFO): explora por níveis. Em grafo **não ponderado**, a árvore BFS a partir de um vértice s dá o **caminho mínimo** (menor número de arestas) de s até qualquer outro vértice alcançável.
- **DFS** usa pilha (ou recursão): explora o mais fundo possível antes de retroceder (backtrack). Classifica arestas em árvore/retorno/avanço/cruzamento — a existência de uma **aresta de retorno** durante o DFS indica **ciclo** no grafo. DFS também é a base de:
  - **Ordenação topológica** (só para DAGs — grafos direcionados acíclicos): ordena vértices de forma que toda aresta (u,v) tenha u antes de v na ordem; obtida inserindo cada vértice no início de uma lista quando o DFS termina de processá-lo.
  - **Componentes fortemente conexas** (algoritmo de Kosaraju/Tarjan): dois DFS, um no grafo original e um no grafo transposto.

```
BFS(G, s):
  para cada vértice u: cor[u] = BRANCO
  cor[s] = CINZA; dist[s] = 0; fila = [s]
  enquanto fila não vazia:
    u = fila.desenfileirar()
    para cada v adjacente a u:
      se cor[v] == BRANCO:
        cor[v] = CINZA; dist[v] = dist[u] + 1; fila.enfileirar(v)
    cor[u] = PRETO
```

### Exemplo passo a passo: BFS a partir do vértice 0

Usando o mesmo grafo de 2.1 (vértices 0-4, arestas 0-1, 0-2, 1-2, 1-3, 2-3, 3-4), partindo de s = 0:

| Passo | Fila (antes de processar) | Vértice processado | Vizinhos descobertos agora | dist[] atualizado |
|---|---|---|---|---|
| 1 | [0] | 0 | 1, 2 (brancos) | dist[0]=0, dist[1]=1, dist[2]=1 |
| 2 | [1, 2] | 1 | 3 (branco; 0 e 2 já visitados) | dist[3]=2 |
| 3 | [2, 3] | 2 | nenhum novo (0, 1, 3 já visitados) | — |
| 4 | [3] | 3 | 4 (branco) | dist[4]=3 |
| 5 | [4] | 4 | nenhum | — |
| 6 | [ ] | fila vazia — fim | — | — |

Resultado: `dist = [0, 1, 1, 2, 3]` — o número mínimo de arestas de 0 até cada vértice. Note que o vértice 3 é alcançado em 2 passos (via 1 ou via 2, tanto faz — BFS acha o primeiro caminho de menor comprimento, não guarda qual).



### Árvore Geradora Mínima (MST)

Subconjunto de arestas que conecta todos os vértices com custo total mínimo, sem ciclos (|V|-1 arestas).

| Algoritmo | Estratégia | Estrutura auxiliar | Complexidade |
|---|---|---|---|
| **Kruskal** | ordena todas as arestas por peso, adiciona a próxima se não formar ciclo | Union-Find (disjoint-set) com union by rank + path compression | O(E log E) — dominado pela ordenação |
| **Prim** | cresce a árvore a partir de um vértice, sempre adicionando a aresta de menor peso que conecta a árvore a um vértice fora dela | fila de prioridade (min-heap) | O(E log V) com heap binário |

Kruskal é melhor para grafos esparsos (trabalha em arestas); Prim é melhor para grafos densos (trabalha em vértices), especialmente com heap de Fibonacci (O(E + V log V)).

### Caminhos Mínimos

| Algoritmo | Caso | Pesos negativos? | Complexidade |
|---|---|---|---|
| **Dijkstra** | origem única (single-source) | **Não** — falha com peso negativo (marca vértice como "finalizado" cedo demais) | O(E log V) com min-heap |
| **Bellman-Ford** | origem única | Sim — e ainda **detecta ciclo negativo** alcançável | O(V·E) |
| **Floyd-Warshall** | todos os pares (all-pairs) | Sim (mas não ciclo negativo alcançável de forma direta) | O(V³), programação dinâmica |

Dijkstra é guloso: sempre expande o vértice não-finalizado com menor distância estimada, assumindo que essa distância já é definitiva — essa suposição só é válida se todos os pesos forem não-negativos. Bellman-Ford relaxa todas as arestas |V|-1 vezes, tolerando pesos negativos. Floyd-Warshall é programação dinâmica sobre "caminho mínimo usando só os primeiros k vértices como intermediários".

## Exemplos em C

BFS usando a struct de grafo com lista de adjacência (a mesma de 2.1) e uma fila simples implementada com array circular.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct no_adj {
    int vertice;
    struct no_adj *prox;
} NoAdj;

typedef struct grafo {
    int num_vertices;
    NoAdj **adj;
} Grafo;

// fila FIFO simples com array circular, capacidade fixa = num_vertices
typedef struct fila {
    int *dados;
    int inicio, fim, tamanho, capacidade;
} Fila;

Fila *fila_cria(int capacidade) {
    Fila *f = (Fila *) malloc(sizeof(Fila));
    f->dados = (int *) malloc(capacidade * sizeof(int));
    f->inicio = f->fim = f->tamanho = 0;
    f->capacidade = capacidade;
    return f;
}

void fila_enfileira(Fila *f, int v) {
    f->dados[f->fim] = v;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}

int fila_desenfileira(Fila *f) {
    int v = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return v;
}

int fila_vazia(Fila *f) {
    return f->tamanho == 0;
}

// BFS a partir de s: imprime a ordem de visita e a distância (em arestas) até cada vértice
void bfs(Grafo *g, int s) {
    int *visitado = (int *) calloc(g->num_vertices, sizeof(int));
    int *dist = (int *) malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) dist[i] = -1; // -1 = não alcançado

    Fila *fila = fila_cria(g->num_vertices);

    visitado[s] = 1;
    dist[s] = 0;
    fila_enfileira(fila, s);

    while (!fila_vazia(fila)) {
        int u = fila_desenfileira(fila);
        printf("visitando %d (dist=%d)\n", u, dist[u]);

        // percorre todos os vizinhos de u na lista de adjacência
        for (NoAdj *p = g->adj[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            if (!visitado[v]) {          // só entra na fila uma vez (garante O(V+E))
                visitado[v] = 1;
                dist[v] = dist[u] + 1;
                fila_enfileira(fila, v);
            }
        }
    }

    free(visitado);
    free(dist);
    free(fila->dados);
    free(fila);
}
```

A fila é o que garante a exploração **por níveis**: todo vértice a distância k de `s` é enfileirado antes de qualquer vértice a distância k+1, porque só processamos `u` (e descobrimos seus vizinhos) depois que todos os vértices enfileirados antes dele já foram processados — é exatamente a ordem FIFO que implementa essa garantia. Se trocássemos a fila por uma pilha (LIFO), o algoritmo viraria uma DFS iterativa, e a propriedade de "menor número de arestas" se perderia.

## Pontos de atenção / pegadinhas comuns de prova

- Dijkstra **não funciona** com arestas de peso negativo — é o erro mais cobrado em prova; sempre justifique com o contra-exemplo de vértice marcado como definitivo antes da hora.
- BFS só dá caminho mínimo em grafo **não ponderado** (ou com todos os pesos iguais) — em grafo ponderado, é preciso Dijkstra/Bellman-Ford.
- A complexidade de Kruskal depende da estrutura union-find: sem path compression/union by rank, a complexidade amortizada piora bastante.
- Ordenação topológica só existe para DAGs — se o DFS encontrar uma aresta de retorno (ciclo), não há ordenação topológica válida.
- Não confundir "árvore geradora mínima" (minimiza soma de pesos, não é sobre caminhos entre pares específicos) com "caminho mínimo" (menor caminho entre dois vértices específicos) — são problemas diferentes que podem ter soluções diferentes no mesmo grafo.

## Anotações pessoais

## Exercícios resolvidos
