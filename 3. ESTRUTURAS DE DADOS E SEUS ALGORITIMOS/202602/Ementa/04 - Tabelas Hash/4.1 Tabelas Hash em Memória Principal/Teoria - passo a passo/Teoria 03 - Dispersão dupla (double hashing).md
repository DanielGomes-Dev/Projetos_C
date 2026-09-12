# Teoria 03 — Dispersão dupla (double hashing)

> **Onde isto entra:** resolve diretamente o problema de clustering primário visto na
> Teoria 02.
> **Antes:** [[Teoria 02 - Colisões — tratamento por posição livre (endereçamento aberto)]].
> **Fonte:** CE (Celes), Cap. 18 "Tabelas de dispersão", pág. 277.

## 1. A ideia em uma frase

Em vez de sempre andar de 1 em 1 posição ao colidir, usa-se **uma segunda função hash**
para decidir de quanto em quanto pular — chaves diferentes passam a ter passos de busca
diferentes, o que evita que elas se acumulem sempre no mesmo cluster.

## 2. Por que isso resolve o problema da Teoria 02

Na Teoria 02, toda chave que colidia avançava **sempre +1** — por isso, uma vez que um
cluster começava a crescer, ele "engolia" qualquer chave que tentasse passar perto, mesmo
sem relação nenhuma com as chaves originais do cluster. Se o **tamanho do passo** depender
da própria chave (via uma segunda função hash), cada chave "pula" a tabela de um jeito
diferente — dificultando que clusters grandes se formem.

## 3. A segunda função hash — lida devagar

```c
static int hash2(int mat) {
  return N - 2 - mat % (N - 2);
}
```

> 📖 **Lendo devagar:**
> 1. `mat % (N - 2)` — resto da divisão por `N - 2` (não por `N`!) — é a primeira parte do
>    truque: usar um módulo **diferente** do da primeira função hash.
> 2. `N - 2 - (...)` — inverte o resultado, num intervalo que garante duas coisas
>    importantes (ver a letra miúda abaixo).

**A fórmula geral de sondagem passa a ser:**
```
h(x, i) = (h(x) + i · h'(x)) mod N
```
em vez de `(h(x) + i) mod N` (que era, na prática, `h'(x) = 1` sempre, na Teoria 02).

## 4. Letra miúda: por que essa fórmula específica para `hash2`

O livro exige dois cuidados na escolha de `h'`:

1. **`h'(x)` nunca pode ser 0** — se fosse, o índice nunca avançaria, e a busca ficaria
   presa para sempre na mesma posição. A fórmula `N - 2 - mat%(N-2)` garante isso porque
   `mat % (N-2)` está sempre entre `0` e `N-3`, então `N - 2 - (...)` está sempre entre `2`
   e `N-2` — nunca zero.
2. **De preferência, `h'(x)` não deve ser divisor de `N`** — se fosse, os saltos ficariam
   presos visitando só um subconjunto fixo de posições (ex.: só as pares, se `N` for par e
   `h'` for par), nunca alcançando o resto da tabela. Escolher `N` **primo** garante
   automaticamente que nenhum número menor que `N` é divisor dele — é o mesmo motivo de
   `N = 127` (primo) ter sido escolhido lá na Teoria 02.

## 5. O código de busca — só muda o incremento

```c
Aluno *hsh_busca(Hash tab, int mat) {
  int h = hash(mat);
  int h2 = hash2(mat);
  while (tab[h] != NULL) {
    if (tab[h]->mat == mat)
      return tab[h];
    h = (h + h2) % N;
  }
  return NULL;
}
```

> 📖 **Comparando com a Teoria 02:** a única mudança é a linha `h = (h + h2) % N` no lugar
> de `h = (h + 1) % N`. `h2` é calculado **uma vez**, no início, a partir da própria chave
> `mat` — e usado em todo avanço subsequente **desta busca específica**. Chaves diferentes
> terão `h2` diferente, logo trilhas de sondagem diferentes.

## 6. Conferindo com números concretos

`N = 7` (pequeno, para caber no papel — o livro usa `N=127`, mas a lógica é a mesma).
`hash(k) = k % 7`; `hash2(k) = N - 2 - k%(N-2) = 5 - k%5`.

Inserindo `10` e depois `24` (que colidem: `10 % 7 = 3`, `24 % 7 = 3`):

- `hash2(10) = 5 - (10%5) = 5 - 0 = 5`.
- `hash2(24) = 5 - (24%5) = 5 - 4 = 1`.

Ambas colidem na posição de origem `3`, mas **avançam de forma diferente** se precisarem
sondar mais: `10` pularia de 5 em 5 (`3 → (3+5)%7=1 → (1+5)%7=6 → ...`), enquanto `24`
pularia de 1 em 1 a partir dali (`3 → (3+1)%7=4 → 5 → ...`) — trilhas diferentes, o que
evita que as duas fiquem "grudadas" no mesmo padrão de avanço, ao contrário do que
aconteceria com incremento fixo de +1 para ambas.

## 7. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| calcular `h2` uma vez, no início da busca/inserção | decido, a partir da própria chave, "de quanto em quanto" ela vai pular se colidir — antes mesmo de saber se vai colidir |
| escolher `N` primo | garanto que `h2` nunca vai "prender" a sondagem num subconjunto pequeno de posições |
| `h = (h + h2) % N` no lugar de `h = (h+1) % N` | troco um passo universal (igual pra todo mundo) por um passo específico da chave — é isso que quebra o clustering primário |

## 8. Exercícios de fixação

1. Calcule `hash2(17)` com `N = 7` (fórmula: `5 - k%5`).
2. Duas chaves com o mesmo `hash2` ainda podem sofrer clustering entre si (clustering
   *secundário*) — por quê, mesmo com dispersão dupla?
3. Por que a fórmula usa `N - 2` no módulo, em vez de `N` direto?

### Gabarito

1. `hash2(17) = 5 - (17%5) = 5 - 2 = 3`.
2. Porque, apesar de `h2` variar entre chaves diferentes, duas chaves que **por acaso**
   têm o mesmo `hash(x)` **e** o mesmo `hash2(x)` ainda seguem exatamente a mesma trilha de
   sondagem uma atrás da outra — double hashing reduz drasticamente a chance disso (já que
   agora são duas condições coincidindo, não uma só), mas não a elimina 100%.
3. Porque o próprio `hash2` usa `N` como o "circuito" da tabela (via `% N` na busca); usar
   `N` também dentro do cálculo de `hash2` arriscaria criar dependências indesejadas entre
   as duas funções. Usar `N - 2` como módulo da segunda função é a escolha do livro para
   manter as duas funções "independentes" o suficiente.

## Resumo

- Dispersão dupla: o passo de sondagem, ao colidir, depende da própria chave via uma
  segunda função hash `h2(x)`, calculada uma vez por busca/inserção.
- `h2(x)` nunca pode ser 0 (senão trava) e, de preferência, não deve ser divisor de `N`
  (senão restringe as posições alcançáveis) — `N` primo resolve os dois cuidados de uma vez.
- Reduz (não elimina) o clustering primário, porque chaves diferentes seguem trilhas de
  sondagem diferentes.

**Próximo:** [[Teoria 04 - Encadeamento separado (listas ligadas nos buckets)]].
