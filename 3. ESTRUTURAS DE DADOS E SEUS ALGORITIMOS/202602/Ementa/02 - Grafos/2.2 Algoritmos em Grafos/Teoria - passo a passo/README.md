# Teoria - passo a passo — 2.2 Algoritmos em Grafos

Um conceito por arquivo. Ver o guia completo em [[../../../_modelo-de-explicacao]].

> **Nota de escopo:** os PDFs de aula disponíveis (`lista04-EDA/07_Grafos_*.pdf`) cobrem
> definições e representações (ver 2.1), mas **não** cobrem BFS, DFS, árvore geradora
> mínima ou caminhos mínimos. A lista04-EDA (Q1–Q5) também não testa esses algoritmos —
> testa contagem, k-regularidade, coloração e igualdade de grafos. Por isso, esta pasta
> cobre exatamente esses quatro algoritmos, sourced no código real da lista. BFS/DFS/MST/
> caminhos mínimos (Kruskal, Prim, Dijkstra, Bellman-Ford, Floyd-Warshall) continuam
> resumidos no `README.md` deste subtópico (fonte: livro CO/Cormen), prontos para virar
> `Teoria` completa assim que houver PDF de aula ou exercício que os cubra.

## Ordem de leitura

1. [[Teoria 01 - Contando vértices e arestas]] — `nn`, `na` (soma de graus / 2).
2. [[Teoria 02 - Grafo k-regular]] — testar se todo vértice tem o mesmo grau.
3. [[Teoria 03 - Verificando uma coloração válida]] — nenhum par de vizinhos com mesma cor.
4. [[Teoria 04 - Testando se dois grafos são iguais]] — igualdade rotulada, dupla inclusão.

Para a explicação passo a passo de cada questão da lista04, veja
`Ementa/ListasExercicios/lista04-EDA/Passo a Passo Lista/`.
