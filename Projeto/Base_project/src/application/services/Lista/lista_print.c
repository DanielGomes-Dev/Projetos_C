#include <stdio.h>
#include "application/services/Lista/ListaService.h"

void lista_print(Lista* lista) {

    Node* atual = lista->inicio;

    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->proximo;
    }

    printf("NULL\n");

}

/*
================================================================================
EXPLICAÇÃO COMPLETA DA FUNÇÃO lista_print
================================================================================

Esta função é responsável por PERCORRER toda a lista encadeada
e imprimir cada elemento no terminal.

Ela começa no primeiro nó da lista e segue os ponteiros
até chegar ao final (NULL).

Exemplo de saída:

10 -> 20 -> 30 -> NULL

Para entender completamente essa função precisamos entender:

1) Percorrimento de listas encadeadas
2) Ponteiros temporários
3) Estrutura Node
4) Estrutura de repetição while
5) Condição de parada NULL
6) A função printf
7) Complexidade da operação

Vamos analisar cada parte detalhadamente.

================================================================================
1) OBJETIVO DA FUNÇÃO
================================================================================

A função recebe:

Lista* lista

Ou seja:

um ponteiro para a estrutura que representa a lista.

O objetivo da função é:

percorrer todos os nós da lista
e imprimir os valores armazenados em cada nó.

================================================================================
2) ESTRUTURA DA LISTA
================================================================================

Lembrando como a lista está organizada na memória:

Lista
 ├ inicio -> Node
 └ tamanho

Cada Node contém:

Node
 ├ valor
 └ proximo -> próximo Node

Exemplo de lista:

lista
 ↓
[10] -> [20] -> [30] -> NULL

================================================================================
3) CRIAÇÃO DO PONTEIRO DE PERCORRIMENTO
================================================================================

Node* atual = lista->inicio;

Aqui criamos um ponteiro chamado:

atual

Esse ponteiro será usado para PERCORRER a lista.

Ele começa apontando para o primeiro nó.

Visualmente:

lista->inicio
     ↓
    [10] -> [20] -> [30] -> NULL
      ↑
     atual

================================================================================
4) POR QUE USAMOS UM PONTEIRO TEMPORÁRIO
================================================================================

Nós NÃO podemos usar diretamente:

lista->inicio

para percorrer a lista.

Porque se fizermos isso:

lista->inicio = lista->inicio->proximo

perderíamos o primeiro elemento da lista.

Então criamos um ponteiro auxiliar chamado:

atual

Assim podemos caminhar pela lista
sem alterar a estrutura original.

================================================================================
5) ESTRUTURA DO LOOP
================================================================================

while (atual != NULL)

Isso significa:

"Continue executando o loop enquanto ainda existir um nó".

NULL representa o final da lista.

Visualmente:

[10] -> [20] -> [30] -> NULL
                          ↑
                      condição de parada

================================================================================
6) PRIMEIRA ITERAÇÃO
================================================================================

Estado inicial:

atual -> [10]

Condição:

atual != NULL  → verdadeiro

Então o loop executa.

================================================================================
7) IMPRESSÃO DO VALOR
================================================================================

printf("%d -> ", atual->valor);

Aqui estamos imprimindo o valor do nó atual.

"%d" significa:

imprimir um número inteiro.

Exemplo:

se valor = 10

a saída será:

10 ->

================================================================================
8) MOVENDO PARA O PRÓXIMO NÓ
================================================================================

atual = atual->proximo;

Aqui avançamos para o próximo nó da lista.

Exemplo:

ANTES:

atual -> [10]

DEPOIS:

atual -> [20]

Isso acontece porque:

cada Node possui um ponteiro chamado proximo
que aponta para o próximo elemento.

================================================================================
9) SEGUNDA ITERAÇÃO
================================================================================

Agora:

atual -> [20]

Loop continua:

printf imprime:

20 ->

Depois:

atual = atual->proximo

Resultado:

atual -> [30]

================================================================================
10) TERCEIRA ITERAÇÃO
================================================================================

Agora:

atual -> [30]

printf imprime:

30 ->

Depois:

atual = atual->proximo

Agora:

atual -> NULL

================================================================================
11) FIM DO LOOP
================================================================================

Condição do while:

while (atual != NULL)

Agora:

atual == NULL

Então o loop termina.

================================================================================
12) IMPRESSÃO FINAL
================================================================================

printf("NULL\n");

Isso imprime o final da lista.

Saída final:

10 -> 20 -> 30 -> NULL

O "\n" significa:

quebra de linha.

================================================================================
13) VISUALIZAÇÃO PASSO A PASSO
================================================================================

Lista:

[10] -> [20] -> [30] -> NULL

Iteração 1

atual -> 10

Saída:
10 ->

Iteração 2

atual -> 20

Saída:
10 -> 20 ->

Iteração 3

atual -> 30

Saída:
10 -> 20 -> 30 ->

Fim

NULL

Saída final:

10 -> 20 -> 30 -> NULL

================================================================================
14) COMPLEXIDADE DA OPERAÇÃO
================================================================================

Essa operação tem complexidade:

O(n)

Onde n é o número de elementos da lista.

Isso acontece porque precisamos visitar
cada nó exatamente uma vez.

Se a lista tiver:

10 elementos → 10 passos
100 elementos → 100 passos
1000 elementos → 1000 passos

================================================================================
15) POSSÍVEIS ERROS
================================================================================

Erro comum:

esquecer de mover o ponteiro.

Se esquecermos:

atual = atual->proximo;

o loop ficaria infinito:

while(atual != NULL)

porque atual nunca mudaria.

================================================================================
16) RESUMO FINAL
================================================================================

A função faz basicamente três coisas:

1) cria um ponteiro para percorrer a lista

Node* atual = lista->inicio

2) percorre todos os nós

while (atual != NULL)

3) imprime o valor de cada nó

printf("%d -> ", atual->valor)

4) avança para o próximo nó

atual = atual->proximo

5) imprime o final da lista

printf("NULL")

Assim conseguimos visualizar toda a estrutura
da lista encadeada no terminal.

================================================================================
*/