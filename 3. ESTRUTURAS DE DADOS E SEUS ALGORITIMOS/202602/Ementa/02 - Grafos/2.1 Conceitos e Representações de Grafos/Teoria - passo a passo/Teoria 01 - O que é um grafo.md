# Teoria 01 — O que é um grafo, e pra que serve

> **Onde isto entra:** primeira ideia do módulo. Grafo é a estrutura mais geral do curso —
> árvore (módulo 01) é um caso particular de grafo (sem ciclo, conectado).
> **Antes:** nenhum pré-requisito de estruturas de dados.
> **Fonte:** `ListasExercicios/lista04-EDA/07_Grafos_2026_08_27.pdf`, págs. 2–14 (slides da
> Profa. Vanessa Braganholo).

## 1. A ideia em uma frase

Um grafo é um conjunto de **pontos** (vértices) e um conjunto de **ligações** entre pares
desses pontos (arestas) — sem hierarquia obrigatória, sem "quem é pai de quem".

## 2. De onde vem a necessidade (motivação antes da definição)

Árvore (módulo 01) já modelava relações — mas só relações **hierárquicas** (um pai, vários
filhos, sem ciclo). Muita coisa do mundo real não é hierárquica: uma malha de estradas não
tem "cidade raiz"; numa rede social, A pode seguir B e B pode seguir A de volta, formando um
ciclo. Grafo é a estrutura que sobra quando você tira a exigência de hierarquia de uma
árvore — qualquer vértice pode se ligar a qualquer outro, em qualquer configuração.

O PDF (págs. 4–12) mostra vários exemplos reais antes de qualquer definição formal:

| Aplicação | Vértices são... | Arestas são... |
|---|---|---|
| Grade curricular | disciplinas | pré-requisitos entre elas |
| Rotas de voo | aeroportos | rotas diretas |
| Internet (cabos submarinos) | pontos de conexão | os próprios cabos |
| Redes sociais | pessoas | amizade/conexão |
| Processos/tarefas (caminho crítico) | tarefas | dependência entre tarefas |
| Páginas da web | páginas | links |
| Times de futebol | times | jogos entre eles num campeonato |
| Tabuleiro de xadrez | casas | "uma peça pode ir de x a y num movimento" |

Repare no padrão: **o mesmo grafo abstrato** serve para modelar situações completamente
diferentes — o que muda é só o significado que você dá a vértice e aresta.

## 3. A definição formal — lida devagar

O PDF (pág. 14) define:

> Um grafo **G** é representado por um conjunto (não vazio) **V** de vértices e um conjunto
> (possivelmente vazio) **E** de arestas (*edges*): **G = (V, E)**.
> **|V|** é a quantidade de vértices de G. **|E|** é a quantidade de arestas de G.

> 📖 **Lendo devagar:**
> 1. `G = (V, E)` — o grafo inteiro é **o par** desses dois conjuntos; não é só os vértices,
>    nem só as arestas, é a combinação dos dois.
> 2. "V não vazio" — todo grafo tem **pelo menos um vértice** (não existe grafo sem
>    nenhum ponto).
> 3. "E possivelmente vazio" — um grafo **pode** ter vértices sem nenhuma aresta entre
>    eles (pontos "soltos", sem ligação nenhuma) — isso ainda é um grafo válido.
> 4. `|V|`, `|E|` — a barra vertical dupla é notação de "quantidade de elementos do
>    conjunto": `|V|` não é o conjunto V, é **o número** de vértices que ele tem.

### Conferindo com o grafo do slide

O PDF usa este grafo de exemplo (pág. 3, 6 vértices):

```
        1
       / | \
      4--+--2
     /|\ | /|
    5 | \|/ 6
      3--/
```

(arestas visíveis no slide: {1,4}, {1,2}, {1,3}, {4,2}, {4,5}, {4,6}, {2,3}, {2,5} — o
desenho exato tem linhas cruzando; o que importa aqui é: 6 vértices, cada um numerado.)

**Conferindo:** `V = {1, 2, 3, 4, 5, 6}`, então `|V| = 6`. Contando as arestas visíveis no
desenho: 8 arestas, então `|E| = 8`. `G = (V, E)` é só o par `({1,2,3,4,5,6}, {essas 8
arestas})`.

## 4. Grafo valorado (ponderado) — uma variação comum

O PDF (pág. 23) apresenta uma variação: um grafo é **valorado** se tiver valores (pesos)
associados às arestas e/ou vértices. Exemplo do próprio slide: num grafo de rotas de voo,
cada aresta pode carregar a **distância** entre os dois aeroportos que ela conecta — o
grafo já não diz só "existe rota", diz também "quanto custa essa rota".

## 5. Letra miúda

**"Conjunto" de arestas, não "lista"** — isso importa porque, formalmente, não existe
"aresta duplicada" nem "ordem entre arestas" na definição — são detalhes que aparecem só
na hora de **representar** o grafo em código (Teoria 05/06), não na definição matemática.

## 6. 📌 O que você está REALMENTE fazendo (ao modelar algo como grafo)

| O passo mecânico | O que ele realmente é |
|---|---|
| "quem são as entidades?" | decido o conjunto V |
| "quais pares de entidades se relacionam?" | decido o conjunto E |
| "a relação tem um valor associado?" | decido se o grafo é valorado |

## 7. Exercícios de fixação

1. Modele "amizade no Facebook" como grafo: quem são os vértices? O que são as arestas?
2. No exemplo do tabuleiro de xadrez (pág. 12 do PDF): se um cavalo está na casa `x` e pode
   se mover para as casas `y1, y2, y3` num único movimento, quantas arestas saem de `x`
   nesse grafo?
3. Um grafo com `V = {a, b, c}` e `E = {}` (conjunto vazio) é um grafo válido? Por quê?
4. Dê um exemplo (fora da lista do PDF) de uma situação que você modelaria com grafo
   valorado, e diga o que o peso representaria.

### Gabarito

1. Vértices = pessoas; arestas = pares de pessoas que são amigas uma da outra.
2. 3 arestas — uma para cada casa alcançável num movimento (`{x,y1}, {x,y2}, {x,y3}`, ou
   `(x,y1), (x,y2), (x,y3)` se for direcionado — ver Teoria 02).
3. Sim — a definição só exige V não vazio; E pode ser vazio (três pontos soltos, sem
   nenhuma ligação, ainda é um grafo).
4. Exemplo: mapa de cidades (vértices) e estradas (arestas), com peso = distância em km, ou
   tempo estimado de viagem.

## Resumo

- Grafo `G = (V, E)`: conjunto de vértices + conjunto de arestas (pares de vértices).
- `|V|` = número de vértices, `|E|` = número de arestas.
- E pode ser vazio; V nunca pode.
- Grafo valorado (ponderado): arestas e/ou vértices carregam um valor extra além da
  conexão.

**Próximo:** [[Teoria 02 - Grafo orientado (digrafo) vs. não orientado]].
