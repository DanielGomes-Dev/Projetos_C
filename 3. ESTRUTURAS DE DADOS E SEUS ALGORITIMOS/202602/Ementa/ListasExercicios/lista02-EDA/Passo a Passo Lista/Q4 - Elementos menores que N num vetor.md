# Q4 — Elementos menores que N, devolvidos num vetor

> **Origem:** `lista02-EDA.pdf`, item (Q4) · **Código resolvido:** [[../Q4/claude/main.c]]
> **Antes disto, veja:** [[../Q3/claude/main.c|Q3 - Retirar elementos ímpares de uma BST]] (mesma técnica de coletar num vetor com percurso em-ordem)

## 1. O que o exercício pede

> Uma função que, dada uma BST, retorne, **num vetor**, todos os elementos menores que `N`:
> `int* mN(TABB*a, int N);`

## 2. A ideia geral (o mapa antes da viagem)

Igual ao "coletar" da Q3, mas com uma vantagem extra que **só existe porque é BST**: se um
nó já tem valor `≥ N`, **toda a subárvore direita dele** também tem valores `≥ N` (1.2,
Teoria 01: tudo à direita é maior que o nó) — então nem vale a pena olhar aquele lado. Essa
"poda" é o que diferencia este exercício de simplesmente filtrar um percurso completo.

## 3. Resolução passo a passo

### Passo 1 — convenção de retorno (tamanho + dados no mesmo vetor)

```c
int *mN(TABB *a, int N) {
    int n = conta(a);
    int *v = malloc(sizeof(int) * (n + 1));
    int k = coleta_menores(a, N, v + 1, 0);
    v[0] = k;
    return v;
}
```

> 📖 **Lendo devagar:** como uma função em C não pode devolver "um vetor e também um
> inteiro" ao mesmo tempo de forma simples, a solução usa um truque comum: a **posição
> `[0]`** do vetor guarda **quantos** elementos foram encontrados, e as posições `[1..k]`
> guardam os elementos de fato. `v + 1` (aritmética de ponteiro) passa para
> `coleta_menores` o endereço logo **depois** da posição reservada para o tamanho — assim
> a função de coleta escreve a partir de `v[1]` sem precisar saber desse detalhe.

### Passo 2 — a coleta com poda

```c
static int coleta_menores(TABB *a, int N, int *v, int i) {
    if (!a)
        return i;
    i = coleta_menores(a->esq, N, v, i);
    if (a->info < N) {
        v[i++] = a->info;
        i = coleta_menores(a->dir, N, v, i);
    }
    return i;
}
```

> 📖 **Lendo devagar, comparando com `coleta_impares` (Q3):** a diferença-chave está no
> `if (a->info < N) { ... i = coleta_menores(a->dir, ...); }` — a chamada na subárvore
> **direita** só acontece **dentro** do `if`. Se `a->info >= N`, a função **nem tenta**
> olhar `a->dir` — é a poda: sabendo que tudo à direita de um nó `≥ N` também é `≥ N`,
> visitar aquele lado seria trabalho desperdiçado.

### Conferindo com a árvore do exemplo (N = 42)

Inserindo `50, 30, 70, 20, 40, 60, 80, 25, 35, 45`:

```
              50
           /      \
         30        70
        /  \       /  \
      20   40    60    80
        \    \
        25    45
          \
          35
```

**Trace de `coleta_menores` (em-ordem, com poda):**

| Nó visitado | `< 42`? | Ação |
|---|---|---|
| `20` | sim | coleta `20`; desce à direita (`25`) |
| `25` | sim | coleta `25`; desce à direita (`35`) |
| `35` | sim | coleta `35`; sem filho direito |
| `30` | sim | coleta `30`; sem filho direito |
| `40` | sim | coleta `40`; desce à direita (`45`) |
| `45` | **não** (`45 ≥ 42`) | **não coleta, e nem olha a subárvore direita de `45`** (poda) |
| `50` | não | não coleta, não desce à direita — **poda a subárvore inteira de `70`** (`60`, `80` nunca são visitados) |

Resultado coletado, em ordem crescente (é assim que a coleta em-ordem naturalmente
produz): `20, 25, 30, 35, 40`.

## 4. Resultado final

`r[0] = 5` (quantidade), `r[1..5] = 20, 25, 30, 35, 40`. Note que a poda evitou visitar
`60` e `80` — numa árvore maior, essa economia cresce proporcionalmente.

**Conferindo:** todo elemento do vetor deve ser `< 42`; e nenhum elemento `< 42` da árvore
deve estar faltando no vetor — os dois lados (nada a mais, nada a menos) precisam bater.

## 5. Habilidades necessárias

- [ ] Poda usando a propriedade de BST → [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 01 - A propriedade de árvore binária de busca|1.2 Teoria 01]]
- [ ] Convenção "tamanho na posição 0" e aritmética de ponteiro (`v + 1`) → `KR`, cap. 5.

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — N menor que tudo na árvore

Se `N` é menor que o menor valor da árvore, a poda acontece logo na raiz (`a->info >= N`),
e a subárvore direita inteira nunca é visitada — mas a subárvore **esquerda** ainda
precisa ser percorrida (pode ter valores menores que `N` lá, mesmo que raros). Resultado:
`r[0] = 0`.

### Aquecimento 2 — N maior que tudo na árvore

Nenhuma poda nunca acontece (`a->info < N` sempre verdadeiro) — a função percorre a árvore
inteira, coletando todos os valores em ordem crescente. Resultado: todos os `n` elementos.
