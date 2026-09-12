# Q2 — Ordenação por inserção em arquivo binário (`insertSort`)

> **Origem:** `lista07-EDA.pdf`, questão 2 · **Código resolvido:** [[../Q2/claude/main.c]]
> **Antes disto, veja:** [[Q1 - Ordenação por bolha em arquivo binário]] (mesma técnica de
> `fseek`/`fread`/`fwrite` para simular acesso por índice num arquivo).

## 1. O que o exercício pede

> Escreva o algoritmo de ordenação **por inserção** em arquivos binários:
> `void insertSort(char *nomeArq)`.

Mesma restrição do Q1: arquivo de `int`, ordenado **no próprio arquivo**, usando só
variáveis simples como memória de trabalho.

## 2. A ideia geral

Insertion sort mantém um prefixo já ordenado `v[0..i-1]` e, a cada passo, pega
`chave = v[i]` e abre espaço deslocando para a direita todo elemento do prefixo que é
**maior** que a chave, até achar a posição certa. A versão em arquivo troca acesso direto
por índice (`v[k]`) por duas funções auxiliares que fazem `fseek` + `fread`/`fwrite` —
isso deixa o algoritmo **visualmente idêntico** à versão em array, só trocando `v[k]` por
`le(fp, k)` e `v[k] = x` por `grava(fp, k, x)`.

## 3. Resolução passo a passo

### Passo 1 — funções auxiliares `le` e `grava`

```c
static int le(FILE *fp, long k) {
    int x;
    fseek(fp, k * (long)sizeof(int), SEEK_SET);
    fread(&x, sizeof(int), 1, fp);
    return x;
}

static void grava(FILE *fp, long k, int x) {
    fseek(fp, k * (long)sizeof(int), SEEK_SET);
    fwrite(&x, sizeof(int), 1, fp);
}
```

> 📖 **Por que isolar isso em duas funções, em vez de repetir `fseek`+`fread` toda hora
> (como o Q1 fez inline):** com `insertSort` fazendo várias leituras/escritas em posições
> diferentes dentro do mesmo laço (compare com o Q1, que só lê 2 posições fixas por
> iteração), embrulhar em `le`/`grava` deixa o algoritmo principal legível — quase
> idêntico ao pseudocódigo de insertion sort em array.

### Passo 2 — o algoritmo, usando `le`/`grava` no lugar de `v[k]`

```c
for (long i = 1; i < n; i++) {
    int chave = le(fp, i);
    long j = i - 1;

    while (j >= 0 && le(fp, j) > chave) {
        grava(fp, j + 1, le(fp, j));   // desloca v[j] para a direita
        j--;
    }
    grava(fp, j + 1, chave);           // insere a chave no lugar certo
}
```

> 📖 **Lendo devagar, comparando com o array:**
> 1. `chave = le(fp, i)` ≡ `chave = v[i]` — lê o elemento que será inserido no prefixo já
>    ordenado.
> 2. `while (j >= 0 && le(fp, j) > chave)` ≡ `while (j >= 0 && v[j] > chave)` — continua
>    deslocando enquanto o elemento à esquerda for maior que a chave.
> 3. `grava(fp, j + 1, le(fp, j))` ≡ `v[j+1] = v[j]` — desloca o elemento uma posição à
>    direita, abrindo espaço.
> 4. `grava(fp, j + 1, chave)` ≡ `v[j+1] = chave` — depois do laço, `j+1` é a posição
>    correta para a chave (ou porque `j` chegou a `-1`, ou porque achou um elemento não
>    maior que a chave).

## 4. Conferindo com um trace pequeno

Arquivo com 4 inteiros: `[3, 1, 4, 2]`.

**`i=1`**: `chave = le(1) = 1`. `j=0`: `le(0)=3 > 1`? sim → `grava(1, 3)` (desloca 3 para a
direita); `j=-1`. Laço para (`j<0`). `grava(0, 1)` → arquivo: `[1, 3, 4, 2]`.

**`i=2`**: `chave = le(2) = 4`. `j=1`: `le(1)=3 > 4`? não → laço nem entra. `grava(2, 4)`
(regrava no mesmo lugar) → arquivo: `[1, 3, 4, 2]` (sem mudança — `4` já estava no lugar
certo do prefixo `[1,3,4]`).

**`i=3`**: `chave = le(3) = 2`. `j=2`: `le(2)=4 > 2`? sim → `grava(3, 4)`; `j=1`.
`le(1)=3 > 2`? sim → `grava(2, 3)`; `j=0`. `le(0)=1 > 2`? não → para. `grava(1, 2)` →
arquivo: `[1, 2, 3, 4]`. ✔

| `i` | prefixo ordenado antes | ação | arquivo depois |
|---|---|---|---|
| 1 | `[3]` | desloca `3`, insere `1` no início | `[1, 3, 4, 2]` |
| 2 | `[1,3]` | `4` já maior que tudo, fica onde está | `[1, 3, 4, 2]` |
| 3 | `[1,3,4]` | desloca `4` e `3`, insere `2` na posição 1 | `[1, 2, 3, 4]` |

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `le(fp, k)` / `grava(fp, k, x)` | simulo `v[k]` / `v[k] = x` — o arquivo se comporta como um array, ao custo de um `fseek` por acesso |
| deslocar (`grava(j+1, le(j))`) em vez de trocar (como no bubble sort do Q1) | movo só **um** elemento por vez para abrir espaço — insertion sort nunca faz "troca de par", só "empurra e insere" |
| manter o prefixo `[0, i-1]` sempre ordenado | garanto a invariante central do algoritmo: a cada `i`, só falta inserir **um** elemento no lugar certo de um prefixo já correto |

## 6. Complexidade

| Caso | Custo (acessos a disco) |
|---|---|
| Pior caso (arquivo em ordem reversa) | O(n²) |
| Melhor caso (arquivo já ordenado) | O(n) — o `while` nunca desloca nada, cada `i` só faz 1 `le` + 1 `grava` |
| Memória de trabalho | O(1) — `chave`, `i`, `j` |

**Comparando com o Q1 (bubble sort):** mesma complexidade de pior caso (O(n²)), mas
insertion sort é geralmente mais rápido na prática para arquivos "quase ordenados",
porque cada elemento fora do lugar custa só os deslocamentos necessários até achar sua
posição — não uma passada inteira pelo arquivo.

## 7. Exercícios de fixação

1. Por que, no `while`, a condição é `le(fp, j) > chave` e não `le(fp, j) >= chave`? O
   que mudaria com `>=`?
2. Se o arquivo já está ordenado, quantas vezes `grava` é chamada, no total, para todo o
   algoritmo (some as chamadas dentro do `while` e a de fora)?
3. Por que `insertSort` não precisa de uma variável `trocou` como o `BolhaBin` do Q1?

### Gabarito

1. Com `>`, elementos **iguais** à chave não são deslocados (a chave fica depois deles),
   mantendo a ordem relativa de iguais — isso é o que torna insertion sort **estável**.
   Com `>=`, a chave sempre passaria na frente de iguais, o que ainda ordena
   corretamente, mas destrói a estabilidade (a ordem relativa de elementos iguais não
   seria mais preservada).
2. `n - 1` chamadas — uma por valor de `i` (de 1 a n-1), a `grava(j+1, chave)` final de
   cada iteração; o `while` nunca desloca nada porque `le(fp,j) > chave` é sempre falso
   quando o arquivo já está ordenado.
3. Porque insertion sort não tem o conceito de "passada completa sem troca" — cada `i` já
   sabe exatamente quando parar (quando `j<0` ou achou o lugar certo). Não há como
   "detectar cedo" que tudo já está ordenado sem processar cada `i` individualmente (o
   melhor caso já é O(n) naturalmente, sem precisar de uma flag extra).

## 8. Exemplos mais simples (aquecimento)

### Aquecimento 1 — arquivo com 2 elementos, já ordenado

`[1, 2]`: `i=1`, `chave=2`, `j=0`: `le(0)=1 > 2`? não → `grava(1, 2)` (sem mudança).

### Aquecimento 2 — arquivo com 2 elementos, fora de ordem

`[2, 1]`: `i=1`, `chave=1`, `j=0`: `le(0)=2 > 1`? sim → `grava(1, 2)`; `j=-1` → para.
`grava(0, 1)` → arquivo final `[1, 2]`.

---

Isso fecha a `Passo a Passo Lista` da lista07-EDA.
