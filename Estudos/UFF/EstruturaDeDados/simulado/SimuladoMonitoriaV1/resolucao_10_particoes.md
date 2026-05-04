# Exercício 10 — Geração de Partições

## Enunciado

Gere as partições para a seguinte sequência de elementos:

```
31 12 84 45 85 23 97 86 30 54 25 56 79 66 59 75
26 48 68  2 24 72  5  7
```

**a)** Seleção com Substituição — memória suporta **5 registros**
**b)** Seleção Natural — reservatório de tamanho **3**, memória suporta **5 registros**

---

## 📚 Conceitos antes de resolver

### O que é "gerar partições"?
Quando um arquivo é grande demais para ordenar tudo de uma vez na memória, dividimos o trabalho em etapas:
1. Lemos alguns elementos para a memória
2. Ordenamos e gravamos em "partições" (arquivos menores ordenados)
3. Depois intercalamos essas partições

### O que é Seleção com Substituição?
> A ideia é manter a memória **sempre cheia**. Cada vez que gravamos um elemento na partição, buscamos o próximo do arquivo para substituir. Se o novo elemento for **menor que o último gravado**, ele fica "congelado" (não pode entrar na partição atual). Quando tudo estiver congelado, a partição fecha e começa outra.

### O que é Seleção Natural?
> Igual à com substituição, mas os elementos congelados vão para um **reservatório** (em disco). Quando o reservatório encher, a partição fecha, o reservatório vira a nova memória e começa tudo de novo.

---

## Parte A — Seleção com Substituição (M = 5)

**Sequência completa:**
```
31 12 84 45 85 | 23 97 86 30 54 | 25 56 79 66 59 | 75 26 48 68 2 | 24 72 5 7
```

**Regras:**
- Memória tem 5 posições
- A cada passo: escolhe o **menor não congelado** da memória, grava na partição, lê próximo do arquivo
- Se o próximo lido for **menor que o último gravado** → **congela**
- Quando tudo estiver congelado → fecha partição, descongela tudo, abre nova

---

### 🔵 PARTIÇÃO 1

**Leitura inicial — carrega os primeiros 5:**
```
Memória: [31, 12, 84, 45, 85]
Último gravado: (nada ainda)
Arquivo restante: 23 97 86 30 54 25 56 ...
```

| Passo | Menor na memória | Grava | Lê do arquivo | Novo < último? | Ação |
|---|---|---|---|---|---|
| 1 | **12** | 12 | 23 | 23 > 12 → não | Entra normalmente |
| 2 | **23** | 23 | 97 | 97 > 23 → não | Entra normalmente |
| 3 | **31** | 31 | 86 | 86 > 31 → não | Entra normalmente |
| 4 | **45** | 45 | 30 | 30 < 45 → **sim** | **Congela 30** |
| 5 | **84** | 84 | 54 | 54 < 84 → **sim** | **Congela 54** |
| 6 | **85** | 85 | 25 | 25 < 85 → **sim** | **Congela 25** |
| 7 | **86** | 86 | 56 | 56 < 86 → **sim** | **Congela 56** |
| 8 | **97** | 97 | 79 | 79 < 97 → **sim** | **Congela 79** |

Memória agora: [30, 54, 25, 56, 79] — todos congelados! → **Fecha Partição 1**

> **Partição 1: 12, 23, 31, 45, 84, 85, 86, 97**

---

### 🟢 PARTIÇÃO 2

Descongela tudo: memória = [30, 54, 25, 56, 79]
Arquivo restante: 66 59 75 26 48 68 2 24 72 5 7

| Passo | Menor na memória | Grava | Lê do arquivo | Novo < último? | Ação |
|---|---|---|---|---|---|
| 1 | **25** | 25 | 66 | 66 > 25 → não | Entra normalmente |
| 2 | **30** | 30 | 59 | 59 > 30 → não | Entra normalmente |
| 3 | **54** | 54 | 75 | 75 > 54 → não | Entra normalmente |
| 4 | **56** | 56 | 26 | 26 < 56 → **sim** | **Congela 26** |
| 5 | **59** | 59 | 48 | 48 < 59 → **sim** | **Congela 48** |
| 6 | **66** | 66 | 68 | 68 > 66 → não | Entra normalmente |
| 7 | **68** | 68 | 2 | 2 < 68 → **sim** | **Congela 2** |
| 8 | **75** | 75 | 24 | 24 < 75 → **sim** | **Congela 24** |
| 9 | **79** | 79 | 72 | 72 < 79 → **sim** | **Congela 72** |

Memória: [26, 48, 2, 24, 72] — todos congelados! → **Fecha Partição 2**

> **Partição 2: 25, 30, 54, 56, 59, 66, 68, 75, 79**

---

### 🟠 PARTIÇÃO 3

Descongela: memória = [26, 48, 2, 24, 72]
Arquivo restante: 5 7

| Passo | Menor na memória | Grava | Lê do arquivo | Novo < último? | Ação |
|---|---|---|---|---|---|
| 1 | **2** | 2 | 5 | 5 > 2 → não | Entra normalmente |
| 2 | **5** | 5 | 7 | 7 > 5 → não | Entra normalmente |
| 3 | **7** | 7 | (fim) | — | Sem mais elementos |
| 4 | **24** | 24 | — | — | — |
| 5 | **26** | 26 | — | — | — |
| 6 | **48** | 48 | — | — | — |
| 7 | **72** | 72 | — | — | — |

Arquivo acabou → **Fecha Partição 3**

> **Partição 3: 2, 5, 7, 24, 26, 48, 72**

---

### ✅ Resultado Final — Parte A

| Partição | Elementos |
|---|---|
| P1 | 12, 23, 31, 45, 84, 85, 86, 97 |
| P2 | 25, 30, 54, 56, 59, 66, 68, 75, 79 |
| P3 | 2, 5, 7, 24, 26, 48, 72 |

---

## Parte B — Seleção Natural (M = 5, Reservatório = 3)

**Diferença principal:** elementos congelados vão para o **reservatório** (tamanho máximo 3). Quando o reservatório **encher**, a partição fecha, o reservatório vira a nova memória.

**Sequência completa:**
```
31 12 84 45 85 23 97 86 30 54 25 56 79 66 59 75 26 48 68 2 24 72 5 7
```

---

### 🔵 PARTIÇÃO 1

**Carga inicial:** memória = [31, 12, 84, 45, 85]
Reservatório: [] (vazio, cap. 3)
Arquivo restante: 23 97 86 30 54 25 56 79 ...

| Passo | Menor mem. | Grava | Lê | Novo < último? | Ação | Reservatório |
|---|---|---|---|---|---|---|
| 1 | **12** | 12 | 23 | 23 > 12 → não | Entra na mem. | [] |
| 2 | **23** | 23 | 97 | 97 > 23 → não | Entra na mem. | [] |
| 3 | **31** | 31 | 86 | 86 > 31 → não | Entra na mem. | [] |
| 4 | **45** | 45 | 30 | 30 < 45 → **sim** | **→ Reservatório** | [30] |
| 5 | **84** | 84 | 54 | 54 < 84 → **sim** | **→ Reservatório** | [30, 54] |
| 6 | **85** | 85 | 25 | 25 < 85 → **sim** | **→ Reservatório** | [30, 54, 25] |

Reservatório **cheio** (3/3)! → **Fecha Partição 1**

> **Partição 1: 12, 23, 31, 45, 84, 85**

---

### 🟢 PARTIÇÃO 2

Reservatório vira memória: [30, 54, 25]
Mas memória suporta 5 → lê mais 2 do arquivo: lê **56** e **79**
Memória: [30, 54, 25, 56, 79]
Reservatório: [] (vazio)
Arquivo restante: 66 59 75 26 48 68 2 24 72 5 7

| Passo | Menor mem. | Grava | Lê | Novo < último? | Ação | Reservatório |
|---|---|---|---|---|---|---|
| 1 | **25** | 25 | 66 | 66 > 25 → não | Entra na mem. | [] |
| 2 | **30** | 30 | 59 | 59 > 30 → não | Entra na mem. | [] |
| 3 | **54** | 54 | 75 | 75 > 54 → não | Entra na mem. | [] |
| 4 | **56** | 56 | 26 | 26 < 56 → **sim** | **→ Reservatório** | [26] |
| 5 | **59** | 59 | 48 | 48 < 59 → **sim** | **→ Reservatório** | [26, 48] |
| 6 | **66** | 66 | 68 | 68 > 66 → não | Entra na mem. | [26, 48] |
| 7 | **68** | 68 | 2 | 2 < 68 → **sim** | **→ Reservatório** | [26, 48, 2] |

Reservatório **cheio** (3/3)! → **Fecha Partição 2**

> **Partição 2: 25, 30, 54, 56, 59, 66, 68**

---

### 🟠 PARTIÇÃO 3

Reservatório vira memória: [26, 48, 2]
Lê mais 2: **24** e **72**
Memória: [26, 48, 2, 24, 72]
Reservatório: []
Arquivo restante: 75 5 7

| Passo | Menor mem. | Grava | Lê | Novo < último? | Ação | Reservatório |
|---|---|---|---|---|---|---|
| 1 | **2** | 2 | 75 | 75 > 2 → não | Entra na mem. | [] |
| 2 | **24** | 24 | 5 | 5 < 24 → **sim** | **→ Reservatório** | [5] |
| 3 | **26** | 26 | 7 | 7 < 26 → **sim** | **→ Reservatório** | [5, 7] |
| 4 | **48** | 48 | (fim) | — | Sem mais | [5, 7] |
| 5 | **72** | 72 | — | — | — | [5, 7] |
| 6 | **75** | 75 | — | — | — | [5, 7] |

Arquivo acabou, reservatório não encheu → **Fecha Partição 3**

> **Partição 3: 2, 24, 26, 48, 72, 75**

---

### 🟣 PARTIÇÃO 4

Reservatório vira memória: [5, 7]
Não há mais elementos no arquivo → memória tem apenas 2 elementos

| Passo | Menor mem. | Grava |
|---|---|---|
| 1 | **5** | 5 |
| 2 | **7** | 7 |

> **Partição 4: 5, 7**

---

### ✅ Resultado Final — Parte B

| Partição | Elementos |
|---|---|
| P1 | 12, 23, 31, 45, 84, 85 |
| P2 | 25, 30, 54, 56, 59, 66, 68 |
| P3 | 2, 24, 26, 48, 72, 75 |
| P4 | 5, 7 |

---

## 🆚 Comparação entre os dois métodos

| Critério | Seleção com Substituição | Seleção Natural |
|---|---|---|
| Partições geradas | **3** | **4** |
| Tamanho médio das partições | Maior (≈ 2×M) | Médio (≈ M×e ≈ 2,7×M com M=n) |
| Elementos congelados vão para... | Ficam na memória | Vão para o **reservatório** |
| Quando a partição fecha? | Quando a memória toda congela | Quando o **reservatório enche** |
| Vantagem | Simples | Partições maiores quando M=n |

> 💡 No nosso caso a Seleção com Substituição gerou menos partições (3 vs 4) porque o reservatório pequeno (tamanho 3) fez a Seleção Natural fechar as partições mais cedo.