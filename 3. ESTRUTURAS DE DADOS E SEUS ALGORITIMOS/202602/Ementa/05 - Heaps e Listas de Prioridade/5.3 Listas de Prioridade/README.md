# 5.3 Listas de Prioridade

## Objetivo de aprendizagem

- Entender fila de prioridade como um **tipo abstrato de dados (TAD)**, distinto de qualquer implementação específica.
- Conhecer as implementações possíveis (array não ordenado, array ordenado, heap binário, heap binomial, heap de Fibonacci) e comparar suas complexidades.
- Reconhecer aplicações práticas onde fila de prioridade é a estrutura correta a usar (Dijkstra, Prim, escalonamento, simulação de eventos).

## Roteiro de leitura

- **SZ (livro-base):** capítulo sobre Heaps e Filas de Prioridade — define o TAD fila de prioridade e normalmente apresenta o heap binário como implementação principal. (conferir página exata)
- **CO (Cormen):** cap. 6 cobre a fila de prioridade implementada com heap binário (`INSERT`, `EXTRACT-MAX/MIN`, `INCREASE-KEY`). Para as implementações mais avançadas — **heaps binomiais** e **heaps de Fibonacci** — o CLRS tem capítulos dedicados na parte de "Estruturas de Dados Avançadas"; são leitura de aprofundamento importante porque o heap de Fibonacci é o que dá a Dijkstra e Prim sua melhor complexidade assintótica conhecida com decrease-key O(1) amortizado. (conferir página exata)
- **CE (Celes):** não identifiquei cobertura de fila de prioridade como TAD separado do heap no livro do Celes — se não encontrar, trate CO como referência principal para as variantes avançadas.
- **KR:** não se aplica diretamente (é conceitual/TAD, não implementação específica de C).

## Notas de estudo elaboradas

### Fila de prioridade como TAD

Uma **fila de prioridade** é um TAD que mantém um conjunto de elementos, cada um com uma **chave/prioridade**, suportando tipicamente:

- `inserir(x)` — adiciona um elemento com sua prioridade.
- `remover-mínimo()` (ou `remover-máximo()`) — remove e retorna o elemento de maior prioridade (menor ou maior chave, a depender da convenção).
- `consultar-mínimo()` / `consultar-máximo()` — retorna sem remover.
- `diminuir-chave(x, nova_chave)` — reduz a prioridade de um elemento já inserido (operação crítica para Dijkstra/Prim).

O ponto central: **fila de prioridade é a interface (o "o quê"); heap é apenas uma das implementações possíveis (o "como")**. Essa distinção é frequentemente cobrada em prova.

### Implementações possíveis e complexidade

| Implementação | Inserir | Remover-mín | Consultar-mín | Diminuir-chave |
|---|---|---|---|---|
| Array não ordenado | O(1) | O(n) | O(n) | O(1) |
| Array ordenado | O(n) | O(1) | O(1) | O(n) |
| Heap binário | O(log n) | O(log n) | O(1) | O(log n) |
| Heap binomial | O(log n) amortizado | O(log n) | O(log n)* | O(log n) |
| Heap de Fibonacci | O(1) amortizado | O(log n) amortizado | O(1) | O(1) amortizado |

\* com um ponteiro auxiliar para o mínimo, consultar-mín pode ser O(1) também em heap binomial.

**Leitura da tabela:** array não ordenado é ótimo pra inserir mas péssimo pra extrair; array ordenado é o oposto. Heap binário equilibra os dois em O(log n). Heap de Fibonacci é o que assintoticamente vence para os algoritmos de grafo, porque `diminuir-chave` em O(1) amortizado é exatamente a operação que Dijkstra e Prim chamam O(E) vezes.

### Por que isso importa para algoritmos de grafo

- **Dijkstra:** a cada iteração extrai o vértice de menor distância provisória (`remover-mínimo`) e, ao relaxar arestas, atualiza distâncias de vértices já na fila (`diminuir-chave`). Com heap binário: O((V+E) log V). Com heap de Fibonacci: O(E + V log V) — melhor quando o grafo é denso (E próximo de V²).
- **Prim (MST):** mesma lógica — extrai o vértice de menor custo de conexão à árvore parcial, atualiza custos dos vizinhos com `diminuir-chave`.
- **Escalonamento de processos / simulação de eventos discretos:** a "próxima ação" a executar é sempre a de maior prioridade (menor timestamp, maior prioridade de processo) — fila de prioridade é a estrutura natural para o "relógio de eventos" de um simulador.

### Heap binomial vs heap de Fibonacci (visão geral, sem entrar em prova de complexidade)

- **Heap binomial:** floresta de árvores binomiais, cada uma respeitando a propriedade de heap; união (`merge`) de dois heaps binomiais é eficiente (como somar em binário) — O(log n).
- **Heap de Fibonacci:** relaxa a estrutura ainda mais (árvores podem ficar "bagunçadas" temporariamente, corrigidas só quando necessário), permitindo `inserir` e `diminuir-chave` O(1) amortizado às custas de uma análise de complexidade mais sofisticada (potencial/crédito). Na prática, a constante escondida é grande, então implementações reais às vezes preferem heap binário simples por simplicidade, apesar da complexidade assintótica pior.

### Quando usar cada implementação, na prática

- **Array não ordenado:** só faz sentido se você quase nunca extrai o mínimo (ex.: coletar todos os elementos primeiro, ordenar uma única vez no final) — inserir é O(1), mas qualquer extração custa uma varredura completa.
- **Array ordenado:** o oposto — útil quando extrações são muito mais frequentes que inserções e a coleção muda pouco (ex.: fila de tarefas já conhecida de antemão, raramente recebe itens novos).
- **Heap binário:** a escolha padrão para a esmagadora maioria dos casos (escalonadores de SO, filas de eventos, Dijkstra/Prim de propósito geral) — bom equilíbrio entre todas as operações, simples de implementar, boa localidade de cache.
- **Heap binomial/Fibonacci:** só valem a complexidade de implementação quando `diminuir-chave` é chamada em volume muito grande, como Dijkstra/Prim em grafos densos de larga escala — fora desse cenário, o heap binário simples costuma ganhar na prática.

## Exemplos em C

O código abaixo mostra a ideia central desta seção em C: a fila de prioridade como **TAD** encapsulando uma implementação concreta (aqui, o heap binário de `5.1`) por trás de uma interface própria. Trocar a implementação (por array ordenado, heap binomial etc.) não muda a assinatura das funções `fp_*` — só o que está dentro delas.

```c
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDADE_MAX 100

// Reaproveita a estrutura de heap de 5.1 como implementação interna.
typedef struct {
    int dados[CAPACIDADE_MAX];
    int tamanho;
} Heap;

static int pai(int i)       { return (i - 1) / 2; }
static int filho_esq(int i) { return 2 * i + 1; }
static int filho_dir(int i) { return 2 * i + 2; }

static void troca(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static void heapify_up(Heap *h, int i) {
    while (i > 0 && h->dados[pai(i)] < h->dados[i]) {
        troca(&h->dados[pai(i)], &h->dados[i]);
        i = pai(i);
    }
}

static void heapify_down(Heap *h, int i) {
    int maior = i, e = filho_esq(i), d = filho_dir(i);
    if (e < h->tamanho && h->dados[e] > h->dados[maior]) maior = e;
    if (d < h->tamanho && h->dados[d] > h->dados[maior]) maior = d;
    if (maior != i) {
        troca(&h->dados[i], &h->dados[maior]);
        heapify_down(h, maior);
    }
}

// ---- TAD Fila de Prioridade: interface própria, escondendo o heap por baixo ----

typedef struct {
    Heap heap;
} FilaPrioridade;

void fp_inicializa(FilaPrioridade *fp) {
    fp->heap.tamanho = 0;
}

void fp_insere(FilaPrioridade *fp, int prioridade) {
    fp->heap.dados[fp->heap.tamanho] = prioridade;
    heapify_up(&fp->heap, fp->heap.tamanho);
    fp->heap.tamanho++;
}

int fp_remove_max(FilaPrioridade *fp) {
    int max = fp->heap.dados[0];
    fp->heap.tamanho--;
    fp->heap.dados[0] = fp->heap.dados[fp->heap.tamanho];
    heapify_down(&fp->heap, 0);
    return max;
}

int fp_consulta_max(FilaPrioridade *fp) {
    return fp->heap.dados[0];  // O(1) — não remove
}
```

Quem usa `FilaPrioridade` só enxerga `fp_insere`, `fp_remove_max`, `fp_consulta_max` — não sabe (nem precisa saber) que por dentro existe um heap binário em array. É exatamente a separação TAD (interface) vs. implementação (heap) discutida acima.

## Pontos de atenção / pegadinhas comuns de prova

- **Não confundir o TAD "fila de prioridade" com a estrutura "heap"** — heap é uma implementação, não a única.
- A vantagem do heap de Fibonacci só aparece **assintoticamente e em grafos densos**; em grafos esparsos ou pequenos, heap binário costuma ser mais rápido na prática (constantes menores, cache).
- `diminuir-chave` é a operação que diferencia as implementações na prática de algoritmos de grafo — não avalie apenas inserir/remover isoladamente.
- Array ordenado e não ordenado são casos-limite úteis para entender o trade-off, mas raramente usados em código real além de fins didáticos.

## Anotações pessoais

## Exercícios resolvidos
