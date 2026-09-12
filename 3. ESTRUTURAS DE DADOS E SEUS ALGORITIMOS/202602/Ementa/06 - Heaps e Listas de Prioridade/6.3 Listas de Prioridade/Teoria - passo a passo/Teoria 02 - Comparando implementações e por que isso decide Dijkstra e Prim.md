# Teoria 02 — Comparando implementações, e por que a escolha decide Dijkstra e Prim

> **Onde isto entra:** fecha 6.3 mostrando por que a escolha de implementação de fila de
> prioridade (Teoria 01) não é um detalhe — ela aparece direto na fórmula de complexidade
> de dois algoritmos centrais de grafos (módulo 02), mesmo sem precisar explicá-los por
> completo aqui.
> **Antes:** [[Teoria 01 - Fila de prioridade como TAD (a interface, não a implementação)]].
> **Fonte:** CO (Cormen) — capítulos de Dijkstra/Prim e de heaps binomiais/Fibonacci
> (parte de "Estruturas de Dados Avançadas") — conferir página exata (PDF não abre nesta
> máquina).

## 1. A ideia em uma frase

Cada implementação da Teoria 01 tem um custo diferente por operação — e a operação que mais
importa para Dijkstra/Prim é especificamente `diminuir-chave`, porque é a que esses
algoritmos chamam **muitas vezes**.

## 2. A tabela de custos — lida devagar

| Implementação | Inserir | Remover-mín | Consultar-mín | Diminuir-chave |
|---|---|---|---|---|
| Array não ordenado | O(1) | O(n) | O(n) | O(1) |
| Array ordenado | O(n) | O(1) | O(1) | O(n) |
| Heap binário (6.1) | O(log n) | O(log n) | O(1) | O(log n) |
| Heap binomial | O(log n) amortizado | O(log n) | O(log n) | O(log n) |
| Heap de Fibonacci | O(1) amortizado | O(log n) amortizado | O(1) | **O(1) amortizado** |

> 📖 **Lendo a tabela por coluna, não por linha:** não pergunte "qual implementação é a
> melhor" (não existe resposta única) — pergunte "**qual operação** meu algoritmo chama
> mais vezes, e em que volume?". Um algoritmo que só insere e nunca remove quer a primeira
> linha; um que só extrai o mínimo repetidamente (sem inserir de volta) quer a segunda; a
> maioria dos usos gerais (escalonadores, filas de evento) usa heap binário, equilíbrio
> razoável em tudo.

## 3. Por que Dijkstra e Prim se importam especificamente com `diminuir-chave`

Os dois algoritmos (você vê o algoritmo completo no módulo `02 - Grafos`) seguem o mesmo
padrão: a cada iteração, **extraem** o vértice de menor "custo provisório" da fila (uma
chamada de `remover-mínimo`), e depois, ao processar as arestas desse vértice, **atualizam**
(reduzem) o custo provisório de vizinhos ainda na fila — isso é exatamente
`diminuir-chave`, chamada **uma vez por aresta processada**, ou seja, até O(E) vezes ao
longo do algoritmo inteiro (E = número de arestas).

## 4. Conferindo com a fórmula de complexidade final

**Com heap binário:** cada `diminuir-chave` custa O(log V) (V = número de vértices, altura
do heap). Chamando isso O(E) vezes: O(E log V). Somado às O(V) extrações de mínimo (também
O(log V) cada): complexidade total **O((V+E) log V)**.

**Com heap de Fibonacci:** cada `diminuir-chave` custa O(1) amortizado. Chamando O(E) vezes:
O(E). Somado às O(V) extrações (O(log V) amortizado cada, mais caras que diminuir-chave):
complexidade total **O(E + V log V)**.

> 📖 **Quando a diferença importa de verdade:** compare os dois totais num grafo **denso**
> (E próximo de V²). `(V+E) log V` fica dominado por `E log V ≈ V² log V`. `E + V log V`
> fica dominado por `E ≈ V²` — **sem** o fator `log V` extra. Nesse regime, heap de
> Fibonacci é assintoticamente melhor. Num grafo **esparso** (E próximo de V), a diferença
> entre os dois totais é pequena, e a constante escondida (maior no heap de Fibonacci) pode
> fazer o heap binário simples ganhar **na prática**, mesmo pior assintoticamente.

## 5. 📌 O que você está REALMENTE escolhendo

| O passo mecânico | O que ele realmente é |
|---|---|
| contar quantas vezes o algoritmo chama cada operação | identifico qual coluna da tabela (seção 2) realmente domina o custo total — não adianta otimizar uma operação pouco usada |
| escolher heap binário "por padrão" | aceito uma complexidade pior no pior caso teórico em troca de simplicidade de implementação e melhor desempenho prático em grafos pequenos/esparsos |
| escolher heap de Fibonacci só quando justificado | pago a complexidade de implementação **apenas** quando o volume de `diminuir-chave` (grafos densos, grande escala) realmente compensa o ganho assintótico |

## 6. Exercícios de fixação

1. Um algoritmo faz `n` inserções e, ao final, `n` remoções-do-mínimo, sem nenhuma
   `diminuir-chave`. Faz sentido usar heap de Fibonacci aqui? Por quê?
2. Num grafo com `V = 1000` vértices e `E = 500.000` arestas (denso, próximo de `V²=10^6`),
   qual das duas fórmulas de complexidade da seção 4 tende a ser menor?
3. Por que "assintoticamente melhor" não significa automaticamente "mais rápido na
   prática"?

### Gabarito

1. Não especialmente — a vantagem do heap de Fibonacci é `diminuir-chave` O(1) amortizado;
   sem nenhuma chamada dessa operação, ele não tem vantagem sobre um heap binário simples
   (que já dá inserção e remoção em O(log n), com implementação mais simples).
2. `E + V log V` (heap de Fibonacci): `500.000 + 1000·log(1000) ≈ 500.000 + 10.000 =
   510.000`. `(V+E) log V` (heap binário): `(1000+500.000)·10 ≈ 5.010.000`. Neste grafo
   denso, a fórmula do heap de Fibonacci é claramente menor.
3. Porque "assintoticamente melhor" só garante vantagem quando `n` (ou, aqui, `V`/`E`) é
   **grande o suficiente** para as constantes escondidas na notação O deixarem de dominar.
   Heap de Fibonacci tem operações mais complexas por chamada (mais "trabalho de
   contabilidade" por trás do amortizado O(1)) — em grafos pequenos ou esparsos, essa
   constante maior pode superar o ganho assintótico, e o heap binário simples ganha na
   prática.

## Resumo

- A escolha de implementação de fila de prioridade não é estética — ela entra direto na
  fórmula de complexidade de quem a usa.
- Dijkstra e Prim chamam `diminuir-chave` até O(E) vezes — é essa operação, especificamente,
  que diferencia heap binário (O(log V) cada) de heap de Fibonacci (O(1) amortizado cada).
- A vantagem assintótica do heap de Fibonacci só se manifesta de fato em grafos densos e de
  grande escala — fora disso, heap binário simples costuma vencer na prática.

---

Isso fecha a teoria do módulo 06 (Heaps e Listas de Prioridade). Para os algoritmos
completos de Dijkstra e Prim, ver [[../../../02 - Grafos/README|módulo 02 - Grafos]].
