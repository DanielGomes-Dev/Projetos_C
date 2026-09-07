# Resumo dos Livros — 1.6 Procedimentos e Funções

## Celes — Introdução a Estruturas de Dados (Cap. 4, "Funções" — seção "Definição de funções")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Diferente do que o placeholder anterior sugeria, o Cap. 4 do Celes **é** o capítulo que ensina funções do zero, com uma progressão pedagógica clara: reimplementa o cálculo de fatorial (já visto no Cap. 3) três vezes seguidas, cada versão adicionando um conceito.

**Versão 1 — função `void`, sem retorno**: `void fat(int n)` imprime o fatorial diretamente. Introduz a forma geral `tipo_retornado nome(parâmetros) { corpo }`, a obrigatoriedade de `void` na lista de parâmetros quando a função não recebe nada (inclusive em `main(void)`), e a exigência de **protótipo** antes do uso (`void fat(int n);`, terminado em `;`, repetindo a assinatura da definição) — o livro explica que o protótipo existe para o compilador verificar tipos na chamada (`fat(4.5)` gera erro porque a função espera `int`).

**Versão 2 — função com retorno**: reescreve `fat` como `int fat(int n) { ...; return f; }`, e argumenta explicitamente por que essa versão é "mais adequada": a responsabilidade de *calcular* o fatorial fica separada da responsabilidade de *imprimir* — quem chama (a "função cliente") decide o que fazer com o resultado. Ilustra a reutilização com uma segunda função, `arranjo(n, k)`, que chama `fat` duas vezes (`fat(n) / fat(n-k)`).

**Pilha de execução**: a explicação mais detalhada dos dois livros nesse ponto específico — Celes descreve passo a passo, com diagramas de memória (endereços fictícios), como parâmetros e variáveis locais são empilhados na chamada e desempilhados no retorno, e por que uma variável local de `fat` deixa de existir assim que a função termina. Usa isso para justificar formalmente por que **passagem por valor** significa que alterar um parâmetro dentro da função nunca afeta a variável original do chamador (exemplo: uma versão de `fat` que decrementa `n` até chegar a 0 — ao final, o `n` de `main` continua intacto).

## K&R — C: A Linguagem de Programação (Cap. 4, seções 4.1-4.3)
A seção 4.1 (Conceitos Básicos) define a forma geral de uma função em C: `nome(lista de argumentos) declarações-de-argumentos { declarações e comandos }`, ilustrada com um mini-programa de busca de padrão (`grep` simplificado) dividido em três funções — `lelinha`, `printf` (já pronta) e `index` — como exemplo de como dividir uma tarefa em peças pequenas e testáveis. Uma função mínima é `vazia() { }`. O livro destaca que a comunicação entre funções ocorre por argumentos e valor de retorno (ou por variáveis externas, tema do próximo tópico), que funções podem aparecer em qualquer ordem no arquivo e podem estar espalhadas por múltiplos arquivos-fonte, e que `return (expressão);` devolve um valor ao chamador — sem expressão, ou ao "cair" no fecha-chaves final, nenhum valor é retornado (o que é permitido mas geralmente indica um problema).

## K&R — C: A Linguagem de Programação (Cap. 4, seções 4.1-4.3)
A seção 4.1 (Conceitos Básicos) define a forma geral de uma função em C: `nome(lista de argumentos) declarações-de-argumentos { declarações e comandos }`, ilustrada com um mini-programa de busca de padrão (`grep` simplificado) dividido em três funções — `lelinha`, `printf` (já pronta) e `index` — como exemplo de como dividir uma tarefa em peças pequenas e testáveis. Uma função mínima é `vazia() { }`. O livro destaca que a comunicação entre funções ocorre por argumentos e valor de retorno (ou por variáveis externas, tema do próximo tópico), que funções podem aparecer em qualquer ordem no arquivo e podem estar espalhadas por múltiplos arquivos-fonte, e que `return (expressão);` devolve um valor ao chamador — sem expressão, ou ao "cair" no fecha-chaves final, nenhum valor é retornado (o que é permitido mas geralmente indica um problema).

A seção 4.2 (Funções que Retornam Valores não Inteiros) explica que, por padrão, uma função não declarada é presumida como retornando `int` — regra que cobre a maioria dos casos, inclusive funções que retornam `char` (promovido a `int`). Quando uma função precisa retornar outro tipo, como `double`, isso deve ser declarado **nos dois lugares**: na própria definição (`double atof(s) ...`) e na função chamadora (`double soma, atof();`) — se a chamadora não souber que a função retorna `double`, o compilador assume `int` e o programa produz resultados sem sentido, um erro que pode passar despercebido se as funções forem compiladas em arquivos separados.

A seção 4.3 (Mais sobre Argumentos de Funções) reforça que argumentos são sempre passados por valor — a função chamada recebe uma cópia e não pode alterar a variável original do chamador — exceto quando o argumento é um nome de vetor, caso em que o que é passado é o **endereço** do primeiro elemento, permitindo à função alterar os elementos do vetor original (efeito equivalente a "passagem por referência"). O livro nota também que C não tem um mecanismo totalmente portável para funções com número variável de argumentos — `printf` resolve isso lendo a própria cadeia de controle para saber quantos argumentos esperar.

## Síntese
A regra que mais gera erro para iniciantes é a necessidade de declarar explicitamente (nos dois lados da chamada) qualquer função que não retorne `int`; a segunda é entender que "passagem por valor" é a regra geral em C, com vetores como única exceção natural — o que prepara diretamente o tópico seguinte (1.7, passagem de parâmetros). Ao contrário do que se supunha, Celes **não** pressupõe esse conhecimento — ensina funções do zero com a mesma profundidade que o K&R, e vai além nesse ponto específico ao mostrar visualmente, passo a passo, o funcionamento da pilha de execução (algo que o K&R trata de forma mais textual).

## Exemplos em C

**Protótipo + definição + separação cálculo/impressão (o padrão que o Celes recomenda):**
```c
#include <stdio.h>

int fatorial(int n);          /* protótipo: obrigatório antes do uso */
int arranjo(int n, int k);    /* reutiliza fatorial() */

int main(void) {
    int n = 5, k = 2;
    printf("Fatorial de %d = %d\n", n, fatorial(n));
    printf("Arranjo de %d em %d = %d\n", n, k, arranjo(n, k));
    return 0;
}

int fatorial(int n) {
    int i, f = 1;
    for (i = 1; i <= n; i++)
        f *= i;
    return f;                 /* calcula e retorna — não imprime nada */
}

int arranjo(int n, int k) {
    return fatorial(n) / fatorial(n - k);
}
```

**Por que passagem por valor não altera a variável do chamador:**
```c
#include <stdio.h>

void tentaZerar(int n) {
    n = 0;              /* só altera a CÓPIA local de n */
}

int main(void) {
    int x = 5;
    tentaZerar(x);
    printf("x continua %d\n", x);   /* imprime 5, não 0 */
    return 0;
}
```
Resolver isso (fazer a função efetivamente alterar a variável do chamador) é exatamente o assunto de [[../1.7 PASSAGEM DE PARÂMETROS POR VALOR E POR REFERÊNCIA/Resumo dos Livros|1.7 Passagem de Parâmetros]].
