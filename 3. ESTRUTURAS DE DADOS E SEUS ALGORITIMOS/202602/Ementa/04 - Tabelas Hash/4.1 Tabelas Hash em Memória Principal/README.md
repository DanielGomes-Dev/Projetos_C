# 4.1 Tabelas Hash em Memória Principal

## Objetivo de aprendizagem

- Entender como uma função hash mapeia chaves para posições de um vetor e o que torna uma função hash "boa".
- Dominar as duas famílias de tratamento de colisão — encadeamento separado e endereçamento aberto — e suas variantes.
- Saber calcular e interpretar o fator de carga, e explicar por que ele governa a complexidade real da tabela.
- Entender quando e por que uma tabela precisa de rehashing.

## Roteiro de leitura

- **SZ (livro-base):** capítulo sobre tabelas de espalhamento (hash), seção de memória principal — cobre função hash, colisões e os métodos de tratamento. *(conferir página exata)*
- **CO (Cormen):** cap. 11 "Tabelas Hash" — cobertura teórica rigorosa: análise de colisões sob a hipótese de hashing uniforme simples, funções hash (método da divisão, método da multiplicação), hashing universal como defesa contra pior caso adversarial. *(conferir página exata)*
- **CE (Celes):** capítulo de implementação de tabelas hash em C — normalmente mostra encadeamento separado com listas ligadas nos buckets, e às vezes endereçamento aberto com linear probing. Útil para a fase de codar a estrutura. *(conferir página exata)*
- **KR:** cap. 6 "Structs" — relevante para implementar o bucket como `struct` com ponteiro `next` (lista ligada) quando usar encadeamento separado. *(conferir página exata)*

## Notas de estudo elaboradas

### Função hash

Uma função hash `h(chave) → índice ∈ [0, m-1]` mapeia um universo grande (ou infinito) de chaves para um vetor de `m` posições. Propriedades desejáveis:

- **Distribuição uniforme:** chaves "típicas" devem se espalhar uniformemente pelas `m` posições, minimizando colisões.
- **Determinismo:** a mesma chave sempre produz o mesmo índice.
- **Custo baixo:** o cálculo de `h(chave)` deve ser O(1) (ou próximo disso), senão perde-se a vantagem sobre outras estruturas.

Métodos clássicos de construção:
- **Método da divisão:** `h(k) = k mod m`. Simples, mas sensível à escolha de `m` — `m` primo (e não próximo de uma potência de 2) costuma evitar padrões ruins nas chaves.
- **Método da multiplicação:** `h(k) = ⌊m · (k·A mod 1)⌋`, com `A` uma constante irracional (Cormen sugere `A ≈ (√5 - 1)/2`). Menos sensível à escolha de `m`.
- **Hashing universal:** escolhe a função hash aleatoriamente de uma família de funções antes de saber quais chaves serão inseridas. Garante, em expectativa, bom desempenho mesmo contra um adversário que conhece o algoritmo — defesa contra ataques de negação de serviço via colisões forçadas.

### Colisões: duas famílias de solução

**Encadeamento separado (separate chaining):** cada posição do vetor é a cabeça de uma lista ligada; colisões viram nós na mesma lista.

**Endereçamento aberto (open addressing):** todos os elementos ficam no próprio vetor; em colisão, uma sequência de sondagem (*probing*) procura a próxima posição livre.
- *Linear probing:* `h(k, i) = (h'(k) + i) mod m`. Simples, mas sofre de **clustering primário** (blocos de posições ocupadas crescem e se fundem, piorando sondagens futuras).
- *Quadratic probing:* `h(k, i) = (h'(k) + c₁i + c₂i²) mod m`. Reduz clustering primário, mas introduz **clustering secundário** (chaves com mesmo hash inicial seguem a mesma sequência de sondagem).
- *Double hashing:* `h(k, i) = (h₁(k) + i·h₂(k)) mod m`. O passo de sondagem depende da própria chave via uma segunda função hash — praticamente elimina clustering, é o método com melhor desempenho prático entre os três.

### Fator de carga (load factor)

`α = n / m` (n = elementos inseridos, m = tamanho da tabela). É a variável que realmente determina o desempenho:

| Método | Complexidade média (busca) | Observação |
|---|---|---|
| Encadeamento separado | O(1 + α) | α pode passar de 1 sem quebrar a tabela (listas crescem) |
| Endereçamento aberto | O(1 / (1 − α)) | **precisa** de α < 1; degrada rapidamente perto de α → 1 |

Pior caso em ambos os métodos é O(n) (todas as chaves colidindo na mesma posição/sequência) — isso é o que hashing universal tenta evitar em expectativa.

### Rehashing

Quando α ultrapassa um limiar (tipicamente 0.7–0.75 em endereçamento aberto, podendo ser maior em encadeamento), a tabela é redimensionada: aloca-se um vetor maior (em geral o dobro) e **todas** as chaves são reinseridas com a nova função hash (que depende do novo `m`). Custa O(n), mas amortizado sobre as inserções que motivaram o crescimento o custo por operação continua O(1).

### Exemplo passo a passo: colisão em encadeamento vs. endereçamento aberto

Tabela com `m = 7` posições (índices 0 a 6), função hash `h(k) = k mod 7`. Inserindo, nesta ordem: **10, 3, 17, 5, 24, 12, 21**.

Primeiro, os hashes de cada chave:

| Chave | h(k) = k mod 7 |
|---|---|
| 10 | 3 |
| 3  | 3 |
| 17 | 3 |
| 5  | 5 |
| 24 | 3 |
| 12 | 5 |
| 21 | 0 |

Repare que **10, 3, 17 e 24 colidem todos na posição 3**, e **5 e 12 colidem na posição 5** — um caso propositalmente ruim para evidenciar a diferença entre os dois métodos.

**Encadeamento separado** — cada posição vira uma lista; a ordem de inserção fica preservada dentro da lista (aqui, inserindo no início):

```
0: 21
1: (vazio)
2: (vazio)
3: 24 → 17 → 3 → 10      (lista com as 4 chaves que colidiram)
4: (vazio)
5: 12 → 5                (lista com as 2 chaves que colidiram)
6: (vazio)
```

Custo de busca por `10`: percorre a lista da posição 3 até achar — no pior caso, 4 comparações (mas as outras 6 posições continuam O(1) ou vazias).

**Endereçamento aberto com linear probing** — `h(k, i) = (h'(k) + i) mod 7`; ao colidir, tenta a próxima posição:

```
Inserção de 10 → posição 3 livre → ocupa 3.
Inserção de 3  → posição 3 ocupada → tenta 4 → livre → ocupa 4.
Inserção de 17 → posição 3 ocupada → tenta 4 (ocupada) → tenta 5 → livre → ocupa 5.
Inserção de 5  → posição 5 ocupada (pelo 17!) → tenta 6 → livre → ocupa 6.
Inserção de 24 → posição 3 ocupada → tenta 4,5,6 (todas ocupadas) → tenta 0 → livre → ocupa 0.
Inserção de 12 → posição 5 ocupada → tenta 6 (ocupada) → tenta 0 (ocupada) → tenta 1 → livre → ocupa 1.
Inserção de 21 → posição 0 ocupada (pelo 24!) → tenta 1 (ocupada) → tenta 2 → livre → ocupa 2.

0: 24
1: 12
2: 21
3: 10
4: 3
5: 17
6: 5
```

Note o **clustering primário**: a colisão original em torno da posição 3 "vazou" e acabou empurrando até `5` (que originalmente mapeia pra posição 5) para a posição 6, e depois `12`, `24` e `21` para posições cada vez mais distantes de onde "deveriam" cair — o bloco ocupado (3,4,5,6,0,1,2 — quase a tabela toda) cresceu e se fundiu num único cluster grande. É exatamente esse efeito cascata que motiva quadratic probing e double hashing.

## Exemplos em C

### Tabela hash com encadeamento separado

```c
#include <stdio.h>
#include <stdlib.h>

#define M 7  // número de posições da tabela (idealmente primo)

// Nó da lista ligada de cada bucket
typedef struct hash_no {
    int chave;
    struct hash_no *prox;
} HashNo;

// A tabela é um vetor de ponteiros — cada posição é a cabeça de uma lista
typedef struct {
    HashNo *bucket[M];
    int n;  // número de elementos inseridos, para calcular o fator de carga
} TabelaHash;

void tabela_inicializa(TabelaHash *t) {
    int i;
    for (i = 0; i < M; i++) t->bucket[i] = NULL;
    t->n = 0;
}

int h(int chave) {
    return chave % M;  // método da divisão
}

// Insere sempre no início da lista do bucket -> O(1)
void tabela_insere(TabelaHash *t, int chave) {
    int i = h(chave);
    HashNo *novo = (HashNo *) malloc(sizeof(HashNo));
    novo->chave = chave;
    novo->prox = t->bucket[i];
    t->bucket[i] = novo;
    t->n++;
    // fator de carga atual: (float) t->n / M
    // se passar de ~0.75-1.0, seria o momento de considerar rehashing
}

// Busca percorre só a lista do bucket correspondente, não a tabela toda
HashNo *tabela_busca(TabelaHash *t, int chave) {
    HashNo *p = t->bucket[h(chave)];
    while (p != NULL && p->chave != chave) p = p->prox;
    return p;  // NULL se não encontrar
}
```

A complexidade de `tabela_busca` é O(1 + α) em média — o "1" é o cálculo do hash (sempre O(1)), o "α" é o tamanho médio da lista que pode ser preciso percorrer.

### Tabela hash com endereçamento aberto (linear probing)

```c
#define M 7
#define VAZIO -1  // marcador de posição livre (assumindo chaves não-negativas)

int tabela[M];

void tabela_inicializa_open(void) {
    int i;
    for (i = 0; i < M; i++) tabela[i] = VAZIO;
}

// Insere sondando linearmente até achar posição livre
int tabela_insere_open(int chave) {
    int i, pos;
    for (i = 0; i < M; i++) {
        pos = (h(chave) + i) % M;  // h(k, i) = (h'(k) + i) mod M
        if (tabela[pos] == VAZIO) {
            tabela[pos] = chave;
            return pos;
        }
    }
    return -1;  // tabela cheia (não deveria acontecer se alpha < 1 for mantido)
}
```

Note que a busca em endereçamento aberto precisa seguir a **mesma sequência de sondagem** usada na inserção — se parar na primeira posição vazia sem checar se a chave já passou por ali antes de um removido, o algoritmo quebra (por isso a nota sobre "tombstones" na deleção, nos pontos de atenção abaixo).

## Pontos de atenção / pegadinhas comuns de prova

- Fator de carga é uma **razão** (n/m), não o número absoluto de elementos — dobrar o número de elementos sem redimensionar a tabela dobra α, não o "quanto está cheia" em termos absolutos.
- Em endereçamento aberto, α deve ser sempre < 1 (não há como inserir mais elementos que posições); em encadeamento separado isso não é uma restrição.
- Linear probing sofre de clustering **primário**; quadratic probing resolve o primário mas introduz **secundário** — são fenômenos diferentes, não confundir.
- Deleção em endereçamento aberto não pode simplesmente esvaziar a posição — isso quebraria cadeias de sondagem de elementos inseridos depois. Usa-se um marcador de "removido" (tombstone).
- Complexidade O(1) de hash é **média/amortizada**, não garantida — no pior caso (todas as chaves colidindo) cai para O(n), diferente de uma árvore balanceada que garante O(log n) sempre.

## Anotações pessoais

## Exercícios resolvidos
