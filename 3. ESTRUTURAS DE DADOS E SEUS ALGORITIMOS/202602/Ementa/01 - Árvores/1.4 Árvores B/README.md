# 1.4 Árvores B

## Objetivo de aprendizagem

- Definir ordem *m* de uma árvore B e suas propriedades estruturais.
- Explicar por que árvores B são a escolha certa para memória secundária (disco), diferente de AVL/BST (memória principal).
- Executar split de nó na inserção e merge/redistribuição na remoção.
- Calcular altura máxima de uma árvore B em função de m e n.

## Roteiro de leitura

- **SZ (livro-base):** capítulo/seção "Árvores B" — este é o livro que mais aprofunda o tema no curso, já que o Szwarcfiter tem foco explícito em estruturas para memória secundária (conecta diretamente com o módulo 03, Arquivos e Ordenação Externa) (conferir página exata).
- **CO (Cormen):** cap. 18 "Árvores B" — referência mais formal para as provas de altura máxima O(log_m n) e para os pseudocódigos de B-TREE-SPLIT-CHILD, B-TREE-INSERT e B-TREE-DELETE (conferir página exata).
- **CE (Celes):** este livro é focado em estruturas de memória principal (listas, pilhas, filas, árvores binárias/BST) — **não** costuma ter capítulo de árvores B. Não force a citação; use SZ e CO como referências principais aqui.
- **KR:** não se aplica diretamente — árvore B é mais sobre organização de blocos/páginas de disco do que sobre um recurso específico da linguagem C.

## Notas de estudo elaboradas

### Motivação: por que não usar AVL em disco?

AVL e BST são otimizadas para acesso em memória principal (RAM), onde qualquer acesso a um nó custa o mesmo. Em disco, o custo dominante é o **número de acessos** (I/O), não o processamento — e cada acesso a disco é ordens de magnitude mais lento que um acesso em RAM. Uma árvore binária com n elementos tem altura O(log₂ n); uma árvore B com ordem m grande tem altura O(log_m n), drasticamente menor para m grande (ex.: m=100 reduz a altura por um fator de ~log₂(100) ≈ 6.6 em relação à binária). Menos altura = menos acessos a disco para achar qualquer chave.

### Propriedades (árvore B de ordem m)

- Todo nó tem no máximo **m filhos** e no máximo **m−1 chaves**.
- Todo nó (exceto raiz) tem no mínimo **⌈m/2⌉ filhos** e **⌈m/2⌉−1 chaves** (garante que os nós fiquem sempre pelo menos "meio cheios" — evita desperdício de espaço/altura).
- A raiz tem no mínimo 2 filhos (se não for folha).
- **Todas as folhas estão na mesma profundidade** — essa é a propriedade central que garante altura balanceada.
- As chaves dentro de um nó estão ordenadas, e funcionam como "separadores" entre os filhos (busca dentro do nó decide qual filho seguir).

### Inserção (split)

Insere-se a chave em uma folha (posição ordenada). Se o nó ultrapassar m−1 chaves (overflow), ele é **dividido (split)**: a chave do meio sobe para o nó pai (inserida lá), e o nó original vira dois nós com as chaves restantes. Se o pai também estourar, o split se propaga para cima — no pior caso, até criar uma nova raiz (esse é o único jeito da árvore B crescer em altura, e é por isso que todas as folhas ficam sempre na mesma profundidade).

### Remoção (merge/redistribuição)

Remove-se a chave (se estiver em nó interno, substitui por predecessor/sucessor, análogo à BST). Se o nó ficar com menos que ⌈m/2⌉−1 chaves (underflow), duas estratégias:
1. **Redistribuição (empréstimo)**: se um nó irmão adjacente tem chaves sobrando (mais que o mínimo), empresta uma chave via o pai (rotação de chave passando pelo separador no pai).
2. **Merge (fusão)**: se nenhum irmão tem sobra, funde o nó com um irmão e a chave separadora do pai, podendo propagar underflow para cima (análogo ao split, mas na direção oposta).

### Complexidade

| Operação | Complexidade |
|---|---|
| Busca | O(log_m n) níveis × O(log m) ou O(m) por nó (busca dentro do nó) |
| Inserção | O(log_m n) |
| Remoção | O(log_m n) |

### Passo a passo: split de nó numa árvore B de ordem m=3

Ordem m=3 → cada nó tem no máximo 2 chaves (m−1) e no máximo 3 filhos. Inserindo `10, 20, 5` num nó folha único (a raiz):

```
insere 10 → [10]
insere 20 → [10, 20]                (nó cheio: 2 chaves = m-1, ok, ainda não estourou)
insere 5  → [5, 10, 20]             (3 chaves > m-1=2 → OVERFLOW)
```

O nó estourou. **Split**: a chave do meio (`10`) sobe para um novo nó pai (que também vira a nova raiz, já que este era o único nó da árvore), e as chaves restantes se dividem em dois nós-filhos:

```
              [10]
             /     \
          [5]      [20]
```

Se a árvore já tivesse um pai antes do split, a chave `10` seria inserida *nele* (não criaria uma raiz nova) — e se esse pai também estourasse, o split se propagaria mais um nível acima. Uma nova raiz só é criada quando o split alcança o topo da árvore — é o único mecanismo pelo qual uma árvore B cresce em altura, e por isso todas as folhas permanecem sempre na mesma profundidade.

## Exemplos em C

Não há implementação de árvore B nas listas de exercícios deste curso (`ListasExercicios/`) — exemplo abaixo é ilustrativo, escrito para acompanhar a explicação acima (ordem *m* configurável, chaves e ponteiros de filho em arrays).

```c
#define M 3                        // ordem da árvore B (máx. de filhos por nó)

typedef struct no_b {
  int chaves[M - 1];               // até m-1 chaves, mantidas ordenadas
  struct no_b *filhos[M];          // até m ponteiros para filhos (folha: todos NULL)
  int n_chaves;                    // quantas chaves o nó tem atualmente
  int folha;                       // 1 se for nó-folha, 0 caso contrário
} NoB;

// Insere `chave` na posição ordenada correta dentro de um nó QUE AINDA
// TEM ESPAÇO (n_chaves < M-1). Não decide split — isso é responsabilidade
// de quem chama, depois de verificar overflow.
void insere_em_no(NoB *no, int chave) {
  int i = no->n_chaves - 1;
  while (i >= 0 && no->chaves[i] > chave) {
    no->chaves[i + 1] = no->chaves[i];   // abre espaço deslocando pra direita
    i--;
  }
  no->chaves[i + 1] = chave;
  no->n_chaves++;
}

// Divide um nó cheio (n_chaves == M-1, prestes a ultrapassar) em dois,
// promovendo a chave do meio. Retorna a chave promovida e preenche
// *nova_direita com o novo nó irmão (metade direita das chaves/filhos).
// Quem chama é responsável por inserir a chave promovida no nó pai
// (ou criar uma nova raiz, se o nó dividido já era a raiz).
int divide_no(NoB *no, NoB **nova_direita) {
  int meio = (M - 1) / 2;                 // índice da chave do meio
  int chave_promovida = no->chaves[meio];

  NoB *direita = malloc(sizeof(NoB));
  direita->folha = no->folha;
  direita->n_chaves = 0;

  // copia as chaves à direita do meio para o novo nó
  for (int i = meio + 1; i < no->n_chaves; i++)
    direita->chaves[direita->n_chaves++] = no->chaves[i];

  if (!no->folha)                         // se não é folha, também move os filhos
    for (int i = meio + 1; i <= no->n_chaves; i++)
      direita->filhos[i - (meio + 1)] = no->filhos[i];

  no->n_chaves = meio;                    // nó original fica só com a metade esquerda
  *nova_direita = direita;
  return chave_promovida;
}
```

Para a inserção completa, a lógica em quem chama `insere_em_no`/`divide_no` desce recursivamente até a folha correta, insere, e — se `n_chaves` ultrapassar `M-1` — chama `divide_no` e propaga a chave promovida para o pai (criando uma nova raiz se o nó dividido não tinha pai). É exatamente o pseudocódigo B-TREE-SPLIT-CHILD/B-TREE-INSERT do CLRS (cap. 18) traduzido para C.

## Pontos de atenção / pegadinhas comuns de prova

- **Confundir "ordem m"** com número de chaves — ordem m = máximo de **filhos**; máximo de chaves é m−1. Esse é o erro mais comum em exercícios de árvore B.
- Split sempre acontece de baixo para cima e pode propagar até criar uma nova raiz — é assim que a árvore B ganha altura (nunca "no meio").
- Nem todo nó preenchido pela metade é igual — o mínimo é ⌈m/2⌉−1 chaves, arredondamento pra cima importa em m ímpar vs par.
- Não confundir árvore B com árvore B+ (1.5) — em árvore B, dados/registros podem estar em qualquer nó (interno ou folha); em B+, só nas folhas.

## Anotações pessoais

## Exercícios resolvidos
