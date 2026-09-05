# 5. Heaps e Listas de Prioridade

## Por que este módulo importa

Heaps são a estrutura por trás de um dos algoritmos de ordenação mais eficientes (heapsort, O(n log n) in-place) e são a implementação padrão de filas de prioridade — o TAD que sustenta algoritmos de grafo essenciais como Dijkstra (caminho mínimo) e Prim (árvore geradora mínima), além de escalonadores de sistema operacional e simuladores de eventos discretos. É também a estrutura usada na seleção por substituição do módulo de ordenação externa (ver `03 - Arquivos e Ordenação Externa`).

## Pré-requisitos

- Árvores binárias (módulo `01 - Árvores`, especialmente 1.1) — heap é uma árvore binária quase-completa, mas representada em array.
- Noção de vetor/array dinâmico em C (ponteiros e alocação — ver KR se precisar revisar).
- Notação de complexidade assintótica (O-grande).

## Subtópicos

1. **[5.1 Heaps em Memória Principal](5.1%20Heaps%20em%20Mem%C3%B3ria%20Principal/README.md)** — heap binário clássico em array: propriedade de heap, heapify, build-heap, heapsort, inserção/extração.
2. **[5.2 Heaps em Memória Secundária](5.2%20Heaps%20em%20Mem%C3%B3ria%20Secund%C3%A1ria/README.md)** — adaptação de heaps para quando os dados não cabem em RAM: heaps multiway (d-ários), ligação com ordenação externa.
3. **[5.3 Listas de Prioridade](5.3%20Listas%20de%20Prioridade/README.md)** — o TAD fila de prioridade, suas implementações possíveis (array, heap binário, heap binomial, heap de Fibonacci) e aplicações em algoritmos de grafo.

Ordem sugerida de estudo: 5.1 → 5.2 → 5.3 (do concreto/memória principal para o TAD abstrato e suas variantes avançadas).
