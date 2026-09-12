# Teoria 03 — Como buscar uma chave numa árvore B?

> **Onde isto entra:** busca é a operação mais simples da árvore B, mas é o alicerce das
> outras duas: inserção (Teoria 04) sempre começa descendo até a folha certa, do mesmo jeito
> que a busca; remoção (Teoria 05) também.
> **Antes:** [[Teoria 02 - O que é uma árvore B (ordem m e propriedades estruturais)]].
> **Fonte:** SZ e CO, cap. 18 (B-TREE-SEARCH) — mesma ideia nos dois, descrita de forma
> muito parecida com busca em BST, só que "dentro de cada nó" agora há uma busca a mais.
> Página exata não verificada nesta sessão (ver aviso na Teoria 01).

## 1. A ideia em uma frase

Buscar numa árvore B é fazer **duas buscas encaixadas**: dentro de cada nó, procure a
chave entre as que estão ali guardadas; se não achar, as próprias chaves do nó dizem qual
filho seguir — desça e repita.

## 2. De onde vem / por que funciona assim

Numa BST, cada nó guarda 1 chave e você só decide entre 2 caminhos (esquerda/direita).
Numa árvore B, cada nó guarda **várias** chaves ordenadas, então a decisão "por onde
descer" não é mais binária — é "entre qual par de chaves vizinhas a chave buscada se
encaixa?". As chaves de um nó funcionam exatamente como os números de página no topo de um
dicionário: elas não são só dados, são **separadores** que dizem onde procurar em seguida.

## 3. O algoritmo — lido pedaço por pedaço

> 📖 **Lendo devagar — o passo dentro de um nó:**
>
> Dado um nó com chaves ordenadas `k₁ < k₂ < ... < kⱼ` (até `m−1` delas) e a chave buscada
> `x`:
> 1. Compare `x` com as chaves do nó, da esquerda para a direita, até achar `x` (busca
>    terminou, achou) **ou** até achar a primeira `kᵢ` maior que `x`.
> 2. Se achou `x` entre as chaves do nó — **pronto**, retorna sucesso (não importa se o nó
>    é folha ou interno: em árvore B "pura", como neste curso, o dado pode estar em
>    qualquer nível).
> 3. Se não achou e o nó é **folha** — `x` não existe na árvore. Retorna falha (não há para
>    onde descer).
> 4. Se não achou e o nó é **interno** — desça para o filho entre `kᵢ₋₁` e `kᵢ` (o filho
>    "encaixado" na posição onde `x` cairia) e repita o processo nesse filho.

## 4. Conferindo com a árvore concreta

Usando a mesma árvore de ordem `m=3` da Teoria 02 (construída passo a passo na Teoria 04):

```
                         [30]
                        /     \
                    [10]       [50]
                   /    \      /    \
                [5]   [20]  [40]  [60]
```

**Busca por 40 (existe na árvore):**

| Nó visitado | Comparações dentro do nó | Decisão |
|---|---|---|
| `[30]` | `40 > 30` | não achou aqui; `40` é maior que a única chave → desce para o filho **da direita** de 30, ou seja `[50]` |
| `[50]` | `40 < 50` | não achou aqui; `40` é menor que a única chave → desce para o filho **da esquerda** de 50, ou seja `[40]` |
| `[40]` | `40 == 40` | **achou!** retorna sucesso |

3 nós visitados (bate com a altura da árvore: 3 níveis, `0,1,2`). ✔

**Busca por 25 (não existe na árvore):**

| Nó visitado | Comparações dentro do nó | Decisão |
|---|---|---|
| `[30]` | `25 < 30` | desce para o filho da esquerda, `[10]` |
| `[10]` | `25 > 10` | `[10]` é **folha** (não tem filho para descer) |

Chegou numa folha sem achar `25` → retorna falha. Repare que a busca não "volta" para
tentar outro caminho — em árvore B, assim como em BST, **existe só um caminho possível**
para onde uma chave poderia estar.

## 5. Letra miúda

**E dentro de um nó, a busca entre as chaves é sequencial ou binária?** Depende do tamanho
de `m`. Para `m` pequeno (como os exemplos deste curso, 3 a 5), procurar sequencialmente
entre as poucas chaves do nó é tão rápido que não faz diferença prática. Para `m` grande
(dezenas/centenas, caso real de disco), vale a pena fazer **busca binária dentro do nó**
(o nó já está todo em RAM depois de lido do disco, então essa parte não custa I/O extra) —
é por isso que a complexidade por nó costuma aparecer como `O(log m)` (busca binária)
e não `O(m)` (busca sequencial) em análises mais cuidadosas.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| "comparo `x` com as chaves do nó" | decido se a resposta já está **aqui**, neste bloco de disco já carregado |
| "não achei, `x` cai entre `kᵢ₋₁` e `kᵢ`" | decido **qual dos próximos blocos de disco** vale a pena ler — é isso que evita ler a árvore inteira |
| "desço para o filho e repito" | faço **mais um acesso a disco** — cada repetição deste passo é o custo real da operação (Teoria 01) |
| "cheguei numa folha e não achei" | não há mais para onde descer; a chave garantidamente **não existe**, porque o caminho até uma chave em árvore B é único |

## 7. Complexidade

| Caso | Complexidade |
|---|---|
| Melhor caso (chave está na raiz) | O(1) nó visitado (mais a busca dentro do nó) |
| Pior caso | O(log_m n) nós visitados (altura da árvore), cada um com uma busca interna de O(log m) ou O(m) |

## 8. Exercícios de fixação

Usando a mesma árvore da seção 4:

1. Trace a busca por `5`. Quantos nós são visitados?
2. Trace a busca por `60`.
3. Trace a busca por `100` (não existe). Em que nó a busca termina, e por quê?
4. Por que a busca em árvore B nunca precisa "voltar atrás" e tentar outro filho depois de
   descer?

### Gabarito

1. `[30]`: `5<30` → esquerda `[10]`. `[10]`: `5<10` → filho esquerdo `[5]`. `[5]`:
   `5==5` → achou. 3 nós visitados.
2. `[30]`: `60>30` → direita `[50]`. `[50]`: `60>50` → filho direito `[60]`. `[60]`:
   `60==60` → achou. 3 nós visitados.
3. `[30]`: `100>30` → direita `[50]`. `[50]`: `100>50` → filho direito `[60]`. `[60]`:
   `100` comparado com a única chave (`60`) — não é igual, e `[60]` é folha (sem filho
   direito para descer) → busca termina em `[60]`, retorna falha.
4. Porque a propriedade de ordenação das chaves (propriedade 5, Teoria 02) garante que,
   dado onde `x` se encaixa entre as chaves de um nó, existe **exatamente um** filho onde
   `x` poderia estar — igual à BST, mas com mais de duas opções por nó em vez de só duas.

## Resumo

- Busca em árvore B = busca dentro do nó (achou? pare) + decidir qual filho descer (não
  achou e há filho) + repetir.
- As chaves de um nó funcionam como separadores que guiam qual filho seguir.
- Custo = altura da árvore × custo de busca dentro de cada nó = O(log_m n) no pior caso.
- O caminho até qualquer chave (existente ou não) é único — nunca há backtracking.

**Próximo:** [[Teoria 04 - Split na inserção (m=3, passo a passo)]].
