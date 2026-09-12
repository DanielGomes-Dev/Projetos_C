# Teoria - passo a passo — 5.1 Árvores B

Um conceito por arquivo, explicado devagar, com uma árvore de ordem m=3 construída e
mantida ao longo dos arquivos (a mesma árvore aparece em busca, inserção e remoção). Fontes:
SZ e CO (Cormen, cap. 18) — ver o guia completo em [[../../../_modelo-de-explicacao]].

## Ordem de leitura

1. [[Teoria 01 - Por que não usar AVL BST em disco (motivação)]] — por que memória
   secundária muda o problema; comparação numérica de acessos a disco (AVL vs. árvore B).
2. [[Teoria 02 - O que é uma árvore B (ordem m e propriedades estruturais)]] — ordem m,
   as 5 propriedades, e a convenção alternativa "grau mínimo t" do Cormen.
3. [[Teoria 03 - Busca em árvore B (por igualdade)]] — duas buscas encaixadas (dentro do
   nó, e entre os filhos); complexidade O(log_m n).
4. [[Teoria 04 - Split na inserção (m=3, passo a passo)]] — construção completa de uma
   árvore de m=3, inserindo `10, 20, 5, 30, 40, 50, 60, 70, 80`, com split simples e split
   propagado até a raiz.
5. [[Teoria 05 - Merge e redistribuição na remoção]] — os dois jeitos de consertar um nó
   com poucas chaves (underflow): pedir emprestado a um irmão, ou fundir com ele.

Depois desta pasta, siga para [[../../5.2 Árvores B+/README|5.2 Árvores B+]].
