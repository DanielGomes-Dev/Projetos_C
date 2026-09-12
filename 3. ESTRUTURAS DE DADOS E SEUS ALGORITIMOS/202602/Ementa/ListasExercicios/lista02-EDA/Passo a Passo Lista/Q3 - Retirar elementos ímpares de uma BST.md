# Q3 — Retirar todos os elementos ímpares de uma BST

> **Origem:** `lista02-EDA.pdf`, item (Q3) · **Código resolvido:** [[../Q3/claude/main.c]]
> **Antes disto, veja:** [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 04 - Remoção numa BST (os três casos)|1.2 Teoria 04]] (a função `TABB_retira` usada aqui)

## 1. O que o exercício pede

> Uma função que, dada uma BST qualquer, retire todos os elementos ímpares:
> `TABB* retira_impares(TABB* a);`

Parece com a Q6 de lista01 (retirar pares de árvore binária qualquer), mas a estratégia
aqui é **completamente diferente** — e mais simples — porque a árvore é uma BST.

## 2. A ideia geral (o mapa antes da viagem)

**Por que não adaptar o código de Q6 (lista01)?** Em Q6, a árvore não tinha ordem — então
"pendurar a subárvore direita onde der" não quebrava nenhuma invariante. Numa BST, isso
**quebraria** a propriedade de ordenação (1.2, Teoria 01): não dá pra simplesmente
rearranjar os filhos de qualquer jeito depois de remover um nó.

A solução aqui evita o problema todo com uma estratégia em duas fases:
1. **Coletar primeiro**: percorrer a árvore (sem alterar nada ainda) e guardar todos os
   valores ímpares num vetor.
2. **Remover depois, um de cada vez**, usando a função `TABB_retira` já pronta e testada
   (que sabe tratar os 3 casos de remoção corretamente — 1.2, Teoria 04) — sem nunca
   mexer diretamente em ponteiros.

> **Por que não remover durante o mesmo percurso que coleta?** Porque remover um nó
> **durante** a recursão que está percorrendo a própria árvore é arriscado: o `free`
> pode invalidar ponteiros que a recursão ainda vai usar para continuar andando. Separar
> "decidir o quê remover" de "remover de fato" evita esse problema.

## 3. Resolução passo a passo

### Passo 1 — contar quantos nós existem (para saber o tamanho do vetor)

```c
static int conta(TABB *a) {
    return a ? 1 + conta(a->esq) + conta(a->dir) : 0;
}
```

Percurso simples, conta todos os nós (não só os ímpares) — o vetor precisa de espaço para
o pior caso (todos ímpares).

### Passo 2 — coletar os ímpares em ordem crescente

```c
static int coleta_impares(TABB *a, int *v, int i) {
    if (!a)
        return i;
    i = coleta_impares(a->esq, v, i);
    if (a->info % 2 != 0)
        v[i++] = a->info;
    i = coleta_impares(a->dir, v, i);
    return i;
}
```

> 📖 **Lendo devagar:** é um percurso **em-ordem** (esquerda, nó, direita — 1.1, Teoria 04)
> — por isso os ímpares saem no vetor **em ordem crescente**. O parâmetro `i` é "quantos já
> coletei até agora"; a cada ímpar encontrado, `v[i++] = a->info` guarda e avança o índice.
> A função devolve o `i` atualizado porque C não tem passagem de parâmetro "por referência"
> simples para inteiros — o jeito de "lembrar quantos já coletei" entre as chamadas
> recursivas é devolver e reatribuir esse contador.

### Passo 3 — remover cada um, usando a função já pronta

```c
TABB *retira_impares(TABB *a) {
    int n = conta(a);
    if (n == 0)
        return a;

    int *v = malloc(sizeof(int) * n);
    int k = coleta_impares(a, v, 0);
    for (int j = 0; j < k; j++)
        a = TABB_retira(a, v[j]);
    free(v);
    return a;
}
```

`TABB_retira` (releia [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 04 - Remoção numa BST (os três casos)|1.2 Teoria 04]]) já sabe lidar
com os 3 casos (folha, um filho, dois filhos — este último via substituição pelo
predecessor). Chamando-a uma vez por valor coletado, a árvore permanece **sempre válida**
entre uma remoção e outra.

### Conferindo com a árvore do exemplo

Valores inseridos: `50, 31, 70, 20, 45, 63, 80, 12, 27`. Ímpares: `31, 45, 63, 27` (em
ordem crescente de valor, que é a ordem em que `coleta_impares` os encontra: `27, 31, 45,
63`? — não, o vetor sai em ordem **crescente pela posição na árvore em-ordem**, que
**coincide** com ordem crescente de valor numa BST: `27, 31, 45, 63`).

Remover, um a um, cada valor de `[27, 31, 45, 63]` com `TABB_retira` — cada remoção usa o
caso certo (folha, um filho, ou substituição por predecessor) automaticamente, sem que
`retira_impares` precise saber qual caso é qual.

## 4. Resultado final

Depois das 4 remoções, a árvore só contém `50, 70, 20, 80, 12` (todos pares).

**Conferindo:** o percurso em-ordem final deveria mostrar só números pares, em ordem
crescente — e a propriedade de BST (1.2, Teoria 01) deve continuar valendo em toda a
árvore (nenhuma remoção deveria ter "torcido" a ordenação).

## 5. Habilidades necessárias

- [ ] Remoção numa BST com os 3 casos → [[../../../01 - Árvores/1.2 Árvores Binárias de Busca/Teoria - passo a passo/Teoria 04 - Remoção numa BST (os três casos)|1.2 Teoria 04]]
- [ ] Em-ordem produz sequência crescente numa BST → [[../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 04 - Percursos em profundidade (pré-ordem, em-ordem, pós-ordem)|1.1 Teoria 04]]
- [ ] Alocar vetor de tamanho dinâmico com `malloc` → `KR`, cap. 5.

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — árvore só com ímpares

Se todos os `n` nós são ímpares, `coleta_impares` enche o vetor inteiro (`k == n`), e o
laço final remove **todos** os nós, um a um — a árvore termina vazia (`a` vira `NULL`
depois da última remoção, já que `TABB_retira` devolve `a` atualizado a cada chamada).

### Aquecimento 2 — árvore sem nenhum ímpar

`coleta_impares` percorre tudo mas nunca escreve em `v` (`k == 0`). O laço `for (j=0; j<0;
...)` não roda nenhuma vez — a árvore volta exatamente como entrou.
