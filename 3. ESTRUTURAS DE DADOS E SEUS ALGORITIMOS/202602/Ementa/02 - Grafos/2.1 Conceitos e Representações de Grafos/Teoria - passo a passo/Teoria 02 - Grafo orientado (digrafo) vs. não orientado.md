# Teoria 02 — Grafo orientado (digrafo) vs. não orientado

> **Onde isto entra:** primeira "bifurcação" de tipos de grafo — muda a forma como aresta
> se escreve, e muda o significado de quase todo termo que vem depois (grau, caminho,
> conexidade).
> **Antes:** [[Teoria 01 - O que é um grafo]].
> **Fonte:** `lista04-EDA/07_Grafos_2026_08_27.pdf`, págs. 15–22.

## 1. A ideia em uma frase

Numa aresta **não orientada**, a ligação vale nos dois sentidos (se A se liga a B, B
também se liga a A). Numa aresta **orientada** (também chamada **arco**), a ligação tem
**um sentido só** — A pode apontar para B sem que B aponte de volta para A.

## 2. Por que essa distinção existe

O PDF (pág. 18) dá dois exemplos que mostram por que "sentido único" é necessário: numa
malha de transporte urbano, uma rua pode ser mão única (A→B não implica B→A). No Instagram,
"A segue B" não implica "B segue A" — são relações **assimétricas** por natureza. Se você
tentasse forçar essas situações num grafo não orientado, perderia informação real (não
saberia dizer quem segue quem, só que "existe uma conexão").

## 3. As duas notações — lidas devagar

> 📖 **Grafo não orientado:** a aresta entre `v1` e `v2` se escreve `{v1, v2}` — **chaves**,
> como conjunto. `{v1, v2}` é a mesma coisa que `{v2, v1}` (não tem ordem dentro de um
> conjunto) — é exatamente isso que captura "vale nos dois sentidos".

> 📖 **Grafo orientado (digrafo):** a aresta de `v1` para `v2` se escreve `(v1, v2)` —
> **parênteses**, como par ordenado. `(v1, v2)` é **diferente** de `(v2, v1)` — a ordem
> dentro do par importa, e é isso que captura "só vale num sentido".

### Conferindo com o exemplo do slide (pág. 16-17)

```
V = {1, 2, 3, 4, 5}
E = {(1,5), (2,3), (2,4), (3,2), (4,3), (5,2), (5,4)}
```

> **Lendo uma entrada por vez:** `(1,5)` — existe seta **saindo de 1, entrando em 5**. Note
> que **não existe** `(5,1)` no conjunto `E` — ou seja, não dá pra ir de 5 para 1
> diretamente, só de 1 para 5. Já `(2,3)` **e** `(3,2)` **ambas** aparecem — nesse par
> específico, a ligação acontece nos dois sentidos, mas isso não é regra geral do grafo,
> é só o caso desses dois vértices em particular.

O equivalente não orientado (pág. 19), com 6 vértices:

```
V = {1, 2, 3, 4, 5, 6}
E = {{1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {2,6}, {3,5}, {4,5}, {4,6}, {6,2}}
```

**Conferindo:** repare que `{2,6}` e `{6,2}` no mesmo conjunto seriam **a mesma aresta**
escrita duas vezes (chaves não têm ordem) — se ambas aparecessem, seria redundante, não
duas arestas diferentes. Compare com o caso orientado acima, onde `(2,3)` e `(3,2)` são
**duas arestas genuinamente diferentes**.

## 4. Formalizando com relação binária (pág. 22)

O PDF formaliza a diferença usando relação matemática `R`:

> **Não orientado:** `{v1, v2} ∈ E ⟺ v1 R v2 E v2 R v1` (as duas direções precisam valer).
> Exemplo: `R` = "é amigo no Facebook".
> **Orientado:** `(v1, v2) ∈ E ⟺ v1 R v2` (só uma direção precisa valer).
> Exemplo: `R` = "segue no Instagram".

> 📖 **Lendo devagar:** o "⟺" se lê "se e somente se" — dos dois lados da seta dupla, uma
> afirmação é verdadeira exatamente quando a outra também é. Para o caso não orientado,
> **preciso das duas metades** (`v1 R v2` **e** `v2 R v1`) para poder desenhar a aresta sem
> direção — é por isso que "ser amigo" (sempre mútuo) vira aresta `{}` sem seta, mas
> "seguir" (pode ser unilateral) só cabe em aresta `(...)` com seta.

## 5. Adjacência e incidência mudam de significado

O PDF (págs. 24–25) define, para cada tipo:

| Termo | Grafo não orientado | Grafo orientado |
|---|---|---|
| `v1` **adjacente** a `v2` | existe `{v1,v2}` — e então **v2 também é adjacente a v1** (simétrico) | existe `(v1,v2)` — **não implica** que v2 seja adjacente a v1 |
| aresta **incidente** | `{v1,v2}` é incidente **em** v1 e v2 (mesmo papel para os dois) | `(v1,v2)` é incidente **de** (sai de) v1 e incidente **a** (entra em) v2 — papéis diferentes |

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| escrever aresta com `{ }` | afirmo que a ligação é simétrica — não preciso guardar "quem primeiro" |
| escrever aresta com `( )` | afirmo que a ordem importa — o primeiro elemento é de onde a ligação **sai** |
| checar se `(v2,v1)` também está em E | descubro se, apesar do grafo ser orientado, **esse par específico** de vértices tem ligação nos dois sentidos |

## 7. Exercícios de fixação

Usando o digrafo do slide (`V = {1,2,3,4,5}`, `E = {(1,5), (2,3), (2,4), (3,2), (4,3),
(5,2), (5,4)}`):

1. Existe aresta de `4` para `1`? E de `1` para `4`?
2. `2` é adjacente a `3`? `3` é adjacente a `2`? Os dois ao mesmo tempo significam o quê?
3. Reescreva `E` como se o grafo fosse **não orientado** (uma única entrada por par
   conectado, sem repetir).
4. Por que "amigo no Facebook" vira grafo não orientado mas "seguir no Instagram" vira
   digrafo — em uma frase, qual é a diferença de fundo entre as duas relações?

### Gabarito

1. Não existe `(4,1)` em `E` — não há aresta de 4 para 1. Também não existe `(1,4)` — não
   há aresta de 1 para 4 (só existe `(1,5)` saindo de 1).
2. `(2,3) ∈ E` → 2 é adjacente a 3. `(3,2) ∈ E` → 3 é adjacente a 2. Como as duas valem,
   **para este par específico** a ligação é "bidirecional" — mas isso não faz o grafo
   inteiro deixar de ser um digrafo, é só uma coincidência local.
3. `{1,5}, {2,3}, {2,4}, {3,4}, {2,5}` — juntando os pares que tinham pelo menos uma
   direção e removendo duplicatas (`(2,3)`+`(3,2)` viram só `{2,3}`; `(4,3)` vira `{3,4}`;
   `(5,2)` vira `{2,5}`; `(5,4)` vira `{4,5}` — cuidado, refazendo: pares únicos são
   `{1,5}, {2,3}, {2,4}, {3,4}, {2,5}, {4,5}`).
4. Amizade é uma relação que **por definição** é mútua (se você é meu amigo, eu sou seu);
   seguir é uma **ação unilateral** — não existe uma regra da plataforma que obrigue B a
   seguir de volta quem o segue.

## Resumo

- Não orientado: aresta `{v1,v2}` (conjunto, sem ordem, sempre simétrica).
- Orientado (digrafo): aresta `(v1,v2)` (par ordenado, `(v1,v2) ≠ (v2,v1)`).
- A escolha entre os dois depende da relação sendo modelada ser ou não naturalmente mútua.

**Próximo:** [[Teoria 03 - Adjacência, incidência, grau e ordem]].
