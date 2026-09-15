# Teoria - passo a passo — 1.4 Árvore Número Variável de Filhos

Um conceito por arquivo, explicado devagar, com exemplos tirados de `TAVAR/TAV.h` e
`TAVAR/TAV.c` (código real, já compilado e testado) e do Celes (cap. 13). Ver o guia
completo em [[../../../_modelo-de-explicacao]].

## Ordem de leitura

1. [[Teoria 01 - Motivação para árvores com número variável de filhos]] — por que a árvore
   binária (1.1) não basta quando o número de filhos de um nó não é conhecido/limitado
   (diretórios, organogramas, HTML/XML).
2. [[Teoria 02 - Definição por lista de filhos (prim_filho e prox_irmao)]] — a struct `TAV`
   com só 2 ponteiros por nó, e a definição recursiva "árvore = raiz + zero ou mais
   subárvores".
3. [[Teoria 03 - Criação de nó e busca em profundidade]] — `TAV_cria` (O(1)) e `TAV_busca`
   (busca em profundidade recursiva, O(n) — sem propriedade de ordenação).
4. [[Teoria 04 - Inserção na árvore variável]] — `TAV_insere`: busca o pai pelo valor,
   encaixa o novo nó no início da lista de filhos dele.
5. [[Teoria 05 - Impressão e liberação em profundidade]] — `TAV_imprime` (pré-ordem) e
   `TAV_libera` (pós-ordem, com o cuidado de guardar o próximo irmão antes de destruir o
   atual).

Depois desta pasta, o `TAVAR/teste_arv_gen.c` mostra as 4 operações usadas juntas, num
programa interativo que lê a árvore pelo teclado. Em seguida, siga para
[[../../02 - Grafos/README|02 - Grafos]] (quando existir) ou revise
[[../../1.1 Árvores Binárias/README|1.1 Árvores Binárias]] para comparar as duas
representações (2 ponteiros com significados diferentes em cada caso).
