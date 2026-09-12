# Q5 — BST de figuras geométricas, ordenada por área

> **Origem:** `lista02-EDA.pdf`, item (Q5) · **Código resolvido:** [[../Q5/claude/main.c]]
> **Antes disto, veja:** [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 01 - A propriedade de árvore binária de busca|1.2 Teoria 01]] (o que significa "chave" de uma BST)

## 1. O que o exercício pede

> Reescreva as operações básicas da ABB para armazenar as figuras geométricas quadrado,
> triângulo, retângulo e trapézio. A **área** define a subárvore esquerda/direita. A
> impressão é em ordem simétrica, mostrando área e dimensões.

## 2. A ideia geral (o mapa antes da viagem)

Até aqui (Q1-Q4), a BST guardava só um `int`. Este exercício pede a mesma ideia, mas com um
dado **composto**: cada nó guarda uma figura inteira (tipo + dimensões), e a **chave de
comparação** (o que decide esquerda/direita) não é o dado inteiro, é **um campo calculado
dele** — a área. Isso mostra que "BST" não é sobre guardar números — é sobre **qualquer**
tipo de dado que tenha uma chave comparável.

## 3. Resolução passo a passo

### Passo 1 — o tipo `Figura` e o cálculo de área na construção

```c
typedef enum { QUADRADO, TRIANGULO, RETANGULO, TRAPEZIO } TipoFig;

typedef struct {
    TipoFig tipo;
    double d1, d2, d3;
    double area;
} Figura;

static Figura fig_quadrado(double lado) {
    Figura f = { QUADRADO, lado, 0, 0, lado * lado };
    return f;
}
```

> 📖 **Lendo devagar:** a `area` é calculada **uma vez**, no momento em que a figura é
> criada (`fig_quadrado`, `fig_triangulo`, etc.) — e fica guardada no struct, pronta para
> ser comparada depois. Isso evita recalcular a área toda vez que a árvore precisa comparar
> duas figuras (comparar é só olhar `f.area`, um `double` já pronto).

### Passo 2 — inserção comparando por área, não pelo struct inteiro

```c
static TABBF *abbf_insere(TABBF *a, Figura fig) {
    if (!a)
        return abbf_cria(fig);
    if (fig.area < a->fig.area)
        a->esq = abbf_insere(a->esq, fig);
    else
        a->dir = abbf_insere(a->dir, fig);
    return a;
}
```

> 📖 **Lendo devagar:** é **exatamente** a mesma estrutura de `TABB_insere` (que você já
> viu implicitamente em Q1-Q4, usada para montar as árvores de exemplo) — a única mudança é
> que a comparação usa `fig.area < a->fig.area` em vez de `x < a->info`. Note: `else`
> manda pra direita mesmo em caso de **empate** (`fig.area == a->fig.area`) — figuras com a
> mesma área convivem na árvore, só que sempre à direita de quem já estava lá (a mesma
> convenção usada, por exemplo, em `TABB_insere` original para valores repetidos).

### Passo 3 — busca e impressão seguem o mesmo padrão

```c
static TABBF *abbf_busca(TABBF *a, double area) {
    if (!a || a->fig.area == area)
        return a;
    if (area < a->fig.area)
        return abbf_busca(a->esq, area);
    return abbf_busca(a->dir, area);
}
```

Mesmíssima lógica de busca em BST (1.2, Teoria 02), só trocando `int info` por
`double area`.

### Conferindo com o exemplo do `main`

Figuras inseridas, na ordem, com suas áreas calculadas:

| Ordem de inserção | Figura | Área |
|---|---|---|
| 1ª | retângulo(4,5) | `4×5=20` |
| 2ª | quadrado(3) | `3×3=9` |
| 3ª | triângulo(6,4) | `6×4/2=12` |
| 4ª | trapézio(5,3,4) | `(5+3)×4/2=16` |
| 5ª | quadrado(6) | `6×6=36` |
| 6ª | triângulo(3,2) | `3×2/2=3` |

**Árvore resultante (comparando por área):**

```
                    20 (retângulo 4x5)
                 /                    \
            9 (quadrado 3)         36 (quadrado 6)
           /        \
    3 (tri. 3,2)   12 (tri. 6,4)
                        \
                    16 (trapézio 5,3,4)
```

**Trace da inserção de `12` (triângulo 6,4):** `12 < 20` → esquerda (`9`). `12 > 9` →
direita de `9` (vazio) → vira filho direito de `9`.

**Trace da inserção de `16` (trapézio):** `16 < 20` → esquerda (`9`). `16 > 9` → direita
(`12`). `16 > 12` → direita de `12` (vazio) → vira filho direito de `12`.

## 4. Resultado final

Impressão em ordem simétrica (crescente por área): `3.00 (triângulo 3,2) → 9.00 (quadrado
3) → 12.00 (triângulo 6,4) → 16.00 (trapézio 5,3,4) → 20.00 (retângulo 4,5) → 36.00
(quadrado 6)`.

**Conferindo:** busca por área `16.0` deve achar o trapézio (percorrendo `20→9→12→16`,
igual ao caminho de inserção); busca por uma área que não existe (ex.: `100.0`) deve
retornar "não encontrada".

## 5. Habilidades necessárias

- [ ] Chave de BST pode ser um campo calculado, não o dado inteiro → [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 01 - A propriedade de árvore binária de busca|1.2 Teoria 01]]
- [ ] Inserção e busca em BST (mesma estrutura, chave diferente) → [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 02 - Busca numa BST|1.2 Teoria 02]], [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 03 - Inserção numa BST|1.2 Teoria 03]]
- [ ] `enum` e `struct` para representar um tipo com variantes → `KR`, cap. 6.

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — duas figuras com a mesma área

Um quadrado de lado 4 (área 16) e um retângulo 8×2 (área 16): a segunda figura inserida
vai para a **direita** da primeira (empate resolvido "pra direita", mesma convenção de
`TABB_insere`), mesmo sendo formas diferentes.

### Aquecimento 2 — inserir só uma figura

`abbf_insere(NULL, fig_quadrado(5))`: `a` é `NULL`, então `abbf_cria` aloca o primeiro nó
direto — a árvore passa a ter só essa figura, sem filhos.
