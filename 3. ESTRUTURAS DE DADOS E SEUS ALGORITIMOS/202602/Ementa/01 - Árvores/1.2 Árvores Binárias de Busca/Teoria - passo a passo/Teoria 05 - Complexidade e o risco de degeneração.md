# Teoria 05 — Complexidade da BST, e por que ela pode degenerar

> **Onde isto entra:** fecha o subtópico explicando o "porém" da BST — e motiva por que o
> curso segue direto para AVL (1.3).
> **Antes:** [[Teoria 04 - Remoção numa BST (os três casos)]].
> **Fonte:** `lista02-EDA/06_ArvoresBinariasBusca.pdf`, pág. 8 e 18.

## 1. A ideia em uma frase

O custo de busca/inserção/remoção numa BST é proporcional à **altura** da árvore — e a
altura depende inteiramente da **ordem** em que os valores foram inseridos, podendo variar
de `log n` (ótimo) até `n` (péssimo).

## 2. De onde vem essa complexidade

O slide (pág. 8) raciocina assim: cada chamada de `busca_ABB` faz um número **constante**
de operações (uma comparação, uma decisão). O número de chamadas é, no pior caso, um por
nível descido — então o custo total é proporcional a **quantos níveis existem no caminho
percorrido**, ou seja, à altura da árvore no pior caso.

## 3. Conferindo com os dois extremos

**Melhor caso — árvore completa** (ver [[../../1.1 Árvores Binárias/Teoria - passo a passo/Teoria 06 - Tipos de árvore binária (cheia, completa, perfeita)|1.1 Teoria 06]]):
com `n` nós bem distribuídos, a altura é `log₂ n`. Para `n = 1000`, isso é só uns 10 níveis.

**Pior caso — árvore degenerada (vira uma "fila")**: se você inserir valores **já
ordenados** — por exemplo `1, 2, 3, 4, 5` — cada novo valor só pode ir para a direita do
anterior (é sempre maior que tudo que já está lá):
```
1
 \
  2
   \
    3
     \
      4
       \
        5
```
Altura = `n - 1` (aqui, 4). Para `n = 1000` valores inseridos em ordem, a altura seria 999
— busca de um valor no fundo custaria **999 comparações**, não 10. É basicamente uma lista
encadeada disfarçada de árvore.

## 4. Por que a mesma estrutura tem comportamentos tão diferentes

Não é a BST "que está errada" — a definição (Teoria 01) é satisfeita nos dois casos. O
problema é que a definição **não impõe nada sobre a forma** — só sobre a ordem dos valores.
Duas árvores com a mesma informação, mas formas diferentes (como você viu na Teoria 01,
seção 5, e na Teoria 03, seção 6), têm custos de operação completamente diferentes.

## 5. 📌 O que você está REALMENTE fazendo (ao analisar complexidade de BST)

| O passo mecânico | O que ele realmente é |
|---|---|
| contar comparações numa busca | contar **níveis descidos** — cada comparação corresponde a um nível |
| perguntar "é o pior caso?" | perguntar "essa é a árvore mais **alta** possível para esses valores?" — inserção em ordem crescente/decrescente é o jeito mais direto de forçar isso |
| dizer "O(log n)" sem qualificar | **incompleto** — só é `O(log n)` se a árvore estiver balanceada; sem essa garantia, o correto é dizer "O(altura da árvore)", que pode ser até O(n) |

## 6. Letra miúda

**"No pior caso" não é uma situação rara e exótica** — é fácil de provocar sem querer: dados
já ordenados (ex.: inserir uma lista de datas em ordem cronológica, ou de IDs sequenciais)
são um padrão de entrada comum na prática, e é exatamente esse padrão que degenera a BST.

## 7. Exercícios de fixação

1. Insira `10, 20, 30, 40, 50` (em ordem) numa BST vazia. Qual a altura da árvore
   resultante?
2. Insira os mesmos 5 valores na ordem `30, 20, 10, 40, 50`. Desenhe e calcule a altura.
   Comparando com a questão 1, o que mudou?
3. Por que "para grandes volumes de dados, árvores binárias de busca não são a alternativa
   mais eficiente" (frase do slide, pág. 18)? O que exatamente está em risco?

### Gabarito

1. Cada valor é maior que o anterior → vira uma fila só para a direita: `10→20→30→40→50`.
   Altura = 4 (5 nós, cada um só com filho direito, exceto o último).
2. `30` raiz. `20<30`→esq. `10<30`→esq(`20`); `10<20`→esq. `40>30`→dir. `50>30`→dir(`40`);
   `50>40`→dir.
   ```
        30
       /  \
      20    40
     /        \
    10         50
   ```
   Altura = 2 — bem menor que a questão 1, com os **mesmos 5 valores**. A diferença é só a
   ordem de inserção.
3. Porque não há **garantia** de que os dados cheguem numa ordem que produza árvore
   balanceada — na pior das hipóteses (dados já ordenados, comuns na prática), a busca
   degrada para O(n), perdendo toda a vantagem de usar árvore em vez de, por exemplo, um
   array ordenado com busca binária. É exatamente essa fragilidade que motiva estruturas
   **auto-balanceadas** como a AVL (1.3) — que garantem altura O(log n) **sempre**,
   independente da ordem de inserção.

## Resumo

- Custo de busca/inserção/remoção em BST é O(altura), não O(log n) garantido.
- Melhor caso (árvore completa): altura O(log n). Pior caso (inserção em ordem): altura
  O(n) — a árvore vira uma lista encadeada disfarçada.
- A forma da árvore depende só da ordem de inserção — não há nada na definição de BST que
  evite o pior caso.

---

Isso fecha a teoria de 1.2. Próximo: [[../../1.3 Árvores AVL/Teoria - passo a passo/README|1.3 Árvores AVL]] — a estrutura que resolve exatamente este problema.
