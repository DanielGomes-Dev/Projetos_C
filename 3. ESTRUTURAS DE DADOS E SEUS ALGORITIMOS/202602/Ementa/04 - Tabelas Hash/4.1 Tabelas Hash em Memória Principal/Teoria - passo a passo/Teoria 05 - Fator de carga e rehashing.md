# Teoria 05 — Fator de carga e rehashing

> **Onde isto entra:** fecha o módulo respondendo "e quando a tabela fica cheia (ou perto
> disso) de verdade?" — a resposta é a mesma ideia por trás de todo `array` dinâmico que
> cresce (`realloc`), só que aplicada a uma tabela hash inteira.
> **Antes:** [[Teoria 04 - Encadeamento separado (listas ligadas nos buckets)]].
> **Fonte:** CO (Cormen, Leiserson, Rivest, Stein — *Algoritmos: Teoria e Prática*), Cap.
> 11 "Tabelas Hash" — cobertura teórica da análise abaixo; **página exata não confirmada
> nesta máquina, conferir ao abrir o PDF**. SZ (Szwarcfiter) também cobre o tópico no
> capítulo de tabelas de espalhamento.

## 1. A ideia em uma frase

O **fator de carga** `α` mede o quão "cheia" a tabela está; quando ele passa de um limite
seguro, a tabela é redimensionada (**rehashing**) para não perder a velocidade O(1) que é
a razão dela existir.

## 2. A fórmula — lida devagar

$$\alpha = \frac{n}{m}$$

> 📖 **Lendo devagar:** `n` é quantos elementos estão **de fato** guardados na tabela agora;
> `m` é quantas posições a tabela **tem** (o `N`/`NTAB` das Teorias 01–04). `α` é essa
> razão — **não** é o número absoluto de elementos, é a **proporção** de ocupação.

**Conferindo com número:** tabela com `m = 50` posições e `n = 40` elementos inseridos
(mesmo exemplo do exercício da Teoria 01): `α = 40/50 = 0,8`. Essa é a mesma tabela que a
Teoria 01 apontou como "acima da regra empírica de 75%" — agora com nome formal: `α = 0,8
> 0,75`.

## 3. Por que `α` determina o desempenho — motivação antes da tabela

Em **encadeamento separado** (Teoria 04), `α` é literalmente o **tamanho médio de cada
lista** — se há `n` elementos espalhados em `m` posições, e a função hash espalha bem, cada
lista tem em média `n/m = α` elementos. Buscar uma chave custa "calcular o hash" (O(1)) mais
"percorrer a lista" (em média `α` passos) — daí a fórmula `O(1 + α)`.

Em **endereçamento aberto** (Teorias 02–03), o raciocínio é mais sutil: quanto mais perto
`α` chega de 1 (tabela cheia), mais **rara** é a chance de achar posição livre logo de
cara — as sondagens ficam sistematicamente mais longas à medida que sobra menos espaço
vazio. A análise (feita rigorosamente no Cormen, sob a hipótese de "hashing uniforme
simples") dá `O(1 / (1 - α))`.

| Método | Complexidade média (busca) | O que acontece perto de `α = 1` |
|---|---|---|
| Encadeamento separado | O(1 + α) | Cresce **linearmente** — `α = 2` só dobra o custo médio |
| Endereçamento aberto | O(1 / (1 − α)) | Cresce **explosivamente** — `α = 0,99` já dá custo médio ~100 |

> **Conferindo com número (endereçamento aberto):** `α = 0,5` → `1/(1-0,5) = 2`. `α = 0,9` →
> `1/(1-0,9) = 10`. `α = 0,99` → `1/(1-0,99) = 100`. Repare o salto: a mesma "distância" de
> 0,1 no valor de `α` (de 0,9 pra 0,99 vs. de 0,5 pra 0,4) tem efeitos completamente
> diferentes conforme `α` se aproxima de 1 — é por isso que endereçamento aberto **precisa**
> de uma margem de segurança maior (a regra do Celes de não passar de ~75%, Teoria 01), e
> encadeamento separado tolera `α` maior sem degradar tão bruscamente.

## 4. Rehashing — a operação de crescer a tabela

Quando `α` ultrapassa o limiar escolhido (tipicamente 0,7–0,75 em endereçamento aberto;
pode ser mais alto em encadeamento), o procedimento é:

1. Aloca-se um vetor **novo**, maior — em geral o **dobro** do tamanho atual (e, se possível,
   o próximo número **primo** acima do dobro, pelos mesmos motivos das Teorias 01 e 03).
2. **Todas** as chaves já armazenadas são reinseridas na tabela nova — recalculando o hash
   de cada uma, porque `hash(chave) = chave % m` **depende de `m`**, que mudou.
3. A tabela antiga é descartada.

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| calcular `α = n/m` a cada inserção | meço, em tempo real, o quão perto estou do ponto em que o desempenho começaria a degradar |
| redimensionar quando `α` cruza o limiar | troco "continuar piorando indefinidamente" por "pagar um custo pontual (O(n)) pra voltar a ter margem" |
| recalcular o hash de **todas** as chaves no rehashing | não existe atalho — como `hash` depende de `m`, uma chave que estava na posição 34 pode pertencer a uma posição totalmente diferente na tabela nova |

## 6. Por que o custo do rehashing "some" no amortizado

**Afirmação:** mesmo custando O(n) uma vez a cada dobra de tamanho, o custo médio por
inserção continua O(1).
**Conferindo com números:** suponha que a tabela dobra de tamanho toda vez que enche (do
tamanho `m` para `2m`). Entre uma dobra e a próxima, acontecem `m` novas inserções antes de
a tabela encher de novo (aproximadamente). O custo daquela dobra específica é O(m)
(reinserir todo mundo) — mas esse custo O(m) é **dividido** entre as `m` inserções que
ficaram "de graça" (O(1) cada) até a tabela encher de novo. Custo total das `m` inserções +
1 dobra: `O(m) + O(m) = O(m)`, ou seja, `O(1)` por inserção em média — o mesmo argumento
usado para justificar por que um array dinâmico que dobra de tamanho (`realloc` do dobro)
tem inserção O(1) amortizado, não O(n).

## 7. Exercícios de fixação

1. Uma tabela com `m = 20` e limiar de rehashing `0,75` — com quantos elementos inseridos
   o rehashing dispara?
2. Depois do rehashing da questão 1 (tabela dobrando para `m = 40`), qual é o novo `α`
   imediatamente após o redimensionamento (mesmo `n` de antes)?
3. Por que, em encadeamento separado, seria **tecnicamente possível** nunca fazer
   rehashing (deixar `α` crescer sem limite)? O que se perderia ao fazer essa escolha?
4. Explique, em uma frase, por que `hash(chave) = chave % m` obriga a reinserção completa
   no rehashing, em vez de só "copiar" os dados de um vetor pro outro maior.

### Gabarito

1. Dispara quando `n/20 ≥ 0,75`, ou seja, `n ≥ 15` elementos.
2. `α = 15/40 = 0,375` — bem abaixo do limiar, com boa margem para crescer de novo antes do
   próximo rehashing.
3. Sim, tecnicamente possível — listas ligadas não têm limite físico de tamanho. O que se
   perde é desempenho: `O(1 + α)` cresce sem limite junto com `α`, então a busca deixaria
   de ser "praticamente O(1)" e se aproximaria de O(n) conforme mais e mais elementos
   fossem inseridos sem nunca aumentar `m`.
4. Porque a posição de uma chave depende do **valor de `m`** usado no cálculo (`chave % m`)
   — ao trocar `m`, o resto da divisão muda para a maioria das chaves, então a posição
   antiga de cada uma não é mais válida na tabela nova; é preciso recalcular `hash` com o
   novo `m` para cada chave.

## Resumo

- `α = n/m` mede a ocupação da tabela; é a variável que realmente determina o desempenho.
- Encadeamento separado degrada linearmente com `α` (`O(1+α)`); endereçamento aberto degrada
  explosivamente perto de `α = 1` (`O(1/(1-α))`) — por isso limiares de segurança diferentes.
- Rehashing = dobrar (tipicamente) o tamanho da tabela e reinserir tudo, recalculando o hash
  de cada chave (pois `hash` depende de `m`). Custa O(n) pontualmente, mas O(1) amortizado
  por inserção, no mesmo espírito de um array dinâmico que dobra de tamanho.

---

Isso fecha a teoria de 4.1. Próximo: [[../../4.2 Tabelas Hash em Memória Secundária/README|4.2 Tabelas Hash em Memória Secundária]] — o mesmo problema de fundo, mas quando a tabela não cabe em RAM.
