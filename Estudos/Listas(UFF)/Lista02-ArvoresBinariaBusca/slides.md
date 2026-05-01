/*

Dada a seguinte representação de uma árvore binária de busca (ABB):

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TABB;

Escreva as seguintes funções:

(Q5) Reescreva as operações básicas da ABB para poder armazenar as figuras geométricas
quadrado, triângulo, retângulo e trapézio. A área da figura será usada para definir os elementos
pertencentes a sub-árvore esquerda e a sub-árvore direita. A impressão será em ordem simétrica e,
além da área, devem ser informadas as dimensões da figura.

*/



---

resolva o exercicio acima com base nas informações abaixo

---

content = """# ÁRVORES BINÁRIAS DE BUSCA

Material baseado nos slides
gentilmente cedidos pela
Professora Vanessa
Braganholo

---

## BUSCA

Diversas aplicações precisam buscar um determinado valor em um
conjunto de dados
Essa busca deve ser feita da forma mais eficiente possível
Árvores binárias possibilitam buscas com eficiência

Exemplo: buscar dados de uma pessoa que possui um determinado
CPF
Dados das pessoas são armazenados numa árvore binária de busca
CPF funciona como “chave”, pois é único para cada pessoa (não
existem duas pessoas com o mesmo CPF)

INSTITUTO DE COMPUTAÇÃO - UFF 2

---

## ÁRVORES BINÁRIAS DE BUSCA

Apresentam uma relação de ordem entre os nós
Ordem é definida pela chave

```text
          raiz 500
          /      \\
        300      800
       /   \\    /   \\
     150   400 600   900
```

`esq | chave | dir`
Demais infos do nó

INSTITUTO DE COMPUTAÇÃO - UFF 3

---

## DEFINIÇÃO

Uma árvore binária é uma
árvore binária de busca se:
→ Chaves da subárvore esquerda de
raiz são menores do que chave de raiz;

→ Chaves da subárvore da direita de
raiz são maiores do que a chave de raiz;
e

→ Subárvores da esquerda e da direita
de raiz são árvores binárias de busca.

```text
          raiz 500
          /      \\
        300      800
       /   \\    /   \\
     150   400 600   900
```

INSTITUTO DE COMPUTAÇÃO - UFF 4

---

## VARIAÇÕES DE ESTRUTURA

Para um mesmo conjunto de
chaves, existem várias árvores
binárias de busca possíveis

Exemplos para o conjunto de
chaves:
{1, 2, 3, 4, 5, 6, 7}

```text
      Exemplo A:           Exemplo B:
          3                    2
        /   \\                /   \\
       1     7              1     7
        \\   /                    /
         2 5                    3
          / \\                    \\
         4   6                    4
                                   \\
                                    5
                                     \\
                                      6
```

INSTITUTO DE COMPUTAÇÃO - UFF 5

---

## OPERAÇÕES

→ Iguais as de árvores binárias, exceto:
– Buscar nó com determinada info;
– Inserir novo nó; e
– Remover nó.

```text
          raiz 500
          /      \\
        300      800
       /   \\    /   \\
     150   400 600   900
```

Operações devem
respeitar a ordem!

INSTITUTO DE COMPUTAÇÃO - UFF 6

---

## BUSCA DE UMA CHAVE

```c
/* representação dos nós*/
typedef struct arvbin{
int info;
struct arvbin *esq, *dir;
}TAB;

TAB *busca(TAB *a, int info){
if((!a) || (a->info == info)) return a;
TAB *resp = busca(a->esq, info);
if(resp) return resp;
return busca(a->dir, info);
}

TAB *busca_ABB(TAB *a, int info){
if((!a) || (a->info == info)) return a;
if(a->info > info)
return busca_ABB(a->esq, info);
return busca_ABB(a->dir, info);
}
```

---

## COMPLEXIDADE

→ Assumindo que a árvore binária de busca seja o mais balanceada possível:

→ Em cada chamada da função busca, é efetuado um número constante de operações.

→ A complexidade da busca é igual ao número de chamadas da função.

→ No pior caso (quando chave buscada está na folha), a complexidade é a altura da árvore.

→ Complexidade de pior caso mínima ocorre para árvore completa, onde altura é log n (n é o número de
nós da árvore).

INSTITUTO DE COMPUTAÇÃO - UFF 8

---

## INSERÇÃO DE UMA CHAVE

```c
/* representação dos nós*/
typedef struct arvbin{
int info;
struct arvbin *esq, *dir;
}TAB;

TAB* cria(int r, TAB *sae, TAB *sad){
TAB *novo = (TAB *)malloc(sizeof(TAB));
novo->info = r;
novo->esq = sae;
novo->dir = sad;
return novo;
}

TAB *insere_ABB(TAB *a, int info){
if(!a) return cria(info, NULL, NULL);
if(info < a->info)
a->esq = insere_ABB(a->esq, info);
else if(info > a->info)
a->dir = insere_ABB(a->dir, info);
return a;
}
```

---

## EXERCÍCIOS DE INSERÇÃO

1. Inserir em uma ABB inicialmente vazia, os seguintes valores:
25, 22, 40, 30, 45, 27, 20, 21, 48
2. Inserir em uma ABB inicialmente vazia, os seguintes valores:
40, 25, 20, 30, 45, 27, 22, 21, 48

INSTITUTO DE COMPUTAÇÃO - UFF 10

---

## RESULTADO DOS EXERCÍCIOS

### Árvore 1:
```text
           25
         /    \\
       22      40
      /       /  \\
    20      30    45
      \\    /       \\
       21 27        48
```

### Árvore 2:
```text
           40
         /    \\
       25      45
      /  \\       \\
    20    30      48
      \\  /
      21 27
        \\
         22
```

INSTITUTO DE COMPUTAÇÃO - UFF 12

---

## RETIRADA DE UMA INFORMAÇÃO

→ Mais complicada que a inserção

→ TRÊS situações possíveis:
(1) retirar folha (mais simples): retirar o elemento e atualizar o pai dessa folha

```text
      Antes (-900):              Depois:
          500                      500
        /     \\                  /     \\
      300     800              300     800
     /   \\   /   \\            /   \\   /
   150   400 600  900        150   400 600
```

→ TRÊS situações possíveis:
(2) retirar um nó com um filho:

```text
      Antes (-800):              Depois:
          500                      500
        /     \\                  /     \\
      300     800              300     600
     /   \\   /                /   \\
   150   400 600              150   400
```

→ TRÊS situações possíveis:
(3) retirar um nó com dois filhos:
(a) encontrar a informação que precede o elemento a ser retirado (maior elemento da esquerda);
(b) trocar a informação do nó a ser retirado com a informação do nó encontrado no passo (a); e
(c) retirar o nó encontrado no passo (a).

```text
      Antes (-500):              Depois:
          500                      400
        /     \\                  /     \\
      300     600              300     600
     /   \\                    /
   150   400                150
```

---

## CÓDIGO DE RETIRADA

```c
TAB *retira_ABB(TAB *a, int info){
if(!a) return a;
if(info < a->info)
a->esq = retira_ABB(a->esq, info);
else if(info > a->info)
a->dir = retira_ABB(a->dir, info);
else{ //info encontrado
if((!a->esq) && (!a->dir)){ //CASO (1)
free(a);
a = NULL;
}
else if((!a->esq) || (!a->dir)){ //CASO (2)
TAB *temp = a;
if(!a->esq) a = a->dir;
else a = a->esq;
free(temp);
}
else{ //CASO (3)
TAB *filho = a->esq;
while(filho->dir) filho = filho->dir;
a->info = filho->info;
filho->info = info;
a->esq = retira_ABB(a->esq, info);
}
}
return a;
}
```

---

## EXERCÍCIO FINAL

Dada a árvore a seguir,
executar o procedimento de
exclusão cumulativo dos
seguintes nós:
100 – 150 – 80 – 270 – 400 –
200

```text
                    200
             /               \\
          100                 300
       /       \\           /       \\
     80        150       250       400
    /         /         /   \\     /   \\
   70       120       220   270 350   500
  /  \\     /   \\              \\
 65  79   110  130            260
```

INSTITUTO DE COMPUTAÇÃO - UFF 17

---

## CONSIDERAÇÕES FINAIS

Para grandes volumes de dados, árvores binárias de busca não são
as alternativas mais eficientes. Ao longo da disciplina veremos
outras alternativas para buscas eficientes em grandes volumes de
dados (Tabelas Hash, Árvores B, Árvores B+).
"""

with open("arvores_binarias_busca.md", "w", encoding="utf-8") as f:
    f.write(content)


O conteúdo foi reorganizado em um arquivo Markdown (.md) estruturado, mantendo a transcrição original linha por linha e recriando as árvores binárias de forma visual utilizando diagramas em texto (ASCII art) para facilitar a compreensão sem o uso de imagens externas.

Your PDF file is ready
[file-tag: code-generated-file-0-1777419937506013097]