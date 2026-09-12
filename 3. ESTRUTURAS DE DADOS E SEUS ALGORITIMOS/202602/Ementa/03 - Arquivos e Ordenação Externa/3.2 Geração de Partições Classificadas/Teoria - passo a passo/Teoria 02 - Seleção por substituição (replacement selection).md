# Teoria 02 — Seleção por substituição (replacement selection)

> **Onde isto entra:** a geração simples (Teoria 01) sempre produz `⌈N/M⌉` partições. Esta
> técnica produz, **em média, metade** disso — menos partições para intercalar depois (3.3).
> **Antes:** [[Teoria 01 - Por que ordenar em disco é diferente, e a geração simples de partições]] ·
> heap mínimo (módulo `06 - Heaps e Listas de Prioridade`, 6.1 — se ainda não viu heap,
> a ideia de "sempre tirar o menor rapidamente" é o que importa aqui).
> **Fonte:** SZ (Szwarcfiter) — capítulo de Ordenação Externa. Exemplo numérico é construção
> própria para ilustrar o método do livro.

## 1. A ideia em uma frase

Em vez de "encher a memória, ordenar, descarregar" em blocos fixos, mantém-se um **heap
mínimo** em RAM e vai-se escrevendo o menor elemento disponível a cada passo — o que, com
uma regra simples, permite que uma partição cresça **além** do tamanho da memória.

## 2. De onde vem a ideia (motivação)

Na geração simples, o tamanho da partição está travado em `M` porque o algoritmo "esquece"
tudo assim que descarrega um bloco. Mas pense: se eu já escrevi o valor `8` como o último
elemento da partição atual, e o próximo valor lido do arquivo é `12` — esse `12` **ainda
serve** para a partição atual (`12 ≥ 8`, mantém a ordem)! Só precisaria começar uma partição
nova se o próximo valor lido fosse **menor** que o último escrito. A seleção por
substituição explora exatamente essa observação.

## 3. O algoritmo — lido devagar

> 📖 **Passo a passo do método:**
> 1. Mantém-se um **heap mínimo ativo** com até `M` registros.
> 2. Repetidamente: remove-se o **menor** do heap ativo, escreve-se na partição de saída
>    atual, e guarda-se esse valor como `último_escrito`.
> 3. Lê-se o próximo registro do arquivo de entrada:
>    - Se ele é **≥ último_escrito** → ainda serve pra partição atual → entra no heap ativo.
>    - Se ele é **< último_escrito** → quebraria a ordem da partição atual → fica
>      "congelado", esperando a **próxima** partição.
> 4. Quando o heap ativo esvazia (só sobraram congelados), a partição atual é fechada; os
>    congelados viram o heap ativo da próxima partição, e `último_escrito` volta a −∞.

## 4. Conferindo com número concreto (mesma entrada da Teoria 01)

Entrada: `6, 2, 9, 4, 1, 8, 12, 3, 10, 5, 7, 11` (na ordem lida), `M = 3`.

**Inicialização:** os 3 primeiros valores entram no heap ativo → `{2, 6, 9}`; congelados =
`{}`; `último_escrito = -∞`.

| Passo | Sai do heap (mín.) | `último_escrito` | Novo lido | Comparação | Vai para |
|---|---|---|---|---|---|
| 1 | 2 | 2 | 4 | `4 ≥ 2` | heap ativo |
| 2 | 4 | 4 | 1 | `1 < 4` | **congelado** |
| 3 | 6 | 6 | 8 | `8 ≥ 6` | heap ativo |
| 4 | 8 | 8 | 12 | `12 ≥ 8` | heap ativo |
| 5 | 9 | 9 | 3 | `3 < 9` | **congelado** |
| 6 | 12 | 12 | 10 | `10 < 12` | **congelado** |

No passo 6 o heap ativo esvaziou (os 3 congelados — `{1,3,10}` — não contam como ativos).
**Fecha a Partição 1** = `[2, 4, 6, 8, 9, 12]` — **6 elementos**, o **dobro** de `M=3`.

Continuando com a Partição 2 (heap ativo = congelados `{1,3,10}`, sem entrada nova
"quebrando" a ordem desta vez): sai `1, 3, 5, 7, 10, 11` (os valores restantes do arquivo
entram sempre `≥ último_escrito` a partir daqui) → **Partição 2** = `[1, 3, 5, 7, 10, 11]`,
também 6 elementos.

**Resultado:** 2 partições de 6 elementos, contra as `⌈12/3⌉ = 4` partições que a geração
simples (Teoria 01) produziria com o mesmo `M=3`.

## 5. Letra miúda

**"Em média 2M" não é garantia.** Para entrada adversarial (por exemplo, já ordenada de trás
para frente), o comportamento pode se aproximar da geração simples (partições de tamanho
~M). O ganho é estatístico, não uma garantia por partição individual — mas na prática, com
dados sem padrão adversarial deliberado, o tamanho médio de 2M costuma se confirmar.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| manter um **heap mínimo** em vez de array/lista | preciso achar "o menor disponível" repetidamente e rápido (O(log M)) — é exatamente o problema que heap resolve |
| comparar o novo valor lido com `último_escrito` | decido, sem olhar o resto da partição, se esse valor ainda respeita a ordem já escrita |
| "congelar" em vez de descartar | não perco o valor — só adio ele pra próxima partição, onde vai caber sem quebrar ordem |

## 7. Exercícios de fixação

1. Por que a estrutura usada precisa ser um **heap mínimo**, e não um array ordenado?
   (Pense no custo de inserir + remover repetidamente.)
2. No trace da seção 4, por que o valor `1` (lido no passo 2) não pôde entrar na Partição 1?
3. Se toda a entrada já viesse **ordenada crescente**, quantas partições a seleção por
   substituição produziria, com qualquer `M`? Por quê?

### Gabarito

1. Array ordenado exigiria deslocar elementos a cada inserção (`O(M)` por inserção) para
   manter a ordem; heap mínimo insere e remove o mínimo em `O(log M)` — muito mais barato
   quando isso se repete para cada um dos `N` registros do arquivo.
2. Porque `1 < 4` (o último valor escrito no passo anterior) — aceitá-lo quebraria a ordem
   crescente da partição corrente (a partição já tinha escrito `..., 4`, e escrever `1`
   depois violaria "cada valor ≥ o anterior").
3. Só **1 partição** — cada novo valor lido seria sempre `≥ último_escrito` (já que a
   entrada é crescente), então nada seria congelado, e o heap ativo nunca esvaziaria antes
   do fim do arquivo. É o melhor caso possível do método.

## Resumo

- Seleção por substituição usa um heap mínimo e a regra "novo valor ≥ último escrito? vai
  pro heap ativo; senão, congela pra próxima partição".
- Gera, em média, partições de tamanho `2M` — metade do número de partições da geração
  simples, com o mesmo limite de memória `M`.
- Menos partições geradas aqui = menos trabalho de intercalação em 3.3.

---

Isso fecha a teoria de 3.2. Próximo: [[../../3.3 Intercalação de Partições/README|3.3 Intercalação de Partições]].
