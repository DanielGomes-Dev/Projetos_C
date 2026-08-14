/*

(b) Dada a seguinte representação de uma árvore binária:

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TAB;

Escreva as seguintes funções:

(Q9) ache a quantidade de nós folha: int nf(TAB *a);

*/



---

resolva o exercicio acima com base nas informações abaixo

---

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

Implementações
typedef struct arvbin{
int info;
struct arvbin *esq, *dir;
}TAB;
void imp_pos(TAB *a){
if(a){
imp_pos(a→esq);
imp_pos(a→dir);
printf(“%d “, a→info);
}
}
void imp_sim(TAB *a){
if(a){
imp_sim(a→esq);
printf(“%d “, a→info);
imp_sim(a→dir);
}
}

void imp_pre(TAB *a){
if(a){
printf(“%d “, a→info);
imp_pre(a→esq);
imp_pre(a→dir);
}
}
void imp_pre_p(TAB *a){
if(!a) return;
TPILHA *p = inicializa_p();
push(p,a);
while(!vazia_p(p)){
TAB *aux = pop(p);
printf(“%d “, aux→info);
if(aux→dir) push(p,aux→dir);
if(aux→esq) push(p,aux->esq);
}
libera_p(p);
}

Implementações
typedef struct arvbin{
int info;
struct arvbin *esq, *dir;
}TAB;
void imp_larg_f(TAB *a){
if(!a) return;
TFILA *f = inicializa_f();
insere_f(f,a);
while(!vazia_f(f)){
TAB *aux = retira_f(f);
printf(“%d “, aux→info);
if(aux→esq) insere_f(f,aux->esq);
if(aux→dir) insere_f(f,aux->dir);
}
libera_f(f);
}