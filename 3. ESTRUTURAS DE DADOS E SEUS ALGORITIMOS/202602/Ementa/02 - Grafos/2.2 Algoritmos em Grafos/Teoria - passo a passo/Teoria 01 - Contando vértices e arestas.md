# Teoria 01 — Contando vértices e arestas de um grafo

> **Onde isto entra:** o algoritmo mais simples possível sobre grafo — e a base de quase
> todo algoritmo maior (quase tudo precisa "andar por todos os vértices" ou "por todos os
> vizinhos" em algum momento).
> **Antes:** [[../../2.1 Conceitos e Representações de Grafos/Teoria - passo a passo/Teoria 06 - Representando um grafo em C|2.1 Teoria 06 - Representando um grafo em C]] ·
> [[../../2.1 Conceitos e Representações de Grafos/Teoria - passo a passo/Teoria 02 - Grafo orientado (digrafo) vs. não orientado|2.1 Teoria 02 - Orientado vs. não orientado]].
> **Fonte:** representação `TG`/`TVIZ` do curso (`ListasExercicios/lista04-EDA/TG/`), usada
> em todas as questões Q1–Q5 da lista04-EDA (todas constroem grafo **não orientado**, com
> `TG_ins_aresta`); e `07_Grafos_2026_09_01.pdf`, pág. 49 ("Lista de Adjacência"), que
> mostra o caso **orientado** — usado aqui de contraste.

## 1. A ideia em uma frase

Contar vértices é percorrer a **lista de vértices** contando um a um — isso não muda com o
tipo de grafo. Contar arestas já depende do tipo: em um grafo **não orientado** (como em
todas as questões desta lista, que usam `TG_ins_aresta`), cada aresta fica guardada
**duas vezes** — uma em cada extremidade — então é preciso somar o grau de cada vértice e
**dividir por 2**. Num grafo **orientado** (dígrafo), cada aresta fica guardada **uma única
vez** (na lista do vértice de onde ela sai) — a soma dos graus de saída já é a resposta
certa, **sem dividir**. A diferença não é da struct `TG` (que serve pros dois casos) — é de
**qual função de inserção você chama** ao montar o grafo.

## 2. Contando vértices — motivação antes do código

`TG` é uma lista ligada de vértices. Contar "quantos vértices existem" é o mesmo problema
de "contar quantos nós tem uma lista encadeada" — nada específico de grafo ainda, só
percorrer até `NULL`.

```c
int nn(TG *g) {
    int total = 0;
    while (g) {
        total++;
        g = g->prox_no;
    }
    return total;
}
```

> 📖 **Lendo devagar:** `while (g)` continua enquanto o ponteiro não for `NULL`. A cada
> volta, soma 1 e avança (`g = g->prox_no`). Quando `g` vira `NULL`, parou de existir
> vértice pra contar — devolve o total acumulado.

**Conferindo com um grafo pequeno:** vértices `1, 2, 3` (uma lista de 3 nós). Trace:
`total=0, g=nó1` → `total=1, g=nó2` → `total=2, g=nó3` → `total=3, g=NULL` → sai do
`while`, devolve `3`. ✔ Custo: **O(V)** — olha cada vértice uma vez, nunca olha aresta.

## 3. Contando arestas — por que (neste curso) não é só "somar os graus"

Ingenuamente, você poderia pensar: "para cada vértice, conto quantos vizinhos ele tem, e
somo tudo". Para as questões desta lista, isso **conta cada aresta duas vezes** — a aresta
não orientada `{u,v}` aparece como vizinho `v` na lista de `u`, **e** como vizinho `u` na
lista de `v` (Teoria 06 de 2.1: `TG_ins_aresta` chama `TG_ins_um_sentido` duas vezes, uma
para cada sentido).

> **Isso só vale porque o grafo é não orientado.** Compare com o slide "Lista de
> Adjacência" (`07_Grafos_2026_09_01.pdf`, pág. 49), que mostra um grafo **orientado**
> `1→2, 1→3, 2→3, 2→4, 3→4`, com estas listas:
> ```
> 1: 2 3 /
> 2: 3 4 /
> 3: 4 /
> 4: /
> ```
> Somando o tamanho de cada lista: `2 + 2 + 1 + 0 = 5` — e o grafo **tem exatamente 5
> arestas**. Não há divisão por 2 aqui: cada aresta orientada `(u,v)` só é guardada **uma
> vez**, na lista de `u` (quem ela sai), nunca na de `v` (quem ela entra) — é por isso que o
> vértice `4` (que só recebe arestas, nunca é origem de nenhuma) tem lista **vazia**, mesmo
> tendo grau de entrada 2.
>
> A função `na` abaixo (com `soma / 2`) está certa **para esta lista**, porque as questões
> Q1–Q5 constroem o grafo com `TG_ins_aresta` (não orientado). Se você precisasse contar
> arestas de um grafo **orientado** representado do mesmo jeito (com `TG_ins_um_sentido`
> chamado direto, uma vez por aresta), a função certa seria a mesma soma **sem** o `/2`.

```c
int na(TG *g) {
    int soma = 0;
    for (TG *no = g; no != NULL; no = no->prox_no) {
        for (TVIZ *v = no->prim_viz; v != NULL; v = v->prox_viz)
            soma++;
    }
    return soma / 2;
}
```

> 📖 **Lendo devagar:** o laço de fora (`for (TG *no = g; ...)`) anda pela lista de
> **vértices**. Para cada vértice, o laço de dentro (`for (TVIZ *v = no->prim_viz; ...)`)
> anda pela lista de **vizinhos daquele vértice**, somando 1 a cada um. No final, `soma`
> tem o **total de "meias-arestas"** (cada aresta real contribuiu 2 vezes) — por isso
> `soma / 2` no final.

### Conferindo com número concreto

Grafo: vértices `1,2,3`, arestas `{1,2}` e `{2,3}` (2 arestas reais).

| Vértice | Lista de vizinhos | Quantos vizinhos (contribui pra `soma`) |
|---|---|---|
| 1 | `[2]` | 1 |
| 2 | `[1, 3]` | 2 |
| 3 | `[2]` | 1 |

`soma = 1 + 2 + 1 = 4`. `na = 4 / 2 = 2`. ✔ Bate com as 2 arestas reais.

## 4. Letra miúda

**Por que `soma` é sempre par?** Porque cada aresta contribui exatamente 2 unidades pra
soma (uma em cada extremidade) — não importa a forma do grafo, a soma total dos graus é
**sempre** par. Se em algum momento você calculasse uma soma ímpar, seria sinal de bug na
inserção de arestas (uma das duas metades não foi inserida).

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| percorrer a lista de vértices, `total++` a cada um | conto O(V) elementos de uma lista — nada específico de grafo |
| somar o comprimento de todas as listas de vizinhos | conto o total de "pontas de aresta" registradas (2 por aresta, **se** o grafo for não orientado; 1 por aresta, se for orientado) |
| dividir a soma por 2 | corrijo a dupla-contagem que a escolha de representar um grafo **não orientado** introduz — só faço isso porque sei que estas questões usam `TG_ins_aresta` |

## 6. Exercícios de fixação

1. Um grafo tem vértices `1,2,3,4` sem nenhuma aresta. Quanto vale `nn`? E `na`?
2. Um grafo tem 4 vértices, cada um com grau exatamente 2 (formando um ciclo). Sem contar
   arestas diretamente, calcule `na` usando a fórmula soma-dos-graus/2.
3. Por que `nn(g)` nunca precisa olhar `prim_viz`, mas `na(g)` precisa?
4. Se eu remover uma aresta `{u,v}` de um grafo (removendo `v` da lista de `u` **e** `u` da
   lista de `v`), o que acontece com `na(g)` antes e depois?

### Gabarito

1. `nn = 4` (4 vértices existem, mesmo isolados). `na = 0` (nenhuma lista de vizinhos tem
   nada, soma = 0, `0/2 = 0`).
2. Soma dos graus = `4 vértices × grau 2 = 8`. `na = 8 / 2 = 4` — bate com um ciclo de 4
   vértices ter 4 arestas.
3. Porque `nn` só precisa saber **quantos vértices existem** (a lista de vértices já
   responde isso); `na` precisa saber **quantas ligações** existem, e ligações só aparecem
   dentro das listas de vizinhos (`prim_viz`/`prox_viz`).
4. Antes: `na` incluía essa aresta na soma. Depois de removida dos dois lados, a soma cai
   em exatamente 2 unidades (uma de cada extremidade removida) — então `na` cai em
   exatamente 1 (já dividido por 2).

## Resumo

- `nn`: percurso simples da lista de vértices, O(V).
- `na`: soma o grau (comprimento da lista de vizinhos) de todo vértice — O(V+E). **Divide
  por 2** se o grafo é não orientado (como em todas as questões desta lista, que usam
  `TG_ins_aresta` e guardam cada aresta duas vezes); **não divide** se o grafo é orientado
  (cada aresta guardada uma única vez, como no exemplo "Lista de Adjacência" do PDF).
- Soma dos graus (não orientado) é sempre par — é uma boa forma de **conferir** se a
  construção do grafo está correta.

**Próximo:** [[Teoria 02 - Grau-regularidade de um grafo]].
