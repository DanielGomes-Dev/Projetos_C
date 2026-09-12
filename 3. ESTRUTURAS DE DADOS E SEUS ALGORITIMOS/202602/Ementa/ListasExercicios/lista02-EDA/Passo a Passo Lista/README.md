# Passo a Passo Lista — lista02-EDA (1.2 Árvores Binárias de Busca)

Explicação devagar de cada questão já resolvida em `Qx/claude/main.c`. Ver o guia de
formatação em [[../../../_modelo-de-arquivo]] e, para a teoria de base, [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/README|1.2 Teoria - passo a passo]].

1. [[Q1 - Maior elemento numa BST]] — desce sempre à direita: O(altura), não O(n) como em árvore binária qualquer (compare com lista01/Q3).
2. [[Q2 - Menor elemento numa BST]] — espelho de Q1.
3. [[Q3 - Retirar elementos ímpares de uma BST]] — coleta em vetor + remoção com `TABB_retira` (evita mexer em ponteiros na mão).
4. [[Q4 - Elementos menores que N num vetor]] — coleta em-ordem com poda (não visita subárvore direita de nó ≥ N).
5. [[Q5 - BST de figuras geométricas por área]] — a mesma BST, agora com chave calculada (área) em vez de `int` puro.
