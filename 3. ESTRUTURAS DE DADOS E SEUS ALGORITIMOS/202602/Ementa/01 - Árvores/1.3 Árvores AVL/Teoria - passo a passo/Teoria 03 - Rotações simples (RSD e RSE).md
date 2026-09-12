# Teoria 03 — Rotações simples: RSD (≡ LL) e RSE (≡ RR)

> **Onde isto entra:** é o "conserto" para quando um nó viola `|FB| ≤ 1` (Teoria 02) — a
> operação que devolve a árvore ao formato AVL sem estragar a ordem das chaves.
> **Antes:** [[Teoria 02 - Definição de AVL e o fator de balanceamento]].
> **Fonte:** `lista03-EDA/07_AVL_2026_08_25.pdf`, págs. 19–27.

## 1. A ideia em uma frase

Uma rotação **reorganiza os ponteiros** de uma subárvore desbalanceada, promovendo um filho
a "novo topo" — sem mover nenhum valor de lugar (a ordem das chaves continua exatamente a
mesma, só a **forma** da árvore muda).

## 2. Nomenclatura do slide

> Considere: `P` a raiz da subárvore desbalanceada; `D` a sua subárvore direita (SAD); `E`
> a sua subárvore esquerda (SAE).

Quando **`P` está pesado à esquerda** (o problema mora do lado esquerdo), a correção "gira"
a árvore para a **direita** — daí o nome Rotação Simples **Direita** (RSD). Quando pesado à
direita, gira para a esquerda (RSE). É comum ver RSD chamada de "LL" (Left-Left) e RSE de
"RR" (Right-Right) — o nome descreve **onde** o desbalanceamento se acumulou.

## 3. RSD — quando aplicar

> **RSD(P):** `FB(P) = 2` **e** `FB(E) ≥ 0`.

Ou seja: `P` está pesado à esquerda (FB=2), **e** o desbalanceamento dentro de `E` também
está do lado esquerdo (ou neutro) — o problema é "reto", por isso resolve com uma única
rotação.

### Conferindo com uma árvore concreta

Antes de qualquer rotação:
```
              120
           /       \
         110         150
        /               \
      100                (subárvore com 130, 200)
     /
    80
```
(estrutura exata do slide, pág. 21: `120`→esq `110`, dir `150`; `110`→esq `100`; `100`→esq
`80`; `150`→esq `130`, dir `200`)

> **Calculando FB (altura de folha=0, vazia=-1):** `80`(FB=0). `100`(esq=`80` alt.0,
> dir=vazia → alt(`100`)=1, **FB(`100`)=0-(-1)=1**). `110`(esq=`100` alt.1, dir=vazia →
> alt(`110`)=2, **FB(`110`)=1-(-1)=2**) — aqui está o problema: `P=110`, `FB(P)=2`.
> `E=100`, `FB(E)=1 ≥ 0` → **condição de RSD satisfeita**.

**Aplicando RSD em `P=110`:** o filho esquerdo (`E=100`) sobe para o lugar de `P`; `P` desce
e vira filho **direito** de `E`; e o que era filho **direito** de `E` (aqui, vazio) passa a
ser filho **esquerdo** de `P`.

```
              120                              120
           /       \                        /       \
         110         150      RSD(110)    100         150
        /               \      ------>   /   \           \
      100                (...)          80    110       (...)
     /
    80
```

> **Conferindo:** `100`(esq=`80` alt.0, dir=`110` alt.0 → alt=1, **FB=0**). `110` agora é
> folha, **FB=0**. Ambos dentro de `{-1,0,1}` — a rotação **consertou** o nó problemático.
> E a ordem continua válida: `80 < 100 < 110`, exatamente como antes.

## 4. O código de RSD — lido devagar

```c
TAVL *RSD(TAVL *a) {
  TAVL *novo = a->esq;              // novo = E, o filho esquerdo de a (=P)
  a->esq = novo->dir;               // P assume o que sobrava do lado direito de E
  novo->dir = a;                    // P desce, vira filho direito de E
  a->alt = 1 + maximo(alt(a->esq), alt(a->dir));      // recalcula altura de P (mudou)
  novo->alt = 1 + maximo(alt(novo->esq), alt(novo->dir)); // recalcula altura de E (mudou)
  return novo;                      // E é o novo topo desta subárvore
}
```

> 📖 **Lendo devagar:** as duas primeiras linhas fazem a "troca de posições" (`novo` sobe,
> `a` desce, e o "resto" de `novo` que não coube migra para `a`) — só depois disso as
> alturas são recalculadas, **na ordem certa**: primeiro `a` (que agora está mais embaixo,
> sua altura só depende de subárvores que já estavam corretas), depois `novo` (que depende
> da altura de `a`, já recém-calculada).

## 5. RSE — o espelho de RSD

> **RSE(P):** `FB(P) = -2` **e** `FB(D) ≤ 0`.

Mesma lógica, espelhada: `P` pesado à **direita**, e o filho `D` também pesado à direita ou
neutro. O código (`RSE`, pág. 27) é RSD com `esq`↔`dir` trocados:

```c
TAVL *RSE(TAVL *a) {
  TAVL *novo = a->dir;
  a->dir = novo->esq;
  novo->esq = a;
  a->alt = 1 + maximo(alt(a->esq), alt(a->dir));
  novo->alt = 1 + maximo(alt(novo->esq), alt(novo->dir));
  return novo;
}
```

### Conferindo RSE com o exemplo do slide (pág. 24)

```
              120                              120
           /       \                        /       \
         100         130        RSE(130)  100         150
        /  \            \        ------>  /  \       /    \
       80   110          150             80  110    130    200
                            \
                            200
```
`P=130` (FB: esq vazia alt -1, dir=`150`→`200` altura 1, `FB(130)=-1-1=-2`); `D=150`
(esq vazia, dir=`200` folha → `FB(150)=-1-0=-1 ≤ 0`) → condição de RSE satisfeita. Depois da
rotação, `150` sobe, `130` desce e vira filho **esquerdo** de `150`; o que sobrava à
esquerda de `150` (vazio) volta como filho direito de `130`.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| checar `FB(P)=±2` | identifico **qual** nó especificamente violou a regra — a rotação é local, não mexe na árvore inteira |
| checar o sinal de `FB(E)` (ou `FB(D)`) | confirmo que o desbalanceamento é "reto" (mesmo lado dos dois níveis) — é isso que decide entre rotação simples (aqui) ou dupla (Teoria 04) |
| reatribuir 3 ponteiros (`novo`, `a->esq`/`dir`, `novo->esq`/`dir`) | reorganizo a estrutura preservando a ordem em-ordem da árvore — nenhum valor muda de "posição relativa", só a forma física muda |
| recalcular `alt` de `a` antes de `novo` | respeito a dependência: a altura de `novo` depende da altura (já correta) de `a` |

## 7. Exercícios de fixação

1. Um nó `P` tem `FB(P) = 2` e seu filho esquerdo `E` tem `FB(E) = 1`. Qual rotação
   aplicar?
2. Depois de uma RSD bem-sucedida, o `FB` do nó que **desceu** (o antigo `P`) pode ainda
   ser diferente de 0? Em que situação?
3. Por que RSD "sobe" o filho esquerdo (`E`), e não o direito?

### Gabarito

1. RSD — `FB(P)=2` (pesado à esquerda) e `FB(E)=1 ≥ 0` (mesmo lado) satisfazem a condição.
2. Sim — se `E` tinha um filho direito não-vazio antes da rotação, esse filho vira filho
   esquerdo do `P` que desceu, e `P` pode ficar com `FB` diferente de 0 (embora ainda dentro
   de `{-1,0,1}`, já que a rotação garante isso quando a condição é satisfeita).
3. Porque o problema está **à esquerda** (`FB(P)=2` significa "esquerda mais alta") — subir
   a raiz da subárvore esquerda é o que reduz a profundidade daquele lado; subir o filho
   direito não teria efeito sobre o desbalanceamento que está à esquerda.

## Resumo

- Rotação reorganiza ponteiros, preservando a ordem das chaves — nunca move valores.
- RSD: `FB(P)=2` e `FB(E)≥0` — sobe `E`, desce `P` como seu filho direito.
- RSE: espelho de RSD (`FB(P)=-2`, `FB(D)≤0`) — sobe `D`, desce `P` como seu filho esquerdo.
- Ambas resolvem desbalanceamento "reto" (mesmo lado nos dois níveis); quando o
  desbalanceamento é "torto", é preciso rotação dupla (Teoria 04).

**Próximo:** [[Teoria 04 - Rotações duplas (RED e RDE)]].
