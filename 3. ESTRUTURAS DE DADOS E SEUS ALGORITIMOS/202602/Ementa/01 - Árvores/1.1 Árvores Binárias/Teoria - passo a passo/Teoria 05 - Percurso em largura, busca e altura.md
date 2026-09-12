# Teoria 05 — Percurso em largura, busca por força bruta, e altura

> **Onde isto entra:** os três percursos da Teoria 04 são todos "em profundidade" (descem
> até o fundo antes de voltar). Aqui vemos o quarto tipo de percurso, que é estruturalmente
> diferente (usa fila em vez de recursão), e mais duas operações que toda árvore binária
> "crua" precisa: buscar um valor e medir a altura.
> **Antes:** [[Teoria 04 - Percursos em profundidade (pré-ordem, em-ordem, pós-ordem)]].
> **Fonte:** `lista01-EDA/05_ArvoresBinarias_caminhamento.pdf`, pág. 7 (slides da Profa.
> Vanessa Braganholo); código idêntico em `ListasExercicios/lista01-EDA/TAB/TAB.c`.

## 1. A ideia em uma frase

Percurso em largura visita a árvore **nível por nível** (todo o nível 0, depois todo o
nível 1, depois todo o nível 2...) — em vez de mergulhar fundo num galho antes de olhar o
outro, como os percursos da Teoria 04 fazem.

## 2. Por que precisa de fila (e não de recursão)

Pré/em/pós-ordem funcionam com recursão porque a pilha de chamadas "lembra" naturalmente
onde voltar depois de esgotar um galho. Percurso em largura precisa de outra coisa: quando
visito um nó, preciso **guardar os filhos dele para visitar depois — só depois que todos os
nós do nível atual já tiverem sido visitados**. Isso é exatamente o que uma **fila** (FIFO —
primeiro que entra, primeiro que sai) garante: quem entrou primeiro (nível mais raso) sai
primeiro.

## 3. O código — lido devagar

```c
void imp_larg_f(TAB *a) {
  if (!a) return;
  TFILA *f = inicializa_f();
  insere_f(f, a);
  while (!vazia_f(f)) {
    TAB *aux = retira_f(f);
    printf("%d ", aux->info);
    if (aux->esq) insere_f(f, aux->esq);
    if (aux->dir) insere_f(f, aux->dir);
  }
  libera_f(f);
}
```

> 📖 **Lendo devagar:**
> 1. `if (!a) return;` — árvore vazia, nada a fazer.
> 2. `insere_f(f, a)` — coloca a **raiz** na fila para começar.
> 3. `while (!vazia_f(f))` — repete enquanto houver algo esperando na fila.
> 4. `aux = retira_f(f)` — tira o próximo da fila (o que está esperando há mais tempo).
> 5. `printf(...)` — visita `aux`.
> 6. `if (aux->esq) insere_f(f, aux->esq)` — **só agora**, depois de visitar `aux`, seus
>    filhos entram na fila — vão esperar sua vez atrás de tudo que já estava na fila.

### Conferindo com a árvore da Teoria 04

```
              a
          /       \
         b          c
        / \        / \
       d   e      f   g
```

> **Trace da fila:**
>
> | Passo | Retira e visita | Fila **depois** de inserir os filhos |
> |---|---|---|
> | 1 | `a` | `[b, c]` |
> | 2 | `b` | `[c, d, e]` |
> | 3 | `c` | `[d, e, f, g]` |
> | 4 | `d` | `[e, f, g]` (d é folha, nada entra) |
> | 5 | `e` | `[f, g]` |
> | 6 | `f` | `[g]` |
> | 7 | `g` | `[]` — fila vazia, `while` para |

Sequência de visita: `a, b, c, d, e, f, g` — repare que sai **nível por nível** (nível 0:
`a`; nível 1: `b, c`; nível 2: `d, e, f, g`), diferente de qualquer um dos percursos em
profundidade da Teoria 04.

## 4. Busca por força bruta

```c
TAB *busca(TAB *a, int info) {
  if ((!a) || (a->info == info)) return a;
  TAB *resp = busca(a->esq, info);
  if (resp) return resp;
  return busca(a->dir, info);
}
```

> 📖 **Lendo devagar:**
> 1. `if ((!a) || (a->info == info)) return a;` — dois casos de parada num só `if`: **ou**
>    a árvore acabou (`!a`, achou `NULL`, valor não está aqui) **ou** achou o valor
>    (`a->info == info`) — nos dois casos, devolve `a` (que é `NULL` no primeiro caso, ou o
>    nó certo no segundo).
> 2. `resp = busca(a->esq, info)` — tenta achar **na subárvore esquerda inteira** primeiro.
> 3. `if (resp) return resp;` — se achou lá (resp não é `NULL`), já devolve — **não perde
>    tempo olhando a direita**.
> 4. `return busca(a->dir, info);` — só chega aqui se não achou à esquerda; tenta à direita
>    (e o resultado, ache ou não, é devolvido direto).

**Por que "força bruta"?** Sem nenhuma propriedade de ordenação (isso só existe a partir da
BST, 1.2), não há como saber se o valor está à esquerda ou à direita sem **olhar as duas** —
no pior caso, é preciso visitar todos os nós. Complexidade: O(n).

## 5. Altura, calculada recursivamente

```c
int maximo(int x, int y) {
  if (x >= y) return x;
  return y;
}

int altura(TAB *a) {
  if (!a) return -1;
  return 1 + maximo(altura(a->esq), altura(a->dir));
}
```

> 📖 **Lendo `altura` devagar:**
> 1. `if (!a) return -1;` — **convenção**: árvore vazia tem altura −1. É essa escolha que
>    faz a fórmula funcionar sem caso especial para folha (veja abaixo).
> 2. `altura(a->esq)`, `altura(a->dir)` — pergunta recursivamente a altura de cada
>    subárvore.
> 3. `maximo(...)` — a altura da árvore é ditada pelo lado **mais fundo** — o mais raso não
>    importa para o "recorde" de profundidade.
> 4. `1 + maximo(...)` — soma 1 porque, ao subir do nível dos filhos para o nível de `a`, o
>    caminho ganhou mais uma ligação.

**Conferindo com um nó-folha:** um nó folha `x` tem `esq = NULL` e `dir = NULL`. Então
`altura(x) = 1 + maximo(altura(NULL), altura(NULL)) = 1 + maximo(-1, -1) = 1 + (-1) = 0`. ✔
Bate com a convenção "folha tem altura 0" — e funcionou **sem** o código precisar checar
"é folha?" separadamente; o `-1` da árvore vazia absorve esse caso.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| usar fila em vez de pilha/recursão | garanto que nós **mais rasos** saem antes dos mais fundos — é a definição de percurso em largura |
| `busca` testar `a->esq` inteiro antes de `a->dir` | sem ordenação, não há informação para "cortar caminho" — preciso olhar tudo até achar ou esgotar |
| `altura(NULL) = -1` | escolho o valor que faz "1 + máximo das subárvores" funcionar até para folha, sem `if` extra |

## 7. Exercícios de fixação

Usando a árvore `130 / 100,200 / 83,120,150,230` (mesma da Teoria 04, seção 7):

1. Escreva a sequência de visita em **largura**.
2. Rode `busca(raiz, 120)` mentalmente: passa por quais nós, em que ordem, até achar?
3. Calcule `altura` da árvore inteira, usando a fórmula recursiva (mostre o cálculo para
   cada folha antes de subir).
4. Por que `busca` não pode simplesmente "ir para a esquerda se o valor for menor", como
   você talvez tenha visto em outro contexto?

### Gabarito

1. Largura: `130, 100, 200, 83, 120, 150, 230` (nível 0, depois nível 1, depois nível 2).
2. `busca(130, 120)`: `130 ≠ 120`, tenta esquerda: `busca(100, 120)`. `100 ≠ 120`, tenta
   esquerda: `busca(83, 120)`. `83 ≠ 120`, tenta esquerda: `busca(NULL, 120)` → retorna
   `NULL`. Volta para o nó `83`, tenta direita: `busca(NULL, 120)` → `NULL`. Volta para
   `100` (esgotou a esquerda, `resp` era `NULL`), tenta direita: `busca(120, 120)` →
   `120 == 120`, **achou**, retorna o nó `120`. Esse resultado sobe até o topo. Visitou:
   `130, 100, 83, (NULL), (NULL), 120`.
3. Folhas `83, 120, 150, 230`: todas com `altura = 0` (subárvores vazias, `1 + máx(-1,-1) =
   0`). Nó `100`: `1 + máx(altura(83), altura(120)) = 1 + máx(0,0) = 1`. Nó `200`: mesma
   conta, `1`. Raiz `130`: `1 + máx(altura(100), altura(200)) = 1 + máx(1,1) = 2`.
   **Altura da árvore = 2.**
4. Porque "ir para a esquerda se o valor for menor" só é uma decisão válida se a árvore
   **garantir** que todo valor à esquerda é menor que o pai — essa é a propriedade de BST
   (1.2), que uma árvore binária qualquer **não tem**. Usar essa regra numa árvore sem essa
   garantia arriscaria nunca olhar o lado onde o valor realmente está.

## Resumo

- Percurso em largura visita nível por nível, usando **fila** (não recursão) — o que entra
  primeiro na fila (mais raso) sai primeiro.
- `busca` numa árvore binária sem ordenação é força bruta: O(n), porque não há informação
  para descartar um lado sem olhar.
- `altura(NULL) = -1` é a convenção que faz a fórmula recursiva `1 + máx(...)` funcionar
  igual para folha e para nó interno, sem caso especial.

**Próximo:** [[Teoria 06 - Tipos de árvore binária (cheia, completa, perfeita)]].
