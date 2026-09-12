# Teoria 04 — Como inserir numa árvore B sem quebrar as propriedades? (split)

> **Onde isto entra:** este é o coração da árvore B — o mecanismo que garante que, depois
> de qualquer inserção, as 5 propriedades da Teoria 02 continuam valendo (em especial,
> "todas as folhas na mesma profundidade").
> **Antes:** [[Teoria 03 - Busca em árvore B (por igualdade)]] — inserir começa igual a
> buscar: desce até a folha certa.
> **Fonte:** README.md deste subtópico (exemplo inicial `10, 20, 5` com m=3) e CO, cap. 18,
> pseudocódigo B-TREE-SPLIT-CHILD / B-TREE-INSERT (a árvore construída aqui é a mesma que
> aparece na Teoria 02 e 03). Página exata de CO não verificada nesta sessão (ver aviso na
> Teoria 01).

## 1. A ideia em uma frase

Insere-se a chave numa folha, no lugar ordenado certo; se isso fizer o nó "transbordar"
(mais chaves do que o máximo permitido), o nó se **divide em dois**, e a chave do meio
**sobe** para o pai — e esse "subir" pode se repetir, nível a nível, até criar até uma nova
raiz.

## 2. De onde vem / por que fazemos assim

Se você simplesmente inserisse a chave na folha certa e parasse por aí, mais cedo ou mais
tarde um nó acabaria com mais chaves (e filhos) do que o máximo `m−1` permite — violando a
propriedade 1 da Teoria 02. A pergunta que motiva o split é: **quando um nó estoura, o que
fazer com o excesso sem desequilibrar a árvore?** A resposta da árvore B é engenhosa: em
vez de só "criar mais um filho para o nó estourado" (o que quebraria a regra de quantos
filhos um nó pode ter), ela **divide o nó em dois nós irmãos** e empurra a chave do meio um
nível acima, para o pai decidir entre os dois. Como o pai recebe só **uma** chave a mais
(não uma folha nova solta por aí), a árvore cresce **em largura primeiro, e só em altura
como último recurso** — e é exatamente esse "só como último recurso" que mantém todas as
folhas na mesma profundidade.

## 3. O algoritmo — lido pedaço por pedaço

> 📖 **Lendo devagar — o que acontece ao inserir uma chave `x`:**
>
> 1. Desça pela árvore como na busca (Teoria 03), até chegar à **folha** onde `x` deveria
>    estar.
> 2. Insira `x` na posição ordenada certa dentro dessa folha.
> 3. **Verifique overflow**: se o nó passou a ter mais que `m−1` chaves, ele **estourou**.
> 4. Se estourou: **divida (split)** o nó em dois — a metade das chaves menores fica num
>    nó, a metade maior fica em outro, e a **chave do meio** (nem uma metade nem outra) é
>    promovida para o nó pai.
> 5. Inserir a chave promovida no pai pode fazer **o pai também estourar** — nesse caso,
>    repita o split **um nível acima**. Isso é chamado de **propagação do split**.
> 6. Se o split chegar até a **raiz** e ela também estourar, cria-se uma **nova raiz**
>    (com só a chave promovida) — este é o **único** jeito de uma árvore B crescer em
>    altura, e é por isso que o crescimento sempre acontece "por igual" em todas as folhas.

## 4. Conferindo com a árvore concreta — construção completa, passo a passo (m=3)

Para `m=3`: máximo de chaves por nó = `m−1=2` (estoura com 3); mínimo de chaves em nó
não-raiz = `⌈3/2⌉−1=1`. Vamos inserir, nesta ordem: `10, 20, 5, 30, 40, 50, 60`.

**Passo 1 — insere 10.** Árvore vazia → cria a raiz como folha: `[10]` (1 chave, cabe).

**Passo 2 — insere 20.** Desce até a raiz (só há ela, e é folha). Insere ordenado:
`[10, 20]` (2 chaves = `m−1`, no limite, mas ainda **não** estourou).

**Passo 3 — insere 5.** Insere ordenado em `[10,20]` → temporariamente `[5, 10, 20]` (3
chaves > `m−1=2` → **OVERFLOW**).

> 📖 **Lendo devagar — dividindo `[5, 10, 20]`:**
> 1. Chave do meio (índice 1, contando de 0): `10`. Essa é a que **sobe**.
> 2. Metade esquerda (chaves antes do meio): `[5]`.
> 3. Metade direita (chaves depois do meio): `[20]`.
> 4. Não havia pai (a raiz estourou) → **cria-se uma nova raiz** só com a chave promovida.

```
              [10]
             /     \
          [5]      [20]
```

A árvore cresceu de altura 0 (só a raiz) para altura 1. ✔ (propriedade 4: as duas folhas
`[5]` e `[20]` estão na mesma profundidade, 1 nível abaixo da raiz.)

**Passo 4 — insere 30.** Desce: `30 > 10` → vai para o filho direito `[20]`. Insere
ordenado: `[20, 30]` (2 chaves, no limite, **não** estourou). Árvore:

```
              [10]
             /     \
          [5]     [20, 30]
```

**Passo 5 — insere 40.** Desce: `40 > 10` → filho direito `[20,30]`. Insere ordenado →
temporariamente `[20, 30, 40]` (3 chaves → **OVERFLOW**).

> 📖 **Lendo devagar — dividindo `[20, 30, 40]`:**
> 1. Chave do meio: `30`. Sobe.
> 2. Metade esquerda: `[20]`. Metade direita: `[40]`.
> 3. **Há pai** (a raiz `[10]`) — a chave `30` é inserida **nele**, não cria raiz nova.

Insere `30` no pai `[10]`: `[10, 30]` (2 chaves, no limite, **não** estourou — o pai tinha
espaço). Os dois novos nós (`[20]` e `[40]`) tomam o lugar do antigo `[20,30]` como filhos:

```
              [10, 30]
             /    |    \
          [5]   [20]   [40]
```

Repare: desta vez o split **não chegou** até criar uma nova raiz, porque o pai ainda tinha
espaço para uma chave a mais — a árvore continua com altura 1.

**Passo 6 — insere 50.** Desce: `50 > 30` → filho direito `[40]`. Insere ordenado:
`[40, 50]` (2 chaves, no limite, **não** estourou).

```
              [10, 30]
             /    |    \
          [5]   [20]   [40, 50]
```

**Passo 7 — insere 60.** Desce: `60 > 30` → filho direito `[40,50]`. Insere ordenado →
temporariamente `[40, 50, 60]` (**OVERFLOW**).

> 📖 **Lendo devagar — dividindo `[40, 50, 60]`, e o que acontece a seguir:**
> 1. Chave do meio: `50`. Sobe. Metade esquerda: `[40]`. Metade direita: `[60]`.
> 2. Insere `50` no pai `[10, 30]` → temporariamente `[10, 30, 50]` (3 chaves →
>    **o pai TAMBÉM estourou!** — o split se propagou um nível acima).
> 3. Divide `[10, 30, 50]`: chave do meio = `30`. Sobe. Metade esquerda: `[10]`. Metade
>    direita: `[50]`.
> 4. `[10,30,50]` **era a raiz** e estourou — não há pai para receber `30` → **cria-se uma
>    nova raiz**, só com a chave `30`.

Os filhos são reorganizados: a antiga raiz tinha 4 filhos, na ordem `[5], [20], [40],
[60]` (o `[40,50,60]` que acabou de dividir virou `[40]` e `[60]`); ao dividir a raiz ao
meio, a metade esquerda (`[10]`) fica com os 2 primeiros filhos (`[5], [20]`) e a metade
direita (`[50]`) fica com os 2 últimos (`[40], [60]`):

```
                         [30]
                        /     \
                    [10]       [50]
                   /    \      /    \
                [5]   [20]  [40]  [60]
```

A árvore cresceu de altura 1 para altura 2 — **esta é exatamente a árvore usada nas
Teorias 02 e 03**. ✔ Todas as 4 folhas (`5,20,40,60`) estão na mesma profundidade (2).

## 5. Casos / variações

- **Split que não chega ao pai estourar** (Passo 3→4 acima): a chave promovida cabe no pai
  sem estourar ele — a árvore não cresce em altura, só o nó que estourou vira dois.
- **Split que propaga até a raiz** (Passo 7 acima): cada nível acima também estoura, até
  não haver mais pai — nesse caso (e só nesse caso) nasce uma raiz nova, e a árvore cresce
  em altura. É o único mecanismo de crescimento em altura da árvore B.

## 6. Letra miúda

**E se o split parasse "no meio do caminho" sem chegar à raiz nem couber no pai?** Isso não
acontece — a propagação sempre ou (a) encontra um ancestral com espaço e para ali, ou
(b) chega até a raiz. Não existe estado intermediário "quebrado": a árvore B garante que,
depois do processo de split terminar (por completo, antes de qualquer nova operação), as 5
propriedades da Teoria 02 voltam a valer.

## 7. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| "insiro a chave na folha ordenada" | igual a uma BST — só que "a folha" aqui pode já ter várias chaves |
| "verifico se o nó tem mais que `m-1` chaves" | checo se ainda caberia num único bloco de disco (propriedade 1 da Teoria 02) |
| "divido o nó, chave do meio sobe" | transformo "um bloco cheio demais" em "dois blocos com espaço", e informo o pai qual é o separador entre eles |
| "insiro a chave promovida no pai, verifico overflow de novo" | repito o mesmo raciocínio um nível acima — é uma recursão, não uma coisa nova |
| "estourei até a raiz → crio nova raiz" | é o único ponto onde a árvore fica mais alta — e por isso todas as folhas continuam na mesma profundidade |

## 8. Complexidade

| Operação | Complexidade |
|---|---|
| Descer até a folha | O(log_m n) acessos (altura) |
| Cada split individual | O(m) (copiar metade das chaves/filhos) |
| Pior caso (propaga até a raiz) | O(log_m n) splits, cada um O(m) → O(m · log_m n) no total |

## 9. Exercícios de fixação

Continuando a partir da árvore final da seção 4 (m=3), insira, nesta ordem: `70`, depois
`80`.

1. Insira `70`. Ele estoura algum nó? Desenhe o resultado.
2. A partir do resultado do item 1, insira `80`. Isso causa split? Se sim, propaga até a
   raiz?
3. Por que, ao dividir um nó de 3 chaves em árvore B de ordem 3, a chave do meio é sempre a
   de índice 1 (contando de 0), nunca a de índice 0 ou 2?

### Gabarito

1. Desce: `70 > 30` → `[50]` → `70 > 50` → filho direito `[60]`. Insere `70` em `[60]` →
   `[60, 70]` (2 chaves, no limite, **não** estourou). Resultado:
   ```
                            [30]
                           /     \
                       [10]       [50]
                      /    \      /    \
                   [5]   [20]  [40]  [60, 70]
   ```
2. Desce: `80 > 30` → `[50]` → `80 > 50` → `[60,70]`. Insere `80` →
   temporariamente `[60,70,80]` (**overflow**). Divide: meio = `70` (sobe), metades
   `[60]` e `[80]`. Insere `70` no pai `[50]` → `[50, 70]` (2 chaves, no limite, **não**
   estourou — não propaga até a raiz). Resultado:
   ```
                            [30]
                           /     \
                       [10]       [50, 70]
                      /    \      /   |    \
                   [5]   [20]  [40] [60]  [80]
   ```
3. Porque com 3 chaves (índices 0, 1, 2), a única divisão que deixa **uma chave de cada
   lado** (metade esquerda com 1 chave, metade direita com 1 chave, e 1 chave sobrando pra
   promover) é tirar a do meio (índice 1). Tirar a de índice 0 ou 2 deixaria uma metade com
   2 chaves e a outra com 0 — quebrando a propriedade de mínimo de chaves da Teoria 02.

## Resumo

- Insere-se sempre numa folha; se ela estourar (mais que `m-1` chaves), ela se **divide**,
  promovendo a chave do meio para o pai.
- A promoção pode se repetir (**propagar**) para cima, nível a nível, se cada ancestral
  também estourar.
- Uma **nova raiz** só é criada quando o split chega ao topo — é o único jeito da árvore B
  crescer em altura, o que garante que todas as folhas continuam na mesma profundidade.
- Split é sempre um processo de baixo para cima, nunca "no meio" da árvore.

**Próximo:** [[Teoria 05 - Merge e redistribuição na remoção (m=3, passo a passo)]].
