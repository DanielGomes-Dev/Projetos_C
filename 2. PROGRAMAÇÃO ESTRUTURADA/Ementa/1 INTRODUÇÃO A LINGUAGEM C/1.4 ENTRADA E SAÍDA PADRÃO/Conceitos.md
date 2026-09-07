# Conceitos — Entrada e Saída Padrão

> Para a referência completa de especificadores, largura de campo, `%[...]`, buffer
> residual e `fgets`+`sscanf`, veja o [Guia - scanf e printf](<Guia - scanf e printf.md>).
> Este arquivo cobre só o conceito e os exemplos essenciais.

## A ideia em uma frase

C não tem comandos de entrada/saída na linguagem: você usa funções da biblioteca
`<stdio.h>` — `printf` para escrever, `scanf` para ler — e a diferença central é que
`scanf` precisa do **endereço** da variável para poder preenchê-la.

## O conceito

- **Saída:** `printf(formato, valores...)`. O `formato` é um texto com "buracos" marcados
  por `%`; cada buraco é preenchido, na ordem, por um valor da lista.
- **Entrada:** `scanf(formato, endereços...)`. Como C passa tudo por cópia, a única forma
  de `scanf` alterar a sua variável é receber o **endereço** dela — daí o `&`.
- **Caractere a caractere:** `getchar()` lê o próximo caractere e devolve como `int`;
  `putchar(c)` escreve um. `getchar` devolve `int` (não `char`) porque precisa
  representar todo caractere **mais** o valor `EOF` (fim de entrada).

Especificadores mais usados:

| | `printf` | `scanf` |
|---|---|---|
| `int` | `%d` | `%d` (endereço) |
| `unsigned` | `%u` | `%u` |
| `float` | `%f` | `%f` |
| `double` | `%f` (serve para os dois) | `%lf` (**o `l` é obrigatório**) |
| `char` | `%c` | `%c` (não pula espaços) |
| string | `%s` | `%s` (para no espaço; use largura: `%29s`) |

## Exemplos passo a passo

### Exemplo 1 — ler, calcular, imprimir formatado

**Problema:** ler uma altura em metros e convertê-la em pés e polegadas.

```c
#include <stdio.h>

int main(void) {
    float metros, polegadas;
    int pes;

    printf("Altura em metros: ");
    scanf("%f", &metros);              // &: passa o endereço de 'metros'

    float cm = metros * 100.0f;
    pes = (int) (cm / 30.48f);         // 1 pé = 30,48 cm
    polegadas = (cm - pes * 30.48f) / 2.54f;  // 1 pol = 2,54 cm

    printf("%d pes e %.1f polegadas\n", pes, polegadas);
    return 0;
}
```

**Passo a passo (entrada `1.80`):** `cm = 180`. `pes = (int)(180 / 30.48) = (int) 5.90 = 5`.
`polegadas = (180 - 5*30.48) / 2.54 = 27.6 / 2.54 ≈ 10.9`. Saída: `5 pes e 10.9 polegadas`.

> Exemplo adaptado de Celes (cap. 2).

### Exemplo 2 — o especificador certo para cada tipo

```c
#include <stdio.h>

int main(void) {
    int idade;
    double salario;
    char inicial;
    char cidade[30];

    printf("Idade: ");    scanf("%d", &idade);
    printf("Salario: ");  scanf("%lf", &salario);   // double: %lf, não %f
    printf("Inicial: ");  scanf(" %c", &inicial);   // espaço antes de %c descarta o \n
    printf("Cidade: ");   scanf("%29s", cidade);    // largura: evita estouro de buffer

    printf("%d anos, R$ %.2f, '%c', %s\n", idade, salario, inicial, cidade);
    return 0;
}
```

**O que observar:**

- `scanf("%f", &salario)` num `double` grava lixo — `%lf` é obrigatório para `double`.
- Depois de ler um número, sobra um `\n` no buffer. O `%c` seguinte leria esse `\n`; o
  espaço em `" %c"` pula qualquer branco pendente.
- `cidade` já é um endereço (nome de vetor), por isso vai sem `&`.

### Exemplo 3 — copiar a entrada caractere a caractere

```c
#include <stdio.h>

int main(void) {
    int c;                          // int, não char: precisa caber o EOF
    while ((c = getchar()) != EOF)   // lê um caractere e testa no mesmo passo
        putchar(c);
    return 0;
}
```

**Passo a passo:** cada volta lê um caractere para `c`. Se for `EOF` (fim do arquivo /
Ctrl+Z no Windows, Ctrl+D no Linux), o laço para. Senão, escreve o caractere e repete.
Os parênteses em `(c = getchar())` são obrigatórios: sem eles, `c = getchar() != EOF`
gravaria `0` ou `1` em `c`.

## Erros comuns / pegadinhas

- **Esquecer o `&` em `scanf`** para tipos escalares. `scanf("%d", n)` compila e quebra.
  (Vetor/string vão sem `&`.)
- **`%f` para `double` no `scanf`.** Use `%lf`.
- **`%c` logo depois de `%d`/`%f`** sem tratar o `\n` residual — lê o `\n`, não espera o
  usuário. Use `" %c"`.
- **`%s` sem largura** — estoura o buffer se o usuário digitar demais. Use `%29s` para um
  `char[30]`.
- **Guardar `getchar()` num `char`** — o `EOF` deixa de ser distinguível.
- **`fflush(stdin)`** para "limpar o teclado" — comportamento indefinido; não use.
- **Ignorar o retorno de `scanf`** — ele devolve quantos itens leu; se não checar, entrada
  inválida vira loop infinito ou lixo.

## Resumo / checklist

- [ ] Sei por que `scanf` precisa de `&` e `printf` não
- [ ] Uso `%lf` para ler `double`
- [ ] Sei tratar o `\n` residual antes de um `%c`
- [ ] Uso largura em `%s` (`%29s`)
- [ ] Guardo `getchar()` em `int` e sei o que é `EOF`
- [ ] Checo o valor de retorno de `scanf`
