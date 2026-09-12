# Teoria 02 — Hashing extensível (diretório e buckets)

> **Onde isto entra:** primeiro método concreto que aplica a ideia da Teoria 01 (minimizar
> acessos a disco via buckets) — usa uma estrutura auxiliar em RAM (o diretório) pra sempre
> acertar o bucket certo de primeira.
> **Antes:** [[Teoria 01 - Por que memória secundária muda o problema]].
> **Fonte:** SZ (Szwarcfiter) é o livro-base para este método, mas **o PDF não pôde ser
> aberto nesta máquina** (falta ferramenta de renderização) — não há como citar página ou
> exemplo numérico exatos do livro. O exemplo numérico abaixo **é construído para esta
> explicação**, fiel ao mecanismo descrito no `README.md` deste subtópico, mas não é
> retirado literalmente do livro. Confirme contra o livro se for citar em prova.

## 1. A ideia em uma frase

Um **diretório** pequeno, guardado em RAM, aponta diretamente para o **bucket** certo em
disco — de forma que qualquer busca custe no máximo 1 acesso a disco (o bucket), porque o
diretório nunca precisa ser lido do disco (já está em RAM).

## 2. Vocabulário novo, um de cada vez

> 📖 **Lendo devagar:**
> - **Profundidade global (`d`)** — quantos bits do hash da chave o diretório usa para
>   decidir a entrada. Um diretório com profundidade `d` tem `2^d` entradas.
> - **Profundidade local (`d_local`)** de um bucket — quantos bits **esse bucket
>   específico** já usou para se diferenciar de outros. Pode ser **menor** que `d` — nesse
>   caso, **mais de uma entrada do diretório aponta pro mesmo bucket**.
> - **Split (divisão de bucket)** — quando um bucket enche e recebe mais uma chave, ele se
>   divide em dois, cada um com `d_local` uma unidade maior que antes.

## 3. Motivação: por que usar bits do hash, e não o valor direto

Usar **bits** (em vez do valor do hash inteiro) permite crescer **gradualmente**: ao invés
de recalcular tudo com um `m` novo (como no rehashing de 4.1), só se olha **mais um bit** do
mesmo hash já calculado — os bits já usados continuam significando a mesma coisa.

## 4. Conferindo com um exemplo concreto, passo a passo

Bucket com capacidade **2 chaves**. Começamos com profundidade global `d = 1` → diretório
com `2^1 = 2` entradas (`0` e `1`), cada uma apontando para seu próprio bucket, ambos com
`d_local = 1`:

```
Diretório (d=1)          Buckets
0 ──► Bucket "0" (d_local=1): [ ]
1 ──► Bucket "1" (d_local=1): [ ]
```

Vamos inserir chaves cujos **2 bits menos significativos do hash** são, nesta ordem:
`01, 11, 10, 00, 01`.

> **Passo 1 — insere chave com hash `...01`:** olha só o último bit (`d=1`): `1` → vai pro
> Bucket "1". `Bucket "1" = [01]`.
>
> **Passo 2 — insere chave com hash `...11`:** último bit `1` → Bucket "1" de novo.
> `Bucket "1" = [01, 11]` — bucket cheio (capacidade 2), mas ainda sem overflow.
>
> **Passo 3 — insere chave com hash `...10`:** último bit `0` → Bucket "0".
> `Bucket "0" = [10]`.
>
> **Passo 4 — insere chave com hash `...00`:** último bit `0` → Bucket "0" de novo.
> `Bucket "0" = [10, 00]` — cheio também, sem overflow ainda.
>
> **Passo 5 — insere chave com hash `...01`:** último bit `1` → Bucket "1", que **já está
> cheio** com `[01, 11]`. **Overflow!**

### O split

Como o Bucket "1" estourou e `d_local` dele (1) é **igual** a `d` do diretório (1), é
preciso **dobrar o diretório primeiro**:

```
Diretório dobra: d = 1 → 2 (agora 2^2 = 4 entradas: 00, 01, 10, 11)
Cada entrada antiga vira duas: a entrada "0" antiga agora tem "00" e "10" apontando pra ela;
a entrada "1" antiga agora tem "01" e "11".
```

Agora o Bucket "1" (que estourou) é dividido em dois, olhando **mais um bit** (o 2º bit
menos significativo) das chaves que estavam nele: `01` e `11` — como o 2º bit de `01` é `0`
e o de `11` é `1`, elas vão para buckets diferentes:

```
Diretório (d=2)         Buckets
00 ──┐
     ├──► Bucket "0" (d_local=1): [10, 00]      (não mudou — d_local ainda 1 < novo d=2)
10 ──┘
01 ──────► Bucket "01" (d_local=2): [01]        (metade do antigo Bucket "1")
11 ──────► Bucket "11" (d_local=2): [11]        (outra metade)
```

E a 5ª chave (hash `...01`), que causou o overflow, agora encontra a entrada `01` do
diretório apontando pro bucket certo, com espaço livre: `Bucket "01" = [01, 01(nova)]`.

> **O que aconteceu, em uma frase:** o diretório inteiro dobrou de tamanho (custo O(tamanho
> do diretório), mas isso é raro), e **só o bucket que estourou** foi de fato dividido e
> teve suas chaves redistribuídas — o Bucket "0" nem foi tocado, só passou a ser apontado
> por 2 entradas em vez de 1.

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| indexar o diretório pelos `d` bits menos significativos do hash | decido, sem tocar disco, exatamente qual bucket devo ler |
| `d_local < d` num bucket | permito que várias entradas do diretório apontem pro mesmo bucket — ele ainda não precisou se diferenciar por aquele bit extra |
| dobrar o diretório só quando `d_local == d` no bucket que estourou | só pago o custo caro (duplicar o diretório) quando realmente não há mais bit disponível pra diferenciar sem crescer |
| dividir só o bucket que estourou | evito reorganizar a tabela inteira — o custo da divisão é proporcional só ao bucket afetado |

## 6. Letra miúda

**Por que no máximo 2 acessos a disco?** O diretório fica em RAM (não conta como acesso a
disco); o bucket certo é identificado direto pelos bits do hash, sem tentativa e erro — 1
acesso a disco (ler o bucket) resolve a busca. Os "2 acessos" citados às vezes na literatura
contam o caso em que o diretório **também** precisaria ser lido de disco (se fosse grande
demais pra RAM) — na prática mais comum, ele cabe em RAM, e é 1 acesso só.

## 7. Exercícios de fixação

1. No estado final da seção 4, quantas entradas do diretório apontam pro Bucket "0"?
2. Se uma nova chave tiver hash terminando em `...00`, ela cai em qual bucket, no estado
   final?
3. Por que dividir o Bucket "0" (que nunca estourou) seria desnecessário neste momento?
4. O que aconteceria se o Bucket "0" também estourasse agora (`d_local = 1`, `d` do
   diretório já é `2`)? Precisaria dobrar o diretório de novo?

### Gabarito

1. Duas: `00` e `10` (porque `d_local` do Bucket "0" ainda é 1, menor que o novo `d=2`).
2. `...00` → olhando os 2 bits do diretório (`d=2`): entrada `00` → Bucket "0" (`[10, 00]`,
   agora receberia mais uma, estourando esse bucket também).
3. Porque ele não estourou — dividir sem necessidade gastaria esforço à toa e não resolve
   nenhum problema real (a estrutura só divide **o bucket que estourou**).
4. Não precisaria dobrar de novo: `d_local` do Bucket "0" (1) é **menor** que `d` do
   diretório (2) — ainda há "bit sobrando" no diretório atual para diferenciar. Bastaria
   dividir o Bucket "0" usando o 2º bit (como já foi feito pro Bucket "1"), sem duplicar o
   diretório outra vez.

## Resumo

- Diretório em RAM, indexado pelos `d` bits menos significativos do hash, aponta direto
  pro bucket certo — busca custa tipicamente 1 acesso a disco.
- `d_local` de um bucket pode ser menor que `d` do diretório — várias entradas podem
  compartilhar o mesmo bucket.
- Overflow dispara split do bucket; **só** dobra o diretório inteiro quando o bucket que
  estourou já usa todos os bits disponíveis (`d_local == d`).

**Próximo:** [[Teoria 03 - Hashing linear (crescimento sem diretório)]].
