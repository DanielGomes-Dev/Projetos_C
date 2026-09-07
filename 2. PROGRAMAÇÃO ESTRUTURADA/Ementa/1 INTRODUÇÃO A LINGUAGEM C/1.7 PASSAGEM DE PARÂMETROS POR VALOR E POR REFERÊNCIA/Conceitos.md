# Conceitos — Passagem de Parâmetros por Valor e por Referência

## A ideia em uma frase

Em C **tudo é passado por valor** (a função recebe uma cópia); para uma função conseguir
alterar uma variável do chamador, você passa o **endereço** dela (um ponteiro) e a função
escreve através desse endereço.

## O conceito

Quando você chama `f(x)`, a função recebe uma **cópia** de `x`. Mexer nessa cópia não
toca o `x` original. Isso é "passagem por valor" e é a única que C tem.

Para simular "passagem por referência":

1. quem chama passa `&x` (o endereço de `x`);
2. o parâmetro é declarado como ponteiro (`int *p`);
3. dentro da função, `*p` lê e escreve **na variável original**.

Isso é exatamente o que `scanf("%d", &x)` faz: passa o endereço para a função poder
gravar o valor lido de volta em `x`.

**Exceção prática:** o nome de um vetor já *é* um endereço. Ao passar `v` para uma função,
você passa o endereço do primeiro elemento — então a função consegue alterar os elementos
do vetor original sem você escrever `&`.

## Exemplos passo a passo

### Exemplo 1 — a versão errada e a certa

```c
#include <stdio.h>

// ERRADO: c e d são cópias; a função não afeta as variáveis do main
void somaprod_errado(int a, int b, int c, int d) {
    c = a + b;
    d = a * b;
}

// CERTO: p e q são endereços; *p e *q escrevem no main
void somaprod(int a, int b, int *p, int *q) {
    *p = a + b;
    *q = a * b;
}

int main(void) {
    int s = 0, pr = 0;

    somaprod_errado(3, 5, s, pr);
    printf("errado:  s=%d pr=%d\n", s, pr);   // s=0 pr=0 (não mudou)

    somaprod(3, 5, &s, &pr);
    printf("certo:   s=%d pr=%d\n", s, pr);   // s=8 pr=15
    return 0;
}
```

**Passo a passo da versão certa:**

1. `somaprod(3, 5, &s, &pr)` passa `a=3`, `b=5`, `p` = endereço de `s`, `q` = endereço de `pr`.
2. `*p = a + b;` → grava `8` no endereço de `s`. Agora `s` vale 8.
3. `*q = a * b;` → grava `15` no endereço de `pr`.
4. A função retorna; `s` e `pr` de `main` ficaram preenchidos.

### Exemplo 2 — `troca` (swap), o exemplo canônico

```c
#include <stdio.h>

void troca(int *px, int *py) {
    int tmp = *px;     // valor apontado por px
    *px = *py;         // grava no lugar de px o valor de py
    *py = tmp;
}

int main(void) {
    int a = 5, b = 7;
    troca(&a, &b);
    printf("a=%d b=%d\n", a, b);   // a=7 b=5
    return 0;
}
```

Com `void troca(int x, int y)` (sem ponteiros), só as cópias `x` e `y` trocariam; `a` e
`b` continuariam `5` e `7`.

### Exemplo 3 — vetor: alterado sem `&`

```c
#include <stdio.h>

void zera(int n, int *v) {     // 'int v[]' também vale; é a mesma coisa
    for (int i = 0; i < n; i++)
        v[i] = 0;
}

int main(void) {
    int a[4] = {1, 2, 3, 4};
    zera(4, a);                 // passa 'a' sem &: nome de vetor já é endereço
    printf("%d %d %d %d\n", a[0], a[1], a[2], a[3]);   // 0 0 0 0
    return 0;
}
```

**O que observar:** `zera` alterou o vetor original de `main`. Isso acontece porque o que
foi passado foi o endereço de `a[0]`, não uma cópia dos 4 inteiros.

### Exemplo 4 — retornar mais de um valor por ponteiro

```c
#include <stdio.h>

// devolve quociente pelo return e resto pelo ponteiro
int divide(int a, int b, int *resto) {
    *resto = a % b;
    return a / b;
}

int main(void) {
    int r;
    int q = divide(17, 5, &r);
    printf("17 = 5*%d + %d\n", q, r);   // 17 = 5*3 + 2
    return 0;
}
```

## Erros comuns / pegadinhas

- **Passar a variável em vez do endereço** quando quer que a função a altere —
  `troca(a, b)` em vez de `troca(&a, &b)`.
- **Passar o endereço mas esquecer o `*` dentro da função** — `px = *py;` altera o
  ponteiro local, não a variável apontada.
- **Passar `&` num nome de vetor** — `f(&v)` tem tipo diferente de `f(v)`; use `v`.
- **Retornar o endereço de uma variável local** — ela deixa de existir no `return`.
- **Achar que existe "passagem por referência" em C** — não existe; é sempre por valor,
  com ponteiros simulando o resto.

## Resumo / checklist

- [ ] Sei que C só tem passagem por valor
- [ ] Sei o trio: quem chama passa `&x`, o parâmetro é `tipo *p`, a função usa `*p`
- [ ] Entendo por que `scanf` pede `&`
- [ ] Sei por que um vetor passado a uma função pode ser alterado sem `&`
- [ ] Sei usar um parâmetro-ponteiro para uma função "devolver" mais de um valor
