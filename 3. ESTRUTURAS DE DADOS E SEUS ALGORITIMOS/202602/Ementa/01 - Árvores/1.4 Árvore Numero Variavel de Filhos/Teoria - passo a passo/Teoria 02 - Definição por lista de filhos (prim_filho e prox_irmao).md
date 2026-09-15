# Teoria 02 — Definição por lista de filhos (`prim_filho` e `prox_irmao`)

> **Onde isto entra:** formaliza a ideia adiantada em Teoria 01 (2 ponteiros por nó) como a
> struct `TAV` usada em todo o código desta pasta (`TAVAR/TAV.h`).
> **Antes:** [[Teoria 01 - Motivação para árvores com número variável de filhos]].
> **Fonte:** Celes, cap. 13, "Representação em C" (págs. 199-201); código real em
> `TAVAR/TAV.h`.

## 1. A ideia em uma frase

Uma árvore com número variável de filhos é, recursivamente, **um nó raiz seguido de zero
ou mais subárvores** — e, em C, cada nó guarda só 2 ponteiros: um para o **primeiro
filho** e um para o **próximo irmão**.

## 2. A struct, lida pedaço por pedaço

Do arquivo `TAVAR/TAV.h`:

```c
typedef struct arv_var{
  int info;
  struct arv_var *prim_filho, *prox_irmao;
}TAV;
```

> **Lendo devagar:**
> - `struct arv_var { ... }` declara o "molde" de um nó — assim como em 1.1, o nó se
>   auto-referencia (contém ponteiros para o próprio tipo `struct arv_var`), o que só é
>   possível porque `struct arv_var *prim_filho` guarda um **endereço**, não uma cópia do
>   nó inteiro (senão a struct precisaria de espaço infinito).
> - `int info` — a informação guardada no nó (aqui, sempre um inteiro; poderia ser
>   qualquer tipo).
> - `struct arv_var *prim_filho` — ponteiro para o **primeiro** filho deste nó. Se este nó
>   não tiver filhos (for uma folha), `prim_filho == NULL`.
> - `struct arv_var *prox_irmao` — ponteiro para o **próximo filho do mesmo pai**, ou seja,
>   o irmão "à direita" deste nó. Se este nó for o **último** filho do seu pai,
>   `prox_irmao == NULL`.
> - `typedef struct arv_var TAV;` — a partir daqui, `TAV` é só um apelido mais curto para
>   `struct arv_var`; o código usa `TAV *a` em vez de `struct arv_var *a`.

O Celes usa os mesmos dois ponteiros, só que com nomes abreviados: `prim` e `prox`, na
struct `arvvar`/`ArvVar`. É a mesma ideia — `TAV` aqui só escreve os nomes por extenso.

## 3. A definição recursiva de árvore

Seguindo o Celes: uma árvore é composta por

- **um nó raiz**; e
- **zero ou mais subárvores** — cada uma dessas subárvores é, ela mesma, uma árvore
  (raiz + suas próprias subárvores).

Note o que isso implica: **não existe árvore vazia**, nessa definição — o caso-base da
recursão é a **folha**, isto é, um nó com **zero** subárvores (`prim_filho == NULL`), não
um ponteiro `NULL` no lugar da árvore inteira. Isso é diferente da árvore binária (1.2),
onde é comum tratar `NULL` como "a subárvore vazia" em ambos os lados de um nó. Aqui,
sempre existe pelo menos a raiz — uma árvore de diretório, por exemplo, nunca é vazia:
sempre existe ao menos o diretório raiz.

> **Por que isso importa para o código:** é por causa dessa definição que `TAV_busca`
> (Teoria 03) acessa `a->info` diretamente, sem checar `a == NULL` antes — a função supõe
> que sempre recebe uma árvore válida (não vazia) como entrada. Já `TAV_imprime` e
> `TAV_libera` (Teoria 05) têm um `if(a){...}` só por defensividade extra; na prática,
> pela forma como `TAV_insere` sempre encadeia nós já criados (nunca `NULL`) antes de
> chamar essas funções, esse `if` nunca chega a barrar um `NULL` de verdade — é a mesma
> garantia de "sempre não-vazia" se repetindo.

## 4. Notação textual e o exemplo do Celes

Da mesma forma que se escreve uma árvore binária como `<raiz esq dir>` (1.1), uma árvore
de filhos variáveis se escreve `<raiz sa1 sa2 ... san>`, listando todas as subárvores
filhas em ordem. A árvore de exemplo do Celes (Figura 13.8: `a` com filhos `b, f, g`; `b`
com filhos `c, e`; `c` com filho `d`; `g` com filhos `h, i`; `i` com filho `j`) se escreve:

```
<a <b <c <d>> <e>> <f> <g <h> <i <j>>>>
```

Desenhada como árvore:

```
                a
          ┌─────┼─────┐
          b      f      g
        ┌─┴─┐         ┌─┴─┐
        c   e         h   i
        │                 │
        d                 j
```

E, na struct `TAV`, cada aresta vertical do desenho acima é um ponteiro `prim_filho`
(pai → primeiro filho) e cada aresta horizontal é um ponteiro `prox_irmao` (irmão →
próximo irmão):

```
a ──prim_filho──▶ b ──prox_irmao──▶ f ──prox_irmao──▶ g
                   │                                   │
              prim_filho                          prim_filho
                   ▼                                   ▼
                   c ──prox_irmao──▶ e                 h ──prox_irmao──▶ i
                   │                                                     │
              prim_filho                                            prim_filho
                   ▼                                                     ▼
                   d                                                     j
```

## 5. Letra miúda

**"Zero ou mais subárvores" — o que isso cobre exatamente?** Cobre tanto uma folha (zero
subárvores, `prim_filho == NULL`) quanto um nó com 1 só filho (`prim_filho` aponta para
esse filho, e o `prox_irmao` **desse filho** é `NULL`, pois ele não tem irmãos) quanto um
nó com N filhos (lista de N nós encadeados por `prox_irmao`, começando em `prim_filho`).
Não há tratamento especial de caso — é a mesma estrutura de dados (uma lista encadeada de
filhos) para qualquer quantidade.

**Existe uma "árvore vazia" na prática?** No sentido do Celes, não — a definição não
menciona árvore vazia, só nó-folha. Mas um **ponteiro** `TAV *a` isolado (uma variável)
pode perfeitamente valer `NULL` antes de ser inicializado com `TAV_cria` — é essa distinção
entre "não existe árvore vazia como conceito" e "um ponteiro pode não apontar para nada
ainda" que o `if(a)` defensivo do item 3 acima protege.

## 6. Exercícios de fixação

1. Escreva, na notação `<raiz sa1 sa2 ...>`, a árvore em que `1` tem filhos `2` e `3`, e
   `2` tem um único filho `4`.
2. Desenhe a árvore da notação `<10 <20> <30 <40> <50>>>` (10 é raiz, com filhos 20 e 30;
   30 tem filhos 40 e 50).
3. No desenho do item 2, qual é o valor de `prox_irmao` do nó `20`? E o de `prim_filho` do
   nó `40`?
4. Por que a struct `TAV` **não** precisa de um campo separado para "número de filhos"?

### Gabarito

1. `<1 <2 <4>> <3>>`.
2. ```
          10
        ┌──┴──┐
        20    30
             ┌─┴─┐
            40   50
   ```
3. `prox_irmao` de `20` aponta para `30` (o próximo filho de `10`, o mesmo pai). `prim_filho`
   de `40` é `NULL` — `40` é folha, não tem filhos.
4. Porque o "número de filhos" nunca precisa ser guardado explicitamente: ele é **implícito**
   no comprimento da lista de irmãos alcançável a partir de `prim_filho` — quem precisar
   saber quantos filhos um nó tem percorre essa lista e conta (é exatamente o que
   `TAV_imprime`, em Teoria 05, faz sem nunca consultar uma "contagem" guardada).

## Resumo

- `TAV` guarda `info` + 2 ponteiros: `prim_filho` (primeiro filho) e `prox_irmao` (próximo
  irmão), sempre — não importa quantos filhos o nó tenha.
- Definição recursiva (Celes): árvore = raiz + zero ou mais subárvores; o caso-base é a
  folha (zero subárvores), não um ponteiro `NULL` no lugar da árvore inteira.
- Notação textual: `<raiz sa1 sa2 ... san>`, generalizando o `<raiz esq dir>` da árvore
  binária (1.1) para um número arbitrário de subárvores.

**Próximo:** [[Teoria 03 - Criação de nó e busca em profundidade]].
