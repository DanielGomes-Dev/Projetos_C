# Teoria 01 — O problema que a AVL resolve

> **Onde isto entra:** retoma exatamente o problema fechado em 1.2 Teoria 05 (degeneração
> de BST) — a AVL existe para resolvê-lo.
> **Antes:** [[../../1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 05 - Complexidade e o risco de degeneração|1.2 Teoria 05]].
> **Fonte:** `lista03-EDA/07_AVL_2026_08_25.pdf`, págs. 2–7 (slides da Profa. Vanessa
> Braganholo).

## 1. A ideia em uma frase

Uma árvore binária de busca comum pode "desbalancear progressivamente" à medida que você
insere ou remove valores, virando uma fila disfarçada — a AVL é a estrutura que **nunca**
deixa isso acontecer.

## 2. Conferindo o problema com os exemplos do slide

O slide mostra três inserções diferentes, todas em BSTs comuns (sem nenhuma correção):

**Inserção de `{24, 27, 13, 10, 56, 15, 30}`:**
```
              24
           /      \
         13         27
        /  \          \
      10    15         56
                        /
                      30
```
Já dá para ver um lado (direita, via `27→56→30`) mais fundo que o outro.

**Inserção de `{13, 10, 15, 24, 27, 30, 56}`** (mesmos 7 valores, ordem diferente):
```
13
  \
   15
     \
      24
        \
         27
           \
            30
              \
               56
```
Cada valor **maior** que o anterior vira uma "fila só para a direita" — exatamente o pior
caso descrito em 1.2 Teoria 05.

**Inserção de `{1, 13, 24, 27, 56}`** — mesmo fenômeno, escala menor:
```
1
 \
  13
    \
     24
       \
        27
          \
           56
```

## 3. A consequência (o slide chama de "consequência" explicitamente)

> **Buscas ficam mais custosas.**

Na última árvore acima, buscar `56` custa 5 comparações (desce todos os níveis) — numa
árvore balanceada com os mesmos 5 valores, custaria no máximo 3. A degradação piora
proporcionalmente ao número de elementos inseridos "em sequência crescente ou decrescente".

## 4. O objetivo do balanceamento

> **Distribuição equilibrada dos nós**, com dois objetivos:
> — otimizar as operações de consulta;
> — diminuir o número médio de comparações.

E a meta concreta: garantir que busca, inserção e remoção sejam **O(log n) no pior caso** —
não só no caso médio ou no melhor caso, como acontecia com BST comum.

## 5. 📌 O que você está REALMENTE observando nesses exemplos

| O que parece | O que realmente é |
|---|---|
| "a árvore ficou tortinha de um lado" | um lado tem altura maior que o outro — é exatamente o que o **fator de balanceamento** (Teoria 02) vai medir numericamente |
| "inserir em ordem crescente é ruim" | é o caso que **maximiza** a diferença de altura entre os lados a cada passo — o pior caso possível |
| "BST comum não previne isso" | porque a definição de BST (1.2 Teoria 01) só fala de **ordem** dos valores, nunca de **forma**/altura da árvore |

## 6. Exercícios de fixação

1. Insira, numa BST comum (sem nenhuma correção), os valores `5, 4, 3, 2, 1` nessa ordem.
   Desenhe. Que formato resulta?
2. Compare com inserir `3, 2, 4, 1, 5` (mesmos 5 valores). Desenhe. A altura é diferente?
3. Por que "buscas ficam mais custosas" é a consequência mais citada do desbalanceamento,
   e não, por exemplo, "inserção fica mais custosa"?

### Gabarito

1. Cada valor é menor que o anterior → fila só para a esquerda:
   ```
           5
          /
         4
        /
       3
      /
     2
    /
   1
   ```
   Altura 4 (5 nós).
2. `3` raiz; `2<3`→esq; `4>3`→dir; `1<3`→esq(`2`),`1<2`→esq; `5>3`→dir(`4`),`5>4`→dir:
   ```
        3
       / \
      2    4
     /      \
    1        5
   ```
   Altura 2 — bem menor com os mesmos 5 valores, só mudando a ordem de inserção.
3. Porque busca é a operação mais executada na prática (uma estrutura de dados normalmente
   é consultada muito mais vezes do que é modificada), e seu custo depende diretamente da
   altura — inserção e remoção também degradam junto (ambas descem a árvore até o lugar
   certo), mas o efeito mais visível e mais citado é o de busca, por ser a operação mais
   frequente.

## Resumo

- BST comum pode degenerar: a mesma coleção de valores pode virar árvore balanceada ou
  "fila", dependendo só da ordem de inserção.
- Consequência direta: busca (e as outras operações) deixam de ser O(log n) e passam a
  custar O(altura), que pode chegar a O(n).
- Objetivo do balanceamento: garantir O(log n) no **pior caso**, sempre — é isso que a AVL
  entrega (Teoria 02 em diante).

**Próximo:** [[Teoria 02 - Definição de AVL e o fator de balanceamento]].
