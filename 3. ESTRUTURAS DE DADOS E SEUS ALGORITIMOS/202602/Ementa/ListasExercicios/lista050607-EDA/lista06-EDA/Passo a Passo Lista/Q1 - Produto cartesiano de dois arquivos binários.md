# Q1 — Produto cartesiano de dois arquivos binários

> **Origem:** `lista06-EDA.pdf`, questão 1 · **Código resolvido:** [[../Q1/claude/main.c]]
> **Antes disto, veja:** [[../../../../03 - Arquivos e Ordenação Externa/3.1 Arquivos Binários e Texto/Teoria - passo a passo/Teoria 03 - Acesso aleatório em arquivo binário (fseek, ftell, rewind)|3.1, Teoria 03]] (`rewind`).

## 1. O que o exercício pede

> Leia dois arquivos binários `a.bin` e `b.bin` com palavras de 10 caracteres e produza
> `c.bin`, onde cada registro é um par (palavra de `a.bin`, palavra de `b.bin`) — todos os
> pares possíveis (produto cartesiano). Todo o processamento deve ser em **memória
> secundária**.

"Memória secundária" é a restrição central: não pode carregar `a.bin`/`b.bin` inteiros em
vetores na RAM — só um registro de cada por vez.

## 2. A ideia geral

É literalmente dois laços aninhados, só que em vez de percorrer arrays em RAM, cada
iteração é uma **leitura de disco**. O laço externo anda uma vez por `a.bin`; para cada
palavra de `a.bin`, o laço interno percorre `b.bin` **inteiro de novo**, do começo — daí a
necessidade de `rewind`.

## 3. Resolução passo a passo

### Passo 1 — modelagem dos registros

```c
#define TAM_PALAVRA 10
```

`a.bin`/`b.bin`: blocos de 10 bytes cada (sem garantia de `'\0'` — são bytes crus, não
strings C terminadas). `c.bin`: blocos de 20 bytes = palavra de `a` + palavra de `b`
concatenadas.

### Passo 2 — os dois laços

```c
while (fread(pa, TAM_PALAVRA, 1, fa) == 1) {   // laço externo: cada palavra de A
    rewind(fb);                                  // volta B pro início — de novo!
    while (fread(pb, TAM_PALAVRA, 1, fb) == 1) {  // laço interno: cada palavra de B
        fwrite(pa, TAM_PALAVRA, 1, fc);
        fwrite(pb, TAM_PALAVRA, 1, fc);
    }
}
```

> 📖 **Por que `rewind(fb)` é a linha-chave:** sem ela, na segunda volta do laço externo, o
> cursor de `fb` já estaria no fim (esgotado pela primeira passada) — o laço interno nunca
> entraria de novo. `rewind` é o que permite "reler B do zero" para cada nova palavra de A.

**Trace com `A = {casa, sol, rua}` (3 palavras), `B = {gato, peixe}` (2 palavras):**

| `pa` (laço externo) | `rewind(fb)` | `pb` percorrido (laço interno) | Pares escritos |
|---|---|---|---|
| casa | sim | gato, peixe | (casa,gato), (casa,peixe) |
| sol | sim | gato, peixe | (sol,gato), (sol,peixe) |
| rua | sim | gato, peixe | (rua,gato), (rua,peixe) |

Total: `3 × 2 = 6` pares — exatamente `|A| × |B|`.

## 4. Resultado final

`c.bin` com 6 registros de 20 bytes cada, contendo todos os pares (casa,gato), (casa,peixe),
(sol,gato), (sol,peixe), (rua,gato), (rua,peixe).

**Conferindo:** o número de registros em `c.bin` deve ser sempre `|A| × |B|` — se vier
diferente, ou o `rewind` está faltando, ou um dos `fread`/`fwrite` está com tamanho errado.

## 5. Habilidades necessárias

- [ ] `rewind` (voltar o cursor ao início) → [[../../../../03 - Arquivos e Ordenação Externa/3.1 Arquivos Binários e Texto/Teoria - passo a passo/Teoria 03 - Acesso aleatório em arquivo binário (fseek, ftell, rewind)|3.1, Teoria 03]]
- [ ] Registro de tamanho fixo sem terminador (`char[10]` cru, não string C).

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — 1 palavra em cada arquivo

`A = {x}`, `B = {y}`. Só uma iteração de cada laço → 1 par: `(x, y)`.

### Aquecimento 2 — A com 2, B com 1

`A = {x, y}`, `B = {z}`. Laço externo roda 2 vezes, cada uma com `rewind` + 1 iteração do
laço interno → pares `(x,z)`, `(y,z)` — 2 registros, `2 × 1 = 2`. ✔
