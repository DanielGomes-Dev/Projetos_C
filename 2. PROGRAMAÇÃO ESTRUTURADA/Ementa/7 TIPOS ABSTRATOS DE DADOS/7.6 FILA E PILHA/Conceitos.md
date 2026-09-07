# Conceitos — Fila e Pilha

## A ideia em uma frase

Pilha e fila são coleções em que você **não escolhe** qual elemento sai: a pilha devolve
sempre o último que entrou (LIFO), a fila devolve sempre o primeiro que entrou (FIFO).

## O conceito

**Pilha (LIFO — Last In, First Out).** Como uma pilha de pratos: você só mexe no topo.
Operações:

- `push(x)` — coloca `x` no topo
- `pop()` — tira e devolve o do topo
- `topo()` — espia o do topo sem tirar
- `vazia()`

Usos: desfazer/refazer, pilha de chamadas de funções, avaliar expressões, percorrer
labirinto (backtracking).

**Fila (FIFO — First In, First Out).** Como a fila do banco: entra no fim, sai da frente.
Operações:

- `enfileira(x)` / `insere(x)` — coloca `x` no fim
- `desenfileira()` / `retira()` — tira e devolve o da frente
- `vazia()`

Usos: impressão, atendimento por ordem de chegada, busca em largura (BFS).

Todas as operações são **O(1)** nas duas estruturas.

### Duas implementações

| | com vetor | com lista encadeada |
|---|---|---|
| Pilha | `vet[n]`, topo em `vet[n-1]` | topo = primeiro nó; push/pop = inserir/remover no início |
| Fila | vetor **circular** + `ini` e `n` | dois ponteiros: `ini` e `fim` |
| Limite | capacidade fixa | cresce até a memória acabar |

## Exemplos passo a passo

### Exemplo 1 — pilha com vetor

```c
#include <stdio.h>
#include <stdlib.h>
#define N 50

typedef struct {
    float vet[N];
    int n;              // nº de elementos E índice da próxima posição livre
} Pilha;

void  pilha_cria(Pilha *p)  { p->n = 0; }
int   pilha_vazia(Pilha *p) { return p->n == 0; }

void pilha_push(Pilha *p, float v) {
    if (p->n == N) { printf("cheia\n"); exit(1); }
    p->vet[p->n++] = v;          // grava em vet[n], depois n++
}
float pilha_pop(Pilha *p) {
    if (pilha_vazia(p)) { printf("vazia\n"); exit(1); }
    return p->vet[--p->n];        // n--, depois lê vet[n]
}

int main(void) {
    Pilha p;
    pilha_cria(&p);
    pilha_push(&p, 10);
    pilha_push(&p, 20);
    pilha_push(&p, 30);
    printf("%.0f ", pilha_pop(&p));   // 30
    printf("%.0f ", pilha_pop(&p));   // 20
    printf("%.0f\n", pilha_pop(&p));  // 10
    return 0;
}
```

**Passo a passo:** após os 3 `push`, `vet = [10,20,30]`, `n = 3`. `pop`: `--n` → 2, lê
`vet[2]` = 30. Próximo `pop`: `--n` → 1, lê `vet[1]` = 20. Sai na ordem inversa da entrada.

### Exemplo 2 — o problema da "fila que anda" e a solução circular

Fila ingênua num vetor: insere no fim, remove da frente. Depois de algumas operações:

```
insere 1,2,3        [1][2][3][ ][ ]   ini=0  fim=3
retira, retira      [ ][ ][3][ ][ ]   ini=2  fim=3
insere 4,5          [ ][ ][3][4][5]   ini=2  fim=5
insere 6           -> "cheia"?! mas há 2 posições livres no começo
```

O vetor "andou" para a direita. Solução: tratar o vetor como **circular** — depois da
última posição vem a primeira, calculado com `% N`.

### Exemplo 3 — fila circular com vetor

```c
#include <stdio.h>
#include <stdlib.h>
#define N 5

typedef struct {
    float vet[N];
    int n;      // quantos elementos
    int ini;    // índice do próximo a sair
} Fila;

void fila_cria(Fila *f)  { f->n = 0; f->ini = 0; }
int  fila_vazia(Fila *f) { return f->n == 0; }

void fila_insere(Fila *f, float v) {
    if (f->n == N) { printf("cheia\n"); exit(1); }
    int fim = (f->ini + f->n) % N;   // posição livre, dando a volta se preciso
    f->vet[fim] = v;
    f->n++;
}
float fila_retira(Fila *f) {
    if (fila_vazia(f)) { printf("vazia\n"); exit(1); }
    float v = f->vet[f->ini];
    f->ini = (f->ini + 1) % N;        // avança circularmente
    f->n--;
    return v;
}

int main(void) {
    Fila f;
    fila_cria(&f);
    fila_insere(&f, 1);
    fila_insere(&f, 2);
    printf("%.0f\n", fila_retira(&f));   // 1
    fila_insere(&f, 3);
    printf("%.0f\n", fila_retira(&f));   // 2
    printf("%.0f\n", fila_retira(&f));   // 3
    return 0;
}
```

**Passo a passo de `(f->ini + f->n) % N`:** com `ini = 3`, `n = 3`, `N = 5`:
`(3 + 3) % 5 = 1`. A próxima inserção vai para o índice 1 — que "deu a volta" e voltou ao
começo do vetor, aproveitando o espaço liberado pelas remoções.

### Exemplo 4 — aplicação de pilha: expressão pós-fixada (RPN)

Regra: número → empilha; operador → desempilha 2, calcula, empilha o resultado.
`1 2 - 4 5 + *` calcula `(1-2) * (4+5)`:

```
token  ação                       pilha
  1    push 1                      [1]
  2    push 2                      [1, 2]
  -    b=2, a=1, push a-b=-1       [-1]
  4    push 4                      [-1, 4]
  5    push 5                      [-1, 4, 5]
  +    b=5, a=4, push 9            [-1, 9]
  *    b=9, a=-1, push -9          [-9]
resultado: -9
```

## Erros comuns / pegadinhas

- **`pop`/`retira` sem checar vazia** — lê índice inválido / deref de `NULL`.
- **`push`/`insere` sem checar cheia** (na versão com vetor) — grava fora do vetor.
- **Fila com vetor sem ser circular** — reporta "cheia" com espaço livre no início.
- **Confundir a ordem dos operandos no RPN** — `a - b`, não `b - a`; o primeiro `pop` é o
  operando da direita.
- **Fila com lista sem guardar o ponteiro do fim** — inserir no fim vira O(n).
- **Misturar `n` e índice** na pilha com vetor — o topo está em `vet[n-1]`, a posição
  livre em `vet[n]`.

## Resumo / checklist

- [ ] Sei a diferença LIFO (pilha) x FIFO (fila)
- [ ] Sei as operações de cada uma e que todas são O(1)
- [ ] Sei implementar pilha com vetor (`vet[n++]` / `vet[--n]`)
- [ ] Sei por que a fila com vetor precisa ser circular e sei usar `% N`
- [ ] Sei avaliar uma expressão pós-fixada com pilha
- [ ] Sempre checo vazia/cheia antes de operar
