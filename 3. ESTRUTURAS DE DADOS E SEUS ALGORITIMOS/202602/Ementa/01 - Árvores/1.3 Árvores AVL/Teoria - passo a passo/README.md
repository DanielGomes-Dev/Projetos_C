# Teoria - passo a passo — 1.3 Árvores AVL

Um conceito por arquivo, explicado devagar, com exemplos tirados dos PDFs de aula
(`lista03-EDA/07_AVL_2026_08_25.pdf`, `07_AVL_parte2.pdf`). Ver o guia completo em
[[../../../_modelo-de-explicacao]].

## Ordem de leitura

1. [[Teoria 01 - O problema que a AVL resolve]] — degeneração de BST, e por que isso
   importa (retoma [[../../1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 05 - Complexidade e o risco de degeneração|1.2 Teoria 05]]).
2. [[Teoria 02 - Definição de AVL e o fator de balanceamento]] — a invariante `|FB| ≤ 1`
   em todo nó, e a fórmula `FB(nó) = altura(esq) − altura(dir)`.
3. [[Teoria 03 - Rotações simples (RSD e RSE)]] — o conserto para desbalanceamento "reto".
4. [[Teoria 04 - Rotações duplas (RED e RDE)]] — o conserto para desbalanceamento "torto"
   (composição de duas rotações simples).
5. [[Teoria 05 - Inserção completa em AVL]] — tudo junto, numa sequência real de 11
   inserções (exercício de aula), com 4 rotações disparadas ao longo do caminho.

Depois desta pasta, siga para os exemplos/exercícios da lista (quando a pasta
`Passo a Passo Lista/` existir em `Ementa/ListasExercicios/lista03-EDA/`), ou direto para
[[../../../05 - Árvore B e B+/README|05 - Árvore B e B+]].
