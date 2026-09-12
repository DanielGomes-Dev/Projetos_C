# Teoria 02 — Representando um heap em array, sem ponteiro nenhum

> **Onde isto entra:** heap é a primeira estrutura em árvore do curso guardada **sem**
> `struct`/ponteiro — é um array puro. Entender por que isso funciona depende de uma ideia
> já vista em 1.1.
> **Antes:** [[Teoria 01 - Propriedade de heap (min-heap e max-heap)]] ·
> [[../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 06 - Tipos de árvore binária (cheia, completa, perfeita)|1.1 Teoria 06]].
> **Fonte:** CO (Cormen), cap. 6; SZ — conferir página exata (PDF não abre nesta máquina).

## 1. A ideia em uma frase

Um heap é sempre uma árvore **completa** (Teoria 06 de 1.1: níveis cheios, exceto o
último, preenchido da esquerda pra direita, sem buraco) — e é exatamente essa garantia de
"sem buraco" que permite guardar a árvore inteira num array, calculando a posição de
qualquer pai/filho **por aritmética de índice**, sem precisar de ponteiro nenhum.

## 2. De onde vem a necessidade

Em 1.1 (Teoria 03), uma árvore binária qualquer precisa de ponteiro `esq`/`dir` porque um
nó pode ter filho só de um lado, ou nenhum, em qualquer posição — não tem como "adivinhar"
onde os filhos estão. Numa árvore **completa**, essa incerteza desaparece: a posição de
cada nó, contando em largura (nível a nível, esquerda pra direita), determina sozinha onde
seus filhos e seu pai estão. É essa previsibilidade que a árvore quase-completa oferece e
que o heap explora.

## 3. A fórmula — lida devagar

Numerando os nós **em largura** (Teoria 05 de 1.1), começando do índice `0` na raiz:

```
pai(i)       = (i - 1) / 2      (divisão inteira)
filho_esq(i) = 2*i + 1
filho_dir(i) = 2*i + 2
```

> 📖 **Lendo devagar:** `filho_esq(i) = 2*i + 1` — "pegue a posição `i`, dobre, e some 1".
> Por que dobrar? Porque, indo de um nível para o próximo, o número de posições **dobra**
> (nível 0 tem 1 posição, nível 1 tem 2, nível 2 tem 4...) — então a posição de um filho
> avança "duas vezes mais rápido" que a do pai. O `+1` (ou `+2` para o filho direito) só
> ajusta o deslocamento dentro do par de filhos.

## 4. Conferindo com árvore E array lado a lado

Árvore (mesma da Teoria 01, seção 3):

```
              8
           /     \
          4       5
         / \
        1   3
```

Numerando em largura: `8`→índice 0, `4`→índice 1, `5`→índice 2, `1`→índice 3, `3`→índice 4.

Array correspondente:

```
índice:  0   1   2   3   4
valor:   8   4   5   1   3
```

**Conferindo a fórmula, nó a nó:**

| Nó (índice) | `pai(i) = (i-1)/2` | Confere na árvore? |
|---|---|---|
| `4` (i=1) | `(1-1)/2 = 0` → pai é índice 0 (`8`) | ✔ `4` é filho de `8` |
| `5` (i=2) | `(2-1)/2 = 0` (divisão inteira: `1/2=0`) → pai é índice 0 (`8`) | ✔ `5` é filho de `8` |
| `1` (i=3) | `(3-1)/2 = 1` → pai é índice 1 (`4`) | ✔ `1` é filho de `4` |
| `3` (i=4) | `(4-1)/2 = 1` (divisão inteira: `3/2=1`) → pai é índice 1 (`4`) | ✔ `3` é filho de `4` |

E na outra direção: `filho_esq(1) = 2*1+1 = 3` → índice 3 é `1` ✔ (filho esquerdo de `4`).
`filho_dir(1) = 2*1+2 = 4` → índice 4 é `3` ✔ (filho direito de `4`). `filho_esq(0) =
2*0+1 = 1` → índice 1 é `4` ✔. `filho_dir(0) = 2*0+2 = 2` → índice 2 é `5` ✔.

## 5. Letra miúda: o que quebra se a árvore não for completa

Essas fórmulas **só** funcionam porque não há buraco antes do último nível. Se você tentar
representar assim uma árvore binária qualquer (por exemplo, um nó com filho só à direita,
deixando a posição do filho esquerdo "vazia" no meio da numeração), o array teria posições
vazias espalhadas no meio, desperdiçando espaço e quebrando a contagem em largura. É por
isso que "heap" e "árvore completa" andam sempre juntos — a representação em array só
compensa quando a estrutura garante ausência de buracos.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| numerar os nós em largura, 0, 1, 2, ... | atribuo a cada nó uma posição de array **sem precisar guardar ponteiro nenhum** — a posição já diz "onde estou na árvore" |
| `(i-1)/2` com divisão inteira | uso o truque de que dois índices consecutivos (`2k+1`, `2k+2`) têm o **mesmo** pai `k` — a divisão inteira "arredonda pra baixo" os dois de volta para `k` |
| escolher representar em array em vez de `struct` com ponteiro | troco flexibilidade (aceitar qualquer formato de árvore) por **economia de memória e localidade de cache** — só vale a troca porque heap é sempre completo |

## 7. Exercícios de fixação

1. Um heap tem 7 elementos, array `[50, 30, 40, 10, 20, 35, 25]` (índices 0 a 6). Desenhe a
   árvore correspondente.
2. Calcule `pai(5)`, `filho_esq(5)`, `filho_dir(5)`. Eles existem no array da questão 1?
3. Por que a raiz (índice 0) é o único índice sem pai válido pela fórmula `(i-1)/2`?
4. Se um heap tem `n = 10` elementos (índices 0 a 9), qual é o **maior** índice que ainda
   tem pelo menos um filho dentro do array (ou seja, é um nó interno, não folha)?

### Gabarito

1.
   ```
                50
             /      \
            30        40
           /  \       /  \
          10   20   35    25
   ```
2. `pai(5) = (5-1)/2 = 2` → índice 2 (`40`). `filho_esq(5) = 2*5+1 = 11` → **não existe**
   no array (só vai até índice 6). `filho_dir(5) = 2*5+2 = 12` → também não existe. Ou
   seja, o nó de índice 5 (`35`) é uma **folha**.
3. Porque `(0-1)/2` envolveria índice negativo — não existe "posição -1" no array; a raiz
   é, por definição, quem não tem pai, e a fórmula simplesmente não deveria ser aplicada a
   ela (todo código real testa `if (i == 0) não tem pai` ou equivalente).
4. `filho_esq(i) = 2i+1` precisa ser `< n = 10`, ou seja, `2i+1 < 10 → i < 4.5 → i ≤ 4`. O
   maior índice com filho é `i = 4` (`filho_esq(4) = 9`, que existe; `filho_dir(4) = 10`,
   que não existe — mas já basta ter um filho para ser nó interno). Índices 5 a 9 são
   todos folhas.

## Resumo

- Heap é sempre árvore **completa** — isso garante "sem buraco", o que permite representar
  em array puro.
- `pai(i)=(i-1)/2`, `filho_esq(i)=2i+1`, `filho_dir(i)=2i+2` — aritmética de índice
  substitui ponteiro.
- Numeração é sempre em **largura** (nível a nível), a mesma ordem da Teoria 05 de 1.1.
- Essa representação só é válida porque a estrutura garante ausência de buracos — não
  generaliza para árvore binária qualquer.

**Próximo:** [[Teoria 03 - Heapify-down e heapify-up (corrigindo a propriedade)]].
