# Teoria 04 — Build-heap (por que é O(n)), inserção, extração, e heapsort

> **Onde isto entra:** fecha 6.1 juntando tudo: como montar um heap do zero a partir de um
> array qualquer, como inserir/remover mantendo a propriedade, e como isso vira um
> algoritmo de ordenação completo.
> **Antes:** [[Teoria 03 - Heapify-down e heapify-up]].
> **Fonte:** CO (Cormen), cap. 6, `BUILD-MAX-HEAP` e `HEAPSORT` — conferir página exata
> (PDF não abre nesta máquina); é a pegadinha de prova mais clássica do capítulo.

## 1. A ideia em uma frase

`Build-heap` transforma um array qualquer (sem nenhuma garantia) num heap válido, aplicando
`heapify_down` de trás para frente — e, apesar de parecer que isso custa O(n log n), a
análise correta mostra que custa **O(n)**.

## 2. Inserção e extração (rápido, já visto na Teoria 03 em ação)

- **Inserir(x):** `dados[tamanho] = x; tamanho++; heapify_up(tamanho-1);` — bota no fim,
  sobe até o lugar certo. O(log n).
- **Extrair-máximo():** guarda `dados[0]`, move o **último** elemento para a raiz
  (`dados[0] = dados[tamanho-1]`), diminui `tamanho`, roda `heapify_down(0)`. O(log n).

> **Por que mover o último para a raiz, e não simplesmente "remover" a raiz?** Um array não
> tem como ter um buraco no meio e continuar completo (Teoria 02) — a única posição que dá
> pra encolher sem deixar buraco é a **última**. Por isso o valor que sobra vai para o topo
> (única posição vaga) e o heapify-down resolve a violação que isso quase certamente causa.

### Conferindo com trace (inserindo 5, 3, 8, 1, 4 num max-heap vazio)

| Inserção | Array após colocar no final | Sift-up | Array final |
|---|---|---|---|
| insere 5 | `[5]` | é a raiz, nada a fazer | `[5]` |
| insere 3 | `[5, 3]` | pai(1)=0, `dados[0]=5 ≥ 3` → nada | `[5, 3]` |
| insere 8 | `[5, 3, 8]` | pai(2)=0, `dados[0]=5 < 8` → troca | `[8, 3, 5]` |
| insere 1 | `[8, 3, 5, 1]` | pai(3)=1, `dados[1]=3 ≥ 1` → nada | `[8, 3, 5, 1]` |
| insere 4 | `[8, 3, 5, 1, 4]` | pai(4)=1, `dados[1]=3 < 4` → troca; pai(1)=0, `dados[0]=8 ≥ 4` → para | `[8, 4, 5, 1, 3]` |

Agora uma **extração**: guarda `dados[0]=8` (resultado), move o último (`3`) para a raiz e
encolhe: `[3, 4, 5, 1]`. `heapify_down(0)`: filhos `4`(idx1) e `5`(idx2), maior é `5` →
troca: `[5, 4, 3, 1]`; recursão em `i=2`: `filho_esq(2)=5`, fora do array (`n=4`) → para.
Extraído: `8`; heap resultante: `[5, 4, 3, 1]`.

## 3. Build-heap — o código

```c
BUILD-MAX-HEAP(A, n):
    para i de floor(n/2)-1 até 0:
        MAX-HEAPIFY(A, i, n)
```

> 📖 **Lendo devagar:** por que começar em `floor(n/2)-1` e não em `n-1` (o último
> índice)? Porque todo índice **a partir de** `floor(n/2)` é folha (não tem filho dentro do
> array — confira com a fórmula `filho_esq(i) = 2i+1 ≥ n`) — e `heapify_down` numa folha
> não faz nada (não tem filho pra comparar). Rodar nas folhas seria trabalho perdido; o
> código pula direto para o **último nó que tem filho**, e vai voltando em direção à raiz.

### Conferindo com um array pequeno

Array de entrada (sem ordem nenhuma): `[1, 5, 3, 8, 2]` (índices 0 a 4, `n=5`).

`floor(5/2) - 1 = 2 - 1 = 1` → o laço roda `i = 1` e depois `i = 0`.

1. `heapify_down(A, 1, 5)`: nó índice 1 (valor `5`). Filhos: idx3 (`8`), idx4 (`2`). Maior é
   `8` (idx3). `8 > 5` → troca: `[1, 8, 3, 5, 2]`. Recursão em `i=3`: sem filhos
   (`filho_esq(3)=7 ≥ 5`) → para.
2. `heapify_down(A, 0, 5)`: nó índice 0 (valor `1`). Filhos: idx1 (`8`), idx2 (`3`). Maior é
   `8` (idx1). `8 > 1` → troca: `[8, 1, 3, 5, 2]`. Recursão em `i=1`: filhos idx3 (`5`),
   idx4 (`2`). Maior é `5` (idx3). `5 > 1` → troca: `[8, 5, 3, 1, 2]`. Recursão em `i=3`:
   sem filhos → para.

Resultado: `[8, 5, 3, 1, 2]` — confira: `8≥5`, `8≥3`, `5≥1`, `5≥2` — max-heap válido, ✔.

## 4. A pegadinha de prova: por que build-heap é O(n), não O(n log n)

**Raciocínio ingênuo (errado, mas tentador):** "o laço roda ~n/2 vezes, cada `heapify_down`
custa O(log n) → total O(n log n)".

**O que esse raciocínio erra:** ele assume que **toda** chamada de `heapify_down` custa o
máximo (O(log n)) — mas isso só é verdade para nós **perto da raiz**. A maioria absoluta
dos nós de uma árvore está **perto das folhas**, onde `heapify_down` desce pouquíssimos
níveis (uma folha custa O(1); um nó a 1 nível da folha custa no máximo O(1) também, etc.).

**Contando certo:** numa árvore de altura `h = log n`, existem no máximo `n/2^(k+1)` nós no
nível `k` contando a partir das folhas — e cada um desses custa O(k) no pior caso. Somando:

```
custo total ≤ Σ (k=0 até h) [ n / 2^(k+1) ] · O(k)  =  O(n) · Σ (k=0 até h) k/2^k
```

A série `Σ k/2^k` (para `k` de 0 até infinito) **converge para uma constante** (o valor é
2) — não cresce com `n`. Então o custo total é `O(n) · constante = O(n)`.

> 📖 **A intuição, em uma frase:** a maioria dos nós está barata (perto da folha) e só uma
> minoria está cara (perto da raiz) — a soma pesada pela quantidade de nós em cada faixa de
> custo dá linear, não `n vezes o pior custo individual`.

## 5. Heapsort — juntando tudo

```c
HEAPSORT(A, n):
    BUILD-MAX-HEAP(A, n)
    para i de n-1 até 1:
        troca A[0], A[i]
        MAX-HEAPIFY(A, 0, i)   // heap "encolhe": só olha até o índice i-1 daqui pra frente
```

> 📖 **Lendo devagar:** depois de `BUILD-MAX-HEAP`, `A[0]` é o maior elemento. `troca A[0],
> A[i]` bota esse maior na **posição final correta** (o fim do array, que a cada volta do
> laço encolhe um a um) — e o valor que estava no fim (provavelmente pequeno) vai para a
> raiz, exigindo `MAX-HEAPIFY` para restaurar a propriedade **só dentro da parte ainda não
> ordenada** (por isso o heapify usa `i`, não `n`, como limite).

**Complexidade total:** O(n) do build-heap + `n` chamadas de heapify a O(log n) cada =
**O(n log n)**, sempre — não depende de melhor/pior/médio caso, é determinístico (diferente
de quicksort). É in-place, mas **não é estável** (a troca pode reordenar elementos iguais).

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| começar o build-heap em `floor(n/2)-1`, não em `n-1` | pulo o trabalho inútil de rodar heapify em folhas, que nunca fazem nada |
| a soma `Σ k/2^k` convergir | a maior parte da "massa" de nós está onde o heapify é barato — o custo médio por nó é constante, não log n |
| trocar `A[0]` com `A[i]` a cada volta de heapsort | uso a raiz do heap (sempre o maior dos restantes) para preencher o array **de trás para frente**, uma posição definitiva por vez |

## 7. Exercícios de fixação

1. Rode `BUILD-MAX-HEAP` no array `[4, 1, 9, 2, 6]` (mostre cada `heapify_down` chamado).
2. Quantos elementos, no máximo, custam O(log n) de fato numa `BUILD-MAX-HEAP` de um heap
   com `n = 16`? (Dica: são os nós perto da raiz — quantos existem no nível mais alto?)
3. Depois de montar o max-heap `[9, 6, 8, 1, 2]`, rode as duas primeiras trocas de
   `HEAPSORT` (mostre o array após cada troca + heapify).

### Gabarito

1. `n=5`, `floor(5/2)-1 = 1`. `i=1` (valor `1`): filhos idx3(`2`), idx4(`6`); maior `6`
   (idx4) → troca: `[4, 6, 9, 2, 1]`; recursão em idx4, sem filhos, para. `i=0` (valor
   `4`): filhos idx1(`6`), idx2(`9`); maior `9` (idx2) → troca: `[9, 6, 4, 2, 1]`; recursão
   em `i=2`: sem filhos (`filho_esq(2)=5 ≥ 5`) → para. Resultado: `[9, 6, 4, 2, 1]`.
2. No nível mais alto (nível 0, só a raiz), existe **1** nó, e ele é o único que pode
   custar o pior caso O(log n) completo (altura total da árvore). Todos os outros custam
   menos que isso — é exatamente por isso que a soma não vira `n · O(log n)`.
3. Array `[9, 6, 8, 1, 2]`, `n=5`. **Volta 1:** troca `A[0]` com `A[4]`: `[2, 6, 8, 1, 9]`;
   `MAX-HEAPIFY(A, 0, 4)` (olhando só até índice 3 agora): filhos idx1(`6`), idx2(`8`);
   maior `8` → troca: `[8, 6, 2, 1, 9]`; recursão em idx2: sem filhos dentro do limite 4 →
   para. **Volta 2:** troca `A[0]` com `A[3]`: `[1, 6, 2, 8, 9]`; `MAX-HEAPIFY(A, 0, 3)`
   (limite agora 3): filhos idx1(`6`), idx2(`2`); maior `6` → troca: `[6, 1, 2, 8, 9]`;
   recursão em idx1: sem filhos dentro do limite 3 → para.

## Resumo

- Inserir: bota no fim + heapify-up, O(log n). Extrair: raiz vira resultado, último
  elemento sobe pra raiz + heapify-down, O(log n).
- Build-heap roda heapify-down de trás pra frente, começando no último nó **com filho**
  (pula folhas) — análise correta dá **O(n)**, não O(n log n) (a maioria dos nós está perto
  da folha, onde heapify é barato).
- Heapsort = build-heap + n extrações "manuais" trocando com o fim do array — O(n log n)
  sempre, in-place, não estável.

---

Isso fecha a teoria de 6.1. Próximo: [[../../6.2 Heaps em Memória Secundária/README|6.2 Heaps em Memória Secundária]].
