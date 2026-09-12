# Teoria 03 — Representando e construindo uma árvore binária em C

> **Onde isto entra:** até aqui, árvore binária era desenho e notação. Agora é código: como
> um nó vira um `struct`, e como as chamadas de `malloc` realmente montam uma árvore na
> memória.
> **Antes:** [[Teoria 02 - Árvore binária (definição e notação)]] · `struct` e ponteiros
> (KR, caps. 5–6, se precisar revisar).
> **Fonte:** `lista01-EDA/05_ArvoresBinarias_sem_caminhamento.pdf`, págs. 5–8 (slides da
> Profa. Vanessa Braganholo) — o mesmo código está em `ListasExercicios/lista01-EDA/TAB/TAB.c`.

## 1. A ideia em uma frase

Um nó de árvore binária é um `struct` com um valor e **dois ponteiros** — um para o filho
esquerdo, um para o direito. Uma árvore vazia é simplesmente o ponteiro `NULL`.

## 2. Por que essa representação e não outra

Você poderia tentar guardar uma árvore num array (como faremos em heap, módulo 06), mas
array exige saber de antemão "quantos nós cabem" e desperdiça espaço se a árvore não for
cheia. Ponteiros resolvem isso: cada nó é alocado **sob demanda** (`malloc`), só quando
existe, e aponta explicitamente para onde estão seus filhos (ou para lugar nenhum, `NULL`,
se não tiver).

## 3. O struct — lido pedaço por pedaço

```c
typedef struct arvbin {
  int info;
  struct arvbin *esq, *dir;
} TAB;
```

> 📖 **Lendo devagar:**
> 1. `struct arvbin { ... }` — declara um novo tipo de registro chamado `arvbin`.
> 2. `int info;` — o valor guardado neste nó (aqui, um inteiro; podia ser qualquer tipo).
> 3. `struct arvbin *esq, *dir;` — **dois ponteiros para o mesmo tipo `struct arvbin`**.
>    Isso é "auto-referência": um nó aponta para outros nós do mesmo tipo. É exatamente o
>    que implementa "subárvore esquerda" e "subárvore direita" da Teoria 02 — `esq` e `dir`
>    **são** as subárvores, representadas como ponteiro para onde elas começam.
> 4. `typedef ... TAB;` — apelido: a partir daqui, `TAB` e `struct arvbin` são o mesmo tipo;
>    o código usa `TAB` por ser mais curto.

## 4. Árvore vazia, e criar um nó

```c
TAB *inicializa(void) {
  return NULL;              // árvore vazia = ponteiro que não aponta para lugar nenhum
}

TAB *cria(int r, TAB *sae, TAB *sad) {
  TAB *novo = (TAB *) malloc(sizeof(TAB));
  novo->info = r;
  novo->esq  = sae;          // já recebe as subárvores PRONTAS
  novo->dir  = sad;
  return novo;
}
```

> 📖 **Lendo `cria(r, sae, sad)` devagar:**
> 1. `malloc(sizeof(TAB))` — pede à memória espaço suficiente para um `TAB` (um `int` + dois
>    ponteiros) e devolve um ponteiro genérico para esse espaço.
> 2. `(TAB *) malloc(...)` — o `(TAB *)` na frente diz "trate esse espaço como um `TAB`" —
>    sem isso, o compilador não saberia que `novo->info` faz sentido.
> 3. `novo->info = r`, `novo->esq = sae`, `novo->dir = sad` — preenche os 3 campos do nó
>    recém-criado. Repare: `cria` **não constrói** as subárvores — ele **recebe** ponteiros
>    para subárvores já prontas e só as pendura no nó novo.

**Consequência importante de "recebe prontas":** para montar uma árvore com `cria`, você
precisa **construir de baixo para cima** — primeiro as folhas (que não têm filhos, então
`sae`/`sad` são `NULL`), depois os nós que as usam como filhos, e por último a raiz.

## 5. Conferindo: construindo a árvore do slide, passo a passo

O slide (pág. 8) monta esta árvore:

```
              1
            /   \
           2      3
                 / \
                4   5
```

Código (`main`, do mesmo slide):

```c
TAB *a5 = cria(5, NULL, NULL);
TAB *a4 = cria(4, NULL, NULL);
TAB *a2 = cria(2, NULL, NULL);
TAB *a3 = cria(3, a4, a5);
TAB *a1 = cria(1, a2, a3);
```

> **Tabela de trace — o que acontece a cada linha:**
>
> | Linha | O que existe depois dela |
> |---|---|
> | `a5 = cria(5, NULL, NULL)` | nó `5`, sem filhos (folha) |
> | `a4 = cria(4, NULL, NULL)` | nó `4`, sem filhos (folha) |
> | `a2 = cria(2, NULL, NULL)` | nó `2`, sem filhos (folha) |
> | `a3 = cria(3, a4, a5)` | nó `3`, com `esq = a4` (o nó `4`) e `dir = a5` (o nó `5`) — agora `3-4-5` já formam uma subárvore completa |
> | `a1 = cria(1, a2, a3)` | nó `1`, com `esq = a2` (o nó `2`, folha) e `dir = a3` (a subárvore `3-4-5` inteira) — **esta é a árvore completa**, e `a1` é o ponteiro para a raiz |

Note a ordem: `a5`, `a4`, `a2` (as folhas) são criados **antes** de `a3` e `a1`, porque
`cria` exige que os filhos já existam como argumento. Se você tentasse escrever
`cria(1, a2, a3)` antes de `a3` existir, `a3` seria lixo de memória — erro clássico.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `malloc(sizeof(TAB))` | reservo espaço na memória para guardar 1 nó — ele existe fisicamente a partir daqui |
| `novo->esq = sae` (com `sae` já pronto) | não crio a subárvore esquerda — só **penduro** uma subárvore que já existe no lugar certo |
| construir de baixo pra cima (folhas primeiro) | é a única ordem possível, porque um nó precisa que os filhos **já existam** para apontar para eles |
| `a1` no final | é o único ponteiro que eu preciso guardar para acessar a árvore inteira — a partir da raiz, `esq`/`dir` alcançam todo o resto |

## 7. Exercícios de fixação

1. Escreva as chamadas de `cria`, na ordem correta, para montar a árvore
   `<10 <20 <> <>> <30 <40 <> <>> <>>>` (notação da Teoria 02).
2. No código da seção 5, o que aconteceria se você trocasse a linha
   `TAB *a3 = cria(3, a4, a5);` por `TAB *a3 = cria(3, a5, a4);`? A árvore resultante ainda
   representa "3 com filhos 4 e 5"?
3. Por que `cria(1, a2, a3)` **precisa** vir depois de `a2` e `a3` existirem, mas a ordem
   entre criar `a4` e criar `a2` não importa?

### Gabarito

1.
   ```c
   TAB *n20 = cria(20, NULL, NULL);
   TAB *n40 = cria(40, NULL, NULL);
   TAB *n30 = cria(30, n40, NULL);
   TAB *n10 = cria(10, n20, n30);
   ```
2. Não da mesma forma: agora `3` teria `esq = a5` (o nó `5`) e `dir = a4` (o nó `4`) — os
   papéis de esquerda e direita trocaram. É uma árvore **diferente** da original (mesmos
   valores, estrutura diferente) — reforça a Teoria 02: esquerda ≠ direita.
3. Porque `cria` recebe os filhos **já prontos** como argumento — não dá pra passar algo que
   ainda não existe. Já `a4` e `a2` são folhas independentes uma da outra (nenhuma é filha
   da outra), então a ordem entre elas não afeta o resultado.

## Resumo

- Nó de árvore binária em C = `struct` com um valor + 2 ponteiros (`esq`, `dir`); árvore
  vazia = `NULL`.
- `cria(valor, sae, sad)` não constrói subárvores — só pendura subárvores **já existentes**
  num nó novo. Isso obriga a construção de baixo para cima: folhas primeiro, raiz por
  último.
- Guardar só o ponteiro da raiz é suficiente para acessar a árvore inteira.

**Próximo:** [[Teoria 04 - Percursos em profundidade (pré-ordem, em-ordem, pós-ordem)]].
