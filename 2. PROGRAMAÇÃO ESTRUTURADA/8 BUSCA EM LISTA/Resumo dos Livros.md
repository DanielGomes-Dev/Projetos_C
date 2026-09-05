# Resumo dos Livros — 8. Busca em Lista

## Celes — Introdução a Estruturas de Dados (Cap. 17, "Busca" — seção "Busca em vetor")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção: busca vem logo **depois** de ordenação (Cap. 16, ver [[../6 ALGORITMOS DE ORDENAÇÃO/Resumo dos Livros|6]]) e **antes** de tabelas de dispersão (Cap. 18) — não logo após vetores/listas em si; a motivação (Parte III do livro) é justamente que busca eficiente em vetor pressupõe ordenação prévia.

**Busca linear** (`busca`): percorre o vetor do início ao fim, retorna o índice ou `-1`. Pior caso O(n), caso médio n/2 comparações — "mas dizemos que O(kn), onde k é uma constante relativamente pequena, é igual a O(n)".

**Busca linear em vetor ordenado** (`busca_ord`): mesma ideia, mas pode parar assim que encontra um elemento **maior** que o buscado (se o vetor está ordenado crescente, o elemento buscado — se existisse — já teria aparecido antes). Melhora a constante, mas o livro é explícito: **continua sendo O(n)** no pior caso — só busca binária muda a ordem de complexidade.

**Busca binária** (`busca_bin`) — a peça central do capítulo, com a mesma analogia que Szwarcfiter usa (mas descrita de forma independente): compara o elemento buscado com o do meio do intervalo `[ini, fim]`; se menor, restringe a busca à metade esquerda (`fim = meio-1`); se maior, à direita (`ini = meio+1`); se igual, encontrou. Repete até `ini > fim` (não encontrado) ou achar. O livro deriva `O(log n)` mostrando a tabela de tamanho do problema a cada repetição (`n, n/2, n/4, ..., 1`) — exatamente a mesma progressão de Szwarcfiter.

**Duas versões recursivas**: `pertence_rec` (só diz se o elemento está ou não presente, retorno booleano) e `busca_bin_rec` (retorna o índice real). Ponto técnico que o livro destaca: a chamada recursiva para a metade direita usa `&vet[meio+1]` como novo "início" do vetor — deslocando o próprio ponteiro em vez de carregar um índice `ini` adicional — e por isso `busca_bin_rec` precisa **recompor** o índice global somando `meio+1+r` ao resultado da chamada recursiva (`r`), já que a subchamada não sabe sua posição dentro do vetor original.

**Alerta que conecta os tópicos do curso**: o livro afirma explicitamente que **busca binária não funciona em lista encadeada** (mesmo ordenada) — porque não há acesso O(1) por índice para calcular o "meio" — só busca linear é possível numa lista encadeada, o que o livro usa para justificar a necessidade de árvores binárias de busca (fora do escopo direto desta ementa) quando se quer busca eficiente **e** inserção/remoção dinâmicas ao mesmo tempo.

**Algoritmo genérico da biblioteca padrão**: `void* bsearch(void *info, void *v, int n, int tam, int (*cmp)(const void*, const void*))`, de `stdlib.h` — mesma família de `qsort` (ver [[../6 ALGORITMOS DE ORDENAÇÃO/6.2 QUICK SORT/Resumo dos Livros|6.2]]): retorna o endereço do elemento encontrado ou `NULL`, e exige que o vetor já esteja ordenado segundo o mesmo critério da função `cmp`.

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Cap. 2)
O capítulo 2 (Listas Lineares) apresenta busca sequencial e busca binária como as primeiras operações sobre uma lista L de n elementos com chaves distintas, antes de avançar para árvores de busca (capítulo 4).

O Algoritmo 2.1 (`busca1`) é a busca sequencial "de livro-texto", percorrendo a lista enquanto `i ≤ n` e comparando `L[i].chave = x` a cada passo. O Algoritmo 2.2 (`busca`) resolve a mesma busca com uma otimização clássica — a "sentinela": copia-se o valor procurado `x` para uma posição extra `L[n+1]`, garantindo que o laço sempre encontre um nó com a chave desejada e eliminando o teste de fim de tabela a cada iteração: *"a cada iteração correspondem dois testes no Algoritmo 2.1 e apenas um no 2.2."* Ambos têm complexidade de pior caso O(n); o livro observa que a complexidade média também é idêntica entre os dois, calculada em função de `q`, a probabilidade de a busca ter sucesso.

Em seguida, para listas **ordenadas**, o livro apresenta a busca binária (Algoritmo 2.4) como "um algoritmo diverso e bem mais eficiente": *"a ideia básica do algoritmo é percorrer a tabela como se folheia, por exemplo, uma lista telefônica, abandonando-se as partes do catálogo onde o nome procurado, com certeza, não será encontrado."* A cada iteração compara-se o elemento do meio (`meio := ⌊(inf + sup)/2⌋`) e descarta-se metade do intervalo `[inf, sup]` de busca. A análise de complexidade do pior caso é explícita: a cada iteração o tamanho da tabela cai pela metade (n, ⌊n/2⌋, ⌊⌊n/2⌋/2⌋, ...) até restar 1 elemento, portanto "o número de iterações é, no máximo, 1 + ⌊log₂ n⌋ [...] logo, a complexidade da busca binária é O(log n)."

## Cormen — Algoritmos: Teoria e Prática (Cap. 2)
O livro não nomeia "busca sequencial" como um algoritmo com pseudocódigo pronto no corpo do texto — ao contrário do Insertion-Sort, que é totalmente desenvolvido logo na seção 2.1 —, mas a introduz como o primeiro exercício proposto imediatamente após ele, funcionando como aplicação introdutória do método de prova por invariante de laço que acabou de ser ensinado. O enunciado do Exercício 2.1-3 define o problema formalmente:

> "Entrada: Uma sequência de n números A = ⟨a₁, a₂, ..., aₙ⟩ e um valor v. Saída: Um índice i tal que v = A[i] ou o valor especial NIL, se v não aparecer em A. Escreva o pseudocódigo para busca linear, que faça a varredura da sequência, procurando por v. Usando um invariante de laço, prove que seu algoritmo é correto."

O tema volta ainda duas vezes no mesmo capítulo, reforçando seu papel de exemplo recorrente: no Exercício 2.2-3, ao pedir a análise assintótica do caso médio e do pior caso da busca linear em notação Θ (o pior caso é sempre Θ(n); o caso médio, sob a hipótese de que o elemento buscado tem probabilidade igual de estar em qualquer posição, também é Θ(n)); e na seção sobre recorrências (capítulo 4), onde uma "versão recursiva da busca linear" é usada como exemplo de recorrência que produz apenas um subproblema por chamada — "criaria apenas um subproblema contendo somente um elemento a menos do que o problema original [...] o que produz a recorrência T(n) = T(n − 1) + Θ(1)". Ou seja, Cormen usa a busca linear/sequencial não como algoritmo a ser estudado por si, mas como veículo pedagógico recorrente para ensinar invariante de laço, análise Θ e recorrências — os mesmos conceitos que depois se aplicam a algoritmos mais complexos.

Busca binária não é o foco desse trecho do capítulo 2 (aparece no livro principalmente associada a estruturas como árvores B, no capítulo 18), mas o padrão de "descartar metade do espaço de busca a cada passo" segue a mesma lógica de divisão e conquista apresentada no capítulo em relação ao Merge Sort.

## Síntese
Os três livros tratam busca sequencial como o algoritmo de busca mais elementar, útil justamente por sua simplicidade didática: Cormen a usa como veículo para ensinar invariante de laço e análise assintótica desde o capítulo 2, enquanto Celes e Szwarcfiter a apresentam de forma mais prática, evoluindo para busca binária (que exige acesso indexado O(1) e é naturalmente recursiva, como visto em [5 Recursividade](<../5 RECURSIVIDADE/Resumo dos Livros.md>)) — os três convergem na mesma tabela de progressão `n, n/2, n/4, ...` para derivar O(log n). Celes é o único a alertar explicitamente que busca binária **exige** vetor (não funciona em lista encadeada) e a conectar isso a `bsearch` da biblioteca padrão real.

## Exemplos em C

**Busca linear, busca linear em vetor ordenado, e busca binária (iterativa e recursiva) — as 4 versões do Celes:**
```c
#include <stdio.h>

int busca_linear(int n, int *vet, int elem) {
    for (int i = 0; i < n; i++)
        if (elem == vet[i])
            return i;
    return -1;
}

int busca_linear_ordenado(int n, int *vet, int elem) {
    for (int i = 0; i < n; i++) {
        if (elem == vet[i]) return i;
        if (elem < vet[i]) return -1;   /* passou do ponto: não está presente */
    }
    return -1;
}

int busca_binaria(int n, int *vet, int elem) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        if (elem < vet[meio])      fim = meio - 1;
        else if (elem > vet[meio]) ini = meio + 1;
        else                        return meio;
    }
    return -1;
}

int busca_binaria_rec(int n, int *vet, int elem) {
    if (n <= 0)
        return -1;

    int meio = n / 2;
    if (elem < vet[meio])
        return busca_binaria_rec(meio, vet, elem);
    if (elem > vet[meio]) {
        int r = busca_binaria_rec(n - 1 - meio, &vet[meio + 1], elem);
        return (r < 0) ? -1 : meio + 1 + r;   /* recompõe o índice global */
    }
    return meio;
}

int main(void) {
    int v[] = {12, 25, 33, 37, 48, 57, 86, 92};   /* precisa estar ORDENADO para a binária */
    int n = sizeof(v) / sizeof(v[0]);

    printf("linear: %d\n", busca_linear(n, v, 57));
    printf("binária: %d\n", busca_binaria(n, v, 57));
    printf("binária recursiva: %d\n", busca_binaria_rec(n, v, 57));
    printf("não encontrado: %d\n", busca_binaria(n, v, 99));

    return 0;
}
```

**`bsearch` da biblioteca padrão (mesma família de `qsort`, ver [[../6 ALGORITMOS DE ORDENAÇÃO/6.2 QUICK SORT/Resumo dos Livros|6.2]]):**
```c
#include <stdio.h>
#include <stdlib.h>

int compara_int(const void *a, const void *b) {
    return *(const int*)a - *(const int*)b;
}

int main(void) {
    int v[] = {12, 25, 33, 37, 48, 57, 86, 92};
    int n = sizeof(v) / sizeof(v[0]);
    int chave = 48;

    int *achou = bsearch(&chave, v, n, sizeof(int), compara_int);
    if (achou != NULL)
        printf("Encontrado no índice %ld\n", achou - v);   /* aritmética de ponteiro */
    else
        printf("Não encontrado\n");

    return 0;
}
```
