# Teoria 03 — Acesso aleatório em arquivo binário: fseek, ftell, rewind

> **Onde isto entra:** até aqui, ler um arquivo binário era sempre sequencial (do começo
> até onde o cursor estiver). Aqui vemos como **pular direto** para qualquer posição — é o
> que permite tratar um arquivo em disco quase como um array, sem carregar tudo pra RAM.
> **Antes:** [[Teoria 02 - Stream, cursor, buffer e as duas famílias de funções de E-S]].
> **Fonte:** `10_Arquivos_binarios.pdf`, págs. 5–6 (slides da disciplina) — a mesma lógica
> de busca binária em disco aparece em `lista07-EDA` (ordenação em arquivo binário).

## 1. A ideia em uma frase

`fseek` move o cursor para **qualquer posição**, não só "a próxima" — isso transforma um
arquivo binário de registros de tamanho fixo num array que mora em disco, acessável por
índice.

## 2. Por que isso é necessário (motivação)

`fread`/`fwrite` sozinhos só avançam o cursor pra frente, sequencialmente. Mas muitos
problemas precisam de acesso **direto** — por exemplo, buscar um valor num arquivo grande
sem ler tudo (o exemplo do PDF, seção 3). Sem `fseek`, a única opção seria ler do início até
achar (O(n) obrigatório). Com `fseek`, dá pra fazer busca binária **em disco**, exigindo só
O(log n) acessos.

## 3. As três funções — lidas devagar

```c
int fseek(FILE *fp, long int offset, int CTE_ORIGEM);
```

> 📖 **Lendo `fseek` devagar:**
> 1. `fp` — o stream.
> 2. `offset` — quantos bytes mover.
> 3. `CTE_ORIGEM` — **a partir de onde** contar esse deslocamento: `SEEK_SET` (início do
>    arquivo, byte 0), `SEEK_CUR` (posição atual do cursor), `SEEK_END` (fim do arquivo).
> 4. Resultado: cursor vai para a posição `offset` bytes **depois** da origem escolhida.
> 5. Retorno `0` = deu certo; ≠ `0` = erro.

```c
long int ftell(FILE *fp);      // pergunta: "cursor está em que posição (em bytes)?"
void rewind(FILE *fp);          // atalho para fseek(fp, 0L, SEEK_SET) — volta ao início
```

## 4. Conferindo com número: por que a posição precisa ser múltiplo do tamanho do registro

Um arquivo binário guarda `int`s (4 bytes cada): `[10, 20, 30, 40, 50]`. As posições em
**bytes** de cada elemento são: `10`→byte 0, `20`→byte 4, `30`→byte 8, `40`→byte 12,
`50`→byte 16 (cada posição = índice × 4).

**Se eu quiser ler o elemento de índice 2 (`30`)**, preciso de
`fseek(fp, 2 * sizeof(int), SEEK_SET)` = `fseek(fp, 8, SEEK_SET)`, **não** `fseek(fp, 2,
SEEK_SET)` — pular só 2 bytes cairia **no meio** de um registro, lendo lixo (metade de `10`
e metade de `20`).

## 5. O exemplo do PDF: busca binária num arquivo binário

```c
int bb(FILE *fp, int elem, int tipo) {
  int ini, fim, meio, elem_meio;
  ini = ftell(fp);
  fseek(fp, 0L, SEEK_END);
  fim = ftell(fp) - tipo;
  while (ini <= fim) {
    meio = (fim + ini) / 2;
    if ((meio % tipo) != 0) meio = prox_mult(meio, tipo);   // arredonda pro início de um registro
    fseek(fp, meio, SEEK_SET);
    fread(&elem_meio, tipo, 1, fp);
    if (elem_meio == elem) return meio;
    if (elem_meio < elem) ini = meio + tipo;
    if (elem_meio > elem) fim = meio - tipo;
  }
  return -1;
}
```

> 📖 **Lendo devagar:**
> 1. `ini = ftell(fp)` — início da busca é onde o cursor já estava (normalmente 0).
> 2. `fseek(fp, 0L, SEEK_END); fim = ftell(fp) - tipo;` — descobre o **tamanho do arquivo em
>    bytes** indo até o fim, e subtrai `tipo` (o tamanho de um registro) para achar a
>    posição do **último** elemento (não a posição "depois do fim").
> 3. `meio = (fim + ini) / 2` — mesma ideia de busca binária em array, mas em **bytes**, não
>    em índices.
> 4. `if ((meio % tipo) != 0) meio = prox_mult(meio, tipo);` — como `meio` é uma posição em
>    bytes, a divisão por 2 pode cair **no meio** de um registro; esta linha corrige,
>    avançando para o próximo múltiplo de `tipo` (início de registro válido).
> 5. `fseek` + `fread` — pula direto para a posição `meio` e lê **só aquele** registro (não
>    lê nada além disso).
> 6. Resto da lógica é busca binária comum: compara, ajusta `ini` ou `fim` **em bytes**
>    (soma/subtrai `tipo`, não `1`, porque "andar uma posição" aqui significa "andar um
>    registro inteiro").

### Trace concreto

Arquivo com `int`s `[5, 12, 18, 27, 40]` (tipo = 4 bytes), buscando `27`:

| Passo | `ini` (bytes) | `fim` (bytes) | `meio` (bytes) | elemento lido | decisão |
|---|---|---|---|---|---|
| 1 | 0 | 16 | 8 | `18` | `18 < 27` → `ini = 8+4 = 12` |
| 2 | 12 | 16 | 14→**16** (arredonda pro múltiplo de 4) | `40` | `40 > 27` → `fim = 16-4 = 12` |
| 3 | 12 | 12 | 12 | `27` | **achou!** retorna `12` |

(Posição `12` em bytes ÷ 4 = índice 3 — de fato `27` é o 4º elemento, índice 3.)

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `fseek(fp, meio, SEEK_SET)` antes de cada `fread` | pulo direto pro registro que quero, sem ler nada antes dele — é o que torna a busca O(log n) em vez de O(n) |
| trabalhar em "bytes" em vez de "índice" | preciso converter posição lógica (3º elemento) em posição física (byte 12) multiplicando por `sizeof(tipo)` |
| `prox_mult` arredondando `meio` | garanto que nunca leio "meio registro" — sempre alinho no início de um registro válido |

## 7. Exercícios de fixação

1. Um arquivo binário de `int`s com 6 elementos. Qual o byte inicial do elemento de índice 4?
2. Por que `fseek(fp, 2, SEEK_SET)` seria um erro grave num arquivo de `int`s (4 bytes cada)?
3. No trace da seção 5, por que o passo 2 teve que "arredondar" `meio` de 14 para 16?

### Gabarito

1. `4 × sizeof(int) = 4 × 4 = 16`.
2. Porque byte 2 cai **no meio** do primeiro `int` (que ocupa bytes 0–3) — `fread` leria uma
   mistura de metade de dois registros diferentes, um valor sem sentido.
3. Porque `14` não é múltiplo de `4` (tamanho do registro) — leria metade do registro em
   posição 12 e metade do de posição 16. `prox_mult` avança para o próximo múltiplo válido.

## Resumo

- `fseek(fp, offset, ORIGEM)` mexe o cursor para qualquer posição; `ftell` pergunta onde ele
  está; `rewind` volta ao início.
- Em arquivo de registros de tamanho fixo, toda posição válida é **múltiplo do tamanho do
  registro** — nunca aponte para o meio de um registro.
- Acesso aleatório (`fseek`) é o que permite tratar um arquivo binário como um array em
  disco — base para os algoritmos de ordenação externa dos próximos subtópicos (3.2, 3.3).

**Próximo:** [[../../3.2 Geração de Partições Classificadas/README|3.2 Geração de Partições Classificadas]].
