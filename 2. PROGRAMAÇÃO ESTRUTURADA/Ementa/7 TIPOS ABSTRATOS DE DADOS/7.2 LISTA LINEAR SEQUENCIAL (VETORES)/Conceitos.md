# Conceitos — Lista Linear Sequencial (Vetores)

## A ideia em uma frase

Uma lista sequencial guarda os elementos em posições **contíguas** de um vetor, com um
contador de quantos estão em uso — o acesso por posição é instantâneo, mas inserir ou
remover no meio custa deslocar os vizinhos.

## O conceito

A representação é um vetor com capacidade fixa e uma variável `n` = quantos elementos
estão realmente ocupados:

```
capacidade = 8
n = 4
índice:  0    1    2    3    4    5    6    7
        [10] [20] [30] [40] [ ?] [ ?] [ ?] [ ?]
                             ^ n aponta para a 1ª posição livre
```

- **Acesso por posição:** `v[i]` é O(1) — o endereço é calculado direto do índice.
- **Inserir na posição `p`:** é preciso empurrar `v[p..n-1]` uma casa para a direita e só
  então gravar. O(n) no pior caso.
- **Remover a posição `p`:** puxar `v[p+1..n-1]` uma casa para a esquerda. O(n).
- **Inserir/remover no fim:** O(1) (nenhum deslocamento).

Esse O(n) do meio é exatamente o motivo das
[[../7.3 LISTA SIMPLESMENTE ENCADEADA/Conceitos|listas encadeadas]] existirem.

## Exemplos passo a passo

### Exemplo 1 — inserir no meio com deslocamento

```c
#include <stdio.h>
#define MAX 100

// insere 'x' na posição 'pos', empurrando o resto para a direita
int insere(int v[], int *n, int pos, int x) {
    if (*n >= MAX || pos < 0 || pos > *n) return 0;   // sem espaço ou posição inválida
    for (int i = *n; i > pos; i--)
        v[i] = v[i - 1];        // de trás para frente, para não sobrescrever
    v[pos] = x;
    (*n)++;
    return 1;
}

int main(void) {
    int v[MAX] = {10, 20, 30, 40};
    int n = 4;

    insere(v, &n, 2, 99);       // quer 10 20 [99] 30 40
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
    return 0;
}
```

**Passo a passo de `insere(v, &n, 2, 99)` com `n = 4`:**

```
início:  [10][20][30][40]           n=4
i=4:     v[4] = v[3] = 40   -> [10][20][30][40][40]
i=3:     v[3] = v[2] = 30   -> [10][20][30][30][40]
(i=2 não entra: i > pos é falso)
grava:   v[2] = 99          -> [10][20][99][30][40]
n vira 5
```

**O que observar:** o laço vai **de trás para frente**. Se fosse de `pos` para o fim,
`v[3] = v[2]` já teria destruído o `30` antes de copiá-lo.

### Exemplo 2 — remover do meio

```c
#include <stdio.h>

int remove_pos(int v[], int *n, int pos) {
    if (pos < 0 || pos >= *n) return 0;
    for (int i = pos; i < *n - 1; i++)
        v[i] = v[i + 1];        // puxa o resto para a esquerda
    (*n)--;
    return 1;
}

int main(void) {
    int v[10] = {10, 20, 99, 30, 40};
    int n = 5;

    remove_pos(v, &n, 2);       // tira o 99
    for (int i = 0; i < n; i++) printf("%d ", v[i]);   // 10 20 30 40
    printf("\n");
    return 0;
}
```

**Passo a passo (`pos = 2`, `n = 5`):** `v[2]=v[3]=30`, `v[3]=v[4]=40`. `n` vira 4. O
antigo `v[4]` (40) continua na memória mas está fora da parte usada (`i < n`).

### Exemplo 3 — busca linear

```c
#include <stdio.h>

int busca(const int v[], int n, int alvo) {
    for (int i = 0; i < n; i++)
        if (v[i] == alvo) return i;   // devolve a posição
    return -1;                         // não encontrado
}

int main(void) {
    int v[] = {10, 20, 30, 40};
    printf("%d\n", busca(v, 4, 30));   // 2
    printf("%d\n", busca(v, 4, 77));   // -1
    return 0;
}
```

Custo: O(n). Se o vetor estiver **ordenado**, dá para usar busca binária, O(log n) — ver
[[../../8 BUSCA EM LISTA/Conceitos|8 Busca em Lista]].

## Erros comuns / pegadinhas

- **Deslocar na direção errada** ao inserir — sobrescreve elementos. Insere: de trás para
  frente. Remove: da frente para trás.
- **Não checar `n >= capacidade`** antes de inserir — grava fora do vetor.
- **Confundir "capacidade" com "n"** — o vetor tem `MAX` posições, mas só `n` valem.
- **Ler `v[i]` com `i >= n`** — lê lixo de uma posição não usada.
- **Retornar um vetor local de uma função** (`int v[10]; return v;`) — o vetor some no
  `return`; use `malloc`.

## Resumo / checklist

- [ ] Sei a representação: vetor + contador `n`
- [ ] Sei que acesso por índice é O(1) e inserção/remoção no meio é O(n)
- [ ] Sei deslocar na direção certa em cada operação
- [ ] Sempre checo espaço antes de inserir e limites antes de acessar
- [ ] Sei por que a lista encadeada troca esse O(n) por O(1) (perdendo o acesso direto)
