# Q4 — Testar se o grafo é k-regular (`testek`)

> **Origem:** `lista04-EDA.pdf`, questão 4 · **Código resolvido:** [[../Q4/claude/main.c]]
> **Antes disto, veja:** [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 02 - Grafo k-regular|2.2 Teoria 02]]

## 1. O que o exercício pede

> "verificar se o grafo, passado como parâmetro de entrada, possui todos os nós com grau
> igual a k: `int testek(TG *g, int k)`."

Ou seja: percorrer todo o grafo e confirmar que **nenhum** vértice tem grau diferente de
`k`. Um grafo assim é chamado **k-regular**.

## 2. A ideia geral (o mapa antes da viagem)

- Este é o primeiro exercício da lista que precisa **parar assim que achar um
  contraexemplo** — diferente de Q1/Q2 (que sempre percorrem tudo), aqui basta **um** vértice
  com grau errado para a resposta já ser "não".
- Estratégia: para cada vértice, contar o grau (comprimento da lista de vizinhos) e
  comparar com `k`; na primeira divergência, retorna `0` imediatamente.
- Por que funciona: "todo vértice tem grau k" é uma afirmação **universal** — basta um
  contraexemplo para derrubá-la, então o algoritmo pode parar cedo (curto-circuito).

## 3. Resolução passo a passo

### Passo 1 — contar o grau de cada vértice e comparar

```c
int testek(TG *g, int k) {
    for (TG *no = g; no != NULL; no = no->prox_no) {
        int grau = 0;
        for (TVIZ *v = no->prim_viz; v != NULL; v = v->prox_viz)
            grau++;
        if (grau != k)          /* achei um no fora do padrao */
            return 0;
    }
    return 1;                   /* todos os nos tem grau k    */
}
```

> 📖 **Lendo devagar:** o laço de fora anda pelos vértices (igual `nn`, Q1). Para cada um,
> o laço de dentro conta o grau do zero (igual a metade de `na`, Q2 — só que **sem**
> acumular numa soma global, porque aqui cada vértice é julgado **sozinho**). `if (grau !=
> k) return 0;` é o curto-circuito: no primeiro vértice errado, a função já termina — não
> precisa checar o resto.

### Passo 2 — trace no ciclo de 4 nós (`1-2, 2-3, 3-4, 4-1`)

| Vértice | Grau | `grau != k` (com `k=2`)? |
|---|---|---|
| 1 | 2 | não — continua |
| 2 | 2 | não — continua |
| 3 | 2 | não — continua |
| 4 | 2 | não — continua |

Percorreu tudo sem achar divergência → `testek(g, 2) = 1`. ✔ (é um ciclo, todo vértice tem
exatamente 2 vizinhos).

### Passo 3 — depois de adicionar a aresta `1-3` (diagonal)

Agora `1` e `3` ganham mais um vizinho (grau 3), enquanto `2` e `4` continuam com grau 2.

| Vértice | Grau | `testek(g, 2)`: `grau != 2`? |
|---|---|---|
| 1 | 3 | **sim** → retorna `0` imediatamente |

A função nem chega a olhar `2`, `3`, `4` — o curto-circuito age no primeiro vértice
(`1`, que foi inserido por último e fica na frente da lista, já que `TG_ins_no` insere no
início). `testek(g, 2) = 0` e `testek(g, 3) = 0` também (nem todos têm grau 3 — `2` e `4`
continuam com grau 2).

## 4. Resultado final

`testek(g, 2) = 1` antes da diagonal, `0` depois. `testek(NULL, k) = 1` para qualquer `k`
— **verdadeiro por vacuidade**: sem nenhum vértice, não existe nenhum que viole a condição.

**Conferindo:** essa é a mesma convenção lógica de "para todo elemento de um conjunto vazio,
qualquer afirmação é verdadeira" — não é um caso especial tratado à parte no código, é
consequência direta do laço `for` nunca executar quando `g == NULL`.

## 5. Habilidades necessárias

- [ ] Contar o grau de um vértice (comprimento da lista de vizinhos) → [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 01 - Contando vértices e arestas|2.2 Teoria 01]]
- [ ] Reconhecer e aplicar curto-circuito numa afirmação universal → [[../../../02 - Grafos/2.2 Algoritmos em Grafos/Teoria - passo a passo/Teoria 02 - Grafo k-regular|2.2 Teoria 02]]

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — um único vértice, sem arestas

Vértice `1`, sem vizinhos. `grau(1) = 0`. `testek(g, 0) = 1` (bate). `testek(g, 1) = 0`
(grau real é 0, não 1).

### Aquecimento 2 — dois vértices ligados por uma aresta

`1-2`. Ambos com grau 1. `testek(g, 1) = 1`. Qualquer outro `k` dá `0` no primeiro vértice
checado.
