# Resumo dos Livros — 7.1 Conceitos

## Celes — Introdução a Estruturas de Dados (Cap. 9, "Tipos abstratos de dados" — seção "Tipo abstrato de dados")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção de número de capítulo: é o **Cap. 9** (abre a Parte II, "Estruturas dinâmicas"), não o 4 — mas a descrição do conteúdo já estava certa. Citação quase literal do livro para a definição: um módulo caracteriza um TAD quando "define um novo tipo de dado e o conjunto de operações para manipular dados desse tipo" — e "abstrato significa 'esquecida a forma de implementação', ou seja, um TAD é descrito pela finalidade do tipo e de suas operações, e não pela forma como está implementado".

Mecânica concreta em C (desenvolvida com o exemplo completo `Ponto`, ver [[../../4 PROGRAMAÇÃO COM MÓDULOS/Resumo dos Livros|4 Programação com Módulos]]): a interface (`.h`) exporta **apenas** o nome do tipo (`typedef struct ponto Ponto;`, sem os campos) e os protótipos das funções; a implementação (`.c`) é o único arquivo que conhece os campos reais da `struct`. Consequência direta, que o livro enuncia explicitamente: **o cliente do TAD não pode acessar os campos diretamente** — só através das funções exportadas — e **a implementação pode ser trocada por completo sem quebrar código cliente**, desde que a interface não mude.

Convenção de nomenclatura que o livro adota daqui em diante em **todo** TAD do restante da obra: prefixar cada função exportada com um identificador curto do tipo (`pto_` para `Ponto`, e mais adiante `pilha_`, `fila_`, `lista_` etc.) — evita colisão de nomes entre módulos diferentes, já que C não tem sobrecarga de função. Recomenda ainda que variáveis globais e funções auxiliares internas de um módulo sejam `static`, para não vazarem para fora do arquivo.

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos

## Szwarcfiter — Estruturas de Dados e Seus Algoritmos
Szwarcfiter não dedica uma seção isolada ao conceito de "tipo abstrato de dados" como entidade teórica separada — o termo aparece de passagem no Capítulo 1 (Preliminares), ao contextualizar o que é uma estrutura de dados: "Quando os dados são dispostos e manipulados de uma forma homogênea, constituem um tipo abstrato de dados. Este é composto por um modelo matemático acompanhado por um conjunto de operações definido sobre esse modelo." O livro segue direto para as estruturas concretas (listas, árvores, heaps etc.), tratando o TAD como um pano de fundo implícito, não como um capítulo próprio.

## Síntese
Este subtópico é essencialmente território do Celes: é o único dos livros da bibliografia do curso a isolar o conceito de TAD em um capítulo dedicado, com o par interface/implementação como eixo central e uma convenção de nomenclatura própria (prefixo por tipo) que reaparece em toda estrutura de dados do restante do livro. Szwarcfiter reconhece a mesma ideia — a definição de "modelo matemático + conjunto de operações" citada acima é, na prática, a mesma noção de TAD do Celes —, mas a trata en passant, sem se deter nela; o interesse do livro está nos algoritmos concretos que seguem.

## Exemplos em C

**O esqueleto que todo TAD do Celes segue — troque `Item`/`ITEM_` pelo tipo real (Pilha, Fila, Lista...):**
```c
/* item.h — a ÚNICA coisa que um módulo cliente pode ver */
typedef struct item Item;

Item* item_cria(int valor);
int   item_valor(Item* it);
void  item_libera(Item* it);
```
```c
/* item.c — a struct real fica ESCONDIDA aqui; pode mudar sem afetar item.h */
#include <stdlib.h>
#include "item.h"

struct item {
    int valor;
    /* amanhã podemos adicionar campos aqui sem quebrar nenhum código cliente */
};

Item* item_cria(int valor) {
    Item* it = malloc(sizeof(Item));
    it->valor = valor;
    return it;
}
int  item_valor(Item* it) { return it->valor; }
void item_libera(Item* it) { free(it); }
```
```c
/* cliente.c — não sabe (nem precisa saber) o que tem dentro de struct item */
#include <stdio.h>
#include "item.h"

int main(void) {
    Item* it = item_cria(42);
    printf("%d\n", item_valor(it));
    /* it->valor = 10;  <-- ERRO de compilação: struct item é incompleta aqui */
    item_libera(it);
    return 0;
}
```
