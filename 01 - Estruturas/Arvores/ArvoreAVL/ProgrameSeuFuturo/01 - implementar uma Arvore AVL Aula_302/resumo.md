Este resumo detalha os conceitos fundamentais sobre **Árvores Balanceadas (especificamente a Árvore AVL)** apresentados na aula, explicando por que elas são necessárias e como funcionam as operações de reequilíbrio.

---

## 1. O Problema: Árvores Degeneradas
Embora as árvores binárias de busca (BST) sejam eficientes na teoria, elas podem enfrentar um problema prático: o **desbalanceamento** ou **degeneração**.

* **O que é:** Ocorre quando os elementos são inseridos de uma forma que a árvore se assemelha a uma **lista encadeada** (todos os nós pendendo para um único lado).
* **Consequência:** As operações de busca, inserção e remoção perdem eficiência. Em vez de serem logarítmicas ($O(\log n)$), tornam-se lineares ($O(n)$), pois pode ser necessário percorrer todos os nós para encontrar um valor.



---

## 2. A Solução: Árvore AVL
A árvore AVL (nomeada em homenagem aos criadores Adelson-Velsky e Landis) é uma árvore binária de busca que se **auto-balanceia**.

* **Eficiência Garantida:** Mantém o custo das operações sempre em $O(\log n)$.
* **Regra de Ouro:** A diferença de altura entre a subárvore esquerda e a direita de qualquer nó não pode ser maior que 1.

### O Fator de Balanceamento (FB)
Para controlar o equilíbrio, calcula-se o FB de cada nó com a fórmula:
$$FB = \text{altura\_esquerda} - \text{altura\_direita}$$

* **Nó Balanceado:** $FB \in \{1, 0, -1\}$
* **Nó Desbalanceado:** $FB = 2$ ou $FB = -2$ (necessita de rotação).

---

## 3. Técnicas de Rebalanceamento (Rotações)
Existem quatro cenários de desbalanceamento, resolvidos por meio de **rotações**, que são manipulações de ponteiros para reorganizar os nós sem ferir a regra da árvore binária (menores à esquerda, maiores à direita).

### A. Rotação Simples à Esquerda
* **Quando ocorre:** Quando a árvore pende excessivamente para a **direita** ($FB = -2$).
* **Ação:** O nó filho à direita sobe para a posição de pai, e o antigo pai torna-se seu filho à esquerda.

### B. Rotação Simples à Direita
* **Quando ocorre:** Quando a árvore pende excessivamente para a **esquerda** ($FB = 2$).
* **Ação:** O nó filho à esquerda sobe para a posição de pai, e o antigo pai torna-se seu filho à direita.



### C. Rotação Dupla Direita-Esquerda
* **Cenário:** O nó está desbalanceado para a direita, mas o seu filho está pendendo para a esquerda (forma um "joelho").
* **Ação:** 1. Uma rotação à direita no filho.
    2. Uma rotação à esquerda no pai (raiz local).

### D. Rotação Dupla Esquerda-Direita
* **Cenário:** O nó está desbalanceado para a esquerda, mas o seu filho está pendendo para a direita.
* **Ação:**
    1. Uma rotação à esquerda no filho.
    2. Uma rotação à direita no pai (raiz local).

---

## Resumo Comparativo

| Característica | Árvore Binária Comum (BST) | Árvore Balanceada (AVL) |
| :--- | :--- | :--- |
| **Complexidade (Melhor Caso)** | $O(\log n)$ | $O(\log n)$ |
| **Complexidade (Pior Caso)** | $O(n)$ (Lista) | $O(\log n)$ |
| **Estrutura** | Pode ser irregular | Sempre equilibrada |
| **Uso de Memória** | Ligeiramente menor | Requer campo para altura/FB |

> **Nota:** Além da AVL, existem outros tipos de árvores balanceadas, como a **Árvore Rubro-Negra (Red-Black)** e a **Árvore 2-3-4**, cada uma com critérios específicos de equilíbrio.