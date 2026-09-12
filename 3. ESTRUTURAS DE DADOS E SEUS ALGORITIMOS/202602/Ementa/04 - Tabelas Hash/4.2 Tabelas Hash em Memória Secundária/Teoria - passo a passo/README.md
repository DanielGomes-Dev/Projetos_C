# Teoria - passo a passo — 4.2 Tabelas Hash em Memória Secundária

Um conceito por arquivo, explicado devagar. Ver o guia completo em
[[../../../_modelo-de-explicacao]].

> **Nota de fonte:** o livro-base deste subtópico (SZ/Szwarcfiter) não pôde ser aberto nesta
> máquina (falta ferramenta de renderização de PDF) — os exemplos numéricos das Teorias 02
> e 03 foram construídos para esta explicação, fiéis ao mecanismo já descrito no
> `README.md` deste subtópico, mas não são retirados literalmente do livro. Confirme contra
> o livro se for citar em prova.

## Ordem de leitura

1. [[Teoria 01 - Por que memória secundária muda o problema]] — bucket, por que "acessos a
   disco" substitui "comparações" como métrica de custo.
2. [[Teoria 02 - Hashing extensível (diretório e buckets)]] — diretório em RAM, profundidade
   global/local, split de bucket.
3. [[Teoria 03 - Hashing linear (crescimento sem diretório)]] — ponteiro de divisão,
   crescimento incremental, overflow temporário.

Isso fecha o módulo `04 - Tabelas Hash`. Próximo módulo: [[../../../05 - Árvore B e B+/README|05 - Árvore B e B+]].
