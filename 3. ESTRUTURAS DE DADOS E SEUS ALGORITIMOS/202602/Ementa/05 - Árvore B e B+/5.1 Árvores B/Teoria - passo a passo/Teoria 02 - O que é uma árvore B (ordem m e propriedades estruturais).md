# Teoria 02 — O que é uma árvore B, exatamente? (ordem *m* e propriedades estruturais)

> **Onde isto entra:** aqui está a definição formal que toda a árvore B precisa respeitar
> **o tempo todo** — antes e depois de qualquer inserção/remoção. Split (Teoria 04) e
> merge/redistribuição (Teoria 05) só existem para **manter** essas propriedades verdadeiras.
> **Antes:** [[Teoria 01 - Por que não usar AVL BST em disco (motivação)]].
> **Fonte:** SZ, capítulo/seção "Árvores B" (propriedades estruturais) e CO, cap. 18
> (definição formal de árvore B, com o parâmetro chamado de "grau mínimo `t`" em vez de
> ordem `m` — ver "letra miúda" abaixo sobre essa diferença de convenção). Página exata não
> verificada nesta sessão (ver aviso na Teoria 01).

## 1. A ideia em uma frase

Uma árvore B de ordem `m` é uma árvore onde **cada nó pode guardar várias chaves ordenadas
e ter até `m` filhos** (não só 2), com uma regra rígida de "nem muito cheio, nem muito
vazio" que garante que **todas as folhas fiquem sempre na mesma profundidade**.

## 2. De onde vem / por que a definição é assim

A Teoria 01 motivou "eu quero nós gordos, com muitos filhos, para achatar a árvore". Mas só
dizer "cada nó pode ter até `m` filhos" não é suficiente — se um algoritmo de inserção
simplesmente fosse enfiando chaves em qualquer nó sem regra nenhuma, a árvore ia ficar
torta: alguns galhos cheios de filhos, outros quase vazios, algumas folhas muito fundo e
outras rasas — perdendo exatamente a vantagem de altura pequena e previsível que motivou a
estrutura. A árvore B soluciona isso com duas regras companheiras: um **teto** (quantas
chaves/filhos um nó pode ter, no máximo) e um **piso** (quantas ele é **obrigado** a ter, no
mínimo) — e a combinação dessas duas regras é o que força todas as folhas a ficarem na
mesma profundidade.

## 3. A definição — lida pedaço por pedaço

> 📖 **Lendo devagar — "árvore B de ordem `m`":**
>
> 1. **`m`** é só um número que você escolhe ao definir a árvore (no papel deste curso,
>    normalmente 3, 4 ou 5; em disco de verdade, dezenas ou centenas — Teoria 01).
> 2. **"Ordem `m`"** quer dizer: **`m` é o número máximo de filhos que um nó pode ter** —
>    não é o número de chaves. Esse é o erro mais comum: ordem = filhos, não chaves.
> 3. Se um nó tem no máximo `m` filhos, e as chaves de um nó funcionam como "separadores"
>    entre esses filhos, então o número máximo de chaves é **um a menos que o número de
>    filhos**: `m − 1`.

As propriedades completas, cada uma com o que ela **impede**:

| # | Propriedade | O que ela impede |
|---|---|---|
| 1 | Todo nó tem **no máximo `m` filhos** e **no máximo `m−1` chaves** | Um nó "gordo demais", que não caberia num bloco de disco |
| 2 | Todo nó, **exceto a raiz**, tem **no mínimo ⌈m/2⌉ filhos** e **⌈m/2⌉ − 1 chaves** | Um nó "murcho", quase vazio, que desperdiçaria espaço e faria a árvore crescer em altura à toa |
| 3 | A **raiz** tem no mínimo **2 filhos** (se não for folha) | Só existe uma exceção ao mínimo geral: a raiz pode ter só 2 filhos mesmo que ⌈m/2⌉ seja maior, porque não há "vizinho" da raiz para redistribuir |
| 4 | **Todas as folhas estão na mesma profundidade** | Este é o "prêmio" das regras acima — nunca existe uma folha mais funda que outra |
| 5 | As chaves dentro de cada nó ficam **ordenadas** | Sem ordem, não dá pra decidir "qual filho seguir" numa busca |

> 📖 **Lendo devagar — `⌈m/2⌉`:**
>
> 1. `⌈ ⌉` é o **teto** (arredonda **para cima**) — diferente de `⌊ ⌋` (piso, arredonda
>    para baixo), que você talvez já tenha visto em outro contexto.
> 2. `⌈m/2⌉` — "metade de `m`, arredondada para cima". Para `m=3`: `3/2 = 1,5` → `⌈1,5⌉ = 2`.
>    Para `m=4`: `4/2 = 2` (já é inteiro) → `⌈2⌉ = 2`.
> 3. O mínimo de **chaves** é esse valor **menos 1**: `⌈m/2⌉ − 1`. Para `m=3`: `2 − 1 = 1`.

## 4. Conferindo com uma árvore concreta (ordem m=3)

Esta é a árvore que a Teoria 04 vai construir passo a passo, a partir de um nó só, inserindo
chaves uma a uma. Por ora, vamos só **conferir que ela obedece todas as 5 propriedades**:

```
                         [30]
                        /     \
                    [10]       [50]
                   /    \      /    \
                [5]   [20]  [40]  [60]
```

Para `m=3`: máximo de chaves por nó = `m−1 = 2`; mínimo de chaves por nó não-raiz =
`⌈3/2⌉ − 1 = 2 − 1 = 1`; mínimo de filhos por nó interno não-raiz = `⌈3/2⌉ = 2`.

- **Propriedade 1 (teto):** todo nó tem no máximo 2 chaves — `[30]` tem 1, `[10]` tem 1,
  `[50]` tem 1, e as 4 folhas têm 1 cada. Nenhum tem mais que 2. ✔
- **Propriedade 2 (piso, não-raiz):** `[10]` e `[50]` (nós internos, não-raiz) têm 1
  chave cada — bate com o mínimo (1). As 4 folhas têm 1 chave cada — também bate (mínimo
  1, e não há mínimo de filhos para folha, já que folha não tem filho). ✔
- **Propriedade 3 (raiz):** a raiz `[30]` tem 2 filhos (`[10]` e `[50]`) — satisfaz "no
  mínimo 2". ✔
- **Propriedade 4 (folhas na mesma profundidade):** `[5]`, `[20]`, `[40]`, `[60]` estão
  todas no mesmo nível (2 ligações abaixo da raiz: `raiz → [10] ou [50] → folha`). ✔
- **Propriedade 5 (ordem):** dentro de cada nó só há 1 chave, então "ordenado" é trivial
  aqui — mas repare que a estrutura como um todo também está ordenada: tudo à esquerda de
  `[10]` (aqui, `[5]`) é menor que 10; tudo entre 10 e 30 (aqui, `[20]`) fica entre os dois;
  e assim por diante — exatamente como numa BST, só que com "múltiplos filhos por
  separador" em vez de só esquerda/direita. ✔

## 5. Letra miúda

**E aquele "⌈m/2⌉" ser diferente para `m` par e ímpar?** É aritmética simples, mas vale
conferir os dois casos porque é fácil errar em prova: para `m` **ímpar** (ex.: `m=5`),
`⌈5/2⌉ = ⌈2,5⌉ = 3`. Para `m` **par** (ex.: `m=4`), `⌈4/2⌉ = ⌈2⌉ = 2` (já é inteiro, o teto
não muda nada). Não existe "truque" — é só lembrar de arredondar pra cima quando a divisão
não é exata.

**E por que a raiz é uma exceção ao mínimo?** Porque não existe "nó irmão da raiz" — a
regra de mínimo em nós comuns existe para garantir que sempre dá pra redistribuir/fundir
com um vizinho quando uma remoção esvazia demais um nó (Teoria 05); a raiz não tem vizinho,
então ela só precisa ter pelo menos 2 filhos (o mínimo para ainda ser uma árvore de verdade
e não degenerar em um único caminho).

**E essa "grau mínimo `t`" que aparece no Cormen?** O CO define a árvore B usando um
parâmetro `t` ("grau mínimo") em vez de `m`: em CO, cada nó tem entre `t` e `2t` filhos
(exceto a raiz), e entre `t−1` e `2t−1` chaves. Isso é **a mesma ideia**, só com a
convenção "de dentro pra fora" (`t` é o mínimo, e o máximo é `2t`) em vez de "de fora pra
dentro" (`m` é o máximo, e o mínimo é `⌈m/2⌉`). Fazendo `m = 2t`, as duas notações batem.
O professor deste curso usa a convenção de ordem `m` (como SZ); ao ler CO, é só lembrar
dessa troca de variável.

## 6. Exercícios de fixação

1. Para `m = 5`: qual o número máximo de chaves por nó? E o mínimo, para um nó não-raiz?
2. Para `m = 4`: mesma pergunta.
3. Um nó com 4 filhos e ordem `m=5` — isso é permitido? E com 6 filhos?
4. Desenhe a árvore da seção 4 mas com uma folha a mais fundo que as outras (invente
   onde) — isso ainda seria uma árvore B válida? Por quê?
5. Traduzindo para `t` (convenção do Cormen): se um livro diz "grau mínimo `t=3`", qual é o
   `m` equivalente?

### Gabarito

1. Máximo de chaves: `m−1 = 4`. Mínimo (não-raiz): `⌈5/2⌉ − 1 = 3 − 1 = 2`.
2. Máximo de chaves: `m−1 = 3`. Mínimo (não-raiz): `⌈4/2⌉ − 1 = 2 − 1 = 1`.
3. Com 4 filhos: permitido (máximo é `m=5` filhos, e o mínimo não-raiz é `⌈5/2⌉=3` — 4
   está dentro do intervalo `[3,5]`). Com 6 filhos: **não permitido** — ultrapassa o
   máximo de `m=5`.
4. Não seria uma árvore B válida — violaria a propriedade 4 ("todas as folhas na mesma
   profundidade"), que é justamente a propriedade que faz a árvore B ser balanceada por
   construção (nunca degenera como uma BST comum pode degenerar).
5. `m = 2t = 2 × 3 = 6`.

## Resumo

- Ordem `m` = número **máximo de filhos** por nó; número máximo de **chaves** é `m − 1`.
- Todo nó, exceto a raiz, tem no mínimo `⌈m/2⌉` filhos e `⌈m/2⌉ − 1` chaves — a raiz só
  precisa de no mínimo 2 filhos.
- A combinação teto + piso é o que garante que **todas as folhas fiquem na mesma
  profundidade** — a propriedade central que torna a árvore B balanceada.
- CO usa a convenção "grau mínimo `t`" (`m = 2t`) em vez de ordem `m` — mesma ideia, outra
  variável.

**Próximo:** [[Teoria 03 - Busca em árvore B (por igualdade)]].
