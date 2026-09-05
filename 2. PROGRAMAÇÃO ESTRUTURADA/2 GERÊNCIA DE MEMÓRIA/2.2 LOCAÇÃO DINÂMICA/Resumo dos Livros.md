# Resumo dos Livros — 2.2 Alocação Dinâmica

## Celes — Introdução a Estruturas de Dados (Cap. 5, "Vetores e alocação dinâmica" — seção "Funções da biblioteca padrão")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

O resumo anterior estava correto na estrutura geral (é de fato o foco central do capítulo), mas o assunto está no **Cap. 5** ("Vetores e alocação dinâmica"), não num capítulo dedicado a ponteiros — Celes trata alocação dinâmica como uma extensão natural de vetores, não como tópico à parte. O livro cobre apenas `malloc`/`free` (não menciona `calloc`/`realloc` nesta seção).

Progressão do capítulo, sempre motivada pelo mesmo exemplo (vetor de notas): `int *v; v = malloc(10*4);` primeiro, depois refinado com `sizeof` para portabilidade — `v = malloc(10*sizeof(int));` — e por fim com o *cast* explícito que o livro recomenda como boa prática (mesmo sendo redundante em C, já que `malloc` retorna `void*`, convertido implicitamente): `v = (int *) malloc(10*sizeof(int));`. Explica que, uma vez alocado, `v` se comporta exatamente como um vetor declarado estaticamente — `v[0]`, `v[1]`, ..., `v[9]` — porque `v` armazena o endereço do primeiro elemento de uma área contígua.

Sobre falha de alocação: se não houver memória livre suficiente, `malloc` retorna `NULL` (definido em `stdlib.h`) — o padrão do livro é sempre checar antes de usar:
```c
v = (int*) malloc(10*sizeof(int));
if (v == NULL) {
    printf("Memoria insuficiente.\n");
    exit(1);
}
```
Para liberar, `free(v);` — com dois avisos explícitos do livro: só se pode passar para `free` um endereço que **tenha sido alocado dinamicamente**, e **não se pode acessar a memória depois de liberada**.

Um ponto que o livro faz questão de deixar visualmente claro (com diagrama de memória, Fig. 5.3) é a diferença entre a **variável ponteiro** `v` em si (que fica na pilha, como qualquer variável local) e a **área para a qual `v` aponta** (que fica na memória livre/heap) — os dois espaços são liberados por mecanismos diferentes: `v` some automaticamente quando a função termina, mas a área apontada só é liberada com `free` explícito (ou nunca, se esquecido — vazamento de memória).

O capítulo fecha reescrevendo o programa de média/variância para alocar `v` dinamicamente com base no `n` lido do usuário — e observa que as funções auxiliares `media`/`variancia` (que recebem `float *v`) **não precisam de nenhuma alteração**, porque, do ponto de vista de uma função que recebe um ponteiro, é irrelevante se o vetor original foi alocado estática ou dinamicamente.

## K&R — C: A Linguagem de Programação (Cap. 5 / Apêndice)
Diferente das edições posteriores de C (que popularizaram `malloc`/`free`), esta edição do K&R introduz o tema pedagogicamente escrevendo um "alocador de memória elementar" próprio, chamado `aloca`/`libera` (seção 5.4, Aritmética com Endereços), e depois aponta que "a biblioteca padrão de C fornece funções análogas" — no vocabulário desta edição, `calloc` e `cfree`. O trecho descreve: *"Existem duas rotinas: `aloca(n)` que retorna um apontador `p` para `n` caracteres consecutivos livres, [...] `libera(p)` libera a área adquirida"*. A implementação mostrada usa um vetor estático interno (`bufaloc`) como reserva de memória e um ponteiro (`aaloc`) que marca o próximo espaço livre:

```c
#define NULL 0
#define TAMALOC 1000

static char bufaloc[TAMALOC];      /* espaço para aloca */
static char *aaloc = bufaloc;      /* próxima posição livre */

char *aloca(n)                     /* retorna um apontador para n caracteres */
int n;
{
    if (aaloc + n <= bufaloc + TAMALOC) {
        aaloc += n;
        return (aaloc - n);        /* apontador antigo */
    } else
        return (NULL);             /* não tem espaço */
}
```

O texto explica que o valor `NULL` (zero) é usado como sinal de falha porque "C garante que nenhum apontador apontando para um objeto válido terá valor zero" — por isso é seguro reservar zero como código de erro, e por isso todo código que chama um alocador deve checar o retorno antes de usar o ponteiro.

Mais adiante, na seção sobre a biblioteca padrão (Gerenciamento de Memória), o livro apresenta a versão "de verdade": `calloc(n, sizeof(objeto))` — "retorna um apontador para `n` objetos do tamanho especificado, ou `NULL` se o pedido não pode ser satisfeito. O armazenamento é inicializado com o valor zero" — e `cfree(p)`, que "libera o espaço apontado por `p`, onde `p` foi obtido por uma chamada a `calloc`", com o aviso de que "é um erro sério liberar alguma coisa não obtida com `calloc`". O livro ainda menciona que o Capítulo 8 mostra a implementação interna de um alocador como esse, com blocos que podem ser liberados em qualquer ordem (ao contrário do `aloca`/`libera` de exemplo, que funciona como uma pilha).

## Síntese
Os dois livros abordam exatamente o mesmo mecanismo por ângulos complementares: K&R constrói um alocador do zero para desmistificar como `malloc`/`calloc` funcionam por baixo (um bloco de memória e um ponteiro de controle), enquanto Celes foca no uso correto e idiomático de `malloc`/`free` já prontos, com bastante ênfase visual (diagramas de memória) na diferença entre o ponteiro em si (na pilha) e a área para a qual ele aponta (no heap) — e no par de erros que decorrem disso: esquecer o `free` (vazamento) e acessar a memória depois de liberada.

## Exemplos em C

**A progressão do Celes até a forma idiomática final:**
```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    float *v;

    printf("Quantos valores? ");
    scanf("%d", &n);

    v = (float *) malloc(n * sizeof(float));  /* sizeof: portável entre máquinas/compiladores */
    if (v == NULL) {
        printf("Memoria insuficiente.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        scanf("%f", &v[i]);      /* v[i] funciona igual a um vetor estático */

    float soma = 0;
    for (int i = 0; i < n; i++)
        soma += v[i];
    printf("Média: %.2f\n", soma / n);

    free(v);        /* devolve a área ao sistema */
    /* v ainda existe como variável, mas NÃO deve mais ser desreferenciado (v[i], *v) */

    return 0;
}
```

**Os dois erros clássicos que o Celes alerta (NÃO fazer isto):**
```c
/* 1) vazamento de memória: aloca e nunca libera */
void vazamento(void) {
    int *p = malloc(100 * sizeof(int));
    /* ... usa p ... */
    /* esqueceu o free(p) — a cada chamada desta função, 400 bytes "somem" até o fim do programa */
}

/* 2) uso após free (dangling pointer / use-after-free) */
int *p = malloc(sizeof(int));
*p = 42;
free(p);
printf("%d\n", *p);   /* undefined behavior: memória já devolvida ao sistema */
```
