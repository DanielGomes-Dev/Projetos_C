# 05 - Árvore B e B+

## Por que este módulo importa (e por que é separado de "01 - Árvores")

A ementa oficial do curso lista "Árvore B e B+ (em memória principal e secundária)" como um
tópico **próprio**, depois de Tabelas Hash — não como mais um tipo de árvore dentro do
módulo 01. A razão é conceitual, não só de organização: árvore B/B+ resolve um problema
diferente do de AVL. AVL (módulo `01 - Árvores`, 1.3) otimiza para **memória principal**
(RAM), onde qualquer acesso a um nó custa o mesmo. Árvore B/B+ otimiza para **memória
secundária** (disco): o custo dominante passa a ser o **número de acessos**, e a estrutura
inteira é desenhada em torno de minimizar isso — nós "gordos" (muitas chaves por nó) para
manter a árvore rasa. É o mesmo tipo de motivação de Tabelas Hash em memória secundária
(módulo `04 - Tabelas Hash`, 4.2) — por isso a ementa agrupa os três (hash, B, B+) depois de
fechar árvores clássicas e grafos.

## Pré-requisitos

- **Árvores binárias e BST** (módulo `01 - Árvores`, 1.1–1.2) — árvore B generaliza a ideia
  de "nó com filhos ordenados que guiam a busca", só que com mais de 2 filhos por nó.
- Noção de acesso a disco vs. RAM (ver `04 - Tabelas Hash/4.2`, que já introduz a motivação
  de memória secundária).

## Subtópicos

1. **[5.1 Árvores B](5.1%20Árvores%20B/README.md)** — ordem *m*, split (inserção) e
   merge/redistribuição (remoção); por que garante altura balanceada.
2. **[5.2 Árvores B+](5.2%20Árvores%20B+/README.md)** — variante com dados só nas folhas e
   folhas encadeadas; por que é a escolha real em índices de banco de dados.

Ordem de estudo: 5.1 → 5.2 (B+ é definida como diferença estrutural em cima de B).
