# Teoria 01 — Por que memória secundária muda o problema

> **Onde isto entra:** motivação de todo o subtópico — sem entender por que "acesso a
> disco" é uma unidade de custo diferente de "comparação em RAM", os métodos de 4.2 parecem
> complexidade gratuita.
> **Antes:** [[../../4.1 Tabelas Hash em Memória Principal/Teoria - passo a passo/README|4.1 Tabelas Hash em Memória Principal]] (a base: função hash, colisão, fator de carga).
> **Fonte:** SZ (Szwarcfiter), capítulo de tabelas de espalhamento, seção de memória
> secundária — **não foi possível abrir o PDF nesta máquina** (falta a ferramenta de
> renderização); a explicação abaixo segue a mesma motivação já registrada no `README.md`
> deste subtópico, sem número de página confirmado. Confira a seção exata ao abrir o livro.

## 1. A ideia em uma frase

Em disco, o que custa caro não é "quantas comparações eu faço", é **quantas vezes eu toco o
disco** — e as técnicas deste subtópico existem só para minimizar esse número.

## 2. De onde vem a diferença (motivação)

Em 4.1, todo o raciocínio de complexidade era em cima de **comparações** (`O(1+α)`,
`O(1/(1-α))`) — porque, em RAM, acessar qualquer posição custa (aproximadamente) o mesmo,
não importa qual. Em disco, isso deixa de ser verdade: um acesso a disco custa **ordens de
magnitude mais** que um acesso à RAM (milissegundos vs. nanossegundos — grosso modo, um
fator de 10 mil a 100 mil vezes). Uma tabela hash com `n` elementos, se guardada
ingenuamente em disco, poderia custar vários acessos a disco por busca (cada tentativa de
sondagem, cada nó de lista percorrido em encadeamento) — e cada um desses acessos pesa
muito mais do que pesava em memória principal.

> 📖 **Traduzindo:** o objetivo dos métodos de 4.2 (hashing extensível, hashing linear) não
> é reduzir "quantas chaves eu comparo" — é reduzir **quantos blocos de disco diferentes eu
> preciso ler** para achar uma chave.

## 3. O vocabulário novo: bucket

> **Bucket** — um bloco de disco, capaz de guardar **vários** registros (não só um). Em vez
> de a função hash apontar para "uma posição = um elemento" (como em 4.1), ela aponta para
> "um bucket = até `k` elementos". Ler um bucket inteiro custa **1 acesso a disco**, não
> importa se ele tem 1 ou `k` elementos — então cabe aproveitar esse acesso ao máximo,
> enchendo o bucket antes de precisar de outro.

## 4. Conferindo com número: por que "1 acesso" muda tudo

Suponha um disco onde 1 acesso custa 5 ms, e a RAM onde 1 comparação custa 5 ns (um fator
de ~1 milhão). Uma busca que em RAM levaria "10 comparações" (desprezível, ~50 ns) seria
catastrófica em disco se cada uma dessas 10 "tentativas" fosse **um bucket diferente**: 10
acessos × 5 ms = 50 ms — um tempo perceptível para um humano. Já se essas mesmas 10
"tentativas" cabem **dentro de um único bucket já lido** (10 registros no mesmo bloco), o
custo real de disco é só **1 acesso** (5 ms) — a comparação entre os 10 registros dentro do
bucket já lido acontece em RAM, praticamente de graça.

> **Conclusão prática:** a métrica que interessa aqui não é "número de comparações", é
> **número de buckets distintos visitados** por operação.

## 5. Por que isso conecta com árvore B (módulo 05)

O mesmo raciocínio de "minimizar acessos a disco, não comparações" é exatamente o que
motiva árvore B/B+ (módulo `05 - Árvore B e B+`) — lá, a solução é uma árvore "achatada"
(poucos níveis, nós gordos); aqui, a solução é uma tabela hash cujo diretório/estrutura
auxiliar cabe em RAM e aponta direto pro bucket certo em disco, quase sempre em **1 único
acesso**. São duas famílias de solução para o mesmo problema de fundo.

## 6. 📌 O que você está REALMENTE otimizando

| O passo mecânico | O que ele realmente é |
|---|---|
| agrupar vários registros por bucket | aproveito ao máximo cada acesso caro a disco, comparando "de graça" (em RAM) os registros já lidos |
| manter um diretório pequeno em RAM apontando pros buckets | pago o acesso a disco só uma vez (o bucket certo), sem precisar "tentar" buckets errados |
| medir sucesso em "acessos a disco", não em comparações | reconheço que a unidade de custo mudou — comparação em RAM é praticamente grátis perto de um acesso a disco |

## 7. Exercícios de fixação

1. Se um bucket comporta 20 registros, e uma tabela tem 100 elementos bem distribuídos,
   qual é o número mínimo de buckets necessários?
2. Por que "10 comparações dentro do mesmo bucket já lido" é praticamente de graça, mas
   "10 tentativas em 10 buckets diferentes" não é?
3. Complete: "Em memória principal, o inimigo é ___________; em memória secundária, o
   inimigo é ___________."

### Gabarito

1. `100 / 20 = 5` buckets, no mínimo (supondo distribuição perfeita, sem desperdício).
2. Porque, uma vez que o bucket já foi lido do disco para a RAM (1 acesso), comparar os
   registros dentro dele é uma operação em memória principal — rápida. Já 10 buckets
   diferentes significam 10 acessos a disco reais, cada um pagando o custo alto de I/O.
3. "Em memória principal, o inimigo é **número de comparações**; em memória secundária, o
   inimigo é **número de acessos a disco**."

## Resumo

- Em disco, o custo dominante é I/O (acesso a bloco), não comparação — um acesso a disco
  custa ordens de magnitude mais que uma comparação em RAM.
- **Bucket**: bloco de disco com vários registros; agrupar registros por bucket aproveita
  cada acesso caro ao máximo.
- O objetivo dos métodos deste subtópico é minimizar **quantos buckets diferentes** uma
  operação precisa visitar — não quantas comparações ela faz.

**Próximo:** [[Teoria 02 - Hashing extensível (diretório e buckets)]].
