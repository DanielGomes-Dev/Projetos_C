# Conceitos — Quick Sort

## A ideia em uma frase

Escolha um elemento como **pivô**, rearranje o vetor para que os menores fiquem à esquerda
dele e os maiores à direita (agora o pivô está na posição final), e repita nos dois lados.

## O conceito

Também é **divisão e conquista**, mas o trabalho pesado está em *dividir*, não em
*combinar*:

1. **Particionar** — escolhe um pivô `x`. Reorganiza o vetor: tudo `≤ x` de um lado, tudo
   `> x` do outro. O pivô vai para o meio, na sua posição definitiva.
2. **Conquistar** — chama o quicksort no lado esquerdo e no lado direito.
3. **Combinar** — nada a fazer; os lados já estão no lugar certo.

**Desempenho:** depende da escolha do pivô.

- Pivô perto da mediana → partições equilibradas → O(n log n).
- Pivô sempre no extremo (ex.: último elemento de um vetor já ordenado) → uma partição
  fica com `n-1`, a outra vazia → **O(n²)**, o pior caso.
- Caso médio: O(n log n).

**Vantagens sobre o [[../6.1 MERGE SORT/Conceitos|merge sort]]:** ordena *in-place* (só
O(log n) de pilha de recursão, sem vetor auxiliar), e na prática é mais rápido. É o que
está por trás do `qsort` da biblioteca.

**Reduzindo o risco do pior caso:** escolher o pivô como a **mediana de três** (primeiro,
meio, último) ou aleatoriamente.

## O particionamento (esquema de Lomuto)

Pivô = último elemento. Um índice `i` marca o fim da zona "≤ pivô". Um índice `j` varre o
resto; sempre que `v[j] <= pivô`, avança `i` e troca `v[i]` com `v[j]`. No fim, troca o
pivô para a posição `i+1`.

## Exemplos passo a passo

### Exemplo 1 — implementação completa

```c
#include <stdio.h>

int particiona(int v[], int lo, int hi) {
    int pivo = v[hi];            // pivô = último elemento
    int i = lo - 1;             // fim da zona "<= pivô"
    for (int j = lo; j < hi; j++) {
        if (v[j] <= pivo) {
            i++;
            int t = v[i]; v[i] = v[j]; v[j] = t;
        }
    }
    int t = v[i + 1]; v[i + 1] = v[hi]; v[hi] = t;   // põe o pivô no lugar
    return i + 1;                                     // posição final do pivô
}

void quicksort(int v[], int lo, int hi) {
    if (lo >= hi) return;                             // 0 ou 1 elemento
    int p = particiona(v, lo, hi);
    quicksort(v, lo, p - 1);     // lado esquerdo (< pivô)
    quicksort(v, p + 1, hi);     // lado direito (> pivô)
}

int main(void) {
    int v[] = {5, 2, 8, 1, 9, 3};
    int n = sizeof v / sizeof v[0];
    quicksort(v, 0, n - 1);
    for (int i = 0; i < n; i++) printf("%d ", v[i]);   // 1 2 3 5 8 9
    printf("\n");
    return 0;
}
```

### Exemplo 2 — traçando `particiona([5 2 8 1 9 3], 0, 5)`

Pivô = `v[5] = 3`. `i = -1`.

```
j=0: v[0]=5 <= 3?  não
j=1: v[1]=2 <= 3?  sim -> i=0, troca v[0]<->v[1]  ->  2 5 8 1 9 3
j=2: v[2]=8 <= 3?  não
j=3: v[3]=1 <= 3?  sim -> i=1, troca v[1]<->v[3]  ->  2 1 8 5 9 3
j=4: v[4]=9 <= 3?  não
fim -> troca v[i+1]=v[2] com v[5]  ->  2 1 3 5 9 8
retorna 2
```

Agora `3` está no índice 2 (posição definitiva): `[2 1]` à esquerda são ≤ 3, `[5 9 8]` à
direita são > 3. Recorre em `[2 1]` e em `[5 9 8]`.

**O que observar:** cada elemento é comparado com o pivô uma vez → a partição custa O(n).
São ~`log n` níveis quando o pivô é bom → O(n log n).

### Exemplo 3 — o pior caso

Vetor já ordenado `[1 2 3 4 5]`, pivô = último elemento:

```
particiona -> pivô 5 fica em v[4]; esquerda = [1 2 3 4], direita = []
particiona -> pivô 4 fica em v[3]; esquerda = [1 2 3],   direita = []
particiona -> pivô 3 ...
```

São `n` níveis de recursão, cada um O(n) → **O(n²)**. É o cenário que a "mediana de três"
evita: com pivô = mediana de `{1, 3, 5}` = `3`, a partição sai equilibrada.

## Erros comuns / pegadinhas

- **Pivô fixo no primeiro/último elemento** com entradas já (quase) ordenadas → O(n²).
  Use mediana de três ou pivô aleatório.
- **`quicksort(v, lo, p)` em vez de `p - 1`** — inclui o pivô de novo → recursão infinita.
- **Caso base `lo == hi`** em vez de `lo >= hi` — trechos vazios (`lo > hi`) causam acesso
  inválido.
- **`i` começando em `lo` em vez de `lo - 1`** — desloca toda a partição.
- **Esperar estabilidade** — quicksort não é estável.
- **`qsort` com comparação `x - y`** — risco de overflow; use `(x > y) - (x < y)`.

## Resumo / checklist

- [ ] Sei os passos: particionar em torno do pivô, recorrer nos dois lados
- [ ] Sei que o pivô fica na posição final após a partição
- [ ] Sei traçar o esquema de Lomuto (índice `i` da zona "≤ pivô")
- [ ] Sei por que o pior caso é O(n²) e como a escolha do pivô muda isso
- [ ] Sei a vantagem sobre o merge sort (in-place, O(log n) de memória)
- [ ] Sei que `qsort` da biblioteca é um quicksort
