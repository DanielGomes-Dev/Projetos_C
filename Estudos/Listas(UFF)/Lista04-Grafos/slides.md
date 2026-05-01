GRAFOS E DIGRAFOS

Material baseado nos slides
gentilmente cedidos pela
Professora Vanessa
Braganholo

4

2

31

5

6

GRAFOS

De
finições
Representação
Algoritmos  Busca  Inserção (arestas e vértices)  Exclusão (arestas e vértices)

GRAFOS

Grafos são estruturas de dados formadas por um conjunto de
vértices e um conjunto de arestas.

INSTITUTO DE COMPUTAÇÃO - UFF 3

4 2

3
1

5 6

vértices
arestas

APLICAÇÕES DE GRAFOS

Associando-se significados aos vértices e às arestas, o grafo
passa a constituir um modelo de uma situação ou informação real

4 2

3
1

5 6

vértices
arestas

GRADE CURRICULAR

INSTITUTO DE COMPUTAÇÃO - UFF 5

ROTAS
DE VOOS

INSTITUTO DE COMPUTAÇÃO - UFF 6

Fonte da imagem: https://www.aviacaocomercial.net/rotastam.htm

INTERNET (MAPA DE CABOS
SUBMARINOS)

INSTITUTO DE COMPUTAÇÃO - UFF 7

Fonte da imagem: https://mhemann.com.br/wp-content/uploads/2017/07/mapacabossubmarinos.jpg

MAPA DE
ESTRADAS

INSTITUTO DE COMPUTAÇÃO - UFF 8 Fonte da imagem: http://www.sp-turismo.com/mapa.htm

MAPA DE
METRÔ

INSTITUTO DE COMPUTAÇÃO - UFF 9

REDES SOCIAIS

INSTITUTO DE COMPUTAÇÃO - UFF 10

Fonte da imagem: https://thenextweb.com/contributors/2017/08/21/blockchain-can-make-social-networks-private-profitable/

PROCESSOS/TAREFAS

INSTITUTO DE COMPUTAÇÃO - UFF 11 Fonte da imagem: https://www.softwareadvice.com/resources/what-is-critical-path/

OUTRAS APLICAÇÕES

Cada vértice é uma página na internet. Cada arco é um link que
leva de uma página a outra.
Os vértices são times de futebol e os arcos são os jogos entre os
times durante um campeonato.
Os vértices são as casas de um tabuleiro de xadrez. Há um
arco de x para y se uma peça do jogo pode ir de x a y em um só
movimento.

GRAFOS –
DEFINIÇÕES

DEFINIÇÃO FORMAL

Um grafo

G é representado por

um conjunto (não vazio)

V de

vértices e um conjunto
(possivelmente vazio)

E de

arestas (edges
)

G = (V, E)
|V| é a quantidade de vértices
de G
|E| é a quantidade de arestas de
G

4

2

31

5

6

GRAFOS ORIENTADOS X NÃO
ORIENTADOS

As arestas podem ter uma direção ou podem ser bi-direcionais
Grafos orientados: as arestas possuem uma direção
 Também são chamados de grafos dirigidos ou digrafos
Grafos não orientados: as arestas são bi-direcionais (se existe
uma conexão a → b então também existe uma conexão b → a)

INSTITUTO DE COMPUTAÇÃO - UFF 15

GRAFO ORIENTADO
(DIRIGIDO OU DIGRAFO)

Arestas possuem uma direção
Alguns autores usam o termo arco para as arestas de um grafo
dirigido
Exemplo:
G = (V, E)
V = {1, 2, 3, 4, 5}
E = {(1, 5), (2, 3), (2, 4), (3, 2), (4, 3), (5, 2), (5, 4)}

INSTITUTO DE COMPUTAÇÃO - UFF 16
5

1

2

4 3

GRAFO ORIENTADO
(DIRIGIDO OU DIGRAFO)

Arestas possuem uma direção
Alguns autores usam o termo arco para as arestas de um grafo
dirigido
Exemplo:
G = (V, E)
V = {1, 2, 3, 4, 5}
E = {(1, 5), (2, 3), (2, 4), (3, 2), (4, 3), (5, 2), (5, 4)}

INSTITUTO DE COMPUTAÇÃO - UFF 17
5

1

2

4 3

GRAFO ORIENTADO
(DIRIGIDO OU DIGRAFO)

Exemplos:
Malha de transporte urbano
Pessoa A segue pessoa B no Instagram (mas o contrário
nem
sempre é verdadeiro)

INSTITUTO DE COMPUTAÇÃO - UFF 18
5

1

2

4 3

GRAFO NÃO ORIENTADO

Arestas são bi-direcionais
G = (V, E)
V = {1, 2, 3, 4, 5, 6}
E = {{1, 2}, {1, 3}, {1, 4}, {2,
3}, {2, 4}, {2, 6}, {3, 5}, {4,
5}, {4, 6}, {6, 2}}

INSTITUTO DE COMPUTAÇÃO - UFF 19
4 2

3
1

5 6

GRAFO NÃO ORIENTADO

Arestas são bi-direcionais
G = (V, E)
V = {1, 2, 3, 4, 5, 6}
E = {{1, 2}, {1, 3}, {1, 4}, {2,
3}, {2, 4}, {2, 6}, {3, 5}, {4,
5}, {4, 6}, {6, 2}}

INSTITUTO DE COMPUTAÇÃO - UFF 20
4 2

3
1

5 6

GRAFO NÃO ORIENTADO

Exemplo:
Amigos no Facebook (se A é
amigo de B, B também é amigo
de A)
 Mapa de cabeamento de uma
rede (se é possível enviar dados
do ponto A ao ponto B, então
também é possível enviar do
ponto B ao ponto A)

INSTITUTO DE COMPUTAÇÃO - UFF 21
4 2

3
1

5 6

GRAFOS ORIENTADOS X NÃO
ORIENTADOS

Um grafo expressa uma relação binária R
Grafo não orientado
 {v1, v2} ∈ G(E) ⇔ v1 R v2 ^ v2 R v1
 Exemplo: R = amigo no Facebook
Grafo orientado
 (v1, v2) ∈ G(E) ⇔ v1 R v2
 Exemplo: R = seguir alguém no Instagram

INSTITUTO DE COMPUTAÇÃO - UFF 22

DEFINIÇÕES E
TERMINOLOGIA

Um grafo é valorado se possuir
valores (pesos) associados às
arestas e/ou aos vértices
Exemplo: num grafo de rotas de
voo, uma aresta pode ser
valorada com a distância entre
os dois aeroportos que ela
conecta

INSTITUTO DE COMPUTAÇÃO - UFF 23

6

1

4 3
2

5
23 8
15 17
7

919

DEFINIÇÕES E
TERMINOLOGIA

Um vértice v1 é adjacente a um vértice v2 em G, se existe uma
aresta conectando v1 a v2 em G.
Em grafo não orientado: v1 é adjacente a v2 se existe aresta
{v1,v2} (nesse caso v2 também é adjacente a v1)
Em grafo orientado, v1 é adjacente a v2 se existe aresta (v1, v2)

INSTITUTO DE COMPUTAÇÃO - UFF 24
v1 v2 v1 v2 v1 v2

adjacência é
simétrica adjacência não é simétrica

Grafo não-
orientado

Grafo orientado

DEFINIÇÕES E
TERMINOLOGIA

Dados dois vértices adjacentes v1 e v2
Em um grafo orientado, uma aresta (v1, v2) é incidente de (sai
de) v1 e é incidente a (entra em) v2

Em um grafo não orientado, uma aresta {v1, v2} é incidente
em v1 e v2

INSTITUTO DE COMPUTAÇÃO - UFF 25

v1 v2

v1 v2

DEFINIÇÕES E
TERMINOLOGIA

O grau de um vértice é o número de arestas que nele/dele incidem

INSTITUTO DE COMPUTAÇÃO - UFF 26

v1

v2 v3 v4

v5 v6 v7
v8

DEFINIÇÕES E
TERMINOLOGIA

O grau de um vértice é o número de arestas que nele/dele incidem

INSTITUTO DE COMPUTAÇÃO - UFF 27

v1

v2 v3 v4

v5 v6 v7
v8

2

0

4 4

4

3

3 4

Vértices com grau 0 são
ditos vértices isolados

DEFINIÇÕES E
TERMINOLOGIA

A ordem de um grafo é o número de vértices que ele possui
G = (V, E)
ordem(G) = |V|

INSTITUTO DE COMPUTAÇÃO - UFF 28

v1

v2 v3 v4

v5 v6 v7
v8

DEFINIÇÕES E
TERMINOLOGIA

O caminho de tamanho k entre dois vértices v1 e v2 é a
sequencia <v0, v1, ..., vk>, onde v0 = v1, vk = v2, e (vi-1, vi

)  G(E)

(ou {vi-1, vi

}  G(E)) para i=1..k

O caminho contém os vértices v0, v1, ..., vk, e as arestas (v0, v1),
(v1, v2), ... (vk-1, vk) (ou {v0, v1}, {v1, v2}, ... {vk-1, vk} para grafos não
orientados)
Exemplo:
 Caminho de tamanho 1 entre os vértices 1 e 3:
 Vértices: {1, 3}
 Arestas: {{1, 3}}
 Caminho de tamanho 2 entre os vértices 1 e 3:
 Vértices: {1, 2, 3}
 Arestas: {{1, 2}, {2, 3}} INSTITUTO DE COMPUTAÇÃO - UFF 29

4 2

1

5 3

DEFINIÇÕES E
TERMINOLOGIA

Se existe um caminho entre v1 e v2, diz-se que v2 é alcançável a
partir de v1
O caminho é simples se todos os vértices no caminho são distintos
Exemplo:
 3 é alcançável a partir de 4
 2 não é alcançável a partir de 1

INSTITUTO DE COMPUTAÇÃO - UFF 30

4 2

1

5 3

DEFINIÇÕES E
TERMINOLOGIA

Um grafo é dito conectado se existe um caminho ligando cada par
de vértices

INSTITUTO DE COMPUTAÇÃO - UFF 31

v2 v3

v1

v4 v5

Conectado

v2 v3

v1

v4 v5

Não Conectado

DEFINIÇÕES E
TERMINOLOGIA

Um grafo é dito completo se todos os seus pares de vértices forem
adjacentes

INSTITUTO DE COMPUTAÇÃO - UFF 32

v2 v3

v1

v4 v5

DEFINIÇÕES E
TERMINOLOGIA

Uma aresta que tem ambas as extremidades em um mesmo vértice
é chamada laço

INSTITUTO DE COMPUTAÇÃO - UFF 33

v1

DEFINIÇÕES E
TERMINOLOGIA

Um caminho <v0, v1, ..., vk> forma um ciclo se v0 = vk e o caminho
contém pelo menos uma aresta
Exemplo: caminho de v1 a v1

INSTITUTO DE COMPUTAÇÃO - UFF 34

v2 v3

v1

v4 v5

DEFINIÇÕES E
TERMINOLOGIA

Um grafo sem ciclos é dito acíclico

INSTITUTO DE COMPUTAÇÃO - UFF 35

v2 v3

v1

v4 v5

v2 v3
v1

v4 v5

v2 v3

v1

v4 v5
Cíclico Acíclico Acíclico

DEFINIÇÕES E
TERMINOLOGIA

Um grafo é dito simétrico se para cada aresta (v, w) existe uma
aresta (w, v)

INSTITUTO DE COMPUTAÇÃO - UFF 36

v1 v2

v3 v4

---

GRAFOS –
REPRESENTAÇÕES

INSTITUTO DE COMPUTAÇÃO - UFF 37

REPRESENTAÇÃO FÍSICA DE
GRAFOS

Matriz de adjacência
Matriz de incidência
Lista de adjacência
Lista de incidência

INSTITUTO DE COMPUTAÇÃO - UFF 38

REPRESENTAÇÃO FÍSICA DE
GRAFOS

Matriz de adjacência
Matriz de incidência
Lista de adjacência
Lista de incidência

INSTITUTO DE COMPUTAÇÃO - UFF 39

MATRIZ DE ADJACÊNCIA

Matriz de adjacência A(n x n) de um grafo G de
ordem n, é uma matriz onde cada elemento ai,j é:
Grafos orientados:
 ai,j = 1 se (vi,vj)  G(E)
 ai,j = 0 se (vi,vj)  G(E)
Grafos não orientados: ai,j = aj,i
 ai,j = 1 se {vi,vj}  G(E)
 ai,j = 0 se {vi,vj}  G(E)

MATRIZ DE ADJACÊNCIA

A matriz de adjacência é uma forma de representação de grafos
simples, econômica e adequada para muitos problemas que
envolvem apenas a estrutura do grafo

1

6 5

4

2 3

vértices vértices

1 2 3 4 5 6
1 0 1 0 1 0 1
2 0 0 1 1 0 0
3 0 0 0 0 0 0
4 0 0 1 0 1 0
5 0 0 0 1 0 1
6 0 1 0 1 0 0

1

4

2

3

1 2 3 4
1 0 1 1 0
2 1 0 1 1
3 1 1 0 1
4 0 1 1 0

MATRIZ DE ADJACÊNCIA
PARA
GRAFO NÃO ORIENTADO

1

4

2

3

1 2 3 4
1 0 1 1 0
2 0 1 1
3 0 1
4 0

MATRIZ DE ADJACÊNCIA
PARA
GRAFO NÃO ORIENTADO

Matriz é simétrica

MATRIZ DE ADJACÊNCIA
PARA GRAFOS VALORADOS

Valores associados às linhas podem ser representados por uma
extensão simples da Matriz de Adjacência
 aij = k se (vi
,vj
)  G(E)

 aij = * se (vi
,vj
)  G(E) 1 2 3 4 5 6
1 * 9 * 7 * 19
2 9 * 23 15 * *
3 * 23 * 27 * *
4 7 15 27 * 30 17
5 * * * 30 * 8
6 19 * * 17 8 *

6

1

4 3
2

5
2730
23 8
15 17
7

19 9

MATRIZ DE ADJACÊNCIA

Matriz binária: ocupa pouco espaço, especialmente para grafos
grandes
Manipulação simples: recursos para manipular matrizes existem em
qualquer linguagem de programação
Fácil determinar se (vi
,vj
)  G(E)

Fácil determinar vértices adjacentes a um determinado vértice v
Quando o grafo é não orientado, a MA é simétrica (mais
econômica)
Inserção de novas arestas é fácil
Inserção de novos vértices é muito difícil

INSTITUTO DE COMPUTAÇÃO - UFF 45

REPRESENTAÇÃO FÍSICA DE
GRAFOS

Matriz de adjacência
Matriz de incidência
Lista de adjacência
Lista de incidência

INSTITUTO DE COMPUTAÇÃO - UFF 46

MATRIZ DE INCIDÊNCIA

É uma matriz B(n x m), sendo n o número de vértices, m o
número de arestas e:
 bij= -1 se o vértice i é a origem da aresta j
 bij= 1 se o vértice i é o término da aresta j
 bij = 0 se aresta (i,j)  G(E)
Para grafos não orientados, bij= 1 se a aresta j é incidente ao
vértice i.

INSTITUTO DE COMPUTAÇÃO - UFF 47
a1 a2 a3 a4 a5
1 -1 -1 0 0 0
2 1 0 -1 -1 0
3 0 1 1 0 -1
4 0 0 0 1 1

1

4

2

3

a2

a5
a1 a4

a3

arestas vértices

REPRESENTAÇÃO FÍSICA DE
GRAFOS

Matriz de adjacência
Matriz de incidência
Lista de adjacência
Listas de incidência

INSTITUTO DE COMPUTAÇÃO - UFF 48

Para cada vértice v é representada a lista de vértices u tais que
(v,u)  G(E)
Possíveis formas de armazenamento: vetores, vetores + listas
encadeadas, listas encadeadas
Melhor forma de representação: listas encadeadas
 Uso racional do espaço
 Flexibilidade
LISTA DE ADJACÊNCIA

INSTITUTO DE COMPUTAÇÃO - UFF 49
1 2 3 /

2

3

4 / /

3

4 /

1 4 /

4

2

3

G

LISTAS DE ADJACÊNCIA

Nós podem ser estendidos para representar outras informações

INSTITUTO DE COMPUTAÇÃO - UFF 50

1

4

2

3

G

2 3 ?

3

4 /

4 ?

1 ?

2 ?

3 ?

4 ? / /

?

?

?

/

/

REPRESENTAÇÃO FÍSICA DE
GRAFOS

Matriz de adjacência
Matriz de incidência
Lista de adjacência
Lista de incidência

INSTITUTO DE COMPUTAÇÃO - UFF 51

LISTAS DE INCIDÊNCIA

INSTITUTO DE COMPUTAÇÃO - UFF 52

1

4

2

3

G 1 2 1 3 2 3 2 4 3 4 /

IMPLEMENTAÇÃO

Veremos a implementação de grafos usando lista de adjacência
 São flexíveis para acomodar inserções e remoções, ao contrário das matrizes de
adjacência e incidência
 Facilitam a identificação dos vértices do grafo, ao contrário das listas de
incidência

---

