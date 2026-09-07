# Resumo dos Livros — 1.3 Operadores Aritméticos, Condicionais, Lógicos e de Atribuição

## Celes — Introdução a Estruturas de Dados (Cap. 2, "Expressões" — seções "Operadores" e "Precedência e ordem de avaliação")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Ao contrário do que o placeholder anterior desta nota sugeria, Celes **dedica uma seção inteira e bem detalhada** aos operadores — não é um tratamento superficial.

**Aritméticos** (`+ - * / %`, mais o `-` unário): o livro enfatiza que "a operação é feita na precisão dos operandos" — `5/2` vale `2` (divisão inteira trunca), mas `5.0/2.0` vale `2.5`. Traz um exemplo didático que mistura os dois casos na mesma sequência: `int a; double b, c; a = 3.5; b = a/2.0; c = 1/3 + b;` resulta em `a=3`, `b=1.5`, `c=1.5` — o ponto sendo que `1/3` (dois `int`) já trunca para `0` **antes** de somar com `b`, mesmo `c` sendo `double`. `%` (módulo) só aceita operandos inteiros; o livro usa `x % 2 == 0` como o teste canônico de paridade.

**Atribuição**: uma atribuição em C é uma **expressão com valor** (o valor atribuído), o que permite `y = x = 5;` (avalia da direita para a esquerda). Cobre os operadores compostos `+= -= *= /= %=`, com a observação importante de que `var op expr;` equivale a `var = var op (expr);` **com parênteses implícitos em `expr`** — por isso `x *= y + 1;` equivale a `x = x * (y + 1)`, não a `x = x * y + 1`.

**Incremento/decremento** (`++`/`--`): explica a diferença prefixado vs. pós-fixado com o exemplo `x = n++;` (atribui o valor *antes* do incremento) vs. `x = ++n;` (atribui *depois*), e destaca que só podem ser aplicados a variáveis (`x = (i+1)++;` é ilegal).

**Relacionais e lógicos**: `< > <= >= == !=` e `&& || !`. Ponto que o livro faz questão de frisar: **C não tem tipo booleano** — `0` é falso, qualquer valor diferente de zero é verdadeiro, e o resultado de uma comparação é sempre `0` ou `1`. Documenta o curto-circuito de `&&`/`||` (avaliação da esquerda para a direita, parando assim que o resultado já é conhecido) com um exemplo concreto: em `a = (c<20) || (d>c);`, se `(c<20)` for verdadeiro, `(d>c)` nem chega a ser avaliada.

**`sizeof`**: apresentado nesta mesma seção (não como operador à parte) — `sizeof(float)` ou `sizeof(variável)`, retornando o tamanho em bytes.

**Conversão de tipo**: reforça a promoção automática em expressões mistas (`3/1.5` promove o `3` para `double`) e em atribuições (`float a = 3;` converte `3` para `3.0F`), e apresenta o *cast* explícito, `(int) 3.5`, notando que ele evita os avisos do compilador que a conversão implícita geraria.

Fecha com uma **tabela de precedência e associatividade** (Tabela 2.3) equivalente em conteúdo à do K&R, incluindo a mesma armadilha de operadores bit-a-bit (`&`) terem precedência menor que operadores relacionais/de igualdade.

## K&R — C: A Linguagem de Programação (Cap. 2, seções 2.5-2.6 e 2.11-2.12)
A seção 2.5 (Operadores Aritméticos) define os binários `+`, `-`, `*`, `/` e o operador módulo `%`, e nota que existe um `-` unário mas não um `+` unário. A divisão inteira trunca a parte fracionária; `%` é o resto (zero se a divisão for exata) e não se aplica a `float`/`double`. Um exemplo clássico do livro é o teste de ano bissexto: `if (ano % 4 == 0 && ano % 100 != 0 || ano % 400 == 0)`. Os operadores `+`/`-` têm a mesma precedência, menor que `*`/`/`/`%`, que por sua vez é menor que a do menos unário — todos associam da esquerda para a direita, mas a ordem de avaliação de operandos não é garantida (o compilador pode reordenar `a + (b + c)` como `(a + b) + c`).

A seção 2.6 (Operadores Relacionais e Lógicos) cobre `>`, `>=`, `<`, `<=`, `==`, `!=`, e os conectores lógicos `&&` e `||`. O ponto central é que expressões com `&&`/`||` são avaliadas da esquerda para a direita e a avaliação **para assim que o resultado já é conhecido** (curto-circuito) — propriedade explorada no idioma clássico `for (i = 0; i < lim-1 && (c = getchar()) != '\n' && c != EOF; ++i)`, onde a ordem dos testes importa: primeiro verifica se há espaço no vetor, só depois lê um novo caractere. Operadores relacionais têm menor precedência que os aritméticos; `&&` tem precedência maior que `||`, e ambos menor que os relacionais — por isso `(c = getchar()) != '\n'` precisa de parênteses (já que `!=` tem precedência maior que `=`). O operador unário `!` inverte verdadeiro/falso.

A seção 2.11 (Expressões Condicionais) apresenta o operador ternário `e1 ? e2 : e3`: `e1` é avaliada primeiro e, dependendo do resultado, apenas `e2` ou apenas `e3` é avaliada — nunca as duas. Exemplo do livro: `z = (a > b) ? a : b;` para calcular o máximo. A seção 2.12 (Precedência e Ordem de Avaliação) fecha o capítulo com a tabela completa de precedência e associatividade de todos os operadores de C, observando que operadores lógicos bit-a-bit (`&`, `|`) têm precedência **menor** que `==`/`!=`, uma armadilha comum que exige parênteses em testes de máscara de bits como `if ((x & MASCARA) == 0)`.

## Síntese
O que realmente precisa ficar automático é a tabela de precedência (sobretudo a armadilha de `&`/`|` abaixo de `==`/`!=`, e de `!=` acima de `=`) e o curto-circuito de `&&`/`||`, que é usado ativamente para evitar acessos inválidos (como ler além do fim de um vetor). Os dois livros convergem quase ponto a ponto — Celes cobre até a mesma armadilha de precedência `&` vs. `==` que o K&R usa como exemplo — mas o K&R vai além com o ternário (`?:`) e mais idiomas de curto-circuito aplicados a I/O de caracteres.

## Exemplos em C

**Precisão dos operandos (o exemplo do Celes, expandido):**
```c
#include <stdio.h>

int main(void) {
    int a = 3.5;              /* trunca na atribuição: a vale 3 */
    double b = a / 2.0;       /* a promovido a double: b vale 1.5 */
    double c = 1 / 3 + b;     /* 1/3 é divisão inteira = 0, ANTES de somar: c vale 1.5 */

    printf("a=%d b=%.1f c=%.1f\n", a, b, c);

    printf("5/2 = %d   (divisão inteira trunca)\n", 5 / 2);
    printf("5.0/2.0 = %.1f (divisão real)\n", 5.0 / 2.0);
    printf("7 %% 3 = %d (resto da divisão)\n", 7 % 3);

    return 0;
}
```

**Pré-incremento vs. pós-incremento (fonte comum de bug sutil):**
```c
#include <stdio.h>

int main(void) {
    int n = 5, x;

    x = n++;   /* x recebe 5 (valor ANTES do incremento); n passa a valer 6 */
    printf("x=%d n=%d\n", x, n);

    n = 5;
    x = ++n;   /* n é incrementado PRIMEIRO; x recebe 6 */
    printf("x=%d n=%d\n", x, n);

    return 0;
}
```

**Curto-circuito evitando acesso inválido a vetor:**
```c
#include <stdio.h>

int main(void) {
    int v[5] = {10, 20, 30, 40, 50};
    int i = 0, alvo = 999;

    /* se i chegasse a 5, v[i] leria fora do vetor — mas o && nunca avalia
       v[i] == alvo quando i < 5 já é falso, então a busca é segura */
    while (i < 5 && v[i] != alvo)
        i++;

    if (i < 5)
        printf("Encontrado no índice %d\n", i);
    else
        printf("Não encontrado\n");

    return 0;
}
```

**Operador ternário e atribuição composta:**
```c
#include <stdio.h>

int main(void) {
    int a = 7, b = 12;
    int maior = (a > b) ? a : b;
    printf("Maior: %d\n", maior);

    int x = 10;
    x *= 2 + 1;   /* equivale a x = x * (2 + 1) = 30, NÃO x = x*2 + 1 */
    printf("x = %d\n", x);

    return 0;
}
```
