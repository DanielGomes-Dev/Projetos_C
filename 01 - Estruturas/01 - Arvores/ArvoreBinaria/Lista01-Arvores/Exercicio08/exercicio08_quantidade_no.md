Para resolver este exercício, precisamos primeiro entender o que é um **nó interno**. Em uma árvore binária, um nó é considerado interno se ele **não é uma folha**. Ou seja, ele possui pelo menos um filho (seja à esquerda, à direita ou em ambos os lados).

Aqui está a implementação da função em C:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct ab {
    int info;
    struct ab *esq, *dir;
} TAB;

int ni(TAB *a) {
    // Caso base: se a árvore está vazia, não há nós
    if (a == NULL) {
        return 0;
    }

    // Verifica se o nó atual é uma folha (não tem filhos)
    if (a->esq == NULL && a->dir == NULL) {
        return 0;
    }

    // Se chegou aqui, o nó tem pelo menos um filho, logo é interno.
    // Retornamos 1 (o nó atual) + a soma dos nós internos das subárvores.
    return 1 + ni(a->esq) + ni(a->dir);
}
```

---

### Explicação da Lógica Recursiva

A função utiliza a estratégia de **dividir para conquistar**, baseada na definição recursiva de árvores binárias apresentada no seu material:

1.  **Caso Base 1 (`a == NULL`)**: Se o ponteiro for nulo, retornamos 0, pois uma árvore vazia não possui nós.
2.  **Caso Base 2 (Folha)**: Se `a->esq` e `a->dir` são ambos nulos, este nó é uma **folha**. Como queremos contar apenas os **internos**, retornamos 0 para este nó.
3.  **Passo Indutivo (Nó Interno)**: Se o nó não é nulo e possui ao menos um filho, ele é contado como **1**. Em seguida, chamamos a função recursivamente para investigar as subárvores à esquerda e à direita, somando todos os resultados.

### Exemplo Visual
Considere a árvore: `<1 <2> <3 <4> <5>>>`
* Nós **Folhas**: 2, 4 e 5.
* Nós **Internos**: 1 e 3.
* **Resultado de `ni`**: 2.

---

O resultado impresso pelo seu programa será: **3**.

Para entender por que o resultado é 3, vamos analisar a estrutura da árvore que você montou no `main` e identificar quem é pai (nó interno) e quem é folha.

### Estrutura da Árvore
Baseado no seu código:
* **a5** (6) e **a4** (5) são criados com filhos `NULL` (**Folhas**).
* **a3** (7) é pai de **a4** e **a5** (**Interno**).
* **a2** (3) é criado com filhos `NULL` (**Folha**).
* **a1** (2) é pai de **a2** (esquerda) e `NULL` (direita) (**Interno**).
* **raiz** (1) é pai de **a3** e **a1** (**Interno**).

Visualmente, a árvore fica assim:

```text
       (1)  <-- RAIZ (Interno)
      /   \
    (7)   (2) <-- Internos
    / \   /
  (5) (6)(3)  <-- Folhas
```

### O Passo a Passo da função `ni(raiz)`:

1.  **Nó (1):** Tem filhos? Sim. Então conta **1** e chama para os filhos.
2.  **Nó (7):** Tem filhos? Sim (5 e 6). Então conta **1** e chama para os filhos.
    * **Nó (5):** É folha? Sim. Retorna **0**.
    * **Nó (6):** É folha? Sim. Retorna **0**.
    * Soma do Nó (7) = $1 + 0 + 0 = 1$.
3.  **Nó (2):** Tem filhos? Sim (o 3). Então conta **1** e chama para os filhos.
    * **Nó (3):** É folha? Sim. Retorna **0**.
    * **Filho Direito:** É `NULL`. Retorna **0**.
    * Soma do Nó (2) = $1 + 0 + 0 = 1$.

### Resultado Final:
$$\text{Total} = 1 (\text{raiz}) + 1 (\text{nó 7}) + 1 (\text{nó 2}) = 3$$

---

### Observações sobre o seu código:
* **Saída do Printf:** O texto no seu `printf` diz "Existem 3 nós na arvore", mas para ser mais preciso e evitar confusão, seria melhor escrever "Existem 3 nós **internos** na arvore", já que o total de nós (incluindo as folhas) é 6.
* **Funções de Impressão:** Notei que em `ImpSim` e `ImpPos` você está chamando `ImpPre` dentro delas em vez de chamar a si mesmas recursivamente. Isso vai bagunçar a ordem da impressão se você tentar usá-las! O correto seria `ImpSim(a->esq)`, etc.