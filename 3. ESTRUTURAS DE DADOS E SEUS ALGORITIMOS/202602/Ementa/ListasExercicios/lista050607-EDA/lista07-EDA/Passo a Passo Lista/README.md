# Passo a Passo Lista — lista07-EDA

Explicação devagar de cada questão já resolvida em código (`Qx/claude/main.c`), seguindo
[[../../../_modelo-de-arquivo|_modelo-de-arquivo]]. Ambas as questões ordenam um arquivo
binário de inteiros *in-place*, simulando acesso por índice via `fseek`/`fread`/`fwrite`.

1. [[Q1 - Ordenação por bolha em arquivo binário]] — `BolhaBin`: comparação de pares
   vizinhos, com corte antecipado quando uma passada não troca nada.
2. [[Q2 - Ordenação por inserção em arquivo binário]] — `insertSort`: prefixo sempre
   ordenado, cada elemento novo desloca só o necessário até achar seu lugar.
