# Resumo dos Livros — 1.5 Estruturas de Seleção e Repetição

## Celes — Introdução a Estruturas de Dados (Cap. 3, "Controle de Fluxo")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Ao contrário do que o placeholder anterior sugeria, Celes dedica um **capítulo inteiro** a isso, estruturado em torno de um único exemplo evolutivo: o cálculo do fatorial, reimplementado 3 vezes (uma por construção de laço), o que o torna especialmente didático para comparar `while`/`for`/`do-while` lado a lado.

**`if`/`else`**: a forma geral com chaves opcionais quando o bloco tem um único comando; o livro é explícito que a indentação é estilo, não sintaxe, e mostra o mesmo aninhamento com dois estilos de chave (mesma linha vs. linha seguinte) — só para reforçar que ambos são igualmente válidos, desde que consistentes.

**`while`** (versão 1 do fatorial): teste no início, então o corpo pode nunca executar. **`for`** (versão 2): o livro mostra explicitamente a equivalência `for (init; teste; incr) {...}` ⟺ `init; while (teste) { ...; incr; }` — a mesma equivalência do K&R. **`do-while`** (versão 3): teste no fim, corpo executa ao menos 1 vez — usado para **validar entrada do usuário em loop** (`do { scanf(...); } while (n < 0);`, repetindo a pergunta enquanto o valor for inválido), um uso prático que o K&R não enfatiza tanto.

**`break`/`continue`**: mesmo comportamento do K&R, mas com um alerta extra e muito valioso — um exemplo explícito de **bug real** com `continue` dentro de `while`: se o incremento da variável de controle vier *depois* do `continue` no corpo do laço, o `continue` pula esse incremento e o laço **nunca termina**. O livro rotula o código de "INCORRETO" e explica a causa exata. (Em `for`, isso não acontece, porque a expressão de incremento roda fora do corpo do laço.)

**`switch`**: mesma sintaxe `case`/`break`/`default` do K&R, ilustrada com uma calculadora de quatro operações que lê um caractere de operador (`'+'`, `'-'`, `'*'`, `'/'`) via `scanf(" %c %c %c", ...)` e usa `switch` sobre esse `char`.

## K&R — C: A Linguagem de Programação (Cap. 3, "Fluxo de Controle")
O capítulo abre (3.1) esclarecendo que em C o ponto-e-vírgula é terminador de comando (não separador, como em ALGOL), e que chaves `{ }` agrupam comandos e declarações num bloco sintaticamente equivalente a um único comando. A seção 3.2 (If-Else) formaliza `if (expressão) comando-1 else comando-2`, com a regra de que um `else` sempre se associa ao `if` mais próximo sem `else` — origem do clássico "dangling else", que o livro ilustra com um exemplo onde a indentação engana o leitor mas não o compilador, recomendando chaves explícitas para desambiguar. A seção 3.3 (Else-If) descreve a cadeia `if / else if / else if / ... / else` como a forma mais geral de decisão múltipla, exemplificada com uma pesquisa binária (`pesq_binaria`) que decide entre "menor", "maior" ou "igual" a cada passo.

A seção 3.4 (Switch) apresenta `switch (expressão) { case c1: ...; break; ... default: ...; }`, reescrevendo o programa de contagem de dígitos do Capítulo 1 com `switch`. O ponto crítico é que a execução "cai" (*fall-through*) de um `case` para o próximo se não houver `break` — às vezes desejável (múltiplos `case` para uma ação, como espaço/tab/nova-linha caindo no mesmo bloco), mas geralmente uma fonte de bugs, por isso o livro recomenda sempre um `break` ao final de cada caso, inclusive o `default`.

A seção 3.5 (Laços — While e For) mostra que `for (e1; e2; e3) comando` é equivalente a `e1; while (e2) { comando; e3; }`, e que qualquer das três expressões pode ser omitida (`for (;;)` é um laço infinito). O critério de escolha entre `while` e `for` é estilístico: `for` é preferido quando há inicialização e reinicialização simples e visíveis no topo do laço. A seção 3.6 (Do-while) introduz o único laço de C que testa a condição **no fim**, garantindo ao menos uma execução do corpo — usado no exemplo `itoa`, que gera dígitos na ordem inversa. As seções 3.7-3.8 cobrem `break` (sai imediatamente do laço ou `switch` mais interno) e `continue` (pula para a próxima iteração, sem sair do laço). A seção 3.9 (Goto e Rótulos) apresenta o `goto` como recurso "infinitamente abusável", útil essencialmente só para abandonar laços aninhados profundamente de uma vez, e que o próprio livro evita usar.

## Síntese
O núcleo prático é: `if/else-if/switch` para decisão, `while`/`for`/`do-while` para repetição (escolhidos por legibilidade, não por poder expressivo — são intercambiáveis), e `break`/`continue` para controlar o fluxo dentro de um laço sem recorrer a `goto`. Os dois livros se complementam bem aqui: Celes usa um único exemplo (fatorial) reimplementado nas 3 formas de laço para deixar a equivalência bem concreta, e traz o alerta prático mais valioso — o `continue` que "pula" o incremento e trava o `while` num loop infinito; o K&R (Capítulo 3 completo) é a referência formal para a regra do "else mais próximo" (dangling else) e o *fall-through* do `switch`.

## Exemplos em C

**As 3 formas de laço, lado a lado (o mesmo exercício que o Celes faz com o fatorial), aqui somando 1 a N:**
```c
#include <stdio.h>

int main(void) {
    int n = 5, i, soma;

    /* while: testa ANTES — pode não executar nenhuma vez */
    soma = 0; i = 1;
    while (i <= n) { soma += i; i++; }
    printf("while: soma = %d\n", soma);

    /* for: inicialização, teste e incremento juntos no cabeçalho */
    soma = 0;
    for (i = 1; i <= n; i++) soma += i;
    printf("for:   soma = %d\n", soma);

    /* do-while: testa DEPOIS — executa pelo menos 1 vez, mesmo se n=0 */
    soma = 0; i = 1;
    do { soma += i; i++; } while (i <= n);
    printf("do-while: soma = %d\n", soma);

    return 0;
}
```

**`do-while` para validar entrada (o padrão que o Celes usa, mais idiomático que o K&R para este caso):**
```c
#include <stdio.h>

int main(void) {
    int n;

    do {
        printf("Digite um valor inteiro não negativo: ");
        scanf("%d", &n);
    } while (n < 0);

    printf("Você digitou %d\n", n);
    return 0;
}
```

**O bug do `continue` em `while` (reproduzindo o alerta do Celes — NÃO fazer isto):**
```c
/* INCORRETO: loop infinito */
int i = 0;
while (i < 10) {
    if (i == 5) continue;   /* pula o resto do corpo, INCLUSIVE o i++ abaixo */
    printf("%d ", i);
    i++;                     /* nunca executa quando i == 5 -> i trava em 5 para sempre */
}
```
```c
/* CORRETO: incrementa antes do continue poder pulá-lo, ou usa for (onde o incremento
   roda fora do corpo, imune a este bug) */
for (int i = 0; i < 10; i++) {
    if (i == 5) continue;
    printf("%d ", i);
}
```

**`switch` (calculadora de 4 operações, no espírito do exemplo do Celes):**
```c
#include <stdio.h>

int main(void) {
    float num1, num2, resultado;
    char op;

    printf("Digite: numero op numero (ex: 3.5 + 2)\n");
    scanf("%f %c %f", &num1, &op, &num2);

    switch (op) {
        case '+': resultado = num1 + num2; break;
        case '-': resultado = num1 - num2; break;
        case '*': resultado = num1 * num2; break;
        case '/':
            if (num2 == 0) { printf("Erro: divisão por zero\n"); return 1; }
            resultado = num1 / num2;
            break;
        default:
            printf("Operador inválido\n");
            return 1;
    }
    printf("Resultado: %.2f\n", resultado);
    return 0;
}
```
