# Teoria 04 — Caminho, conectividade, completude, laço e ciclo

> **Onde isto entra:** vocabulário para descrever "como se anda" dentro de um grafo — base
> para qualquer algoritmo de busca (fora do escopo desta subpasta, ver 2.2).
> **Antes:** [[Teoria 03 - Adjacência, incidência, grau e ordem]].
> **Fonte:** `lista04-EDA/07_Grafos_2026_08_27.pdf`, págs. 29–36.

## 1. A ideia em uma frase

Um **caminho** é uma sequência de vértices ligados um ao próximo por arestas reais do
grafo. Todo o resto desta teoria (alcançável, conectado, ciclo) é construído em cima dessa
ideia.

## 2. Caminho — lido devagar

O PDF (pág. 29) define: "o caminho de tamanho k entre v1 e v2 é a sequência `⟨v0, v1, ...,
vk⟩`, onde `v0 = v1` (início), `vk = v2` (fim), e `(vi-1, vi) ∈ E` para `i = 1..k`."

> 📖 **Lendo devagar:** o "tamanho k" do caminho é o número de **arestas** usadas (não o
> número de vértices — um caminho com k arestas tem k+1 vértices, contando repetições se
> houver). A condição `(vi-1, vi) ∈ E` diz: cada passo da sequência **precisa ser uma
> aresta que realmente existe** no grafo — não vale "pular" para um vértice não-adjacente.

### Conferindo com o exemplo do slide (pág. 29)

Grafo com vértices `1,2,3,4,5` e arestas incluindo `{1,3}`, `{1,2}`, `{2,3}`:

> **Caminho de tamanho 1 entre 1 e 3:** usa só a aresta `{1,3}` diretamente. Vértices:
> `{1,3}`. Arestas: `{{1,3}}`.
> **Caminho de tamanho 2 entre 1 e 3:** passa por um vértice intermediário. Vértices:
> `{1,2,3}`. Arestas: `{{1,2}, {2,3}}` — dois passos em vez de um, mesmo destino final.

**O que isso mostra:** pode existir **mais de um caminho** entre o mesmo par de vértices,
com tamanhos diferentes — diferente de árvore (módulo 01), onde o caminho entre raiz e
qualquer nó é **único**.

## 3. Alcançável e caminho simples (pág. 30)

> **Alcançável:** se existe **algum** caminho de `v1` até `v2`, dizemos que `v2` é
> alcançável a partir de `v1`. Em digrafo, isso é **assimétrico** — o slide mostra o
> exemplo: "3 é alcançável a partir de 4" mas "2 **não** é alcançável a partir de 1" (as
> setas do digrafo não permitem o caminho de volta).
> **Caminho simples:** todos os vértices da sequência são distintos (não repete nenhum).

## 4. Conectado, completo, laço, ciclo, acíclico, simétrico — lidos um a um

> 📖 **Conectado** (pág. 31): existe caminho ligando **cada par** de vértices. O slide
> mostra dois desenhos lado a lado: um conectado (dá pra ir de qualquer vértice a
> qualquer outro) e um não-conectado (existem "ilhas" separadas, sem caminho entre elas).

> 📖 **Completo** (pág. 32): todos os pares de vértices são adjacentes — ou seja, **toda
> aresta possível existe**. Um grafo completo com `n` vértices tem o máximo de arestas
> possível para aquele número de vértices.

> 📖 **Laço** (pág. 33): uma aresta que liga um vértice **a ele mesmo** (`{v1,v1}`). É um
> caso especial — a maioria dos algoritmos do curso assume grafo **sem laço** (chamado
> "grafo simples"), a menos que se diga o contrário.

> 📖 **Ciclo** (pág. 34): um caminho `⟨v0, v1, ..., vk⟩` onde `v0 = vk` (volta pro início)
> **e** o caminho contém pelo menos uma aresta (não conta "ficar parado"). Exemplo do
> slide: `v1 → v2 → v4 → v5 → v3 → v1` fecha um ciclo porque começa e termina em `v1`.

> 📖 **Acíclico** (pág. 35): um grafo **sem nenhum ciclo**. O slide mostra três grafos:
> um cíclico e dois acíclicos — repare que "acíclico" não exige que o grafo seja
> desconectado nem "pobre em arestas", só que nenhuma sequência de arestas feche um laço
> voltando ao vértice de origem.

> 📖 **Simétrico** (pág. 36): um digrafo é simétrico se, para toda aresta `(v,w)`, também
> existe `(w,v)`. Isso é diferente de "grafo não orientado" — um digrafo simétrico **tem**
> as duas setas explicitamente, enquanto um grafo não orientado nem precisa da noção de
> seta (ver Teoria 02).

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| seguir arestas reais de vértice em vértice | construo um caminho — cada passo tem que ser uma aresta que existe |
| checar se dá pra ir de qualquer um a qualquer outro | testo se o grafo é conectado |
| checar se um caminho fecha voltando ao início | testo se existe ciclo |
| checar se toda aresta possível já existe | testo se o grafo é completo |

## 6. Exercícios de fixação

1. Num grafo com vértices `{a,b,c}` e arestas `{{a,b},{b,c},{a,c}}`, o grafo é completo?
   Justifique.
2. Dê um exemplo de caminho de tamanho 3 num grafo linear `1-2-3-4` (arestas `{1,2},
   {2,3}, {3,4}`).
3. Um grafo tem duas "ilhas" de vértices, sem nenhuma aresta ligando uma à outra. Ele é
   conectado? E completo?
4. Um triângulo `a-b-c-a` (arestas `{a,b},{b,c},{c,a}`) tem ciclo? Qual é o caminho que
   forma esse ciclo?

### Gabarito

1. Sim — com 3 vértices, o máximo de arestas possíveis (sem laço, sem repetir) é 3 (todo
   par distinto ligado), e as 3 já existem: `{a,b}`, `{b,c}`, `{a,c}`. Todos os pares são
   adjacentes → completo.
2. `⟨1,2,3,4⟩` — usa as arestas `{1,2}, {2,3}, {3,4}`, 3 arestas = tamanho 3, do vértice 1
   até o vértice 4.
3. Não é conectado (não existe caminho entre as duas ilhas). Também não é completo (falta
   pelo menos a aresta entre qualquer vértice de uma ilha e qualquer vértice da outra) —
   um grafo pode falhar em ser conectado e completo ao mesmo tempo, não são opostos um do
   outro.
4. Sim — `⟨a, b, c, a⟩` começa e termina em `a`, usa 3 arestas reais (`{a,b}, {b,c}, {c,a}`)
   e tem pelo menos uma aresta, o que satisfaz a definição de ciclo.

## Resumo

- Caminho: sequência de vértices ligados por arestas reais; "tamanho" conta arestas.
- Alcançável: existe algum caminho (pode ser assimétrico em digrafo).
- Conectado: existe caminho entre **todo** par de vértices.
- Completo: **toda** aresta possível existe (todo par é adjacente).
- Laço: aresta de um vértice para ele mesmo. Ciclo: caminho que volta ao início. Acíclico:
  sem ciclo nenhum.

**Próximo:** [[Teoria 05 - Representações físicas (matriz e lista)]].
