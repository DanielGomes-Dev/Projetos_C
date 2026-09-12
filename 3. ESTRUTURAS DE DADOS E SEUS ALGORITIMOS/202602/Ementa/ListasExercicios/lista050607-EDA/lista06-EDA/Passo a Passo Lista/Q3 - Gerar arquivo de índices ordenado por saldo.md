# Q3 — Gerar arquivo de índices ordenado por saldo

> **Origem:** `lista06-EDA.pdf`, questão 3 · **Código resolvido:** [[../Q3/claude/main.c]]
> **Antes disto, veja:** [[Q2 - Buscar cliente por CPF sem carregar tudo]].

## 1. O que o exercício pede

> Receba o arquivo de clientes do Q2 e produza um arquivo binário de índices
> `indices.bin`, onde a sequência dos índices descreve os registros do arquivo de
> clientes **ordenados pelo saldo**.

Ou seja: não é para reordenar `clientes.bin` em si — é para criar um segundo arquivo,
pequeno, que diz **em que ordem** ler os registros de `clientes.bin` para obtê-los do
menor saldo para o maior.

## 2. A ideia geral

Reordenar fisicamente `clientes.bin` seria caro: cada registro tem 5 campos (61 bytes),
e trocar registros de lugar significa mover blocos grandes de disco. A alternativa —
**arquivo de índices** — guarda só números inteiros (4 bytes cada), uma posição por
registro, na ordem desejada. Consultar por ordem de saldo depois é simples: leia
`indices.bin` em sequência e, para cada índice `i` lido, pule direto (`fseek`) até o
registro `i` de `clientes.bin`.

**Por que isso é mais barato:** ordenar um vetor de inteiros (índices) é muito mais rápido
que ordenar registros inteiros — e o arquivo de clientes nunca precisa ser reescrito.

## 3. Resolução passo a passo

### Passo 1 — descobrir quantos registros existem, sem ler nenhum

```c
fseek(fc, 0, SEEK_END);
long bytes = ftell(fc);
rewind(fc);
int n = (int)(bytes / (long)sizeof(Cliente));
```

`ftell` depois de `fseek` até o fim devolve o **tamanho do arquivo em bytes**; dividindo
pelo tamanho de um registro (`sizeof(Cliente)`), obtém-se `n` sem ler um único byte de
dado — só a posição do arquivo é consultada.

### Passo 2 — ler só o saldo de cada registro (não o registro inteiro)

```c
static float saldo[MAXREG];
static int   idx[MAXREG];
Cliente c;
for (int i = 0; i < n; i++) {
    fread(&c, sizeof(Cliente), 1, fc);
    saldo[i] = c.saldo;
    idx[i]   = i;
}
```

> 📖 **Por que ler o registro inteiro (`fread(&c, sizeof(Cliente), ...)`) se só o saldo
> importa?** Porque o arquivo tem registros de tamanho fixo — não dá para "pular" até o
> campo `saldo` sem ler o registro inteiro de uma vez (os campos não são arquivos
> separados). O que se **guarda** depois, em `saldo[i]`, é só o valor — o resto do
> registro (`c.nome`, `c.cpf`...) é descartado a cada iteração, nunca acumulado num vetor
> grande. Isso é o que garante memória O(n) em vez de O(n × sizeof(Cliente)).

`idx[i] = i` inicializa o vetor de índices na ordem original (`0, 1, 2, ..., n-1`) — é
esse vetor que a próxima etapa vai reordenar, nunca os registros em si.

### Passo 3 — ordenar `idx[]`, comparando pelos saldos

```c
for (int i = 1; i < n; i++) {
    int chave = idx[i];
    int j = i - 1;
    while (j >= 0 && saldo[idx[j]] > saldo[chave]) {
        idx[j + 1] = idx[j];
        j--;
    }
    idx[j + 1] = chave;
}
```

> 📖 **Lendo devagar:** é o insertion sort de sempre, mas com uma indireção a mais —
> em vez de comparar `idx[j]` com `chave` diretamente, compara-se `saldo[idx[j]]` com
> `saldo[chave]`. `idx[j]` e `chave` são **posições**; `saldo[idx[j]]` é "o saldo do
> registro que está na posição `idx[j]`". O que se move dentro do laço são as posições
> (`idx[j+1] = idx[j]`), nunca os saldos nem os registros — o vetor `saldo[]` original
> não muda de ordem, só serve de referência para decidir a troca.

**Trace**, com 4 registros e saldos `[1500.00, 300.50, 9800.75, 45.20]` (índices 0–3):

| `i` | `chave = idx[i]` | Comparações (`saldo[idx[j]] > saldo[chave]`?) | `idx[]` depois |
|---|---|---|---|
| início | — | — | `[0, 1, 2, 3]` |
| 1 | `idx[1]=1` (saldo 300.50) | `saldo[0]=1500 > 300.50`? sim → desloca | `[1, 0, 2, 3]` |
| 2 | `idx[2]=2` (saldo 9800.75) | `saldo[0]=1500 > 9800.75`? não → para | `[1, 0, 2, 3]` |
| 3 | `idx[3]=3` (saldo 45.20) | `9800.75>45.20`✔, `1500>45.20`✔, `300.50>45.20`✔ → desloca os 3 | `[3, 1, 0, 2]` |

Resultado: `idx[] = [3, 1, 0, 2]` — registro 3 (saldo 45.20, o menor) primeiro, depois 1
(300.50), depois 0 (1500.00), depois 2 (9800.75, o maior). ✔ Bate com a ordem crescente
de saldo.

### Passo 4 — gravar o vetor de índices

```c
FILE *fi = fopen(arqIndices, "wb");
fwrite(idx, sizeof(int), n, fi);
```

`fwrite` grava os `n` inteiros de `idx[]` de uma vez — `indices.bin` fica com `n × 4`
bytes (em vez dos `n × sizeof(Cliente)` bytes que reordenar `clientes.bin` custaria).

## 4. Resultado final

Lendo `indices.bin` em ordem e usando cada índice para pular (`fseek`) até o registro
correspondente em `clientes.bin`:

```
Clientes por saldo CRESCENTE (via indices.bin):
  indice 3 -> Diego Alves     saldo    45.20
  indice 1 -> Bruno Lima      saldo   300.50
  indice 0 -> Ana Souza       saldo  1500.00
  indice 2 -> Carla Dias      saldo  9800.75
```

**Conferindo:** os saldos impressos estão em ordem estritamente crescente — se algum par
saísse fora de ordem, seria sinal de erro na comparação `saldo[idx[j]] > saldo[chave]`
(por exemplo, usar `<` por engano inverteria a ordem).

## 5. Habilidades necessárias

- [ ] `fseek`/`ftell` para descobrir o tamanho de um arquivo sem ler seu conteúdo → ver
      [[../../../../03 - Arquivos e Ordenação Externa/3.1 Arquivos Binários e Texto/Teoria - passo a passo/Teoria 03 - Acesso aleatório em arquivo binário (fseek, ftell, rewind)|3.1, Teoria 03]].
- [ ] Ordenar por indireção (vetor de índices + vetor de chaves) em vez de ordenar os
      dados diretamente — a mesma ideia por trás de índices de banco de dados reais.
- [ ] Insertion sort — O(n²), aceitável aqui porque só ordena `n` inteiros, não os
      registros inteiros.

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — 2 clientes, já em ordem de saldo

Saldos `[100.00, 200.00]`. `idx` começa `[0,1]`; na única iteração (`i=1`),
`saldo[0]=100 > saldo[1]=200`? Não → nada se move. `idx` final: `[0,1]` (ordem não muda,
porque já estava certa).

### Aquecimento 2 — 2 clientes, ordem invertida

Saldos `[200.00, 100.00]`. `idx` começa `[0,1]`; `i=1`: `saldo[0]=200 > saldo[1]=100`? Sim
→ desloca: `idx = [1, 0]`. Resultado: registro 1 (saldo 100, menor) vem antes do registro
0 — a inversão exatamente esperada.

---

Isso fecha a `Passo a Passo Lista` da lista06-EDA.
