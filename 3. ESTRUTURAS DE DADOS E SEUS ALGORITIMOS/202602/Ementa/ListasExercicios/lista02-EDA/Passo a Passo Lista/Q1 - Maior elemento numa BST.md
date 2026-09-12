# Q1 — Maior elemento de uma árvore binária de busca

> **Origem:** `lista02-EDA.pdf`, item (Q1) · **Código resolvido:** [[../Q1/claude/main.c]]
> **Antes disto, veja:** [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 01 - A propriedade de árvore binária de busca|1.2 Teoria 01]] (a propriedade que torna este exercício simples)

## 1. O que o exercício pede

> Maior elemento da árvore: `TABB* maior(TABB *a);`

Mesmo enunciado da Q3 de lista01 — mas agora a árvore **é** uma BST.

## 2. A ideia geral (o mapa antes da viagem)

Compare com a Q3 de lista01 (árvore binária qualquer): lá, era preciso **olhar todo mundo**
(força bruta, O(n)), porque não havia garantia de onde o maior valor estaria. Numa BST, a
propriedade de ordenação (1.2, Teoria 01: tudo à esquerda é menor, tudo à direita é maior)
garante uma coisa poderosa: **o maior elemento está sempre no fim do caminho mais à
direita** — não existe maior valor "escondido" à esquerda de nada. Isso transforma um
problema O(n) em um problema O(altura).

## 3. Resolução passo a passo

```c
TABB *maior(TABB *a) {
    if (!a)
        return NULL;
    while (a->dir)
        a = a->dir;
    return a;
}
```

> 📖 **Lendo devagar:** nenhuma recursão nem comparação de valores é necessária — só
> **seguir sempre por `dir`** até não haver mais `dir` (`a->dir == NULL`). Esse último nó,
> por definição da BST, não tem nada maior que ele em lugar nenhum da árvore (se houvesse,
> estaria à direita dele, mas ele já é o mais à direita possível).

### Conferindo com a árvore do exemplo

Construída inserindo, nesta ordem, `50, 30, 70, 20, 40, 60, 80, 65` (com `TABB_insere`, que
desce comparando e insere no lugar certo — ver [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 03 - Inserção numa BST|1.2 Teoria 03]]):

```
              50
           /      \
         30        70
        /  \       /  \
      20   40    60    80
                          \
                          (65 fica à esquerda de 70, não de 80 — confira!)
```

Espere — vamos rastrear a inserção de `65` com cuidado: `65 > 50` → direita (`70`);
`65 < 70` → esquerda de `70`. Como `70` já tinha filho esquerdo `60`, `65` desce mais:
`65 > 60` → direita de `60`. Árvore correta:

```
              50
           /      \
         30        70
        /  \       /  \
      20   40    60    80
                    \
                    65
```

**Trace de `maior`:** começa em `50`. `50->dir = 70` (existe) → vai pra `70`. `70->dir = 80`
(existe) → vai pra `80`. `80->dir = NULL` → **para aqui**. Resultado: `80`.

## 4. Resultado final

`m->info = 80`. Só 2 passos (`50→70→80`) em vez de visitar os 8 nós — essa é a economia
real que a propriedade de BST compra.

**Conferindo:** o percurso em-ordem (1.1, Teoria 04) da árvore deveria terminar exatamente
em `80` — em-ordem numa BST sempre visita em ordem crescente, então o **último** valor
impresso é sempre o maior.

## 5. Habilidades necessárias

- [ ] Propriedade de BST (esquerda < pai < direita) → [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 01 - A propriedade de árvore binária de busca|1.2 Teoria 01]]
- [ ] Em-ordem numa BST produz sequência crescente → [[../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 04 - Percursos em profundidade (pré-ordem, em-ordem, pós-ordem)|1.1 Teoria 04]]

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — árvore com um nó só

`maior(TABB_cria(7,NULL,NULL))`: `a->dir` já é `NULL` desde o início — o `while` nem roda.
Resultado: o próprio `7`.

### Aquecimento 2 — árvore "torta" para a direita (pior caso)

`50 → 60 → 70 → 80` (cada inserção maior que a anterior): a árvore degenera numa fila só de
`dir`. `maior` ainda funciona corretamente (`80`), mas agora precisa de 3 passos (visita
todos os 4 nós) — o pior caso de uma BST degenerada tem o mesmo custo da força bruta (ver
[[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 05 - Complexidade e o risco de degeneração|1.2 Teoria 05]]).
