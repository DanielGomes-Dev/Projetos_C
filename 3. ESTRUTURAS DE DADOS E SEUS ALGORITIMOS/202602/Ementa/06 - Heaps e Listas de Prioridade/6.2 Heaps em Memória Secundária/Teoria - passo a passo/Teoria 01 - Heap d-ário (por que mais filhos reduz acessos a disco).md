# Teoria 01 — Heap d-ário: trocar filhos a mais por menos níveis

> **Onde isto entra:** o mesmo padrão de motivação que você já viu em árvore B (módulo 05):
> em disco, o que custa é o **número de acessos**, não o número de comparações — e a
> resposta, de novo, é "nós mais gordos, árvore mais rasa".
> **Antes:** [[../../6.1 Heaps em Memória Principal/Teoria - passo a passo/Teoria 02 - Representando um heap em array (índices pai e filhos)|6.1 Teoria 02]].
> **Fonte:** SZ (livro-base) — conferir página exata (PDF não abre nesta máquina). CO
> (Cormen) não tem capítulo dedicado a heap em memória secundária — a ideia abaixo
> generaliza o heap binário de 6.1 usando o mesmo raciocínio de custo de disco do módulo
> `04 - Tabelas Hash` (4.2) e `05 - Árvore B e B+`.

## 1. A ideia em uma frase

Um heap **d-ário** é a mesma ideia do heap binário (6.1), só que cada nó pode ter até `d`
filhos em vez de 2 — trocando "poucos filhos, árvore alta" por "muitos filhos, árvore
baixa".

## 2. De onde vem a necessidade

O heap binário de 6.1 assume que navegar entre índices `i`, `2i+1`, `2i+2` custa sempre o
mesmo — verdade em RAM, falsa em disco, onde cada acesso pode custar uma leitura de bloco
inteira. Uma inserção ou extração num heap binário de `n` elementos toca até `log₂ n` nós —
em disco, até `log₂ n` acessos. Reduzir esse número é o objetivo.

## 3. A fórmula — lida devagar

```
pai(i)     = (i - 1) / d
filho_k(i) = d*i + k + 1        (k = 0, 1, ..., d-1)
```

> 📖 **Lendo devagar:** compare com a fórmula binária de 6.1 (`2i+1`, `2i+2` — que é este
> caso com `d=2`, `k=0` e `k=1`). Aumentar `d` significa que cada nó "absorve" mais
> posições como filho — a numeração em largura ainda vale, só que agora cada nível tem `d`
> vezes mais posições que o anterior, em vez de 2 vezes mais.

## 4. Conferindo com número: por que altura cai

**Afirmação:** heap binário com `n=1000` tem altura ≈ `log₂(1000) ≈ 10`; heap 4-ário com o
mesmo `n` tem altura ≈ `log₄(1000) ≈ 5`.

**Conferindo:** `2^10 = 1024 ≥ 1000` ✔ (10 níveis bastam pra caber 1000 nós num heap
binário quase-completo). `4^5 = 1024 ≥ 1000` ✔ (5 níveis bastam pra caber 1000 nós num
heap 4-ário). **Metade dos níveis** para o mesmo número de elementos — em disco, isso
significa até metade dos acessos no pior caso de uma inserção/extração.

## 5. O preço: mais comparações por nível

Descer um nível num heap binário compara com **2** filhos (escolhe o maior). Descer um
nível num heap 4-ário compara com **até 4** filhos. O trade-off:

| d (grau) | Altura (níveis = acessos, pior caso) | Comparações por nível ao descer |
|---|---|---|
| 2 (binário) | O(log₂ n) — mais níveis | 2 (menos comparações) |
| 4 | O(log₄ n) — metade dos níveis de d=2 | até 4 (mais comparações) |
| d grande | O(log_d n) — poucos níveis | até d-1 (muitas comparações) |

**Por que vale a pena em disco:** comparação em RAM é praticamente grátis perto do custo de
um acesso a disco. Trocar "menos acessos" por "mais comparações (todas em RAM)" é sempre um
bom negócio até o ponto em que os `d` ponteiros/filhos de um nó deixam de caber numa página
de disco — daí em diante o próprio nó exigiria mais de um acesso para ser lido, e o ganho
para.

## 6. O código — só a parte que muda de verdade

```c
static int filho_d(HeapD *h, int i, int k) { return h->d * i + 1 + k; }  // k = 0..d-1

static void heapd_down(HeapD *h, int i) {
    int maior = i;
    for (int k = 0; k < h->d; k++) {          // agora é um LAÇO sobre até d filhos,
        int filho = filho_d(h, i, k);         // não um `if` fixo comparando 2
        if (filho < h->tamanho && h->dados[filho] > h->dados[maior])
            maior = filho;
    }
    if (maior != i) {
        troca(&h->dados[i], &h->dados[maior]);
        heapd_down(h, maior);
    }
}
```

> 📖 **Lendo a mudança:** compare com `heapify_down` de 6.1 (Teoria 03), que tinha dois
> `if` fixos (um para `filho_esq`, um para `filho_dir`). Aqui, o `for (k de 0 até d-1)`
> generaliza isso para **qualquer** número de filhos — o heap binário de 6.1 é literalmente
> este código com `d=2`.

## 7. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| aumentar `d` na fórmula de índice | reduzo o número de **níveis** (logo, de acessos a disco no pior caso) às custas de mais filhos por nó |
| o `for` em `heapd_down` percorrer até `d` filhos | pago em **comparações (RAM, barato)** o que economizo em **acessos (disco, caro)** |
| escolher `d` até o limite do tamanho de bloco de disco | paro de aumentar `d` no ponto em que um nó com `d` filhos deixaria de caber numa leitura de página — depois disso, o ganho desaparece |

## 8. Exercícios de fixação

1. Um heap 8-ário tem `n = 4096` elementos. Estime a altura (`log₈(4096)`).
2. Por que aumentar `d` indefinidamente **não** continua compensando para sempre?
3. Escreva a fórmula de `pai(i)` para um heap 8-ário e calcule `pai(20)`.

### Gabarito

1. `8^4 = 4096`, então altura ≈ 4 níveis (`log₈(4096) = 4`).
2. Porque, em algum ponto, os `d` ponteiros/filhos de um único nó deixam de caber numa
   página/bloco de disco — o próprio nó passaria a exigir mais de 1 acesso pra ser lido
   inteiro, cancelando o ganho de ter menos níveis.
3. `pai(i) = (i-1)/8` (divisão inteira). `pai(20) = (20-1)/8 = 19/8 = 2` (divisão inteira).

## Resumo

- Heap d-ário generaliza o binário: até `d` filhos por nó, fórmulas `pai(i)=(i-1)/d`,
  `filho_k(i)=d·i+1+k`.
- Mais filhos → menos níveis → menos acessos a disco no pior caso — às custas de mais
  comparações por nível (pagas em RAM, quase de graça perto de um acesso a disco).
- `d` ideal é limitado pelo tamanho de bloco de disco, não é "quanto maior, melhor" sem
  limite.

**Próximo:** [[Teoria 02 - Heap externo e seleção por substituição]].
