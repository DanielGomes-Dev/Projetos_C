# Resumo dos Livros — 1.7 Passagem de Parâmetros por Valor e por Referência

## Celes — Introdução a Estruturas de Dados (Cap. 4, "Funções" — seções "Ponteiro de variáveis" e "Passando ponteiros para funções")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Confirmado: este é de fato o ponto mais insistente e mais detalhado do livro (mais até que o K&R nessa seção específica), construído em 3 passos com exemplos completos.

**Passo 1 — o problema**: uma função `somaprod(int a, int b, int c, int d)` que tenta calcular soma e produto escrevendo em `c` e `d` (parâmetros comuns, não ponteiros) é apresentada como **"versão errada"** explícita no livro — os parâmetros `c`/`d` são cópias locais; alterá-los dentro da função não afeta as variáveis `s`/`p` do chamador, que continuam com "lixo" (não inicializadas).

**Passo 2 — variáveis do tipo ponteiro**: introduz `int *p;` (declara um ponteiro para `int`) e os dois operadores unários: `&` ("endereço de") e `*` ("conteúdo de", também chamado de-referência). Insiste, com um exemplo de código deliberadamente incorreto (`int *p; *p = 3;` sem `p` ter sido inicializado), que **só se pode escrever através de um ponteiro depois de ele apontar para um endereço válido** — escrever em um ponteiro "lixo" é undefined behavior que "às vezes funciona", o que o livro chama de um dos erros mais perigosos de C.

**Passo 3 — a versão correta de `somaprod`**: `void somaprod(int a, int b, int *p, int *q) { *p = a+b; *q = a*b; }`, chamada como `somaprod(3, 5, &s, &p);` — a função recebe os *endereços* de `s`/`p` e escreve nesses endereços via `*p`/`*q`. Reforça com um segundo exemplo canônico, a função `troca`, praticamente idêntica ao exemplo do K&R:
```c
void troca(int *px, int *py) {
    int temp = *px;
    *px = *py;
    *py = temp;
}
```
chamada como `troca(&a, &b);`. O livro fecha a seção com a frase-chave que conecta tudo isso ao tópico anterior (1.4): **"Agora fica explicado por que passamos o endereço das variáveis para a função `scanf`"** — `scanf` é, ela mesma, apenas mais um exemplo desse padrão.

## K&R — C: A Linguagem de Programação (Cap. 1, seção 1.8; Cap. 5, seção 5.2)
A seção 1.8 (Argumentos — Chamada por Valor) introduz o conceito logo no primeiro capítulo: em C, todo argumento é passado "por valor" — a função chamada recebe uma **cópia** do valor numa variável temporária, não o endereço do original, ao contrário de Fortran e PL/1, que usam "chamada por referência". A consequência direta é que uma função não pode alterar uma variável do chamador através de um argumento comum; só pode alterar sua própria cópia. O livro trata isso como vantagem, não desvantagem, pois permite tratar argumentos como variáveis locais convenientemente pré-inicializadas (exemplo: a função `pot` usa o argumento `n` como contador, decrementando-o livremente sem afetar o valor original do chamador). Já fica adiantado ali que, quando é necessário alterar uma variável do chamador, "quem chama deve fornecer o endereço da variável... e a função chamada deve declarar que o argumento é um apontador" — e que um nome de vetor, ao ser passado como argumento, já é o endereço do seu início (por isso vetores se comportam como se fossem passados por referência).

A seção 5.2 (Apontadores e Argumentos de Funções) desenvolve isso com o exemplo canônico `troca`: uma primeira tentativa, `troca(x, y)` recebendo `int x, y`, é marcada como **ERRADO** no próprio livro, porque troca apenas os valores locais e não afeta `a`/`b` do chamador. A versão correta passa os endereços — `troca(&a, &b);` — e a função recebe ponteiros: `troca(int *ax, int *ay) { int temp = *ax; *ax = *ay; *ay = temp; }`, usando o operador de indireção `*` para ler e escrever através do ponteiro. O livro generaliza o padrão com a função `leint`, que "retorna" um valor através de um argumento-ponteiro (`int *an`, usado internamente como `*an = 10 * *an + c - '0';`) justamente porque o valor de retorno normal da função já está ocupado sinalizando fim de arquivo — mostrando por que ponteiros como parâmetro são o mecanismo de C para uma função devolver mais de um resultado.

## Síntese
Não existe "passagem por referência" nativa em C: existe apenas passagem por valor, e o efeito de referência é simulado passando um ponteiro (o endereço de uma variável, obtido com `&`) e desreferenciando-o (`*`) dentro da função — vetores são o único caso em que isso acontece automaticamente. Celes e K&R convergem quase literalmente no mesmo exemplo (`troca`/`swap` com dois ponteiros `int *`) — o que é um bom sinal de que esse é *o* exemplo canônico do assunto em C, não uma escolha arbitrária de um dos dois autores.

## Exemplos em C

**A versão errada e a versão correta de `somaprod`, lado a lado:**
```c
#include <stdio.h>

/* ERRADO: c e d são cópias locais; alterá-las não afeta s e p do chamador */
void somaprod_errado(int a, int b, int c, int d) {
    c = a + b;
    d = a * b;
}

/* CORRETO: p e q são ponteiros; *p e *q escrevem no endereço original */
void somaprod(int a, int b, int *p, int *q) {
    *p = a + b;
    *q = a * b;
}

int main(void) {
    int s, p;

    somaprod_errado(3, 5, s, p);
    printf("errado:  s e p continuam lixo (não inicializados)\n");

    somaprod(3, 5, &s, &p);
    printf("correto: soma = %d, produto = %d\n", s, p);

    return 0;
}
```

**`troca` (swap) — o exemplo canônico de passagem por referência via ponteiro:**
```c
#include <stdio.h>

void troca(int *px, int *py) {
    int temp = *px;
    *px = *py;
    *py = temp;
}

int main(void) {
    int a = 5, b = 7;
    troca(&a, &b);
    printf("a=%d b=%d\n", a, b);   /* a=7 b=5 */
    return 0;
}
```

**Por que `scanf` é só mais uma aplicação do mesmo padrão:**
```c
int x;
scanf("%d", &x);   /* mesma ideia de somaprod/troca: passa o ENDEREÇO
                       para que a função escreva de volta na variável do chamador */
```
