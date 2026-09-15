# SimulEDA P1 — Exercício 10 (Geração de Partições)

> Toda a mecânica abaixo (posição do arquivo consumida a cada leitura, conteúdo exato da
> memória/reservatório a cada passo) foi conferida rodando um simulador em C, elemento por
> elemento — não só "no olho". Isso importa porque um rastreamento manual de 24 elementos é
> fácil de errar (achei e corrigi justamente um erro desse tipo revisando este exercício —
> nota no final da Parte B).

## Entrada (24 elementos, na ordem lida do arquivo)

```
31 12 84 45 85 23 97 86 30 54 25 56 79 66 59 75 26 48 68 2 24 72 5 7
```

## Conceito: por que "gerar partições"?

Um arquivo grande demais pra caber inteiro na memória não pode ser ordenado de uma vez. A
primeira fase de uma ordenação externa é **gerar partições** (trechos já ordenados, do
tamanho que a memória permitir) que depois são intercaladas (módulo 3.3). O objetivo aqui é
gerar **poucas** partições, e **grandes** — quanto menos partições, menos trabalho de
intercalação depois.

---

## Parte A — Seleção por substituição (M = 5)

**Regra** ([[../../03 - Arquivos e Ordenação Externa/3.2 Geração de Partições Classificadas/Teoria - passo a passo/Teoria 02 - Seleção por substituição (replacement selection)|Teoria 02 de 3.2]]):
mantenho até M registros "ativos" na memória; a cada passo, tiro o **menor ativo**, gravo na
partição e leio o próximo elemento do arquivo no lugar dele — se esse novo elemento for
**menor que o último gravado**, ele não serve mais para a partição atual: fica **congelado**
(ocupa a mesma memória, mas não compete mais como "menor" até a partição fechar). Quando
todos os M registros estiverem congelados, a partição fecha e os congelados viram a memória
ativa da próxima partição.

### Partição 1

Memória inicial: `[31, 12, 84, 45, 85]`.

| Sai (menor ativo) | Grava | Lê a seguir | Comparação com o gravado | Ação |
|---|---|---|---|---|
| 12 | 12 | 23 | 23 ≥ 12 | entra ativo |
| 23 | 23 | 97 | 97 ≥ 23 | entra ativo |
| 31 | 31 | 86 | 86 ≥ 31 | entra ativo |
| 45 | 45 | 30 | 30 < 45 | **congela** (reservatório: 30) |
| 84 | 84 | 54 | 54 < 84 | **congela** (30, 54) |
| 85 | 85 | 25 | 25 < 85 | **congela** (30, 54, 25) |
| 86 | 86 | 56 | 56 < 86 | **congela** (30, 54, 25, 56) |
| 97 | 97 | 79 | 79 < 97 | **congela** (30, 54, 25, 56, 79) — memória toda congelada! |

**Partição 1 = 12, 23, 31, 45, 84, 85, 86, 97** (8 elementos)

### Partição 2

Memória = congelados da partição 1: `[30, 54, 25, 56, 79]`.

| Sai | Grava | Lê a seguir | Comparação | Ação |
|---|---|---|---|---|
| 25 | 25 | 66 | 66 ≥ 25 | ativo |
| 30 | 30 | 59 | 59 ≥ 30 | ativo |
| 54 | 54 | 75 | 75 ≥ 54 | ativo |
| 56 | 56 | 26 | 26 < 56 | congela (26) |
| 59 | 59 | 48 | 48 < 59 | congela (26, 48) |
| 66 | 66 | 68 | 68 ≥ 66 | ativo |
| 68 | 68 | 2 | 2 < 68 | congela (26, 48, 2) |
| 75 | 75 | 24 | 24 < 75 | congela (26, 48, 2, 24) |
| 79 | 79 | 72 | 72 < 79 | congela (26, 48, 2, 24, 72) — memória toda congelada! |

**Partição 2 = 25, 30, 54, 56, 59, 66, 68, 75, 79** (9 elementos)

### Partição 3

Memória = congelados da partição 2: `[26, 48, 2, 24, 72]`. Só restam **5** e **7** no
arquivo.

| Sai (menor ativo) | Grava | Lê a seguir | Ação |
|---|---|---|---|
| 2 | 2 | 5 | 5 ≥ 2 → ativo |
| 5 | 5 | 7 | 7 ≥ 5 → ativo |
| 7 | 7 | (arquivo acabou) | posição fica vazia |
| 24 | 24 | — | — |
| 26 | 26 | — | — |
| 48 | 48 | — | — |
| 72 | 72 | — | — |

**Partição 3 = 2, 5, 7, 24, 26, 48, 72** (7 elementos)

### Resultado — Parte A

| Partição | Elementos | Tamanho |
|---|---|---|
| P1 | 12, 23, 31, 45, 84, 85, 86, 97 | 8 |
| P2 | 25, 30, 54, 56, 59, 66, 68, 75, 79 | 9 |
| P3 | 2, 5, 7, 24, 26, 48, 72 | 7 |

**3 partições** (contra `⌈24/5⌉ = 5` que a geração simples produziria com o mesmo M).

---

## Parte B — Seleção natural (M = 5, reservatório = 3)

**Diferença para a Parte A:** os elementos congelados não ficam ocupando slots dentro dos
mesmos M registros — vão para um **reservatório à parte**, com capacidade fixa de **3**. Isso
significa que a partição pode fechar **antes** de a memória inteira esvaziar, assim que o
reservatório enche (não há mais onde pôr o próximo elemento pequeno demais).

> ⚠️ **Ponto em aberto:** o enunciado não detalha o que fazer com os registros que ainda
> estão ativos na memória (nem gravados, nem congelados) no exato momento em que o
> reservatório enche. Adotei a regra que **não perde nenhum elemento**: eles passam direto
> para a memória da **próxima** partição, junto com o conteúdo do reservatório (só então a
> partição atual fecha de verdade). É a única leitura que não descarta dado nenhum do
> arquivo — qualquer implementação real *precisa* disso, senão a ordenação corrompe a saída.
> Se o professor usou uma regra diferente em sala, é só essa parte que muda.

### Partição 1

Memória inicial: `[31, 12, 84, 45, 85]`. Reservatório: `[]` (capacidade 3).

| Sai | Grava | Lê a seguir | Ação | Reservatório |
|---|---|---|---|---|
| 12 | 12 | 23 | 23 ≥ 12 → ativo | [] |
| 23 | 23 | 97 | 97 ≥ 23 → ativo | [] |
| 31 | 31 | 86 | 86 ≥ 31 → ativo | [] |
| 45 | 45 | 30 | 30 < 45 → congela | [30] |
| 84 | 84 | 54 | 54 < 84 → congela | [30, 54] |
| 85 | 85 | 25 | 25 < 85 → congela | [30, 54, 25] — **cheio!** |

Reservatório cheio: fecha a partição. Na memória ainda restavam **86 e 97** — nunca tinham
sido escolhidos como "menor ativo" (os dois eram grandes, sempre perdiam a vez), então não
foram nem gravados nem congelados. Eles **passam direto para a próxima partição**, junto com
o reservatório.

**Partição 1 = 12, 23, 31, 45, 84, 85** (6 elementos)

### Partição 2

Memória = reservatório `[30, 54, 25]` + sobras ativas `[86, 97]` = `[30, 54, 25, 86, 97]`
(já enche os 5 — nada a ler do arquivo ainda). Reservatório: `[]`.

| Sai | Grava | Lê a seguir | Ação | Reservatório |
|---|---|---|---|---|
| 25 | 25 | 56 | 56 ≥ 25 → ativo | [] |
| 30 | 30 | 79 | 79 ≥ 30 → ativo | [] |
| 54 | 54 | 66 | 66 ≥ 54 → ativo | [] |
| 56 | 56 | 59 | 59 ≥ 56 → ativo | [] |
| 59 | 59 | 75 | 75 ≥ 59 → ativo | [] |
| 66 | 66 | 26 | 26 < 66 → congela | [26] |
| 75 | 75 | 48 | 48 < 75 → congela | [26, 48] |
| 79 | 79 | 68 | 68 < 79 → congela | [26, 48, 68] — **cheio!** |

Fecha a partição. **86 e 97** de novo nunca chegaram a ser escolhidos (continuam sendo os
maiores de toda a memória) — passam de novo, intactos, para a próxima partição.

**Partição 2 = 25, 30, 54, 56, 59, 66, 75, 79** (8 elementos)

### Partição 3

Memória = reservatório `[26, 48, 68]` + sobras `[86, 97]` = `[26, 48, 68, 86, 97]`.
Reservatório: `[]`.

| Sai | Grava | Lê a seguir | Ação | Reservatório |
|---|---|---|---|---|
| 26 | 26 | 2 | 2 < 26 → congela | [2] |
| 48 | 48 | 24 | 24 < 48 → congela | [2, 24] |
| 68 | 68 | 72 | 72 ≥ 68 → ativo | [2, 24] |
| 72 | 72 | 5 | 5 < 72 → congela | [2, 24, 5] — **cheio!** |

Fecha a partição. **86 e 97** sobrevivem intactos de novo (é a 3ª vez seguida que perdem a
vez de "menor").

**Partição 3 = 26, 48, 68, 72** (4 elementos)

### Partição 4

Memória = reservatório `[2, 24, 5]` + sobras `[86, 97]` = `[2, 24, 5, 86, 97]`. Arquivo:
só resta o **7**.

| Sai | Grava | Lê a seguir | Ação |
|---|---|---|---|
| 2 | 2 | 7 | 7 ≥ 2 → ativo |
| 5 | 5 | (arquivo acabou) | — |
| 7 | 7 | — | — |
| 24 | 24 | — | — |
| 86 | 86 | — | — |
| 97 | 97 | — | — |

Arquivo esgotado: o que sobra na memória sai em ordem crescente, sem mais nenhuma leitura
(nada resta para comparar/congelar).

**Partição 4 = 2, 5, 7, 24, 86, 97** (6 elementos)

### Resultado — Parte B

| Partição | Elementos | Tamanho |
|---|---|---|
| P1 | 12, 23, 31, 45, 84, 85 | 6 |
| P2 | 25, 30, 54, 56, 59, 66, 75, 79 | 8 |
| P3 | 26, 48, 68, 72 | 4 |
| P4 | 2, 5, 7, 24, 86, 97 | 6 |

**4 partições** (6+8+4+6 = 24 ✔ nenhum elemento perdido) — uma a mais que a Parte A. Repare
como **86 e 97** (lidos muito cedo, na Partição 1) só conseguem sair na **última** partição:
como são os dois maiores valores do arquivo inteiro, perdem a disputa de "menor ativo" toda
vez e ficam sendo empurrados de partição em partição até sobrar só o final do arquivo.

---

## Comparação

| Critério | Seleção com substituição (A) | Seleção natural, reservatório=3 (B) |
|---|---|---|
| Partições geradas | **3** | **4** |
| Tamanho médio | maior (~8/partição) | menor (~5/partição) |
| Onde ficam os "pequenos demais" | na própria memória M, só marcados | num reservatório separado, de tamanho fixo |
| Quando fecha a partição | quando TODA a memória (M) está congelada | quando o RESERVATÓRIO enche (mesmo com memória ainda ativa) |

O reservatório limitado é sempre **igual ou pior** que a substituição sem limite (nunca gera
menos partições) — ele só existe para modelar um cenário onde não dá pra reservar memória
suficiente para guardar todos os elementos "adiantados" de uma vez.
