# 01 - Árvores

## Por que árvores importam

Árvores são a estrutura de dados não-linear mais fundamental do curso: permitem busca, inserção e remoção em tempo logarítmico (quando balanceadas), representam hierarquias naturalmente (sistemas de arquivos, DOM, árvores de decisão, índices de banco de dados) e são a base conceitual para grafos (módulo 02) e para as árvores B/B+ de memória secundária (módulo 05). Entender árvores bem é pré-requisito direto para heaps (módulo 06, que são árvores binárias completas com uma propriedade extra).

## Pré-requisitos

- **Recursão** — a maioria dos algoritmos de árvore (percursos, busca, inserção) é naturalmente recursiva.
- **Ponteiros e alocação dinâmica de memória** — nós de árvore são registros auto-referenciados alocados dinamicamente. Não há uma pasta de "Fundamentos" neste curso; se precisar revisar `struct` com ponteiro para si mesma, `malloc`/`free`, e ponteiros em geral, consulte o KR (Kernighan & Ritchie), caps. 5 (Ponteiros e Arrays) e 6 (Structs), na raiz do curso.

## Subtópicos

1. **[1.1 Árvores Binárias](1.1%20Árvores%20Binárias/README.md)** — definições, tipos (cheia, completa, perfeita), percursos (pré-ordem, em-ordem, pós-ordem, em largura).
2. **[1.2 Árvores Binárias de Busca](1.2%20Árvores%20Binárias%20de%20Busca/README.md)** — a propriedade de ordenação que permite busca eficiente; busca, inserção, remoção; risco de degeneração.
3. **[1.3 Árvores AVL](1.3%20Árvores%20AVL/README.md)** — a primeira árvore auto-balanceada do curso; fator de balanceamento e rotações.

Ordem de estudo recomendada: siga a numeração acima (1.1 → 1.3). Cada subtópico depende do anterior.

> Árvores multi-caminho para disco (B e B+) não ficam aqui — a ementa oficial as trata como
> capítulo próprio, depois de Tabelas Hash. Ver [[../05 - Árvore B e B+/README|05 - Árvore B e B+]].
