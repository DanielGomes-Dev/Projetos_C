# Teoria 04 — Encadeamento separado (listas ligadas nos buckets)

> **Onde isto entra:** terceira estratégia de tratamento de colisão, e a mais usada na
> prática — resolve o problema de "tabela cheia" que endereçamento aberto (Teorias 02–03)
> sempre tem no limite.
> **Antes:** [[Teoria 03 - Dispersão dupla (double hashing)]].
> **Fonte:** CE (Celes), Cap. 18 "Tabelas de dispersão", pág. 278–279.

## 1. A ideia em uma frase

Em vez de forçar cada chave a caber **numa posição só** do vetor, cada posição vira a
cabeça de uma **lista ligada** — todas as chaves que colidem naquele índice moram na mesma
lista, sem limite de quantas.

## 2. Por que essa estratégia (motivação)

Nos dois métodos anteriores (Teorias 02–03), toda chave precisa ocupar uma posição própria
do vetor — no limite, a tabela pode **encher completamente**, e nenhuma inserção nova cabe.
Com listas ligadas, uma posição do vetor nunca "enche": ela só cresce (a lista fica maior).
O preço é que cada posição deixa de ser O(1) garantido — vira "percorrer uma lista", que na
prática costuma ser curta se a função hash espalhar bem as chaves.

## 3. O struct — lido pedaço por pedaço

```c
struct aluno {
  int mat;
  char nome[81];
  char turma;
  char email[41];
  struct aluno *prox;   /* encadeamento na lista de colisão */
};
typedef struct aluno Aluno;
```

> 📖 **Lendo devagar:** o único campo novo em relação ao struct das Teorias 01–03 é
> `struct aluno *prox` — um ponteiro **para outro aluno**. Cada posição do vetor
> (`tab[h]`) agora é o **primeiro elemento de uma lista**; `prox` encadeia os demais que
> colidiram naquele mesmo índice.

## 4. Busca — lida devagar

```c
Aluno *hsh_busca(Hash tab, int mat) {
  int h = hash(mat);
  Aluno *a = tab[h];
  while (a != NULL) {
    if (a->mat == mat)
      return a;
    a = a->prox;
  }
  return NULL;
}
```

> 📖 **Comparando com a busca de endereçamento aberto (Teoria 02):** a estrutura do código
> é quase idêntica — a diferença é que, em vez de `h = (h+1) % N` (mudar de **posição** do
> vetor), aqui é `a = a->prox` (mudar de **nó da lista**, sem sair da posição `h`). A busca
> nunca sai da lista que começa em `tab[h]`.

## 5. Inserção — lida devagar

```c
Aluno *hsh_insere(Hash tab, int mat, char *n, char *e, char t) {
  int h = hash(mat);
  Aluno *a = tab[h];
  while (a != NULL) {
    if (a->mat == mat)
      break;
    a = a->prox;
  }
  if (a == NULL) {                       /* não encontrou o elemento */
    a = (Aluno *) malloc(sizeof(Aluno));
    a->mat = mat;
    a->prox = tab[h];                    /* insere no INÍCIO da lista */
    tab[h] = a;
  }
  strcpy(a->nome, n);
  strcpy(a->email, e);
  a->turma = t;
  return a;
}
```

> 📖 **Lendo devagar:**
> 1. Primeiro, percorre a lista de `tab[h]` procurando se `mat` já existe (igual à busca).
> 2. Se `a == NULL` no fim do laço, a chave **não existia** — aloca um nó novo e o insere
>    **no início** da lista (`a->prox = tab[h]; tab[h] = a;` — o clássico "empilhar" numa
>    lista ligada, O(1), sem precisar percorrer até o fim).
> 3. Se a chave **já existia**, o laço parou nela (via `break`) — `a` aponta pro nó
>    existente, e as linhas finais (`strcpy`, `a->turma = t`) **atualizam** os dados em vez
>    de criar duplicata.

## 6. Conferindo com números concretos (mesma tabela das Teorias 02–03)

`N = 7`, `hash(k) = k % 7`, inserindo `10, 3, 17, 5, 24, 12, 21` (mesmos valores).

| Chave | `hash(k)` |
|---|---|
| 10, 3, 17, 24 | 3 |
| 5, 12 | 5 |
| 21 | 0 |

Inserindo **no início** de cada lista, na ordem dada:

```
0: 21
3: 24 → 17 → 3 → 10      (24 foi inserido por último dos 4, então fica na frente)
5: 12 → 5
1,2,4,6: (vazio)
```

**Comparando com endereçamento aberto (Teoria 02) para os mesmos dados:** lá, o cluster
"vazou" e acabou ocupando quase a tabela toda (posições 0,1,2,3,4,5,6 — 7 de 7). Aqui, só
3 posições têm algo (`0`, `3`, `5`) — as demais continuam livres, disponíveis para chaves
futuras sem nenhum efeito de clustering entre índices diferentes.

**Custo de buscar `10`:** percorre a lista da posição 3 até o fim — 4 comparações
(`24, 17, 3, 10`). Mas note que essa lista poderia crescer **além** dos 7 elementos da
tabela inteira, sem nunca "travar" por falta de espaço — diferente de endereçamento aberto.

## 7. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `tab[h]` ser cabeça de lista, não um único slot | troco "tabela pode encher" por "tabela nunca enche, só listas individuais crescem" |
| inserir sempre no início da lista | evito percorrer a lista inteira **na inserção** (só é preciso percorrer inteira quando a chave já existe, pra achar e atualizar) |
| `a->prox = a->prox` em vez de `h = (h+1)%N` | a "trilha de colisão" agora é uma lista explícita, não um padrão de sondagem sobre o vetor |

## 8. Letra miúda

**O vetor `tab` continua tendo tamanho fixo `N`** — o que cresce sem limite são as listas
dentro de cada posição, não o número de posições. Se a função hash for ruim (muitas chaves
caindo nas mesmas posições), algumas listas ficam muito longas enquanto outras posições
seguem vazias — o problema de "espalhar mal" (Teoria 01) continua existindo, só que agora
se manifesta como "listas desbalanceadas" em vez de "vetor cheio".

## 9. Exercícios de fixação

1. Com a tabela final da seção 6, quantas comparações `hsh_busca` faz para achar `24`?
   E para concluir que `18` (que mapearia pra posição 3) **não** está na tabela?
2. Por que inserir no início da lista é O(1), enquanto inserir no fim exigiria percorrer a
   lista inteira primeiro?
3. Uma tabela com `N = 1` (uma posição só) e encadeamento separado ainda "funciona"
   (não trava, não perde dados)? O que ela vira, na prática?

### Gabarito

1. `24` está na frente da lista (inserido por último) → **1 comparação**. Para `18`
   (posição 3): percorre `24, 17, 3, 10` (4 comparações, todas diferentes de 18) e chega no
   final da lista (`prox == NULL`) → retorna `NULL` depois de **4 comparações**.
2. Inserir no início só exige apontar o novo nó para o que já era a cabeça (`a->prox =
   tab[h]`) e atualizar a cabeça (`tab[h] = a`) — 2 atribuições, sem percorrer nada. Inserir
   no fim exigiria andar até o último nó (`prox == NULL`) antes de poder ligá-lo, custando
   O(tamanho da lista).
3. Sim, ainda funciona corretamente — mas vira, na prática, **uma lista ligada única**
   (todo elemento cai na mesma posição 0), perdendo toda vantagem de O(1) médio da tabela
   hash: toda busca vira O(n), percorrendo todos os elementos. É o caso extremo de "função
   hash que não espalha nada".

## Resumo

- Encadeamento separado: cada posição do vetor é a cabeça de uma lista ligada; colisões
  viram nós na mesma lista, sem limite de tamanho.
- A tabela nunca "enche" — só as listas individuais crescem, o que é a principal vantagem
  sobre endereçamento aberto.
- Inserção no início da lista é O(1); busca/atualização precisam percorrer a lista da
  posição correspondente, cujo tamanho médio depende de quão bem a função hash espalha as
  chaves.

**Próximo:** [[Teoria 05 - Fator de carga e rehashing]].
