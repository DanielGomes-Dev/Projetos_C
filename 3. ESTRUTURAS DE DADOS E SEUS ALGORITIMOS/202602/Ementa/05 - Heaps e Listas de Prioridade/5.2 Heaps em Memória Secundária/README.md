# 5.2 Heaps em Memória Secundária

## Objetivo de aprendizagem

- Entender por que a representação clássica de heap em array (memória principal) é ineficiente quando os dados residem em disco.
- Conhecer heaps multiway (d-ários) como estratégia para reduzir a altura da árvore e, consequentemente, o número de acessos a disco.
- Relacionar heaps externos com o algoritmo de seleção por substituição usado em ordenação externa.

## Roteiro de leitura

- **SZ (livro-base):** capítulo sobre Heaps e Filas de Prioridade — costuma tratar a extensão do heap para memória secundária logo após o heap clássico, incluindo a motivação de reduzir I/O. (conferir página exata)
- **CO (Cormen):** o CLRS não tem capítulo dedicado a heaps em memória secundária — o foco do cap. 6 é heap em memória principal. Não há cobertura direta deste subtópico no Cormen; use-o só como base teórica do heap clássico (ver 5.1) e generalize o raciocínio de I/O usando a mesma lógica do módulo `03 - Arquivos e Ordenação Externa`.
- **CE (Celes):** não cobre heap em memória secundária (é mais focado em estruturas de memória principal) — diga isso se não encontrar a seção correspondente no PDF.
- **KR:** não se aplica diretamente — este subtópico é mais conceitual/algorítmico que de implementação em C específica.
Marque com "(conferir página exata)" já que não consegui confirmar paginação real dos PDFs.

## Notas de estudo elaboradas

### Por que o heap em array não é ideal em disco

O heap binário clássico (ver `5.1`) assume acesso aleatório barato: heapify-down/up navegam entre índices `i`, `2i+1`, `2i+2` que, em memória principal, custam o mesmo independentemente de onde estão. Em disco, o custo dominante não é o número de comparações, mas o **número de acessos** (I/O), e acessos não sequenciais (saltar entre índices distantes de um heap grande) são caros porque cada acesso pode custar uma leitura de página/bloco inteira.

O objetivo em memória secundária é o mesmo dos outros módulos que tratam de disco (árvores B, hashing extensível, ordenação externa): **minimizar o número de acessos**, não o número de comparações.

### Heaps multiway (d-ários)

Uma estratégia é generalizar o heap binário para um **heap d-ário**, onde cada nó tem até `d` filhos em vez de 2:

```
pai(i)      = (i - 1) / d
filho_k(i)  = d*i + k + 1     (k = 0, ..., d-1)
```

**Efeito:** a altura do heap cai de `O(log₂ n)` para `O(log_d n)`, reduzindo o número de níveis — e, portanto, o número de acessos a disco no pior caso — às custas de mais comparações por nível na hora de encontrar o maior/menor entre os `d` filhos ao fazer heapify-down.

**Trade-off central:**

| d (grau) | Altura (acessos no pior caso) | Comparações por heapify-down |
|---|---|---|
| 2 (heap binário) | O(log₂ n) — mais níveis | menos comparações por nível |
| d grande | O(log_d n) — menos níveis | mais comparações por nível (até d-1) |

Em memória secundária, como o custo de um acesso a disco domina fortemente o custo de uma comparação em memória, vale a pena escolher `d` maior (reduzir acessos) mesmo pagando mais comparações — o oposto do que se otimizaria em memória principal.

### Ligação com ordenação externa

O algoritmo de **seleção por substituição** (replacement selection), usado no módulo `03 - Arquivos e Ordenação Externa` (subtópico 3.2, geração de partições) para gerar partições (runs) maiores que a memória disponível, usa internamente um heap (min-heap) para sempre saber qual é o próximo menor elemento a escrever na partição corrente. É a mesma estrutura de dados (heap), só que operando sobre um fluxo de entrada maior que a memória — reforçando por que dominar heap em memória principal (5.1) é pré-requisito direto para este subtópico e para 3.2.

Da mesma forma, a fase de **intercalação de k vias** (módulo 3.3) usa um heap (ou tournament tree, equivalente) para escolher, a cada passo, o menor elemento entre as k partições sendo mescladas — outra aplicação direta de heap em contexto de memória secundária.

### Exemplo concreto: por que d maior reduz acessos

Considere um heap com **n = 1000 elementos**:

- **Heap binário (d=2):** altura ≈ `log₂(1000) ≈ 10` níveis. No pior caso, uma inserção ou extração toca ~10 nós — em disco, até 10 acessos.
- **Heap 4-ário (d=4):** altura ≈ `log₄(1000) ≈ 5` níveis. A mesma operação toca ~5 nós — pela metade dos acessos a disco, quase.

O custo por nível sobe (heapify-down agora compara entre até 4 filhos em vez de 2), mas essa comparação é feita **em memória**, praticamente de graça perto do custo de um acesso a disco. Por isso, em memória secundária, aumentar `d` costuma compensar até o ponto em que o próprio nó (com seus `d` filhos/ponteiros) deixa de caber confortavelmente numa página/bloco de disco — daí em diante o ganho para.

## Exemplos em C

Variação do heap de `5.1`, parametrizada pelo grau `d` (heap d-ário). A diferença central está nas fórmulas de índice e em `heapify_down`, que agora escolhe o menor (ou maior) entre até `d` filhos em vez de 2:

```c
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDADE_MAX 1000

typedef struct {
    int dados[CAPACIDADE_MAX];
    int tamanho;
    int d;  // grau do heap (2 = binário, 4 = quaternário, ...)
} HeapD;

void heapd_inicializa(HeapD *h, int grau) {
    h->tamanho = 0;
    h->d = grau;
}

static int pai_d(HeapD *h, int i)        { return (i - 1) / h->d; }
static int filho_d(HeapD *h, int i, int k) { return h->d * i + 1 + k; }  // k = 0..d-1

static void troca(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Sobe o elemento em dados[i] até restaurar a propriedade de heap. O(log_d n).
static void heapd_up(HeapD *h, int i) {
    while (i > 0 && h->dados[pai_d(h, i)] < h->dados[i]) {
        troca(&h->dados[pai_d(h, i)], &h->dados[i]);
        i = pai_d(h, i);
    }
}

// Desce o elemento em dados[i] escolhendo, entre os até d filhos, o maior. O(d · log_d n).
static void heapd_down(HeapD *h, int i) {
    int maior = i;
    for (int k = 0; k < h->d; k++) {
        int filho = filho_d(h, i, k);
        if (filho < h->tamanho && h->dados[filho] > h->dados[maior])
            maior = filho;
    }
    if (maior != i) {
        troca(&h->dados[i], &h->dados[maior]);
        heapd_down(h, maior);
    }
}

void heapd_insere(HeapD *h, int valor) {
    h->dados[h->tamanho] = valor;
    heapd_up(h, h->tamanho);
    h->tamanho++;
}

int heapd_extrai_max(HeapD *h) {
    int max = h->dados[0];
    h->tamanho--;
    h->dados[0] = h->dados[h->tamanho];
    heapd_down(h, 0);
    return max;
}
```

Note que `heapd_down` agora é um laço sobre os `d` filhos (em vez de comparar só 2 valores fixos) — é exatamente o trade-off "menos níveis, mais comparações por nível" discutido acima, escrito em código.

## Pontos de atenção / pegadinhas comuns de prova

- O ganho de um heap d-ário em disco vem de **reduzir acessos**, não de reduzir comparações — o número total de comparações pode até aumentar; o que se otimiza é o número de níveis/acessos.
- Não confundir heap d-ário com árvore B: a árvore B é balanceada e ordenada em cada nó (múltiplas chaves ordenadas por nó), enquanto o heap d-ário só mantém a propriedade fraca de heap (pai ≥ filhos, sem ordem entre irmãos).
- A escolha do grau `d` ideal depende da relação entre custo de I/O e custo de comparação em memória — não existe um `d` universalmente ótimo, é um trade-off dependente do hardware/contexto.
- Ao explicar seleção por substituição, lembre que o heap usado ali é do tamanho da memória principal disponível — a partição gerada é maior que a memória porque elementos são substituídos no heap conforme são consumidos, não porque o heap em si seja maior que a memória.

## Anotações pessoais

## Exercícios resolvidos
