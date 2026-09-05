# 5.1 Heaps em Memória Principal

## Objetivo de aprendizagem

- Entender a propriedade de heap (min-heap/max-heap) e por que ela é mais fraca que a propriedade de BST.
- Saber representar um heap binário em array (sem ponteiros) e derivar os índices de pai/filhos por aritmética.
- Dominar as operações heapify-up, heapify-down, build-heap, inserção e extração do topo, com suas complexidades.
- Entender heapsort como aplicação direta do heap e por que build-heap é O(n), não O(n log n).

## Roteiro de leitura

- **SZ (livro-base):** capítulo sobre Heaps e Filas de Prioridade — cobre a definição de heap, representação em array e as operações básicas. (conferir página exata)
- **CO (Cormen):** cap. 6 "Heapsort" do CLRS — a referência mais completa e rigorosa deste subtópico: define heap binário, demonstra `MAX-HEAPIFY`, `BUILD-MAX-HEAP` (com a prova de que é O(n), não O(n log n)) e o algoritmo `HEAPSORT`. (conferir página exata)
- **CE (Celes):** não identifiquei capítulo dedicado a heap/fila de prioridade no livro do Celes — o foco dele é listas, pilhas, filas, árvores e hash em memória principal. Se ao abrir o PDF você encontrar uma seção sobre isso, complemente aqui; caso contrário, use CO como referência de implementação teórica e adapte para C.
- **KR:** cap. 5 "Ponteiros e Arrays" — útil se for implementar o heap com array dinâmico (realloc quando o heap cresce além da capacidade alocada). (conferir página exata)

## Notas de estudo elaboradas

### Definição e propriedade de heap

Um **heap binário** é uma árvore binária **quase-completa** (todos os níveis cheios, exceto possivelmente o último, que é preenchido da esquerda para a direita) que satisfaz a **propriedade de heap**:

- **Max-heap:** para todo nó `i` diferente da raiz, `valor(pai(i)) ≥ valor(i)` — a raiz contém o maior elemento.
- **Min-heap:** para todo nó `i` diferente da raiz, `valor(pai(i)) ≤ valor(i)` — a raiz contém o menor elemento.

Diferença crucial em relação a uma BST: heap garante ordem apenas entre **pai e filho**, não entre irmãos nem em qualquer ordem de percurso (em-ordem não produz sequência ordenada). Isso torna a busca de um elemento arbitrário O(n) num heap — a estrutura não foi desenhada pra isso, só para acesso rápido ao mínimo/máximo.

### Representação em array

Por ser quase-completa, o heap é representado eficientemente num array `A[0..n-1]` sem ponteiros:

```
pai(i)          = (i - 1) / 2
filho_esq(i)    = 2*i + 1
filho_dir(i)    = 2*i + 2
```

Isso economiza a memória de ponteiros e melhora localidade de cache em relação a uma árvore ligada.

### Heapify-down (sift-down / max-heapify)

Corrige a propriedade de heap quando o nó `i` pode ser menor que um dos filhos (usado após remover a raiz e recolocar o último elemento nela):

```
MAX-HEAPIFY(A, i, n):
    maior = i
    e = filho_esq(i); d = filho_dir(i)
    se e < n e A[e] > A[maior]: maior = e
    se d < n e A[d] > A[maior]: maior = d
    se maior != i:
        troca A[i], A[maior]
        MAX-HEAPIFY(A, maior, n)
```

Complexidade: O(log n) — proporcional à altura do heap.

### Heapify-up (sift-up)

Corrige a propriedade quando um nó pode ser maior que o pai (usado após inserir um elemento no final do array):

```
SIFT-UP(A, i):
    enquanto i > 0 e A[pai(i)] < A[i]:
        troca A[i], A[pai(i)]
        i = pai(i)
```

Complexidade: O(log n).

### Build-heap — por que é O(n) e não O(n log n)

```
BUILD-MAX-HEAP(A, n):
    para i de floor(n/2)-1 até 0:
        MAX-HEAPIFY(A, i, n)
```

**Análise ingênua (errada):** n/2 chamadas de heapify, cada uma O(log n) → O(n log n).

**Análise correta:** a maioria dos nós está perto das folhas, onde heapify custa pouco. Formalmente, a soma dos custos é:

```
Σ (para h de 0 até log n) [ n / 2^(h+1) ] · O(h)  =  O(n) · Σ h/2^h  =  O(n)
```

porque a série `Σ h/2^h` (h de 0 a ∞) converge para uma constante (2). Essa é uma pegadinha clássica de prova — build-heap **é linear**, não `O(n log n)`.

### Inserção e extração

- **Inserir(x):** coloca `x` no final do array (`A[n] = x`, `n++`) e aplica `SIFT-UP`. O(log n).
- **Extrair-máximo():** guarda `A[0]` (o resultado), move o último elemento para a raiz (`A[0] = A[n-1]`, `n--`), aplica `MAX-HEAPIFY(A, 0, n)`. O(log n).
- **Consultar-máximo():** retorna `A[0]`. O(1).

### Heapsort

```
HEAPSORT(A, n):
    BUILD-MAX-HEAP(A, n)
    para i de n-1 até 1:
        troca A[0], A[i]
        MAX-HEAPIFY(A, 0, i)   # heap "encolhe" — A[i] já está na posição final
```

Complexidade total: O(n) do build-heap + n chamadas de heapify O(log n) cada = **O(n log n)**, sempre (não depende de caso melhor/pior/médio — é determinístico). É **in-place** (não precisa de memória auxiliar como merge sort), mas **não é estável** (elementos iguais podem trocar de ordem relativa).

### Tabela de complexidade

| Operação | Complexidade |
|---|---|
| Build-heap (n elementos) | O(n) |
| Inserir | O(log n) |
| Extrair mín/máx | O(log n) |
| Consultar mín/máx | O(1) |
| Heapsort completo | O(n log n) |
| Buscar elemento arbitrário | O(n) |

### Exemplo passo a passo

Vamos inserir, um a um, os valores **5, 3, 8, 1, 4** num max-heap representado em array, aplicando `SIFT-UP` a cada inserção:

| Inserção | Array após colocar no final | Sift-up | Array final |
|---|---|---|---|
| insere 5 | `[5]` | raiz, nada a fazer | `[5]` |
| insere 3 | `[5, 3]` | pai(1)=0, A[0]=5 ≥ 3 → nada | `[5, 3]` |
| insere 8 | `[5, 3, 8]` | pai(2)=0, A[0]=5 < 8 → troca | `[8, 3, 5]` |
| insere 1 | `[8, 3, 5, 1]` | pai(3)=1, A[1]=3 ≥ 1 → nada | `[8, 3, 5, 1]` |
| insere 4 | `[8, 3, 5, 1, 4]` | pai(4)=1, A[1]=3 < 4 → troca; pai(1)=0, A[0]=8 ≥ 4 → para | `[8, 4, 5, 1, 3]` |

Heap final: `A = [8, 4, 5, 1, 3]` (raiz = maior elemento, 8).

Agora uma **extração do máximo**: guarda `A[0] = 8` como resultado, move o último elemento (3) para a raiz e reduz o tamanho (`n` de 5 para 4): `A = [3, 4, 5, 1]`. Aplica `MAX-HEAPIFY` a partir da raiz:

1. `i=0` (valor 3): filho esq. `i=1` (valor 4) e filho dir. `i=2` (valor 5) — o maior dos três é 5 (índice 2) → troca `A[0]` com `A[2]`: `A = [5, 4, 3, 1]`.
2. `i=2` (valor 3): filho esq. seria índice 5, fora do array (`n=4`) → para.

Resultado: elemento extraído = **8**, heap resultante = `[5, 4, 3, 1]`.

## Exemplos em C

Min-heap (ou max-heap — aqui usamos max-heap, consistente com os exemplos acima) representado em array, com capacidade fixa por simplicidade:

```c
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDADE_MAX 100

typedef struct {
    int dados[CAPACIDADE_MAX];
    int tamanho;
} Heap;

void heap_inicializa(Heap *h) {
    h->tamanho = 0;
}

static int pai(int i)       { return (i - 1) / 2; }
static int filho_esq(int i) { return 2 * i + 1; }
static int filho_dir(int i) { return 2 * i + 2; }

static void troca(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Corrige a propriedade de heap subindo o elemento em dados[i]
// (usada logo após uma inserção no final do array).
static void heapify_up(Heap *h, int i) {
    while (i > 0 && h->dados[pai(i)] < h->dados[i]) {
        troca(&h->dados[pai(i)], &h->dados[i]);
        i = pai(i);
    }
}

// Corrige a propriedade de heap descendo o elemento em dados[i]
// (usada após mover o último elemento para a raiz, na extração).
static void heapify_down(Heap *h, int i) {
    int maior = i;
    int e = filho_esq(i);
    int d = filho_dir(i);

    if (e < h->tamanho && h->dados[e] > h->dados[maior]) maior = e;
    if (d < h->tamanho && h->dados[d] > h->dados[maior]) maior = d;

    if (maior != i) {
        troca(&h->dados[i], &h->dados[maior]);
        heapify_down(h, maior);
    }
}

// Insere um elemento: coloca no final e "sobe" até restaurar a propriedade. O(log n).
void heap_insere(Heap *h, int valor) {
    if (h->tamanho >= CAPACIDADE_MAX) {
        fprintf(stderr, "Heap cheio!\n");
        return;
    }
    h->dados[h->tamanho] = valor;
    heapify_up(h, h->tamanho);
    h->tamanho++;
}

// Remove e retorna o maior elemento: raiz vira o último, heap "encolhe",
// e heapify_down restaura a propriedade a partir da raiz. O(log n).
int heap_extrai_max(Heap *h) {
    int max = h->dados[0];
    h->tamanho--;
    h->dados[0] = h->dados[h->tamanho];
    heapify_down(h, 0);
    return max;
}
```

Repare que `heapify_up` e `heapify_down` são exatamente `SIFT-UP` e `MAX-HEAPIFY` descritos acima, só traduzidos para C com aritmética de ponteiros de array em vez de pseudocódigo.

## Pontos de atenção / pegadinhas comuns de prova

- **Build-heap é O(n), não O(n log n)** — o erro de multiplicar ingenuamente "n operações × O(log n) cada" é o mais cobrado em prova sobre esse tópico.
- Heap **não garante ordenação global** — só a relação pai ≥ filhos (max-heap). Não confundir com BST, onde existe uma ordem total percorrível.
- Heapsort é O(n log n) **sempre** (pior, médio e melhor caso), diferente de quicksort, que degrada para O(n²) no pior caso.
- Heapsort **não é estável**: elementos com mesma chave podem sair em ordem diferente da entrada.
- Ao remover a raiz, o erro comum é esquecer de mover o **último** elemento do array para a raiz antes de aplicar heapify-down — sem isso a propriedade de árvore quase-completa se quebra.

## Anotações pessoais

## Exercícios resolvidos
