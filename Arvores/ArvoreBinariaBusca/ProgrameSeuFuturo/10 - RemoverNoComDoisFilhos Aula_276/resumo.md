Este vídeo conclui a série sobre remoção de nós em **Árvores Binárias de Busca (BST)**, focando no cenário mais complexo: **remover um nó que possui dois filhos**.

Abaixo, apresento um resumo detalhado da lógica, da estratégia utilizada e da implementação apresentada.

---

## 1. O Problema do Nó com Dois Filhos
Quando um nó tem dois filhos, não podemos simplesmente deletá-lo ou "puxar" um filho para o seu lugar (como fazemos com um único filho), pois isso deixaria o outro filho "órfão" e quebraria a estrutura da árvore. O nó possui três conexões críticas: o ponteiro do pai e os seus dois próprios ponteiros (esquerda e direita).



---

## 2. A Estratégia de Troca (Substituição)
Para simplificar o problema, o autor utiliza uma técnica que transforma a remoção complexa em uma remoção simples (de folha ou de nó com um filho).

### Passos Lógicos:
1.  **Escolha uma Subárvore:** Você pode ir para a **esquerda** ou para a **direita**.
2.  **Encontre o Substituto Ideal:**
    * Se for para a **esquerda**: Procure o elemento **mais à direita** dessa subárvore (o maior valor da subárvore esquerda).
    * Se for para a **direita**: Procure o elemento **mais à esquerda** dessa subárvore (o menor valor da subárvore direita).
3.  **Troque os Valores:** O valor do nó que você quer remover é trocado pelo valor desse substituto encontrado.
4.  **Remova o Substituto:** Agora, o valor indesejado está na extremidade da árvore (onde era o substituto). Como ele era o "mais à direita" ou "mais à esquerda", ele garantidamente **não tem dois filhos** — ele será ou uma folha ou terá apenas um filho.
5.  **Chamada Recursiva:** Chama-se a função `remover` novamente, mas apenas na subárvore onde o valor foi colocado, para eliminá-lo definitivamente.



---

## 3. Implementação no Código (C)
O trecho principal inserido no `if` de dois filhos segue esta estrutura:

```c
if (raiz->esquerda != NULL && raiz->direita != NULL) {
    struct Nodo *aux = raiz->esquerda; // Escolheu a subárvore esquerda
    
    // Caminha até o nó mais à direita da subárvore esquerda
    while (aux->direita != NULL) {
        aux = aux->direita;
    }
    
    // Troca os valores (conteúdo) entre o nó atual e o substituto
    raiz->valor = aux->valor;
    aux->valor = chave; // Coloca o valor que queremos remover no nó folha
    
    // Chama a remoção recursivamente na subárvore esquerda
    raiz->esquerda = remover(raiz->esquerda, chave);
    
    return raiz;
}
```

---

## 4. Demonstração e Testes
O autor demonstra a funcionalidade removendo a **raiz** da árvore (583):
* O algoritmo identifica que o 583 tem dois filhos.
* Ele busca na subárvore esquerda o valor mais à direita (389).
* Troca o 583 com o 389.
* Agora o 583 está na posição onde ficava o 389. Como o 389 tinha apenas um filho (ou era folha), o 583 é removido usando as funções de casos simples já implementadas.
* A árvore é reorganizada e mantém a coerência: **todos à esquerda da nova raiz são menores e todos à direita são maiores.**

---

## 5. Conclusão
A estratégia de **troca de conteúdo seguida de recursão** é apresentada como a forma mais didática de resolver a remoção de dois filhos, pois reaproveita os códigos de remoção de folha e de um filho, reduzindo o grau de complexidade do problema original.