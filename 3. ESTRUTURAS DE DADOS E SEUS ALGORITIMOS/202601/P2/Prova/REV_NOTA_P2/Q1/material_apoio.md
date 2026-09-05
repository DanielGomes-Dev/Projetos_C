
## 2. Árvores B

(*) Figuras obtidas de T.H. Cormen, C.E. Leiserson e R.L. Rivest, Algoritmos, Campus.

### Definição de árvores B

* **Suposição:**
* Qualquer informação extra associada a uma chave está armazenada no nó onde a chave aparece


* **Uma árvore B possui as seguintes propriedades:**
* Todo nó de árvore tem as seguintes características:
1. nchaves (int)
2. nchaves armazenadas em ordem crescente ($ch_1 < ch_2 < … < ch_{nchaves}$)
3. folha (int)
4. (nchaves + 1) ponteiros para os filhos


* Cada nó interno possui (nchaves + 1) ponteiros válidos para os seus filhos. Já nas folhas, esses ponteiros são iguais a NULL



### Definição de árvores B (cont.)

→ As chaves de um nó separam os intervalos de chaves que podem ser armazenadas em cada subárvore

→ Cada folha tem a mesma altura $h$ (da raiz), onde $h = \log_t n$.

→ Existem limites inferiores e superiores sobre o número de chaves que cada nó pode possuir, expressos em termos de um inteiro $t$, $t \geq 2$, chamado de **grau mínimo** da árvore B:

* Todo nó, exceto a raiz, deve ter, pelo menos, $t – 1$ chaves (e $t$ filhos). O limite inferior da raiz é 1; e
* Todo nó pode conter, no máximo, $2t – 1$ chaves (e $2t$ filhos).

### Exemplo de árvore B mínima

* Árvore B mais simples: $t = 2 \rightarrow$ árvore 2-3-4
* Na prática $t$ é muito maior!
* Altura? $h = \log_t n$

### Estrutura e operações básicas

```c
typedef struct arvb{
  int nchaves, folha;
  int *chave;
  struct arvb **filho; // Ajuste técnico: ponteiro de ponteiro para os filhos
} TARVB;

//Inicializar uma árvore
TARVB* inicializa(void){
  return NULL;
}

//Cria um nó de árvore
TARVB* Cria(int t){
  TARVB *novo = (TARVB *) malloc(sizeof(TARVB));
  novo->nchaves = 0;
  novo->chave = (int *) malloc(sizeof(int) * (2*t-1));
  novo->folha = 1;
  novo->filho = (TARVB **) malloc(sizeof(TARVB *)*2*t);
  int i;
  for(i = 0; i < 2*t; i++)
    novo->filho[i] = NULL;
  return novo;
}

```

### Operações básicas (Impressão e Liberação)

> **Algoritmos de “uma passagem”?** Algoritmos que seguem em sentido descendente, a partir da raiz da árvore, sem ter que subir na estrutura!

```c
void imp_aux(TARVB *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      imp_aux(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf(" ");
      printf("%d\n", a->chave[i]);
    }
    imp_aux(a->filho[i],andar+1);
  }
}

//Impressão de uma árvore
void imprime(TARVB *a){
  imp_aux(a,0);
}

//Liberação de uma árvore
void libera(TARVB *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++)
        libera(a->filho[i]);
    }
    free(a->filho);
    free(a->chave);
    free(a);
  }
}

```

### Operações básicas (Busca)

```c
TARVB *Busca(TARVB* a, int ch){
  if(!a) return NULL;
  int i = 0;
  while(i < a->nchaves && ch > a->chave[i]) i++;
  if(i < a->nchaves && ch == a->chave[i]) return a;
  if(a->folha) return NULL;
  return Busca(a->filho[i], ch);
}

```

### 3. Inserção na Árvore B

* **Algoritmo preemptivo?** Não deixa o problema acontecer: corrige a árvore antes!
* **Qual é o problema?** Nó no caminho de inserção contendo $2t – 1$ chaves.
* **Ideia do algoritmo?**
* Procura-se pela posição (na folha) para a inserção.
* Inserção pode violar o limite superior.



### Resolução do Problema (Divisão)

* **Analisando a partir do nó pai:** se a inserção deve ser feita no nó $y$, e $y$ está completo:
* Dividir um nó $y$ completo ao redor da chave $t$, em dois nós com $t – 1$ chaves.
* A chave $t$ (chave mediana) desloca-se para o pai do nó $y$.
* O pai não estará completo porque estamos usando um algoritmo preemptivo (corrige a árvore antes do problema ocorrer).



### Algoritmo de “uma passagem”: inserção

* Não se espera descobrir a necessidade de divisão.
* À medida que se desce na árvore à procura pela folha a ser inserida a chave, **divide-se cada nó completo encontrado** (incluindo-se a raiz e a folha).
* Assim, sempre que for necessário dividir um nó completo, temos a certeza de que o pai não está completo.

### Operação de Divisão

> **Nota:** Esta operação pode causar o incremento da altura da árvore!

**Entradas:**

1. Nó interno $x$ não completo;
2. Índice $i$;
3. Nó completo $y$, tal que é o $i$-ésimo filho de $x$;
4. $t$.

**Ideia:**

* Divisão de $y$ em 2;
* Ajustar $x$ para que ele tenha um filho adicional;
* **Para a raiz completa:** Transforma a raiz em um filho de um nó raiz vazio para usar o algoritmo de divisão; SOMENTE dessa maneira a árvore cresce uma unidade em altura.

### Implementação da Inserção e Divisão

```c
TARVB *Insere(TARVB *T, int k, int t){
  if(Busca(T,k)) return T;
  if(!T){
    T=Cria(t);
    T->chave[0] = k;
    T->nchaves=1;
    return T;
  }
  if(T->nchaves == (2*t)-1){
    TARVB *S = Cria(t); // Ajustado de TAB para TARVB conforme struct
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = Divisao(S,1,T,t);
    S = Insere_Nao_Completo(S,k,t);
    return S;
  }
  T = Insere_Nao_Completo(T,k,t);
  return T;
}

TARVB *Divisao(TARVB *x, int ind, TARVB* y, int t){
  TARVB *z = Cria(t);
  z->nchaves = t-1;
  z->folha = y->folha;
  int j;
  for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t];
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t-1;
  for(j=x->nchaves; j>=ind; j--)
    x->filho[j+1]=x->filho[j];
  x->filho[ind] = z;
  for(j=x->nchaves; j>=ind; j--)
    x->chave[j] = x->chave[j-1];
  x->chave[ind-1] = y->chave[t-1];
  x->nchaves++;
  return x;
}

TARVB *Insere_Nao_Completo(TARVB *x, int k, int t){
  int i = x->nchaves-1;
  if(x->folha){
    while((i>=0) && (k<x->chave[i])){
      x->chave[i+1] = x->chave[i];
      i--;
    }
    x->chave[i+1] = k;
    x->nchaves++;
    return x;
  }
  while((i>=0) && (k<x->chave[i])) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){
    x = Divisao(x, (i+1), x->filho[i], t);
    if(k>x->chave[i]) i++;
  }
  x->filho[i] = Insere_Nao_Completo(x->filho[i], k, t);
  return x;
}

```

---


Conforme solicitado, procederei com a transcrição fiel dos tópicos apresentados, removendo as redundâncias das animações e consolidando os casos do algoritmo.

---

## Operações básicas: retirada

* Mais complicada que a inserção: chave pode ser eliminada de qualquer nó (não só folha)
* Retirada em um nó interno: filhos podem ser reorganizados porque não se pode violar o limite inferior de chaves em uma árvore B
* Deve-se garantir que nenhum nó terá menos que t – 1 chaves, exceto a raiz
* Algoritmo de retirada é chamado recursivamente em um nó x, com no mínimo t chaves
* A condição supracitada exige, pelo menos, 1 chave a mais que o mínimo

### Algoritmo de retirada

* **CASO 1:** se a chave k está em x, e x é folha, elimine k de x
* **CASO 2:** se a chave k está em x:
* **CASO 2A:** se o filho y que precede k no nó x tem, ao menos, t chaves, então encontre o predecessor k’ de k na árvore com raiz em y. Elimine recursivamente k’ e substitua k por k’ em x
* **CASO 2B:** se o filho z que sucede k no nó x tem, ao menos, t chaves, então encontre o sucessor k’ de k na árvore com raiz em z. Elimine recursivamente k’ e substitua k por k’ em x
* **CASO 2C:** se tanto y e z têm apenas t – 1 chaves, faça a intercalação de k com todas as chaves de z em y, de modo que x perca a chave k e o ponteiro z. Assim, y terá 2t – 1 chaves. A seguir retire recursivamente k de y.


* **CASO 3:** se a chave k não está em x, descubra qual é o filho f onde k pode estar. Se f tiver t – 1 chaves, faça ou o CASO 3A, ou o CASO 3B.
* Essa ação é necessária para garantir que desceremos até um nó contendo, ao menos, t chaves. Em seguida, execute a recursão sobre o filho apropriado de x
* **CASO 3A:** se a subárvore onde k deve estar tiver somente t – 1 chaves, mas possuir um irmão com t chaves, forneça ao pai uma chave do irmão, e retire o ponteiro associado a chave emprestada, caso este ponteiro exista
* **CASO 3B:** se o filho f (que pode conter k) de x tem t - 1 chaves e todos os seus irmãos imediatos têm t – 1 chaves também, faça a intercalação de f com um de seus irmãos, o que envolve mover uma chave do pai para o novo nó intercalado



> **Nota:** CASOS 2C e 3B são as únicas operações que podem causar o decremento da altura da árvore

### Considerações finais

* Maioria das chaves estão armazenadas nas folhas
* Algoritmo continua ser de uma passagem
* Mesmo nos CASOS 2A e 2B, onde se substitui chaves (ou pelo predecessor, ou pelo sucessor, respectivamente)

---


