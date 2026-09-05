# Resumo dos Livros — 5. Recursividade

## Celes — Introdução a Estruturas de Dados (Cap. 4, "Funções" — seção "Recursividade")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Confirmado: o tratamento é breve nesse capítulo (uma página), mas denso — e o livro retoma recursão de forma muito mais extensa mais adiante, em listas encadeadas ("Implementações recursivas", Cap. 10) e árvores (Cap. 13), exatamente como o resumo original previa.

Aqui a seção define recursão **direta** (uma função A chama a própria A) vs. **indireta** (A chama B, que chama A de volta) — distinção que nem Szwarcfiter nem K&R nomeiam explicitamente nos trechos citados abaixo. Reforça, no mesmo vocabulário da pilha de execução já construído na seção anterior do capítulo, que cada chamada recursiva empilha seu **próprio** conjunto de parâmetros e variáveis locais — "como se estivéssemos chamando funções diferentes" — o que explica por que chamadas recursivas não colidem entre si.

O exemplo é o mesmo fatorial já usado 3 vezes no capítulo (iterativo com `while`, com `for`, agora recursivo), apresentado a partir da definição matemática recursiva (0! = 1; n! = n × (n-1)!) traduzida quase literalmente para código:
```c
int fat(int n) {
    if (n == 0)
        return 1;
    else
        return n * fat(n - 1);
}
```
O livro nota explicitamente o trade-off, no mesmo espírito de Szwarcfiter e K&R: "diversas implementações ficam muito mais fáceis com a recursividade. Por outro lado, implementações não recursivas tendem a ser mais eficientes."

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Cap. 1, seção 1.3)
A seção define o conceito com precisão: um procedimento "que contém, em sua descrição, uma ou mais chamadas a si mesmo [...] é denominado recursivo, e a chamada a si mesmo é dita chamada recursiva." O texto observa que "todo procedimento, recursivo ou não, deve possuir pelo menos uma chamada proveniente de um local exterior a ele", chamada de "chamada externa".

Um ponto central da seção é a equivalência teórica com iteração: "de modo geral, a todo procedimento recursivo corresponde um outro não recursivo que executa, exatamente, a mesma computação." As vantagens listadas para a versão recursiva são concisão e proximidade com uma prova por indução matemática ("muitas vezes é aparente a relação direta entre um procedimento recursivo e uma prova por indução matemática [...] a verificação da correção pode se tornar mais simples"); a desvantagem citada é eficiência — "um algoritmo não recursivo equivalente pode ser mais eficiente."

O exemplo canônico é o fatorial, apresentado nas duas formas para comparação direta:

```
função fat(i)
    fat(i) := se i ≤ 1 então 1 senão i × fat(i – 1)
```

versus a versão iterativa, que usa um vetor auxiliar:

```
fat[0] := 1
para j := 1, …, n faça
    fat[j] := j × fat[j – 1]
```

O segundo exemplo desenvolvido é a Torre de Hanói, escolhido por ser um caso "onde a solução recursiva é natural e intuitiva" — o autor decompõe o problema de `n` discos em três passos (mover `n-1` discos para o pino de trabalho, mover o maior disco, mover os `n-1` discos de volta), formalizados no procedimento `hanoi(n, A, B, C)`, que se chama recursivamente duas vezes, uma antes e outra depois de mover o disco do topo.

## K&R — C: A Linguagem de Programação (Cap. 4, seção 4.10)
A seção "Recursividade" apresenta o tema com um exemplo próprio da linguagem C: a impressão de um número inteiro em decimal, escolhido porque expõe bem o problema que a recursão resolve elegantemente — "os dígitos são gerados na ordem inversa: dígitos de mais baixa ordem estão disponíveis antes que os de mais alta ordem, mas eles devem ser impressos na ordem inversa." A versão recursiva evita o vetor auxiliar da versão iterativa:

```c
imprdec(n)              /* imprime n em decimal (recursivo) */
int n;
{
    int i;
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if ((i = n / 10) != 0)
        imprdec(i);
    putchar(n % 10 + '0');
}
```

O livro explica o mecanismo subjacente: "quando uma função chama a si própria recursivamente, cada ativação recebe um conjunto novo de todas as variáveis locais, independente do conjunto anterior" — cada chamada empilha seu próprio `n` e `i`. O texto é honesto quanto ao custo: "recursividade em geral não fornece economia de memória, desde que em algum lugar uma pilha de valores sendo processados tem de ser montada. Nem será mais rápida. Mas o código recursivo é mais compacto, e frequentemente mais fácil de escrever e entender" — conclusão que converge quase palavra por palavra com a de Szwarcfiter. O livro aponta ainda que a recursividade "é especialmente conveniente para estrutura de dados definidas recursivamente tais como árvores."

## Síntese
Os três livros concordam no trade-off central: recursão troca eficiência (pilha de chamadas, sem ganho de memória ou velocidade) por clareza de código e proximidade com a definição matemática do problema — ponto que Szwarcfiter formaliza com rigor de prova por indução e K&R ilustra com um exemplo de C idiomático (`imprdec`). Ambos concordam também que a recursão brilha em problemas naturalmente recursivos (Hanói, árvores), tema que reaparece de forma prática em [8 Busca em Lista](<../8 BUSCA EM LISTA/Resumo dos Livros.md>) (busca binária recursiva).

## Exemplos em C

**Fatorial (o exemplo do Celes, direto da definição matemática):**
```c
#include <stdio.h>

int fatorial(int n) {
    if (n == 0)
        return 1;
    return n * fatorial(n - 1);
}

int main(void) {
    printf("5! = %d\n", fatorial(5));
    return 0;
}
```

**`imprdec` (o exemplo do K&R) — imprime um inteiro em decimal usando a pilha de chamadas para inverter a ordem dos dígitos:**
```c
#include <stdio.h>

void imprdec(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10 != 0)
        imprdec(n / 10);      /* imprime os dígitos mais significativos primeiro */
    putchar(n % 10 + '0');    /* e só então o último dígito, "na volta" da recursão */
}

int main(void) {
    imprdec(-4321);
    putchar('\n');
    return 0;
}
```

**Torre de Hanói (o exemplo do Szwarcfiter) — recursão dupla, decompondo o problema em 3 subpassos:**
```c
#include <stdio.h>

void hanoi(int n, char origem, char aux, char destino) {
    if (n == 0)
        return;
    hanoi(n - 1, origem, destino, aux);    /* move n-1 discos para o pino auxiliar */
    printf("Mova o disco %d de %c para %c\n", n, origem, destino);
    hanoi(n - 1, aux, origem, destino);    /* move os n-1 discos do auxiliar para o destino */
}

int main(void) {
    hanoi(3, 'A', 'B', 'C');
    return 0;
}
```

**Recursão indireta (A chama B, que chama A de volta) — par par/ímpar por recursão mútua, só para ilustrar o conceito:**
```c
#include <stdio.h>

int eh_par(int n);
int eh_impar(int n);

int eh_par(int n) {
    if (n == 0) return 1;
    return eh_impar(n - 1);
}

int eh_impar(int n) {
    if (n == 0) return 0;
    return eh_par(n - 1);
}

int main(void) {
    printf("7 é par? %s\n", eh_par(7) ? "sim" : "não");
    return 0;
}
```
