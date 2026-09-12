# Teoria 02 — Onde o heap aparece de novo: seleção por substituição

> **Onde isto entra:** heap não é só uma estrutura isolada — ela é usada **dentro** de
> outro algoritmo do curso, na etapa mais difícil de entender do módulo de ordenação
> externa. Ver esse uso concreto ajuda a fixar por que dominar heap importa mesmo fora
> deste módulo.
> **Antes:** [[Teoria 01 - Heap d-ário (por que mais filhos reduz acessos a disco)]] ·
> [[../../../03 - Arquivos e Ordenação Externa/README|módulo 03 - Arquivos e Ordenação Externa]] (contexto de ordenação externa).
> **Fonte:** SZ (livro-base) — conferir página exata (PDF não abre nesta máquina).

## 1. A ideia em uma frase

**Seleção por substituição** (replacement selection) é um método de gerar partições
(pedaços já ordenados de um arquivo grande) que usa um **min-heap** para sempre saber, a
cada passo, qual é o próximo menor elemento a escrever — e o truque é que, às vezes, dá
pra continuar usando o mesmo heap para gerar uma partição **maior que a memória
disponível**.

## 2. De onde vem a necessidade (o problema que ordenação externa resolve)

Quando o arquivo a ordenar não cabe inteiro na memória (módulo 03), a estratégia clássica é
dividir o arquivo em pedaços que cabem na memória, ordenar cada pedaço (uma **partição**) e
depois intercalar as partições ordenadas. Quanto **maiores** as partições, menos partições
existem para intercalar depois — e seleção por substituição é um jeito de gerar partições
maiores que o próprio espaço de memória usado para gerá-las.

## 3. O mecanismo — lido devagar

> Imagine um heap (min-heap) do tamanho da memória disponível, digamos capacidade `M`.

1. Enche o heap com os primeiros `M` elementos do arquivo de entrada.
2. Repete:
   - Remove o mínimo do heap (Teoria 04 de 6.1: `heap_extrai_min`) — esse valor é escrito
     na partição de saída, que assim cresce em ordem crescente.
   - Lê o **próximo** elemento do arquivo de entrada.
     - **Se esse elemento for ≥ o último valor escrito na partição**, ele ainda cabe na
       partição atual (mantém a ordem) — insere ele no heap, no lugar do que saiu.
     - **Se for menor** que o último valor escrito, ele **não pode** entrar nesta partição
       (quebraria a ordem crescente) — ele é guardado à parte, para a **próxima** partição,
       e o heap "encolhe" uma posição (fica temporariamente com menos elementos).
3. A partição atual termina quando o heap "encolhido" fica vazio; começa então uma nova
   partição com os elementos que foram guardados à parte.

> 📖 **A parte que costuma confundir:** o heap **não** precisa ter sempre exatamente `M`
> elementos — ele pode encolher (quando um elemento não cabe na partição atual) e, na
> prática, o processo de "um sai, um novo entra" é o que permite a partição de saída
> crescer **além** do tamanho `M` da memória: o heap em si nunca ultrapassa `M`, mas o
> **arquivo de partição gerado** pode ser muito maior, porque elementos vão sendo
> substituídos (daí o nome) um a um, não processados em blocos fixos de tamanho `M`.

## 4. Conferindo com um exemplo pequeno

Memória para `M = 3` elementos. Arquivo de entrada, na ordem em que chega:
`5, 2, 8, 1, 9, 3`.

| Passo | Heap (min) | Ação | Partição de saída (até agora) |
|---|---|---|---|
| início | `[5, 2, 8]` | enche o heap com os 3 primeiros | `` |
| 1 | remove `2` | `2` é o menor → escreve. Lê próximo (`1`). `1 < 2`? Sim → não cabe nesta partição; guarda `1` à parte; heap encolhe: `[5, 8]` | `2` |
| 2 | remove `5` | escreve `5`. Lê próximo (`9`). `9 ≥ 5`? Sim → insere no heap: `[8, 9]` | `2, 5` |
| 3 | remove `8` | escreve `8`. Lê próximo (`3`). `3 ≥ 8`? Não → guarda `3` à parte; heap encolhe: `[9]` | `2, 5, 8` |
| 4 | remove `9` | escreve `9`. Sem mais entrada — heap fica vazio | `2, 5, 8, 9` |

Partição 1 completa: `2, 5, 8, 9` — **4 elementos**, maior que `M = 3` (o tamanho da
memória usada). Os elementos guardados à parte (`1`, `3`) formam o início da próxima
partição.

## 5. Ligação com a intercalação (módulo 3.3)

Depois de geradas as partições (cada uma já ordenada internamente), a fase de
**intercalação de k vias** (subtópico 3.3) precisa, a cada passo, escolher o menor entre os
"próximos" elementos de até `k` partições sendo mescladas — de novo, exatamente o problema
que um **min-heap** (ou uma estrutura equivalente, tournament tree) resolve: manter o
mínimo corrente acessível em O(1) e substituí-lo em O(log k) a cada remoção.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| remover o mínimo do heap e escrever na partição | garanto que a partição de saída cresce em ordem, um elemento de cada vez, sempre o menor disponível no momento |
| comparar o próximo elemento lido com o **último escrito** | decido se ele ainda mantém a partição corrente em ordem crescente, ou se pertence à próxima partição |
| deixar o heap encolher quando um elemento não cabe | não força um elemento fora de ordem para dentro da partição atual — prefiro adiar ele, mantendo a garantia de ordem |

## 7. Exercícios de fixação

1. Com `M = 2` e entrada `4, 1, 6, 2, 9`, monte a tabela de seleção por substituição (como
   na seção 4) e diga quantos elementos tem a primeira partição gerada.
2. Por que a partição gerada pode ser **maior** que `M`, mesmo o heap nunca tendo mais que
   `M` elementos ao mesmo tempo?
3. Que estrutura de dados do módulo 6.1 é reaproveitada aqui, e qual operação dela é usada
   a cada passo?

### Gabarito

1. Heap inicial `[4, 1]`. Remove `1` → escreve `1`. Lê `6`: `6 ≥ 1`? Sim → insere: `[4, 6]`.
   Remove `4` → escreve `4`. Lê `2`: `2 ≥ 4`? Não → guarda à parte; heap encolhe: `[6]`.
   Remove `6` → escreve `6`. Sem mais entrada relevante (só resta o guardado `2` e o `9`
   ainda não lido) → heap fica vazio, partição termina. Partição 1: `1, 4, 6` — **3
   elementos**, maior que `M=2`.
2. Porque o processo não lê a entrada em blocos fixos de tamanho `M` e para — ele
   **substitui** um elemento de cada vez (remove um, insere outro no lugar, se couber),
   então o total de elementos que passam pela partição antes dela "fechar" pode ultrapassar
   `M`, mesmo o heap em si nunca crescendo além disso.
3. O **heap (min-heap)** de 6.1 — a cada passo, usa `extrai-mínimo` (Teoria 04 de 6.1) para
   decidir o próximo valor a escrever, e `inserir` (mesma Teoria) para repor o heap com o
   elemento seguinte da entrada, quando ele couber na partição corrente.

## Resumo

- Seleção por substituição usa um min-heap do tamanho da memória disponível para gerar
  partições ordenadas **maiores** que essa memória.
- A cada passo: remove o mínimo (escreve na saída), lê o próximo da entrada, e decide se
  ele cabe na partição atual (`≥` último escrito) ou se vai para a próxima partição.
- A mesma ideia de heap (agora min, do tamanho de `k` partições) resolve a intercalação de
  k vias em 3.3 — heap não é só teoria isolada, é peça de outro algoritmo do curso.

---

Isso fecha a teoria de 6.2. Próximo: [[../../6.3 Listas de Prioridade/README|6.3 Listas de Prioridade]].
