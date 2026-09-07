# Resumo dos Livros — 1.8 Escopo e Variáveis Globais

## Celes — Introdução a Estruturas de Dados (Cap. 4, "Funções" — seções "Variáveis globais" e "Variáveis estáticas")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Confirmado: Celes é de fato mais prescritivo aqui, e chega a essa recomendação por um caminho concreto — reescreve o exemplo `somaprod` de [[../1.7 PASSAGEM DE PARÂMETROS POR VALOR E POR REFERÊNCIA/Resumo dos Livros|1.7]] usando variáveis globais (`int s, p;` fora de qualquer função, alteradas diretamente dentro de `somaprod`) só para, na sequência imediata, avisar: **"o uso de variáveis globais em um programa deve ser feito com critério, pois podemos criar um alto grau de interdependência entre as funções... Nos nossos exemplos, vamos evitar o uso de variáveis globais."** — e o livro de fato evita, preferindo o padrão de ponteiro como parâmetro visto em 1.7.

Sobre **variáveis globais**: definidas fora do corpo de qualquer função, visíveis a "todas as funções subsequentes" no arquivo, e — ponto central — **não ficam na pilha de execução**, então não são destruídas quando uma função termina; existem durante todo o programa.

Sobre **variáveis estáticas**: podem ser declaradas dentro de uma função (`static int n = 1;`) — nesse caso não ficam na pilha, mas também **não são visíveis fora da função onde foram declaradas** (diferente de uma global). O exemplo é uma função `imprime(float a)` que numera internamente quantas vezes já foi chamada (via `static int n`) para quebrar linha a cada 5 valores impressos — e o livro destaca a utilidade central de `static` local: **"recuperar o valor de uma variável atribuída na última vez em que a função foi executada"**, algo que uma variável automática comum não consegue (ela nasce do zero a cada chamada). Também nota que uma `static` (ou global) não inicializada explicitamente recebe `0` automaticamente — diferente de uma automática, que fica com lixo.

## K&R — C: A Linguagem de Programação (Cap. 4, seções 4.4-4.6)
A seção 4.4 (Variáveis Externas) define um programa C como um conjunto de objetos externos — variáveis ou funções — sendo "externo" o oposto de "interno" (argumentos e variáveis automáticas dentro de uma função). Por padrão, variáveis externas são globais: toda referência ao mesmo nome, mesmo em arquivos compilados separadamente, aponta para a mesma variável (análogo ao `COMMON` do Fortran). O livro justifica seu uso por três razões: (1) comunicação entre muitas funções sem listas de argumentos longas, (2) só variáveis externas/estáticas podem ser inicializadas na declaração (automáticas, não), e (3) escopo e tempo de vida — uma externa existe durante todo o programa, retendo valor entre chamadas de função, ao contrário de uma automática, que nasce e morre a cada ativação. O exemplo condutor é uma calculadora de pilha (notação polonesa reversa) em que a pilha (`val[]`) e seu topo (`ap`) são declarados como externos, visíveis para `empil`/`desempil`/`zera`, mas propositalmente **não** para `main`, que só conhece as operações, não a representação.

A seção também distingue **declaração** de **definição**: `int ap;` fora de função *define* a variável (aloca memória); `extern int ap;` apenas *declara* que ela existe em outro lugar, sem alocar nada — deve haver exatamente uma definição em todo o programa, mas quantas declarações `extern` forem necessárias nos outros arquivos que a usam.

A seção 4.5 (Regras de Escopo) formaliza: o escopo de uma automática é a função onde é declarada (nomes iguais em funções diferentes não têm relação); o escopo de uma externa vai do ponto de sua declaração no arquivo até o fim dele — se usada antes de definida, ou definida em outro arquivo, a declaração `extern` é obrigatória.

A seção 4.6 (Variáveis Estáticas) introduz a terceira classe de armazenamento: `static` pode se aplicar a uma variável interna (local a uma função, mas que **persiste** entre chamadas, ao contrário de uma automática) ou a uma externa (visível só dentro do arquivo-fonte onde foi declarada, invisível para outros arquivos — mesmo que usem o mesmo nome). O exemplo é o par `getch`/`ungetch`, cujo buffer compartilhado é declarado `static` justamente para não vazar nem colidir com nomes em outros arquivos. Funções também podem ser `static`, tornando-as invisíveis fora do arquivo.

## Síntese
Há três classes de armazenamento a distinguir: automática (local, efêmera), externa (global, todo o programa a vê) e estática (persistente, mas com escopo restrito — a uma função, se interna, ou a um arquivo, se externa). A recomendação prática de ambos os livros converge: usar `static` para esconder o que só um módulo (arquivo ou par de funções) precisa saber, e preferir passar dados via parâmetros a espalhar variáveis globais sem necessidade — princípio central para os tipos abstratos de dados que vêm depois no curso. Celes chega a essa conclusão de forma muito concreta: mostra a versão "com globais" funcionando e imediatamente recomenda não fazer assim, preferindo o padrão de ponteiro-como-parâmetro do tópico anterior.

## Exemplos em C

**`static` local — a única forma de uma variável "lembrar" seu valor entre chamadas sem ser global:**
```c
#include <stdio.h>

void imprime(float a) {
    static int n = 1;     /* inicializada com 1 só na 1a chamada; preserva valor depois */
    printf("%.1f ", a);
    if (n % 5 == 0)
        printf("\n");
    n++;
}

int main(void) {
    float valores[] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f};
    int i;
    for (i = 0; i < 7; i++)
        imprime(valores[i]);   /* quebra linha automaticamente a cada 5 valores */
    printf("\n");
    return 0;
}
```

**Global vs. `static` local vs. automática — mesmo nome, três comportamentos diferentes:**
```c
#include <stdio.h>

int contador_global = 0;   /* visível em todo o arquivo, existe o programa todo */

void incrementa_global(void) {
    contador_global++;     /* toda chamada altera a MESMA variável */
}

void incrementa_static(void) {
    static int contador_static = 0;  /* só esta função enxerga; persiste entre chamadas */
    contador_static++;
    printf("static: %d\n", contador_static);
}

void incrementa_automatica(void) {
    int contador_automatico = 0;     /* recriada do zero a cada chamada */
    contador_automatico++;
    printf("automática: %d\n", contador_automatico);  /* sempre imprime 1 */
}

int main(void) {
    for (int i = 0; i < 3; i++) {
        incrementa_global();
        incrementa_static();
        incrementa_automatica();
    }
    printf("global final: %d\n", contador_global);  /* 3 */
    return 0;
}
```
