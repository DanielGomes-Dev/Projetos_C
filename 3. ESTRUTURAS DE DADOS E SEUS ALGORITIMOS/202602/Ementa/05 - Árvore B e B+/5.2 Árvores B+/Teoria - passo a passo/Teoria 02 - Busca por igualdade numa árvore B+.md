# Teoria 02 — Como buscar uma chave exata numa árvore B+?

> **Onde isto entra:** parece igual à busca de árvore B (5.1, Teoria 03), mas tem uma
> pegadinha: em B+, achar a chave num nó interno **não termina a busca**.
> **Antes:** [[Teoria 01 - As duas diferenças estruturais entre B e B+]].
> **Fonte:** síntese do `README.md` deste subtópico, seção "Busca" (ver aviso de fonte na
> Teoria 01 sobre paginação de livro não confirmada).

## 1. A ideia em uma frase

Buscar por igualdade numa árvore B+ desce pela árvore usando as chaves dos nós internos só
como **guia de navegação** — e **sempre** termina numa folha, mesmo que a chave buscada
apareça "no caminho" como separador.

## 2. De onde vem essa diferença (motivação)

Na árvore B (5.1), o dado podia estar em qualquer nó — então a busca podia **parar assim
que achasse a chave**, em qualquer nível. Na árvore B+ (Teoria 01), você já sabe que nós
internos **não têm dado**, só separador. Isso muda a regra do jogo: achar a chave `10` num
nó interno não significa "achei o dado" — significa só "sei para que lado descer". O dado
de verdade só existe na folha.

## 3. O algoritmo — lido pedaço por pedaço

> 📖 **Lendo devagar — buscando `x` numa árvore B+:**
>
> 1. Compare `x` com as chaves do nó atual (começando na raiz), da esquerda para a direita.
> 2. **Mesmo que `x` seja igual a uma das chaves do nó**, isso só diz **qual filho seguir**
>    — não retorna o dado ainda (diferente da árvore B comum!).
> 3. Se o nó atual é uma **folha**: procure `x` entre as chaves dessa folha. Se achar,
>    retorne o dado associado. Se não achar, `x` não existe na árvore.
> 4. Se o nó atual é **interno**: desça para o filho certo (o mesmo critério de "encaixe
>    entre separadores" da árvore B) e repita a partir do passo 1.

## 4. Conferindo com a árvore concreta

```
                 [10 | 20]
                /     |     \
           [3,5] → [10,15] → [20,25,30]
```

**Busca por `10` (existe, e "aparece" no nó interno como separador):**

| Nó visitado | O que acontece | Decisão |
|---|---|---|
| `[10\|20]` (raiz, interna) | `10` é igual à primeira chave do nó | **não retorna aqui** — é só um separador; desce para o filho **do meio** (entre as duas chaves), que é `[10,15]` |
| `[10,15]` (folha) | procura `10` entre as chaves da folha | achou `10` — **agora sim**, retorna o dado associado a `10` |

> **Conferindo a pegadinha:** se esta fosse uma árvore B comum (5.1), a busca por `10`
> **pararia na raiz**, porque lá o dado já estaria disponível. Em B+, o encontro da chave no
> nó interno é **ignorado como resposta** — ele só decide o caminho; a busca **sempre**
> desce até uma folha antes de responder.

**Busca por `7` (não existe):**

| Nó visitado | O que acontece | Decisão |
|---|---|---|
| `[10\|20]` | `7 < 10` | desce para o filho da esquerda, `[3,5]` |
| `[3,5]` (folha) | procura `7` entre `3` e `5` | não achou, e é folha (sem filho para descer) → **retorna falha** |

## 5. Letra miúda

**"Mesmo que ache no nó interno" é a regra que mais gente erra em prova.** É tentador, ao
ver a chave buscada aparecer num nó interno, achar que "já terminou" — copiando o hábito da
árvore B (5.1) ou da BST. Em árvore B+, **a resposta nunca está no nó interno** — ele só
existe para guiar. Se o exercício perguntar "quantos nós a busca por X visita", a resposta
sempre inclui pelo menos uma folha, mesmo que X apareça mais cedo como separador.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| comparar `x` com separadores de um nó interno | decido só **para que lado ir** — nunca leio um dado aqui |
| ignorar uma "coincidência" de `x` com um separador | respeito a regra de que dado só existe em folha — não corto caminho |
| procurar `x` dentro da folha alcançada | é o único lugar onde a busca pode, de fato, achar o dado |

## 7. Exercícios de fixação

Usando a mesma árvore da seção 4:

1. Trace a busca por `20`. Em quantos nós ela realmente para para procurar o dado?
2. Trace a busca por `30`.
3. Por que a busca por igualdade em árvore B+ nunca é **mais rápida** que numa árvore B
   equivalente (na verdade, no pior caso, visita exatamente a mesma quantidade de níveis)?

### Gabarito

1. `[10|20]`: `20` é igual à segunda chave — decide ir para o filho **da direita** de `20`,
   que é `[20,25,30]` (não retorna ainda). `[20,25,30]` (folha): acha `20` entre as chaves —
   **agora sim** retorna o dado. Visitou 2 nós, mas só "procurou o dado de fato" na folha.
2. `[10|20]`: `30 > 20` → desce para `[20,25,30]`. Folha: acha `30` → retorna o dado.
3. Porque em ambos os casos (B e B+) o número de níveis (altura) é o que domina o custo, e
   B+ não reduz o número de **comparações por busca** — ela só muda **onde** o dado é
   encontrado (sempre na folha, nunca antes). A vantagem de B+ não é a busca por igualdade —
   é a busca por **intervalo** (Teoria 03).

## Resumo

- Busca por igualdade em B+ sempre termina numa **folha** — encontrar a chave num nó
  interno não conta como resposta, só decide o caminho.
- O algoritmo de navegação (comparar com separadores, escolher o filho) é igual ao da
  árvore B (5.1) — a diferença é só onde a busca **para de fato**.
- Isso não torna a busca por igualdade mais rápida que numa árvore B — a vantagem de B+
  aparece na busca por intervalo (próximo arquivo).

**Próximo:** [[Teoria 03 - Busca por intervalo (range query)]].
