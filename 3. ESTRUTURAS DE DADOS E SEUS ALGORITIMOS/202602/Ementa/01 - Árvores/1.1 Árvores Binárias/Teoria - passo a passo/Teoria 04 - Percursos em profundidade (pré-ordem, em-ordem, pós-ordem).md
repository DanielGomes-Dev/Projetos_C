# Teoria 04 — Percursos em profundidade: pré-ordem, em-ordem, pós-ordem

> **Onde isto entra:** com a árvore montada (Teoria 03), a primeira coisa que se faz com ela
> é **visitar todos os nós, numa ordem específica** — é a base de quase todo algoritmo sobre
> árvore daqui pra frente (impressão, cópia, liberação de memória, e em 1.2 a busca ordenada).
> **Antes:** [[Teoria 03 - Representando e construindo uma árvore binária em C]].
> **Fonte:** `lista01-EDA/05_ArvoresBinarias_caminhamento.pdf` (slides da Profa. Vanessa
> Braganholo).

## 1. A ideia em uma frase

Um **caminhamento** (ou percurso) é uma receita que visita cada nó da árvore **exatamente
uma vez**. Existem várias receitas possíveis — a diferença entre elas é só **a ordem** em
que raiz, subárvore esquerda e subárvore direita são visitadas.

## 2. De onde vem a necessidade

Uma árvore não tem uma "próxima posição" óbvia como um array (`i`, `i+1`, `i+2`...). Pra
processar todos os nós (imprimir, somar valores, liberar memória), é preciso uma regra
explícita de "por onde ir primeiro". O slide define a visita como "acesso a um nó para
realizar alguma operação" — e o caminhamento é só a ordem em que essas visitas acontecem.

## 3. As três ordens — lidas devagar, com a árvore do slide

Árvore de referência (pág. 2 do PDF):

```
              a
          /       \
         b          c
        / \        / \
       d   e      f   g
```

> 📖 **Lendo cada definição, de trás pra frente pela regra, aplicando na árvore:**

**Pré-ordem** (raiz — esquerda — direita): visita a raiz **primeiro**, antes de entrar em
qualquer subárvore.
```
a – b – d – e – c – f – g
```
Trace: chega em `a`, visita `a` (1º). Desce pra SAE (`b`): visita `b` (2º) antes de entrar
nos filhos de `b`. Desce pra SAE de `b` (`d`): `d` não tem filhos, visita `d` (3º). Volta,
desce pra SAD de `b` (`e`): visita `e` (4º). Terminou a SAE de `a`. Desce pra SAD de `a`
(`c`): visita `c` (5º), depois `f` (6º), depois `g` (7º).

**Em-ordem / simétrico** (esquerda — raiz — direita): visita a raiz **entre** as duas
subárvores.
```
d – b – e – a – f – c – g
```
Trace: para visitar `a`, primeiro tem que **terminar toda a SAE** de `a` (a subárvore de
`b`). Dentro dela: para visitar `b`, primeiro termina a SAE de `b` (`d`, que é folha —
visita direto). Só depois de esgotar a esquerda de `b` é que `b` é visitado, e só depois
disso vai pra direita de `b` (`e`). Terminou a SAE de `a` inteira (`d,b,e`) — **agora sim**
visita `a`. Repete o processo na SAD de `a` (`c`): esquerda primeiro (`f`), depois `c`,
depois direita (`g`).

**Pós-ordem** (esquerda — direita — raiz): visita a raiz **por último**, depois das duas
subárvores completas.
```
d – e – b – f – g – c – a
```
Trace: mesma lógica de "esgotar antes de visitar", mas agora a raiz espera **as duas**
subárvores (não só a esquerda). `d`, `e` (esgotam a subárvore de `b`), aí sim `b`. Depois
`f`, `g` (esgotam a subárvore de `c`), aí sim `c`. Só no fim, com tudo visitado, `a`.

## 4. Por que cada ordem existe (motivação, não decoreba)

| Ordem | Para que serve na prática |
|---|---|
| Pré-ordem | Copiar/serializar a árvore — a raiz vem escrita antes das subárvores, então dá pra reconstruir a árvore lendo a sequência da esquerda pra direita. |
| Em-ordem | Numa **BST** (1.2), produz os valores em ordem **crescente** — é o motivo de existir; numa árvore binária qualquer (sem propriedade de busca, como aqui), não tem esse significado especial. |
| Pós-ordem | Processar filhos antes do pai — ex.: liberar a memória de uma árvore (`libera`), você precisa liberar os filhos antes de poder liberar (`free`) o nó pai, senão perde o ponteiro para eles. |

## 5. O código — lido pedaço por pedaço

```c
void imp_pre(TAB *a) {
  if (a) {
    printf("%d ", a->info);   // 1. visita a raiz
    imp_pre(a->esq);          // 2. depois a subárvore esquerda inteira
    imp_pre(a->dir);          // 3. depois a subárvore direita inteira
  }
}
```

> 📖 **Lendo `imp_pre` devagar:**
> 1. `if (a)` — **caso base** da recursão: se `a` é `NULL` (árvore vazia), não faz nada e
>    retorna. Sem isso, a recursão nunca pararia.
> 2. `printf("%d ", a->info)` — a "visita": imprime o valor do nó atual.
> 3. `imp_pre(a->esq)` — chamada recursiva na subárvore esquerda **inteira** (não só no
>    filho — a função, ao rodar de novo, vai imprimir esse filho e recursivamente todos os
>    descendentes dele).
> 4. `imp_pre(a->dir)` — mesma ideia, à direita.
> 5. **A única diferença entre pré/em/pós-ordem é a posição do `printf` em relação às duas
>    chamadas recursivas** — compare:

```c
void imp_sim(TAB *a) {                 // em-ordem
  if (a) {
    imp_sim(a->esq);
    printf("%d ", a->info);            // o printf está NO MEIO
    imp_sim(a->dir);
  }
}

void imp_pos(TAB *a) {                 // pós-ordem
  if (a) {
    imp_pos(a->esq);
    imp_pos(a->dir);
    printf("%d ", a->info);            // o printf está NO FIM
  }
}
```

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `if (a) { ... }` sem `else` | trato "árvore vazia" como "não fazer nada e voltar" — é o que permite a recursão nunca acessar campo de ponteiro `NULL` |
| mover o `printf` de posição | escolho **quando**, relativo às duas metades da árvore, o nó atual é processado — antes de ambas, entre elas, ou depois de ambas |
| chamar `imp_pre(a->esq)` | não visito só o filho esquerdo — delego "visite toda essa subárvore, na mesma ordem" pra uma cópia da mesma função |

## 7. Exercícios de fixação

Usando a árvore do slide de exemplo (pág. 5 do PDF):

```
              130
          /         \
        100           200
       /    \        /    \
      83    120    150    230
```

1. Qual a sequência em **pré-ordem**?
2. Qual a sequência **em-ordem**?
3. Qual a sequência em **pós-ordem**?
4. Por que a sequência em-ordem desta árvore específica sai **crescente** (`83, 100, 120,
   130, 150, 200, 230`), diferente da árvore `a,b,c,...` da seção 3?
5. Se você fosse implementar `libera(TAB *a)` (que dá `free` em cada nó), qual dos três
   percursos você usaria como base, e por quê?

### Gabarito

1. Pré-ordem: `130, 100, 83, 120, 200, 150, 230` (raiz, depois SAE inteira, depois SAD
   inteira).
2. Em-ordem: `83, 100, 120, 130, 150, 200, 230`.
3. Pós-ordem: `83, 120, 100, 150, 230, 200, 130`.
4. Porque esta árvore tem uma propriedade que a árvore `a,b,c,...` não tinha: os valores
   estão organizados de forma que "esquerda < pai < direita" em todo nó — isso é
   precisamente a propriedade de **árvore binária de busca**, que você formaliza em 1.2. A
   árvore `a,b,c,...` guardava letras sem nenhuma relação de ordem, então em-ordem não
   produzia nada de especial.
5. Pós-ordem — porque `free(a)` só é seguro depois que os filhos de `a` já foram liberados
   (senão você perderia os ponteiros `a->esq`/`a->dir` antes de poder liberá-los). É
   exatamente `imp_pos`, trocando `printf` por `free`.

## Resumo

- Um percurso visita cada nó exatamente uma vez; a diferença entre pré/em/pós-ordem é só
  **onde**, relativo às duas subárvores, a visita da raiz acontece.
- Pré-ordem: raiz, esquerda, direita. Em-ordem: esquerda, raiz, direita. Pós-ordem:
  esquerda, direita, raiz.
- No código, as três são a mesma função, só com o `printf` (a "visita") em posição
  diferente entre as duas chamadas recursivas.
- Em-ordem só produz sequência crescente numa **BST** — em árvore binária qualquer, não tem
  esse significado.

**Próximo:** [[Teoria 05 - Percurso em largura, busca e altura]].
