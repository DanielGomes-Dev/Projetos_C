# Teoria 06 — Tipos de árvore binária: cheia, completa, perfeita

> **Onde isto entra:** são três "formatos" especiais de árvore binária que voltam a
> aparecer o curso inteiro — em particular, heap (módulo 06) **é definido** em cima do
> conceito de árvore completa.
> **Antes:** [[Teoria 05 - Percurso em largura, busca e altura]].
> **Fonte:** livros-base SZ/CE (Szwarcfiter; Celes) — os slides de aula (`04_Arvores.pdf`,
> `05_ArvoresBinarias_*.pdf`) não cobrem esses três termos especificamente; confira a
> página exata ao abrir o PDF do livro, se quiser citar em prova.

## 1. A ideia em uma frase

As três palavras descrevem **o quão "preenchida"** uma árvore binária está, cada uma com
uma régua diferente e mais rígida que a anterior.

## 2. Por que isso importa (motivação antes da definição)

Uma árvore binária "torta" (por exemplo, todo nó só com filho à direita, virando uma fila)
tem altura O(n) — perde toda vantagem de estrutura em árvore. Os três termos abaixo
descrevem formatos "bem distribuídos", que são exatamente os formatos que garantem altura
pequena (O(log n)) — é por isso que import a se a árvore é cheia/completa/perfeita: é um
jeito de **medir** o quão perto do melhor caso ela está.

## 3. As três definições — lidas devagar, uma de cada vez

> 📖 **Cheia (full):** todo nó tem **0 ou 2** filhos — nunca exatamente 1.

Conferindo: a árvore
```
       1
     /   \
    2     3
   / \
  4   5
```
é cheia? `1` tem 2 filhos ✔. `2` tem 2 filhos ✔. `3` tem 0 filhos ✔. `4` e `5` têm 0 filhos
✔. Nenhum nó tem exatamente 1 filho → **é cheia**.

Contra-exemplo: se `3` tivesse só um filho (`6`, à esquerda, por exemplo), a árvore deixaria
de ser cheia — `3` teria grau 1, violando a regra "0 ou 2".

> 📖 **Completa (complete):** todos os níveis estão preenchidos, **exceto possivelmente o
> último**, que é preenchido **da esquerda para a direita**, sem buracos.

Conferindo: a mesma árvore acima — nível 0 (`1`) cheio, nível 1 (`2,3`) cheio, nível 2
(`4,5`) preenchido da esquerda pra direita (existem `4` e `5`, mas não teria como pular e
só ter, por exemplo, um filho de `3` sem antes preencher os dois filhos de `2`) →
**é completa**.

Contra-exemplo: se o nível 2 tivesse só `4` (filho de `2`) e um filho de `3`, **pulando** o
segundo filho de `2`, isso violaria "esquerda para direita sem buraco" — não seria completa.

> 📖 **Perfeita (perfect):** **todos** os níveis totalmente preenchidos — todas as folhas na
> mesma profundidade.

A árvore do exemplo **não é perfeita** — `3` é folha no nível 1, enquanto `4` e `5` são
folhas no nível 2 (profundidades diferentes). Uma árvore perfeita com a mesma altura (2)
teria: `1` com dois filhos, cada um desses com dois filhos — 7 nós ao todo, todas as 4
folhas no nível 2.

## 4. A relação entre as três (letra miúda importante)

> **Toda árvore perfeita é completa e cheia. A recíproca não vale** — uma árvore pode ser
> completa sem ser perfeita (o exemplo da seção 3 é exatamente isso: completa, cheia, mas
> não perfeita, porque `3` "acaba cedo").

Pense nisso como três círculos um dentro do outro: perfeita ⊂ completa, e perfeita ⊂ cheia,
mas completa e cheia não implicam uma na outra em geral (embora, coincidentemente, o
exemplo acima seja os dois ao mesmo tempo).

## 5. Fórmula da árvore perfeita — conferindo com número

**Afirmação:** uma árvore perfeita de altura `h` tem exatamente `2^(h+1) − 1` nós.
**Conferindo:** árvore perfeita de altura `h = 2` (a de 7 nós mencionada acima): `2^(2+1) −
1 = 2^3 − 1 = 8 − 1 = 7`. ✔ Bate: `1` (nível 0) + `2` (nível 1) + `4` (nível 2) = 7.

**Por que essa fórmula:** cada nível `i` (contando do 0) tem exatamente `2^i` nós numa
árvore perfeita (nível 0 → 1 nó; nível 1 → 2; nível 2 → 4; ...). Somando do nível 0 até o
nível `h`: `2^0 + 2^1 + ... + 2^h = 2^(h+1) − 1` (soma de progressão geométrica de razão 2).

## 6. 📌 O que você está REALMENTE verificando

| O passo mecânico | O que ele realmente é |
|---|---|
| checar "todo nó tem 0 ou 2 filhos" | testando se existe algum "desperdício de galho" (nó com 1 filho só) — cheia |
| checar "último nível preenchido da esquerda pra direita" | testando se dá pra guardar a árvore num **array sem buracos** (é exatamente a representação de heap, módulo 06) — completa |
| checar "todas as folhas na mesma profundidade" | testando o caso **mais balanceado possível** para uma dada altura — perfeita |

## 7. Exercícios de fixação

1. Uma árvore com um único nó (sem filhos) é cheia? É completa? É perfeita?
2. Desenhe uma árvore binária que seja **completa mas não cheia**. (Dica: pense em um nível
   incompleto onde algum nó do penúltimo nível tem só 1 filho.)
3. Quantos nós tem uma árvore perfeita de altura `h = 3`?
4. Por que "completa" é a propriedade que interessa para representar heap em array (mais
   adiante, no módulo 06), e não "cheia" nem "perfeita"?

### Gabarito

1. Sim às três — um nó único tem grau 0 (não é "exatamente 1", então cheia ✔), o único
   nível existente está totalmente preenchido (completa ✔), e a única folha (o próprio nó)
   está na única profundidade que existe (perfeita ✔). Caso base de todas as três.
2. Exemplo: raiz `1` com filhos `2` e `3`; `2` tem só o filho esquerdo `4` (`2` tem grau 1,
   então **não é cheia**), mas o nível 2 está preenchido da esquerda pra direita (só falta
   o que viria depois de `4`, e como é o último nível, tudo bem) → completa, não cheia.
3. `2^(3+1) − 1 = 2^4 − 1 = 16 − 1 = 15` nós.
4. Porque "completa" é exatamente a garantia de "sem buracos, preenchido da esquerda pra
   direita" — a mesma garantia que permite calcular a posição de pai/filho por aritmética
   de índice num array, sem guardar ponteiro nenhum (você vê isso em detalhe no módulo 06).
   "Cheia" não diz nada sobre *onde* estão os buracos (podia ter buraco no meio, só não
   pode ter grau 1). "Perfeita" é rígida demais — exigiria que o número de nós fosse sempre
   `2^(h+1) − 1` exato, o que quase nunca acontece na prática.

## Resumo

- **Cheia**: todo nó tem 0 ou 2 filhos (nunca 1).
- **Completa**: níveis preenchidos, exceto possivelmente o último, que enche da esquerda
  pra direita sem buraco — é a propriedade que permite representar a árvore num array.
- **Perfeita**: todos os níveis 100% cheios; todas as folhas na mesma profundidade; tem
  exatamente `2^(h+1) − 1` nós para altura `h`.
- Perfeita ⟹ completa e cheia; as recíprocas não valem.

---

Isso fecha a teoria de 1.1. Próximo passo: os exemplos e exercícios da lista (ver
`Ementa/ListasExercicios/lista01-EDA/Passo a Passo Lista/`, quando disponível), ou seguir
para [[../../1.2 Árvores Binárias de Busca/README|1.2 Árvores Binárias de Busca]].
