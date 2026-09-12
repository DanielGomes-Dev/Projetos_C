# Teoria 04 — Merge e redistribuição: como a árvore B remove sem violar suas regras

> **Onde isto entra:** é o espelho da Teoria 03 — lá, inserção podia fazer um nó "estourar
> por cima" (overflow); aqui, remoção pode fazer um nó "estourar por baixo" (underflow,
> menos chaves que o mínimo).
> **Antes:** [[Teoria 03 - Split na inserção]].
> **Fonte:** SZ (livro-base) · CO (Cormen, cap. Árvores B — pseudocódigo B-TREE-DELETE;
> conferir página exata).

## 1. A ideia em uma frase

Depois de remover uma chave, se um nó ficar com **menos** que o mínimo de chaves permitido
(Teoria 02), a árvore B conserta isso de duas formas possíveis: **pedindo emprestado** a um
irmão que tem sobra, ou **fundindo** com um irmão quando ninguém tem sobra.

## 2. De onde vem a necessidade

Remover uma chave de um nó folha é simples — só tirar. O problema é que isso pode deixar o
nó com menos chaves que o mínimo exigido (`⌈m/2⌉ − 1`), violando a Teoria 02. A árvore
precisa de um jeito de "reabastecer" esse nó sem quebrar nenhuma outra regra — em especial,
sem quebrar "todas as folhas na mesma profundidade".

## 3. Remover de nó interno (antes de underflow): substituir por predecessor/sucessor

Se a chave a remover está num nó **interno** (não folha), ela não pode simplesmente
desaparecer (sobraria um "buraco" entre dois ponteiros de filho). A solução, igual à BST
(1.2): substituir pelo **predecessor** (maior chave da subárvore à esquerda) ou **sucessor**
(menor chave da subárvore à direita), e então remover essa chave substituta de onde ela
realmente estava (numa folha, recaindo no caso da seção 4).

## 4. As duas estratégias quando um nó fica com poucas chaves (underflow)

Suponha `m = 3` (mínimo 1 chave por nó não-raiz) e este trecho de árvore, onde o nó `[8]`
acabou de perder sua única chave (underflow: 0 chaves, precisa de pelo menos 1):

```
              [10]
             /      \
          [ ]       [15]
         (underflow)
```

> 📖 **Estratégia 1 — Redistribuição (empréstimo):** se um irmão adjacente tem chaves
> **sobrando** (mais que o mínimo), empresta uma, passando pelo pai.

Neste exemplo, o irmão `[15]` só tem 1 chave (o mínimo) — **não tem sobra**, não dá pra
redistribuir. Vamos para a estratégia 2.

> 📖 **Estratégia 2 — Merge (fusão):** funde o nó vazio com um irmão **e** a chave
> separadora do pai que ficava entre eles.

```
Antes:            [10]                    Depois do merge:
                 /      \                        [10, 15]
              [ ]       [15]        →      (um único nó, agora raiz)
```

O nó vazio, o irmão `[15]` e a chave do pai (`10`) se fundem num único nó `[10, 15]`. Como
o pai perdeu sua única chave nesse processo, e o pai era a raiz, **a árvore perde um nível**
(a fusão é o processo inverso do split — em vez de crescer, a árvore encolhe).

### Um exemplo onde a redistribuição funciona

```
              [10]
             /      \
          [ ]      [15, 20]
         (underflow, mín=1)
```

Aqui o irmão `[15, 20]` **tem sobra** (2 chaves, mínimo é 1). Redistribuição: a menor chave
do irmão (`15`) sobe para o lugar do separador no pai, e o separador antigo do pai (`10`)
desce para preencher o nó vazio:

```
              [15]
             /      \
          [10]      [20]
```

**Conferindo:** `[10]` e `[20]` agora têm 1 chave cada (mínimo satisfeito), e a árvore
continua com 2 níveis — **não precisou encolher**, porque havia sobra para emprestar.

## 5. Por que a ordem de preferência importa (redistribuir antes de fundir)

> **Redistribuição é preferida sobre merge sempre que possível**, porque redistribuição
> **não muda a altura** da árvore (mais barato), enquanto merge pode propagar underflow
> para cima (o pai perde uma chave ao doá-la na fusão) e, no pior caso, encolher a árvore
> inteira em um nível — análogo ao split, mas na direção oposta.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| substituir por predecessor/sucessor (nó interno) | transformo "remover do meio" em "remover de uma folha", onde é seguro simplesmente tirar |
| checar se o irmão tem sobra antes de fundir | escolho a operação **mais barata** que resolve o underflow sem afetar mais nada acima |
| fundir com a chave do pai | reverto o que o split fez — devolvo ao nível de baixo uma chave que só existia como separador |
| árvore perde um nível quando o merge alcança a raiz | é o único jeito da árvore B encolher, espelhando o único jeito dela crescer (Teoria 03) |

## 7. Exercícios de fixação

1. Por que remover uma chave de um nó **folha** nunca precisa de predecessor/sucessor?
2. Numa árvore com `m = 3`, um nó tem 1 chave (o mínimo) e um irmão adjacente também tem
   exatamente 1 chave. Ao remover a única chave de um deles, qual estratégia é usada:
   redistribuição ou merge? Por quê?
3. Complete: "o merge é o processo inverso do ___, assim como redistribuição não muda a
   ___ da árvore."

### Gabarito

1. Porque a chave já está no "fim da linha" — não há subárvore abaixo dela para ficar com
   um buraco. Só as chaves de nós **internos** precisam de substituto, porque removê-las
   deixaria um ponteiro de filho "órfão" no meio da estrutura.
2. Merge — porque o irmão com 1 chave (o mínimo) **não tem sobra** para emprestar sem ele
   mesmo cair abaixo do mínimo. Sem sobra em nenhum irmão, a única opção é fundir.
3. "...split, assim como redistribuição não muda a **altura** da árvore."

## Resumo

- Remover de nó interno: substitui por predecessor/sucessor, empurrando o problema para uma
  folha.
- Underflow numa folha (ou nó interno após substituição): tenta **redistribuir** primeiro
  (pega emprestado de irmão com sobra, via o pai) — mais barato, não muda altura.
- Sem sobra em nenhum irmão: **funde** (merge) o nó com um irmão e a chave separadora do
  pai — pode propagar underflow para cima e, no limite, encolher a árvore em um nível.

---

Isso fecha a teoria de 5.1. Próximo: [[../../5.2 Árvores B+/README|5.2 Árvores B+]].
