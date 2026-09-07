# Conceitos — Matriz

## A ideia em uma frase

Uma matriz é uma tabela de linhas e colunas; na memória do computador, que é linear, ela
sempre vira uma sequência de valores — a questão é **como mapear `(linha, coluna)` para
uma posição** nessa sequência.

## O conceito

### Matriz estática

`float m[4][3];` — em C, isso é "um vetor de 4 elementos, cada um sendo um vetor de 3
`float`". Os 12 valores ficam contíguos, **por linha** (*row-major*): primeiro
`m[0][0], m[0][1], m[0][2]`, depois `m[1][0]...`.

Ao passar para uma função, o número de **colunas tem que aparecer** no tipo:
`void f(float m[][3], int lin)` — sem ele o compilador não sabe onde uma linha termina.

### Matriz dinâmica — 3 estratégias

| Estratégia | Como | Acesso | Prós / contras |
|---|---|---|---|
| **1. Vetor linearizado** | `malloc(m*n*sizeof(float))` | `mat[i*n + j]` | 1 `malloc`/`free`; mas a conta `i*n+j` deixa o código feio |
| **2. Vetor de ponteiros** | vetor de `m` ponteiros; cada linha um `malloc` | `mat[i][j]` | sintaxe limpa; mas `m+1` mallocs e liberação em laço |
| **3. Simétrica** | guarda só a metade `n(n+1)/2` | função de acesso espelha `(i,j)` | economiza memória quando `mat[i][j] == mat[j][i]` |

## Exemplos passo a passo

### Exemplo 1 — matriz estática e o mapa row-major

```c
#include <stdio.h>

void imprime(int lin, int col, int m[][3]) {   // colunas obrigatórias no tipo
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++)
            printf("%3d", m[i][j]);
        printf("\n");
    }
}

int main(void) {
    int m[2][3] = {{1, 2, 3}, {4, 5, 6}};
    imprime(2, 3, m);
    return 0;
}
```

**Como `m[1][2]` vira um endereço:** o compilador calcula `base + (1*3 + 2) * sizeof(int)`
= `base + 5*4`. O `3` na fórmula é o número de colunas — por isso ele precisa estar no
tipo do parâmetro.

### Exemplo 2 — matriz dinâmica linearizada (estratégia 1)

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int lin = 3, col = 4;
    float *m = malloc(lin * col * sizeof(float));   // 1 bloco de 12 floats

    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++)
            m[i*col + j] = i * 10 + j;              // "m[i][j]" escrito à mão

    printf("%.0f\n", m[2*col + 1]);                 // elemento (2,1) -> 21
    free(m);                                        // 1 free só
    return 0;
}
```

**Passo a passo de `m[2*col + 1]`:** `col = 4`, então `2*4 + 1 = 9`. O elemento `(2,1)`
está na posição 9 do vetor: pulou 2 linhas inteiras (8 elementos) e mais 1 coluna.

### Exemplo 3 — matriz dinâmica como vetor de ponteiros (estratégia 2)

```c
#include <stdio.h>
#include <stdlib.h>

float **cria(int lin, int col) {
    float **m = malloc(lin * sizeof(float *));      // vetor de ponteiros de linha
    for (int i = 0; i < lin; i++)
        m[i] = malloc(col * sizeof(float));          // cada linha, seu próprio bloco
    return m;
}

void libera(float **m, int lin) {
    for (int i = 0; i < lin; i++) free(m[i]);        // linhas PRIMEIRO
    free(m);                                         // vetor de ponteiros DEPOIS
}

int main(void) {
    int lin = 3, col = 4;
    float **m = cria(lin, col);

    m[2][1] = 21;                                    // sintaxe natural, sem i*col+j
    printf("%.0f\n", m[2][1]);

    libera(m, lin);
    return 0;
}
```

**O que observar:** a ordem de liberação é o **inverso** da alocação. Se você fizer
`free(m)` antes de liberar as linhas, perde os ponteiros `m[i]` e vaza cada linha.

### Exemplo 4 — matriz simétrica (estratégia 3)

Numa matriz simétrica, `mat[i][j] == mat[j][i]`. Guardar as duas metades é desperdício —
guarde só a triangular inferior (`n(n+1)/2` elementos) e faça a função de acesso espelhar:

```c
#include <stdio.h>
#include <stdlib.h>

static int idx(int i, int j) {
    if (i < j) { int t = i; i = j; j = t; }   // sempre trabalha na metade i >= j
    return i * (i + 1) / 2 + j;
}

int main(void) {
    int n = 4;
    float *m = malloc(n * (n + 1) / 2 * sizeof(float));   // 10 floats, não 16

    m[idx(2, 1)] = 7.5f;
    printf("%.1f\n", m[idx(1, 2)]);   // 7.5 — (1,2) e (2,1) vão para o mesmo lugar
    free(m);
    return 0;
}
```

## Erros comuns / pegadinhas

- **Omitir o número de colunas** ao passar matriz estática para função.
- **Escrever `m[i, j]`** — em C isso é `m[j]` (operador vírgula). Use `m[i][j]`.
- **`i*col + j` com o número errado** (usar `lin` no lugar de `col`).
- **Liberar o vetor de ponteiros antes das linhas** — vaza todas as linhas.
- **Esquecer que a estratégia 2 não é contígua** — as linhas podem estar espalhadas; não
  dá para tratar `m[0]` como um bloco de `lin*col` elementos.
- **Acessar fora dos limites** — C não verifica em nenhuma das estratégias.

## Resumo / checklist

- [ ] Sei que matriz estática é "vetor de vetores" e é armazenada row-major
- [ ] Sei por que o nº de colunas entra no tipo do parâmetro
- [ ] Sei linearizar: `mat[i*col + j]`
- [ ] Sei alocar e liberar a matriz vetor-de-ponteiros na ordem certa
- [ ] Sei a ideia da matriz simétrica (guardar metade, espelhar no acesso)
