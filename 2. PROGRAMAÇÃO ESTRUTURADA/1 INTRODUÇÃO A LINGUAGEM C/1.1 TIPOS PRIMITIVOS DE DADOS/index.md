# 1.1 Tipos Primitivos de Dados

## Resumo
Os tipos primitivos (ou básicos) de C são `char`, `int`, `float` e `double`, com qualificadores `short`, `long`, `signed`/`unsigned` que alteram faixa e representação. Pontos centrais: tamanho em bytes é dependente de implementação (usar `sizeof`), conversões implícitas (promoção de tipos em expressões mistas) e conversões explícitas (`cast`), e a diferença entre precisão de `float` (~6-7 dígitos) e `double` (~15-16 dígitos).

## Onde estudar
- **K&R** — cap. 2, seções 2.1–2.7 (Nomes de Variáveis, Tipos e Tamanhos de Dados, Constantes, Declarações, Conversões Aritméticas).
- **Celes** — cap. 2 ("Expressões"), seções "Variáveis" e "Tipos básicos" — traz a tabela de tamanho×faixa de cada tipo inteiro e a distinção `float`/`double`.

## Checklist
- [ ] Diferenciar `int`, `char`, `float`, `double` e seus qualificadores
- [ ] Saber quando o compilador promove/converte tipos automaticamente
- [ ] Usar `sizeof` corretamente
- [ ] Entender overflow e perda de precisão
- [ ] Saber os sufixos de constante: `L`/`l` (long), `U`/`u` (unsigned), `F`/`f` (float) — sem sufixo, uma constante real é `double` e uma inteira é `int`

## Anotações
- Faixas de valor (regra prática, não garantida pela linguagem — sempre confirme com `sizeof` na máquina/compilador alvo): `char` 1 byte (-128 a 127, ou 0-255 se `unsigned`), `short` 2 bytes, `int`/`long` tipicamente 4 bytes em máquinas modernas de 32/64 bits, `float` 4 bytes (~6-7 dígitos de precisão), `double` 8 bytes (~15-16 dígitos).
- `char` é tecnicamente um tipo inteiro pequeno (armazena o código numérico do caractere, na tabela ASCII/Unicode) — por isso `'A' + 1` é uma expressão válida que resulta em `'B'` (65 + 1 = 66).
- Erro clássico: declarar variável sem inicializar e usar seu valor — o conteúdo é lixo indefinido (bits que já estavam naquele endereço de memória), não necessariamente zero. É a causa raiz clássica de bugs "que funcionam às vezes".

```c
#include <stdio.h>

int main(void) {
    printf("Tamanhos nesta máquina/compilador:\n");
    printf("char:   %zu byte(s)\n", sizeof(char));
    printf("short:  %zu byte(s)\n", sizeof(short));
    printf("int:    %zu byte(s)\n", sizeof(int));
    printf("long:   %zu byte(s)\n", sizeof(long));
    printf("float:  %zu byte(s)\n", sizeof(float));
    printf("double: %zu byte(s)\n", sizeof(double));
    return 0;
}
```
`sizeof` devolve `size_t` (inteiro sem sinal) — o especificador correto em `printf` é `%zu`, não `%d`.
