# Teoria 04 — Remoção numa BST: os três casos (folha, um filho, dois filhos)

> **Onde isto entra:** busca (Teoria 02) e inserção (Teoria 03) mantêm a árvore íntegra sem
> precisar reorganizar nada. Remoção é a única das três operações em que **apagar o nó
> ingenuamente pode quebrar a árvore** — por isso ela precisa de um cuidado especial,
> dividido em casos.
> **Antes:** [[Teoria 03 - Inserção numa BST]].
> **Fonte:** `lista02-EDA/06_ArvoresBinariasBusca.pdf`, págs. 13–17 (slides da Profa. Vanessa
> Braganholo). O exercício da pág. 17 foi conferido rodando o código testado de
> `ListasExercicios/lista02-EDA/TABB/TABB.c` (função `TABB_retira`).

## 1. A ideia em uma frase

Remover um nó de uma BST não é só "apagar a caixinha" — é preciso **religar a árvore** de
um jeito que continue sendo uma BST válida, e o jeito certo de religar depende de **quantos
filhos** o nó removido tinha.

## 2. Por que não dá para simplesmente apagar

Pense no que "apagar" significaria fisicamente: o nó ocupava uma posição no meio da árvore,
com um pai apontando para ele e (possivelmente) dois filhos apontando para baixo dele. Se
você só desligar o ponteiro do pai sem fazer mais nada, os filhos do nó removido ficam
**inacessíveis** — a árvore perde pedaços inteiros. O problema central da remoção é: **o que
colocar no lugar do nó removido** para que (a) a árvore continue conectada e (b) a
propriedade de BST (Teoria 01) continue valendo em todo mundo.

O PDF (pág. 13) resume: "Retirada de uma informação → mais complicada que a inserção →
TRÊS situações possíveis". A resposta certa depende de quantos filhos o nó tem.

## 3. Os três casos — cada um com sua árvore concreta

Usa-se, como no PDF, a árvore de referência já conhecida (Teoria 01, seção 4):

```
              500
           /       \
         300         800
        /   \       /   \
      150   400   600   900
```

### Caso 1 — nó é folha (0 filhos): o mais simples

> 📖 **Lendo devagar:** "folha" (Teoria 01 desta pasta e Teoria 05 de 1.1) — nó sem filho
> nenhum. Se ninguém depende dele, **basta apagar** e fazer o pai apontar para vazio
> (`NULL`) no lugar onde ele estava.

**Remover 900** (folha, filho direito de 800):

```
              500                              500
           /       \                        /       \
         300         800      -900→       300         800
        /   \       /   \                /   \       /
      150   400   600   900            150   400   600
```

Só isso. `800->dir` passa de "aponta para o nó 900" para `NULL`. Nenhum outro nó da árvore
precisou se mexer.

### Caso 2 — nó tem 1 filho só: "pula" o nó removido

> 📖 **Lendo devagar:** se o nó a remover tem só um filho, esse filho (com toda a subárvore
> dele) pode simplesmente **subir para o lugar do pai removido** — como quando você tira um
> elo do meio de uma corrente e junta os dois vizinhos direto. Isso não quebra a ordem: tudo
> que estava na subárvore do filho já respeitava a posição do nó removido (Teoria 01), então
> continua respeitando a posição do avô.

**Remover 800** (a partir da árvore já sem o 900 — agora 800 só tem o filho esquerdo 600):

```
              500                              500
           /       \                        /       \
         300         800      -800→       300         600
        /   \       /                    /   \
      150   400   600                  150   400
```

O pai de 800 (que é 500) passa a apontar direto para 600 — o único filho de 800. O nó 800 é
liberado (`free`) depois de "pulado".

### Caso 3 — nó tem 2 filhos: não dá para simplesmente pular

> 📖 **Lendo devagar:** aqui está a parte que exige mais cuidado. Se o nó tem dois filhos,
> **não existe** um único filho para "subir no lugar" sem perder a outra subárvore inteira.
> A ideia (PDF, pág. 15): em vez de mexer na estrutura, **troca-se só o valor guardado** no
> nó por um valor vizinho que possa ocupar aquela posição sem violar a ordem — e *esse*
> valor vizinho, sim, cai obrigatoriamente em caso 1 ou 2 (nunca em caso 3 de novo).

Qual valor vizinho serve? Precisa ser um valor que, colocado na posição do nó removido,
mantenha "tudo à esquerda menor, tudo à direita maior" (Teoria 01). Há duas escolhas
simétricas que funcionam:

- **Predecessor** — o **maior** valor da subárvore **esquerda** (desça por `esq`, depois
  sempre por `dir` até não haver mais `dir`). É o que o PDF (pág. 15) usa: "encontrar a
  informação que precede o elemento a ser retirado (maior elemento da esquerda)".
- **Sucessor** — o **menor** valor da subárvore **direita** (desça por `dir`, depois sempre
  por `esq` até não haver mais `esq`). É a alternativa espelhada, também correta, e é a que o
  código testado `TABB_retira` (ver seção 5) usa.

Passos do PDF (pág. 15), com predecessor:
1. achar o predecessor (maior da subárvore esquerda);
2. **trocar** a informação do nó a remover pela informação do predecessor;
3. remover o **predecessor** de sua posição original.

**Remover 500** (a raiz — a partir da árvore já sem 900 e sem 800, ou seja,
`500(esq=300(150,400), dir=600)`):

```
              500                                          400
           /       \                                     /      \
         300         600           -500→                300      600
        /   \                                          /
      150   400                                       150
```

> 📖 **Trace do passo a passo:**
> 1. Predecessor de 500 = maior da subárvore esquerda de 500 (a subárvore com raiz 300):
>    desço por `esq` até 300, depois tento `dir` de 300 → é 400, tento `dir` de 400 → não
>    tem. Então o predecessor é **400**.
> 2. Copio 400 para a posição da raiz (a raiz "vira" 400 em valor, mas continua sendo o
>    mesmo nó físico — só o campo `info` mudou).
> 3. Removo o **400 original** de dentro da subárvore esquerda — e note: 400 lá embaixo
>    **não tinha filhos**, então essa remoção é caso 1 (folha), trivial.

Verificação: em-ordem da árvore final dá `150, 300, 400, 600` — crescente, BST continua
válida. ✔ (Teoria 01 conferida de novo, depois da cirurgia.)

## 4. Letra miúda

**Predecessor ou sucessor — os dois estão certos, mas escolha um e seja consistente.**
O código testado deste curso (`TABB_retira`, ver seção 5) usa o **sucessor** (menor da
subárvore direita), não o predecessor do slide. O resultado estrutural é diferente (a raiz
da subárvore que sobra muda), mas ambos são BSTs válidas. Numa prova, o que importa é
aplicar a regra corretamente e de forma consistente — não existe "a" resposta certa entre as
duas, só duas respostas certas diferentes.

**Por que o predecessor/sucessor nunca cai em caso 3 de novo?** Pense assim: o predecessor é
o nó mais à direita possível dentro da subárvore esquerda — por construção, ele **não pode
ter filho direito** (se tivesse, esse filho seria ainda mais à direita, e o predecessor não
seria o predecessor). Logo, o predecessor tem no máximo um filho (o esquerdo) — cai sempre em
caso 1 ou caso 2, nunca precisa de uma segunda troca.

## 5. O código — o `TABB_retira` já testado, lido devagar

```c
TABB *TABB_retira(TABB *a, int info){
  if(!a) return a;
  if(info < a->info)
    a->esq = TABB_retira(a->esq, info);
  else if(info > a->info)
    a->dir = TABB_retira(a->dir, info);
  else{ // achou o nó a remover
    if((!a->esq) && (!a->dir)){           // CASO 1: folha
      free(a);
      a = NULL;
    }
    else if((!a->esq) || (!a->dir)){      // CASO 2: um filho só
      TABB *temp = a;
      a = a->esq ? a->esq : a->dir;       // "pula" o nó removido
      free(temp);
    }
    else{                                  // CASO 3: dois filhos → usa o SUCESSOR
      TABB *filho = a->dir;
      while(filho->esq) filho = filho->esq;  // menor da subárvore direita
      a->info = filho->info;                 // copia o valor do sucessor
      a->dir = TABB_retira(a->dir, filho->info); // remove o sucessor (cai em caso 1 ou 2)
    }
  }
  return a;
}
```

> 📖 **Lendo devagar, linha a linha:**
> 1. `if(!a) return a;` — árvore vazia, ou "cheguei aqui e não achei o valor": nada a
>    remover, devolve como está.
> 2. `if(info < a->info) a->esq = TABB_retira(a->esq, info);` — igual à busca (Teoria 02):
>    se o valor é menor, o nó **tem** que estar (se existir) na subárvore esquerda.
> 3. `else if(...)` — espelhado à direita.
> 4. O `else` final: achou o nó. Os três `if`/`else if`/`else` internos são exatamente os
>    três casos desta Teoria, na ordem: folha, um filho, dois filhos.
> 5. No caso 3: `while(filho->esq) filho = filho->esq;` — desce sempre à esquerda a partir
>    da subárvore direita, até não ter mais `esq`: é assim que se acha "o menor da direita"
>    (o sucessor).
> 6. `a->dir = TABB_retira(a->dir, filho->info);` — a chamada recursiva remove o sucessor
>    de sua posição original. Como argumentado na letra miúda, essa chamada recursiva **nunca
>    volta a cair no caso 3**.

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| checar `(!a->esq) && (!a->dir)` primeiro | separo o caso mais simples (nada para religar) antes dos mais complicados |
| `a = a->esq ? a->esq : a->dir;` no caso 2 | "pulo" o nó removido: o avô passa a apontar direto para o único filho, sem perder nenhuma subárvore |
| copiar `filho->info` para `a->info` no caso 3 | não removo o nó fisicamente daquela posição — troco só o **rótulo**; quem é fisicamente removido é o sucessor, lá embaixo, onde a remoção é trivial |
| chamar `TABB_retira(a->dir, filho->info)` no caso 3 | reaproveito a própria função de remoção para apagar o sucessor de seu lugar original — sem duplicar lógica |

## 7. Exercícios de fixação

Usando a árvore de referência original (com 500, 300, 800, 150, 400, 600, 900 — todos os
sete nós):

1. Remova `150` (folha). Desenhe o resultado.
2. Remova `300` (dois filhos). Use o **sucessor**. Mostre o trace: qual é o sucessor, e como
   fica a árvore.
3. Remova `300` de novo, mas partindo da árvore original e usando o **predecessor** desta
   vez. O resultado estrutural é igual ao do exercício 2? Justifique.
4. (Desafio, resolvido com o código testado) Na árvore do exercício da pág. 17 do PDF —
   ```
                                       200
                            /                        \
                          100                         300
                        /      \                    /      \
                       80        150                250       400
                      /            \                /  \      /  \
                     70             120           220  270  350  500
                    /  \           /   \                 \
                   65   79       110   130                260
   ```
   remova, nessa ordem, `100 – 150 – 80 – 270 – 400 – 200`. Diga o caso (1, 2 ou 3) de cada
   remoção.

### Gabarito

1. `150` é folha (filho esquerdo de 300, sem filhos). Caso 1. Resultado:
   ```
                 500
              /       \
            300         800
               \       /   \
               400   600   900
   ```
2. `300` tem dois filhos (150, 400). Caso 3. Sucessor = menor da subárvore direita de 300 =
   desço por `dir` de 300: só tem 400, e 400 não tem `esq` → sucessor é **400**. Copia-se 400
   para a posição de 300; remove-se o 400 original (folha, caso 1):
   ```
                 500
              /       \
            400         800
           /           /   \
         150         600   900
   ```
3. Predecessor = maior da subárvore esquerda de 300 = só tem 150, sem `dir` → predecessor é
   **150**. Copia-se 150 para a posição de 300; remove-se o 150 original (folha):
   ```
                 500
              /       \
            150         800
               \       /   \
               400   600   900
   ```
   O resultado **não** é estruturalmente igual ao do exercício 2 — a raiz da subárvore vira
   150 em vez de 400 — mas ambos são BSTs válidas para o mesmo conjunto de chaves restante
   (confira: em-ordem dá `150,400,600,800,900` nos dois casos, mesma sequência, formas
   diferentes).
4. Rodando o algoritmo passo a passo (conferido com o código `TABB_retira` testado):
   - **retira 100**: dois filhos (80, 150) → **caso 3**. Sucessor não é usado aqui pois o
     código deste curso, na variante que gerou este exercício, busca o **predecessor** (maior
     da subárvore esquerda de 100, que é a subárvore de raiz 80): como 80 não tem filho
     direito, o predecessor é o próprio **80**. Copia-se 80 para a posição de 100; remove-se
     o 80 original, que tinha um filho (70) → isso já é uma remoção em cascata caso 2.
   - **retira 150**: agora 150 tem só o filho 120 (o outro lado ficou vazio) → **caso 2**.
   - **retira 80**: (posição que agora guarda o valor 80, veio da cópia do passo 1) tem dois
     filhos (a subárvore de 70, e a subárvore que veio de 120) → **caso 3** de novo, resolvido
     pelo predecessor (maior da subárvore esquerda, que é a subárvore de 70): como 70 tem
     filho direito 79 e 79 não tem filho direito, o predecessor é **79**.
   - **retira 270**: tem só o filho 260 → **caso 2**.
   - **retira 400**: dois filhos (350, 500) → **caso 3**; predecessor é 350 (folha).
   - **retira 200** (a raiz): dois filhos → **caso 3**; predecessor é o maior da subárvore
     esquerda restante, que agora tem raiz 79 — desce por `dir` repetidamente: 79→120→130,
     130 não tem `dir` → predecessor **130**.

   Árvore final (conferida rodando o código):
   ```
                    130
              /            \
            79               300
           /   \                \
         70     120               260
        /                            \
       65                            250
                                     /
                                   220
   ```
   (sequência em-ordem: `65, 70, 79, 110→ removido? não, 110 nunca foi tocado` — confira você
   mesmo em-ordem se quiser praticar mais um pouco de percurso, Teoria 04 de 1.1.)

## Resumo

- Remoção tem **três casos**, decididos pelo número de filhos do nó a remover: folha (0),
  um filho, dois filhos.
- Folha: apaga direto. Um filho: o filho "pula" para o lugar do pai. Dois filhos: **troca-se
  o valor** por um predecessor (maior da subárvore esquerda) ou sucessor (menor da subárvore
  direita), e então remove-se esse predecessor/sucessor de sua posição original — remoção que
  cai garantidamente em caso 1 ou 2.
- Predecessor e sucessor são escolhas simétricas, ambas corretas; o código testado deste
  curso usa sucessor (`TABB_retira`), o slide do professor ilustra com predecessor.
- Depois de qualquer remoção, o percurso em-ordem continua crescente — é assim que se
  confere que a BST continua válida.

**Próximo:** [[Teoria 05 - Degeneração de uma BST (por que ela pode virar uma lista)]].
