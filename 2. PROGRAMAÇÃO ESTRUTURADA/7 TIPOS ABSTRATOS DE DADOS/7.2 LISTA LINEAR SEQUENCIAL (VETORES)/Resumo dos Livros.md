# Resumo dos Livros — 7.2 Lista Linear Sequencial (Vetores)

## Celes — Introdução a Estruturas de Dados (Cap. 5, "Vetores e alocação dinâmica")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Confirmado: é o capítulo que abre a Parte I dando a base de vetores, mas — diferente do que o resumo anterior supunha — Celes **não** desenvolve aqui um algoritmo genérico de inserção/remoção com deslocamento de elementos (isso fica implícito, não é codificado explicitamente); o capítulo foca em fundamentos: declaração, indexação, aritmética de ponteiros e passagem para funções — a base que [[../7.6 FILA E PILHA/Resumo dos Livros|pilha/fila com vetor]] usa depois para as operações reais de inserir/remover numa estrutura sequencial.

**Motivação**: um programa que calcula média E variância de valores exige guardar todos os valores (a média sozinha não precisa, dá para acumular durante a leitura) — motivação concreta para precisar de uma coleção, não só variáveis soltas.

**Declaração e indexação**: `int v[10];` reserva 10×4=40 bytes contíguos; índice vai de `0` a `n-1` — `v[10]` num vetor de 10 é explicitamente marcado como **ERRADO** ("invasão de memória"), com o alerta de que o compilador C **não verifica limites** em tempo de execução (diferente de linguagens com bounds-checking).

**Vetor ⟺ ponteiro**: `v` sozinho (sem índice) já é o endereço do primeiro elemento — `&v[i]` ⟺ `(v+i)`, `v[i]` ⟺ `*(v+i)`, com a aritmética de ponteiro automaticamente escalada pelo `sizeof` do tipo. Ver [[../../2 GERÊNCIA DE MEMÓRIA/2.3 PONTEIROS/Resumo dos Livros|2.3 Ponteiros]] para o desenvolvimento completo dessa equivalência.

**Passagem para função**: passar um vetor é sempre passar o endereço do 1º elemento (`float media(int n, float* v)`) — nunca uma cópia dos dados; por isso uma função que recebe `int *v` pode alterar os elementos do vetor original do chamador.

**Vetores locais a funções**: seção final do capítulo — um vetor declarado dentro de uma função é alocado na pilha de execução como qualquer variável local, e **deixa de existir quando a função retorna**; retornar um ponteiro para um vetor local (`return v;` de dentro da função, com `int v[10]` local) é um erro clássico, já que o espaço é desalocado no momento em que a função termina.

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Seções 2.2–2.3)

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos (Seções 2.2–2.3)
A Seção 2.2 define a alocação sequencial como "a maneira mais simples de se manter uma lista linear na memória do computador": colocar seus nós em posições contíguas, de modo que "o endereço real do (j+1)-ésimo nó da lista se encontra c unidades adiante daquele correspondente ao j-ésimo", com c o tamanho do nó — a correspondência entre índice e endereço real é automática, feita pela linguagem. Como a implementação em linguagens de alto nível reserva memória previamente, inserção/remoção não movem memória de fato; usam-se variáveis indicando os limites da parte realmente utilizada — por isso o livro chama essa alocação de "estática".

A Seção 2.3 desenvolve os algoritmos de busca sobre essa representação, com análise de complexidade média cuidadosa: o Algoritmo 2.1 (busca linear ingênua, dois testes por iteração) e o Algoritmo 2.2 (mesma busca, mas usando um nó sentinela em `L[n+1]` para eliminar um dos testes por iteração — mesma complexidade de pior caso O(n), porém constante menor). Para listas ordenadas, o Algoritmo 2.3 usa a mesma técnica de sentinela e explora a ordenação para parar mais cedo em buscas sem sucesso, sendo analisado com uma complexidade média mais refinada (dividindo o espaço de entradas em 2n+1 casos distintos). Por fim, o livro apresenta a **busca binária** como alternativa "bem mais eficiente" para listas ordenadas, com complexidade O(log n) — "a ideia básica do algoritmo é percorrer a tabela como se folheia [...] uma lista telefônica".

## Síntese
Os dois livros descrevem a mesma estrutura de base — nós contíguos, endereço calculado por índice, sem necessidade de campo de ponteiro. Szwarcfiter trata com rigor a análise de complexidade média das buscas lineares (com e sem sentinela) e prova a complexidade logarítmica da busca binária — ver [[../../8 BUSCA EM LISTA/Resumo dos Livros|8 Busca em Lista]] para os algoritmos completos; Celes fica nos fundamentos de C sobre vetor (declaração, limites, equivalência com ponteiro, passagem para função) que sustentam qualquer uma dessas implementações.

## Exemplos em C

**Inserção e remoção com deslocamento — o algoritmo que a seção do Celes não codifica explicitamente, mas que decorre diretamente dos fundamentos que ela dá:**
```c
#include <stdio.h>

#define MAX 100

/* insere v na posição pos, deslocando os elementos seguintes uma casa à direita */
int insere(int vet[], int *n, int pos, int v) {
    if (*n >= MAX || pos < 0 || pos > *n)
        return 0;   /* falha: sem espaço ou posição inválida */

    for (int i = *n; i > pos; i--)
        vet[i] = vet[i - 1];   /* desloca à direita, de trás para frente */

    vet[pos] = v;
    (*n)++;
    return 1;
}

/* remove o elemento da posição pos, deslocando os seguintes uma casa à esquerda */
int remove_pos(int vet[], int *n, int pos) {
    if (pos < 0 || pos >= *n)
        return 0;

    for (int i = pos; i < *n - 1; i++)
        vet[i] = vet[i + 1];   /* desloca à esquerda */

    (*n)--;
    return 1;
}

int main(void) {
    int vet[MAX] = {10, 20, 30, 40};
    int n = 4;

    insere(vet, &n, 2, 99);         /* 10 20 99 30 40 */
    for (int i = 0; i < n; i++) printf("%d ", vet[i]);
    printf("\n");

    remove_pos(vet, &n, 0);         /* 20 99 30 40 */
    for (int i = 0; i < n; i++) printf("%d ", vet[i]);
    printf("\n");

    return 0;
}
```
Custo: O(n) por inserção/remoção no pior caso (deslocar até n elementos) — o motivo estrutural pelo qual [[../7.3 LISTA SIMPLESMENTE ENCADEADA/Resumo dos Livros|listas encadeadas]] existem: trocam esse O(n) de deslocamento por O(1), ao custo de perder o acesso direto por índice.

**O erro clássico de retornar ponteiro para vetor local (o alerta do Celes):**
```c
int* cria_vetor_ERRADO(void) {
    int v[10] = {0};
    return v;   /* ERRADO: v é desalocado quando a função retorna */
}

int* cria_vetor_correto(void) {
    int *v = malloc(10 * sizeof(int));   /* alocado dinamicamente: sobrevive ao retorno */
    return v;                             /* quem chamar é responsável por dar free() */
}
```
