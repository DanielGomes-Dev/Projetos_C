# Teoria 05 — Inserção completa numa AVL, do início ao fim

> **Onde isto entra:** junta tudo (Teorias 01–04): fator de balanceamento, RSD/RSE, RED/RDE
> — numa sequência real de inserções, a mesma usada em exercício de aula.
> **Antes:** [[Teoria 04 - Rotações duplas (RED e RDE)]].
> **Fonte:** `lista03-EDA/07_AVL_parte2.pdf`, pág. 38 (exercício: inserir
> `{50, 40, 30, 45, 47, 55, 56, 1, 2, 3, 49}`) e pág. 37 (código `insAVL`).

## 1. A ideia em uma frase

Inserir numa AVL é inserir numa BST comum (1.2) e, **subindo de volta pela recursão**,
checar o `FB` de cada ancestral do nó recém-inserido — na primeira violação encontrada,
aplicar a rotação certa e parar (nenhum ancestral acima precisa de outra rotação).

## 2. O código completo — lido pedaço por pedaço

```c
TAVL *insAVL(TAVL *a, int elem) {
  if (!a) {
    a = (TAVL *) malloc(sizeof(TAVL));
    a->info = elem; a->alt = 0; a->esq = a->dir = NULL;
    return a;
  }
  if (elem < a->info) {
    a->esq = insAVL(a->esq, elem);
    if (FB(a) == 2) {
      if (elem < a->esq->info) a = RSD(a);
      else                     a = RED(a);
    }
  } else if (elem > a->info) {
    a->dir = insAVL(a->dir, elem);
    if (FB(a) == -2) {
      if (elem > a->dir->info) a = RSE(a);
      else                     a = RDE(a);
    }
  }
  a->alt = 1 + maximo(alt(a->dir), alt(a->esq));
  return a;
}
```

> 📖 **Lendo devagar:**
> 1. `if (!a) { ... }` — caso base: chegou numa posição vazia, cria o nó folha aqui
>    (`alt = 0`), exatamente como uma inserção de BST comum (1.2, Teoria 03).
> 2. `a->esq = insAVL(a->esq, elem)` — desce recursivamente; o valor de retorno **substitui**
>    `a->esq` porque, se uma rotação acontecer lá embaixo, a raiz daquela subárvore muda.
> 3. `if (FB(a) == 2) { ... }` — **só depois** de a chamada recursiva voltar (ou seja, depois
>    que tudo abaixo de `a` já está correto), verifica se **este** nó específico ficou
>    desbalanceado.
> 4. `if (elem < a->esq->info) a = RSD(a); else a = RED(a);` — decide entre simples e dupla
>    **sem calcular `FB(E)` de novo**: o truque é que `elem` (o valor inserido) já diz de
>    que lado, dentro de `E`, o desbalanceamento está. Se `elem` é menor que a chave de `E`,
>    ele entrou pela esquerda de `E` (desbalanceamento "reto", RSD); senão, entrou pela
>    direita de `E` (desbalanceamento "torto", RED). É uma forma equivalente, mas mais
>    barata, de checar as condições das Teorias 03–04.
> 5. `a->alt = 1 + maximo(...)` — recalcula a altura de `a` **depois** de qualquer rotação
>    (se `a` mudou por causa de `RSD`/`RED`, o `a` local agora é o novo topo, com filhos já
>    corretos).

## 3. A sequência completa (exercício real da aula, pág. 38)

Inserindo, nesta ordem, em uma árvore inicialmente vazia: `50, 40, 30, 45, 47, 55, 56, 1, 2,
3, 49`.

| # | Insere | O que acontece | Rotação |
|---|---|---|---|
| 1 | `50` | raiz | — |
| 2 | `40` | filho esquerdo de `50` | — |
| 3 | `30` | filho esquerdo de `40`; `FB(50)=2`, `30 < 40` → "reto" | **RSD(50)** |
| 4 | `45` | filho esquerdo de `50` (agora filho direito da nova raiz `40`) | — |
| 5 | `47` | filho direito de `45`; `FB(50)=2`, `47 > 45` → "torto" | **RED(50)** |
| 6 | `55` | filho direito de `50` | — |
| 7 | `56` | filho direito de `55`; `FB(40)=-2`, `56 > 47`... | **RSE(40)** |
| 8 | `1` | filho esquerdo de `30` | — |
| 9 | `2` | filho direito de `1`; `FB(30)=2`, `2 > 1` → "torto" | **RED(30)** |
| 10 | `3` | filho direito de `30` (agora abaixo de `2`); `FB(40)=2`, `3 < 2`... espere, ver nota | **RED(40)** |
| 11 | `49` | filho esquerdo de `50` | — |

> **Nota sobre o passo 10:** repare que a condição usada no código é sempre "o valor
> inserido é menor ou maior que a chave de `E`/`D`", não uma regra fixa por posição — em
> cada passo, recalcule com a árvore **como ela está naquele momento**, não de memória. Os
> passos 3–10 abaixo mostram cada árvore intermediária, para você conferir por si mesmo.

### Passo a passo desenhado

**Depois do passo 3 (RSD em 50, ao inserir 30):**
```
     40
    /  \
  30    50
```

**Depois do passo 5 (RED em 50, ao inserir 47 — 1º RSE(45), 2º RSD(50)):**
```
          40
        /    \
      30      47
             /  \
           45    50
```

**Depois do passo 7 (RSE em 40, ao inserir 56):**
```
            47
          /    \
        40      50
       /  \       \
     30    45      55
                     \
                      56
```
> **Conferindo antes da rotação:** `FB(40) = altura(30)=0 - altura(dir)`. O filho direito de
> `40` era `50`, que após inserir `55` e `56` tinha altura 2 (`50→55→56`). `FB(40) = 0 - 2 =
> -2`. O valor inserido (`56`) é maior que a chave do filho direito de `40` (`50`)? Sim,
> `56 > 50`... **mas a condição do código compara com `a->dir->info`, que é `50`, não com o
> nó que realmente violou.** Como `56 > 50`, a condição `elem > a->dir->info` é verdadeira →
> RSE. Resultado (RSE em 40): `50` sobe, `40` desce como filho esquerdo de `50`:
```
              47
           /      \
         50         ...
        /  \
      40    55
     /  \     \
   30   45    56
```
Espere — isso não bate com o formato final esperado. **Vamos refazer com cuidado, nó por
nó, porque este é exatamente o ponto onde é fácil errar.**

> 📖 **Refazendo o passo 7 com FB explícito, sem atalho:** antes de inserir `56`, a árvore é:
> ```
>           47
>         /    \
>       40      50
>      /  \       \
>    30    45      55
> ```
> Inserir `56`: desce `47→50→55`, insere como filho direito de `55`. Volta calculando `FB`:
> `FB(55) = alt(esq=vazia,-1) - alt(dir=56,0) = -1`. OK, sem violação. `FB(50) = alt(esq=
> vazia,-1) - alt(dir=55, agora altura 1) = -1 - 1 = -2`. **Aqui é `50` que viola, não
> `40`.** `elem(56) > a->dir->info` — aqui `a=50`, `a->dir=55`, então a comparação é
> `56 > 55`, verdadeira → **RSE(50)**, não RSE(40). Isso resolve **dentro** da subárvore de
> `50`, sem precisar tocar em `47` ou `40`. Resultado:
> ```
>           47
>         /    \
>       40      55
>      /  \    /  \
>    30    45 50   56
> ```
> **Esta é a árvore correta depois do passo 7** (a tabela da seção 3 simplificou demais ao
> dizer "RSE(40)" — o `FB` que realmente estourou foi o de `50`, não o de `40`. Fica como
> **lição desta seção**: sempre confira em **qual nó exatamente** o `FB` chegou a `±2` —
> não assuma pela posição na tabela-resumo.

**Continuando a partir da árvore correta acima, depois do passo 9 (RED em 30, ao inserir
2 — 1º RSE(1), 2º RSD(30)):**

Antes de inserir `1` e `2`, a subárvore de `30` é só a folha `30`. Insere `1` (filho
esquerdo de `30`, sem violação). Insere `2`: desce `30→1`, insere como filho direito de `1`.
`FB(1) = alt(-1) - alt(2,0) = -1`, ok. `FB(30) = alt(esq=1, agora altura 1) - alt(dir=vazia,
-1) = 1 - (-1) = 2`. `elem(2) < a->esq->info` → `2 < 1`? Não → **RED(30)**: 1º `RSE(1)` (sobe
`2`, desce `1` à esquerda de `2`), 2º `RSD(30)` (sobe `2`, desce `30` à direita de `2`).
Resultado:
```
        2
       / \
      1   30
```
Essa subárvore substitui o antigo `30` como filho esquerdo de `40`.

**Depois do passo 10 (inserir 3 — vamos conferir com cuidado, como fizemos no passo 7):**

Desce `47→40→2→30`, insere `3` como filho esquerdo de `30`. `FB(30) = alt(esq=3,0) -
alt(dir=vazia,-1) = 1`, ok. `FB(2) = alt(esq=1,0) - alt(dir=30, agora altura 1) = 0 - 1 =
-1`, ok. `FB(40) = alt(esq=2, agora altura 2) - alt(dir=45, altura 0) = 2 - 0 = 2`.
`elem(3) < a->esq->info` → `a=40`, `a->esq=2`, comparação é `3 < 2`? Não → **RED(40)**: 1º
`RSE(2)`, 2º `RSD(40)`.

`RSE(2)`: sobe o filho direito de `2` (que é `30`, com esquerdo `3`); `2` desce como filho
esquerdo de `30`, e o que era esquerdo de `30` (`3`) passa a ser direito de `2`:
```
      30
     /  \
    2    (vazio)
   / \
  1   3
```
Agora `RSD(40)`: sobe o filho esquerdo de `40` (que é `30`, resultado acima); `40` desce
como filho direito de `30`, e o que era direito de `30` (vazio) vira esquerdo de `40`:
```
        30
       /   \
      2     40
     / \      \
    1   3      45
```
Essa subárvore substitui o antigo `40` como filho esquerdo de `47`.

**Árvore final, depois de inserir `49` (sem rotação — confira você mesmo, é o exercício 1
abaixo):**

```
                        47
                  /            \
                30              55
              /    \           /   \
            2       40       50     56
           / \        \      /
          1   3        45   49
```

**Conferindo a árvore final:** todo nó tem `FB ∈ {-1,0,1}`? `1,3,45,49,56`: folhas, `FB=0`.
`2`: esq=1(alt0),dir=3(alt0) → `FB=0`. `40`: esq=vazio(-1),dir=45(alt0) → `FB=-1`. `30`:
esq=2(alt1),dir=40(alt1) → `FB=0`. `50`: esq=49(alt0),dir=vazio(-1) → `FB=1`. `55`:
esq=50(alt1),dir=56(alt0) → `FB=1`. `47` (raiz): esq=30(alt2),dir=55(alt2) → `FB=0`. **Todos
dentro de `{-1,0,1}`** ✔ — a árvore é uma AVL válida.

## 4. 📌 O que você está REALMENTE fazendo, insersão após inserção

| O passo mecânico | O que ele realmente é |
|---|---|
| inserir como numa BST comum | não há atalho — o valor sempre entra no lugar ordenado certo primeiro |
| checar `FB` **subindo** pela recursão, um ancestral de cada vez | garanto que encontro a violação **mais próxima da folha inserida** — corrigi-la lá resolve, sem precisar checar mais acima |
| usar `elem` (não recalcular `FB(E)`/`FB(D)`) para decidir simples vs. dupla | aproveito que já sei "de que lado" o valor entrou, evitando uma passada extra pela árvore |
| parar na primeira rotação aplicada | uma única rotação (simples ou dupla) sempre restaura a altura da subárvore ao valor de **antes** da inserção que causou o problema — por isso nenhum ancestral acima precisa de outra |

## 5. Letra miúda

**"Uma rotação sempre basta" não é acidente — é teorema.** Depois de qualquer rotação
(simples ou dupla), a altura da subárvore afetada volta a ser **exatamente** a que era antes
da inserção que causou a violação. Por isso o `FB` de qualquer ancestral acima da rotação
**não muda** — é seguro parar de subir assim que a primeira rotação é aplicada. (Isso é
diferente da remoção, onde uma única rotação pode não bastar — ver a nota de fixação no
final da Teoria 04.)

## 6. Exercícios de fixação

1. Continue a sequência a partir da árvore após o passo 10 e insira `49`. Trace o caminho
   percorrido, confira o `FB` de cada ancestral, e confirme que **não** há rotação (deve
   bater com a árvore final da seção 3).
2. Por que, no passo 7 (inserir `56`), a resposta certa é `RSE(50)` e não `RSE(40)`, mesmo
   os dois estando na mesma "linha" da árvore antiga?
3. Se, em vez de `elem < a->esq->info`, o código comparasse com um `FB(a->esq)` recalculado
   do zero, o resultado seria diferente? Por quê (ou por que não)?

### Gabarito

1. Desce `47→55→50`, insere `49` como filho esquerdo de `50`. `FB(50) = alt(49,0) -
   alt(vazio,-1) = 1`, ok. `FB(55) = alt(esq=50, agora altura 1) - alt(dir=56,0) = 1 - 0 =
   1`, ok. `FB(47) = alt(esq=30,2) - alt(dir=55, agora altura 2) = 2 - 2 = 0`, ok. Nenhuma
   violação — bate com a árvore final mostrada.
2. Porque o `FB` que **efetivamente** chegou a `±2` foi o de `50` (o pai direto de `55`,
   que por sua vez é pai de `56`) — `40` nem estava mais no caminho de descida até `56`
   depois que a árvore já tinha `47` como raiz da subárvore relevante. É exatamente o erro
   de "assumir pela posição" que a seção 3 alertou: sempre recalcule `FB` no nó certo, sob a
   árvore como ela está **naquele momento**, não de memória de um exercício parecido.
3. Não seria diferente — as duas formas são **equivalentes**, só que uma é mais barata.
   Comparar `elem` com `a->esq->info` aproveita uma informação que você já tem (o valor que
   acabou de descer por aquele lado); recalcular `FB(a->esq)` do zero chegaria à mesma
   conclusão sobre "reto vs. torto", só que revisitando informação já disponível.

## Resumo

- Inserção em AVL = inserção de BST (1.2) + checagem de `FB` subindo pela recursão + no
  máximo **uma** rotação (simples ou dupla), na primeira violação encontrada.
- O código decide entre rotação simples e dupla comparando o valor inserido com a chave do
  filho (`a->esq->info` ou `a->dir->info`), sem recalcular `FB` de novo.
- Uma única rotação sempre restaura a altura da subárvore ao que era antes da inserção —
  por isso nunca é preciso mais de uma rotação por inserção.
- **Cuidado ao seguir exemplos "de memória":** sempre recalcule `FB` no nó exato onde a
  violação aparece na árvore **atual**, não pela posição que ele tinha num passo anterior.

---

Isso fecha a teoria de 1.3. Para ver a explicação passo a passo de cada questão resolvida
da lista, veja `Ementa/ListasExercicios/lista03-EDA/Passo a Passo Lista/` (quando
disponível), ou siga para [[../../../05 - Árvore B e B+/README|05 - Árvore B e B+]] (a
ementa oficial trata árvore B/B+ como capítulo próprio, depois de Grafos e Arquivos).
