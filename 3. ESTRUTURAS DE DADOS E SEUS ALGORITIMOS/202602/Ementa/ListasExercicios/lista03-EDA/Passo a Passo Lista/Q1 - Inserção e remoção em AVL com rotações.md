# Q1 — Inserção e remoção em AVL, indicando as rotações

> **Origem:** `lista03-EDA.pdf`, questão 1 · **Código resolvido:** [[../Q1/claude/main.c]]
> **Antes disto, veja:** [[../../../01 - Árvores/1.3 Árvores AVL/Teoria - passo a passo/Teoria 05 - Inserção completa em AVL|1.3 Teoria 05]] (o método usado aqui é exatamente o mesmo, só numa sequência maior)

## 1. O que o exercício pede

> Partindo de uma AVL que é uma folha com a informação `50`:
> (a) inserir `{1, 64, 12, 18, 66, 38, 95, 58, 59, 70, 68, 39, 62, 7, 60, 43, 16, 67, 34,
> 35}`, indicando as rotações;
> (b) retirar `{50, 95, 70, 60, 35}`, explicitando as rotações.

Ou seja: partindo da árvore `[50]`, inserir 20 valores um de cada vez (anotando toda
rotação que disparar), e depois remover 5 valores específicos da árvore final (anotando
rotações também).

## 2. A ideia geral

Isto não é um exercício novo — é o método de [[../../../01 - Árvores/1.3 Árvores AVL/Teoria - passo a passo/Teoria 05 - Inserção completa em AVL|1.3 Teoria 05]] aplicado a uma sequência **bem maior** (20 inserções, contra 11 da Teoria), mais a parte de remoção (que a Teoria 05 não cobriu). O código (`TAVL_insere`, `TAVL_retira` em `TAVL.c`) já imprime a rotação a cada vez que ela acontece — a única coisa que muda entre inserção e remoção é a **condição** que decide qual rotação aplicar:

| | Inserção (`TAVL_insere`) | Remoção (`TAVL_retira`) |
|---|---|---|
| Decide RSD vs. RED comparando... | o valor inserido (`elem`) com a chave do filho | o **sinal do FB do filho** (`FB(t->esq) >= 0` ou `<= 0`) |
| Por quê a diferença? | na inserção, você sabe de que lado o valor **entrou** | na remoção, o nó removido já **saiu** — não há "valor" para comparar, só o formato que sobrou |

## 3. Resolução passo a passo

### Parte (a) — as 20 inserções

Trace completo (verificado à mão, célula por célula, seguindo exatamente `TAVL_insere`):

| # | Insere | Nó que violou `FB` | Rotação impressa |
|---|---|---|---|
| 1 | `1` | — | — |
| 2 | `64` | — | — |
| 3 | `12` | — | — |
| 4 | `18` | `1` (`FB=-2`, `18>12`→"reto") | `RSE(1)` |
| 5 | `66` | — | — |
| 6 | `38` | — | — |
| 7 | `95` | `64` (`FB=-2`, `95>66`→"reto") | `RSE(64)` |
| 8 | `58` | — | — |
| 9 | `59` | `64` (`FB=-2`, `59>58`→"reto") | `RSE(64)` |
| 10 | `70` | — | — |
| 11 | `68` | `95` (`FB=2`, `68<70`→"reto") | `RSD(95)` |
| 12 | `39` | `18` (`FB=-2`, `39>38`→"reto") | `RSE(18)` |
| 13 | `62` | — | — |
| 14 | `7` | — | — |
| 15 | `60` | `59` (`FB=-2`, `60<62`→"torto") | `RDE(59)` |
| 16 | `43` | — | — |
| 17 | `16` | — | — |
| 18 | `67` | — | — |
| 19 | `34` | — | — |
| 20 | `35` | `12` (`FB=-2`, `35<38`→"torto") | `RDE(12)` |

> 📖 **Um exemplo trabalhado, passo 15 (`RDE(59)`), pra você conferir o método:** antes de
> inserir `60`, o nó `59` tem `esq` vazio e `dir=62` (folha) — `FB(59) = -1 - 0 = -1`. Insere
> `60`: desce `59 → 62`, `60 < 62` → entra como filho **esquerdo** de `62`. Subindo:
> `FB(62) = alt(60,0) - alt(vazio,-1) = 1` (ok, sem violação). `FB(59) = alt(vazio,-1) -
> alt(62, agora altura 1) = -2`. O código checa `elem(60) > t->dir->info` → `t->dir` é `62`,
> então `60 > 62`? **Não** → cai no `else`, aplica `RDE(59)` — exatamente o mesmo critério
> "torto" da [[../../../01 - Árvores/1.3 Árvores AVL/Teoria - passo a passo/Teoria 04 - Rotações duplas (RED e RDE)|Teoria 04]]. Resultado: `60` sobe, vira raiz da subárvore, com `59`
> à esquerda e `62` à direita.

**Árvore depois das 20 inserções** (raiz `50`, conferida nó a nó — todo `FB ∈ {-1,0,1}`):

```
                                50
                    /                          \
                  18                            66
                /    \                        /    \
              12       38                   58       70
             /  \     /  \                 /  \     /  \
            1    16  34   39              64   60  68   95
             \        \     \                  / \   \
              7        35    43               59 62  67
```

### Parte (b) — as 5 remoções

`TAVL_retira` trata "remover um nó com dois filhos" trocando pelo **predecessor** (o maior
valor da subárvore esquerda) e removendo o predecessor de onde ele realmente estava — a
mesma técnica de remoção de BST (1.2, Teoria 04), só que seguida de uma checagem de `FB` na
volta da recursão.

| Remove | O que acontece | Rotação impressa |
|---|---|---|
| `50` (raiz, 2 filhos) | predecessor = `43` (maior da subárvore esquerda) — `50` vira `43`; o `43`-folha original é removido de onde estava | — |
| `95` (folha) | remove direto; sobe checando `FB` — `70` fica com `FB=2` (`68 ≥ 0` → "reto") | `RSD(70)` |
| `70` (1 filho, `68`) | remove direto, `68` assume o lugar; sem violação de `FB` ao subir | — |
| `60` (2 filhos: `59`,`62`) | predecessor = `59` (é o próprio filho esquerdo, sem filho direito) — `60` vira `59`; o `59`-folha original é removido | — |
| `35` (folha) | remove direto; sem violação de `FB` ao subir | — |

> 📖 **Conferindo a remoção de `95` (a única com rotação):** antes de remover, `70` tem
> `esq=68[esq=67]` (altura 1) e `dir=95` (folha, altura 0) — `FB(70) = 1 - 0 = 1`. Remove
> `95` (é folha, sai direto): `70->dir = NULL`. Subindo: `FB(70) = alt(68,1) - alt(vazio,-1)
> = 1 - (-1) = 2`. O código checa `FB(t->esq) >= 0` → `FB(68)`: `68` tem `esq=67`
> (altura 0), `dir` vazio → `FB(68) = 0 - (-1) = 1 ≥ 0` → **RSD(70)**. Resultado: `68` sobe,
> `70` desce como filho direito de `68`.

**Árvore final, depois das 5 remoções** (conferida nó a nó — todo `FB ∈ {-1,0,1}`):

```
                                43
                    /                          \
                  18                            66
                /    \                        /    \
              12       38                   58       68
             /  \     /  \                 /  \       \
            1    16  34   39              64   59      67
             \                                   \
              7                                   62
```

## 4. Resultado final

Árvore da seção 3 (parte b) é o resultado final impresso por `TAVL_imprime` ao rodar o
código — rode `Q1/claude/main.c` para conferir a saída exata (formato rotacionado 90°, como
`TAVL_imprime`/`imprime_aux` desenha).

**Conferindo:** todo nó tem `FB ∈ {-1,0,1}`? Sim (verificado nó a nó acima) — a árvore
final é uma AVL válida.

## 5. Habilidades necessárias

- [ ] Calcular `FB` e decidir entre rotação simples e dupla → [[../../../01 - Árvores/1.3 Árvores AVL/Teoria - passo a passo/Teoria 02 - Definição de AVL e o fator de balanceamento|1.3 Teoria 02]]
- [ ] Aplicar RSD/RSE → [[../../../01 - Árvores/1.3 Árvores AVL/Teoria - passo a passo/Teoria 03 - Rotações simples (RSD e RSE)|1.3 Teoria 03]]
- [ ] Aplicar RED/RDE → [[../../../01 - Árvores/1.3 Árvores AVL/Teoria - passo a passo/Teoria 04 - Rotações duplas (RED e RDE)|1.3 Teoria 04]]
- [ ] Remoção de BST com predecessor (dois filhos) → [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 04 - Remoção numa BST (os três casos)|1.2 Teoria 04]]

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — só 3 inserções, sem remoção

Insira `10, 5, 1` (nessa ordem) numa AVL vazia. Trace: `10`→raiz. `5`→esquerda de `10`, sem
violação (`FB(10)=1`). `1`→esquerda de `5`; sobe: `FB(5)=1` (ok); `FB(10)=alt(5,1)-alt(vazio,-1)
=1-(-1)=2`. `elem(1)<t->esq->info(5)`? `1<5` sim → **RSD(10)**. Resultado: `5` sobe, `10`
desce à direita, `1` continua à esquerda de `5`:
```
    5
   / \
  1   10
```

### Aquecimento 2 — uma remoção simples, sem rotação

Na árvore do Aquecimento 1, remova `10` (folha). `TAVL_retira(10, t=5)`: `10>5` → desce à
direita; `10==10`, é folha (sem filho esquerdo) → remove direto, retorna `NULL`. Subindo:
`FB(5) = alt(1,0) - alt(vazio,-1) = 0-(-1)=1`. Sem violação, sem rotação. Resultado:
```
  5
 /
1
```
