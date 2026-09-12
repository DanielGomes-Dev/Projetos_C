# Teoria 01 — Fila de prioridade: o TAD, separado de qualquer implementação

> **Onde isto entra:** até aqui, "heap" e "fila de prioridade" andaram juntos como se
> fossem a mesma coisa. Este arquivo separa os dois — é uma distinção que prova cobra
> direto.
> **Antes:** [[../../6.2 Heaps em Memória Secundária/Teoria - passo a passo/Teoria 02 - Heap externo e seleção por substituição|6.2 Teoria 02]].
> **Fonte:** CO (Cormen), cap. 6 (fila de prioridade com heap binário); SZ — conferir
> página exata (PDF não abre nesta máquina).

## 1. A ideia em uma frase

**Fila de prioridade** é o **TAD** (tipo abstrato de dados — o "o quê": que operações
existem e o que elas fazem); **heap** é apenas **uma** implementação possível desse TAD (o
"como"). Poderia existir uma fila de prioridade implementada de outro jeito, sem heap
nenhum.

## 2. De onde vem a necessidade dessa distinção

Você já viu TAD vs. implementação antes, sem o nome: "árvore binária de busca" (1.2) é uma
ideia (busca ordenada), implementável com ponteiros (como no curso) ou, em teoria, de
outras formas. Aqui é igual: "eu preciso, a qualquer momento, tirar o elemento de maior
prioridade" é o **problema**; heap é **uma solução boa**, mas não a única, e cada solução
tem um perfil de custo diferente (seção 4).

## 3. A interface — lida devagar

> 📖 Uma fila de prioridade responde a estas operações (nomes podem variar, a ideia não):
> - `inserir(x)` — adiciona `x` com sua prioridade.
> - `remover-mínimo()` (ou máximo, a depender da convenção) — remove **e devolve** o
>   elemento de maior prioridade.
> - `consultar-mínimo()` — devolve sem remover.
> - `diminuir-chave(x, nova_chave)` — reduz a prioridade de um elemento **já inserido**,
>   sem removê-lo e reinseri-lo.

**Por que `diminuir-chave` é uma operação própria, e não "remover + inserir de novo"?**
Porque, dependendo da implementação, fazer isso diretamente (sem remover) é **mais barato**
— e, mais importante, alguns algoritmos (Dijkstra, Prim — seção 5) chamam essa operação
tantas vezes que a diferença de custo entre "diminuir direto" e "remover+reinserir" decide
a complexidade final do algoritmo inteiro.

## 4. Conferindo: a mesma interface, duas implementações bem diferentes

**Implementação A — array não ordenado:** `inserir(x)` = bota no fim, O(1).
`remover-mínimo()` = precisa **varrer tudo** pra achar o menor, O(n).

**Implementação B — heap binário (6.1):** `inserir(x)` = O(log n). `remover-mínimo()` =
O(log n).

**A mesma pergunta** ("qual é o próximo de maior prioridade?") tem respostas com custo
completamente diferente dependendo de qual das duas você escolheu por baixo — mas **quem
usa a fila de prioridade não precisa saber qual é**, só precisa saber que `inserir` e
`remover-mínimo` existem. Essa é a essência de "TAD": o código que usa a fila **não muda**
trocando a implementação por baixo.

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| chamar `fp_insere`/`fp_remove_max` sem saber o que tem "por dentro" | uso a **interface** — o TAD — sem me acoplar a uma implementação específica |
| trocar heap binário por array ordenado "por baixo" | mudo o **custo** de cada operação, sem mudar **nenhuma** linha de quem usa a fila |
| `diminuir-chave` existir como operação própria | reconheço que "reduzir prioridade de algo já lá dentro" é comum o bastante (Dijkstra, Prim) para merecer não pagar o preço de remover+reinserir |

## 6. Exercícios de fixação

1. Se um código chama só `inserir` e `consultar-mínimo` (nunca remove), qual das duas
   implementações da seção 4 seria melhor escolha, e por quê?
2. Por que "fila de prioridade" e "heap" não são sinônimos, mesmo sendo comum ouvir os dois
   nomes usados um pelo outro?
3. Dê um exemplo (fora de Dijkstra/Prim) de uma situação real onde `diminuir-chave` faria
   sentido, sem consultar a Teoria 02.

### Gabarito

1. Array não ordenado — `inserir` O(1) e, como nunca remove, o custo O(n) de
   `remover-mínimo` nunca é pago. Heap gastaria O(log n) em cada inserção sem necessidade,
   já que a vantagem do heap (remoção rápida) nunca seria usada.
2. Porque "fila de prioridade" é a **especificação** (quais operações existem, o que cada
   uma promete) e "heap" é **uma** estrutura de dados que cumpre essa especificação — assim
   como "lista" é um TAD e "array" ou "lista encadeada" são implementações possíveis dele.
3. Qualquer resposta razoável serve — ex.: um sistema de tickets de suporte onde a
   prioridade de um ticket já aberto muda (de "baixa" para "urgente") sem precisar fechar e
   reabrir o ticket.

## Resumo

- Fila de prioridade = TAD (interface): `inserir`, `remover-mínimo/máximo`,
  `consultar-mínimo/máximo`, `diminuir-chave`.
- Heap é **uma** implementação; array (ordenado ou não) é outra — cada uma com um perfil de
  custo diferente (Teoria 02).
- `diminuir-chave` existe como operação própria porque é comum o bastante (Dijkstra, Prim)
  para merecer um custo menor que remover+reinserir.

**Próximo:** [[Teoria 02 - Comparando implementações e por que isso decide Dijkstra e Prim]].
