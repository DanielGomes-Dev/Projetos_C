#include <stdlib.h>
#include "application/services/Lista/ListaService.h"

void lista_insert(Lista* lista, int valor) {

    Node* novo = (Node*) malloc(sizeof(Node));

    if (novo == NULL) {
        return;
    }

    novo->valor = valor;
    novo->proximo = lista->inicio;

    lista->inicio = novo;

    lista->tamanho++;

}

/*
================================================================================
EXPLICAÇÃO COMPLETA DA FUNÇÃO lista_insert
================================================================================

Esta função é responsável por INSERIR um novo elemento dentro de uma
lista encadeada.

Mais especificamente, ela insere o novo elemento no INÍCIO da lista.

Para entender completamente essa função precisamos entender vários conceitos:

1) Alocação dinâmica de memória
2) Estrutura Node
3) Encadeamento de nós
4) Inserção no início da lista
5) Ponteiros
6) Manipulação da memória
7) Complexidade da operação

Vamos analisar passo a passo.

================================================================================
1) OBJETIVO DA FUNÇÃO
================================================================================

A função recebe dois parâmetros:

    Lista* lista
    int valor

Isso significa:

- lista -> ponteiro para a estrutura da lista
- valor -> valor que será armazenado no novo nó

O objetivo é criar um novo nó contendo esse valor
e inserir esse nó na lista.

Exemplo:

Lista atual:

    [10] -> [20] -> [30] -> NULL

Inserindo valor 5:

Resultado:

    [5] -> [10] -> [20] -> [30] -> NULL

Ou seja, o novo elemento vira o PRIMEIRO da lista.

================================================================================
2) ASSINATURA DA FUNÇÃO
================================================================================

void lista_insert(Lista* lista, int valor)

Significa:

lista  -> endereço da lista
valor  -> valor que será inserido

A função não retorna nada (void),
ela apenas modifica a lista diretamente.

Isso acontece porque passamos um ponteiro para a lista.

================================================================================
3) CRIAÇÃO DO NOVO NÓ
================================================================================

Node* novo = (Node*) malloc(sizeof(Node));

Essa linha faz três coisas importantes:

1) reserva memória
2) define o tipo do ponteiro
3) cria o novo nó

Vamos quebrar essa linha.

================================================================================
4) O QUE É malloc
================================================================================

malloc significa:

Memory Allocation

Ela serve para reservar memória dinamicamente
no HEAP.

Sintaxe:

malloc(tamanho_em_bytes)

Nesse caso:

sizeof(Node)

retorna o tamanho da estrutura Node em bytes.

Exemplo de Node:

typedef struct Node {
    int valor;
    struct Node* proximo;
} Node;

Então o tamanho será aproximadamente:

    int valor        -> 4 bytes
    ponteiro proximo -> 8 bytes (em sistemas 64 bits)

Total aproximado:

    12 ou 16 bytes dependendo do alinhamento da memória.

Então o malloc faz algo como:

"Reserve um bloco de memória grande o suficiente
para armazenar um Node".

================================================================================
5) O RETORNO DO MALLOC
================================================================================

malloc retorna:

void*

Ou seja:

um ponteiro genérico.

Por isso fazemos o cast:

(Node*)

Assim informamos ao compilador que aquele ponteiro
deve ser tratado como um ponteiro para Node.

Resultado final:

novo -> endereço de memória de um Node recém criado.

Visualmente:

novo
 ↓
[ memória reservada ]

================================================================================
6) VERIFICAÇÃO DE ERRO
================================================================================

if (novo == NULL) {
    return;
}

Essa verificação é EXTREMAMENTE importante.

Se o sistema não tiver memória disponível,
o malloc retorna NULL.

Se continuássemos usando esse ponteiro
o programa iria quebrar com:

Segmentation Fault.

Então verificamos:

"Se não conseguiu alocar memória, apenas saia da função."

================================================================================
7) ATRIBUIÇÃO DO VALOR
================================================================================

novo->valor = valor;

Aqui estamos preenchendo o campo valor do novo nó.

Exemplo:

Se chamarmos:

lista_insert(&lista, 50)

Então teremos:

novo->valor = 50

Visualmente:

Node novo

    valor = 50
    proximo = ?

================================================================================
8) ENCADEAMENTO DO NOVO NÓ
================================================================================

novo->proximo = lista->inicio;

Essa é uma das linhas mais importantes da função.

Aqui estamos conectando o novo nó
ao antigo primeiro elemento da lista.

Exemplo:

Lista atual:

lista->inicio
     ↓
    [10] -> [20] -> [30]

Depois dessa linha:

novo
 ├ valor = 5
 └ proximo -> [10]

Visualmente:

novo -> [10] -> [20] -> [30]

Ainda não atualizamos a lista.

================================================================================
9) ATUALIZAÇÃO DO INÍCIO DA LISTA
================================================================================

lista->inicio = novo;

Agora informamos à lista que o primeiro elemento mudou.

Antes:

lista->inicio -> [10]

Depois:

lista->inicio -> [5]

Estrutura final:

lista
 ↓
[5] -> [10] -> [20] -> [30]

O novo nó agora é oficialmente o primeiro da lista.

================================================================================
10) ATUALIZAÇÃO DO TAMANHO
================================================================================

lista->tamanho++;

Essa linha incrementa o contador de elementos da lista.

O operador ++ significa:

"somar 1".

Exemplo:

Antes da inserção:

tamanho = 3

Depois:

tamanho = 4

Manter esse contador atualizado é importante para:

- saber quantos elementos existem
- evitar percorrer a lista apenas para contar
- otimizar operações futuras

================================================================================
11) ESTADO DA MEMÓRIA (PASSO A PASSO)
================================================================================

Suponha a lista:

[10] -> [20] -> NULL

PASSO 1 — malloc

novo -> memória reservada

PASSO 2 — atribuir valor

novo
 ├ valor = 5
 └ proximo = ?

PASSO 3 — apontar para antigo início

novo
 ├ valor = 5
 └ proximo -> [10]

PASSO 4 — atualizar lista

lista->inicio -> novo

Resultado final:

[5] -> [10] -> [20] -> NULL

================================================================================
12) COMPLEXIDADE DA OPERAÇÃO
================================================================================

Essa operação tem complexidade:

O(1)

Isso significa:

tempo constante.

Não importa se a lista tem:

10 elementos
1000 elementos
1 milhão de elementos

A inserção no início sempre levará
o mesmo tempo.

Por isso listas encadeadas são muito eficientes
para inserções no início.

================================================================================
13) POR QUE INSERIR NO INÍCIO
================================================================================

Inserir no início é a operação mais rápida
em listas encadeadas.

Inserir no final exigiria:

percorrer toda a lista:

[10] -> [20] -> [30] -> NULL

até encontrar o último nó.

Isso seria:

O(n)

================================================================================
14) POSSÍVEIS ERROS SE FEITO INCORRETAMENTE
================================================================================

Se esquecermos:

novo->proximo = lista->inicio

perderíamos toda a lista existente.

Exemplo:

novo -> [5]

lista->inicio -> [5]

E os nós antigos ficariam perdidos na memória
(memory leak).

================================================================================
15) RESUMO FINAL
================================================================================

A função realiza 5 passos principais:

1) Aloca memória para um novo nó

Node* novo = malloc(sizeof(Node))

2) Verifica se a alocação deu certo

if (novo == NULL)

3) Armazena o valor dentro do nó

novo->valor = valor

4) Conecta o novo nó ao início da lista

novo->proximo = lista->inicio

5) Atualiza o início da lista

lista->inicio = novo

6) Atualiza o contador de elementos

lista->tamanho++

Assim garantimos que o novo elemento
foi inserido corretamente na lista.

================================================================================
*/