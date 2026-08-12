# Estruturas de Dados e seus Algoritmos 

## Objetivos
Consolidar conceitos de abstração de dados com a construção e a utilização de tipos abstratos de
dados: árvores, grafos e arquivos. Capacitar o aluno a manipular arquivos sequenciais e de acesso
direto, usando estruturas de índices.

## Tópicos Abordados

- Árvores binárias, binárias de busca e AVL;
- Grafos;
- Arquivos;
- Ordenação externa de arquivos binários e texto (para o último tipo de arquivo, a ordenação é
dividida em duas etapas: geração de partições classificadas e intercalação de partições);
- Árvores B e B+
- Tabelas hash (ou de dispersão) mantidas em memórias principal e secundária; e
- Listas de prioridade (ou heaps) mantidas em memórias principal e secundária.

## Bibliografia básica

- T.H. Cormen, C.E. Leiserson e R.L. Rivest, Introduction to algorithms, McGraw-Hill, 2009.
- J. Szwarcfiter e L. Markenzon, Estruturas de Dados e Algoritmos, LTC, 1994.
- W. Celes, R. Cerqueira e J.L. Rangel, Introdução a Estruturas de Dados, Campus, 2004.
- I.N. Ferraz, Programação com Arquivos, Manole Ltda, 2003.
- B.W. Kernighan e D.M. Ritchie, C: a linguagem de programação (Padrão ANSI), Campus, Segunda Edição, 1990.

## Bibliografia complementar

- A.M. Tenenbaum, Y. Langsam e M.J. Augenstein, Estruturas de Dados Usando C, Pearson,
Primeira Edição, 1995.
- R. Ramakrishnan, Database Management Systems, McGraw Hill, Third Edition, 2003.

## Ponteiros em C

-> Motivação para o estudo de ponteiros e listas simplesmente encadeadas;
-> Definição de listas simplesmente encadeadas;
-> Algumas operações iterativas do tipo abstrato de dados (TAD) lista simplesmente encadeada: (a) inicialização de uma lista e (b) inserção no início da lista; e
-> Operaçoẽs iterativas e recursivas desse TAD.

``` c

#include <stdio.h>

int main(void){
  int *pa, a, b;
  char *pc, c, d;
  double *pd, e, E;
  
  printf("a = %d[%p]\tb = %d[%p]\tpa = %p[%p]\n", a, &a, b, &b, pa, &pa);
  printf("c = %c->%d[%p]\td = %c->%d[%p]\tpc = %p[%p]\n", c, c, &c, d, d, &d, pc, &pc);
  printf("e = %.5f[%p]\tE = %.5f[%p]\tpd = %p[%p]\n\n\n", e, &e, E, &E, pd, &pd);
  
  pa = &a;
  pc = &c;
  pd = &e;
  (*pa) = 5;
  a++;
  c = 'A';
  (*pc)++;
  e = 102.3456789;
  printf("a = %d[%p]\tb = %d[%p]\tpa = %p[%p]\n", a, &a, b, &b, pa, &pa);
  printf("c = %c->%d[%p]\td = %c->%d[%p]\tpc = %p[%p]\n", c, c, &c, d, d, &d, pc, &pc);
  printf("e = %.5f[%p]\tE = %.5f[%p]\tpd = %p[%p]\n", e, &e, E, &E, pd, &pd);
  
  pa++;
  pc++;
  pd++;
  printf("a = %d[%p]\tb = %d[%p]\tpa = %p[%p]\n", a, &a, b, &b, pa, &pa);
  printf("c = %c->%d[%p]\td = %c->%d[%p]\tpc = %p[%p]\n", c, c, &c, d, d, &d, pc, &pc);
  printf("e = %.5f[%p]\tE = %.5f[%p]\tpd = %p[%p]\n\n\n", e, &e, E, &E, pd, &pd);

  (*pa) = (int) e;
  (*pc) = 'b';
  (*pd) = 25.252525;
  printf("a = %d[%p]\tb = %d[%p]\tpa = %p[%p]\n", a, &a, b, &b, pa, &pa);
  printf("c = %c->%d[%p]\td = %c->%d[%p]\tpc = %p[%p]\n", c, c, &c, d, d, &d, pc, &pc);
  printf("e = %.5f[%p]\tE = %.5f[%p]\tpd = %p[%p]\n\n\n", e, &e, E, &E, pd, &pd);

  pa++;
  pc++;
  pd++;
  printf("a = %d[%p]\tb = %d[%p]\tpa = %p[%p]\n", a, &a, b, &b, pa, &pa);
  printf("c = %c->%d[%p]\td = %c->%d[%p]\tpc = %p[%p]\n", c, c, &c, d, d, &d, pc, &pc);
  printf("e = %.5f[%p]\tE = %.5f[%p]\tpd = %p[%p]\n\n\n", e, &e, E, &E, pd, &pd);

  pa++;
  //(*pa) = 300; //falha de segmentacao aqui...
  pc++;
  (*pc) = 2;
  pd++;
  (*pa) *= 5;
  printf("a = %d[%p]\tb = %d[%p]\tpa = %p[%p]\n", a, &a, b, &b, pa, &pa);
  printf("c = %c->%d[%p]\td = %c->%d[%p]\tpc = %p[%p]\n", c, c, &c, d, d, &d, pc, &pc);
  printf("e = %.5f[%p]\tE = %.5f[%p]\tpd = %p[%p]\n\n\n", e, &e, E, &E, pd, &pd); 
  return 0; 
}

```


## TLSE_TA

-> Mais operações (versões iterativas e recursivas) do TAD lista simplesmente encadeada; e
-> Ordenação de listas usando o método selection sort e o algoritmo qsort implementado em stdlib.h, usando memória extra (isto é, uso de um vetor auxiliar) para realizar a operação.


## Arvores e Arvores Binaria

-> Conceitos de árvores;
-> Definição de árvores binárias;
-> Criação de uma árvore binária, a partir de uma informação considerada raiz, uma subárvore esquerda e subárvore direita;
-> Exemplo de uso: criação de uma árvore balanceada a partir de um vetor; e
-> Percorrimento em árvores binárias: pré-ordem (ou profundidade), simétrico, pós-ordem e em largura.

``` pdf Arvores

Árvores Material baseado nos
slides gentilmente
cedidos pela Professora
Vanessa Braganholo

Árvores

Instituto de Computação - UFF 2
Fonte de consulta: W.
Celes, R. Cerqueira e J.L.
Rangel, Introdução a
Estruturas de Dados,
Campus.

Árvores

Constituem uma das estruturas
mais importantes da área de
computação, em uma variedade de
aplicações

Dados devem ser dispostos de
maneira hierárquica

A

B C D

E F G H

I J K

Árvore de Grau-n
Sistema de Arquivos

Exemplos de Aplicações

Árvore de derivação
 Usada pelos compiladores

+

a

* /

b c +

d e

Expressão aritmética: ( a * b ) + ( c / ( d + e ) )

Exemplos de Aplicações

Ordenação de valores 200

100

150 350

170 250 500

400 600

Árvores

→ Forma mais natural: recursividade

→ Composta de um conjunto de nós

→ Um nó raiz contém ZERO ou mais subárvores, cujas as
raízes estão ligadas a raiz.

→ A? Filhos de A? Folhas? Irmãos de B? Primos de H? Pai de I?

A

B C D

E F G H

I J K
raiz

Terminologia

Raiz

B C

A

D

Terminologia A

B C D

E F G H

I J K

Sub-árvores (de A)
Raiz

Terminologia
(usando o nó X como referencial)

X Irmão

Pai

Filho

Filho
= filha
= descendente
= sucessor
Pai
= mãe
= ascendente
= antecessor

Irmão
= irmã

A

B C D

E F G H

I J K

Terminologia: GRAU De um
Nó

→ Grau
 número de sub-árvores do nó ou
 número de filhos de um nó

grau 3 grau 2

grau 1

Terminologia: Grau da Árvore

→ Grau de uma árvore
 máximo entre os graus de seus nós

A

B C D

E F G H

I J K
grau 3 grau 2

grau 1

Terminologia: Nó Interno

Nó interno (ou nó de derivação)
 nó com grau maior do que zero

A

B C D

E F G H

I J K

Terminologia: Nó Folha

Nó folha (nó terminal ou externo)
 nó com grau igual a zero

null null

A

B C D

E F G H

I J K

Terminologia: CAMINHO

→ Um caminho é uma
sequência de nós
consecutivos distintos entre
dois nós
 v1 alcança vk
 vk é alcançado por v1

→ CAMINHO ÚNICO entre v1 e
vk

A

B C D

E F G H

I J K
v1

vk

Terminologia: Comprimento
do Caminho

Comprimento do caminho
 Número de ligações entre os nós
do caminho

A

B C D

E F G H

I J K
v1

vk

Comprimento do
caminho= 3

Terminologia: Nível

Nível A

B C D

E F G H

I J K
nível 0

nível 3
nível 1

nível 2

Terminologia: ALTURA Da
árvore

Altura?
 Comprimento do caminho
mais longo entre o nó raiz até
uma das folhas
 Altura de nó raiz é 0

A

B C D

E F G H

I J K Altura = 3

Altura X Nível

A

B C D

E F G H

I J K

Nível 0

Nível 1

Nível 2

Nível 3

Altura = 3

Terminologia: Floresta

Floresta = Conjunto de árvores

A

B C D

E F G H

I J K

X

Y

M

N

O P

L

Q

R S T

TIPOS DE ÁRVORES

→ Número de filhos permitidos em cada nó:
✓ árvores n-árias x árvores binárias

→ Tipo de informações armazenadas:
✓ árvores homogêneas x árvores heterogêneas
```

``` pdf arvores bionaria

Árvores Binárias Material baseado nos slides
gentilmente cedidos pela
Professora Vanessa
Braganholo
Instituto de Computação - UFF 1

Árvores binárias

→ Árvores binárias são uma das
árvores mais usadas em
computação

→ Cada nó da árvore tem ou
ZERO, ou UM ou DOIS filhos.

Instituto de Computação - UFF 2
+

a

/*

b +c

d e

Expressão aritmética: ( a * b ) + ( c / ( d + e ) )

Definição recursiva

Uma árvore binária é:
– Ou uma árvore vazia;
– Ou um nó raiz com duas subárvores: a subárvore da esquerda
(SAE) e a subárvore da direita (SAD).

Instituto de Computação - UFF 3

Árvores Binárias

a

b c

d e gf

h i

→ Uma representação textual:
<R SAE SAD>
<a <b <d <h <> <>> <i <> <>>> <e <><>>><c <f <> <>>
<g <> <>>>>

→ Outra representação textual:
<X <> <>> ≡ <X>
<a <b <d <h> <i>> <e>> <c <f> <g>>>

Representação de Árvore
Binária em C

1

2 3

4 5
raiz

esq info dir Representação
do nó:
/* representação dos nós*/
typedef struct arvbin{
int info;
struct arvbin *esq, *dir;
}TAB;

Inicializar árvore

TAB* inicializa(void){
return NULL;
}

/* representação dos nós*/
typedef struct arvbin{
int info;
struct arvbin *esq, *dir;
}TAB;

Criar nó

TAB* cria(int r, TAB *sae, TAB *sad){
TAB *novo;
novo = (TAB *)malloc(sizeof(TAB));
novo->info = r;
novo->esq = sae;
novo->dir = sad;
return novo;
}

/* representação dos nós*/
typedef struct arvbin{
int info;
struct arvbin *esq, *dir;
}TAB;

Exemplo

1

2

3

4

5
raiz

i
n
t m
a
i
n
(
v
o
i
d
)
{

T
A
B *
a
5 = c
r
i
a
(
5
, N
U
L
L
, N
U
L
L
)
;

T
A
B *
a
4 = c
r
i
a
(
4
, N
U
L
L
, N
U
L
L
)
;

T
A
B *
a
2 = c
r
i
a
(
2
, N
U
L
L
, N
U
L
L
)
;

T
A
B *
a
3 = c
r
i
a
(
3
, a
4
, a
5
)
;

T
A
B *
a
1 = c
r
i
a
(
1
, a
2
, a
3
)
;

/
/
P
r
ó
x
i
m
a
s i
m
p
l
e
m
e
n
t
a
ç
õ
e
s
.
.
.

i
m
p
r
i
m
e
(
a
1
)
;

l
i
b
e
r
a
(
a
1
)
;

r
e
t
u
r
n 0
;

}

Caminhamentos em
Árvores Binárias

Consulta a um nó

Acesso sempre através da raiz
Cada nó deve ser “visitado” uma vez, e apenas uma vez

Visita a um nó:
 Acesso a um nó para realizar alguma operação

a
cb
d gfe

Método de percurso sistemático de todos os nós de uma árvore, de
modo a que cada nó seja visitado exatamente uma vez
Caminhamentos

a
cb
d gfe

Caminhamentos

→ Um caminhamento (ou percurso) define uma sequência de nós

→ Sequência de nós depende do caminhamento

→ Caminhamento pré-ordem (profundidade): raiz – esq – dir
a – b – d – e – c – f - g
→ Caminhamento simétrico: esq – raiz – dir
d – b – e – a – f – c - g
→ Caminhamento pós-ordem: esq – dir - raiz
d – e – b – f – g – c - a
→ Caminhamento em largura: por nível
a – b – c – d – e – f - g

a
c b
d gfe

Exemplo

130

100 200

83 120 230150

Profundidade ou pré-ordem?

Pós-ordem?

Simétrica?

```

# TAB

-> Mais operações de árvores binárias: impressão em pré-ordem ou profundidade (recursiva e iterativa usando pilha), impressão em largura (iterativa usando fila), impressão simétrica e impressão pós-ordem; liberação da árvore em pós-ordem; busca de uma informação na árvore em pré-ordem, e altura de uma árvore binária; e
-> Exemplo de uso: função que retorna uma árvore binária a partir de uma string, que segue a notação pré-fixada. Nessa string existe um espaço em branco entre cada informação e cada delimitador de sub-árvore.
TAB.zip
Arquivo compactado

lista01-EDA.pdf
PDF

## Lista de Exercícios de Estruturas de Dados e seus Algoritmos

(a) Implemente o tipo abstrato de dados lista simplesmente encadeada genérica, usando void *.
(b) Dada a seguinte representação de uma árvore binária:
typedef struct ab{
int info;
struct ab *esq, *dir;
}TAB;
Escreva as seguintes funções:
(Q1) cópia de uma árvore: TAB* copia (TAB *a);
(Q2) espelho de uma árvore (o que está a esquerda na árvore original, estará a direita no espelho, e
vice-versa): TAB* espelho (TAB *a);
(Q3) maior elemento da árvore: TAB* maior(TAB *a);
(Q4) menor elemento da árvore: TAB* menor(TAB *a);
(Q5) uma função que, dadas duas árvores deste tipo, testa se estas árvores são iguais. A função
retorna um se elas são iguais e zero, caso contrário. A função deve obedecer ao seguinte protótipo:
int igual (TAB* a1, TAB* a2);
(Q6) uma função em C que, dada uma árvore binária qualquer, retire todos os elementos pares da
árvore original. A função deve ter o seguinte protótipo: TAB* retira_pares (TAB* arv);
(Q7) se esta estrutura TAB tivesse um campo cor (int cor), defina uma função em C que, ao
receber uma árvore binária “sem cor” e totalmente balanceada (isto é, a distância da raiz a qualquer
folha da árvore é sempre a mesma), retorne esta árvore com os nós coloridos somente de vermelho e
preto, sendo que o nó pai NUNCA pode ter a mesma cor de seus filhos. A função deve possuir o
seguinte protótipo: void colore (TAB* arv);
(Q8) descubra a quantidade de nós internos: int ni(TAB *a);
(Q9) ache a quantidade de nós folha: int nf(TAB *a);