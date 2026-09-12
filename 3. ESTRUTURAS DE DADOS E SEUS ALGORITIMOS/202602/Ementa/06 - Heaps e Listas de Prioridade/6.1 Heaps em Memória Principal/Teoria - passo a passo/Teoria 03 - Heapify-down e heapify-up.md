# Teoria 03 — Heapify-down e heapify-up: corrigindo a propriedade de heap

> **Onde isto entra:** toda vez que um heap muda (inserção ou remoção do topo), a
> propriedade da Teoria 01 pode quebrar em **um** ponto — essas duas operações consertam
> exatamente esse ponto, sem precisar reconstruir a árvore inteira.
> **Antes:** [[Teoria 02 - Representando um heap em array (índices pai e filhos)]].
> **Fonte:** CO (Cormen), cap. 6, `MAX-HEAPIFY` — conferir página exata (PDF não abre nesta
> máquina); código equivalente em C já usado no `README.md` deste subtópico.

## 1. A ideia em uma frase

Se **só um nó** pode estar violando a propriedade de heap (maior que o pai, ou menor que um
filho), basta "empurrar" esse nó na direção certa — para baixo (heapify-down) ou para cima
(heapify-up) — até ele parar num lugar onde a regra volta a valer.

## 2. De onde vem a necessidade

Depois de uma inserção (Teoria 04) ou de uma remoção do topo, a árvore quase inteira ainda
respeita a propriedade de heap — só o nó recém-colocado pode estar "fora do lugar". Refazer
o heap do zero seria O(n log n) por operação; heapify-down/up aproveitam que só **um
caminho** (da posição do nó até a raiz, ou até uma folha) precisa ser corrigido, custando
O(log n) — a altura da árvore.

## 3. Heapify-down — lido devagar

Usado quando um nó pode ser **menor** que um de seus filhos (típico após colocar um valor
pequeno na raiz).

```c
static void heapify_down(Heap *h, int i) {
    int maior = i;
    int e = filho_esq(i);
    int d = filho_dir(i);

    if (e < h->tamanho && h->dados[e] > h->dados[maior]) maior = e;
    if (d < h->tamanho && h->dados[d] > h->dados[maior]) maior = d;

    if (maior != i) {
        troca(&h->dados[i], &h->dados[maior]);
        heapify_down(h, maior);
    }
}
```

> 📖 **Lendo devagar:**
> 1. `maior = i` — hipótese inicial: talvez o próprio nó `i` já seja o maior dos três
>    (ele mesmo, filho esquerdo, filho direito).
> 2. `if (e < h->tamanho && ...)` — **duas condições, nessa ordem, por causa do curto-
>    circuito de `&&`**: primeiro confere se o filho esquerdo **existe** (`e < tamanho`);
>    só se existir é seguro acessar `h->dados[e]`. Sem essa ordem, acessaria posição fora
>    do array.
> 3. Se o filho existente for maior que o "maior" atual, atualiza `maior` para apontar pra
>    ele.
> 4. Repete para o filho direito.
> 5. `if (maior != i)` — se algum filho venceu a comparação (não é mais o próprio `i`),
>    troca os dois valores e **chama a si mesma** na nova posição (`maior`) — o valor que
>    desceu pode continuar violando a propriedade mais abaixo, então o processo continua
>    até parar (folha, ou não violar mais).

### Conferindo com trace completo

Array `[3, 8, 5, 1, 4]` (violação na raiz — `3` é menor que os filhos `8` e `5`):

```
índice:  0   1   2   3   4
valor:   3   8   5   1   4
```

`heapify_down(h, 0)`:
1. `maior = 0` (valor 3). `e = 1` (valor 8): `8 > 3` → `maior = 1`. `d = 2` (valor 5):
   `5 > 8`? Não → `maior` continua 1.
2. `maior (1) != i (0)` → troca `dados[0]` com `dados[1]`: array vira `[8, 3, 5, 1, 4]`.
3. Chamada recursiva: `heapify_down(h, 1)` (o valor `3` agora está na posição 1).
4. `maior = 1` (valor 3). `e = 2*1+1 = 3` (valor 1): `1 > 3`? Não. `d = 2*1+2 = 4` (valor
   4): `4 > 3`? Sim → `maior = 4`.
5. `maior (4) != i (1)` → troca `dados[1]` com `dados[4]`: array vira `[8, 4, 5, 1, 3]`.
6. Chamada recursiva: `heapify_down(h, 4)` (índice 4 não tem filhos, `filho_esq(4)=9` fora
   do array) → `maior` continua 4, `maior == i`, **para**.

Resultado final: `[8, 4, 5, 1, 3]` — max-heap válido (confira: `8≥4`, `8≥5`, `4≥1`, `4≥3`).

## 4. Heapify-up — lido devagar

Usado quando um nó pode ser **maior** que o pai (típico após colocar um valor novo no
final do array).

```c
static void heapify_up(Heap *h, int i) {
    while (i > 0 && h->dados[pai(i)] < h->dados[i]) {
        troca(&h->dados[pai(i)], &h->dados[i]);
        i = pai(i);
    }
}
```

> 📖 **Lendo devagar:** `while (i > 0 && h->dados[pai(i)] < h->dados[i])` — duas condições:
> "ainda não cheguei na raiz" **e** "sou maior que meu pai". Enquanto as duas forem
> verdadeiras, troco de lugar com o pai e **atualizo `i` para a nova posição** (`i =
> pai(i)`) — o laço, não recursão, sobe um nível a cada volta.

**Diferença de forma em relação a heapify-down:** heapify-down precisa **escolher entre 2
filhos** (por isso usa recursão com um `if` comparando os dois); heapify-up só tem **1**
pai para comparar (por isso um `while` simples basta, sem precisar de recursão).

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| heapify-down troca com o **maior** dos dois filhos, não com qualquer um | garante que, depois da troca, o filho que **ficou** no lugar do pai continua ≥ seu irmão — senão a violação só mudaria de lugar |
| heapify-up compara só com o pai, num laço | só existe 1 caminho pra cima (cada nó tem 1 pai só) — não há escolha a fazer, diferente de descer |
| ambas param assim que a condição deixa de valer | o custo é proporcional a **quantos níveis** o valor precisou percorrer, não à árvore inteira — daí o O(log n) |

## 6. Exercícios de fixação

1. Rode `heapify_down` sobre o array `[2, 9, 7, 1, 8]` (violação na raiz), mostrando cada
   troca, até o resultado final.
2. Rode `heapify_up` sobre o array `[8, 4, 5, 1, 3, 9]` (o `9` acabou de ser inserido no
   índice 5), mostrando cada troca.
3. Por que heapify-up nunca precisa de recursão, mas heapify-down é naturalmente escrito
   com recursão (ou um laço que também escolhe entre dois lados)?

### Gabarito

1. `maior(0)`: filhos `9`(idx1) e `7`(idx2), maior é `9` → troca `dados[0]` com `dados[1]`:
   `[9, 2, 7, 1, 8]`. Recursão em `i=1`: filhos de índice 1 são idx `3`(`1`) e idx `4`(`8`);
   maior entre `2,1,8` é `8` (idx4) → troca: `[9, 8, 7, 1, 2]`. Recursão em `i=4`: sem
   filhos (índice 4, `filho_esq=9` fora do array) → para. Resultado: `[9, 8, 7, 1, 2]`.
2. `i=5` (valor 9): `pai(5)=(5-1)/2=2` (valor 5). `5 < 9` → troca: `[8, 4, 9, 1, 3, 5]`,
   `i` vira 2. `pai(2)=(2-1)/2=0` (valor 8). `8 < 9` → troca: `[9, 4, 8, 1, 3, 5]`, `i` vira
   0. `i == 0`, laço para (condição `i > 0` falha). Resultado: `[9, 4, 8, 1, 3, 5]`.
3. Porque subir tem sempre **um único** caminho possível (cada nó tem exatamente 1 pai),
   então basta um laço comparando com esse único pai. Descer tem **dois** caminhos
   possíveis (2 filhos) — é preciso decidir qual dos dois seguir (o maior, para não deixar
   uma violação pra trás), e essa decisão de "qual dos dois" é o que naturalmente pede um
   `if` a mais a cada nível (por isso a versão recursiva/com escolha).

## Resumo

- Heapify-down conserta um nó que pode ser menor que um filho: escolhe o **maior** filho,
  troca, e repete na nova posição — O(log n).
- Heapify-up conserta um nó que pode ser maior que o pai: só compara com o único pai, num
  laço simples — O(log n).
- Ambas corrigem **um** caminho na árvore, não a árvore inteira — é isso que as torna
  rápidas.

**Próximo:** [[Teoria 04 - Build-heap, inserção, extração e heapsort]].
