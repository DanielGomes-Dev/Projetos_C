# Resumo dos Livros — 7. Tipos Abstratos de Dados

## Celes — Introdução a Estruturas de Dados (Cap. 9-12)
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido — ver os resumos de cada subtópico (7.1-7.7) para o detalhamento seção por seção.

Correção de capítulos: TAD é o **Cap. 9** (não 4) — abre a Parte II ("Estruturas dinâmicas") do livro, não a Parte I. A partir daí: listas encadeadas (**Cap. 10**), pilhas (**Cap. 11**) e filas (**Cap. 12**) — não 5/6/7. Vetores como lista sequencial (7.2) e matrizes (7.7) são tratados antes, na Parte I (Cap. 5 e 6), junto com os fundamentos da linguagem — não fazem parte do bloco de TADs dinâmicos propriamente dito.

Confirma-se o essencial do resumo anterior: pilha e fila são de fato apresentadas em **duas variantes cada** (vetor e lista encadeada), com o código completo das operações básicas seguindo sempre a mesma convenção de nomenclatura por prefixo (`lst_`, `pilha_`, `fila_`) estabelecida no capítulo de TAD.

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Cap. 2)

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Cap. 2)
O Capítulo 2 trata todas as listas lineares — sequenciais e encadeadas, incluindo pilhas, filas e listas circulares/duplas — de forma unificada, sem tratá-las como capítulos isolados. A introdução (2.1) define formalmente uma lista linear como "um conjunto de n ≥ 0 nós L[1], L[2], …, L[n] tais que suas propriedades estruturais decorrem, unicamente, da posição relativa dos nós dentro da sequência linear": se n > 0, L[1] é o primeiro nó, e para 1 < k ≤ n, L[k] é precedido por L[k−1].

O texto já introduz ali os casos particulares que dão nome aos subtópicos do curso: se inserções/remoções só ocorrem nas extremidades, a lista é um **deque**; se ocorrem só em uma extremidade, é uma **pilha**; se inserções ocorrem numa extremidade e remoções em outra, é uma **fila**. A organização do capítulo segue exatamente a classificação por tipo de armazenamento: alocação sequencial (posições contíguas em memória, Seção 2.2) versus alocação encadeada (posições ligadas por ponteiros, Seção 2.6-2.7) — a escolha entre uma e outra "depende essencialmente das operações que serão executadas sobre a lista, do número de listas envolvidas na operação, bem como das características particulares dessas listas".

## Cormen — Algoritmos: Teoria e Prática (Cap. 10)
O Capítulo 10, "Estruturas de Dados Elementares", abre anunciando o escopo: "examinaremos a representação de conjuntos dinâmicos por estruturas de dados simples que usam ponteiros [...]: pilhas, filas, listas ligadas e árvores enraizadas." A Seção 10.1 cobre pilhas (LIFO) e filas (FIFO) implementadas sobre um arranjo simples, com todas as operações em tempo O(1). A Seção 10.2 cobre listas ligadas, tratando por padrão a variante duplamente ligada (cada nó com ponteiros `próximo` e `anterior`), mencionando que uma lista pode ser simplesmente ou duplamente ligada, ordenada ou não, circular ou não — a mesma taxonomia de Szwarcfiter, mas com nomenclatura e ênfase ligeiramente diferentes.

Diferente de Szwarcfiter, Cormen enquadra essas estruturas explicitamente como implementações de "conjuntos dinâmicos" — uma interface abstrata comum (INSERT, DELETE, SEARCH) da qual pilha, fila e lista são casos particulares, o que aproxima seu tratamento da noção de TAD do Celes.

## Síntese
Os três livros descrevem essencialmente o mesmo mapa conceitual — separar interface de implementação, e dentro da implementação separar alocação sequencial de alocação encadeada — mas com pesos diferentes: Celes é o único que nomeia e isola explicitamente o conceito de TAD como capítulo próprio (base do subtópico 7.1); Szwarcfiter oferece o tratamento mais sistemático e unificado das variantes de lista em um único capítulo, com prova de complexidade a cada operação; Cormen enquadra as mesmas estruturas sob a lente de "conjuntos dinâmicos", com pseudocódigo mais próximo de código real e invariantes de laço formais.
