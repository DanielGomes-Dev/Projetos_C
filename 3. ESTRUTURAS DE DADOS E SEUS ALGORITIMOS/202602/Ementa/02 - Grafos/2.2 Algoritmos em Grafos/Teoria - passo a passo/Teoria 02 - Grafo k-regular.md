# Teoria 02 — Testando se um grafo é k-regular

> **Onde isto entra:** aplica o conceito de grau (2.1, Teoria 03) num teste sobre o grafo
> **inteiro**: "todo mundo tem o mesmo grau?" — um padrão de algoritmo que reaparece (ver
> Teoria 03, 04: "testar uma propriedade em todo vértice/aresta").
> **Antes:** [[../../2.1 Conceitos e Representações de Grafos/Teoria - passo a passo/Teoria 03 - Adjacência, incidência, grau e ordem|2.1 Teoria 03]] · [[Teoria 01 - Contando vértices e arestas]].
> **Fonte:** representação `TG`/`TVIZ` do curso; conceito de grafo regular é padrão da
> área (não coberto explicitamente nos PDFs de aula disponíveis).

## 1. A ideia em uma frase

Um grafo é **k-regular** quando **todo** vértice tem exatamente grau `k` — nem mais, nem
menos. Testar isso é: calcular o grau de cada vértice e conferir se todos batem com `k`.

## 2. Motivação: por que "regular" importa

Grafos regulares aparecem em situações onde cada elemento precisa se conectar ao **mesmo
número** de outros — por exemplo, um ciclo (cada vértice tem exatamente 2 vizinhos, os
"vizinhos do lado") é 2-regular; um grafo completo com `n` vértices é `(n-1)`-regular
(todo vértice se liga a todos os outros). Testar k-regularidade é um exemplo de um padrão
comum: "essa propriedade vale para **todo** vértice do grafo?"

## 3. O algoritmo — lido devagar

```c
int testek(TG *g, int k) {
    for (TG *no = g; no != NULL; no = no->prox_no) {
        int grau = 0;
        for (TVIZ *v = no->prim_viz; v != NULL; v = v->prox_viz)
            grau++;
        if (grau != k)
            return 0;
    }
    return 1;
}
```

> 📖 **Lendo devagar:**
> 1. Laço de fora: para cada vértice `no` do grafo...
> 2. Laço de dentro: conto o grau de `no` (comprimento da lista de vizinhos) — igual
>    Teoria 01, mas agora **por vértice**, não somado.
> 3. `if (grau != k) return 0;` — assim que **um único** vértice não bater com `k`, já
>    posso responder "não é k-regular" e **parar imediatamente** (nem preciso olhar o
>    resto do grafo).
> 4. Se o laço de fora terminar **sem nenhum `return 0`**, todos os vértices bateram —
>    devolve `1`.

**Padrão importante:** "existe algum vértice que viole a propriedade?" → assim que **achar
um**, retorna a resposta negativa na hora (não precisa guardar nada, não precisa terminar
o laço). Só se **nenhum** violar é que se chega ao `return 1` no final.

## 4. Conferindo com número concreto — um ciclo de 4 vértices

Grafo: `1-2, 2-3, 3-4, 4-1` (ciclo).

| Vértice | Vizinhos | Grau |
|---|---|---|
| 1 | `[2, 4]` | 2 |
| 2 | `[1, 3]` | 2 |
| 3 | `[2, 4]` | 2 |
| 4 | `[3, 1]` | 2 |

`testek(g, 2)`: percorre 1 (grau 2 = k, continua), 2 (grau 2 = k, continua), 3, 4 — nenhum
diverge → devolve **1**. `testek(g, 3)`: já no vértice 1 (`grau 2 ≠ 3`) → devolve **0**
imediatamente, sem olhar 2, 3, 4.

**E se eu adicionar a aresta `{1,3}` (uma diagonal)?** Agora `1` e `3` passam a ter grau 3,
mas `2` e `4` continuam com grau 2 — o grafo **deixa de ser regular** para qualquer `k`
(nem todo mundo é 2, nem todo mundo é 3).

## 5. Letra miúda

**Grafo vazio (`g == NULL`) e `testek`:** o laço `for (TG *no = g; ...)` nunca executa
(não há `no` pra processar) — o código cai direto no `return 1` **por vacuidade**: não
existe nenhum vértice que viole a propriedade `k`, então "todo vértice tem grau k" é
tecnicamente verdadeiro (não há contraexemplo). Isso é uma convenção lógica comum
("universalmente verdadeiro sobre um conjunto vazio"), não um erro do código.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `if (grau != k) return 0;` dentro do laço | uso o vértice atual como **contraexemplo** assim que ele aparece — corte antecipado (não preciso olhar o resto) |
| `return 1` só depois do laço inteiro | só afirmo "vale para todos" depois de checar **de fato** todos, sem exceção |
| grafo vazio → `return 1` | trato "nenhum vértice viola" como verdadeiro quando não há vértice nenhum pra violar |

## 7. Exercícios de fixação

1. Um grafo tem vértices com graus `[3, 3, 3, 2]`. Ele é 3-regular? É `k`-regular para
   algum `k`?
2. Reescreva mentalmente o trace de `testek` para o grafo do item 1 com `k=3`: em qual
   vértice o código descobre que não é regular?
3. Por que `testek` **não precisa** saber quantas arestas o grafo tem para responder?
4. Um grafo completo com 5 vértices (todo par ligado) é k-regular para qual valor de `k`?

### Gabarito

1. Não é 3-regular (o último vértice tem grau 2, não 3). Não é k-regular para nenhum `k`
   — os graus não são todos iguais entre si.
2. No 4º vértice da lista (o que tem grau 2), assumindo que os 3 primeiros (grau 3) já
   passaram sem disparar o `return 0`.
3. Porque `testek` olha o **grau de cada vértice individualmente** (comprimento de cada
   lista de vizinhos) — nunca precisa somar nem dividir por 2 como em `na` (Teoria 01);
   o total de arestas não entra na lógica.
4. `k = 4` — com 5 vértices e todos ligados entre si, cada vértice se conecta aos outros
   4 (`n - 1 = 5 - 1 = 4`).

## Resumo

- k-regular: **todo** vértice tem grau exatamente `k`.
- Algoritmo: percorre vértices, calcula grau de cada um, corta assim que um diverge de
  `k`; só afirma "sim" depois de checar todos sem exceção.
- Grafo vazio é k-regular por vacuidade (não há contraexemplo possível).

**Próximo:** [[Teoria 03 - Verificando uma coloração válida]].
