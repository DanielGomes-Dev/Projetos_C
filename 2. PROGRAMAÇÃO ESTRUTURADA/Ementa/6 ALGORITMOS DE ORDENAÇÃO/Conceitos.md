# Conceitos — Algoritmos de Ordenação (panorama)

## A ideia em uma frase

Ordenar é rearranjar os elementos em ordem crescente (ou decrescente); os métodos se
dividem em **simples** (fáceis de escrever, O(n²)) e **eficientes** (mais elaborados,
O(n log n)).

## O conceito

Vocabulário que vale para qualquer método:

- **Comparação e troca** — os métodos "por comparação" só olham "a < b?" e trocam
  posições. Existe um limite teórico: nenhum método por comparação faz melhor que
  O(n log n).
- **In-place (no lugar)** — usa só um punhado de memória extra, além do vetor.
- **Estável** — dois elementos com a mesma chave mantêm a ordem relativa original. Importa
  quando você ordena por um campo e quer preservar uma ordenação anterior por outro.

| Método | Melhor | Médio | Pior | Memória | Estável |
|---|---|---|---|---|---|
| Bolha (bubble) | O(n) | O(n²) | O(n²) | O(1) | sim |
| Seleção | O(n²) | O(n²) | O(n²) | O(1) | não |
| Inserção | O(n) | O(n²) | O(n²) | O(1) | sim |
| [[6.1 MERGE SORT/Conceitos\|Merge sort]] | O(n log n) | O(n log n) | O(n log n) | O(n) | sim |
| [[6.2 QUICK SORT/Conceitos\|Quick sort]] | O(n log n) | O(n log n) | O(n²) | O(log n) | não |

Regra prática: para vetores pequenos ou quase ordenados, um método simples serve. Para o
resto, use `qsort` da biblioteca (quicksort por dentro).

## Exemplos passo a passo

### Exemplo 1 — bubble sort e a ideia de "empurrar o maior para o fim"

A cada passada, comparo pares vizinhos e troco se estiverem fora de ordem. O maior
elemento "borbulha" até o fim.

```c
#include <stdio.h>

void bubble(int v[], int n) {
    for (int fim = n - 1; fim > 0; fim--) {
        int trocou = 0;
        for (int j = 0; j < fim; j++) {
            if (v[j] > v[j + 1]) {
                int t = v[j]; v[j] = v[j + 1]; v[j + 1] = t;
                trocou = 1;
            }
        }
        if (!trocou) return;      // nenhuma troca -> já está ordenado (melhor caso O(n))
    }
}

int main(void) {
    int v[] = {5, 1, 4, 2, 8};
    int n = 5;
    bubble(v, n);
    for (int i = 0; i < n; i++) printf("%d ", v[i]);   // 1 2 4 5 8
    printf("\n");
    return 0;
}
```

**Passo a passo (1ª passada, `v = 5 1 4 2 8`):**

```
(5,1) 5>1 troca -> 1 5 4 2 8
(5,4) 5>4 troca -> 1 4 5 2 8
(5,2) 5>2 troca -> 1 4 2 5 8
(5,8) ok             1 4 2 5 8   <- o 8 já estava no lugar
```

Fim da passada: o `8` está garantidamente no fim. 2ª passada trabalha só até o índice 3, e
assim por diante. Se uma passada inteira não fizer nenhuma troca, o vetor já está ordenado
e o algoritmo para.

### Exemplo 2 — seleção: achar o menor e colocar na frente

```c
#include <stdio.h>

void selecao(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (v[j] < v[min]) min = j;
        int t = v[i]; v[i] = v[min]; v[min] = t;   // 1 troca por passada
    }
}

int main(void) {
    int v[] = {29, 10, 14, 37, 13};
    selecao(v, 5);
    for (int i = 0; i < 5; i++) printf("%d ", v[i]);  // 10 13 14 29 37
    printf("\n");
    return 0;
}
```

**Passo a passo:** varre `v[0..4]`, acha o menor (`10`, índice 1), troca com `v[0]`.
Agora varre `v[1..4]`, acha o menor (`13`), troca com `v[1]`. E assim por diante — sempre
uma troca por rodada.

### Exemplo 3 — ordenação genérica com `qsort` (qualquer tipo)

A biblioteca padrão já traz um quicksort genérico. Você só fornece a função de comparação.

```c
#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);     // -1, 0 ou 1 sem risco de overflow
}

int main(void) {
    int v[] = {25, 48, 37, 12, 57, 86, 33, 92};
    int n = sizeof v / sizeof v[0];
    qsort(v, n, sizeof(int), cmp_int);
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
    return 0;
}
```

**O que observar:** `qsort` recebe o vetor, quantos elementos, o tamanho de cada um em
bytes, e um ponteiro para a função de comparação. Ela deve devolver negativo / zero /
positivo. Para ordenar `struct`s por um campo, basta escrever a `cmp` que compara esse
campo (com `strcmp` para nomes, por exemplo).

## Erros comuns / pegadinhas

- **`return x - y` na comparação** — pode dar overflow com inteiros grandes. Use
  `(x > y) - (x < y)`.
- **Trocar `v[j]` com `v[j+1]` quando `j` já é `n-1`** — acesso fora do vetor. O laço
  interno vai até `< fim`, não `<= fim`.
- **Achar que bubble/seleção são "burros demais para usar"** — para `n` pequeno são ótimos
  e não têm o custo de memória do merge nem o pior caso do quick.
- **Esperar estabilidade da seleção ou do quicksort** — não são estáveis.
- **Passar `sizeof(v)` para `qsort`** quando `v` é um ponteiro (parâmetro de função) — dá
  o tamanho do ponteiro, não do vetor. Passe `n` explicitamente.

## Resumo / checklist

- [ ] Sei o que significam in-place, estável e o limite O(n log n)
- [ ] Sei traçar uma passada do bubble sort e por que o maior vai para o fim
- [ ] Sei quando um método O(n²) é aceitável
- [ ] Sei usar `qsort` com uma função de comparação
- [ ] Sei escrever uma comparação sem overflow
