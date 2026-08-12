ÁRVORES AVL Material baseado nos slides
gentilmente cedidos pela
Professora Vanessa
Braganholo

RECAPITULANDO:
ÁRVORES BINÁRIAS DE
BUSCA
Apresentam uma relação de ordem
A ordem é definida pela chave
Operações:
 inserir
 consultar
 excluir

500

300 800

150 400 600 900

INSTITUTO DE COMPUTAÇÃO - UFF 2

PROBLEMAS COM ÁRVORE
BINÁRIA DE BUSCA (ABB)

Desbalanceamento progressivo →
Inserção e Retirada

Exemplo: inserção de {24, 27, 13, 10,
56, 15, 30}

24

13 27

10 15 56

30
INSTITUTO DE COMPUTAÇÃO - UFF 3

PROBLEMAS COM ABB

Desbalanceamento progressivo →
Inserção e Retirada

Exemplo: inserção de {13, 10, 15, 24,
27, 30, 56}

13

10 15

24

30
27

56
INSTITUTO DE COMPUTAÇÃO - UFF 4

PROBLEMAS COM ABB

Desbalanceamento progressivo →
Inserção e Retirada

Exemplo: inserção de {1, 13, 24, 27,
56}

1

13

24

56

27

INSTITUTO DE COMPUTAÇÃO - UFF 5

CONSEQUÊNCIA

Buscas ficam mais custosas

INSTITUTO DE COMPUTAÇÃO - UFF 6

1

13

24

56

27

BALANCEAMENTO DE
ÁRVORES

→ Distribuição equilibrada dos nós

→ Objetivo:
– Otimizar as operações de consulta
– Diminuir o número médio de comparações

→ Busca, Inserção e retirada: O(log n) no pior caso

INSTITUTO DE COMPUTAÇÃO - UFF 7

ÁRVORES AVL
ADELSON-VELSKII E LANDIS
(1962)

Uma árvore binária de busca (ABB) é uma
AVL quando, para qualquer um de seus nós,
o módulo da diferença entre as alturas de
suas subárvores esquerda e direita é, no
máximo, 1.

INSTITUTO DE COMPUTAÇÃO - UFF 8

EXERCÍCIO

Verifique quais das ABB são AVL

130

100 150

110
80 120 200

120

100 130

150

80 110 200

INSTITUTO DE COMPUTAÇÃO - UFF 9

RESPOSTA

AVL ABB

INSTITUTO DE COMPUTAÇÃO - UFF 10
120

100 130

150

80 110 200

Diferença entre alturas
das subárvores é 2

130

100 150

110
80 120 200

FATOR DE BALANCEAMENTO
(FB)

Fator de Balanceamento: diferença entre altura da subárvore
esquerda e direita
FB(no) = altura(no->esq) – altura(no->dir)

130

100 150

110
80 120 200

120

100 130

150

80 110 200

Módulo da diferença entre alturas
das subárvores é 2 (FB = -2)

1

-1 -1

0 0

0

1

0

0 0 1
-2 0

-1

INSTITUTO DE COMPUTAÇÃO - UFF 11

FATOR DE BALANCEAMENTO
(FB)

FB precisa ser -1, 0 ou +1 em todos os nós da árvore para que
árvore seja AVL.
130

100 150

110
80 120 200

120

100 130

150

80 110 200

Módulo da diferença entre alturas
das subárvores é 2 (FB = -2)

1

-1 -1

0 0

0

1

0

0 0 1
-2 0

-1

INSTITUTO DE COMPUTAÇÃO - UFF 12

EXERCÍCIO

Verifique quais das ABB são AVL:

42

15 88

20
6 27 63 94

57 71

42

15 88

6 27 63 94

42

15 88

20
27 63

57 71
INSTITUTO DE COMPUTAÇÃO - UFF 13

OPERAÇÕES

Inserção e Exclusão devem preservar as propriedades da AVL

INSTITUTO DE COMPUTAÇÃO - UFF 14

0 1
-1

1

0

0
-1

INSERÇÃO

INSTITUTO DE COMPUTAÇÃO - UFF 15

→ Como em ABB: inserção na folha,
verificando a propriedade AVL

→ Verificação da propriedade AVL: no
caminho da folha até a raiz

1 1
0

1

0

0
-1

0

INSERÇÃO

INSTITUTO DE COMPUTAÇÃO - UFF 16

1 1
0

0

0

-1
-2

0

0

→ Como em ABB: inserção na folha,
verificando a propriedade AVL

→ Verificação da propriedade AVL: no
caminho da folha até a raiz

→ Como manter o balanceamento? Por
meio de rotações

→ Característica da operação de
rotação: preservar a ordem das chaves.

INSERÇÃO

INSTITUTO DE COMPUTAÇÃO - UFF 17
Balancear árvore

1 1
0

0

0

-1
-2

0 0

RESUMINDO...

→ Quando uma inserção ou exclusão faz com que a árvore perca as
propriedades de árvore AVL, deve-se realizar uma operação de
Rotação

→ Rotação preserva a ordem das chaves, de modo que a árvore
resultante é uma árvore binária de busca válida e é uma árvore AVL
válida

INSTITUTO DE COMPUTAÇÃO - UFF 18

BALANCEAMENTO DE
ÁRVORES AVL POR ROTAÇÃO

→ Considere:
– P a raiz da subárvore desbalanceada
– D a sua subárvore direita (SAD)
– E a sua subárvore esquerda (SAE)

INSTITUTO DE COMPUTAÇÃO - UFF 19

ROTAÇÃO SIMPLES DIREITA
(RSD) ≡ LL

20

RSD(P):
– FB(P) = 2
– FB(E) ≥ 0

1

0

0 0

2

0

120

110 150

100

80

130 200

0

0

0 0 0

120

110 150

100 130 200

P

E

1

1

ROTAÇÃO SIMPLES DIREITA
(RSD) ≡ LL

21

1

0

0 0

2

1

0

120

110 150

100

80

130 200

0

0

0 0

0

0 0
120

100 150

80 110 130 200

RSD(P):
– FB(P) = 2
– FB(E) ≥ 0

P

E

ROTAÇÃO SIMPLES DIREITA
(RSD) ≡ LL

22

RSD(P):
– FB(P) = 2
– FB(E) ≥ 0

42

15 88

6 27

2

0 1

1 0

0 4

15

6

4 27 88

0

0 1

0 0 0
42

IMPLEMENTAÇÃO DE RSD

/* representação dos nós*/
typedef struct avl{
int info;
int alt;
struct avl *esq, *dir;
}TAVL;
int maximo(int x, int y){
if(x >= y) return x;
return y;
}
int alt(TAVL *a){
if(!a) return -1;
return a→alt;
}
TAVL *RSD(TAVL *a){
TAVL *novo = a→esq;
a→esq = novo→dir;
novo→dir = a;
a→alt = 1 + maximo (alt(a→esq), alt(a→dir));
novo→alt = 1 + maximo (alt(novo→esq), alt(novo→dir));
return novo;
} INSTITUTO DE COMPUTAÇÃO - UFF 23

ROTAÇÃO SIMPLES ESQUERDA
(RSE) ≡ RR

24

RSE(P):
– FB(P) = -2
– FB(D) ≤ 0

120

100 130

80 110 150

0

0

0 0 0

120

100 130

150

200

80 110

-1

0

0 0

0
-2

-1

-1

P

E

ROTAÇÃO SIMPLES ESQUERDA
(RSE) ≡ RR

25

RSE(P):
– FB(P) = -2
– FB(D) ≤ 0

120

100 130

150

200

80 110

-1

0

0 0

0
-2

-1

P

E

120

100 150

80 110 130 200

0

0

0 0

0

0 0

42

15 88

67 94

90

EXEMPLO 2: INSERIR 90?

INSTITUTO DE COMPUTAÇÃO - UFF 26

IMPLEMENTAÇÃO DE RSE

/* representação dos nós*/
typedef struct avl{
int info;
int alt;
struct avl *esq, *dir;
}TAVL;
int maximo(int x, int y){
if(x >= y) return x;
return y;
}
int alt(TAVL *a){
if(!a) return -1;
return a→alt;
}
TAVL *RSE(TAVL *a){
TAVL *novo = a→dir;
a→dir = novo→esq;
novo→esq = a;
a→alt = 1 + maximo (alt(a→esq), alt(a→dir));
novo→alt = 1 + maximo (alt(novo→esq), alt(novo→dir));
return novo;
} INSTITUTO DE COMPUTAÇÃO - UFF 27

ROTAÇÃO ESQUERDA
DIREITA (RED) ≡ LR

INSTITUTO DE COMPUTAÇÃO - UFF 28

RED(P):
– FB(P) = 2
– FB(E) < 0
RED(P):
1o RSE(E)
2o RSD(P)

120

110 150

80 130 200

0

1

0 0 0
0

120

110 150

80 130 200

1

2

-1

0 0
0

100
0
P

E

ROTAÇÃO ESQUERDA
DIREITA (RED) ≡ LR

INSTITUTO DE COMPUTAÇÃO - UFF 29

120

110 150

80 130 200

1

2

-1

100
P

E

120

110 150

100 130 200

1

2

1

0 0
P 0

80
0 RSE(E)

RED(P):
– FB(P) = 2
– FB(E) < 0
RED(P):
1o RSE(E)
2o RSD(P)

ROTAÇÃO ESQUERDA
DIREITA (RED) ≡ LR

120

110 150

100 130 200

1

2

1

P 0

80

120

150

130 200
0

RSD(P) 0 100

80 110
0

RED(P):
– FB(P) = 2
– FB(E) < 0
RED(P):
1o RSE(E)
2o RSD(P)

EXEMPLO: INSERIR 34?

42

15 88

6 27

IMPLEMENTAÇÃO DE RED

/* representação dos nós*/
typedef struct avl{
int info;
int alt;
struct avl *esq, *dir;
}TAVL;
int maximo(int x, int y){
if(x >= y) return x;
return y;
}
int alt(TAVL *a){
if(!a) return -1;
return a→alt;
}
TAVL *RED(TAVL *a){
a→esq = RSE(a→esq);
a = RSD(a);
return a;
}

INSTITUTO DE COMPUTAÇÃO - UFF 32

ROTAÇÃO DIREITA
ESQUERDA (RDE) ≡ RL

INSTITUTO DE COMPUTAÇÃO - UFF 33

RDE(P):
– FB(P) = -2
– FB(D) > 0
RDE(P):
1o RSD(D)
2o RSE(P)

120

100 130

80 110 200

0

-1

120

100 130

200

150

80 110

-1

-2

1

0 0

ROTAÇÃO DIREITA
ESQUERDA (RDE) ≡ RL

INSTITUTO DE COMPUTAÇÃO - UFF 34

RDE(P):
– FB(P) = -2
– FB(D) > 0
RDE(P):
1o RSD(D)
2o RSE(P)

120

100 130

200

150

80 110

-1

-2

1

0

120

100 130

150

200

80 110

P

D

RSD(D) -2

-1

ROTAÇÃO DIREITA
ESQUERDA (RDE) ≡ RL

INSTITUTO DE COMPUTAÇÃO - UFF 35

RDE(P):
– FB(P) = -2
– FB(D) > 0
RDE(P):
1o RSD(D)
2o RSE(P)

120

100 130

150

200

80 110

-2

-1
RSE(P)

120

100 150

80 110 130 200

IMPLEMENTAÇÃO DE RDE

/* representação dos nós*/
typedef struct avl{
int info;
int alt;
struct avl *esq, *dir;
}TAVL;
int maximo(int x, int y){
if(x >= y) return x;
return y;
}
int alt(TAVL *a){
if(!a) return -1;
return a→alt;
}
TAVL *RDE(TAVL *a){
a→dir = RSD(a→dir);
a = RSE(a);
return a;
}

---


IMPLEMENTAÇÃO DE
INSERÇÃO

/* representação dos nós */
typedef struct avl{
int info;
int alt;
struct avl *esq, *dir;
}TAVL;
TAVL *insAVL(TAVL *a, int elem){
if(!a){
a = (TAVL *) malloc(sizeof(TAVL));
a→info = elem;
a→alt = 0;
a→esq = a→dir = NULL;
return a;
}
...

if(elem < a→info){
a→esq = insAVL(a→esq, elem);
if(FB(a) == 2){
if(elem < a→esq→info) a = RSD(a);
else a = RED(a);
}
}
else if(elem > a→info){
a→dir = insAVL(a→dir, elem);
if(FB(a) == -2){
if(elem > a→dir→info) a = RSE(a);
else a = RDE(a);
}
}
a→alt = 1 + maximo(alt(a→dir), alt(a→esq));
return a;
}

EXERCÍCIOS

Inserir nós com as seguintes chaves em uma árvore AVL, fazendo
rotações, caso seja necessário, e anotando as rotações realizadas:
{50, 40, 30, 45, 47, 55, 56, 1, 2, 3, 49}

INSTITUTO DE COMPUTAÇÃO - UFF 38

COMO FAZER REMOÇÃO EM
AVL?

→ Parecido com ABB, exceto pelas rotações que podem ser feitas
(do nó inserido até a raiz), caso seja necessário

→ Mais complicada que a inserção

→ TRÊS situações possíveis:
(1) retirar folha (mais simples);
(2) retirar um nó com um filho; e
(3) retirar um nó com dois filhos:
[a] encontrar a informação que precede o elemento a ser retirado (maior elemento da esquerda);
[b] trocar a informação do nó a ser retirado com a informação do nó encontrado no passo [a]; e
[c] retirar o nó encontrado no passo [a].

INSTITUTO DE COMPUTAÇÃO - UFF 39

RESUMINDO AS ROTAÇÕES...

INSTITUTO DE COMPUTAÇÃO - UFF 40

RSD(P):
● FB(P) = 2
● FB(E) ≥ 0
RSE(P):
● FB(P) = -2
● FB(D) ≤ 0
RED(P):
● FB(P) = 2
● FB(E) < 0
RED(P):
1o
RSE(E)
2o
RSD(P)
RDE(P):
● FB(P) = -2
● FB(D) > 0
RDE(P):
1o
RSD(D)
2o
RSE(P)

EXERCÍCIO

Remover os nós de chave 400,
140, 120, 130, 150, 200, 250,
350

220

120 300

100 150 260 400

80 110 130 200 250 270 350

140