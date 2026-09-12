# Teoria 06 — Representando um grafo em C (a struct usada neste curso)

> **Onde isto entra:** a Teoria 05 mostrou 4 representações em abstrato; aqui é o código
> real usado nos exercícios da lista04, que você vai reaproveitar/adaptar em toda questão.
> **Antes:** [[Teoria 05 - Representações físicas (matriz e lista)]] · struct e ponteiros
> (KR, se precisar revisar).
> **Fonte:** `ListasExercicios/lista04-EDA/TG/TG.h` e `TG.c` (código do curso, testado nas
> questões Q1–Q5 da lista04-EDA).

## 1. A ideia em uma frase

O grafo deste curso é representado como uma **lista ligada de vértices**, onde cada
vértice guarda, por sua vez, uma **lista ligada de vizinhos** — é uma lista de adjacência
(Teoria 05), mas implementada como "lista dentro de lista", sem usar array nenhum.

## 2. Por que essa forma específica (não é a única possível)

A Teoria 05 disse que lista de adjacência pode ser guardada em "vetor de listas" ou "lista
encadeada pura". Este curso escolhe a segunda: **nem os vértices são um array** — são eles
mesmos uma lista ligada. Vantagem: não precisa saber de antemão quantos vértices o grafo
vai ter (cresce sob demanda, com `malloc`, igual árvore binária no módulo 01). Custo:
achar um vértice específico exige percorrer a lista de vértices (O(V)) — não há acesso
direto por índice como haveria com array.

## 3. As duas structs — lidas pedaço por pedaço

```c
typedef struct viz {
    int id_viz;
    struct viz *prox_viz;
} TVIZ;

typedef struct grafo {
    int id_no;
    TVIZ *prim_viz;
    struct grafo *prox_no;
} TG;
```

> 📖 **Lendo `TVIZ` (um nó da lista de vizinhos):**
> 1. `id_viz` — o identificador do vértice vizinho (não é um ponteiro para o vértice, é só
>    o **número/nome** dele).
> 2. `prox_viz` — ponteiro para o próximo vizinho na lista (auto-referência, igual lista
>    encadeada comum).

> 📖 **Lendo `TG` (um nó da lista de vértices — o "grafo" é a cadeia inteira desses nós):**
> 1. `id_no` — o identificador deste vértice.
> 2. `prim_viz` — ponteiro para o **início da lista de vizinhos** deste vértice (um `TVIZ`).
>    Se o vértice não tem vizinho nenhum, `prim_viz = NULL`.
> 3. `prox_no` — ponteiro para o **próximo vértice** do grafo (não confundir com
>    `prim_viz`: um anda pela lista de vértices, o outro anda pela lista de vizinhos de
>    *um* vértice).

**A estrutura toda é acessada por um único ponteiro** — o primeiro `TG*` da cadeia. Andar
por `prox_no` visita todos os vértices; para cada um, andar por `prim_viz`/`prox_viz`
visita todos os seus vizinhos.

## 4. Construindo um grafo concreto, passo a passo

Grafo do exercício Q1 da lista04 (5 vértices, arestas `1-2, 1-3, 2-3, 3-4, 4-5`):

```c
TG *g = TG_inicializa();          // g = NULL (grafo vazio)
for (int i = 5; i >= 1; i--)
    g = TG_ins_no(g, i);          // insere 5, depois 4, 3, 2, 1
TG_ins_aresta(g, 1, 2);
TG_ins_aresta(g, 1, 3);
TG_ins_aresta(g, 2, 3);
TG_ins_aresta(g, 3, 4);
TG_ins_aresta(g, 4, 5);
```

> **Tabela de trace — o que existe depois de cada bloco:**
>
> | Linha | O que existe depois |
> |---|---|
> | `TG_inicializa()` | `g = NULL` |
> | laço `TG_ins_no` (5→1) | lista de vértices `1 → 2 → 3 → 4 → 5` (cada `TG_ins_no` **insere no início**, por isso inserir 5,4,3,2,1 nessa ordem resulta em 1 na frente) |
> | `TG_ins_aresta(g,1,2)` | vértice 1 ganha vizinho 2 **e** vértice 2 ganha vizinho 1 (ver seção 5 — a função insere nos dois sentidos) |
> | ... (demais arestas) | cada uma soma 2 entradas de vizinho (uma em cada extremidade) |

## 5. `TG_ins_aresta` — por que insere duas vezes

```c
void TG_ins_um_sentido(TG *g, int no1, int no2) {
    TG *p = TG_busca_no(g, no1);
    TVIZ *nova = (TVIZ *) malloc(sizeof(TVIZ));
    nova->id_viz = no2;
    nova->prox_viz = p->prim_viz;   // insere no INÍCIO da lista de vizinhos de no1
    p->prim_viz = nova;
}

void TG_ins_aresta(TG *g, int no1, int no2) {
    TVIZ *v = TG_busca_aresta(g, no1, no2);
    if (v) return;                  // já existe — não duplica
    TG_ins_um_sentido(g, no1, no2);
    TG_ins_um_sentido(g, no2, no1);
}
```

> 📖 **Lendo devagar:** `TG_ins_um_sentido(g, no1, no2)` só faz **metade do trabalho** —
> registra "no2 é vizinho de no1", mas não o contrário. `TG_ins_aresta` chama essa função
> **duas vezes**, trocando a ordem dos argumentos na segunda chamada — é assim que o grafo
> **não orientado** (Teoria 02) fica representado: a aresta `{u,v}` vira duas entradas de
> lista, uma em cada direção. Isso explica por que, na lista04, `Q2 (na)` soma o grau de
> todos os vértices e **divide por 2** — cada aresta foi contada duas vezes.

## 6. Busca de vértice e de aresta — força bruta, igual árvore sem ordenação

```c
TG* TG_busca_no(TG* g, int x) {
  if ((!g) || (g->id_no == x)) return g;
  return (TG_busca_no(g->prox_no, x));
}
```

> Igual à `busca` de árvore binária genérica (módulo 01, Teoria 05): sem nenhuma ordenação
> nos vértices, é preciso percorrer a lista até achar ou esgotar — O(V) no pior caso.

## 7. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| inserir vizinho no início da lista (`nova->prox_viz = p->prim_viz`) | O(1) — não preciso percorrer a lista pra inserir, só "empilho" na frente |
| `TG_ins_aresta` chamar `TG_ins_um_sentido` duas vezes | garanto que a aresta não-orientada apareça **nas duas listas de vizinhos**, uma para cada extremidade |
| `TG_busca_no` recursivo | ando pela lista de vértices até achar o `id_no` certo ou esgotar (`NULL`) |

## 8. Exercícios de fixação

1. Depois de `TG_ins_no(g, 3)` num grafo vazio, quantos vértices tem `g`? Quantos vizinhos
   tem o vértice 3?
2. Se eu chamar `TG_ins_aresta(g, 1, 2)` duas vezes seguidas, o que acontece na segunda
   chamada? (dica: releia `TG_ins_aresta` na seção 5.)
3. Por que `TG_busca_aresta(g, no1, no2)` precisa primeiro achar os dois vértices
   (`TG_busca_no`) antes de procurar a aresta entre eles?
4. Desenhe o estado da lista de vizinhos do vértice 3, depois de `TG_ins_aresta(g,1,3)` e
   `TG_ins_aresta(g,3,4)`, nessa ordem.

### Gabarito

1. 1 vértice. 0 vizinhos (`prim_viz = NULL` — acabou de ser criado, sem arestas ainda).
2. Nada muda — `TG_busca_aresta` acha que a aresta já existe (`if (v) return;`) e a função
   retorna sem inserir de novo. Evita aresta duplicada.
3. Porque a aresta é representada **dentro da lista de vizinhos de cada vértice** — sem
   achar o vértice primeiro, não tem lista de vizinhos nenhuma pra procurar.
4. `TG_ins_aresta(g,1,3)` insere `3` como vizinho de `1` **e** `1` como vizinho de `3`
   (início da lista de 3: `1 → NULL`). Depois `TG_ins_aresta(g,3,4)` insere `4` como
   vizinho de `3` **no início**, empurrando o `1` pra trás: lista de vizinhos de `3` fica
   `4 → 1 → NULL`.

## Resumo

- Grafo do curso = lista ligada de vértices (`TG`), cada um com sua própria lista ligada
  de vizinhos (`TVIZ`) — uma implementação concreta de lista de adjacência.
- `TG_ins_aresta` insere a ligação **duas vezes** (uma em cada extremidade), porque o
  grafo é não orientado.
- Toda busca (vértice ou aresta) é força bruta O(V) ou O(V+E) — não há ordenação que
  permita atalho.

---

Isso fecha a teoria de 2.1. Para ver a explicação passo a passo de cada questão resolvida
da lista, veja `Ementa/ListasExercicios/lista04-EDA/Passo a Passo Lista/` (quando
disponível), ou siga para [[../../2.2 Algoritmos em Grafos/README|2.2 Algoritmos em Grafos]].
