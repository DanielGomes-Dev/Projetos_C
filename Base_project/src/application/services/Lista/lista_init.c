#include <stddef.h>
#include "application/services/Lista/ListaService.h"

void lista_init(Lista* lista) {

    lista->inicio = NULL;
    lista->tamanho = 0;

}

/*
================================================================================
EXPLICAÇÃO COMPLETA DA FUNÇÃO lista_init
================================================================================

Esta função é responsável por INICIALIZAR uma estrutura de dados chamada LISTA.
Ela prepara a lista para ser utilizada pelo restante do programa.

Para entender completamente o que está acontecendo aqui precisamos entender
vários conceitos fundamentais da linguagem C:

1) STRUCT
2) PONTEIROS
3) PASSAGEM POR REFERÊNCIA
4) MEMÓRIA
5) LISTA ENCADEADA
6) VALOR NULL
7) ARQUITETURA DO PROJETO

Vamos explicar cada um deles.

================================================================================
1) O QUE É UMA LISTA ENCADEADA
================================================================================

Uma lista encadeada é uma estrutura de dados onde cada elemento aponta
para o próximo elemento.

Exemplo visual:

    [10] -> [20] -> [30] -> NULL

Cada bloco é chamado de NÓ (Node).

Cada nó contém duas coisas:

    valor
    ponteiro para o próximo nó

Exemplo de estrutura:

    Node
    ├ valor = 10
    └ proximo -> endereço do próximo nó

Isso permite criar estruturas dinâmicas na memória.

================================================================================
2) COMO A LISTA FOI DEFINIDA (STRUCT)
================================================================================

Em algum arquivo do projeto (normalmente Lista.h) existe algo assim:

typedef struct Node {
    int valor;
    struct Node* proximo;
} Node;

typedef struct {
    Node* inicio;
    int tamanho;
} Lista;

Explicando:

Node representa UM ELEMENTO da lista.

Node possui:

    valor
    ponteiro para próximo Node

Já a estrutura Lista representa A LISTA INTEIRA.

Ela possui:

    inicio  -> ponteiro para o primeiro nó
    tamanho -> quantidade de elementos

Visualmente:

Lista
 ├ inicio ----> Node
 └ tamanho

================================================================================
3) O QUE SIGNIFICA Lista* lista
================================================================================

A função foi declarada assim:

void lista_init(Lista* lista)

Isso significa:

"lista é um ponteiro para uma estrutura Lista"

Um ponteiro é uma variável que guarda o ENDEREÇO de memória de outra variável.

Exemplo:

Lista lista;

Isso cria uma variável chamada lista.

Na memória ficaria algo assim:

endereço 0x1000 -> Lista

Quando passamos para a função fazemos:

lista_init(&lista);

O operador & significa:

"pegue o endereço dessa variável"

Então a função recebe:

lista = 0x1000

Ou seja:

lista aponta para a estrutura real na memória.

================================================================================
4) POR QUE USAMOS PONTEIROS AQUI
================================================================================

Se a função fosse:

void lista_init(Lista lista)

Ela receberia uma CÓPIA da estrutura.

Isso significa que qualquer alteração feita dentro da função
não afetaria a lista original.

Mas quando usamos:

Lista* lista

Estamos passando o ENDEREÇO da lista.

Então podemos modificar diretamente o conteúdo dela.

================================================================================
5) O OPERADOR ->
================================================================================

Dentro da função temos:

lista->inicio = NULL;

O operador -> significa:

"acessar um campo de uma struct através de um ponteiro"

Ele é equivalente a:

(*lista).inicio

Explicando:

lista é um ponteiro
*lista acessa o conteúdo
.inicio acessa o campo

Então:

(*lista).inicio

é o mesmo que

lista->inicio

================================================================================
6) O QUE SIGNIFICA NULL
================================================================================

NULL significa:

"nenhum endereço"

ou

"ponteiro vazio"

Isso é muito importante em estruturas de dados.

Quando fazemos:

lista->inicio = NULL;

Estamos dizendo:

"A lista ainda não possui elementos"

Visualmente:

Lista
 ├ inicio -> NULL
 └ tamanho = 0

Ou seja:

lista vazia.

================================================================================
7) O CAMPO TAMANHO
================================================================================

A linha:

lista->tamanho = 0;

define que a lista começa com zero elementos.

Isso ajuda em várias operações futuras como:

- saber quantos elementos existem
- validar remoções
- otimizar algoritmos

================================================================================
8) ESTADO DA MEMÓRIA ANTES E DEPOIS
================================================================================

ANTES da inicialização:

A memória pode conter lixo.

Exemplo:

Lista
 ├ inicio -> ??????
 └ tamanho -> ??????

Depois da inicialização:

Lista
 ├ inicio -> NULL
 └ tamanho -> 0

Agora a lista está em um estado seguro para uso.

================================================================================
9) COMO ISSO SE CONECTA COM O RESTO DO PROJETO
================================================================================

Fluxo de execução:

main
 ↓
controller
 ↓
service
 ↓
estrutura de dados

Exemplo real no código:

main chama:

iniciar_lista()

controller chama:

lista_init(&lista)

Isso prepara a lista para as próximas operações:

lista_insert
lista_remove
lista_print

================================================================================
10) POR QUE ESSA FUNÇÃO É IMPORTANTE
================================================================================

Sem essa função a lista começaria com valores aleatórios
na memória, causando erros como:

- segmentation fault
- acesso a memória inválida
- loops infinitos

Por isso toda estrutura de dados precisa de uma função
de inicialização.

================================================================================
11) RESUMO FINAL
================================================================================

Essa função faz apenas duas coisas:

1) define que a lista começa vazia

lista->inicio = NULL

2) define que o tamanho da lista é zero

lista->tamanho = 0

Com isso garantimos que a estrutura está pronta
para receber elementos com segurança.

================================================================================
*/