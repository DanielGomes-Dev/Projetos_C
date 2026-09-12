# Teoria 03 — Split: como a árvore B insere sem violar suas regras

> **Onde isto entra:** inserir uma chave pode fazer um nó "estourar" o limite de `m − 1`
> chaves (Teoria 02) — split é o mecanismo que conserta isso sem quebrar a propriedade de
> "todas as folhas na mesma profundidade".
> **Antes:** [[Teoria 02 - Ordem m e propriedades da árvore B]].
> **Fonte:** SZ (livro-base) · CO (Cormen, cap. Árvores B — pseudocódigo B-TREE-SPLIT-CHILD
> e B-TREE-INSERT; conferir página exata).

## 1. A ideia em uma frase

Inserir sempre acontece numa **folha**; se a folha ficar com chaves demais, ela é **dividida
em duas**, e a chave do meio "sobe" para o nó pai — repetindo esse processo para cima, se
necessário, até uma nova raiz nascer (se preciso).

## 2. De onde vem a necessidade

Se você simplesmente colocasse a nova chave na folha certa sem mais nada, um nó poderia
acabar com mais de `m − 1` chaves — violando a Teoria 02. Split é a "válvula de escape":
em vez de deixar o nó estourado, ele é dividido ao meio, e a chave do meio some do nível
atual e reaparece **um nível acima**, como separador entre as duas metades.

## 3. O procedimento — lido devagar, com `m = 3`

Com `m = 3`: máximo 2 chaves por nó (`m − 1 = 2`). Inserindo `10`, depois `20`, depois `5`
num nó folha único (que também é a raiz, inicialmente):

```
insere 10 → [10]
insere 20 → [10, 20]                (2 chaves = m−1, no limite, mas ainda válido)
insere 5  → [5, 10, 20]             (3 chaves > m−1=2 → OVERFLOW)
```

> 📖 **Lendo o split que resolve o overflow:**
> 1. **Identifica a chave do meio** das 3: ordenadas, `5, 10, 20` — o meio é `10`.
> 2. **A chave do meio (`10`) sobe** para um nó pai novo (que, como não havia pai, também
>    vira a nova raiz da árvore).
> 3. **As chaves restantes se dividem**: as menores que `10` (`5`) formam o nó da esquerda;
>    as maiores (`20`) formam o nó da direita.

Resultado:

```
              [10]
             /      \
          [5]      [20]
```

**Conferindo:** a árvore agora tem 2 níveis. `[10]` (raiz) tem 1 chave, 2 filhos — dentro
das regras (raiz só precisa de 2 filhos, não do mínimo geral). `[5]` e `[20]` têm 1 chave
cada, ambas no nível 1 — **mesma profundidade**, propriedade central preservada. ✔

## 4. E se o split precisar propagar?

Se a árvore já tivesse um pai antes do split, a chave `10` seria inserida **nesse pai**
existente (não criaria uma raiz nova) — e se esse pai **também** estourasse com a chegada de
`10`, o mesmo procedimento de split se repetiria nele, propagando mais um nível acima.

> **Regra-chave:** uma nova raiz só é criada quando o split alcança o **topo** da árvore
> (o nó que estourou não tinha pai). É o **único** mecanismo pelo qual uma árvore B ganha
> altura — e é exatamente por isso que a árvore cresce "por igual" em todos os ramos,
> mantendo todas as folhas na mesma profundidade (Teoria 02).

## 5. O código — lido pedaço por pedaço

```c
#define M 3

typedef struct no_b {
  int chaves[M - 1];
  struct no_b *filhos[M];
  int n_chaves;
  int folha;
} NoB;

int divide_no(NoB *no, NoB **nova_direita) {
  int meio = (M - 1) / 2;                 // índice da chave do meio
  int chave_promovida = no->chaves[meio];

  NoB *direita = malloc(sizeof(NoB));
  direita->folha = no->folha;
  direita->n_chaves = 0;

  for (int i = meio + 1; i < no->n_chaves; i++)
    direita->chaves[direita->n_chaves++] = no->chaves[i];

  if (!no->folha)
    for (int i = meio + 1; i <= no->n_chaves; i++)
      direita->filhos[i - (meio + 1)] = no->filhos[i];

  no->n_chaves = meio;
  *nova_direita = direita;
  return chave_promovida;
}
```

> 📖 **Lendo `divide_no` devagar:**
> 1. `meio = (M - 1) / 2` — com `M = 3`, `meio = 1` (índice 1, contando de 0): a chave do
>    meio de `[chaves[0], chaves[1]]` estourado (3 chaves temporariamente) é `chaves[1]`.
> 2. `chave_promovida = no->chaves[meio]` — guarda essa chave para devolver a quem chamou
>    (que vai inserir `chave_promovida` no nó pai).
> 3. o laço `for (i = meio+1; ...)` copia as chaves **à direita** do meio para um novo nó
>    (`direita`) — essas viram a metade direita.
> 4. `if (!no->folha) { ... }` — se o nó dividido **não** é folha, os ponteiros de filho
>    também precisam ser divididos (senão o novo nó direito ficaria sem seus próprios
>    filhos).
> 5. `no->n_chaves = meio` — o nó original agora só guarda a metade esquerda (`meio`
>    chaves).
> 6. `return chave_promovida` — quem chamou esta função é responsável por inserir essa
>    chave no nó pai (ou criar uma nova raiz, se este nó não tinha pai).

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| achar a chave do meio | escolho o "ponto de corte justo" que deixa as duas metades com o mesmo tamanho (ou quase) |
| a chave do meio sobe para o pai | transformo uma chave que estava "no meio de um nó cheio demais" num **separador** entre duas subárvores agora menores |
| propagar o split para cima quando o pai também estoura | garanto que o ajuste nunca deixa a árvore "desbalanceada por baixo" — o crescimento acontece sempre no topo |

## 7. Exercícios de fixação

1. Com `m = 3`, insira `1, 2, 3, 4` (nessa ordem) num nó folha único e trace cada split.
2. No passo 3 da seção 3, por que a chave promovida (`10`) não aparece **duplicada** em
   nenhum lugar da árvore resultante (diferente do que acontece em árvore B+, ver 5.2)?
3. Por que dividir sempre pela chave do **meio** (e não pela primeira ou última)?

### Gabarito

1. Insere `1`: `[1]`. Insere `2`: `[1,2]`. Insere `3`: `[1,2,3]` → overflow (3 > m−1=2).
   Split: meio = `2`. Sobe `2` para nova raiz; `[1]` e `[3]` viram folhas:
   ```
         [2]
        /    \
      [1]    [3]
   ```
   Insere `4`: vai para a folha `[3]` (maior que 2): `[3,4]` — 2 chaves, dentro do limite
   (`m−1=2`), **sem overflow**. Árvore final:
   ```
         [2]
        /    \
      [1]    [3,4]
   ```
2. Porque em árvore B (diferente de B+), cada chave existe em **exatamente um** lugar da
   árvore — quando `10` sobe, ela **deixa de existir** no nó original (só sobra como
   separador no pai). Em B+, os dados ficam só nas folhas e a chave promovida é uma
   **cópia** (o dado original continua na folha) — ver 5.2, seção 1.
3. Porque dividir pelo meio mantém as duas metades resultantes o mais próximas possível em
   tamanho — evita criar um nó quase vazio de um lado (o que violaria o mínimo de chaves da
   Teoria 02 mais cedo, exigindo split de novo logo em seguida).

## Resumo

- Inserção sempre entra numa folha; se ela estourar (`> m−1` chaves), faz-se **split**: a
  chave do meio sobe, o resto se divide em dois nós.
- Split pode propagar para cima; só cria uma nova raiz quando alcança o topo — é o único
  jeito da árvore B crescer em altura, mantendo todas as folhas na mesma profundidade.
- No código, `divide_no` faz a divisão e devolve a chave promovida; quem chama decide onde
  inserir essa chave (pai existente ou nova raiz).

**Próximo:** [[Teoria 04 - Merge e redistribuição na remoção]].
