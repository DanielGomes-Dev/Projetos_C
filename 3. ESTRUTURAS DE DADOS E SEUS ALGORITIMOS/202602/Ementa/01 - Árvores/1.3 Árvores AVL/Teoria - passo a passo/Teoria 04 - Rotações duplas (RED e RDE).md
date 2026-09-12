# Teoria 04 — Rotações duplas: RED (≡ LR) e RDE (≡ RL)

> **Onde isto entra:** cobre o caso que a rotação simples (Teoria 03) não resolve sozinha —
> quando o desbalanceamento é "torto" (zigue-zague), não "reto".
> **Antes:** [[Teoria 03 - Rotações simples (RSD e RSE)]].
> **Fonte:** `lista03-EDA/07_AVL_2026_08_25.pdf`, págs. 28–36 (regra e código); exemplo
> numérico da seção 3 construído para este arquivo (menor que os do PDF, mas verificando a
> mesma regra) — o PDF ilustra o mesmo caso com uma árvore maior, ver pág. 28-30 se quiser
> conferir contra o material original.

## 1. A ideia em uma frase

Quando o desbalanceamento "muda de lado no meio do caminho" (ex.: pesado à esquerda, mas o
problema real está à *direita* daquele filho esquerdo), uma única rotação simples pioraria
as coisas — é preciso **duas rotações em sequência**.

## 2. As regras — lidas devagar

> **RED(P)** (Rotação Esquerda-Direita, ≡ "LR"): `FB(P) = 2` **e** `FB(E) < 0`.
> Aplicação: **1º** `RSE(E)`, **2º** `RSD(P)`.
>
> **RDE(P)** (Rotação Direita-Esquerda, ≡ "RL"): `FB(P) = -2` **e** `FB(D) > 0`.
> Aplicação: **1º** `RSD(D)`, **2º** `RSE(P)`.

> 📖 **Por que duas rotações, e nessa ordem:** em RED, `P` está pesado à esquerda
> (`FB(P)=2`), mas dentro do lado esquerdo (`E`), o peso está à **direita** de `E`
> (`FB(E)<0`) — é um "zigue-zague" (esquerda depois direita). A primeira rotação (`RSE(E)`)
> **endireita** esse zigue-zague, transformando o caso em um desbalanceamento "reto" que a
> segunda rotação (`RSD(P)`) já sabe resolver (Teoria 03). RDE é o espelho completo.

## 3. Conferindo RED com um exemplo numérico pequeno

Construa a árvore: `P=50` com `esq=E=30` (`30` tem `esq` vazia, `dir=40`, folha) e `dir`
vazio.
```
        50
       /
     30
       \
        40
```

> **Calculando FB:** `40` é folha, `FB=0`, `altura=0`. `30`: esq vazia (altura -1), dir=`40`
> (altura 0) → `altura(30) = 1+max(-1,0) = 1`, **`FB(30) = -1 - 0 = -1`** (negativo → ✔
> condição `FB(E)<0`). `50`: esq=`30` (altura 1), dir vazia (altura -1) →
> **`FB(50) = 1 - (-1) = 2`** (✔ condição `FB(P)=2`). RED se aplica.

**Passo 1 — `RSE(E=30)`:** gira a subárvore de `30` para a esquerda: `40` (filho direito de
`30`) sobe, `30` desce e vira filho **esquerdo** de `40`.
```
        50                    50
       /                     /
     30          RSE(30)   40
       \        ------->   /
        40                30
```
Depois deste passo, o zigue-zague virou "reto": `50` pesado à esquerda, e agora o lado
esquerdo (`40`) também pesado à esquerda.

**Passo 2 — `RSD(P=50)`:** agora é uma rotação simples direita comum (Teoria 03): `40` sobe
para o lugar de `50`; `50` desce e vira filho **direito** de `40`.
```
        50                     40
       /            RSD(50)   /  \
     40             ------->  30   50
     /
   30
```

> **Conferindo o resultado:** `30` e `50` são folhas (`FB=0` cada). `40`: esq=`30` altura 0,
> dir=`50` altura 0 → `FB(40)=0`. Todos dentro de `{-1,0,1}` — **consertado**. E a ordem
> em-ordem continua `30, 40, 50` — a mesma de antes da rotação (só a forma mudou).

## 4. O código — lido devagar

```c
TAVL *RED(TAVL *a) {
  a->esq = RSE(a->esq);   // passo 1: endireita o zigue-zague dentro do filho esquerdo
  a = RSD(a);              // passo 2: agora é rotação simples comum
  return a;
}

TAVL *RDE(TAVL *a) {
  a->dir = RSD(a->dir);    // espelho: endireita o zigue-zague dentro do filho direito
  a = RSE(a);
  return a;
}
```

> 📖 **Lendo `RED` devagar:** `a->esq = RSE(a->esq)` chama a rotação já conhecida (Teoria 3)
> só na subárvore esquerda, e **reconecta** o resultado ali — depois disso, `a` (que é `P`)
> já está no formato "reto", e `a = RSD(a)` resolve como de costume. **`RED` não tem lógica
> nova nenhuma** — é só orquestrar `RSE` e `RSD`, já prontas, na ordem certa.

## 5. RDE — o espelho, conferido com o mesmo tipo de exemplo

Árvore: `P=50` com `dir=D=70` (`70` tem `esq=60`, `dir` vazia) e `esq` vazio.
```
        50
          \
           70
          /
        60
```
`FB(70) = altura(60)=0 - altura(vazia)=-1 = 1` (positivo → ✔ condição `FB(D)>0`). `FB(50) =
altura(vazia)=-1 - altura(70)=1 = -2` (✔ condição `FB(P)=-2`). RDE se aplica: **1º**
`RSD(D=70)` (endireita, `60` sobe dentro da subárvore de `70`), **2º** `RSE(P=50)` (agora
reto, `60` sobe para o topo). Resultado final: `60` raiz, `esq=50`, `dir=70` — todos com
`FB=0`, em-ordem `50, 60, 70` preservada.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| checar `FB(E)<0` (não só `FB(P)=2`) | distingo "reto" (Teoria 03) de "torto" (aqui) — é essa checagem extra que decide qual receita usar |
| aplicar `RSE(E)` antes de `RSD(P)` | resolvo o zigue-zague **primeiro no nível de baixo**, transformando o problema num caso já conhecido, em vez de inventar uma rotação nova |
| reaproveitar `RSE`/`RSD` sem alterá-las | rotação dupla não é um algoritmo novo — é composição de duas rotações simples já corretas |

## 7. Exercícios de fixação

1. Um nó `P` tem `FB(P)=2`. O filho esquerdo `E` tem `FB(E)=1`. Isso é RSD ou RED? Por quê?
2. Um nó `P` tem `FB(P)=-2`, e o filho direito `D` tem `FB(D)=0`. Isso é RSE ou RDE?
3. Depois de aplicar `RSE(E)` (o passo 1 de RED), a árvore inteira já está balanceada, ou é
   preciso necessariamente o passo 2?

### Gabarito

1. RSD — a condição de RED exige `FB(E) < 0`; aqui `FB(E)=1` (positivo, "reto"), então é
   caso de RSD (Teoria 03), não RED.
2. RSE — a condição de RDE exige `FB(D) > 0`; aqui `FB(D)=0`, que satisfaz a condição de
   RSE (`FB(D) ≤ 0`), não a de RDE.
3. É preciso o passo 2. O passo 1 (`RSE(E)`) só **reorganiza o zigue-zague** para virar
   "reto" — ele não muda a altura total daquele lado nem conserta o `FB(P)` da raiz `P`.
   Só depois do passo 2 (`RSD(P)`) o nó `P` fica com `FB` dentro de `{-1,0,1}`.

## Resumo

- RED (LR): `FB(P)=2`, `FB(E)<0` → `RSE(E)` depois `RSD(P)`.
- RDE (RL): `FB(P)=-2`, `FB(D)>0` → `RSD(D)` depois `RSE(P)`.
- Rotação dupla não é uma operação nova — é duas rotações simples aplicadas em sequência,
  a primeira "endireitando" o zigue-zague, a segunda resolvendo o desbalanceamento "reto"
  resultante.

**Próximo:** [[Teoria 05 - Inserção completa em AVL]].
