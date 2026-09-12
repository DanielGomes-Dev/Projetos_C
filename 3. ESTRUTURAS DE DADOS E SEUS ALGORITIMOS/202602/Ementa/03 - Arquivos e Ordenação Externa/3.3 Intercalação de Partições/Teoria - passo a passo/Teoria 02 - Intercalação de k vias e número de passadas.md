# Teoria 02 — Intercalação de k vias, e por que o número de passadas importa

> **Onde isto entra:** generaliza o merge de 2 partições (Teoria 01) para **k** partições
> de uma vez, e explica a conta que decide quanto custa ordenar um arquivo inteiro
> externamente.
> **Antes:** [[Teoria 01 - Intercalando duas partições (merge de 2 arquivos ordenados)]].
> **Fonte:** SZ (Szwarcfiter) — capítulo de Ordenação Externa, seção de técnicas de merge
> (conferir página exata). Nenhum PDF de aula específico para k-way merge está disponível
> ainda; exemplo numérico é construção própria seguindo o método do livro.

## 1. A ideia em uma frase

Em vez de só 2 partições, mantenho o "topo" de **k** partições ao mesmo tempo e, a cada
passo, escolho o menor entre os k — exatamente a mesma ideia da Teoria 01, só que com mais
candidatos disputando.

## 2. Por que generalizar (motivação)

Se um arquivo virou 100 partições depois da fase de geração (3.2), fazer merge **2 a 2** exigiria
várias rodadas (merge par a par, depois merge dos resultados, etc.). Fazer merge de **k de
uma vez** reduz o número de rodadas necessárias — é a mesma lógica de "quanto maior a base
de uma potência, menos dígitos preciso para representar o mesmo número".

## 3. O algoritmo — lido devagar, com número concreto

Três partições já ordenadas: `P1 = [1, 5, 9]`, `P2 = [2, 3, 8]`, `P3 = [4, 6, 7]`
(k = 3 vias). Cada partição tem um **topo** (o próximo valor ainda não escrito).

> 📖 **A cada passo:** olho os três topos, escrevo o menor na saída, e avanço **só** o
> ponteiro daquela partição — as outras duas ficam paradas, sem gastar leitura extra.

| Passo | Topo P1 | Topo P2 | Topo P3 | Menor escolhido | Saída acumulada |
|---|---|---|---|---|---|
| 1 | 1 | 2 | 4 | **1** (P1) | 1 |
| 2 | 5 | 2 | 4 | **2** (P2) | 1,2 |
| 3 | 5 | 3 | 4 | **3** (P2) | 1,2,3 |
| 4 | 5 | 8 | 4 | **4** (P3) | 1,2,3,4 |
| 5 | 5 | 8 | 6 | **5** (P1) | 1,2,3,4,5 |
| 6 | 9 | 8 | 6 | **6** (P3) | 1,2,3,4,5,6 |
| 7 | 9 | 8 | 7 | **7** (P3, esgota) | ...,7 |
| 8 | 9 | 8 | — | **8** (P2, esgota) | ...,8 |
| 9 | 9 | — | — | **9** (P1, esgota) | 1,2,3,4,5,6,7,8,9 |

Repare: uma partição só sai da disputa quando esgota — até lá, ela continua participando de
toda comparação, mesmo perdendo repetidamente (P1 "perde" nos passos 2, 3, 4, 6, 7, 8, mas
nunca é descartada até realmente acabar no passo 9).

**Escolher o menor entre k candidatos, eficientemente:** comparar os k topos um a um (busca
linear) custa `O(k)` por escolha. Um **heap mínimo de tamanho k** reduz isso a `O(log k)` —
mesma estrutura da seleção por substituição (3.2), só que aqui o heap guarda "de qual
partição veio cada topo", não os próprios dados.

## 4. A conta que importa: número de passadas

> 📖 **Passada:** uma rodada completa de intercalação, onde grupos de até k partições são
> combinados em partições maiores, até restar 1 no fim da rodada.

Se existem `P` partições (vindas de 3.2) e o grau de intercalação é `k`:

$$\text{número de passadas} = \lceil \log_k P \rceil$$

**Conferindo com número:** `P = 100` partições, `k = 10` (intercala 10 de cada vez).
- **Passada 1:** agrupa as 100 em 10 grupos de 10, intercala cada grupo → sobram 10
  partições (cada uma 10× maior).
- **Passada 2:** agrupa essas 10 num único grupo, intercala → sobra 1 partição — **o
  arquivo inteiro, ordenado.**

Total: 2 passadas. Confere com a fórmula: `⌈log₁₀(100)⌉ = ⌈2⌉ = 2`. ✔

Com o mesmo `P=100` mas `k=2` (merge só de 2 em 2, como na Teoria 01): `⌈log₂(100)⌉ =
⌈6.64...⌉ = 7` passadas — muito mais rodadas de I/O para o mesmo trabalho.

## 5. Letra miúda: por que não usar k gigante sempre

Cada partição sendo intercalada precisa de um "canal" de leitura ativo (na prática, um
buffer de memória reservado para ler daquela partição). k gigante exige k buffers
simultâneos — de novo esbarra no limite de memória `M` que motivou o módulo inteiro (3.1).
Na prática, `k` é escolhido em função de quanta RAM sobra para buffers, não escolhido livre.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| manter k "topos", um por partição | generalizo os 2 candidatos da Teoria 01 para k candidatos — a lógica de "escolha o menor" não muda |
| aumentar k | reduzo `⌈log_k P⌉`, o número de passadas — cada passada custa uma leitura+escrita do arquivo inteiro, então menos passadas = menos I/O total |
| heap de tamanho k para escolher o menor | troco `O(k)` por escolha por `O(log k)` — importa quando k é grande (muitos buffers/partições simultâneas) |

## 7. Exercícios de fixação

1. Com `P = 64` partições e `k = 4`, quantas passadas são necessárias?
2. Por que dobrar `k` não reduz o número de passadas pela metade (a relação não é linear)?
3. No trace da seção 3, por que a saída final está correta mesmo `P1` "perdendo" a maior
   parte das comparações?

### Gabarito

1. `⌈log₄(64)⌉ = ⌈3⌉ = 3` passadas (64 → 16 → 4 → 1).
2. Porque a relação é **logarítmica**, não linear: `log_k P` cresce/decresce como um
   logaritmo em `k`, não proporcionalmente. Dobrar `k` de 2 para 4 já dá um ganho grande
   (log base maior encolhe mais no começo), mas dobrar de 100 para 200 dá um ganho bem
   menor em termos absolutos de passadas.
3. Porque o método garante, a cada passo, que o menor **global** entre os candidatos
   disponíveis é escrito — não importa de qual partição ele veio nem quantas vezes aquela
   partição "perdeu" antes. Correção não depende de "quem vence mais", só de sempre
   escolher corretamente o mínimo a cada rodada.

## Resumo

- Intercalação de k vias: mantém o topo de k partições, escreve sempre o menor, avança só
  aquele lado — extensão direta do merge de 2 (Teoria 01).
- Número de passadas = `⌈log_k P⌉`; aumentar k reduz o número de passadas (menos I/O total),
  mas exige mais buffers de memória simultâneos.
- Escolher o mínimo entre k candidatos com heap custa `O(log k)`, contra `O(k)` de busca
  linear — importa quando k é grande.

---

Isso fecha a teoria de 3.3 e do módulo `03 - Arquivos e Ordenação Externa`. Próximo módulo:
[[../../../04 - Tabelas Hash/README|04 - Tabelas Hash]].
