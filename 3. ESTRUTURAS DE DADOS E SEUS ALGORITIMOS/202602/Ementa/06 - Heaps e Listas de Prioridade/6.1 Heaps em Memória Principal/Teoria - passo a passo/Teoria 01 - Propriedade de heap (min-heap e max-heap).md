# Teoria 01 — O que é a propriedade de heap, e por que ela é mais fraca que BST

> **Onde isto entra:** heap é a estrutura por trás de heapsort e de toda fila de
> prioridade (Dijkstra, Prim, escalonadores). Antes de qualquer operação, é preciso saber
> exatamente o que a estrutura garante — e, mais importante, o que ela **não** garante.
> **Antes:** [[../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 06 - Tipos de árvore binária (cheia, completa, perfeita)|1.1 Teoria 06 - Tipos de árvore binária]] (heap é construído sobre o conceito de árvore *completa*).
> **Fonte:** CO (Cormen), cap. 6 "Heapsort"; SZ (livro-base), seção de Heaps — não foi
> possível abrir os PDFs para conferir página exata nesta máquina (falta `poppler`); os
> algoritmos abaixo são a apresentação padrão desses livros.

## 1. A ideia em uma frase

Um heap é uma árvore binária **quase-completa** (Teoria 06 de 1.1) em que todo nó respeita
uma regra fraca com o pai: **num max-heap, o pai é sempre ≥ os filhos**; **num min-heap, o
pai é sempre ≤ os filhos**. É só isso — nada é dito sobre a relação entre irmãos.

## 2. De onde vem a necessidade (motivação antes da definição)

Imagine que você só precisa, repetidamente, pegar **o maior elemento** de um conjunto que
muda (ganha e perde elementos o tempo todo) — não precisa nunca da lista inteira ordenada,
só do topo. Manter uma BST (1.2) garantiria acesso ordenado a tudo, mas isso é **mais
garantia do que você precisa**, e custa mais para manter em certas operações. Heap é o
"TAD faça-o-mínimo-necessário": abre mão de qualquer ordem entre irmãos, e em troca ganha
uma estrutura mais simples de representar (Teoria 02) e operações tão rápidas quanto BST
para o que interessa (acessar/remover o topo).

## 3. A definição — lida devagar

> **Max-heap:** para todo nó `i` diferente da raiz, `valor(pai(i)) ≥ valor(i)`.
> **Min-heap:** para todo nó `i` diferente da raiz, `valor(pai(i)) ≤ valor(i)`.

> 📖 **Lendo devagar:** "para todo nó `i` diferente da raiz" — a regra não fala da raiz
> porque a raiz não tem pai; ela é automaticamente o extremo (maior, num max-heap; menor,
> num min-heap) porque **todo mundo** abaixo dela respeita "pai ≥ filho" em cadeia até
> chegar nela.

### Conferindo com uma árvore concreta

```
              8
           /     \
          4       5
         / \
        1   3
```

Isso é um max-heap? Verifique **cada** relação pai-filho, não o conjunto inteiro de uma vez:
- `8` (raiz) vs. filhos `4` e `5`: `8 ≥ 4` ✔, `8 ≥ 5` ✔.
- `4` vs. filhos `1` e `3`: `4 ≥ 1` ✔, `4 ≥ 3` ✔.
- `5` não tem filhos — nada a checar.

Todas as relações pai-filho passam → **é um max-heap válido**. Note que `5 > 4` (o nó `5`
é maior que o nó `4`, que está "acima" dele numa posição diferente da árvore) — **isso não
viola nada**, porque `5` e `4` não são pai e filho um do outro, são de subárvores
diferentes. Essa é exatamente a diferença para BST, na seção 4.

## 4. A diferença crucial para BST (letra miúda que costuma confundir)

Numa BST, existe uma ordem **global**: percorrendo em-ordem, os valores saem crescentes.
Num heap, a garantia é **só local** (pai vs. filho direto) — **não existe** ordem entre
irmãos, nem entre nós de subárvores diferentes, nem o percurso em-ordem produz nada
ordenado.

**Conferindo:** no heap acima, em-ordem daria `1, 4, 3, 8, 5` — **não está em ordem
crescente** (`3 > 1` mas depois `8 > 5`, sem padrão). Isso é esperado — heap nunca prometeu
isso.

**Consequência prática:** buscar um valor arbitrário num heap é O(n) — força bruta, igual à
Teoria 05 de 1.1 (busca sem propriedade de ordenação), porque não há informação de "vá para
a esquerda ou direita" que a estrutura ofereça. Heap não foi desenhado para busca — foi
desenhado para acesso rápido ao **topo** (o maior ou o menor), que é O(1) (é sempre a raiz).

## 5. 📌 O que você está REALMENTE garantindo

| O passo mecânico (checar "pai ≥ filho" em cada nó) | O que ele realmente garante |
|---|---|
| a regra vale para a raiz vs. seus filhos diretos | a raiz é ≥ tudo que está mais fundo que ela por **qualquer** caminho — é assim que "raiz = extremo" emerge de uma regra só local |
| a regra **não** compara nós de subárvores diferentes entre si | dois "primos" (mesma altura, ramos diferentes) podem estar em qualquer ordem relativa — só importa a cadeia pai→filho de cada um até a raiz |
| não existe garantia sobre em-ordem | heap não é substituto de BST — se você precisa de tudo ordenado, precisa de outra estrutura ou de heapsort completo (ver Teoria 04) |

## 6. Exercícios de fixação

1. A árvore `10 (filhos 9 e 12)` é um max-heap válido? Justifique olhando a definição.
2. Dado o max-heap da seção 3, se você trocasse o valor do nó `1` por `9`, a árvore ainda
   seria um max-heap válido? Por quê?
3. Um min-heap com raiz `2`, filho esquerdo `5`, filho direito `3` — os dois filhos podem
   estar em qualquer ordem relativa entre si (`5` e `3`, mesmo `5 > 3`)? Justifique.
4. Por que "buscar o valor 3 num heap" custa O(n) mesmo o heap tendo altura O(log n)?

### Gabarito

1. Não. `10 ≥ 9` ✔, mas `10 ≥ 12`? Não — `12 > 10`, viola a regra pai ≥ filho. Não é
   max-heap válido.
2. Não. `4` (pai de `1`) passaria a ter filho `9`, e `4 ≥ 9` é falso — viola a propriedade
   de heap naquele nó. A troca quebrou a estrutura.
3. Sim, sem problema — a definição de min-heap só exige `pai ≤ cada filho`, nada sobre a
   relação entre os filhos entre si. `2 ≤ 5` ✔ e `2 ≤ 3` ✔, independente de `5` ser maior
   que `3`.
4. Porque a altura O(log n) só ajuda a navegar quando existe uma regra de "para qual lado
   ir" — heap não garante isso para busca de valor arbitrário (só garante sobre pai vs.
   filho, não sobre esquerda vs. direita). Sem essa informação, é preciso olhar todos os
   nós no pior caso — igual à Teoria 05 de árvore binária qualquer, em 1.1.

## Resumo

- Heap = árvore binária quase-completa + "pai ≥ filho" (max) ou "pai ≤ filho" (min), regra
  **local**, checada nó a nó.
- Não existe ordem entre irmãos nem entre nós de subárvores diferentes — só a cadeia
  pai→filho importa.
- Consequência: acesso ao topo é O(1) (é sempre a raiz), mas busca de valor arbitrário é
  O(n) — heap não substitui BST.

**Próximo:** [[Teoria 02 - Representando um heap em array (índices pai e filhos)]].
