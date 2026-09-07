# Conceitos — Merge Sort

## A ideia em uma frase

Divida o vetor ao meio, ordene cada metade (recursivamente) e depois **intercale** as duas
metades ordenadas numa só — que já sai ordenada.

## O conceito

Merge sort é o exemplo clássico de **divisão e conquista**:

1. **Dividir** — parte o vetor em duas metades.
2. **Conquistar** — ordena cada metade chamando `merge_sort` nela. O caso base é um trecho
   de 0 ou 1 elemento (já ordenado).
3. **Combinar** — `merge` funde duas metades ordenadas numa sequência ordenada.

```
                [25 48 37 12 57 86 33 92]
                /                        \
       [25 48 37 12]                [57 86 33 92]
        /        \                    /        \
   [25 48]     [37 12]           [57 86]     [33 92]
    /   \       /   \             /   \       /   \
 [25] [48]   [37] [12]         [57] [86]   [33] [92]
    \  /        \  /              \  /        \  /
  [25 48]     [12 37]           [57 86]     [33 92]     <- merge
      \          /                  \          /
    [12 25 37 48]                [33 57 86 92]           <- merge
             \                        /
        [12 25 33 37 48 57 86 92]                        <- merge
```

**Custos:** são `log n` níveis de divisão, e cada nível faz O(n) de trabalho no `merge`.
Total: **O(n log n) sempre** — melhor, médio e pior caso iguais, porque o algoritmo não
depende da ordem inicial.

**Preço:** o `merge` precisa de vetores auxiliares — O(n) de memória extra. É por isso que
o quicksort (in-place) costuma ser preferido na prática.

## O `merge` — o coração do algoritmo

Duas pilhas de cartas ordenadas, viradas para cima. A cada passo, pego a menor das duas
cartas do topo e ponho na saída. Quando uma pilha acaba, jogo o resto da outra.

## Exemplos passo a passo

### Exemplo 1 — implementação completa

```c
#include <stdio.h>
#include <stdlib.h>

// funde v[esq..centro] e v[centro+1..dir], ambos já ordenados
void merge(int v[], int esq, int centro, int dir) {
    int n1 = centro - esq + 1;
    int n2 = dir - centro;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = v[esq + i];
    for (int j = 0; j < n2; j++) R[j] = v[centro + 1 + j];

    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2)
        v[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];   // pega o menor dos dois topos
    while (i < n1) v[k++] = L[i++];                    // sobrou em L
    while (j < n2) v[k++] = R[j++];                    // sobrou em R

    free(L);
    free(R);
}

void merge_sort(int v[], int esq, int dir) {
    if (esq >= dir) return;                            // 0 ou 1 elemento
    int centro = esq + (dir - esq) / 2;               // evita overflow de (esq+dir)/2
    merge_sort(v, esq, centro);
    merge_sort(v, centro + 1, dir);
    merge(v, esq, centro, dir);
}

int main(void) {
    int v[] = {25, 48, 37, 12, 57, 86, 33, 92};
    int n = sizeof v / sizeof v[0];
    merge_sort(v, 0, n - 1);
    for (int i = 0; i < n; i++) printf("%d ", v[i]);   // 12 25 33 37 48 57 86 92
    printf("\n");
    return 0;
}
```

### Exemplo 2 — o `merge` de `[25 48]` com `[12 37]`

```
L = [25 48]   R = [12 37]      saída: []
i=0 j=0:  L[0]=25  R[0]=12  -> 12 é menor -> saída [12], j=1
i=0 j=1:  L[0]=25  R[1]=37  -> 25 é menor -> saída [12 25], i=1
i=1 j=1:  L[1]=48  R[1]=37  -> 37 é menor -> saída [12 25 37], j=2
R acabou (j==n2) -> copia o resto de L -> saída [12 25 37 48]
```

**O que observar:** como percorremos os dois lados uma única vez, o `merge` de um trecho
de `m` elementos custa O(m). Somando por nível, O(n) por nível.

### Exemplo 3 — por que `esq + (dir - esq) / 2` e não `(esq + dir) / 2`

As duas fórmulas dão o mesmo resultado matemático, mas em vetores enormes `esq + dir` pode
estourar o limite do `int` e virar um número negativo. `esq + (dir - esq) / 2` nunca
soma dois valores grandes.

## Erros comuns / pegadinhas

- **Caso base errado** — `if (esq == dir)` em vez de `esq >= dir` pode entrar em recursão
  infinita para trechos vazios.
- **`centro + 1` esquecido** na segunda chamada — o elemento do meio fica de fora ou
  duplicado.
- **Comparar com `<` em vez de `<=` no `merge`** — perde a estabilidade (elementos iguais
  invertem).
- **Não liberar `L` e `R`** — vazamento a cada `merge`.
- **Alocar `L`/`R` do tamanho do vetor inteiro toda vez** — desperdício; aloque do
  tamanho do trecho.

## Resumo / checklist

- [ ] Sei os 3 passos: dividir, ordenar as metades, intercalar
- [ ] Sei que é O(n log n) em qualquer caso e por quê
- [ ] Sei o custo: O(n) de memória auxiliar
- [ ] Sei traçar um `merge` de dois trechos ordenados
- [ ] Sei por que usar `esq + (dir - esq)/2`
- [ ] Sei que merge sort é estável (com `<=` no merge)
