# Q1 — Ordenação por bolha em arquivo binário (`BolhaBin`)

> **Origem:** `lista07-EDA.pdf`, questão 1 · **Código resolvido:** [[../Q1/claude/main.c]]
> **Antes disto, veja:** [[../../../../03 - Arquivos e Ordenação Externa/3.1 Arquivos Binários e Texto/Teoria - passo a passo/Teoria 03 - Acesso aleatório em arquivo binário (fseek, ftell, rewind)|3.1, Teoria 03]] (`fseek`/`ftell`).

## 1. O que o exercício pede

> Escreva o algoritmo de ordenação **por bolha** em arquivos binários:
> `void BolhaBin(char *nomeArq)`.

O arquivo contém uma sequência de `int` (4 bytes cada) e precisa ser ordenado **no
próprio arquivo** — sem carregar tudo para um vetor em RAM. A "memória de trabalho"
permitida é só um punhado de variáveis simples (`int a, b`, contadores).

## 2. A ideia geral

Bubble sort comum compara pares vizinhos `v[j]` e `v[j+1]` num vetor, trocando quando
estão fora de ordem, repetindo passadas até que uma passada inteira não troque nada. A
adaptação para arquivo é direta: **trocar "acessar `v[j]`" por "posicionar o cursor do
arquivo em `j` e ler/gravar"**. Cada posição `j` no arquivo começa no byte `j *
sizeof(int)` — é só aritmética de posição, a mesma ideia de índice de array, aplicada a
bytes em disco em vez de células de memória.

## 3. Resolução passo a passo

### Passo 1 — abrir para leitura E escrita, e descobrir `n`

```c
FILE *fp = fopen(nomeArq, "rb+");
fseek(fp, 0, SEEK_END);
long n = ftell(fp) / (long)sizeof(int);
```

> 📖 **Por que `"rb+"` e não `"rb"`:** o algoritmo precisa **ler** (`fread`) para comparar
> e **escrever** (`fwrite`) para trocar, no mesmo arquivo. `"rb"` (só leitura) não
> permitiria `fwrite`; `"rb+"` abre um arquivo binário existente para os dois.

`n` = número de inteiros = tamanho do arquivo em bytes ÷ 4 (tamanho de um `int`) — a
mesma técnica de "descobrir `n` sem ler dado nenhum" já vista em 3.1.

### Passo 2 — comparar e trocar via `fseek`/`fread`/`fwrite`

```c
for (long j = 0; j < n - 1 - i; j++) {
    int a, b;
    fseek(fp, j * (long)sizeof(int), SEEK_SET);
    fread(&a, sizeof(int), 1, fp);   // v[j]
    fread(&b, sizeof(int), 1, fp);   // v[j+1] (cursor já avançou sozinho)

    if (a > b) {
        fseek(fp, j * (long)sizeof(int), SEEK_SET);
        fwrite(&b, sizeof(int), 1, fp);
        fwrite(&a, sizeof(int), 1, fp);
        trocou = 1;
    }
}
```

> 📖 **Lendo devagar:**
> 1. `fseek(fp, j * sizeof(int), SEEK_SET)` — posiciona o cursor **no início do byte de
>    `v[j]`**. Multiplicar `j` pelo tamanho do tipo é o que converte "índice lógico" em
>    "posição física em bytes".
> 2. `fread(&a, ...)` lê `v[j]`, e o cursor **avança sozinho** para o próximo `int` — por
>    isso o segundo `fread(&b, ...)`, sem novo `fseek`, já lê `v[j+1]`.
> 3. Se `a > b` (fora de ordem): um **novo** `fseek` volta o cursor para a posição de
>    `v[j]` (ele tinha avançado 2 posições com os dois `fread`), e dois `fwrite`
>    seguidos gravam `b` (agora em `j`) e `a` (agora em `j+1`) — a troca.
> 4. **Regra da biblioteca padrão**: não se pode simplesmente alternar `fread`/`fwrite`
>    sem um `fseek` entre eles — é por isso que há um `fseek` explícito antes de cada
>    bloco de gravação, mesmo repetindo uma posição já conhecida.

### Passo 3 — parar cedo se uma passada não trocar nada

```c
if (!trocou) break;
```

Otimização clássica do bubble sort: se uma passada inteira não encontrou par fora de
ordem, o arquivo já está ordenado — não adianta continuar.

## 4. Conferindo com um trace pequeno

Arquivo com 4 inteiros: `[3, 1, 4, 2]`.

**Passada `i=0`** (`j` de 0 a 2):
| `j` | `v[j], v[j+1]` lidos | `a>b`? | Ação | Arquivo depois |
|---|---|---|---|---|
| 0 | `3, 1` | sim | troca | `[1, 3, 4, 2]` |
| 1 | `3, 4` | não | — | `[1, 3, 4, 2]` |
| 2 | `4, 2` | sim | troca | `[1, 3, 2, 4]` |

`trocou=1` → passada seguinte não é pulada.

**Passada `i=1`** (`j` de 0 a 1, porque o maior já "borbulhou" até a posição 3):
| `j` | `v[j], v[j+1]` | `a>b`? | Ação | Arquivo depois |
|---|---|---|---|---|
| 0 | `1, 3` | não | — | `[1, 3, 2, 4]` |
| 1 | `3, 2` | sim | troca | `[1, 2, 3, 4]` |

`trocou=1` → mais uma passada testa, não troca nada (`trocou=0`) → `break`. Arquivo final:
`[1, 2, 3, 4]`. ✔

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `fseek(fp, j * sizeof(int), SEEK_SET)` | traduzo "índice `j`" para "posição em bytes" — o array não existe fisicamente, é só aritmética sobre o arquivo |
| ler `a`, `b`, comparar, e só então regravar | mantenho a memória de trabalho em O(1) — nunca existe um vetor do arquivo inteiro em RAM |
| `fseek` de novo antes de gravar | respeito a regra da stdio: não alternar leitura/escrita sem reposicionar o cursor |
| `if (!trocou) break` | corto o algoritmo assim que a condição de parada (arquivo ordenado) é detectada, sem esperar todas as `n-1` passadas |

## 6. Complexidade

| Aspecto | Custo |
|---|---|
| Comparações/acessos a disco | O(n²) no pior caso (arquivo em ordem reversa) |
| Memória de trabalho | O(1) — só `a`, `b`, contadores |
| Melhor caso (já ordenado) | O(n) — uma passada, `trocou=0`, `break` |

## 7. Exercícios de fixação

1. Por que não dá para simplesmente carregar o arquivo inteiro num `int v[n]`, ordenar em
   RAM, e regravar tudo de uma vez — o que isso violaria no enunciado?
2. Se o arquivo já estiver ordenado, quantas passadas o algoritmo faz?
3. Por que existe um `fseek` logo antes dos dois `fwrite`, se o cursor já está em algum
   lugar do arquivo depois dos dois `fread` anteriores?

### Gabarito

1. Violaria "todo processamento em memória secundária" / a ideia de custar memória O(1) —
   carregar tudo num vetor é exatamente o que o exercício pede para evitar (é a mesma
   memória O(n) que arquivos grandes, maiores que a RAM disponível, não teriam como
   pagar).
2. Uma única passada — nenhuma troca acontece, `trocou` permanece 0, e o `break` interrompe
   antes da segunda passada.
3. Porque, depois dos dois `fread` (que leram `v[j]` e `v[j+1]`), o cursor está
   posicionado **depois** de `v[j+1]` — não mais em `v[j]`, que é onde a gravação precisa
   começar. O `fseek` reposiciona o cursor de volta.

## 8. Exemplos mais simples (aquecimento)

### Aquecimento 1 — arquivo com 2 elementos fora de ordem

`[5, 2]`: `j=0`, `a=5, b=2`, `5>2` → troca → `[2, 5]`. Uma passada, `trocou=1`; segunda
passada (`i=1`, mas `n-1-i = 0`, laço interno não executa) — termina.

### Aquecimento 2 — arquivo com 1 elemento

`n=1`: o laço externo `for (i=0; i<n-1; i++)` não executa nenhuma vez (`n-1=0`) — arquivo
já "ordenado" trivialmente, função retorna sem tocar no arquivo.

---

**Próximo:** [[Q2 - Ordenação por inserção em arquivo binário]].
