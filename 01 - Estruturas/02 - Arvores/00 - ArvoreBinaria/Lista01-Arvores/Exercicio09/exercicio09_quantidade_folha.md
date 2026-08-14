Para resolver o exercício **(Q9)**, precisamos identificar as características de um nó folha. Como visto no material, uma árvore binária é definida recursivamente. Um nó é considerado **folha** quando ele **não possui nenhum filho**, ou seja, tanto o seu ponteiro para a esquerda (`esq`) quanto o seu ponteiro para a direita (`dir`) são `NULL`.

---

### Implementação da Função em C

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct ab {
    int info;
    struct ab *esq, *dir;
} TAB;

int nf(TAB *a) {
    // 1. Caso base: se a árvore está vazia, não há folhas
    if (a == NULL) {
        return 0;
    }

    // 2. Verifica se o nó atual é uma folha
    // (Não tem filho à esquerda E não tem filho à direita)
    if (a->esq == NULL && a->dir == NULL) {
        return 1;
    }

    // 3. Se não for folha, continua a busca nas subárvores
    // A soma das folhas da árvore é a soma das folhas das subárvores
    return nf(a->esq) + nf(a->dir);
}
```

---

### Explicação da Lógica Recursiva

A lógica segue a estrutura de caminhamento apresentada no material, mas com uma condição de parada específica para as folhas:

* **`if (a == NULL)`**: Garante que, ao atingir um ramo vazio (filho de um nó que só tem um dos lados preenchido, por exemplo), a função retorne 0 para não interferir na soma.
* **`if (a->esq == NULL && a->dir == NULL)`**: Esta é a "identidade" da folha. Se encontrarmos esse padrão, retornamos **1**, indicando que achamos uma unidade folha.
* **`return nf(a->esq) + nf(a->dir)`**: Se o nó atual for um nó interno (tem pelo menos um filho), ele não se conta. Ele apenas atua como uma ponte, retornando o total de folhas que existem "abaixo" dele, tanto no lado esquerdo quanto no direito.

### Exemplo Prático
Usando a árvore do exemplo do material: `(1, 2, 3)` onde `3` tem filhos `4` e `5`.
* O nó **1** chama a esquerda (**2**) e direita (**3**).
* O nó **2** percebe que é folha e retorna **1**.
* O nó **3** não é folha (tem 4 e 5), então ele chama os filhos e soma os resultados (**1 + 1 = 2**).
* O resultado final na raiz será **1 (do nó 2) + 2 (do nó 3) = 3 folhas**.