# Teoria 02 — Definição de AVL e o fator de balanceamento (FB)

> **Onde isto entra:** dá nome e número ao problema descrito na Teoria 01 — como medir "o
> quanto" uma árvore está desbalanceada, e onde traçar o limite.
> **Antes:** [[Teoria 01 - O problema que a AVL resolve]].
> **Fonte:** `lista03-EDA/07_AVL_2026_08_25.pdf`, págs. 8–13.

## 1. A ideia em uma frase

Uma AVL é uma BST onde, em **todo** nó, as duas subárvores (esquerda e direita) nunca têm
alturas com diferença maior que 1.

## 2. A definição — lida devagar

> Adelson-Velskii e Landis (1962): uma árvore binária de busca é uma AVL quando, para
> qualquer um de seus nós, **o módulo da diferença** entre as **alturas** de suas
> subárvores esquerda e direita é, no máximo, **1**.

> 📖 **Lendo devagar:**
> 1. "para **qualquer** um de seus nós" — não é só a raiz; **todo** nó da árvore precisa
>    satisfazer a condição, inclusive nós no meio ou perto das folhas.
> 2. "módulo da diferença" — não importa qual lado é mais alto, só o **tamanho** da
>    diferença. Diferença de `+1` (esquerda um pouco mais alta) é tão aceitável quanto `-1`.
> 3. "no máximo 1" — diferença `0` ou `1` (em módulo) está OK; diferença `2` ou mais **não**
>    é uma AVL válida.

## 3. O fator de balanceamento (FB) — a fórmula que mede isso

```
FB(no) = altura(no->esq) - altura(no->dir)
```

> 📖 **Lendo devagar:** é a mesma subtração de sempre — altura da subárvore esquerda menos
> altura da subárvore direita. **Sem módulo aqui** (o módulo era só na definição em
> português; o FB guarda o sinal, porque o sinal diz **qual lado** está mais pesado — isso
> importa para escolher a rotação certa, Teorias 03–04).

**Regra derivada:** para a árvore inteira ser AVL, **todo** nó precisa ter `FB ∈ {-1, 0, 1}`.

## 4. Conferindo com as duas árvores do slide

```
           130                              120
         /     \                          /     \
      100        150                   100        130
     /  \          \                   /  \          \
    80   120       200                80   110       200
        /                                             /
      110                                           150
```
(esquerda: AVL) — (direita: não é AVL)

> **Calculando FB de cada nó (altura de folha = 0, altura(vazia) = -1), de baixo pra cima:**
>
> Árvore da esquerda: `80`, `110`, `200` são folhas → FB=0 cada. `120`(esq=`110` altura 0,
> dir=vazia altura -1 → altura(`120`)=1+max(0,-1)=1, FB=0-(-1)=**1**). `100`(esq=`80` altura
> 0, dir=`120` altura 1 → altura(`100`)=1+max(0,1)=2, FB=0-1=**-1**). `150`(esq=vazia altura
> -1, dir=`200` altura 0 → altura(`150`)=1+max(-1,0)=1, FB=-1-0=**-1**). `130`(raiz: esq=`100`
> altura 2, dir=`150` altura 1 → FB=2-1=**1**). Todos os FB estão em `{-1,0,1}` → **é AVL**. ✔
>
> Árvore da direita: `80`, `110`, `150` são folhas → FB=0 cada. `100`(esq=`80` alt.0,
> dir=`110` alt.0 → altura(`100`)=1, FB=0). `200`(esq=`150` altura 0, dir=vazia altura -1 →
> altura(`200`)=1+max(0,-1)=1, FB=0-(-1)=**1**). `130`(esq=vazia altura -1, dir=`200` altura
> 1 → altura(`130`)=1+max(-1,1)=2, **FB=-1-1=-2**). Já aqui, no nó `130` (não na raiz), o
> módulo passou de 1 — **não é AVL**, mesmo a raiz `120` tendo FB=1-2=**-1** (dentro do
> limite). ✔ Isso mostra que **um único nó violando** já invalida a árvore inteira, mesmo
> que a raiz "pareça" equilibrada.

## 5. Letra miúda

**"No máximo 1" não é "no máximo 1 por acidente que se resolve sozinho".** Uma árvore com
FB=2 em algum nó **não vira** AVL automaticamente com mais inserções — ela **permanece**
inválida até que uma rotação (Teorias 03–04) seja aplicada especificamente naquele nó.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| calcular `altura(esq) - altura(dir)` em cada nó | meço, numericamente, "quanto" aquele nó específico está pesado para um lado |
| verificar `FB ∈ {-1,0,1}` em **todo** nó | confirmo que o desbalanceamento de qualquer parte da árvore está contido — não é preciso a árvore inteira estar "perfeita", só que nenhum ponto isolado passe do limite |
| olhar o **sinal** do FB (não só o módulo) | descubro **qual lado** está pesado — informação necessária para escolher entre rotação simples à direita ou à esquerda (Teoria 03) |

## 7. Exercícios de fixação

1. Um nó tem subárvore esquerda de altura 3 e subárvore direita de altura 1. Qual o FB
   desse nó? A árvore (nesse nó) ainda pode ser AVL?
2. Um nó é folha. Qual o FB dele? Por quê?
3. Um nó tem subárvore esquerda vazia e subárvore direita com um único nó-folha. Qual o FB?

### Gabarito

1. `FB = 3 - 1 = 2`. **Não** pode ser AVL — módulo 2, viola "no máximo 1".
2. `FB = altura(vazia) - altura(vazia) = -1 - (-1) = 0`. Toda folha tem FB=0 — as duas
   subárvores (ambas vazias) têm a mesma altura.
3. `altura(esq)=-1` (vazia), `altura(dir)=0` (um nó, folha). `FB = -1 - 0 = -1` — dentro do
   limite, ainda é válido para AVL.

## Resumo

- AVL = BST + "toda subárvore tem `|FB| ≤ 1`" em todo nó.
- `FB(nó) = altura(esq) - altura(dir)` — com sinal, ao contrário da definição em português
  que usa módulo.
- `FB` fora de `{-1,0,1}` não se autocorrige — exige rotação (Teorias 03–04).

**Próximo:** [[Teoria 03 - Rotações simples (RSD e RSE)]].
