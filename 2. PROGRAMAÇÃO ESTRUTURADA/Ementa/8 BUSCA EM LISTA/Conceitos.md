# Conceitos — Busca em Lista

## A ideia em uma frase

Procurar um valor numa coleção: percorrer tudo (**busca linear**, O(n), funciona sempre)
ou, se os dados estiverem **ordenados** e em vetor, cortar o espaço de busca pela metade a
cada passo (**busca binária**, O(log n)).

## O conceito

**Busca linear.** Olha um elemento por vez, do começo ao fim. Devolve a posição ou `-1`.

- Pior caso: O(n) (elemento no fim ou ausente).
- Vale para qualquer coleção — vetor desordenado, lista encadeada, etc.
- Num vetor **ordenado**, dá para parar assim que passa do ponto onde o valor estaria —
  melhora a constante, mas **continua O(n)**.

**Busca binária.** Só em vetor **ordenado**. Compara com o elemento do meio:

- igual → achou;
- alvo menor → repete só na metade esquerda;
- alvo maior → repete só na metade direita.

O espaço de busca vira `n, n/2, n/4, ..., 1` → no máximo `1 + log₂ n` passos → **O(log n)**.
Para 1 milhão de elementos, ~20 comparações.

**Por que binária não funciona em lista encadeada:** não há como "ir ao meio" em O(1) —
seria preciso percorrer metade da lista só para achar o elemento central. Em lista
encadeada, só busca linear.

## Exemplos passo a passo

### Exemplo 1 — busca linear

```c
#include <stdio.h>

int busca_linear(const int v[], int n, int alvo) {
    for (int i = 0; i < n; i++)
        if (v[i] == alvo) return i;
    return -1;
}

int main(void) {
    int v[] = {40, 10, 30, 20};
    printf("%d\n", busca_linear(v, 4, 30));   // 2
    printf("%d\n", busca_linear(v, 4, 99));   // -1
    return 0;
}
```

### Exemplo 2 — busca binária iterativa

```c
#include <stdio.h>

int busca_binaria(const int v[], int n, int alvo) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = ini + (fim - ini) / 2;      // evita overflow de (ini+fim)/2
        if (v[meio] == alvo)  return meio;
        if (alvo < v[meio])   fim = meio - 1;   // descarta a metade direita
        else                  ini = meio + 1;   // descarta a metade esquerda
    }
    return -1;
}

int main(void) {
    int v[] = {12, 25, 33, 37, 48, 57, 86, 92};   // PRECISA estar ordenado
    printf("%d\n", busca_binaria(v, 8, 57));       // 5
    printf("%d\n", busca_binaria(v, 8, 99));       // -1
    return 0;
}
```

**Passo a passo de `busca_binaria(v, 8, 57)`:**

```
ini=0 fim=7  meio=3  v[3]=37  57>37 -> ini=4
ini=4 fim=7  meio=5  v[5]=57  achou! -> retorna 5
```

Duas comparações para 8 elementos. Para 1000 elementos seriam ~10.

**Passo a passo de um valor ausente, `busca_binaria(v, 8, 99)`:**

```
ini=0 fim=7  meio=3  v[3]=37  99>37 -> ini=4
ini=4 fim=7  meio=5  v[5]=57  99>57 -> ini=6
ini=6 fim=7  meio=6  v[6]=86  99>86 -> ini=7
ini=7 fim=7  meio=7  v[7]=92  99>92 -> ini=8
ini(8) > fim(7) -> sai do laço -> retorna -1
```

### Exemplo 3 — busca binária recursiva

```c
#include <stdio.h>

int bb_rec(const int v[], int ini, int fim, int alvo) {
    if (ini > fim) return -1;                    // caso base: intervalo vazio
    int meio = ini + (fim - ini) / 2;
    if (v[meio] == alvo) return meio;
    if (alvo < v[meio])  return bb_rec(v, ini, meio - 1, alvo);
    else                 return bb_rec(v, meio + 1, fim, alvo);
}

int main(void) {
    int v[] = {12, 25, 33, 37, 48, 57, 86, 92};
    printf("%d\n", bb_rec(v, 0, 7, 33));   // 2
    return 0;
}
```

Passar `ini` e `fim` como parâmetros evita ter que "recompor" o índice — a função sempre
trabalha com posições do vetor original.

### Exemplo 4 — `bsearch` da biblioteca

```c
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void) {
    int v[] = {12, 25, 33, 37, 48, 57, 86, 92};
    int chave = 48;
    int *achou = bsearch(&chave, v, 8, sizeof(int), cmp);
    if (achou) printf("indice %d\n", (int)(achou - v));   // 4
    else       printf("nao achou\n");
    return 0;
}
```

`bsearch` faz busca binária genérica; **exige o vetor ordenado** pelo mesmo critério da
função `cmp`.

## Erros comuns / pegadinhas

- **Busca binária em vetor não ordenado** — dá resultado errado sem erro.
- **`(ini + fim) / 2`** — pode estourar em vetores enormes; use `ini + (fim - ini) / 2`.
- **`while (ini < fim)`** em vez de `<=` — não testa o último candidato quando
  `ini == fim`.
- **`fim = meio` / `ini = meio`** em vez de `meio - 1` / `meio + 1` — loop infinito.
- **Tentar busca binária em lista encadeada** — não há acesso O(1) ao meio.
- **Comparação `x - y`** com risco de overflow.

## Resumo / checklist

- [ ] Sei quando usar linear (sempre) e binária (vetor ordenado)
- [ ] Sei que linear é O(n) e binária é O(log n), e sei derivar o log
- [ ] Sei traçar a busca binária para um valor presente e um ausente
- [ ] Sei escrever a versão recursiva passando `ini`/`fim`
- [ ] Sei por que binária não serve para lista encadeada
- [ ] Uso `ini + (fim - ini)/2` e `meio ± 1`
