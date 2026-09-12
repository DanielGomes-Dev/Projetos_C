# Teoria 01 — Por que ordenar em disco é diferente, e a geração simples de partições

> **Onde isto entra:** primeira ideia de ordenação externa — por que os algoritmos de
> ordenação que você já conhece (quicksort, heapsort) não resolvem sozinhos quando o
> arquivo é maior que a RAM.
> **Antes:** [[../../3.1 Arquivos Binários e Texto/Teoria - passo a passo/README|3.1 Arquivos Binários e Texto]] (acesso a arquivo em C).
> **Fonte:** SZ (Szwarcfiter) — capítulo de Ordenação Externa; é o único dos 4 livros do
> curso com foco em memória secundária (conferir página exata ao abrir o PDF). Nenhum dos
> PDFs de aula já disponíveis (`lista050607-EDA/`) cobre este subtópico especificamente
> ainda — o exemplo numérico abaixo é construção própria para ilustrar o método do livro.

## 1. A ideia em uma frase

Quando o arquivo não cabe inteiro na memória, a ordenação vira um processo em **duas
etapas**: primeiro quebrar o arquivo em pedaços pequenos, cada um já ordenado (este
subtópico), depois juntar esses pedaços ordenados num único arquivo ordenado (3.3).

## 2. De onde vem a necessidade

Quicksort, heapsort e companhia assumem que **todos os dados cabem na memória ao mesmo
tempo** — o algoritmo precisa poder comparar/trocar qualquer par de elementos a qualquer
momento. Se o arquivo tem 10 milhões de registros e a RAM só comporta 100 mil, essa
suposição quebra: não dá pra "ver" o arquivo inteiro de uma vez. A pergunta que motiva este
subtópico: **como ordenar algo maior do que cabe na sua mesa de trabalho?**

## 3. A ideia central — lida devagar

> 📖 **Partição (ou *run*):** um pedaço do arquivo original, **já ordenado internamente**,
> pequeno o suficiente para ter sido ordenado inteiramente em memória.

A estratégia mais direta ("geração simples"): ler blocos de tamanho igual à memória
disponível (`M` registros), ordenar cada bloco por completo em RAM (com qualquer algoritmo
de ordenação em memória, custo `O(M log M)` por bloco), e escrever esse bloco já ordenado
de volta no disco como uma partição.

## 4. Conferindo com número concreto

Arquivo com `N = 12` registros, memória disponível `M = 3` registros:

```
Arquivo original:  6, 2, 9, 4, 1, 8, 12, 3, 10, 5, 7, 11
```

> **Trace da geração simples:**
> 1. Lê os 3 primeiros: `[6, 2, 9]` → ordena em RAM → `[2, 6, 9]` → escreve como Partição 1.
> 2. Lê os 3 seguintes: `[4, 1, 8]` → ordena → `[1, 4, 8]` → Partição 2.
> 3. Lê os 3 seguintes: `[12, 3, 10]` → ordena → `[3, 10, 12]` → Partição 3.
> 4. Lê os 3 últimos: `[5, 7, 11]` → já está ordenado → Partição 4.

**Número de partições geradas:** `⌈N / M⌉ = ⌈12 / 3⌉ = 4` — sempre esse valor, não importa a
ordem dos dados de entrada (cada bloco de `M` registros vira exatamente 1 partição).

## 5. Por que o número de partições importa (motivação para o próximo arquivo)

Quanto **mais** partições saem desta fase, mais trabalho a fase de intercalação (3.3) terá
depois para juntar tudo de volta. Isso motiva uma pergunta natural: **dá pra gerar menos
partições, maiores, sem aumentar o limite de memória `M`?** A resposta (sim — via seleção
por substituição) é o assunto do próximo arquivo.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| ler um bloco de `M` registros por vez | respeito o limite físico da RAM — nunca tento enxergar mais do arquivo do que cabe |
| ordenar cada bloco com quicksort/heapsort comum | dentro do bloco, é ordenação em memória normal — nada de novo aqui |
| escrever o bloco ordenado de volta como partição | "descarrego" o resultado no disco antes de processar o próximo bloco — libero a RAM pro próximo pedaço |

## 7. Exercícios de fixação

1. Um arquivo com `N = 100` registros e memória `M = 7`. Quantas partições a geração
   simples produz?
2. Por que a **última** partição pode ter menos que `M` registros?
3. O custo de ordenar cada bloco é `O(M log M)`. Por que isso **não** vira `O(N log N)`
   direto, mesmo processando o arquivo inteiro?

### Gabarito

1. `⌈100 / 7⌉ = ⌈14.28...⌉ = 15` partições (14 partições de 7 e 1 partição final de 1
   registro).
2. Porque `N` nem sempre é múltiplo de `M` — sobra um resto no final, que forma uma
   partição menor.
3. O custo total é `⌈N/M⌉ × O(M log M)`, que é `O(N log M)` — mais barato que `O(N log N)`
   porque `M ≪ N`. Mas repare: essa é só a fase de **geração**; o custo de **intercalar**
   as partições depois (3.3) é o que faz o total se aproximar de `O(N log N)` de novo — a
   divisão em fases não é mágica, só torna cada fase individualmente viável em memória
   limitada.

## Resumo

- Ordenação externa existe porque nem todo arquivo cabe em RAM de uma vez.
- Duas fases: gerar partições ordenadas (este subtópico) e depois intercalá-las (3.3).
- Geração simples: blocos de tamanho `M`, cada um ordenado em memória e escrito como
  partição — sempre gera `⌈N/M⌉` partições.

**Próximo:** [[Teoria 02 - Seleção por substituição (replacement selection)]].
