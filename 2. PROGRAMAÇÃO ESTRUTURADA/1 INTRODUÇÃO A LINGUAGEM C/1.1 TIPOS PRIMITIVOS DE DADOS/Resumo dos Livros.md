# Resumo dos Livros — 1.1 Tipos Primitivos de Dados

## Celes — Introdução a Estruturas de Dados (Cap. 2, "Expressões" — seções "Variáveis" e "Tipos básicos")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Celes define variável como "um espaço na memória do computador para armazenar um determinado tipo de dado" e enfatiza que em C **toda variável precisa ser declarada explicitamente**, com tipo e nome — só se pode armazenar naquele espaço valores do tipo declarado.

Para inteiros, o livro lista `char`, `short int`, `int` e `long int` (com formas curtas `short`/`long`) e apresenta a tabela de tamanho × faixa de valores, já distinguindo com/sem sinal:

| Tipo | Tamanho | Faixa |
|---|---|---|
| `char` | 1 byte | -128 a 127 |
| `unsigned char` | 1 byte | 0 a 255 |
| `short int` | 2 bytes | -32768 a 32767 |
| `unsigned short int` | 2 bytes | 0 a 65535 |
| `long int` | 4 bytes | -2147483648 a 2147483647 |
| `unsigned long int` | 4 bytes | 0 a 4294967295 |

O livro observa que `int` "puro" é mapeado para o inteiro natural da máquina — na prática, 4 bytes na maioria das máquinas modernas de 32/64 bits (mas cita o TurboC/DOS, de 2 bytes, como contraexemplo histórico de que **o tamanho não é garantido pela linguagem**). Para ponto flutuante, `float` (4 bytes, ±10⁻³⁸ a 10³⁸) e `double` (8 bytes, ±10⁻³⁰⁸ a 10³⁰⁸) — o livro recomenda `double` sempre que a precisão numérica for crítica (ex. simulações).

Sobre constantes: uma constante real sem sufixo é `double` por padrão; o sufixo `F`/`f` (`12.45F`) força `float`, evitando o aviso de conversão implícita `double → float` que alguns compiladores emitem. O capítulo também trata explicitamente o perigo de **variáveis não inicializadas** ("lixo") — com o exemplo clássico de um programa que "funciona de manhã e não funciona à tarde" porque o valor indefinido de uma variável, embora sempre exista fisicamente na memória, não é controlado pelo programador.

## Exemplos em C
```c
#include <stdio.h>

int main(void) {
    char letra = 'A';
    short idade = 30;
    int contador = 1000000;
    long populacao = 8000000000L;      /* sufixo L: garante que a constante é long */
    unsigned int codigo = 4000000000u;  /* sufixo u/U: sem sinal */
    float pi_f = 3.14159F;              /* sufixo F: força float, não double */
    double pi_d = 3.14159265358979;

    printf("char:  %d byte(s), valor '%c'\n", (int) sizeof(letra), letra);
    printf("short: %d byte(s), valor %hd\n", (int) sizeof(idade), idade);
    printf("int:   %d byte(s), valor %d\n", (int) sizeof(contador), contador);
    printf("long:  %d byte(s), valor %ld\n", (int) sizeof(populacao), populacao);
    printf("unsigned int: valor %u\n", codigo);
    printf("float: %d byte(s), valor %f\n", (int) sizeof(pi_f), pi_f);
    printf("double:%d byte(s), valor %f\n", (int) sizeof(pi_d), pi_d);

    return 0;
}
```

## K&R — C: A Linguagem de Programação (Cap. 2, seções 2.1-2.7)
Esta faixa do Capítulo 2 é a referência formal de tipos em C. A seção 2.1 (Nomes de Variáveis) estabelece as regras de identificadores: começam por letra (o `_` conta como letra), diferenciam maiúsculas de minúsculas, e só os primeiros 8 caracteres de nomes internos são garantidamente significativos — uma limitação histórica do compilador da época.

A seção 2.2 lista os quatro tipos básicos — `char` (um byte, um caractere), `int` (tamanho natural da máquina), `float` (precisão simples) e `double` (precisão dupla) — e os qualificadores `short`, `long` e `unsigned`, deixando claro que o tamanho exato de cada um depende da implementação (a única garantia é `short` não ser maior que `long`). A seção 2.3 (Constantes) cobre notação científica para `float`/`double`, sufixo `L` para `long`, notação octal (`0` inicial) e hexadecimal (`0x`), constantes de caractere (`'x'`, com sequências de escape como `\n`, `\t`, `\0`) e a distinção crucial entre `'x'` (constante de caractere, um `int`) e `"x"` (cadeia de um caractere mais o `\0` terminal).

A seção 2.4 (Declarações) mostra a sintaxe `tipo lista-de-variáveis;` e como inicializar na própria declaração — variáveis automáticas sem inicialização explícita ficam com "lixo", enquanto externas/estáticas são zeradas por padrão. A 2.5 e 2.6 (tratadas em detalhe no resumo de 1.3) cobrem operadores aritméticos e relacionais.

A seção 2.7 (Conversões de Tipos) é a mais densa: explica que `char` é sempre promovido a `int` em expressões aritméticas (o que permite escrever `atoi` fazendo `s[i] - '0'`), que a conversão de `char` para `int` pode ou não fazer extensão de sinal dependendo da máquina (por isso `getchar()` deve ser guardado em `int`, nunca em `char`, para representar corretamente o `EOF`), e enuncia a cadeia de promoção aritmética: `char`/`short` → `int`, depois promoção para `double`, `long` ou `unsigned` conforme o operando "maior" da expressão. Fecha com a conversão explícita via *cast*, `(tipo) expressão`, exemplificada com `sqrt((double) n)`.

## Síntese
O essencial é internalizar que em C o tamanho de um tipo primitivo não é garantido pela linguagem (por isso `sizeof`) e que expressões mistas seguem uma cadeia fixa de promoção — sobretudo `char`→`int`, a razão pela qual `getchar()` deve ser recebido em `int`. Celes contextualiza isso dentro do uso em estruturas de dados; o K&R (2.1-2.7) é a fonte de regras precisas de sintaxe e conversão.
