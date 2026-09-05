# 2.1 Conceitos e Representações de Grafos

## Objetivo de aprendizagem

- Dominar a terminologia formal de grafos (grau, caminho, ciclo, conexidade, ponderação).
- Saber escolher entre matriz de adjacência e lista de adjacência de acordo com a densidade do grafo e as operações mais frequentes.
- Entender o impacto de cada representação na complexidade de espaço e de tempo dos algoritmos que virão em 2.2.

## Roteiro de leitura

- **SZ (livro-base):** capítulo de "Grafos" — conceitos, definições formais e as representações (matriz e lista de adjacência) (conferir página exata).
- **CO (Cormen):** cap. 22 "Algoritmos Elementares de Grafos", seção 22.1 "Representações de grafos" — compara formalmente matriz vs. lista de adjacência em termos de espaço O(V²) vs. O(V+E) (conferir página exata).
- **CE (Celes):** não cobre grafos — o livro é focado em listas, árvores e tabelas hash em memória principal. Não há capítulo equivalente.
- **KR:** não se aplica diretamente; ao implementar lista de adjacência em C você vai usar ponteiros e structs (cap. 5 "Ponteiros e Arrays" e cap. 6 "Structs") — consulte só se precisar revisar esses mecanismos de linguagem.

## Notas de estudo elaboradas

### Definições formais

- **Grafo** G = (V, E): conjunto de vértices V e conjunto de arestas E, onde cada aresta conecta um par de vértices.
- **Dígrafo (grafo direcionado):** arestas têm sentido — (u, v) ≠ (v, u).
- **Grafo não-direcionado:** aresta {u, v} é simétrica.
- **Ordem** do grafo: |V| (número de vértices). **Tamanho**: |E| (número de arestas).
- **Grau** de um vértice: número de arestas incidentes nele. Em dígrafos, separa-se em **grau de entrada** (in-degree) e **grau de saída** (out-degree).
- **Caminho:** sequência de vértices conectados por arestas, sem repetir vértice (caminho simples).
- **Ciclo:** caminho que retorna ao vértice de origem.
- **Grafo conexo:** existe caminho entre todo par de vértices (não-direcionado). Em dígrafos, fala-se em **fortemente conexo** (caminho direcionado em ambos os sentidos entre todo par) e **fracamente conexo** (conexo ignorando direção).
- **Grafo ponderado:** cada aresta tem um peso/custo associado, w(u, v).
- **Grafo denso** vs. **esparso:** denso quando |E| se aproxima de |V|², esparso quando |E| é próximo de |V| — essa distinção guia a escolha de representação.

### Matriz de adjacência vs. lista de adjacência

| Critério | Matriz de adjacência | Lista de adjacência |
|---|---|---|
| Espaço | O(V²) | O(V + E) |
| Verificar se (u,v) é aresta | O(1) | O(grau(u)) no pior caso |
| Listar vizinhos de um vértice | O(V) | O(grau(u)) |
| Adicionar aresta | O(1) | O(1) |
| Remover aresta | O(1) | O(grau(u)) (precisa achar na lista) |
| Melhor para | grafos densos, ou quando precisa checar adjacência com frequência | grafos esparsos (a maioria dos casos reais) — é a representação padrão usada em BFS/DFS/Dijkstra |

A matriz de adjacência é uma matriz V×V onde `M[i][j] = 1` (ou peso, se ponderado) se existe aresta de i para j. Para grafo não-direcionado, a matriz é simétrica — metade da informação é redundante.

A lista de adjacência é um array (ou tabela hash) de V listas, onde a lista do vértice i contém todos os vértices adjacentes a i (e, se ponderado, o peso da aresta). É a representação mais usada na prática porque a maioria dos grafos do mundo real é esparsa (|E| ≈ O(V), não O(V²)).

### Representando grafos ponderados

Na matriz: `M[i][j] = peso` em vez de 1 (e um valor sentinela, como infinito, para "sem aresta"). Na lista: cada nó da lista guarda `(vértice_destino, peso)` em vez de só o destino.

### Exemplo concreto: as duas representações lado a lado

Grafo não-direcionado com 5 vértices (0 a 4) e 6 arestas: {0,1}, {0,2}, {1,2}, {1,3}, {2,3}, {3,4}.

**Matriz de adjacência** (V×V = 5×5, simétrica):

```
     0  1  2  3  4
  0  0  1  1  0  0
  1  1  0  1  1  0
  2  1  1  0  1  0
  3  0  1  1  0  1
  4  0  0  0  1  0
```

Repare que a matriz gasta 25 células mesmo esse grafo tendo só 6 arestas (12 entradas "1", já que cada aresta aparece duas vezes por simetria) — a maior parte da matriz é zero. Isso é o desperdício de espaço O(V²) na prática quando o grafo é esparso.

**Lista de adjacência** (5 listas, uma por vértice):

```
0 → [1, 2]
1 → [0, 2, 3]
2 → [0, 1, 3]
3 → [1, 2, 4]
4 → [3]
```

Mesmo grafo, mas o espaço usado é proporcional a 2|E| = 12 entradas no total (cada aresta aparece nas listas dos seus dois extremos), não V² = 25. Para checar se existe aresta {0,3}, na matriz é `M[0][3]` direto (O(1)); na lista é preciso percorrer a lista do vértice 0 (`[1, 2]`) até não achar 3 (O(grau(0)) = O(2) nesse caso, mas em geral O(V) no pior caso).

## Exemplos em C

Implementação de grafo não-direcionado com **lista de adjacência** — a representação padrão na prática (grafos esparsos, algoritmos de 2.2 como BFS/DFS/Dijkstra usam essa forma).

```c
#include <stdio.h>
#include <stdlib.h>

// nó de uma lista de adjacência: representa "existe aresta para este vértice"
typedef struct no_adj {
    int vertice;            // vértice de destino da aresta
    int peso;                // peso da aresta (1 se grafo não-ponderado)
    struct no_adj *prox;
} NoAdj;

// grafo = vetor de listas, uma por vértice
typedef struct grafo {
    int num_vertices;
    NoAdj **adj;             // adj[i] = cabeça da lista ligada do vértice i
} Grafo;

Grafo *grafo_cria(int num_vertices) {
    Grafo *g = (Grafo *) malloc(sizeof(Grafo));
    g->num_vertices = num_vertices;
    // adj é um vetor de ponteiros — cada posição começa NULL (lista vazia)
    g->adj = (NoAdj **) calloc(num_vertices, sizeof(NoAdj *));
    return g;
}

// insere aresta u-v; para grafo não-direcionado, insere nos dois sentidos
void grafo_insere_aresta(Grafo *g, int u, int v, int peso) {
    NoAdj *novo_uv = (NoAdj *) malloc(sizeof(NoAdj));
    novo_uv->vertice = v;
    novo_uv->peso = peso;
    novo_uv->prox = g->adj[u];   // insere no início da lista de u
    g->adj[u] = novo_uv;

    NoAdj *novo_vu = (NoAdj *) malloc(sizeof(NoAdj));
    novo_vu->vertice = u;
    novo_vu->peso = peso;
    novo_vu->prox = g->adj[v];   // insere no início da lista de v
    g->adj[v] = novo_vu;
}

void grafo_imprime(Grafo *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        printf("%d ->", i);
        for (NoAdj *p = g->adj[i]; p != NULL; p = p->prox)
            printf(" %d(peso %d)", p->vertice, p->peso);
        printf("\n");
    }
}
```

Uso: `Grafo *g = grafo_cria(5); grafo_insere_aresta(g, 0, 1, 1); ...` reproduz exatamente o grafo do exemplo acima (0-1, 0-2, 1-2, 1-3, 2-3, 3-4).

## Pontos de atenção / pegadinhas comuns de prova

- Não confundir grau de entrada e saída em dígrafos — a soma dos graus de saída de todos os vértices é igual a |E|, não a soma de (entrada + saída).
- Em grafo não-direcionado, a soma de todos os graus é sempre **2|E|** (cada aresta contribui para o grau de 2 vértices) — erro comum é esquecer o fator 2.
- Matriz de adjacência gasta O(V²) de espaço mesmo que o grafo seja esparso — não é "mais rápida" por padrão, é um trade-off de espaço por tempo constante de consulta.
- "Conexo" e "fortemente conexo" não são a mesma coisa em dígrafos — um dígrafo pode ser fracamente conexo (conexo ignorando direção) sem ser fortemente conexo.

## Anotações pessoais

## Exercícios resolvidos
