# Resumo dos Livros — 6.2 Quick Sort

## Celes — Introdução a Estruturas de Dados (Cap. 16, "Ordenação" — seção "Ordenação rápida")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção importante: **Celes não cobre mergesort em nenhum lugar** — o capítulo de ordenação tem só duas seções, "Ordenação bolha" (ver [[../Resumo dos Livros|resumo do capítulo]]) e "Ordenação rápida" (quicksort). O quicksort aparece logo *depois* do bubble sort, não do mergesort.

**Ideia central, no vocabulário do livro**: como o bubble sort, o quicksort "resolve o problema da ordenação por partes" — mas em vez de posicionar o maior elemento a cada passada (bolha), posiciona um elemento arbitrário `x` (o **pivô**) na sua posição final, garantindo que tudo à esquerda seja menor e tudo à direita seja maior, e então ordena os dois subvetores recursivamente. Melhor caso: pivô = mediana → O(n log n) (subvetores sempre pela metade); pior caso: pivô sempre o extremo (maior ou menor) → degenera para o comportamento O(n²) do bubble sort. O livro afirma, sem provar formalmente (diferente de Szwarcfiter/Cormen abaixo), que o caso médio "ainda apresenta... um desempenho O(n log(n))".

**Algoritmo com pivô = primeiro elemento** (`v[0]`), desenvolvido passo a passo sobre o mesmo vetor de exemplo usado no bubble sort (`25 48 37 12 57 86 33 92`): dois índices `a` (varre da esquerda) e `b` (varre da direita) avançam até `a` achar um elemento `> x` e `b` achar um elemento `<= x`; trocam-se `v[a]`/`v[b]`; repete até `a` e `b` se cruzarem — nesse ponto troca-se o pivô `v[0]` com `v[b]`, que fica na posição final correta, e o algoritmo recorre sobre os dois subvetores resultantes:
```c
void rapida(int n, int* v) {
    if (n <= 1) return;
    int x = v[0], a = 1, b = n-1;
    do {
        while (a < n && v[a] <= x) a++;   /* teste extra a<n: pivô pode ser o maior elemento */
        while (v[b] > x) b--;              /* sem teste extra: v[0]==x garante b não passa de 0 */
        if (a < b) { int t=v[a]; v[a]=v[b]; v[b]=t; }
        a++; b--;
    } while (a <= b);
    v[0] = v[b]; v[b] = x;      /* posiciona o pivô */
    rapida(b, v);                /* ordena subvetor esquerdo */
    rapida(n-a, &v[a]);          /* ordena subvetor direito */
}
```
O livro explica com cuidado por que o teste de `a` precisa do `a < n` extra (o pivô pode ser o maior elemento, então `v[a] <= x` pode nunca ser falso) enquanto o teste de `b` não precisa de `b >= 0` (como `v[0]` é o próprio pivô, `b` nunca ultrapassa a posição 0).

**`qsort` da biblioteca padrão**: o capítulo fecha conectando isso à função genérica de `stdlib.h`, `void qsort(void *v, int n, int tam, int (*cmp)(const void*, const void*))` — o livro nota que quicksort é "o algoritmo de ordenação mais utilizado no desenvolvimento de aplicações" e que, mesmo para ordenar uma lista encadeada, a prática comum é copiar os ponteiros dos nós para um vetor temporário, ordenar esse vetor com `qsort`, e reencadear na ordem resultante.

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Seção 7.5)

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Seção 7.5)
Szwarcfiter descreve o quicksort como "um dos mais eficientes dentre os conhecidos" e formaliza o procedimento recursivo em quatro passos: se n ≤ 1 a tabela já está ordenada; escolhe-se um elemento pivô x; separa-se o restante em S1 = {elementos < x} e S2 = {elementos ≥ x}, ordenando cada um recursivamente; e L recebe a concatenação S1, x, S2.

O livro destaca dois pontos como decisivos para o desempenho: **a escolha do pivô** e **o particionamento**. Sobre o pivô, mostra que tomar sempre o primeiro elemento é ruim quando a tabela já está ordenada na ordem inversa (gera partições de tamanho n−1 e 0); a alternativa recomendada é a mediana de três elementos (primeiro, último e central), evitando o custo de calcular a mediana real ou gerar números aleatórios. Sobre o particionamento, descreve o esquema de dois ponteiros `i` e `j` que se aproximam pelas extremidades opostas até cruzarem — o mesmo esquema de Hoare —, e discute explicitamente o tratamento de chaves repetidas: parar o percurso nos elementos iguais ao pivô produz partições mais equilibradas, ao custo de trocas desnecessárias.

A análise de complexidade (7.5.1) trata separadamente pior, melhor e caso médio, todos partindo da recorrência T(n) = T(i) + T(n−i−1) + cn, onde i é o tamanho de S1. No **pior caso** (pivô sempre o menor elemento), a soma telescópica dá T(n) = O(n²). No **melhor caso** (pivô sempre a mediana, partições equilibradas), chega a T(n) = O(n log n). No **caso médio**, assumindo cada tamanho de S com probabilidade 1/n, o livro conduz a álgebra até introduzir a constante de Euler-Mascheroni no somatório harmônico, concluindo T(n) = O(n log n).

## Cormen — Algoritmos: Teoria e Prática (Cap. 7)
Cormen abre afirmando que o quicksort tem "tempo de execução do pior caso de Θ(n²)", mas ainda assim "é a melhor opção prática para ordenação" devido à eficiência média Θ(n log n) com constantes pequenas, além de ordenar no lugar e funcionar bem em ambientes de memória virtual.

O algoritmo segue o mesmo esquema de divisão e conquista de mergesort: **Dividir** — o procedimento `Partition` reorganiza `A[p..r]` de modo que todo elemento de `A[p..q−1]` seja ≤ `A[q]` que, por sua vez, é ≤ todo elemento de `A[q+1..r]`; **Conquistar** — ordenar os dois subarranjos recursivamente; **Combinar** — trivial, pois já estão ordenados no lugar. O `Partition` sempre escolhe `A[r]` como pivô e mantém um invariante de laço formalmente demonstrado (com as três etapas: inicialização, manutenção, término), rodando em tempo Θ(n).

A Seção 7.2 discute informalmente por que partições balanceadas dão desempenho próximo ao mergesort, enquanto partições muito desbalanceadas degradam para o comportamento da ordenação por inserção. A Seção 7.3 introduz o `Randomized-Quicksort`, que escolhe o pivô aleatoriamente para que nenhuma entrada específica force o pior caso. A Seção 7.4 formaliza a análise: no **pior caso**, resolvendo T(n) = max₀≤q≤n−1(T(q) + T(n−q−1)) + Θ(n) pelo método de substituição com o palpite T(n) ≤ cn², chega-se a T(n) = O(n²) — e mostra que esse limite é justo (Θ(n²)). No **tempo esperado**, prova via análise probabilística que `Randomized-Quicksort` roda em O(n lg n) esperado, combinando esse limite superior com o limite inferior Θ(n lg n) do melhor caso.

## Síntese
Os três livros chegam à mesma conclusão central — quicksort é Θ(n²) no pior caso e Θ(n log n) em média/melhor caso, e a escolha do pivô é o fator decisivo. Szwarcfiter e Cormen provam isso formalmente (recorrências resolvidas algebricamente, análise probabilística); Celes apresenta o mesmo algoritmo com pivô fixo no primeiro elemento (a escolha mais simples e mais vulnerável ao pior caso — exatamente o que Szwarcfiter recomenda evitar com "mediana de três" e Cormen com aleatorização), com código C completo e passo a passo sobre um exemplo numérico, e conecta o algoritmo à função `qsort` real da biblioteca padrão.

## Exemplos em C

**O quicksort do Celes, testável (pivô = primeiro elemento):**
```c
#include <stdio.h>

void rapida(int n, int *v) {
    if (n <= 1) return;

    int x = v[0], a = 1, b = n - 1;
    do {
        while (a < n && v[a] <= x) a++;
        while (v[b] > x) b--;
        if (a < b) {
            int temp = v[a]; v[a] = v[b]; v[b] = temp;
        }
        a++; b--;
    } while (a <= b);

    v[0] = v[b];
    v[b] = x;

    rapida(b, v);
    rapida(n - a, &v[a]);
}

int main(void) {
    int v[] = {25, 48, 37, 12, 57, 86, 33, 92};
    int n = sizeof(v) / sizeof(v[0]);

    rapida(n, v);

    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");   /* 12 25 33 37 48 57 86 92 */
    return 0;
}
```

**Usando o `qsort` de verdade da biblioteca padrão (o que o Celes recomenda na prática):**
```c
#include <stdio.h>
#include <stdlib.h>

int compara_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return x - y;   /* negativo se x<y, zero se iguais, positivo se x>y */
}

int main(void) {
    int v[] = {25, 48, 37, 12, 57, 86, 33, 92};
    int n = sizeof(v) / sizeof(v[0]);

    qsort(v, n, sizeof(int), compara_int);

    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
    return 0;
}
```

**Ordenando structs com `qsort` (o caso de "vetor de alunos" que o Celes usa para motivar comparação por chave):**
```c
#include <string.h>

typedef struct { char nome[81]; int matricula; } Aluno;

int compara_aluno_por_nome(const void *a, const void *b) {
    const Aluno *x = a, *y = b;
    return strcmp(x->nome, y->nome);
}

/* qsort(alunos, n, sizeof(Aluno), compara_aluno_por_nome); */
```
