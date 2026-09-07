# Resumo dos Livros — 7.6 Fila e Pilha

## Celes — Introdução a Estruturas de Dados (Cap. 11, "Pilhas"; Cap. 12, "Filas")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção de capítulo: **Cap. 11 (Pilhas)** e **Cap. 12 (Filas)**, não 6/7 — mas o resto da descrição já estava correta: os dois capítulos seguem exatamente a mesma estrutura em 3 partes (interface, implementação com vetor, implementação com lista), e a convenção de nomes (`pilha_`/`fila_`) segue o padrão de TAD do Cap. 9.

**Pilha — interface** (`pilha.h`): `pilha_cria`, `pilha_push`, `pilha_pop`, `pilha_vazia`, `pilha_libera` — usando `push`/`pop` mesmo em português, como termos já consagrados. Analogia usada: pilha de pratos (só se acessa/remove o do topo) → LIFO.

**Pilha com vetor**: `struct pilha { int n; float vet[N]; }` — `n` é ao mesmo tempo "quantos elementos há" **e** "o índice da próxima posição livre" (o topo fica em `vet[n-1]`). `push` checa `n == N` (estouro de capacidade) antes de inserir; `pop` checa `pilha_vazia` antes de remover.

**Pilha com lista**: `struct pilha { Lista* prim; }` — o topo é sempre o primeiro nó da lista; `push` = inserir no início da lista, `pop` = remover do início — literalmente a operação de inserção/remoção no início de [[../7.3 LISTA SIMPLESMENTE ENCADEADA/Resumo dos Livros|7.3]], sem nenhuma lógica nova.

**Aplicação — calculadora pós-fixada (RPN)**: exemplo desenvolvido por completo, motivado pelas calculadoras HP. Regra: número → empilha; operador → desempilha 2 operandos, calcula, empilha o resultado. `(1-2)*(4+5)` vira `1 2 - 4 5 + *`. O TAD `Calc` (`calc.h`, funções `calc_cria`/`calc_operando`/`calc_operador`/`calc_libera`) é implementado **usando o TAD `Pilha` já pronto** — o livro usa isso para reforçar a ideia de reuso de TAD (a calculadora não sabe nem precisa saber se a pilha por baixo usa vetor ou lista).

**Fila — interface** (`fila.h`): `fila_cria`, `fila_insere`, `fila_retira`, `fila_vazia`, `fila_libera` → FIFO. Analogia: fila do dia a dia.

**Fila com vetor — o ponto mais rico do capítulo**: o livro primeiro mostra o problema ingênuo (inserir no fim / retirar do início faz a fila "andar" pelo vetor até bater no final, mesmo sobrando espaço livre no início) e então resolve com **índices circulares**: `struct fila { int n; int ini; float vet[N]; }`, onde `fim = (ini + n) % N`. Deriva o incremento circular em 3 formas progressivas — `if (i == N-1) return 0; else return i+1;` → `return (i+1) % N;` → inline `i = (i+1) % N;` — a mesma técnica de índice modular usada depois em [[../../6 ALGORITMOS DE ORDENAÇÃO/Resumo dos Livros|ordenação]] e coberta de forma mais teórica por Szwarcfiter/Cormen abaixo.

**Fila com lista**: precisa manter **dois** ponteiros (início e fim), diferente da pilha com lista — inserir no fim de uma lista simples é O(n) a menos que se guarde o ponteiro do último nó diretamente na estrutura da fila, o que o livro faz.

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Seções 2.4, 2.5 e 2.7.2)

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Seções 2.4, 2.5 e 2.7.2)
**Alocação sequencial (2.4).** A pilha, sobre vetor, usa um único ponteiro `topo`; inserção e remoção testam overflow (`topo = M`) e underflow (`topo = 0`), ambas em tempo O(1). A fila exige dois ponteiros, `f` (início) e `r` (retaguarda), e o livro chama atenção para um problema real da implementação sequencial: à medida que os ponteiros avançam, "a fila 'se move'", criando a falsa impressão de memória esgotada mesmo com posições livres no início do vetor. A solução apresentada é tratar o vetor como circular (`F[1]` segue `F[M]`), calculando a próxima posição via `r mod M + 1` antes de efetivar a inserção.

**Aplicação — Notação Polonesa (2.5).** Como aplicação de pilha, o livro trata a conversão de expressões aritméticas da notação tradicional (ambígua, exige regras de precedência) para a notação polonesa reversa (pós-fixa), "tradicionalmente utilizada em máquinas de calcular" — ex.: `A*B − C/D` vira `AB*CD/−`. O algoritmo de conversão usa uma pilha para armazenar operadores pendentes, decidindo quando emiti-los com base na ordem em que devem ser calculados.

**Alocação encadeada (2.7.2).** Sobre lista encadeada, a pilha (sem nó-cabeça) usa um único ponteiro `topo` apontando para o primeiro nó — inserir/remover é sempre O(1), sem necessidade de busca. A fila usa dois ponteiros, `inicio` e `fim`; a inserção emenda no fim, a remoção retira do início, também O(1). Como aplicação de fila, o livro descreve a **ordenação por distribuição** (radix sort com filas), com complexidade O(nd) para chaves de d dígitos na base b, citando como curiosidade histórica as classificadoras de cartão perfurado que usavam exatamente esse princípio.

## Cormen — Algoritmos: Teoria e Prática (Seção 10.1)
Cormen define pilhas e filas como "conjuntos dinâmicos nos quais o elemento removido [...] é especificado previamente": a pilha implementa política LIFO ("último a entrar, primeiro a sair"), com `INSERT` chamada `PUSH` e `DELETE` chamada `POP` — nomes que aludem às pilhas de pratos empilháveis de restaurante. A fila implementa FIFO ("primeiro a entrar, primeiro a sair"), com `ENQUEUE` e `DEQUEUE`, comparada a uma fileira de caixa registradora.

A implementação apresentada usa um arranjo `S[1..n]` com atributo `S.topo` para a pilha (`S.topo = 0` é pilha vazia; ultrapassar `n` é estouro). Para a fila, um arranjo `Q[1..n]` com atributos `Q.início` e `Q.fim`, tratado como circular — "a posição 1 segue imediatamente a posição n em uma ordem circular" —, exatamente o mesmo mecanismo de índice modular que Szwarcfiter usa em 2.4. O texto enfatiza que cada uma das operações — `PUSH`, `POP`, `ENQUEUE`, `DEQUEUE` — "demora o tempo O(1)".

## Síntese
Os três livros convergem ponto a ponto: mesma definição LIFO/FIFO, mesma complexidade O(1) para todas as operações, e — notavelmente — exatamente a mesma solução para o problema da "fila que se move" em alocação sequencial: tratar o vetor como circular via aritmética modular (`% N`), com Celes derivando essa fórmula passo a passo em código C real, enquanto Szwarcfiter/Cormen a apresentam já formalizada. Celes contribui a aplicação mais imediatamente prática (calculadora RPN completa, reusando o TAD `Pilha`); Szwarcfiter cobre também conversão para notação polonesa e ordenação por distribuição.

## Exemplos em C

**Pilha com vetor (interface completa, no espírito do Celes):**
```c
#include <stdio.h>
#include <stdlib.h>

#define N 50

typedef struct {
    float vet[N];
    int n;          /* também é o índice da próxima posição livre */
} Pilha;

void pilha_cria(Pilha *p)      { p->n = 0; }
int  pilha_vazia(Pilha *p)     { return p->n == 0; }

void pilha_push(Pilha *p, float v) {
    if (p->n == N) { printf("Pilha cheia.\n"); exit(1); }
    p->vet[p->n++] = v;
}

float pilha_pop(Pilha *p) {
    if (pilha_vazia(p)) { printf("Pilha vazia.\n"); exit(1); }
    return p->vet[--p->n];
}

int main(void) {
    Pilha pilha;
    pilha_cria(&pilha);
    pilha_push(&pilha, 10);
    pilha_push(&pilha, 20);
    printf("%.0f\n", pilha_pop(&pilha));  /* 20 — último a entrar, primeiro a sair */
    printf("%.0f\n", pilha_pop(&pilha));  /* 10 */
    return 0;
}
```

**Calculadora pós-fixada (RPN) usando a pilha acima — o exemplo do Celes:**
```c
#include <ctype.h>
#include <string.h>

float avalia_posfixa(const char *expr) {
    Pilha pilha;
    pilha_cria(&pilha);
    char token[32];
    int i = 0;

    /* tokeniza por espaço; cada token é um número ou um operador */
    char buf[256];
    strcpy(buf, expr);
    char *tok = strtok(buf, " ");
    while (tok != NULL) {
        if (isdigit(tok[0]) || (tok[0] == '-' && tok[1] != '\0')) {
            pilha_push(&pilha, atof(tok));
        } else {
            float b = pilha_pop(&pilha);
            float a = pilha_pop(&pilha);
            switch (tok[0]) {
                case '+': pilha_push(&pilha, a + b); break;
                case '-': pilha_push(&pilha, a - b); break;
                case '*': pilha_push(&pilha, a * b); break;
                case '/': pilha_push(&pilha, a / b); break;
            }
        }
        tok = strtok(NULL, " ");
    }
    return pilha_pop(&pilha);
}

/* avalia_posfixa("1 2 - 4 5 + *") calcula (1-2)*(4+5) = -9 */
```

**Fila circular com vetor (a derivação do Celes, `% N`):**
```c
#include <stdio.h>
#include <stdlib.h>

#define N 5

typedef struct {
    float vet[N];
    int n;      /* quantidade de elementos */
    int ini;    /* índice do próximo a sair */
} Fila;

void fila_cria(Fila *f)    { f->n = 0; f->ini = 0; }
int  fila_vazia(Fila *f)   { return f->n == 0; }

void fila_insere(Fila *f, float v) {
    if (f->n == N) { printf("Fila cheia.\n"); exit(1); }
    int fim = (f->ini + f->n) % N;   /* posição circular do próximo espaço livre */
    f->vet[fim] = v;
    f->n++;
}

float fila_retira(Fila *f) {
    if (fila_vazia(f)) { printf("Fila vazia.\n"); exit(1); }
    float v = f->vet[f->ini];
    f->ini = (f->ini + 1) % N;   /* avança circularmente */
    f->n--;
    return v;
}

int main(void) {
    Fila fila;
    fila_cria(&fila);
    fila_insere(&fila, 1);
    fila_insere(&fila, 2);
    printf("%.0f\n", fila_retira(&fila));  /* 1 — primeiro a entrar, primeiro a sair */
    fila_insere(&fila, 3);
    printf("%.0f\n", fila_retira(&fila));  /* 2 */
    return 0;
}
```
