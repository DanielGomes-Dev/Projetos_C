# Resumo dos Livros — 1.4 Entrada e Saída Padrão

## Celes — Introdução a Estruturas de Dados (Cap. 2, "Expressões" — seção "Entrada e saída básicas")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Celes abre a seção lembrando que **C não tem comandos de entrada/saída embutidos na linguagem** — tudo é feito por funções da biblioteca padrão (`stdio.h`). Ele apresenta `printf` e `scanf` de forma bem direta e prática, com o formato informal `printf(formato, lista de valores...)` / `scanf(formato, lista de endereços...)`.

Para `printf`, lista os especificadores `%c` (char), `%d` (int), `%u` (unsigned int), `%f` (double/float), `%e` (double/float em notação científica) e `%g` (double/float, escolhe automaticamente entre `%f` e `%e`) e `%s` (string), além dos caracteres de escape `\n`, `\t`, `\r`, `\"` e `\\`. Mostra também a especificação de largura de campo (`%4d`) e precisão (`%7.2f`, `%.2f` para fixar 2 casas decimais).

Para `scanf`, o livro é explícito sobre a diferença crucial em relação a `printf`: **o formato deve ser seguido por uma lista de *endereços* de variáveis**, não de valores — daí a necessidade do operador `&`, que "retorna o endereço de uma variável" (Celes remete a isso o assunto de ponteiros, tratado em detalhe mais adiante no livro). Lista os especificadores `%c`, `%d`, `%u`, e — ponto que o livro destaca especificamente — `%f`/`%e`/`%g` para `float`, mas **`%lf`/`%le`/`%lg` para `double`** (diferença que não existe em `printf`, onde `%f` cobre os dois). Explica ainda que caracteres literais no formato (fora dos especificadores) exigem correspondência exata na entrada — por exemplo `scanf("%d:%d", &h, &m)` exige que os dois inteiros venham separados por `:` — e que um espaço em branco no formato "pula" brancos da entrada.

O capítulo fecha a seção com um programa completo de exemplo: ler uma altura em metros (`scanf("%f", &h)`) e converter para pés e polegadas usando as constantes 30,48 cm/pé e 2,54 cm/polegada, imprimindo o resultado formatado com `printf("Altura: %dft %.1fpol\n", f, p)` — primeiro programa do livro que combina leitura, cálculo e saída formatada.

## K&R — C: A Linguagem de Programação (Cap. 7, seções 7.1-7.4; Cap. 1, seção 1.5)
O Capítulo 1 (seção 1.5, "Entrada e Saída de Caracteres") já introduz a base: `getchar()` lê o próximo caractere da entrada e o retorna como valor; `putchar(c)` é seu complemento, escrevendo `c` na saída. Nenhuma das duas é "especial" na linguagem — são funções de biblioteca comuns. O padrão idiomático mostrado é `while ((c = getchar()) != EOF) putchar(c);`, que centraliza a leitura numa única chamada dentro do teste do `while` — e o livro insiste que `c` deve ser declarado `int`, não `char`, porque `getchar()` precisa poder representar todo caractere possível **mais** o valor distinto `EOF` (definido como `-1` em `stdio.h`), o que não caberia num `char`.

## K&R — C: A Linguagem de Programação (Cap. 7, seções 7.1-7.4; Cap. 1, seção 1.5)
O Capítulo 1 (seção 1.5, "Entrada e Saída de Caracteres") já introduz a base: `getchar()` lê o próximo caractere da entrada e o retorna como valor; `putchar(c)` é seu complemento, escrevendo `c` na saída. Nenhuma das duas é "especial" na linguagem — são funções de biblioteca comuns. O padrão idiomático mostrado é `while ((c = getchar()) != EOF) putchar(c);`, que centraliza a leitura numa única chamada dentro do teste do `while` — e o livro insiste que `c` deve ser declarado `int`, não `char`, porque `getchar()` precisa poder representar todo caractere possível **mais** o valor distinto `EOF` (definido como `-1` em `stdio.h`), o que não caberia num `char`.

O Capítulo 7 formaliza a biblioteca padrão de E/S. A seção 7.1 explica que todo arquivo-fonte que usa a biblioteca precisa de `#include <stdio.h>`. A seção 7.2 revisita `getchar`/`putchar`, mostrando que a entrada/saída padrão pode ser redirecionada de/para arquivo via `<` e `>`, ou encadeada entre programas via `|`, de forma transparente para o programa (que não sabe se está lendo do terminal ou de um arquivo).

A seção 7.3 (Saída Formatada — Printf) detalha `printf(controle, arg1, arg2, ...)`: a cadeia de controle mistura texto literal com especificações de conversão iniciadas por `%` — sinal de ajuste à esquerda (`-`), largura mínima de campo, um ponto separando a precisão, modificador `l` para `long`, e o caractere de conversão (`d` decimal, `o` octal, `x` hexadecimal, `u` sem sinal, `c` caractere, `s` cadeia, `e`/`f`/`g` ponto flutuante). A seção 7.4 (Entrada Formatada — Scanf) espelha isso para `scanf(controle, arg1, ...)`: cada argumento (exceto quando a conversão é suprimida com `*`) **deve ser um ponteiro**, já que C passa argumentos por valor e a função precisa do endereço para escrever o resultado de volta — o erro mais comum citado no livro é escrever `scanf("%d", n)` em vez de `scanf("%d", &n)`. `scanf` retorna o número de itens lidos com sucesso, ou `EOF` no fim do arquivo.

## Síntese
O par `getchar`/`putchar` (cap. 1 e 7.2) resolve E/S caractere a caractere e deve sempre usar `int` para a variável que recebe o caractere, por causa do `EOF`; `printf`/`scanf` (7.3-7.4) resolvem E/S formatada, com a regra inflexível de que todo argumento de `scanf` precisa ser um ponteiro (`&variável`). Celes chega ao mesmo conjunto de regras por um caminho mais enxuto — inclusive já aponta corretamente a diferença `%f`/`%lf` entre `float` e `double` no `scanf`, que o K&R só formaliza depois — e prioriza um exemplo prático completo (conversão de unidades) em vez do detalhamento exaustivo de todos os especificadores que o K&R oferece. Ver **[[Guia - scanf e printf]]** para a tabela completa consolidando os dois livros, mais os pontos que nenhum dos dois cobre em profundidade (buffer residual, `%[...]`, `fgets`+`sscanf`).

## Exemplos em C

**Reproduzindo o exemplo do Celes (conversão de metros para pés/polegadas):**
```c
#include <stdio.h>

int main(void) {
    float h, p;
    int f;

    printf("Digite a altura em metros: ");
    scanf("%f", &h);

    h = 100 * h;                 /* converte para centímetros */
    f = (int) (h / 30.48);       /* pés inteiros */
    p = (h - f * 30.48) / 2.54;  /* polegadas restantes */

    printf("Altura: %dft %.1fpol\n", f, p);
    return 0;
}
```

**Usando os especificadores certos para cada tipo (o ponto que mais gera bug):**
```c
#include <stdio.h>

int main(void) {
    int idade;
    unsigned int codigo;
    float peso;       /* %f no scanf */
    double salario;   /* %lf no scanf — obrigatório */
    char inicial;
    char cidade[30];

    printf("Idade: ");        scanf("%d", &idade);
    printf("Código (sem sinal): "); scanf("%u", &codigo);
    printf("Peso (kg): ");    scanf("%f", &peso);
    printf("Salário: ");      scanf("%lf", &salario);
    printf("Inicial: ");      scanf(" %c", &inicial);   /* espaço descarta \n residual */
    printf("Cidade: ");       scanf("%29s", cidade);    /* largura evita overflow */

    printf("\n%d anos, código %u, %.1fkg, salário %.2f, inicial '%c', mora em %s\n",
           idade, codigo, peso, salario, inicial, cidade);
    return 0;
}
```
