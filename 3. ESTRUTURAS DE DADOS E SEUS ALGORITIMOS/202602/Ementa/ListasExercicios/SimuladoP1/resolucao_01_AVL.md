# SimulEDA P1 — Exercício 1 (AVL)

> Toda rotação abaixo foi conferida rodando o algoritmo real (inserção/retirada com
> rebalanceamento bottom-up) num programinha em C, não só "no olho" — por isso alguns passos
> aqui **divergem** de um cálculo apressado feito só de cabeça (é fácil, numa árvore grande,
> esquecer de checar o desequilíbrio de um ancestral mais distante depois de uma inserção
> "tranquila").

## Árvore inicial

```
        20
       /  \
      10   30
     / \   / \
    5  15 25  35
```

## Regra AVL (recapitulando)

Para todo nó, **fator de balanceamento** FB = altura(subárvore esquerda) − altura(subárvore
direita) tem que estar em **{-1, 0, 1}**. Depois de inserir ou retirar, subo da posição
alterada até a raiz recalculando FB em cada ancestral; no primeiro nó onde `|FB| > 1`, aplico
a rotação (simples ou dupla, dependendo do sinal do FB do filho) e **paro de subir** — o resto
da árvore acima já não muda de altura, então não pode ter ficado desequilibrado por causa
desta inserção.

---

## Inserções: 27, 29, 26, 28, 12, 14, 40, 37, 1, 4, 11, 13, 9, 3

| # | Insere | Desce por | Desequilíbrio em | Caso | Rotação |
|---|---|---|---|---|---|
| 1 | 27 | 20→30→25→(dir) | — | — | nenhuma |
| 2 | 29 | ...→25→27→(dir) | **25** (FB=-2) | Direita-Direita | simples à esquerda em 25 |
| 3 | 26 | 20→27→25→(dir) | **30** (FB=+2) | Esquerda-Esquerda | simples à direita em 30 |
| 4 | 28 | 20→27→30→29→(esq) | **20** (FB=-2) | Direita-Direita | simples à esquerda em 20 |
| 5 | 12 | 27→20→10→15→(esq) | — | — | nenhuma |
| 6 | 14 | ...→15→12→(dir) | **15** (FB=+2) | Esquerda-Direita | dupla: esq. em 12, dir. em 15 |
| 7 | 40 | 27→30→35→(dir) | — | — | nenhuma |
| 8 | 37 | ...→35→40→(esq) | **35** (FB=-2) | Direita-Esquerda | dupla: dir. em 40, esq. em 35 |
| 9 | 1 | 27→20→10→5→(esq) | — | — | nenhuma |
| 10 | 4 | ...→5→1→(dir) | **5** (FB=+2) | Esquerda-Direita | dupla: esq. em 1, dir. em 5 |
| 11 | 11 | 27→20→10→14→12→(esq) | **20** (FB=+2) | Esquerda-Direita | dupla: esq. em 10, dir. em 20 |
| 12 | 13 | 27→14→10→12→(dir) | — | — | nenhuma |
| 13 | 9 | 27→14→10→4→5→(dir) | **27** (FB=+2, raiz!) | Esquerda-Esquerda | simples à direita em 27 |
| 14 | 3 | 14→10→4→1→(dir) | — | — | nenhuma |

### Passo 2 — inserir 29 (1ª rotação)

29 desce até virar filho direito de 27, que é filho direito de 25 → **dois "direita" seguidos**
a partir de 25: caso Direita-Direita, resolvido com uma única rotação à esquerda em 25.

```
   antes             depois (rotação simples à esquerda em 25)
     25                        27
       \                      /  \
        27          ->      25    29
          \
          29
```

### Passo 3 — inserir 26 (a rotação que o "olhômetro" costuma perder)

26 desce até virar filho direito de 25 (que agora é filho esquerdo de 27). Isso não desequilibra
25 nem 27 — mas **aumenta a altura de 27 em 1**, e é o nó **30** (avô de 27) que estoura:
FB(30) = altura(27)=2 − altura(35)=0 = **2**. Como o filho esquerdo de 30 (27) tem FB ≥ 0
(Esquerda-Esquerda), a correção é uma rotação simples à direita em 30 — e 27 sobe de posição,
virando filho direito de 20 (no lugar onde estava 30):

```
 antes (subárvore de 30)             depois (rotação simples à direita em 30)
        30                                    27
       /  \                                  /  \
      27   35                              25    30
     /  \                                    \   / \
    25   29                                  26 29  35
      \
      26
```

### Passo 4 — inserir 28

28 entra como filho esquerdo de 29. Isso deixa **20** (a raiz) com FB = altura(10)=1 −
altura(27)=3 = **-2**. O filho direito de 20 (27) tem FB = −1 (Direita-Direita) → rotação
simples à esquerda em 20. Como 20 era a raiz, **27 vira a nova raiz da árvore inteira**:

```
antes                                         depois (rotação simples à esquerda em 20)
              20                                          27
            /    \                                    /        \
          10      27                                20           30
         /  \    /  \                              /  \         /  \
        5   15  25   30                          10    25      29   35
                  \   / \                        / \     \     /
                  26 29  35                     5  15    26   28
                      \
                      28
```

### Passo 6 — inserir 14

14 entra como filho direito de 12 (que é filho esquerdo de 15). FB(15) = altura(12)=1 −
altura(vazia)=−1 = **2**, e o filho esquerdo de 15 (12) tem FB = −1 (< 0) → caso
Esquerda-Direita, resolvido com **rotação dupla**: primeiro rotaciona à esquerda em 12, depois
à direita em 15.

```
antes (subárvore de 15)      depois de girar 12       depois de girar 15 (resultado final)
      15                          15                          14
     /                           /                            / \
    12                         14                            12  15
      \                       /
      14                    12
```

### Passo 8 — inserir 37

37 entra como filho esquerdo de 40 (filho direito de 35). FB(35) = −1 − altura(40)=1 = **-2**,
e o filho direito de 35 (40) tem FB = +1 (> 0) → caso Direita-Esquerda: rotaciona à direita em
40, depois à esquerda em 35.

```
antes (subárvore de 35)      depois de girar 40       depois de girar 35 (resultado final)
   35                            35                          37
     \                             \                        /  \
      40                            37                    35    40
     /                                \
    37                                 40
```

### Passo 10 — inserir 4

Mesmo padrão do passo 6, um nível abaixo: 4 entra como filho direito de 1 (filho esquerdo de
5). Esquerda-Direita em 5 → dupla: gira 1 à esquerda, depois 5 à direita.

```
antes            depois de girar 1        depois de girar 5
  5                    5                        4
 /                    /                        / \
1                    4                        1   5
  \                 /
  4                1
```

### Passo 11 — inserir 11

11 entra como filho esquerdo de 12 (filho direito de 10, que é filho esquerdo de 20). Isso
deixa **20** com FB = altura(10)=3 − altura(25)=1 = **2**, e o filho esquerdo de 20 (10) tem
FB = −1 (Esquerda-Direita) → dupla: gira 10 à esquerda, depois 20 à direita. Repare que essa
rotação acontece **dentro** da subárvore que é filha esquerda de 27 — a raiz da árvore inteira
não muda aqui, só a raiz *daquela* subárvore (que passa a ser 14 em vez de 20):

```
antes (subárvore de 20)                    depois (14 vira raiz desta subárvore)
              20
           /      \                                  14
         10         25                            /      \
        /  \           \                        10         20
       4   14           26                      /  \       /  \
      / \  / \                                  4   12    15   25
     1   5 12  15                              / \    \          \
             \                                1   5   11          26
             11
```

### Passo 13 — inserir 9 (a raiz muda de novo)

9 entra como filho direito de 5 (bem no fundo, do lado esquerdo da árvore). Isso empurra a
altura de toda a subárvore esquerda de 14 para cima, e quem estoura é a **raiz**: FB(27) =
altura(14)=4 − altura(30)=2 = **2**. O filho esquerdo de 27 (14) tem FB = +1
(Esquerda-Esquerda) → rotação simples à direita em 27. **A raiz da árvore passa a ser 14.**

```
antes (arvore inteira)                                    depois (rotacao simples a direita em 27)
                     27
              /             \                                          14
           14                 30                                  /         \
         /    \              /   \                              10           27
       10       20         29     37                           /  \        /    \
      /  \     /  \       /      /  \                         4   12     20      30
     4   12   15   25    28    35   40                       / \  / \   /  \    /  \
    / \  / \        \                                        1  5 11 13  15  25 29  37
   1  5 11 13        26                                          \             \  /  \
        \                                                         9            26 28 (35,40 abaixo de 37)
        9
```

> A versão em texto (nível a nível) da árvore acima, pra conferir sem ambiguidade de desenho:
> `14 / 10, 27 / 4, 12, 20, 30 / 1, 5, 11, 13, 15, 25, 29, 37 / 9(de 5), 26(de 25), 28(de 29), 35(de 37), 40(de 37)`.

## Árvore final após as 14 inserções

```
                                    14
                        /                          \
                     10                                27
                  /       \                        /        \
                 4         12                     20            30
                / \        /  \                  /  \          /   \
               1   5      11   13               15   25       29    37
                \   \                                  \      /     /  \
                 3   9                                  26   28   35   40
```

**Conferindo:** o percurso em-ordem tem que sair crescente (propriedade de BST) — `1, 3, 4, 5,
9, 10, 11, 12, 13, 14, 15, 20, 25, 26, 27, 28, 29, 30, 35, 37, 40` ✔, e todo FB está em
{-1,0,1} (checado direto no programa de apoio).

---

## Retiradas: 20, 5, 9, 40, 29, 28

Na retirada de um nó com **dois filhos**, a convenção usada é substituí-lo pelo seu **sucessor
em ordem** (o menor elemento da subárvore direita) e remover o sucessor da posição original.

| # | Retira | Caso | O que acontece | Desequilíbrio | Rotação |
|---|---|---|---|---|---|
| 1 | 20 | 2 filhos (15, 25) | sucessor = 25 (não tem filho esq.); 20 vira 25, e o 26 (filho direito do 25 original) sobe no lugar | — | nenhuma |
| 2 | 5 | 1 filho (9) | 9 sobe e ocupa o lugar de 5 | — | nenhuma |
| 3 | 9 | folha | remove direto; **4** fica com FB=+2 | **4** | dupla: gira 1 à esquerda, depois 4 à direita |
| 4 | 40 | folha | remove direto | — | nenhuma |
| 5 | 29 | 1 filho (28) | 28 sobe e ocupa o lugar de 29 | — | nenhuma |
| 6 | 28 | folha | remove direto; **30** fica com FB=-2 | **30** | dupla: gira 37 à direita, depois 30 à esquerda |

### Passo 3 — retirar 9

Depois de tirar 5 (passo 2), a subárvore de 4 ficou `4(1(_,3), 9)`. Tirando a folha 9, sobra só
o lado esquerdo: FB(4) = altura(1)=1 − altura(vazia)=−1 = **2**. O filho esquerdo (1) tem
FB = −1 (Esquerda-Direita) → dupla: gira 1 à esquerda, depois 4 à direita.

```
antes (subárvore de 4, após tirar 5 e 9)     depois de girar 1        depois de girar 4
      4                                            4                        3
     /                                            /                        / \
    1                                            3                        1   4
      \                                         /
      3                                        1
```

### Passo 6 — retirar 28

Depois de tirar 29 (passo 5, 28 sobe no lugar dele), a subárvore de 30 ficou `30(28, 37(35,_))`.
Tirando a folha 28, sobra só o lado direito: FB(30) = −1 − altura(37)=1 = **-2**. O filho
direito (37) tem FB = +1 (Direita-Esquerda) → dupla: gira 37 à direita, depois 30 à esquerda.

```
antes (subárvore de 30, apos tirar 28)     depois de girar 37       depois de girar 30
   30                                           30                       35
     \                                            \                     /  \
     37                                            35                  30   37
     /                                               \
    35                                                37
```

## Árvore final após as 6 retiradas

```
                            14
                    /                \
                  10                    27
               /      \              /      \
              3        12           25        35
             / \        / \        /  \       /  \
            1   4      11  13     15   26    30   37
```

**Conferindo:** em-ordem sai `1, 3, 4, 10, 11, 12, 13, 14, 15, 25, 26, 27, 30, 35, 37` — 15
elementos (21 inseridos − 6 retirados = 15 ✔), crescente ✔, e todos os FB em {-1,0,1}.
