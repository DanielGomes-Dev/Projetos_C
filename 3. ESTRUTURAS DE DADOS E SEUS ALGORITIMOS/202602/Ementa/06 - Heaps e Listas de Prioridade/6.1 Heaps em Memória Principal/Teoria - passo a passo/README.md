# Teoria - passo a passo — 6.1 Heaps em Memória Principal

Um conceito por arquivo, devagar. Ver o guia completo em
[[../../../_modelo-de-explicacao]] e o exemplo de referência em
[[../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/README|1.1 Árvores Binárias]].

## Ordem de leitura

1. [[Teoria 01 - Propriedade de heap (min-heap e max-heap)]] — a regra pai-filho, e por que
   é mais fraca que BST.
2. [[Teoria 02 - Representando um heap em array (índices pai e filhos)]] — por que árvore
   completa (1.1, Teoria 06) permite guardar tudo num array, sem ponteiro.
3. [[Teoria 03 - Heapify-down e heapify-up]] — as duas operações que corrigem a propriedade
   depois de uma mudança.
4. [[Teoria 04 - Build-heap, inserção, extração e heapsort]] — monta um heap do zero em
   O(n), e como isso vira um algoritmo de ordenação completo.

Depois desta pasta, siga para [[../../6.2 Heaps em Memória Secundária/README|6.2 Heaps em
Memória Secundária]].
