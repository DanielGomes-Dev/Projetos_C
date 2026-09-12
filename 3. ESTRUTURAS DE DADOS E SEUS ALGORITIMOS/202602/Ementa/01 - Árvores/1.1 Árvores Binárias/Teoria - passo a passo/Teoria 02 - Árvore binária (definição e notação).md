# Teoria 02 — O que é uma árvore *binária*, especificamente

> **Onde isto entra:** árvore binária é o caso particular de árvore (Teoria 01) que o resto
> do curso usa o tempo todo — BST (1.2), AVL (1.3), heap (módulo 06) são todas árvores
> binárias com uma regra extra.
> **Antes:** [[Teoria 01 - O que é uma árvore (terminologia)]].
> **Fonte:** `lista01-EDA/05_ArvoresBinarias_sem_caminhamento.pdf` (slides da Profa. Vanessa
> Braganholo).

## 1. A ideia em uma frase

Numa árvore binária, **cada nó tem no máximo 2 filhos** — e esses dois filhos são
**diferentes entre si**: um é "o da esquerda", outro é "o da direita". Trocar os dois muda a
árvore, mesmo que os valores sejam iguais.

## 2. Por que "no máximo 2" e por que a ordem importa

Na Teoria 01, um nó podia ter qualquer número de filhos (grau qualquer), sem distinção entre
eles. Árvore binária restringe isso por um motivo prático: com só duas posições possíveis
por nó, dá pra guardar a árvore inteira usando **exatamente 2 ponteiros por nó** — nem mais,
nem menos. É a estrutura mais simples que ainda permite tudo o que o curso precisa
(percursos, busca, balanceamento). A distinção esquerda/direita importa porque, mais adiante
(BST, 1.2), o **lado** vai carregar significado ("menor que o pai" vs. "maior que o pai") —
uma árvore com filho só à esquerda é estruturalmente diferente de uma com filho só à
direita, mesmo tendo o mesmo único filho.

## 3. A definição — lida devagar

O slide (pág. 3) dá a definição **recursiva**:

> Uma árvore binária é:
> — Ou uma árvore vazia;
> — Ou um nó raiz com duas subárvores: a subárvore da esquerda (SAE) e a subárvore da
>   direita (SAD).

> 📖 **Lendo devagar:**
> 1. "Ou uma árvore vazia" — o **caso base** da recursão. Toda árvore, por maior que seja,
>    termina em pontas vazias (é isso que faz um algoritmo recursivo sobre árvore saber
>    quando parar).
> 2. "Ou um nó raiz com duas subárvores" — o **caso recursivo**: a árvore inteira é só um
>    valor (a raiz) mais **duas árvores menores** dentro dela (SAE e SAD). Cada uma dessas
>    subárvores é, de novo, "ou vazia, ou um nó com duas subárvores" — a mesma definição se
>    aplicando em escala menor.
> 3. Note que SAE e SAD **também podem ser vazias** — um nó pode ter filho só à esquerda,
>    só à direita, nos dois, ou em nenhum (nó folha).

### Conferindo com uma árvore concreta

O slide (pág. 4) usa esta árvore:

```
              a
          /       \
         b          c
        / \        / \
       d   e      f   g
      / \
     h   i
```

Aplicando a definição: a árvore inteira é o nó `a` com SAE = (a árvore que começa em `b`) e
SAD = (a árvore que começa em `c`). Dentro da SAE de `a`: o nó `b` tem SAE = (árvore que
começa em `d`) e SAD = (árvore só com o nó `e`, que por sua vez tem SAE e SAD **vazias** —
`e` é folha). E assim por diante, até chegar nas folhas `h`, `i`, `e`, `f`, `g`, todas com
SAE e SAD vazias.

## 4. Notação textual (útil pra escrever árvore sem desenhar)

O mesmo slide mostra uma forma de escrever qualquer árvore binária como texto, na forma
`<Raiz SAE SAD>`. Para a árvore acima:

```
<a <b <d <h <> <>> <i <> <>>> <e <> <>>> <c <f <> <>> <g <> <>>>>
```

> 📖 **Lendo devagar, de dentro pra fora:** comece pela parte mais interna.
> - `<h <> <>>` — nó `h`, com SAE vazia (`<>`) e SAD vazia (`<>`): `h` é folha.
> - `<d <h <> <>> <i <> <>>>` — nó `d`, cuja SAE é a folha `h` (o bloco acima) e cuja SAD é
>   a folha `i`.
> - subindo mais um nível: `<b <d ...> <e <> <>>>` — nó `b`, com SAE = a subárvore de `d`
>   (que contém `h` e `i`) e SAD = a folha `e`.
> - e assim até `<a <b...> <c...>>` — a árvore inteira.

Existe uma versão abreviada: como `<> <>` (as duas subárvores vazias) é tão comum, escreve-se
só `<X>` para "nó `X`, folha". A mesma árvore fica: `<a <b <d <h> <i>> <e>> <c <f> <g>>>` —
mais curto, mesma informação.

## 5. Letra miúda

**"Duas subárvores" não significa "sempre dois filhos".** Uma árvore vazia é uma subárvore
válida — então "duas subárvores" inclui o caso de uma (ou as duas) ser vazia. Não confundir
"tem duas subárvores" (sempre verdade, na definição) com "tem dois filhos" (só verdade se
nenhuma das subárvores for vazia).

## 6. Exercícios de fixação

1. Escreva, na notação `<Raiz SAE SAD>` completa (sem a versão abreviada), a árvore com raiz
   `1`, filho esquerdo `2` (folha) e filho direito `3` (folha).
2. Desenhe a árvore representada por `<a <b> <c <d> <e>>>` (usando a notação abreviada
   `<X>` = folha).
3. Uma árvore com um único nó `5` (sem filhos) é uma árvore binária válida? Justifique
   usando a definição recursiva.
4. Duas árvores: a primeira tem raiz `10` com filho **esquerdo** `20` (e mais nada); a
   segunda tem raiz `10` com filho **direito** `20` (e mais nada). Elas são a mesma árvore
   binária? Por quê?

### Gabarito

1. `<1 <2 <> <>> <3 <> <>>>`.
2. `a` é a raiz; SAE de `a` é a folha `b`; SAD de `a` é o nó `c`, cuja SAE é a folha `d` e
   SAD é a folha `e`:
   ```
          a
        /   \
       b     c
            / \
           d   e
   ```
3. Sim. Pela definição, "um nó raiz com duas subárvores" — as duas subárvores de `5` são
   ambas vazias (`<> <>`), o que é permitido. `<5 <> <>>` é uma árvore binária válida.
4. Não são a mesma árvore — em árvore binária, esquerda e direita são posições distintas.
   A primeira é `<10 <20 <> <>> <>>`; a segunda é `<10 <> <20 <> <>>>`. Estruturas
   diferentes, mesmo com os mesmos valores.

## Resumo

- Árvore binária: cada nó tem **até 2** subárvores, e elas são distinguíveis (esquerda ≠
  direita).
- Definição recursiva: árvore vazia (caso base) OU nó + SAE + SAD (caso recursivo, onde SAE
  e SAD são, elas mesmas, árvores binárias — possivelmente vazias).
- Notação textual `<Raiz SAE SAD>` (ou `<X>` abreviado para folha) é só outro jeito de
  escrever a mesma estrutura, útil quando não dá pra desenhar.

**Próximo:** [[Teoria 03 - Representando e construindo uma árvore binária em C]].
