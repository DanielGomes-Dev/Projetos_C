# Q7 — Colorindo uma árvore totalmente balanceada (vermelho/preto)

> **Origem:** `lista01-EDA.pdf`, item (Q7) · **Código resolvido:** [[../Q7/claude/main.c]]
> **Antes disto, veja:** [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 01 - O que é uma árvore (terminologia)|1.1 Teoria 01]] (nível de um nó)

## 1. O que o exercício pede

> Se a estrutura `TAB` tivesse um campo `int cor`, defina uma função que, ao receber uma
> árvore binária "sem cor" e **totalmente balanceada** (distância da raiz a qualquer folha
> sempre igual), retorne essa árvore colorida só de vermelho e preto, de forma que **o nó
> pai nunca tenha a mesma cor de seus filhos**: `void colore (TAB* arv);`

## 2. A ideia geral (o mapa antes da viagem)

"Totalmente balanceada" aqui é a **letra miúda** que resolve o problema inteiro: como
**todas** as folhas estão na mesma profundidade (é a definição de árvore perfeita — 1.1,
Teoria 06), o **nível** de um nó é uma informação confiável e fácil de calcular. E, se
raiz é preta, nível 1 é vermelho, nível 2 é preto, nível 3 é vermelho... — cores alternando
por nível — então **todo pai e todo filho automaticamente têm cores diferentes**, porque
filho está sempre exatamente 1 nível abaixo do pai. Não é preciso nenhuma lógica
complicada de "escolher a cor evitando conflito" — a alternância por nível já garante isso
de graça.

> **Por que isso não funcionaria numa árvore não-balanceada?** Se a árvore não fosse
> perfeita, ainda seria possível colorir por paridade de nível, mas a pergunta do exercício
> ("nós NUNCA têm a mesma cor dos filhos") continuaria valendo do mesmo jeito — a exigência
> de balanceamento aqui é mais sobre garantir que "todo nível existe por igual" do que uma
> necessidade estrita do algoritmo de colorir. O exercício pede especificamente esse caso
> mais simples.

## 3. Resolução passo a passo

### Passo 1 — struct local (o `TAB.h` fornecido não tem campo `cor`)

```c
typedef struct ab {
    int info;
    struct ab *esq, *dir;
    int cor;
} TAB;
```

Como o exercício é hipotético ("se esta estrutura TIVESSE um campo cor"), a solução
redefine `TAB` localmente com o campo extra, em vez de mexer no `TAB.h` compartilhado com
as outras questões.

### Passo 2 — a recursão que alterna cor por nível

```c
static void colore_aux(TAB *arv, int cor) {
    if (!arv)
        return;
    arv->cor = cor;
    colore_aux(arv->esq, !cor);
    colore_aux(arv->dir, !cor);
}

void colore(TAB *arv) {
    colore_aux(arv, PRETO);
}
```

> 📖 **Lendo devagar:**
> 1. `colore(arv)` chama `colore_aux(arv, PRETO)` — a **raiz sempre começa preta** (decisão
>    arbitrária, mas precisa ser consistente).
> 2. `arv->cor = cor` — pinta o nó atual com a cor recebida.
> 3. `colore_aux(arv->esq, !cor)` — chama recursivamente nos filhos, mas com a cor
>    **invertida** (`!cor`: se `cor` é `PRETO` (definido como 1), `!cor` vira `0`
>    (`VERMELHO`), e vice-versa).
> 4. Como cada chamada recursiva desce **um nível**, e cada nível inverte a cor do anterior,
>    o resultado automático é: nível 0 (raiz) preto, nível 1 vermelho, nível 2 preto, ... —
>    a alternância que garante "pai nunca igual ao filho".

### Passo 3 — conferindo com a árvore do exemplo (7 nós, altura 2 — perfeita)

```
              4  (nível 0)
            /   \
          2       6   (nível 1)
         / \     / \
        1   3   5   7  (nível 2)
```

| Nível | Nós | Cor |
|---|---|---|
| 0 | `4` | PRETO |
| 1 | `2`, `6` | VERMELHO |
| 2 | `1`, `3`, `5`, `7` | PRETO |

**Conferindo a regra "pai ≠ filho":** `4`(PRETO) tem filhos `2`,`6`(VERMELHO) — diferente ✔.
`2`(VERMELHO) tem filhos `1`,`3`(PRETO) — diferente ✔. `6`(VERMELHO) tem filhos `5`,`7`
(PRETO) — diferente ✔. Nenhum par pai-filho tem a mesma cor.

## 4. Resultado final

`imp_sim` (em-ordem) imprime `1[PRETO] 2[VERMELHO] 3[PRETO] 4[PRETO] 5[PRETO] 6[VERMELHO]
7[PRETO]` — confira que cada nó tem a cor esperada pela tabela acima (a ordem em-ordem só
muda a **sequência** de impressão, não a cor de cada um).

## 5. Habilidades necessárias

- [ ] Nível de um nó = profundidade a partir da raiz → [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 01 - O que é uma árvore (terminologia)|1.1 Teoria 01]]
- [ ] Árvore perfeita: todas as folhas na mesma profundidade → [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 06 - Tipos de árvore binária (cheia, completa, perfeita)|1.1 Teoria 06]]
- [ ] Operador `!` em C aplicado a inteiro (`!1 == 0`, `!0 == 1`) → `KR`, cap. 2.

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — árvore com um nó só

`colore(raiz)`: `colore_aux(raiz, PRETO)` pinta a raiz de preto; `colore_aux(NULL, ...)`
(dos dois lados) retorna direto sem fazer nada. Resultado: um nó, preto.

### Aquecimento 2 — árvore de altura 1 (3 nós)

Raiz `A` com filhos `B` e `C` (ambos folha): `A`=PRETO (nível 0); `B`,`C`=VERMELHO (nível
1, `!PRETO`). Confere: pai preto, filhos vermelhos — diferentes.
