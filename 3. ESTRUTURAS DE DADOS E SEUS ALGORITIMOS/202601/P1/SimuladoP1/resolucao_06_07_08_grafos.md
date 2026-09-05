# SimulEDA P1 — Exercícios 6, 7 e 8

---

## 📚 Conceitos fundamentais sobre Grafos

Antes de resolver, vamos entender o que é um grafo, já que os três exercícios trabalham com ele.

**O que é um grafo?**
> Um grafo é uma estrutura formada por **vértices** (nós) conectados por **arestas** (ligações). Diferente de uma árvore, um grafo pode ter **ciclos** e um vértice pode se conectar a qualquer outro.

```
  0 ---- 1
  |    / |
  |   /  |
  2 ---- 3
```

**O que é `TG`?**
> É o tipo do grafo na biblioteca. Geralmente representado por uma **matriz de adjacência** ou **lista de adjacência**.

**O que é `TLSE`?**
> É a lista encadeada da biblioteca — usada para representar um caminho (sequência de vértices).

**O que é um caminho?**
> Uma sequência de vértices onde cada um está conectado ao próximo por uma aresta. Ex: 0 → 2 → 3 → 1

---

## Exercício 6

**Enunciado:** Faça uma função que encontre **um** caminho entre dois vértices de um grafo.
**Assinatura:** `TLSE* caminho(TG *g, int origem, int destino);`

---

### 💡 Estratégia

Usamos **DFS (Busca em Profundidade)** — a ideia é:
1. Partir da origem
2. Visitar um vizinho não visitado
3. Continuar até achar o destino
4. Se não achar por um caminho, volta e tenta outro (backtrack)

Precisamos de um array `visitado[]` para não entrar em loop.

```c
#include "grafo.h"
#include "listaSE.h"

// Função auxiliar recursiva
int dfs_caminho(TG *g, int atual, int destino,
                int *visitado, TLSE *caminho) {

    // Marca o vértice atual como visitado
    visitado[atual] = 1;

    // Adiciona ao caminho
    inserirFinal(caminho, atual);

    // Chegamos ao destino!
    if (atual == destino)
        return 1;

    // Tenta visitar cada vizinho
    for (int v = 0; v < g->numVertices; v++) {
        // Se existe aresta E o vizinho não foi visitado
        if (g->matriz[atual][v] && !visitado[v]) {
            // Tenta achar o destino a partir desse vizinho
            if (dfs_caminho(g, v, destino, visitado, caminho))
                return 1; // achou! propaga o sucesso
        }
    }

    // Backtrack: esse caminho não levou ao destino
    removerFinal(caminho);
    return 0;
}

// Função principal
TLSE* caminho(TG *g, int origem, int destino) {
    // Cria array de visitados zerado
    int visitado[g->numVertices];
    for (int i = 0; i < g->numVertices; i++)
        visitado[i] = 0;

    TLSE *resultado = criarLista();

    // Se não achou nenhum caminho, retorna lista vazia
    if (!dfs_caminho(g, origem, destino, visitado, resultado)) {
        liberarLista(resultado);
        return NULL;
    }

    return resultado;
}
```

---

### 🔍 Passo a passo com exemplo

**Grafo:** origem = 0, destino = 3
```
  0 ---- 1
  |      |
  2 ---- 3
```

| Passo | Vértice atual | Visitados | Caminho atual | Ação |
|---|---|---|---|---|
| 1 | 0 | [0] | [0] | Tenta vizinho 1 |
| 2 | 1 | [0,1] | [0,1] | Tenta vizinho 3 |
| 3 | 3 | [0,1,3] | [0,1,3] | **É o destino!** ✅ |

**Retorna:** `[0, 1, 3]`

---

---

## Exercício 7

**Enunciado:** Faça uma função que encontre **TODOS** os caminhos entre dois vértices de um grafo.
**Assinatura:** `TLSE** caminhos(TG *g, int origem, int destino);`

---

### 💡 Diferença do exercício 6

No exercício 6, parávamos assim que achávamos **um** caminho. Aqui precisamos **continuar a busca** mesmo depois de achar um caminho, para encontrar todos os outros.

A chave é: ao encontrar o destino, **salvar o caminho atual** e **continuar a busca** (não retornar imediatamente).

```c
// Conta quantos caminhos existem (para alocar o vetor)
int contar(TG *g, int atual, int destino, int *visitado) {
    if (atual == destino) return 1;

    visitado[atual] = 1;
    int total = 0;

    for (int v = 0; v < g->numVertices; v++) {
        if (g->matriz[atual][v] && !visitado[v])
            total += contar(g, v, destino, visitado);
    }

    visitado[atual] = 0; // backtrack
    return total;
}

// Busca todos os caminhos recursivamente
void dfs_todos(TG *g, int atual, int destino,
               int *visitado, TLSE *atual_caminho,
               TLSE **resultado, int *indice) {

    // Adiciona vértice atual ao caminho
    inserirFinal(atual_caminho, atual);
    visitado[atual] = 1;

    // Chegamos ao destino: salva uma cópia do caminho
    if (atual == destino) {
        resultado[*indice] = copiarLista(atual_caminho);
        (*indice)++;
    } else {
        // Continua explorando todos os vizinhos
        for (int v = 0; v < g->numVertices; v++) {
            if (g->matriz[atual][v] && !visitado[v]) {
                dfs_todos(g, v, destino, visitado,
                          atual_caminho, resultado, indice);
            }
        }
    }

    // Backtrack: remove vértice atual para tentar outro caminho
    removerFinal(atual_caminho);
    visitado[atual] = 0;
}

// Função principal
TLSE** caminhos(TG *g, int origem, int destino) {
    int visitado[g->numVertices];
    for (int i = 0; i < g->numVertices; i++)
        visitado[i] = 0;

    // Conta caminhos para saber o tamanho do vetor
    int total = contar(g, origem, destino, visitado);

    // Aloca vetor de listas (+1 para sentinela NULL)
    TLSE **resultado = malloc((total + 1) * sizeof(TLSE*));
    resultado[total] = NULL;

    TLSE *atual_caminho = criarLista();
    int indice = 0;

    dfs_todos(g, origem, destino, visitado,
              atual_caminho, resultado, &indice);

    liberarLista(atual_caminho);
    return resultado;
}
```

---

### 🔍 Passo a passo com exemplo

**Grafo:** origem = 0, destino = 3
```
  0 ---- 1
  |    ╲ |
  |     ╲|
  2 ---- 3
```
Arestas: 0-1, 0-2, 1-3, 2-3, 1-2

| Exploração | Caminho | Chegou em 3? |
|---|---|---|
| 0 → 1 → 2 → 3 | [0,1,2,3] | ✅ Salva |
| 0 → 1 → 3 | [0,1,3] | ✅ Salva |
| 0 → 2 → 1 → 3 | [0,2,1,3] | ✅ Salva |
| 0 → 2 → 3 | [0,2,3] | ✅ Salva |

**Retorna:** `[[0,1,2,3], [0,1,3], [0,2,1,3], [0,2,3]]`

---

---

## Exercício 8

**Enunciado:** Faça uma função que encontre o **menor caminho** entre dois vértices de um grafo.
**Assinatura:** `TLSE* menor_caminho(TG *g, int origem, int destino);`

---

### 📚 O que é o "menor caminho"?

Depende do tipo de grafo:
- Em grafos **sem peso** → menor caminho = caminho com **menos arestas**
- Em grafos **com peso** → menor caminho = caminho com **menor soma dos pesos**

Para grafo **sem peso**, o melhor algoritmo é o **BFS (Busca em Largura)**, pois ele explora os vértices camada por camada e **garante** que o primeiro caminho encontrado é o mais curto.

---

### 💡 Como funciona o BFS?

Imagine jogar uma pedra na água — as ondas se expandem em círculos. O BFS faz o mesmo: explora primeiro todos os vizinhos diretos, depois os vizinhos dos vizinhos, e assim por diante.

```
Nível 0: [origem]
Nível 1: [vizinhos da origem]
Nível 2: [vizinhos dos vizinhos]
...
```

O primeiro nível em que encontramos o destino = caminho mais curto!

Para reconstruir o caminho, guardamos o **"predecessor"** de cada vértice — ou seja, por qual vértice chegamos até ele.

```c
TLSE* menor_caminho(TG *g, int origem, int destino) {
    int n = g->numVertices;

    int visitado[n];
    int predecessor[n]; // guarda de onde viemos para chegar em cada vértice
    for (int i = 0; i < n; i++) {
        visitado[i] = 0;
        predecessor[i] = -1; // -1 = sem predecessor ainda
    }

    // Fila manual para o BFS (pode usar biblioteca de fila)
    int fila[n];
    int inicio = 0, fim = 0;

    // Começa pela origem
    fila[fim++] = origem;
    visitado[origem] = 1;

    int achou = 0;

    // BFS: processa vértice por vértice na fila
    while (inicio < fim) {
        int atual = fila[inicio++]; // retira da frente da fila

        if (atual == destino) {
            achou = 1;
            break;
        }

        // Adiciona todos os vizinhos não visitados na fila
        for (int v = 0; v < n; v++) {
            if (g->matriz[atual][v] && !visitado[v]) {
                visitado[v] = 1;
                predecessor[v] = atual; // veio de 'atual'
                fila[fim++] = v;
            }
        }
    }

    // Se não achou caminho, retorna NULL
    if (!achou) return NULL;

    // Reconstrói o caminho de trás para frente usando predecessor[]
    TLSE *resultado = criarLista();
    int v = destino;
    while (v != -1) {
        inserirInicio(resultado, v); // insere na frente para ficar na ordem certa
        v = predecessor[v];
    }

    return resultado;
}
```

---

### 🔍 Passo a passo com exemplo

**Grafo:** origem = 0, destino = 3
```
  0 ---- 1
  |      |
  2 ---- 3
```

**Fase BFS:**

| Iteração | Fila | Vértice processado | Vizinhos adicionados | Predecessores |
|---|---|---|---|---|
| Início | [0] | — | — | pred = [-1,-1,-1,-1] |
| 1 | [1, 2] | 0 | 1, 2 | pred[1]=0, pred[2]=0 |
| 2 | [2, 3] | 1 | 3 | pred[3]=1 |
| 3 | — | 2 | (3 já visitado) | — |
| 4 | — | 3 | **destino!** ✅ | — |

**Fase de reconstrução** (de trás pra frente):

```
v = 3  → pred[3] = 1  → insere 3 no início: [3]
v = 1  → pred[1] = 0  → insere 1 no início: [1, 3]
v = 0  → pred[0] = -1 → insere 0 no início: [0, 1, 3]
v = -1 → para
```

**Retorna:** `[0, 1, 3]` — o menor caminho com apenas 2 arestas! ✅

---

### ✅ Resumo dos 3 exercícios

| Exercício | Algoritmo | Retorna | Ideia central |
|---|---|---|---|
| 6 - Um caminho | DFS + backtrack | `TLSE*` (uma lista) | Para quando acha o destino |
| 7 - Todos os caminhos | DFS + backtrack completo | `TLSE**` (vetor de listas) | Não para ao achar: salva e continua |
| 8 - Menor caminho | BFS | `TLSE*` (uma lista) | Explora camada por camada, garante o menor |

### 🔑 Diferença crucial entre DFS e BFS

```
DFS (Profundidade):        BFS (Largura):
vai fundo primeiro         explora por níveis

0 → 1 → 3                 Nível 0: [0]
    ↑                      Nível 1: [1, 2]
    vai longe              Nível 2: [3]  ← destino!
    antes de tentar 2
```

> **BFS sempre encontra o caminho mais curto** em grafos sem peso, porque ele nunca "pula" um nível — quando acha o destino, é garantido que chegou pelo menor número possível de arestas.