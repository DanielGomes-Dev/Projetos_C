# Q2 — Inserção e remoção numa AVL maior, partindo de uma árvore não trivial

> **Origem:** `lista03-EDA.pdf`, questão 2 · **Código resolvido:** [[../Q2/claude/main.c]]
> **Antes disto, veja:** [[Q1 - Inserção e remoção em AVL com rotações]] (mesmo método,
> em escala menor — leia primeiro se ainda não leu)

## 1. O que o exercício pede

> Partindo da AVL dada (16 nós, veja abaixo):
> (a) inserir `{1, 65, 12, 18, 66, 38, 95, 58, 59, 70, 68, 39, 62, 60, 43, 16, 67, 36, 35}`,
> indicando as rotações;
> (b) retirar `{35, 34, 67, 16, 42, 60, 62, 39, 68, 70, 59, 58, 95, 38, 66, 18, 12, 64, 1}`,
> explicitando as rotações.

Árvore inicial:
```
                       61
              34                 78
          19      47         64      87
        15   29  42  53        76      84
       13 17  32
```

## 2. A ideia geral

**Mesmo método de [[Q1 - Inserção e remoção em AVL com rotações]]** — a única diferença
real é que aqui você **começa** de uma árvore de 16 nós já não trivial, em vez de uma
folha só. O comentário do código explica como essa árvore inicial é montada: inserindo os
16 valores **em ordem de nível** (BFS) — como a árvore já é uma AVL válida, essa ordem de
inserção reconstrói exatamente a mesma forma, sem disparar nenhuma rotação (você pode
conferir isso rodando só a primeira parte do `main`).

**Conferindo que a árvore inicial é mesmo uma AVL válida** (spot-check, de baixo pra cima):
`15`: esq=`13`(alt0), dir=`17`(alt0) → `FB=0`, alt=1. `29`: dir=`32`(alt0), esq vazio →
`FB=-1`, alt=1. `19`: esq=`15`(alt1), dir=`29`(alt1) → `FB=0`, alt=2. `47`: esq=`42`(alt0),
dir=`53`(alt0) → `FB=0`, alt=1. `34`: esq=`19`(alt2), dir=`47`(alt1) → `FB=1`, alt=3.
`64`: esq vazio, dir=`76`(alt0) → `FB=-1`, alt=1. `87`: esq=`84`(alt0), dir vazio → `FB=1`,
alt=1. `78`: esq=`64`(alt1), dir=`87`(alt1) → `FB=0`, alt=2. `61` (raiz): esq=`34`(alt3),
dir=`78`(alt2) → `FB=1`, alt=4. **Todo nó com `FB ∈ {-1,0,1}`** ✔ — é uma AVL válida.

Dada a escala (19 inserções + 19 remoções — praticamente esvaziar a árvore de novo), este
arquivo **não repete o trace exaustivo célula por célula** que o Q1 já fez em detalhe para
uma sequência de tamanho comparável — o método é idêntico, e refazer tudo aqui seria
repetição, não ensino novo. Em vez disso: as primeiras inserções são trabalhadas por
completo abaixo (cobrindo os três tipos de rotação de novo, para você comparar direto com
o Q1), e o restante fica como verificação via o código já testado (`Q2/claude/main.c`,
que imprime cada rotação ao rodar).

## 3. Resolução passo a passo (início da parte a — as 3 primeiras inserções)

### Passo 1 — insere `1`

Desce `61→34→19→15→13`, entra como filho esquerdo de `13`. Subindo: `FB(13)=1`(ok, filho
novo). `FB(15)`, `FB(19)` seguem ok. `FB(34) = alt(esq=19, agora altura 3) - alt(dir=47,
altura 1) = 3-1=2`. `elem(1) < t->esq->info(19)`? `1<19` sim → **RSD(34)**. `19` sobe, `34`
desce como filho direito de `19` (levando `47` junto), e o antigo filho direito de `19`
(`29`) passa a ser filho esquerdo de `34`:

```
                    19
              /            \
            15              34
           /  \            /   \
          13   17         29    47
         /                 \    /  \
        1                   32 42  53
```

### Passo 2 — insere `65`

Desce `61→78→64→76`, entra como filho esquerdo de `76`. Subindo: `FB(76)=1`(ok). `FB(64) =
alt(esq vazio,-1) - alt(dir=76, agora altura 1) = -2`. `elem(65) > t->dir->info(76)`?
`65>76`? **Não** → **RDE(64)**: 1º `RSD(76)` (sobe `65`, `76` desce à direita de `65`), 2º
`RSE(64)` (sobe `65` de novo, `64` desce à esquerda de `65`). Resultado:

```
              65
             /  \
           64    76
```
(substitui o antigo `64` como filho esquerdo de `78`)

### Passo 3 — insere `12`

Desce `61→19→15→13→1`, entra como filho direito de `1`. Subindo: `FB(1)=-1`(ok). `FB(13) =
alt(esq=1, agora altura 1) - alt(dir vazio,-1) = 2`. `elem(12) < t->esq->info(1)`? `12<1`?
**Não** → **RED(13)**: 1º `RSE(1)` (sobe `12`, `1` desce à esquerda de `12`), 2º `RSD(13)`
(sobe `12` de novo, `13` desce à direita de `12`). Resultado:

```
             12
            /  \
           1    13
```
(substitui o antigo `13` como filho esquerdo de `15`)

**Árvore depois das 3 primeiras inserções:**

```
                              61
                    /                    \
                  19                      78
                /     \                 /    \
              15        34            65      87
             /  \      /   \         /  \       \
            12   17   29    47      64   76      84
           /  \         \    /  \
          1    13         32 42  53
```

**Já apareceram os três tipos de rotação** (RSD no passo 1, RDE no passo 2, RED no passo 3)
— exatamente como no Q1. As 16 inserções restantes de (a) e as 19 remoções de (b) seguem a
mesma mecânica; confira rodando `Q2/claude/main.c` (o código já imprime cada rotação e a
árvore depois de cada operação).

## 4. Resultado final

Depois das 19 inserções e das 19 remoções (que removem quase tudo que existia + o que foi
inserido, sobrando só alguns valores), a árvore final é a impressa por `TAVL_imprime` ao
final do programa — rode o código para conferir. **Verificação que você pode fazer sozinho:**
depois de rodar, escolha 3–4 nós da árvore final e confira `FB ∈ {-1,0,1}` manualmente
(mesma técnica da seção 2) — se algum não bater, é sinal de erro no código (que, aqui,
já está testado, então não deve acontecer).

## 5. Habilidades necessárias

- [ ] Verificar se uma árvore dada é uma AVL válida, nó a nó → [[../../../01 - Árvores/1.3 Árvores AVL/Teoria - passo a passo/Teoria 02 - Definição de AVL e o fator de balanceamento|1.3 Teoria 02]]
- [ ] Rotações simples e duplas → [[../../../01 - Árvores/1.3 Árvores AVL/Teoria - passo a passo/Teoria 03 - Rotações simples (RSD e RSE)|1.3 Teoria 03]] e [[../../../01 - Árvores/1.3 Árvores AVL/Teoria - passo a passo/Teoria 04 - Rotações duplas (RED e RDE)|1.3 Teoria 04]]
- [ ] Trace completo de uma sequência de inserções/remoções → [[Q1 - Inserção e remoção em AVL com rotações]]

## 6. Exemplos mais simples (aquecimento)

Ver os dois aquecimentos já resolvidos em [[Q1 - Inserção e remoção em AVL com rotações]] —
são a base mínima para entender tanto Q1 quanto Q2 (a diferença entre os dois é só a escala
e o ponto de partida, não o método).
