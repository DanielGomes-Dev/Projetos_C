# Teoria 02 — Ordem *m* e as propriedades de uma árvore B

> **Onde isto entra:** antes de inserir ou remover qualquer coisa, é preciso saber exatamente
> o que uma árvore B **é** — as regras que ela nunca pode violar.
> **Antes:** [[Teoria 01 - Por que não usar AVL em disco]].
> **Fonte:** SZ (livro-base) · CO (Cormen, cap. Árvores B — conferir página exata).

## 1. A ideia em uma frase

Uma árvore B de ordem `m` é uma árvore onde cada nó pode ter **até `m` filhos** (e portanto
até `m − 1` chaves), mas nunca menos que a metade disso — e todas as folhas ficam sempre na
**mesma profundidade**.

## 2. Por que "ordem m" e não "número fixo de filhos"

Diferente de árvore binária (sempre 2 filhos possíveis), aqui `m` é um parâmetro que você
escolhe ao projetar o sistema — tipicamente escolhido para que **um nó inteiro caiba
exatamente num bloco de disco** (ex.: se um bloco tem 4KB e cada chave+ponteiro ocupa um
certo número de bytes, `m` é calculado para preencher o bloco). Um `m` maior = nós mais
"gordos" = árvore mais rasa (Teoria 01).

## 3. As regras — lidas devagar, uma de cada vez

> 📖 **Lendo cada propriedade:**
>
> 1. **Todo nó tem no máximo `m` filhos e no máximo `m − 1` chaves.** Note o "menos 1": se
>    um nó tem `k` chaves, ele tem `k + 1` "espaços entre/ao redor das chaves" para
>    ponteiros de filho — por isso o número de filhos é sempre uma unidade a mais que o
>    número de chaves.
> 2. **Todo nó (exceto a raiz) tem no mínimo `⌈m/2⌉` filhos e `⌈m/2⌉ − 1` chaves.** O
>    símbolo `⌈ ⌉` (teto) significa "arredonde para cima". Essa regra garante que nenhum nó
>    fica "quase vazio" — todo nó (menos a raiz) está pelo menos "meio cheio". É essa regra
>    que evita desperdiçar altura com nós subutilizados.
> 3. **A raiz tem no mínimo 2 filhos** (se não for folha) — mesmo que a regra 2 permitisse
>    menos, a raiz é a única exceção que pode ter só 1 chave (2 filhos).
> 4. **Todas as folhas estão na mesma profundidade.** Esta é a propriedade **central**: é
>    ela que garante altura previsível e balanceada. Ela só é possível porque a árvore B
>    cresce de um jeito específico — de baixo para cima, ver Teoria 03.
> 5. **As chaves dentro de um nó ficam ordenadas** e funcionam como separadores: o
>    ponteiro de filho **entre** duas chaves aponta para a subárvore com valores **entre**
>    essas duas chaves.

## 4. Conferindo com um exemplo concreto (m = 3)

Com `m = 3`: cada nó tem no máximo 3 filhos → no máximo 2 chaves. Mínimo (exceto raiz):
`⌈3/2⌉ = 2` filhos → 1 chave.

```
                [10 | 20]
               /     |    \
           [5]    [15]   [25, 30]
```

**Conferindo as regras:**
- Nó raiz `[10|20]`: 2 chaves, 3 filhos. Regra 1: `2 ≤ m−1=2` ✔, `3 ≤ m=3` ✔.
- Nó `[5]`: 1 chave, 0 filhos (é folha). Regra 2 (mínimo, não-raiz): `⌈3/2⌉−1 = 1` chave —
  tem exatamente o mínimo ✔.
- Nó `[25,30]`: 2 chaves — dentro do máximo (2) ✔, acima do mínimo (1) ✔.
- Todas as folhas (`[5]`, `[15]`, `[25,30]`) estão no mesmo nível (nível 1) ✔ — propriedade
  central satisfeita.
- Navegação: para achar `22`, comparo com a raiz `[10|20]`: `22 > 20`, sigo o ponteiro **à
  direita de 20** → chego em `[25,30]`. `22 < 25`, não está lá — a busca termina "não
  encontrado" (mas note que passou pelo nó certo: `10 < 22 < ... ` a navegação por
  separadores funcionou).

## 5. Letra miúda

**"m ≥ 3"?** Com `m = 2`, cada nó teria no máximo 1 chave — isso degenera numa estrutura
parecida com lista encadeada (perde toda vantagem de "nó gordo"). Na prática, os exemplos
do curso usam `m` pequeno (3, 4, 5) só para caber no papel/quadro — **pode assumir `m ≥ 3`**
sempre que o exercício não disser o contrário.

## 6. 📌 O que você está REALMENTE fazendo ao verificar se uma árvore é uma árvore B válida

| O passo mecânico | O que ele realmente é |
|---|---|
| contar chaves/filhos de cada nó e comparar com `m−1`/`m` | verifico que nenhum nó "estourou" o espaço de um bloco de disco |
| contar o mínimo em nós não-raiz | verifico que nenhum nó está desperdiçando espaço de bloco (menos da metade cheio) |
| medir a profundidade de cada folha | verifico a garantia central de balanceamento — sem isso, não é uma árvore B |

## 7. Exercícios de fixação

1. Para `m = 5`: qual o número máximo de chaves por nó? E o mínimo (não-raiz)?
2. Um nó não-raiz de uma árvore B com `m = 4` tem 1 chave. Isso viola alguma regra?
3. Nesta árvore (`m = 3`), todas as folhas estão na mesma profundidade?
   ```
              [10]
             /      \
          [5]      [15|20]
                    /  |   \
                 [12] [17] [25]
   ```

### Gabarito

1. Máximo: `m − 1 = 4` chaves. Mínimo (não-raiz): `⌈5/2⌉ − 1 = 3 − 1 = 2` chaves.
2. Sim — para `m = 4`, o mínimo de chaves num nó não-raiz é `⌈4/2⌉ − 1 = 2 − 1 = 1`... na
   verdade **não viola**: `⌈4/2⌉ = 2` filhos mínimo, ou seja `1` chave mínimo. Um nó com
   exatamente 1 chave está no limite mínimo, permitido.
3. Não. A folha `[5]` está no nível 1 (filha direta da raiz), enquanto `[12]`, `[17]`,
   `[25]` estão no nível 2 (netas da raiz, via `[15|20]`). Profundidades diferentes — **essa
   árvore viola a propriedade central e não é uma árvore B válida** (provavelmente
   resultado de uma inserção/remoção mal feita).

## Resumo

- Ordem `m`: até `m` filhos / `m − 1` chaves por nó; mínimo `⌈m/2⌉` filhos / `⌈m/2⌉ − 1`
  chaves (exceto raiz, que só precisa de 2 filhos se não for folha).
- Chaves dentro do nó são separadores ordenados, guiando a navegação entre filhos.
- **Todas as folhas na mesma profundidade** é a propriedade central — é o que garante altura
  balanceada, e é mantida ativamente por split (inserção, Teoria 03) e merge/redistribuição
  (remoção, Teoria 04).

**Próximo:** [[Teoria 03 - Split na inserção]].
