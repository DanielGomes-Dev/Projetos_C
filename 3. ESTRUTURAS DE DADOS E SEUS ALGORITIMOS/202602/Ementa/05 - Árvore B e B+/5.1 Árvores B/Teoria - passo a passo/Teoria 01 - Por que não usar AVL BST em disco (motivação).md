# Teoria 01 — Por que não usar AVL/BST quando os dados estão em disco?

> **Onde isto entra:** antes de definir a árvore B propriamente, você precisa entender **o
> problema** que ela resolve — sem isso, "ordem m", "split", "⌈m/2⌉" viram decoreba solta.
> **Antes:** BST e AVL (módulos anteriores) — em particular, saber que AVL garante altura
> O(log₂ n) porque rebalanceia a cada inserção/remoção.
> **Fonte:** SZ (Szwarcfiter), capítulo/seção "Árvores B" — este é o livro-base do curso
> com foco explícito em estruturas para memória secundária. CO (Cormen), cap. 18 "Árvores
> B", também abre o capítulo com essa mesma motivação de custo de I/O. **Aviso:** nesta
> sessão não foi possível abrir os PDFs para confirmar o número exato da página (a
> ferramenta de leitura de PDF depende de um programa externo — `poppler-utils` — que não
> está disponível aqui); a seção é fácil de achar pelo sumário de qualquer um dos dois
> livros, procurando por "Árvores B" / "B-trees". Não invente números de página a partir
> disto — confira no seu exemplar antes da prova.

## 1. A ideia em uma frase

Em memória RAM, uma AVL é ótima porque toda comparação custa "quase nada"; em disco, o que
custa caro não é comparar — é **ir buscar o próximo nó**, e uma árvore B é desenhada para
minimizar exatamente esse número de "idas ao disco".

## 2. De onde vem / por que essa estrutura existe

Uma AVL guarda um número em cada nó e dois ponteiros (esquerda/direita) — no máximo 2
filhos por nó. Isso é perfeito quando a árvore inteira mora na RAM: acessar `no->esq` ou
`no->dir` custa nanossegundos, não importa se o nó está "logo ali" ou "espalhado" na
memória.

Só que bancos de dados, sistemas de arquivo e índices geralmente não cabem inteiros na
RAM — eles moram em **disco**. E disco tem uma característica que RAM não tem: **buscar um
bloco de disco é ordens de magnitude mais lento que um acesso à RAM** (a diferença é
parecida com a diferença entre você lembrar de algo na hora e ter que ir até um arquivo
físico numa outra sala pegar um papel). O número que realmente importa passa a ser: **em
quantos "nós" (blocos de disco) preciso tocar para achar uma chave?** — ou seja, a
**altura** da árvore, porque descer um nível = um acesso a disco.

Uma AVL com `n` chaves tem altura proporcional a `log₂ n` — cada nó só reduz a busca pela
metade porque só tem 2 filhos. **A pergunta que motiva a árvore B é**: e se cada nó tivesse
não 2, mas **centenas** de filhos? A busca desceria muito mais devagar em número de níveis
(cada nível "corta" o problema não ao meio, mas em centenas de pedaços) — trocando um nó
"magro" (2 filhos) por um nó "gordo" (m filhos, guardando várias chaves e ponteiros dentro
de um único bloco de disco que já é lido de uma vez).

## 3. A comparação — lida devagar

> 📖 **Lendo devagar — o que `O(log_m n)` quer dizer:**
>
> 1. `log_m n` — "logaritmo de `n` na base `m`". Isso responde: "quantas vezes preciso
>    dividir `n` por `m` até chegar a 1?" — ou seja, quantos níveis uma árvore onde cada nó
>    tem até `m` filhos precisa ter para guardar `n` chaves.
> 2. Em AVL/BST, a base é sempre **2** (cada nó só tem 2 filhos) — por isso a altura é
>    `log₂ n`.
> 3. Em árvore B, a base é **m**, o número de filhos por nó — que pode ser dezenas ou
>    centenas, escolhido para caber exatamente num bloco de disco.
> 4. Quanto **maior** a base do log, **menor** o resultado, para o mesmo `n` — é por isso
>    que árvore B com m grande tem altura muito menor que uma AVL com o mesmo número de
>    chaves.

**Afirmação:** para `n` grande, uma árvore B com ordem `m` grande tem altura drasticamente
menor que uma AVL com o mesmo `n`, e isso significa muito menos acessos a disco.

**Conferindo com números concretos:** suponha `n = 1.000.000` chaves, e que cada acesso a
disco custe (de forma realista) **10 ms**.

| Estrutura | Altura aproximada | Acessos a disco no pior caso | Tempo estimado |
|---|---|---|---|
| AVL (base 2): `log₂(1.000.000) ≈ 19,9` | ≈ 20 níveis | ≈ 20 acessos | 20 × 10 ms = **200 ms** |
| Árvore B, ordem m=100: `log₁₀₀(1.000.000) ≈ 3` | ≈ 3 níveis | ≈ 3 acessos | 3 × 10 ms = **30 ms** |

`log₁₀₀(1.000.000)` se calcula assim: `log₁₀₀(1.000.000) = ln(1.000.000) / ln(100) ≈
13,8 / 4,6 ≈ 3`. Ou seja, trocar a base do log de 2 para 100 derruba a altura de ~20 para
~3 — quase 7 vezes menos acessos a disco para achar **qualquer** chave, uma vez que a
árvore esteja construída. ✔ Essa é a conta que o SZ e o CO usam para justificar a árvore B
antes de definir qualquer propriedade formal.

## 4. E por que não simplesmente "guardar tudo em cache/RAM"?

Isso ajuda (e bancos de dados reais fazem cache pesado dos níveis superiores da árvore),
mas não resolve o problema de fundo: a base de dados como um todo (tabelas inteiras,
índices completos) costuma ser grande demais para caber inteira na RAM disponível — sempre
sobra uma parte que precisa vir do disco, e é o **pior caso** (quantos acessos a disco na
pior hipótese) que uma estrutura de dados precisa garantir que seja pequeno.

## 5. Letra miúda

**E por que `m` não é sempre "o maior possível"?** Cada nó de uma árvore B ocupa
tipicamente **um bloco de disco inteiro** (ex.: 4 KB). `m` é escolhido em função de quantas
chaves + ponteiros cabem nesse bloco — não é um número arbitrário que se aumenta à vontade.
Na prática deste curso, os exercícios usam `m` pequeno (3, 4, 5) só para caber no papel;
**o raciocínio de custo de I/O é o mesmo**, só a escala muda.

## 6. Exercícios de fixação

1. Em uma palavra: por que uma AVL é uma boa escolha em RAM mas uma escolha ruim para um
   índice de banco de dados que mora em disco?
2. Se cada acesso a disco custa 5 ms (em vez de 10 ms), quanto tempo leva, no pior caso,
   para achar uma chave numa árvore B de altura 3? E numa AVL de altura 20 com o mesmo
   `n`?
3. Por que aumentar `m` para um valor absurdamente grande (por exemplo, `m = 1.000.000`)
   não é uma boa ideia na prática?
4. O que exatamente conta como "um acesso" nesta comparação — uma comparação de números,
   ou uma leitura de bloco de disco?

### Gabarito

1. Porque em RAM todo acesso a nó custa igual (muito barato), então minimizar
   **comparações** (o que a AVL faz, com altura `log₂ n`) já é suficiente. Em disco, o
   custo dominante é o **número de acessos a blocos diferentes**, e uma AVL, por ter só 2
   filhos por nó, precisa de muito mais níveis (muito mais acessos a disco) que uma árvore
   B com o mesmo `n`.
2. Árvore B: 3 × 5 ms = 15 ms. AVL: 20 × 5 ms = 100 ms — a árvore B continua sendo
   quase 7× mais rápida, porque a vantagem vem da **altura**, não do custo por acesso.
3. Porque `m` não é livre — ele é limitado pelo tamanho do bloco de disco (quantas chaves +
   ponteiros de filho cabem nesse bloco de uma vez). Um `m` maior que isso obrigaria um nó
   a ocupar vários blocos, e você perderia a vantagem de "1 nó = 1 acesso a disco".
4. Uma **leitura de bloco de disco** (equivalente a "visitar um nó"). Comparações de
   números dentro do bloco já lido são baratas (acontecem em RAM, depois que o bloco já
   está carregado) — o que se conta e se minimiza é quantos blocos **diferentes** você
   precisa ler.

## Resumo

- Em RAM, o custo dominante é o número de **comparações**; em disco, é o número de
  **acessos a blocos diferentes** — e cada acesso a disco é ordens de magnitude mais lento.
- Altura da árvore = número de acessos a disco no pior caso, porque descer um nível = ler
  um bloco novo.
- AVL/BST têm base 2 no logaritmo da altura (`log₂ n`) porque só têm 2 filhos por nó;
  árvore B usa base `m` (`log_m n`), com `m` escolhido para caber num bloco de disco.
- Aumentar a base do logaritmo derruba a altura drasticamente para `n` grande — é essa
  conta (não uma opinião de gosto) que justifica a árvore B.

**Próximo:** [[Teoria 02 - O que é uma árvore B (ordem m e propriedades estruturais)]].
