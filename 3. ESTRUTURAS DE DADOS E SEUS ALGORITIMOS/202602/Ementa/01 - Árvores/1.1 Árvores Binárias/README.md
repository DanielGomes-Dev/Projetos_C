# 1.1 Árvores Binárias

## Objetivo de aprendizagem

- Definir formalmente árvore binária e distinguir árvore cheia, completa e perfeita.
- Implementar os quatro percursos clássicos (pré-ordem, em-ordem, pós-ordem, em largura) recursiva e iterativamente.
- Calcular altura, número de nós e propriedades estruturais de uma árvore binária.
- Entender por que árvore binária "pura" (sem propriedade de busca) é a base para BST, AVL, heaps.

## Roteiro de leitura

- **SZ (livro-base):** capítulo "Árvores" (conceitos gerais de árvore como estrutura, terminologia: raiz, folha, altura, profundidade, grau) seguido do capítulo/seção "Árvores Binárias" (conferir página exata).
- **CO (Cormen):** não há capítulo dedicado só a árvores binárias genéricas — o CLRS introduz árvores binárias como parte do cap. 10 "Estruturas de Dados Elementares" (representação com ponteiros) e retoma a ideia ao entrar em BST no cap. 12. Vale ler a seção de representação de árvores do cap. 10 (conferir página exata).
- **CE (Celes):** capítulo dedicado a árvores binárias com implementação completa em C (`struct` do nó, funções de inserção/percurso) — é a referência principal para a fase de codar este tópico (conferir página exata).
- **KR:** cap. 6 "Structs" (struct auto-referenciada via ponteiro) e cap. 5 "Ponteiros e Arrays" (alocação dinâmica de nós) — consultar se tiver dúvida pontual de sintaxe C ao implementar.

## Notas de estudo elaboradas

### Definição

Uma árvore binária é uma estrutura em que cada nó tem no máximo dois filhos, distinguidos como filho esquerdo e filho direito (a distinção importa — uma árvore com só filho esquerdo é estruturalmente diferente de uma com só filho direito, mesmo com um nó). A árvore vazia é uma árvore binária válida (caso base da recursão).

### Tipos de árvore binária

| Tipo | Definição |
|---|---|
| **Cheia (full)** | Todo nó tem 0 ou 2 filhos (nunca exatamente 1). |
| **Completa (complete)** | Todos os níveis preenchidos, exceto possivelmente o último, que é preenchido da esquerda para a direita. |
| **Perfeita (perfect)** | Todos os níveis totalmente preenchidos — todas as folhas na mesma profundidade. Uma árvore perfeita com altura *h* tem exatamente 2^(h+1) − 1 nós. |
| **Balanceada** | Para cada nó, a diferença de altura entre subárvore esquerda e direita é limitada (definição formal varia; AVL usa diferença ≤ 1). |

Toda árvore perfeita é completa e cheia; a recíproca não vale.

### Percursos

```
pré-ordem(nó):        visita(nó); pré-ordem(esq); pré-ordem(dir)
em-ordem(nó):          em-ordem(esq); visita(nó); em-ordem(dir)
pós-ordem(nó):         pós-ordem(esq); pós-ordem(dir); visita(nó)
em largura (BFS):      usa fila; visita nível a nível
```

- **Pré-ordem**: útil para copiar/serializar a árvore (a raiz vem antes das subárvores, então dá pra reconstruir).
- **Em-ordem**: em uma BST, visita os nós em ordem crescente de chave — é o percurso mais importante quando a árvore tem propriedade de busca (ver 1.2).
- **Pós-ordem**: útil quando é preciso processar os filhos antes do pai (ex.: liberar memória da árvore — desalocar filhos antes do nó atual).
- **Em largura**: usa fila (FIFO) em vez de recursão/pilha; é o único percurso que não é naturalmente DFS.

### Complexidade

| Operação | Complexidade |
|---|---|
| Percurso completo (qualquer ordem) | O(n) — visita cada nó uma vez |
| Cálculo de altura | O(n) |
| Contagem de nós | O(n) |

Sem propriedade de busca, **não existe** operação de busca eficiente em árvore binária genérica — encontrar um valor exige O(n) no pior caso (é preciso olhar todos os nós). Isso é o que motiva a BST (1.2).

### Passo a passo: construindo e percorrendo uma árvore concreta

Considere a árvore binária (não é BST — os valores não seguem nenhuma ordem, só a forma da árvore importa aqui):

```
          1
        /   \
       2     3
      / \     \
     4   5     6
```

- **Construção** (bottom-up, como o `TAB_cria` faz): primeiro criam-se os nós-folha (4, 5, 6), depois combinam-se em subárvores (`2` com filhos 4 e 5; `3` com filho direito 6, esquerdo nulo), e por fim a raiz `1` liga as duas subárvores.
- **Pré-ordem** (visita → esquerda → direita): `1, 2, 4, 5, 3, 6`
- **Em-ordem** (esquerda → visita → direita): `4, 2, 5, 1, 3, 6` — repare que aqui a sequência **não é crescente**, porque esta árvore não tem propriedade de busca (isso só aconteceria numa BST, ver 1.2).
- **Pós-ordem** (esquerda → direita → visita): `4, 5, 2, 6, 3, 1`
- **Em largura** (nível a nível, com fila): começa com fila = `[1]`; desenfileira `1`, visita, enfileira `2` e `3` → fila `[2,3]`; desenfileira `2`, visita, enfileira `4` e `5` → fila `[3,4,5]`; desenfileira `3`, visita, enfileira `6` → fila `[4,5,6]`; desenfileira e visita `4, 5, 6` em sequência. Resultado: `1, 2, 3, 4, 5, 6`.
- **Altura**: a subárvore mais funda é a que passa por `3 → 6`, com profundidade 2 a partir da raiz (contando raiz como profundidade 0) — então `altura(árvore) = 2`. Isso bate com a recursão `TAB_altura`: `altura(nó) = 1 + max(altura(esq), altura(dir))`, com `altura(vazia) = -1`.

## Exemplos em C

Trechos abaixo adaptados de uma implementação real e testada de árvore binária genérica, disponível completa em `ListasExercicios/lista01-EDA/TAB/` (`TAB.h` + `TAB.c`).

```c
// TAB.h — struct do nó: sem nenhuma propriedade de ordenação,
// só a forma da árvore (esq/dir) importa
typedef struct arvbin {
  int info;
  struct arvbin *esq, *dir;
} TAB;

TAB *TAB_inicializa(void);
TAB *TAB_cria(int raiz, TAB *esq, TAB *dir);
void TAB_imp_pre(TAB *a);
void TAB_imp_sim(TAB *a);
void TAB_imp_pos(TAB *a);
void TAB_libera(TAB *a);
TAB *TAB_busca(TAB *a, int elem);
int  TAB_altura(TAB *a);
```

```c
// TAB.c
TAB *TAB_inicializa(void) {
  return NULL;              // árvore vazia = ponteiro NULL (caso base de toda recursão abaixo)
}

TAB *TAB_cria(int raiz, TAB *esq, TAB *dir) {
  TAB *novo = (TAB *) malloc(sizeof(TAB));
  novo->info = raiz;
  novo->esq  = esq;         // já recebe subárvores prontas — construção é bottom-up
  novo->dir  = dir;
  return novo;
}

// Busca por FORÇA BRUTA: sem propriedade de ordenação, é preciso
// checar a subárvore esquerda inteira antes de tentar a direita.
// Pior caso O(n) — compare com TABB_busca em 1.2, que é O(log n) numa BST balanceada.
TAB *TAB_busca(TAB *a, int elem) {
  if ((!a) || (a->info == elem)) return a;
  TAB *resp = TAB_busca(a->esq, elem);
  if (resp) return resp;
  return TAB_busca(a->dir, elem);
}

void TAB_imp_pre(TAB *a) {                  // pré-ordem: visita, esq, dir
  if (a) {
    printf("%d ", a->info);
    TAB_imp_pre(a->esq);
    TAB_imp_pre(a->dir);
  }
}

void TAB_imp_sim(TAB *a) {                  // em-ordem: esq, visita, dir
  if (a) {
    TAB_imp_sim(a->esq);
    printf("%d ", a->info);
    TAB_imp_sim(a->dir);
  }
}

void TAB_imp_pos(TAB *a) {                  // pós-ordem: esq, dir, visita
  if (a) {
    TAB_imp_pos(a->esq);
    TAB_imp_pos(a->dir);
    printf("%d ", a->info);
  }
}

void TAB_libera(TAB *a) {                   // libera em pós-ordem: filhos antes do pai
  if (a) {
    TAB_libera(a->esq);
    TAB_libera(a->dir);
    free(a);
  }
}

int TAB_altura(TAB *a) {
  if (!a) return -1;                        // convenção: árvore vazia tem altura -1
  int he = TAB_altura(a->esq), hd = TAB_altura(a->dir);
  return (he >= hd ? he : hd) + 1;
}
```

Código completo e testado em `ListasExercicios/lista01-EDA/TAB/` (inclui também `TAB_imp_ident`, impressão identada da árvore, útil pra depurar visualmente).

## Pontos de atenção / pegadinhas comuns de prova

- Não confundir "árvore completa" com "árvore cheia" — são propriedades diferentes e independentes (uma árvore pode ser cheia sem ser completa).
- Altura de árvore vazia costuma ser definida como −1 e altura de nó folha como 0 — confira a convenção usada no seu curso/livro-base antes da prova, porque isso muda fórmulas de contagem.
- Em-ordem só produz sequência ordenada se a árvore for uma **árvore binária de busca** — em árvore binária genérica não tem esse significado.
- Percurso em largura usa fila; percursos DFS (pré/em/pós-ordem) usam recursão ou pilha explícita — trocar essas estruturas é um erro clássico de implementação.

## Anotações pessoais

## Exercícios resolvidos
