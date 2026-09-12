# Passo a Passo Lista — lista06-EDA

Explicação devagar de cada questão já resolvida em código (`Qx/claude/main.c`), seguindo
[[../../../_modelo-de-arquivo|_modelo-de-arquivo]]. Veja a teoria correspondente em
`03 - Arquivos e Ordenação Externa/3.1/Teoria - passo a passo/`.

1. [[Q1 - Produto cartesiano de dois arquivos binários]] — gerar todos os pares
   (palavra de `a.bin`, palavra de `b.bin`) em `c.bin`, sem carregar nenhum arquivo
   inteiro na RAM.
2. [[Q2 - Buscar cliente por CPF sem carregar tudo]] — busca sequencial em arquivo
   binário, comparando `memcmp` registro a registro.
3. [[Q3 - Gerar arquivo de índices ordenado por saldo]] — arquivo de índices (indireção)
   em vez de reordenar os registros originais.
