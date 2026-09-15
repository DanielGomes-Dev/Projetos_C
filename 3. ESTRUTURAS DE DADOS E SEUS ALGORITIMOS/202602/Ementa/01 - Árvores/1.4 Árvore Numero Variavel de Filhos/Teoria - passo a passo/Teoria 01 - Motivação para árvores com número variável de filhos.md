# Teoria 01 — Motivação para árvores com número variável de filhos

> **Onde isto entra:** generaliza a árvore binária (1.1) para o caso em que um nó pode ter
> **qualquer** número de filhos — é o primeiro passo antes de ver a representação concreta
> em C (Teoria 02).
> **Antes:** [[../../1.1 Árvores Binárias/Teoria - passo a passo/Teoria 02 - Árvore binária (definição e notação)|1.1 Teoria 02]] · [[../../1.1 Árvores Binárias/Teoria - passo a passo/Teoria 03 - Representando e construindo uma árvore binária em C|1.1 Teoria 03]].
> **Fonte:** Celes, cap. 13 "Árvores com número variável de filhos" (págs. 196-199);
> Cormen (CLRS), seção 10.4 "Representação de árvores enraizadas"; Szwarcfiter, seção 3.5
> "Conversão de uma Floresta".

## 1. A ideia em uma frase

Numa árvore binária cada nó tem no máximo 2 filhos — mas um diretório de arquivos pode ter
30 subpastas, uma pessoa pode ter 5 filhos, um nó de HTML pode ter qualquer número de
elementos-filho: precisamos de uma árvore em que o número de filhos de cada nó **não é
fixo nem limitado**.

## 2. De onde vem / por que fazemos assim

**O problema:** o Celes cita exatamente essa motivação — árvores de diretório, onde "o
número de filhos varia arbitrariamente". Outros exemplos do mesmo tipo: um organograma de
empresa (um chefe pode ter qualquer número de subordinados), uma árvore genealógica
(qualquer número de filhos por pessoa), a árvore de tags de um documento HTML/XML.

**Primeira tentativa (ingênua): um campo de ponteiro por filho possível.** Se soubéssemos
que nenhum nó tem mais de 3 filhos, poderíamos declarar:

```c
struct arv3 {
  char info;
  struct arv3 *f1, *f2, *f3;   /* um ponteiro por filho, deixando NULL o que sobrar */
};
```

Isso até funciona (é o que o Celes usa para exemplificar quadtree/octree — árvores de
Computação Gráfica com exatamente 4 e 8 filhos por nó, respectivamente), mas exige saber
**de antemão** um limite máximo de filhos, e o código para acessar os filhos não é
sistemático (é um `if`/`printf` por campo, sem um jeito de "percorrer todos os filhos" num
laço).

**Segunda tentativa: um vetor de N ponteiros.**

```c
#define N 3
struct arv3 {
  char info;
  struct arv3 *f[N];   /* agora dá pra percorrer com um for (i = 0; i < N; i++) */
};
```

Melhor — agora um laço `for` visita todos os filhos —, mas ainda exige um `N` fixo,
conhecido em tempo de compilação. Szwarcfiter formaliza por que isso não escala: se `m` é
o maior número de filhos entre os nós da árvore, cada nó precisa de `m` campos de
ponteiro; como `m` pode chegar a ser proporcional a `n` (o número de nós), o total de
memória usado é `O(n²)` — a esmagadora maioria desses campos fica com `NULL`, um
"consumo inaceitável de memória" nas palavras do livro.

**A solução real: cada nó guarda só 2 ponteiros, sempre.** Em vez de "um ponteiro por
filho", cada nó guarda:

1. um ponteiro para o **primeiro** filho, e
2. um ponteiro para o **próximo irmão** (o próximo filho do mesmo pai).

Com isso, um nó com 10 filhos não precisa de 10 campos — ele aponta só para o primeiro
filho, e os filhos ficam encadeados entre si como uma lista. Cormen chama isso de
representação **"filho-esquerda, irmão-direita"**; Celes chama de **"lista de filhos"**;
Szwarcfiter chega ao mesmo resultado por outro caminho — convertendo qualquer árvore
`T` numa árvore binária `B(T)` (filho esquerdo de `B(v)` = primeiro filho de `v` em `T`;
filho direito de `B(v)` = irmão seguinte de `v` em `T`). As três fontes descrevem
exatamente a mesma ideia. O detalhe completo (a struct em C, a definição recursiva) fica
para [[Teoria 02 - Definição por lista de filhos (prim_filho e prox_irmao)|Teoria 02]].

## 3. Prévia da solução (sem detalhar ainda)

Adiantando o que vem no próximo arquivo: a árvore da Figura 13.8 do Celes,

```
< a <b <c <d>> <e>> <f> <g <h> <i <j>>>>
```

(um nó `a` com filhos `b`, `f`, `g`; `b` com filhos `c`, `e`; `c` com filho `d`; `g` com
filhos `h`, `i`; `i` com filho `j`) fica assim, na representação por 2 ponteiros:

```
a ──primeiro_filho──▶ b ──irmão──▶ f ──irmão──▶ g
                       │                        │
                  primeiro_filho            primeiro_filho
                       ▼                        ▼
                       c ──irmão──▶ e           h ──irmão──▶ i
                       │                                     │
                  primeiro_filho                        primeiro_filho
                       ▼                                     ▼
                       d                                      j
```

Cada seta "──irmão──▶" ou "──primeiro_filho──▶" é **um único ponteiro por nó** — nunca
mais que 2 por nó, não importa quantos filhos ele tenha.

## 4. 📌 O que você está REALMENTE ganhando com essa troca

| O que parece | O que realmente é |
|---|---|
| "reduzi de N campos para 2 campos" | troquei uma estrutura de acesso **direto** (índice → filho) por uma estrutura de acesso **sequencial** (percorrer a lista de irmãos) — o preço de usar sempre 2 ponteiros é que, para achar o 5º filho de um nó, você percorre 4 irmãos primeiro, em vez de indexar `f[4]` direto |
| "não preciso mais saber o número máximo de filhos" | o número de filhos de cada nó agora é **implícito** no tamanho da lista de irmãos encadeada a partir de `prim_filho` — nada é reservado antecipadamente |
| "uso O(n) de memória, não O(n²)" | cada um dos `n` nós usa exatamente 2 ponteiros, sempre — o total nunca depende de quantos filhos os nós têm |

## 5. Exercícios de fixação

1. Por que a struct `struct arv3 { char info; struct arv3 *f1, *f2, *f3; }` não serve para
   representar uma árvore de diretórios de um sistema de arquivos real?
2. Se uma árvore tem `n` nós e cada nó reserva `m` campos de ponteiro (onde `m` é o maior
   número de filhos de qualquer nó da árvore), quantos campos de ponteiro existem ao todo,
   no pior caso, se `m` for proporcional a `n`? E na representação por 2 ponteiros?
3. Na representação "filho-esquerda, irmão-direita", quantos ponteiros tem **cada nó**,
   não importa se ele é uma folha ou se tem 20 filhos?

### Gabarito

1. Porque um diretório pode ter um número de subpastas que não se sabe de antemão (e pode
   crescer/diminuir com o tempo) — a struct fixa `f1, f2, f3` só suportaria no máximo 3
   filhos por nó, e sobraria memória desperdiçada em `NULL` para diretórios com poucos
   arquivos.
2. `O(n · m)` = `O(n²)` no pior caso (m proporcional a n) contra `O(n · 2)` = `O(n)` na
   representação por 2 ponteiros — uma diferença de ordem de grandeza.
3. Sempre exatamente **2** — um para `prim_filho` (ou `NULL` se for folha) e um para
   `prox_irmao` (ou `NULL` se for o último filho do seu pai).

## Resumo

- Árvore binária limita cada nó a no máximo 2 filhos; muitas aplicações reais (diretórios,
  organogramas, HTML/XML) precisam de um número de filhos arbitrário por nó.
- Reservar um campo de ponteiro por filho possível (`f1, f2, ..., fN`) exige conhecer um
  limite `N` antecipadamente e desperdiça memória quando `N` é grande mas pouco usado.
- A solução — usada por Celes, Cormen e Szwarcfiter de formas equivalentes — é dar a cada
  nó só **2** ponteiros: um para o primeiro filho, outro para o próximo irmão. Isso mantém
  o uso de memória em `O(n)` não importa quantos filhos cada nó tenha.

**Próximo:** [[Teoria 02 - Definição por lista de filhos (prim_filho e prox_irmao)]].
