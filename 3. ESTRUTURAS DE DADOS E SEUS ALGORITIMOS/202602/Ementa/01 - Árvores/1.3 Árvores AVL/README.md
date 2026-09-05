# 1.3 Árvores AVL

## Objetivo de aprendizagem

- Definir fator de balanceamento e a invariante AVL.
- Identificar os 4 casos de desbalanceamento (LL, RR, LR, RL) e aplicar a rotação correta.
- Explicar por que a invariante AVL garante altura O(log n).
- Entender o custo de manter o balanceamento (rotações após inserção/remoção).

## Roteiro de leitura

- **SZ (livro-base):** capítulo/seção "Árvores Balanceadas" ou "Árvores AVL" — cobre fator de balanceamento e as 4 rotações com o mesmo enfoque usado aqui (conferir página exata).
- **CO (Cormen):** o CLRS **não** usa AVL como exemplo principal de árvore balanceada — usa **árvores rubro-negras** (cap. 13). Vale a leitura por contraste: rubro-negra relaxa a condição de balanceamento (usa cor + regras de caminho preto em vez de diferença de altura estrita) para reduzir o número de rotações por operação, trocando um pouco de altura por menos reestruturação. Não é o mesmo algoritmo de AVL, mas ajuda a entender *por que* existe mais de uma estratégia de árvore auto-balanceada (conferir página exata).
- **CE (Celes):** verificar se o Celes tem seção de árvores AVL — em geral esse livro é mais focado em estruturas clássicas (listas, pilhas, filas, árvores binárias/BST) e pode não aprofundar rotações AVL. Não force a citação se não encontrar o capítulo — nesse caso, use SZ como referência principal de implementação também.
- **KR:** não se aplica um capítulo específico além do já citado em ponteiros/structs (1.1) — a implementação de rotação é manipulação de ponteiros entre nós já existentes.

## Notas de estudo elaboradas

### Fator de balanceamento e invariante

Fator de balanceamento de um nó = altura(subárvore direita) − altura(subárvore esquerda). Uma árvore é **AVL-válida** se, para todo nó, esse fator ∈ {−1, 0, +1}.

Essa invariante é o que diferencia AVL de uma BST comum (1.2): toda AVL é uma BST, mas nem toda BST é AVL.

### As 4 rotações

Desbalanceamento é sempre detectado em um nó (o "nó crítico") após inserção ou remoção. O caso é determinado observando dois níveis: o filho mais alto do nó crítico, e o neto mais alto desse filho.

| Caso | Situação | Correção |
|---|---|---|
| **LL** | Desbalanço à esquerda, e o desbalanço do filho esquerdo também é à esquerda | Rotação simples à direita |
| **RR** | Desbalanço à direita, e o desbalanço do filho direito também é à direita | Rotação simples à esquerda |
| **LR** | Desbalanço à esquerda, mas o desbalanço do filho esquerdo é à direita | Rotação dupla: esquerda no filho, depois direita no nó crítico |
| **RL** | Desbalanço à direita, mas o desbalanço do filho direito é à esquerda | Rotação dupla: direita no filho, depois esquerda no nó crítico |

Cada rotação é O(1) (só religa um número fixo de ponteiros) e restaura a invariante localmente. Depois de uma rotação, é preciso continuar subindo pela árvore recalculando fator de balanceamento — em **inserção**, no máximo 1 rotação (ou rotação dupla) já resolve toda a árvore; em **remoção**, pode ser necessário rebalancear em cascata subindo até a raiz (mais de uma rotação em ancestrais diferentes).

### Por que garante O(log n)

A prova formal (relação com números de Fibonacci) mostra que a altura mínima possível de uma árvore AVL com n nós é Θ(log n) — a invariante de fator ∈ {−1,0,1} impede a degeneração linear que uma BST comum permite. Isso garante busca, inserção e remoção em O(log n) no pior caso, ao custo de rotações extras a cada modificação.

### Passo a passo: uma sequência de inserção que força os 4 casos

Insira, nesta ordem, `30, 20, 40, 10, 25, 5` numa AVL inicialmente vazia:

1. `30` → raiz. `20` → filho esquerdo. `40` → filho direito. Árvore balanceada (FB de todo nó ∈ {-1,0,1}), sem rotação.
2. Insere `10`: vai para a esquerda de `20`. Fator de balanceamento de `30` = altura(dir=40)=0 − altura(esq=20)= 1 → -1, ainda ok. Sem rotação.
3. Insere `25`: vai para a direita de `20` (25 > 20). Ainda balanceado.
   ```
              30
            /    \
          20      40
         /  \
       10    25
   ```
4. Insere `5`: vai para a esquerda de `10`. Agora o nó `20` tem subárvore esquerda de altura 1 (10→5) e subárvore direita de altura 0 (25) — ok. Mas o nó `30`: subárvore esquerda (20, com 10,25,5) tem altura 2, subárvore direita (40) tem altura 0 → diferença 2. **Desbalanceou em `30`.**
   - O novo elemento (`5`) é menor que `30->esq->info` (20)? Sim → **caso LL**. Aplica-se rotação simples à direita em `30`.
   - **Antes:**
     ```
                30
              /    \
            20      40
           /  \
         10    25
        /
       5
     ```
   - **Depois da rotação direita em 30:** `20` sobe e vira a nova raiz da subárvore; `30` desce e vira filho direito de `20`, herdando a antiga subárvore direita de `20` (`25`) como sua nova subárvore esquerda:
     ```
              20
            /    \
          10      30
         /       /  \
        5      25    40
     ```
     Agora todos os fatores de balanceamento voltam para {-1,0,1}.

Se em vez disso o próximo elemento inserido fosse tal que ele caísse **à direita** do filho esquerdo do nó desbalanceado (ex.: inserir algo entre 20 e 30 depois de já ter 10 à esquerda de 20), o caso seria **LR** (rotação dupla: esquerda no filho, depois direita no nó crítico) — os casos RR e RL são espelhados destes.

## Exemplos em C

Trecho abaixo adaptado de uma implementação real e testada de AVL, disponível completa em `ListasExercicios/lista03-EDA/TAVL/` (`TAVL.h` + `TAVL.c`).

```c
// TAVL.h
typedef struct avl {
  int info;
  struct avl *esq, *dir;
  int alt;              // altura do nó, mantida incrementalmente (evita recalcular do zero)
} TAVL;

TAVL *TAVL_busca(int e, TAVL *t);
TAVL *TAVL_insere(int e, TAVL *t);
TAVL *TAVL_retira(int x, TAVL *t);
int   FB(TAVL *t);       // fator de balanceamento
```

```c
// TAVL.c — as 4 rotações

static TAVL *TAVL_rot_dir(TAVL *t) {        // rotação simples à direita (caso LL)
  TAVL *novo = t->esq;
  t->esq = novo->dir;
  novo->dir = t;
  t->alt = max(calc_alt(t->esq), calc_alt(t->dir)) + 1;      // recalcula alturas: t primeiro
  novo->alt = max(calc_alt(novo->esq), t->alt) + 1;           // ...depois novo (que agora é pai de t)
  return novo;                              // novo é a nova raiz da subárvore
}

static TAVL *TAVL_rot_esq(TAVL *t) {        // rotação simples à esquerda (caso RR) — espelho da acima
  TAVL *novo = t->dir;
  t->dir = novo->esq;
  novo->esq = t;
  t->alt = max(calc_alt(t->esq), calc_alt(t->dir)) + 1;
  novo->alt = max(calc_alt(novo->dir), t->alt) + 1;
  return novo;
}

static TAVL *TAVL_rot_esq_dir(TAVL *t) {    // rotação dupla LR: esquerda no filho, depois direita no nó
  t->esq = TAVL_rot_esq(t->esq);
  return TAVL_rot_dir(t);
}

static TAVL *TAVL_rot_dir_esq(TAVL *t) {    // rotação dupla RL: direita no filho, depois esquerda no nó
  t->dir = TAVL_rot_dir(t->dir);
  return TAVL_rot_esq(t);
}

// Inserção com rebalanceamento automático
TAVL *TAVL_insere(int e, TAVL *t) {
  if (!t) {
    t = (TAVL *) malloc(sizeof(TAVL));
    t->info = e;
    t->alt = 0;
    t->esq = t->dir = NULL;
  }
  else if (e < t->info) {
    t->esq = TAVL_insere(e, t->esq);
    if (calc_alt(t->esq) - calc_alt(t->dir) == 2)
      // decide LL vs LR comparando o NOVO elemento com a chave do filho esquerdo —
      // isso identifica pra que lado o desbalanço do "neto" está, sem inspecionar
      // FB em dois níveis explicitamente
      if (e < t->esq->info) t = TAVL_rot_dir(t);        // caso LL
      else                  t = TAVL_rot_esq_dir(t);    // caso LR
  }
  else if (e > t->info) {
    t->dir = TAVL_insere(e, t->dir);
    if (calc_alt(t->dir) - calc_alt(t->esq) == 2)
      if (e > t->dir->info) t = TAVL_rot_esq(t);        // caso RR
      else                  t = TAVL_rot_dir_esq(t);    // caso RL
  }
  t->alt = max(calc_alt(t->esq), calc_alt(t->dir)) + 1;
  return t;
}
```

Código completo e testado em `ListasExercicios/lista03-EDA/TAVL/` (inclui também `TAVL_retira`, que rebalanceia em cascata subindo pela árvore — repare que ali o teste de qual rotação aplicar já não pode comparar com o elemento inserido, pois é remoção; usa diretamente o fator de balanceamento do filho, `FB(t->esq)`/`FB(t->dir)`, para decidir entre rotação simples e dupla).

## Pontos de atenção / pegadinhas comuns de prova

- **Errar o caso** (LL vs LR, RR vs RL) é o erro mais comum — sempre olhe o desbalanço em dois níveis (nó crítico → filho → neto), nunca decida só pelo primeiro nível.
- **Esquecer o rebalanceamento em cascata na remoção**: diferente da inserção (que para na primeira rotação), a remoção pode exigir corrigir múltiplos ancestrais até a raiz.
- Depois de qualquer rotação, é obrigatório **recalcular a altura/fator de balanceamento dos nós envolvidos** (o nó que desceu e o que subiu) antes de continuar subindo na árvore — esquecer isso quebra o restante do algoritmo.
- Rotação dupla (LR/RL) é literalmente duas rotações simples em sequência — não é uma operação atômica separada, é composição das duas simples.

## Anotações pessoais

## Exercícios resolvidos
