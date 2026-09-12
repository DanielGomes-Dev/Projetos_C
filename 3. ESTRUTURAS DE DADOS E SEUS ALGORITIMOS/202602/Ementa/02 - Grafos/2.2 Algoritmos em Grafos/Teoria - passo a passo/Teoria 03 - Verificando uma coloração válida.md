# Teoria 03 — Verificando se uma coloração de grafo é válida

> **Onde isto entra:** primeiro algoritmo que precisa **combinar** informação de dois
> vértices diferentes (o vértice e cada um de seus vizinhos) para decidir algo — mais rico
> que os testes "olhe cada vértice sozinho" das Teorias 01–02.
> **Antes:** [[Teoria 02 - Grafo k-regular]].
> **Fonte:** exercício da lista04-EDA (Q3); coloração de grafos é conceito clássico da
> área (não coberto explicitamente nos PDFs de aula disponíveis — ver nota no README do
> subtópico).

## 1. A ideia em uma frase

"Colorir" um grafo é atribuir uma cor (aqui, um número) a cada vértice. A coloração é
**válida** quando **nenhum par de vizinhos** tem a mesma cor — é o problema por trás de
"pintar um mapa sem dois países vizinhos da mesma cor".

## 2. Motivação: por que "vizinhos com cor diferente" é útil

Pense em atribuir horários de prova: se dois alunos vizinhos num grafo de "fazem a mesma
matéria" não podem ter o mesmo horário de prova (conflito), colorir o grafo = atribuir
horários; validar a coloração = checar que nenhum conflito escapou.

## 3. O algoritmo — lido devagar

```c
int nao_tem_mesma_cor(TG *g) {
    for (TG *u = g; u != NULL; u = u->prox_no) {
        for (TVIZ *v = u->prim_viz; v != NULL; v = v->prox_viz) {
            TG *pv = busca_no(g, v->id_viz);
            if (pv && pv->cor == u->cor)
                return 0;
        }
    }
    return 1;
}
```

> 📖 **Lendo devagar:**
> 1. Laço de fora: para cada vértice `u` do grafo...
> 2. Laço de dentro: para cada vizinho `v` (guardado só como `id_viz`, um número) na lista
>    de `u`...
> 3. `busca_no(g, v->id_viz)` — o vizinho está guardado só pelo **número**, não pelo
>    ponteiro pro nó completo. Preciso "traduzir" esse número de volta para o nó real
>    (`pv`) pra poder consultar o campo `cor` dele.
> 4. `if (pv && pv->cor == u->cor) return 0;` — se achei o vizinho **e** a cor dele é
>    igual à de `u`, achei um conflito: dois vizinhos com a mesma cor. Retorna 0 na hora.
> 5. Se terminar os dois laços sem nenhum conflito, devolve `1`.

## 4. Conferindo com número concreto

Triângulo `1-2-3-1`, cores: `1→0, 2→1, 3→2` (três cores distintas).

> **Trace parcial:** `u=1` (cor 0). Vizinho `2` (cor 1) — `0 ≠ 1`, sem conflito. Vizinho
> `3` (cor 2) — `0 ≠ 2`, sem conflito. `u=2` (cor 1). Vizinho `1` (cor 0) — sem conflito.
> Vizinho `3` (cor 2) — sem conflito. `u=3`: mesma coisa. Termina sem nenhum `return 0` →
> devolve **1** (coloração válida).

Agora mude: `1→0, 2→0` (mesma cor), `3→1`.

> **Trace:** `u=1` (cor 0). Vizinho `2` (cor 0) — `0 == 0` → **conflito!** `return 0`
> imediatamente — nem chega a olhar o vizinho `3` de `1`, nem os outros vértices.

## 5. Letra miúda

**Cada aresta é checada duas vezes** (uma como `u=1,v=2` e outra como `u=2,v=1`, já que a
representação guarda a aresta nos dois sentidos — 2.1, Teoria 06) — isso não muda o
resultado (se há conflito, ele aparece nos dois sentidos), só o custo: o comentário do
código original já observa isso e aceita o custo extra em nome da clareza.

**Custo de `busca_no` dentro do laço duplo:** cada chamada a `busca_no` já é O(V) sozinha
— dentro de dois laços aninhados, o custo total vira O(V·E) no pior caso. Seria possível
baixar para O(V+E) guardando as cores num vetor indexado pelo id em vez de "traduzir" o
vizinho toda vez com busca — mas o código escolhe a versão mais direta por clareza (é uma
troca de desempenho por legibilidade, aceitável na escala destes exercícios).

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `busca_no(g, v->id_viz)` | traduzo "número do vizinho" de volta para "o nó completo, com todos os campos" |
| comparar `pv->cor == u->cor` | testo a condição central de coloração válida: nenhum vizinho compartilha cor |
| retornar 0 no primeiro conflito achado | mesmo padrão de corte antecipado da Teoria 02 — não precisa continuar depois de achar 1 contraexemplo |

## 7. Exercícios de fixação

1. Um grafo com um único vértice (sem vizinhos) tem coloração válida, para qualquer cor
   que você dê a ele? Por quê?
2. Um grafo é uma aresta só, `{1,2}`, com `1→0` e `2→0`. É válido?
3. Por que o algoritmo **não** compara a cor de `u` com a cor de vértices que **não** são
   vizinhos dele?
4. Quantas cores distintas, no mínimo, são necessárias para colorir validamente um
   triângulo (3 vértices, todos vizinhos entre si)?

### Gabarito

1. Sim — sem vizinho nenhum, o laço de dentro nunca executa para esse vértice, nunca há
   chance de conflito. Vale por vacuidade, igual `testek` em grafo vazio.
2. Não — `1` e `2` são vizinhos e têm a mesma cor (`0 == 0`) → conflito, retorna 0.
3. Porque a definição de coloração válida só proíbe **vizinhos** com a mesma cor —
   vértices não-vizinhos podem compartilhar cor livremente (não há aresta entre eles pra
   causar conflito).
4. 3 cores — cada vértice é vizinho dos outros dois, então nenhum par pode compartilhar
   cor; com só 2 cores, pelo menos dois dos três vértices ficariam com a mesma cor
   (princípio da casa dos pombos).

## Resumo

- Coloração válida: nenhum par de vizinhos compartilha cor.
- Algoritmo: para cada vértice, olha cada vizinho, traduz o id de volta pro nó completo
  (`busca_no`), compara cores; corta no primeiro conflito.
- Custo O(V·E) nesta versão (por causa da busca dentro do laço duplo) — trade-off
  deliberado de clareza por desempenho.

**Próximo:** [[Teoria 04 - Testando se dois grafos são iguais]].
