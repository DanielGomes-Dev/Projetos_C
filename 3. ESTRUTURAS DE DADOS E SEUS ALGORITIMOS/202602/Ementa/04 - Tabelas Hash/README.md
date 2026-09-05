# 4. Tabelas Hash

Hashing é a técnica que troca a garantia de ordenação (que árvores oferecem) por velocidade: em condições típicas, busca, inserção e remoção custam **O(1) amortizado**, contra O(log n) de uma árvore balanceada. É a estrutura por trás de dicionários/mapas (`HashMap`, `dict`, tabelas de símbolos de compiladores) e de índices em bancos de dados quando não é preciso fazer buscas por intervalo (range queries) — aí árvores B/B+ (ver módulo 1) continuam vencendo.

**Pré-requisitos:** vetores/arrays, listas ligadas (para encadeamento separado), noção de complexidade amortizada.

## Subtópicos

- **[4.1 Tabelas Hash em Memória Principal](4.1%20Tabelas%20Hash%20em%20Mem%C3%B3ria%20Principal/README.md)** — função hash, tratamento de colisões (encadeamento vs endereçamento aberto), fator de carga, rehashing.
- **[4.2 Tabelas Hash em Memória Secundária](4.2%20Tabelas%20Hash%20em%20Mem%C3%B3ria%20Secund%C3%A1ria/README.md)** — adaptação do hashing para disco: hashing extensível e hashing linear, minimizando acessos a disco.

## Ordem de estudo

Primeiro 4.1 (hashing em memória principal, a base conceitual), depois 4.2 (a mesma ideia adaptada para quando a tabela não cabe em RAM — o paralelo natural é com árvores B do módulo 1, que resolvem o mesmo problema de minimizar I/O).
