# Q1 — Remover palavras consecutivas repetidas

> **Origem:** `lista05-EDA.pdf`, questão 1 · **Código resolvido:** [[../Q1/claude/main.c]]
> **Antes disto, veja:** [[../../../../03 - Arquivos e Ordenação Externa/3.1 Arquivos Binários e Texto/Teoria - passo a passo/README|3.1 Arquivos Binários e Texto]] (leitura/escrita de arquivo texto em C).

## 1. O que o exercício pede

> Desenvolva um procedimento que receba o nome de um arquivo texto e retire deste texto
> palavras consecutivas repetidas, gravando o resultado no arquivo de saída —
> `void RetRepet(char *ArqEnt, char *ArqSaida)`.

Ou seja: ler um texto palavra por palavra, e sempre que uma palavra for **igual à anterior**
(a que já foi escrita), pular ela — só a primeira ocorrência de cada "sequência de repetição"
sobrevive.

## 2. A ideia geral

Isso é um problema de **percorrer uma sequência lembrando só o último elemento** — não
precisa guardar o texto inteiro em memória, só a última palavra escrita, para comparar com
a próxima. É o mesmo padrão de "cursor" que 3.1 (Teoria 02) descreve: uma passada única,
O(1) de memória extra (fora os dois buffers de palavra).

**Por que `fscanf(fp, "%s", buf)` resolve a tokenização de graça:** o especificador `%s` já
pula automaticamente espaços, tabs e quebras de linha, e para no próximo espaço em branco —
então cada "palavra" (inclusive um `.` isolado) sai pronta, sem precisar separar manualmente
por espaço.

## 3. Resolução passo a passo

### Passo 1 — abrir os dois arquivos

```c
FILE *fe = fopen(ArqEnt, "r");
FILE *fs = fopen(ArqSaida, "w");
```

Um em modo leitura texto (`"r"`), outro em escrita texto (`"w"`) — dois streams
independentes e simultaneamente abertos (ver 3.1, Teoria 02, sobre por que cada modo existe).

### Passo 2 — ler palavra por palavra, comparando com a anterior

```c
char anterior[MAXPAL] = "";     // vazio no início: garante que a 1ª palavra nunca "repete"
while (fscanf(fe, "%255s", atual) == 1) {
    if (primeira) {
        fputs(atual, fs);
        primeira = 0;
    } else if (strcmp(atual, anterior) != 0) {
        fputc(' ', fs);
        fputs(atual, fs);
    }
    if (strcmp(atual, anterior) != 0)
        strcpy(anterior, atual);
}
```

**Tabela de trace**, para a entrada `"texto texto repetido repetido repetido"`:

| Iteração | `atual` | `anterior` (antes) | Igual? | Escreve? | `anterior` (depois) |
|---|---|---|---|---|---|
| 1 | texto | "" (vazio) | não | sim (1ª palavra) | texto |
| 2 | texto | texto | **sim** | **não** | texto (sem mudar) |
| 3 | repetido | texto | não | sim | repetido |
| 4 | repetido | repetido | **sim** | **não** | repetido |
| 5 | repetido | repetido | **sim** | **não** | repetido |

Saída acumulada: `texto repetido` — as 4 repetições consecutivas viraram 1 palavra escrita.

### Passo 3 — a pegadinha documentada no próprio código

O comentário do código (linhas 22–27) aponta uma inconsistência real no enunciado: no
exemplo dado, `"um um"` no final **deveria** colapsar para `"um"` pela regra "remove
repetição consecutiva" — mas o gabarito do PDF mantém `"um um"`. A solução implementada
segue a **regra coerente** (colapsar sempre), divergindo do exemplo só nesse ponto
específico — e documenta isso explicitamente, em vez de silenciosamente reproduzir uma
inconsistência do enunciado.

## 4. Resultado final

Para a entrada completa do enunciado, a saída (com a regra coerente) é:
```
Isto e um texto repetido . Com as repeticoes fica sem sentido . Sem elas melhora um pouco .
```
(divergindo do gabarito do PDF só no "um um" → "um", pelo motivo explicado acima).

**Conferindo:** nenhuma palavra na saída é igual à que vem logo antes dela — a invariante
que o algoritmo garante.

## 5. Habilidades necessárias

- [ ] Leitura de arquivo texto token a token (`fscanf` com `%s`) → [[../../../../03 - Arquivos e Ordenação Externa/3.1 Arquivos Binários e Texto/Teoria - passo a passo/Teoria 02 - Stream, cursor, buffer e as duas famílias de funções de E-S|3.1, Teoria 02]]
- [ ] Comparação de strings (`strcmp`) e cópia (`strcpy`) — revisar KR se necessário.

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — duas palavras repetidas

Entrada: `"a a b"`. Trace: `a` (1ª, escreve) → `a` (igual à anterior, pula) → `b` (diferente,
escreve). Saída: `"a b"`.

### Aquecimento 2 — sem nenhuma repetição

Entrada: `"a b c"`. Nenhuma palavra é igual à anterior — saída idêntica à entrada: `"a b c"`.
