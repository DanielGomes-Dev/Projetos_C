# Resumo dos Livros — 6. Algoritmos de Ordenação

## Celes — Introdução a Estruturas de Dados (Cap. 16, "Ordenação")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção de escopo: o capítulo é bem mais enxuto do que a suposição genérica anterior — **apenas dois algoritmos**, bolha (bubble sort) e rápida (quicksort). **Não há seleção, inserção nem mergesort** neste livro. Em compensação, o capítulo é notavelmente mais profundo em engenharia de software do que os equivalentes teóricos: cada algoritmo é apresentado em **três versões progressivas** — ingênua, otimizada (com parada antecipada quando não há trocas), e por fim **genérica** (via `void*` + função de comparação passada por *callback*, no mesmo espírito de `qsort` da biblioteca padrão).

**Ordenação bolha** — versão 1 (ingênua, sempre O(n²) mesmo se o vetor já estiver ordenado); versão 2 (com flag `troca`, encerra na primeira passada sem trocas — melhor caso vira O(n) num vetor já ordenado); versão 3 (genérica, com `compara(void*, void*)` como parâmetro de função). Desenvolvida passo a passo sobre o vetor `25 48 37 12 57 86 33 92`, com a contagem explícita de comparações por passada usada para justificar `O(n²)` (soma de uma PA: `(n-1)+(n-2)+...+1`).

**Ordenação rápida (quicksort)** — cobre a versão recursiva com pivô fixo no primeiro elemento; ver [[6.2 QUICK SORT/Resumo dos Livros|6.2]] para o algoritmo completo.

**Merge sort** — **ausente do livro**; ver o aviso em [[6.1 MERGE SORT/Resumo dos Livros|6.1]].

**Ordenação genérica com callback** (o ponto mais avançado do capítulo, sem equivalente direto em Szwarcfiter/Cormen abaixo): o livro reescreve o bubble sort para ordenar **qualquer** tipo de dado, generalizando em 3 etapas — (1) extrair a comparação para uma função auxiliar `compara(a, b)`; (2) trocar os parâmetros `int`/`int*` por `void*` genéricos, exigindo um parâmetro extra `tam` (tamanho em bytes de cada elemento, para poder calcular endereços); (3) passar a função de comparação como um **ponteiro para função** (`int (*cmp)(void*, void*)`), já que a implementação de `compara` precisa ser diferente para cada tipo (`int`, string via `strcmp`, `struct Aluno` por nome). O resultado, `bolha_gen(int n, void* v, int tam, int(*cmp)(void*,void*))`, é estruturalmente idêntico ao `qsort` de `stdlib.h` que o livro apresenta logo depois, na seção de quicksort.

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Cap. 7)

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Cap. 7)
O Capítulo 7 abre observando que a ordenação foi um dos primeiros problemas a gerar discussão sobre eficiência de algoritmos, justamente porque aparece como pré-processamento em praticamente qualquer aplicação que manipule tabelas. Szwarcfiter contrasta os métodos simples — bolha (7.2) e inserção (7.3), de complexidade O(n²) mas de "extrema simplicidade de implementação", úteis quando a tabela é pequena ou quase ordenada — com os métodos eficientes: intercalação/mergesort (7.4), rápido/quicksort (7.5) e heapsort (7.6), todos O(n log n). A Seção 7.7 fecha o capítulo estabelecendo um limite inferior teórico Ω(n log n) para qualquer algoritmo de ordenação baseado em comparações, via árvore de decisão.

O critério de organização do capítulo é didaticamente relevante: ele deixa claro que a "simplicidade de implementação" dos métodos O(n²) é uma vantagem prática real (não apenas um degrau pedagógico antes dos métodos bons), e que mergesort/quicksort resolvem o mesmo problema de formas estruturalmente diferentes — o primeiro sempre O(n log n) à custa de memória auxiliar, o segundo em média O(n log n) no lugar, mas com pior caso O(n²) dependente da escolha do pivô.

## Cormen — Algoritmos: Teoria e Prática (Parte II, cap. 6–9)
A introdução da Parte II ("Ordenação e Estatísticas de Ordem") formaliza o problema de ordenação — entrada é uma sequência de n números, saída é uma permutação em ordem não decrescente — e justifica por que ordenar é considerado "o problema mais fundamental no estudo de algoritmos": aplicações que dependem disso diretamente (extratos bancários), uso como subrotina em outros algoritmos, riqueza de técnicas de projeto exemplificadas pelos algoritmos de ordenação, existência de um limite inferior não trivial demonstrável, e as questões de engenharia real (cache, memória virtual) que aparecem na implementação.

Cormen resume os algoritmos cobertos nos capítulos 2 e 6–9 numa tabela de complexidades: ordenação por inserção Θ(n²); ordenação por intercalação Θ(n log n) (pior e médio caso); ordenação por heap O(n log n) no lugar; quicksort Θ(n²) no pior caso mas Θ(n log n) esperado, e "em geral supera a ordenação por heap na prática"; além dos métodos não comparativos (contagem, digital/radix, balde), que contornam o limite inferior Ω(n log n) usando informação adicional sobre a distribuição dos dados. O Capítulo 8 prova formalmente esse limite inferior via árvore de decisão — o mesmo argumento que Szwarcfiter apresenta na Seção 7.7.

## Síntese
Os dois livros teóricos convergem no ponto central: métodos por comparação têm limite inferior Ω(n log n), e mergesort/heapsort o atingem sempre, enquanto quicksort só o atinge em média. Szwarcfiter apresenta os quatro métodos (bolha, inserção, mergesort, quicksort) dentro de um único capítulo autocontido com prova de complexidade a cada seção; Cormen distribui o mesmo conteúdo em capítulos separados (2, 6, 7, 8) e acrescenta os métodos de tempo linear (contagem, radix, balde). Celes é o mais restrito em escopo (só bolha e rápida, sem prova formal de complexidade), mas o único a mostrar como generalizar um algoritmo de ordenação em C real via `void*` e ponteiro de função — a técnica de engenharia por trás de como `qsort` da biblioteca padrão realmente funciona por dentro.

## Exemplos em C

**Bolha genérico com callback — a técnica central que o Celes desenvolve (funciona para qualquer tipo, igual `qsort`):**
```c
#include <stdio.h>
#include <string.h>

/* acessa o elemento i de um vetor genérico de elementos de 'tam' bytes cada */
static void* acessa(void *v, int i, int tam) {
    return (char*)v + i * tam;
}

static void troca(void *a, void *b, int tam) {
    char *v1 = a, *v2 = b;
    for (int i = 0; i < tam; i++) {
        char t = v1[i]; v1[i] = v2[i]; v2[i] = t;
    }
}

void bolha_gen(int n, void *v, int tam, int (*cmp)(void*, void*)) {
    for (int i = n - 1; i > 0; i--) {
        int fez_troca = 0;
        for (int j = 0; j < i; j++) {
            void *p1 = acessa(v, j, tam);
            void *p2 = acessa(v, j + 1, tam);
            if (cmp(p1, p2)) {
                troca(p1, p2, tam);
                fez_troca = 1;
            }
        }
        if (!fez_troca) return;   /* parada antecipada: já está ordenado */
    }
}

/* especializações da função de comparação — só isto muda por tipo */
int compara_int(void *a, void *b) {
    return *(int*)a > *(int*)b;
}
int compara_string(void *a, void *b) {
    return strcmp(*(char**)a, *(char**)b) > 0;
}

int main(void) {
    int v[] = {25, 48, 37, 12, 57, 86, 33, 92};
    int n = sizeof(v) / sizeof(v[0]);
    bolha_gen(n, v, sizeof(int), compara_int);
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
    return 0;
}
```
