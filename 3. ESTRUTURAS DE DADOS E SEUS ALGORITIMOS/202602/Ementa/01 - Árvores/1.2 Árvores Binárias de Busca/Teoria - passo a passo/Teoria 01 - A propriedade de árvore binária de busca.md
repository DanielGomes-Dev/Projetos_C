# Teoria 01 — O que torna uma árvore binária uma árvore de *busca*

> **Onde isto entra:** em 1.1, buscar um valor exigia olhar a árvore inteira (força bruta,
> O(n)). Aqui aparece a regra que resolve isso.
> **Antes:** [[../../1.1 Árvores Binárias/Teoria - passo a passo/Teoria 05 - Percurso em largura, busca e altura|1.1 Teoria 05]] (busca força bruta, para comparar).
> **Fonte:** `lista02-EDA/06_ArvoresBinariasBusca.pdf` (slides da Profa. Vanessa Braganholo).

## 1. A ideia em uma frase

Uma árvore binária de busca (BST) é uma árvore binária **onde a posição de cada valor
carrega informação**: olhando só a raiz, você já sabe de que lado um valor buscado *tem*
que estar — sem essa garantia (1.1), era preciso olhar os dois lados.

## 2. Por que essa regra, e não outra

O motivo de existir é resolver o problema da Teoria 05 de 1.1: busca força bruta é O(n)
porque, sem ordenação, nada garante que o valor não esteja "do outro lado". A pergunta que
motiva a BST é: *que regra eu poderia impor à árvore para que, a cada passo, eu pudesse
**descartar metade** da árvore sem olhar nela?* Resposta: usar o valor do nó atual como
"divisor de águas".

## 3. A definição — lida devagar

O slide (pág. 4) define: uma árvore binária é uma BST se, para todo nó (chamado `raiz`
aqui, mas vale para qualquer nó, não só a raiz da árvore inteira):

> — Chaves da subárvore esquerda de `raiz` são **menores** do que a chave de `raiz`;
> — Chaves da subárvore da direita de `raiz` são **maiores** do que a chave de `raiz`; e
> — As subárvores da esquerda e da direita de `raiz` são, elas mesmas, árvores binárias de
>   busca.

> 📖 **Lendo devagar:** as duas primeiras condições parecem simples, mas a terceira é a
> parte que costuma passar despercebida — **não basta** os filhos diretos respeitarem a
> ordem; **todo descendente**, por mais fundo que esteja, também precisa. É uma definição
> recursiva: a mesma regra vale em cada subárvore, recursivamente.

## 4. Conferindo com a árvore do slide

```
              500
           /       \
         300         800
        /   \       /   \
      150   400   600   900
```

Conferindo nó por nó: `300 < 500` ✔ (subárvore esquerda de `500`), `800 > 500` ✔. Dentro da
subárvore de `300`: `150 < 300` ✔, `400 > 300` ✔ — **e também** `150 < 500` e `400 < 500`
(precisam respeitar não só o pai direto, mas todo ancestral). Mesma checagem do lado
direito. **É uma BST válida.**

## 5. Uma "pegadinha": várias BSTs para o mesmo conjunto

O slide (pág. 5) mostra que, para o conjunto de chaves `{1,2,3,4,5,6,7}`, existem **várias**
BSTs válidas diferentes — por exemplo, uma com raiz `3` e outra com raiz `2`, ambas válidas,
com formas bem diferentes (uma mais balanceada, outra mais "torta"). Isso é importante para
a Teoria 05 (complexidade): a **mesma informação** pode estar organizada de formas com
custo de busca muito diferente.

## 6. Letra miúda

**"Menor" e "maior" pressupõem que não há chaves repetidas.** O código deste curso (seção
seguinte) trata `elem < a->info` e `elem > a->info` como as duas únicas alternativas depois
de descartar igualdade — se sua aplicação precisar de chaves repetidas, a regra "onde vai o
igual" precisa ser decidida à parte (não é coberta aqui).

## 7. Exercícios de fixação

1. Verifique se esta árvore é uma BST válida: raiz `50`, filho esquerdo `70`, filho direito
   `90`. Justifique.
2. Numa BST com raiz `40`, existe algum nó com valor `35` na subárvore **direita** de `40`?
   Por quê?
3. Desenhe duas BSTs diferentes e válidas para o conjunto `{10, 20, 30}`.

### Gabarito

1. Não é válida — `70 > 50`, mas está na subárvore **esquerda**, violando "esquerda deve
   ser menor que a raiz".
2. Não — a subárvore direita de `40` só pode conter valores **maiores** que `40`; `35 < 40`
   não pode estar lá, em nenhuma profundidade.
3. Ex.: (a) raiz `20`, esquerda `10`, direita `30` (balanceada); (b) raiz `10`, sem
   esquerda, direita `20`, que tem direita `30` (uma "fila" — ainda é uma BST válida, só que
   degenerada — ver Teoria 05).

## Resumo

- BST: subárvore esquerda **toda** menor que o nó, subárvore direita **toda** maior — regra
  que vale recursivamente em todo nível, não só nos filhos diretos.
- Existe mais de uma BST válida para o mesmo conjunto de chaves — a forma depende da ordem
  de inserção (Teoria 03).
- É essa garantia que permite descartar metade da árvore a cada passo de busca (Teoria 02),
  em vez de olhar os dois lados como em 1.1.

**Próximo:** [[Teoria 02 - Busca numa BST]].
