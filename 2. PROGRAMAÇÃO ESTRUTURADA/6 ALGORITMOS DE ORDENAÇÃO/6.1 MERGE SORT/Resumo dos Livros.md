# Resumo dos Livros — 6.1 Merge Sort

## Celes — Introdução a Estruturas de Dados
> ⚠️ **Celes NÃO cobre merge sort.** Conferido diretamente na extração OCR do texto completo do livro (`Livros/00 - celes extracao google.md`): o Cap. 16 ("Ordenação") tem exatamente duas seções — "Ordenação bolha" (bubble sort, ver [[../Resumo dos Livros|resumo do capítulo]]) e "Ordenação rápida" (quicksort, ver [[../6.2 QUICK SORT/Resumo dos Livros|6.2]]). Nenhuma menção a mergesort/intercalação aparece no livro. A afirmação anterior desta nota ("o mergesort costuma ser apresentado logo após os métodos elementares") era uma suposição de estrutura genérica, incorreta para esta obra especificamente — para merge sort, use Szwarcfiter e Cormen abaixo como referência principal deste subtópico.

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Seção 7.4)
Szwarcfiter apresenta o mergesort como um método que "tem como procedimento básico o procedimento de intercalação de listas". A ideia central: para ordenar a lista L, dividi-la ao meio e ordenar cada metade recursivamente; como as duas metades ordenadas resultantes podem ser intercaladas, basta um procedimento de intercalação eficiente. O procedimento `intercalar` percorre simultaneamente os dois trechos com ponteiros `ini1`/`ini2`, copiando sempre o menor elemento corrente para uma tabela temporária `Tmp`, e ao final copiando `Tmp` de volta para `L`. O pseudocódigo do `mergesort(esq, dir)` é literalmente:

```
se esq < dir então
    centro := ⌊(esq + dir)/2⌋
    mergesort(esq, centro)
    mergesort(centro + 1, dir)
    intercalar(esq, centro + 1, dir)
```

A análise da recorrência é feita de forma explícita e "manual" (sem o método mestre): partindo de T(n) = 2T(n/2) + n (assumindo n potência de 2), o livro divide ambos os lados por n, soma as equações teleścopicamente ao longo dos níveis de recursão e conclui T(n) = O(n log n) para o pior caso — que aqui coincide com melhor e médio caso, já que o algoritmo sempre faz o mesmo trabalho independente da ordem de entrada.

Um ponto que o livro destaca e que costuma passar despercebido: apesar da boa complexidade assintótica, "a ordenação por intercalação não é um dos métodos de ordenação mais empregados" — sua eficiência prática depende de uma implementação cuidadosa da área temporária, evitando cópias desnecessárias (por exemplo, alternando os papéis de `L` e `Tmp` entre níveis de recursão em vez de copiar de volta a cada chamada).

## Cormen — Algoritmos: Teoria e Prática (Cap. 2, Seção 2.3.1)
Cormen introduz o mergesort na Seção 2.3.1 como o exemplo canônico do paradigma de divisão e conquista, descrito nos três passos clássicos: **Dividir** a sequência de n elementos em duas subsequências de n/2; **Conquistar**, ordenando cada uma recursivamente; **Combinar**, intercalando as duas subsequências ordenadas. A recursão termina quando a sequência tem comprimento 1 (trivialmente ordenada).

A operação-chave é o procedimento auxiliar `Merge(A, p, q, r)`, que recebe dois subarranjos já ordenados `A[p..q]` e `A[q+1..r]` e os funde num único subarranjo ordenado, em tempo Θ(n). Cormen ilustra com a analogia de duas pilhas de cartas viradas para cima: a cada passo, compara-se o topo das duas pilhas, remove-se a menor e coloca-se na pilha de saída — cada passo em tempo constante, logo Θ(n) passos no total. A implementação do livro usa **sentinelas** (valor ∞ no fim de cada subarranjo auxiliar `L` e `R`) para evitar checar explicitamente se uma das pilhas se esvaziou a cada iteração, e o texto prova formalmente a corretude do laço principal via invariante de laço (inicialização, manutenção, término).

A análise da recorrência é retomada no Capítulo 4 (Divisão e Conquista): o tempo de execução do pior caso é descrito por T(n) = 2T(n/2) + Θ(n), cuja solução é T(n) = Θ(n log n) — resolvida ali com três métodos gerais (substituição, árvore de recursão, método mestre), em vez do somatório telescópico usado por Szwarcfiter.

## Síntese
Os dois livros tratam o mergesort de forma estruturalmente idêntica — divisão ao meio, ordenação recursiva das metades, intercalação — e chegam à mesma recorrência T(n) = 2T(n/2) + O(n) e à mesma complexidade Θ(n log n) garantida em qualquer caso. A diferença está no aparato: Cormen prova corretude formalmente via invariante de laço e resolve a recorrência com métodos gerais reaproveitáveis (mestre, árvore de recursão), enquanto Szwarcfiter resolve por manipulação algébrica direta da equação e chama atenção, de forma mais pragmática, para o fato de que a boa complexidade teórica não torna o mergesort o método mais usado na prática — observação que casa com o fato de o próprio Celes, livro-base do curso, pular direto de bubble sort para quicksort sem passar por merge sort.

## Exemplos em C

**Merge sort — implementação padrão em C (não há versão do Celes para comparar; segue diretamente o pseudocódigo de Szwarcfiter/Cormen: dividir, ordenar recursivamente, intercalar):**
```c
#include <stdio.h>
#include <stdlib.h>

void merge(int *v, int esq, int centro, int dir) {
    int n1 = centro - esq + 1;
    int n2 = dir - centro;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = v[esq + i];
    for (int j = 0; j < n2; j++) R[j] = v[centro + 1 + j];

    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2)               /* intercala os dois já ordenados */
        v[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) v[k++] = L[i++];        /* copia o resto de L, se sobrou */
    while (j < n2) v[k++] = R[j++];        /* copia o resto de R, se sobrou */

    free(L);
    free(R);
}

void merge_sort(int *v, int esq, int dir) {
    if (esq >= dir)
        return;                             /* 0 ou 1 elemento: já ordenado */

    int centro = esq + (dir - esq) / 2;     /* evita overflow de (esq+dir)/2 em vetores grandes */
    merge_sort(v, esq, centro);
    merge_sort(v, centro + 1, dir);
    merge(v, esq, centro, dir);
}

int main(void) {
    int v[] = {25, 48, 37, 12, 57, 86, 33, 92};
    int n = sizeof(v) / sizeof(v[0]);

    merge_sort(v, 0, n - 1);

    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");   /* 12 25 33 37 48 57 86 92 */
    return 0;
}
```

**Por que O(n) de memória auxiliar importa na prática** — a desvantagem que Szwarcfiter cita e que explica por que Celes prioriza quicksort:
```c
/* cada chamada de merge() aloca L e R do tamanho do trecho que está intercalando —
   no total, ao longo da recursão, isso soma O(n) de memória extra além do vetor original.
   quicksort (ver 6.2), particionando IN-PLACE, usa apenas O(log n) de pilha de recursão. */
```
