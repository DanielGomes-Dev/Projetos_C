# 2. Grafos

Grafos modelam relações entre entidades — redes, mapas, dependências, fluxos — e são a estrutura de dados mais geral do curso: listas, árvores e filas de prioridade aparecem como casos particulares ou como ferramentas auxiliares dos algoritmos de grafos (ex.: heap no Dijkstra/Prim, union-find no Kruskal).

**Pré-requisitos:** recursão, filas e pilhas (usadas em BFS/DFS), e noções básicas de ponteiros/structs em C para representar listas de adjacência — não há pasta de "Fundamentos" neste curso; se precisar revisar ponteiros/structs, consulte o KR (Kernighan & Ritchie) diretamente.

## Subtópicos

1. **[2.1 Conceitos e Representações de Grafos](2.1%20Conceitos%20e%20Representa%C3%A7%C3%B5es%20de%20Grafos/README.md)** — definições formais, matriz de adjacência vs. lista de adjacência e quando usar cada uma.
2. **[2.2 Algoritmos em Grafos](2.2%20Algoritmos%20em%20Grafos/README.md)** — busca (BFS/DFS), árvore geradora mínima (Kruskal/Prim) e caminhos mínimos (Dijkstra/Bellman-Ford/Floyd-Warshall).

Estude 2.1 antes de 2.2: os algoritmos da segunda subpasta dependem de escolher a representação certa na primeira.
