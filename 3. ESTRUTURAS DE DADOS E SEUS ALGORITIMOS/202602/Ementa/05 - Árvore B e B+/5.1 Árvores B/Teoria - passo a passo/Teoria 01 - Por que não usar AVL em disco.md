# Teoria 01 — Por que não usar AVL quando os dados estão em disco

> **Onde isto entra:** é a motivação para a árvore B existir — sem entender o problema de
> disco, a estrutura toda parece "complicação desnecessária" em cima da AVL (1.3).
> **Antes:** [[../../../01 - Árvores/1.3 Árvores AVL/README|1.3 Árvores AVL]] (a árvore
> balanceada de memória principal, para comparação).
> **Fonte:** SZ (Szwarcfiter, livro-base — capítulo de Árvores B, com foco explícito em
> memória secundária) · CO (Cormen, cap. "Árvores B" — conferir página exata na edição em
> mãos). Não há PDF de aula deste módulo ainda (turma não chegou lá).

## 1. A ideia em uma frase

Em RAM, qualquer acesso a um nó custa (aproximadamente) o mesmo. Em disco, o custo que
realmente importa é **quantas vezes você precisa ir ao disco** — e é isso que a árvore B
minimiza, ao custo de nós "mais gordos" (com várias chaves cada).

## 2. De onde vem o problema

Pense na AVL (1.3): ela minimiza a **altura** contando em número de nós — uma AVL com um
milhão de chaves tem altura por volta de 20 (log₂ de um milhão). Isso é ótimo em RAM. Mas
em disco, cada "descer um nível" na árvore normalmente significa **um acesso a disco**
(porque o próximo nó pode estar em qualquer lugar físico do disco, não guardado perto do
atual). E um acesso a disco custa, em ordem de grandeza, **milhares de vezes mais** que um
acesso à RAM. Então "só 20 acessos" ainda é lento se cada um custa milhares de vezes mais
que uma operação em memória.

> **Pergunta que motiva a árvore B:** dá pra desenhar uma árvore onde cada nó carregue
> *várias* chaves (não só uma), pra reduzir drasticamente quantos **níveis** (= acessos a
> disco) são necessários para achar qualquer chave?

## 3. Comparando com número concreto

**Afirmação:** para o mesmo número de chaves, uma árvore com "nós gordos" tem altura muito
menor que uma árvore binária.

**Conferindo:** com 1 milhão de chaves:
- Árvore binária balanceada (AVL): altura ≈ log₂(1.000.000) ≈ **20 níveis** → até 20
  acessos a disco por busca.
- Árvore B com ordem m = 100 (até 99 chaves por nó): altura ≈ log₁₀₀(1.000.000) = 3 (porque
  100³ = 1.000.000) → até **3 ou 4 níveis** → 3 ou 4 acessos a disco por busca.

Essa é a diferença entre "a busca demora um instante perceptível" e "a busca é instantânea"
num banco de dados real.

## 4. Letra miúda

**"Custa milhares de vezes mais" não é um número exato de todo hardware** — SSDs modernos
são mais rápidos que discos magnéticos antigos, mas a ordem de grandeza do problema (acesso
sequencial em RAM vs. um acesso a um dispositivo de armazenamento externo) continua válida;
é por isso que índices de banco de dados (que ficam em disco ou em armazenamento
persistente) ainda usam árvore B/B+ hoje, mesmo com SSDs rápidos.

## 5. 📌 O que você está REALMENTE fazendo (ao escolher árvore B em vez de AVL)

| A escolha de design | O que ela realmente resolve |
|---|---|
| nó com várias chaves em vez de uma | troco "muitos nós pequenos" por "poucos nós grandes" — cada nó cabe exatamente num bloco de disco, então "ler um nó" = "1 acesso a disco", processando várias chaves de uma vez |
| árvore mais "rasa" (menos níveis) | reduzo o número de blocos de disco que preciso visitar para achar qualquer chave |

## 6. Exercícios de fixação

1. Se uma árvore B tem ordem m = 10 (até 9 chaves por nó) e guarda 1000 chaves, qual é,
   aproximadamente, sua altura (use log₁₀)?
2. Por que "altura pequena" importa mais em disco do que em RAM, mesmo que a definição de
   altura seja a mesma nos dois casos?
3. Verdadeiro ou falso: "árvore B é sempre melhor que AVL". Justifique.

### Gabarito

1. log₁₀(1000) = 3 — altura aproximada de 3 níveis (a fórmula exata depende de detalhes de
   preenchimento mínimo dos nós, mas a ordem de grandeza é essa).
2. Porque em RAM o custo por nível é praticamente constante e pequeno; em disco, cada nível
   a menos representa um acesso a disco a menos — e um acesso a disco custa ordens de
   grandeza mais que qualquer processamento em RAM. A mesma "altura 3 vs. altura 20" é
   irrelevante em RAM e crítica em disco.
3. Falso. Em RAM (dados que cabem inteiramente na memória), AVL é competitiva ou melhor —
   árvore B otimiza especificamente para minimizar acessos a um armazenamento lento e
   bloco-orientado, o que só importa quando os dados não cabem em RAM.

## Resumo

- Em disco, o que importa é **número de acessos**, não processamento.
- Árvore B troca "muitos nós com 1 chave cada" (AVL) por "poucos nós com várias chaves
  cada" — isso reduz a altura drasticamente para o mesmo número de chaves.
- É uma escolha de design específica para memória secundária, não uma "AVL melhorada" de
  uso geral.

**Próximo:** [[Teoria 02 - Ordem m e propriedades da árvore B]].
