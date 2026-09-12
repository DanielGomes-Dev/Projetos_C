# Teoria - passo a passo — 4.1 Tabelas Hash em Memória Principal

Um conceito por arquivo, explicado devagar, com o exemplo real do livro-base (matrícula de
aluno, CE/Celes, Cap. 18). Ver o guia completo em [[../../../_modelo-de-explicacao]].

## Ordem de leitura

1. [[Teoria 01 - Por que precisamos de uma função hash]] — o problema do vetor gigante e a
   ideia central de comprimir a chave num índice pequeno.
2. [[Teoria 02 - Colisões — tratamento por posição livre (endereçamento aberto)]] — sondagem
   linear, clustering primário.
3. [[Teoria 03 - Dispersão dupla (double hashing)]] — segunda função hash pra variar o
   passo de sondagem entre chaves diferentes.
4. [[Teoria 04 - Encadeamento separado (listas ligadas nos buckets)]] — cada posição vira
   lista, tabela nunca "enche".
5. [[Teoria 05 - Fator de carga e rehashing]] — `α = n/m`, por que ele determina o
   desempenho, e quando/como redimensionar a tabela.

Depois desta pasta, siga para [[../../4.2 Tabelas Hash em Memória Secundária/README|4.2 Tabelas Hash em Memória Secundária]].
