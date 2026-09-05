Esta aula foca em como realizar a operação de **Busca em uma Árvore Binária de Busca (BST)**, utilizando uma abordagem **recursiva**. O professor explica a lógica por trás do algoritmo, a importância do retorno na recursão e como implementar isso na linguagem C.

Aqui está o resumo detalhado dos pontos abordados:

---

### 1. Objetivo e Estrutura do Retorno
* **Por que retornar um ponteiro?** A função de busca é projetada para retornar um ponteiro para o nó encontrado (`NoArv*`).
* **Vantagem:** Se o elemento for encontrado, temos acesso direto ao nó. Se não for encontrado, a função retorna `NULL`, o que serve como um indicativo claro de que o valor não existe na árvore.

### 2. Lógica da Busca em BST
A busca aproveita a propriedade principal da Árvore Binária de Busca para ser eficiente:
1.  **Caso Base 1 (Não encontrado):** Se a `raiz` atual for `NULL`, a busca terminou sem sucesso (retorna `NULL`).
2.  **Caso Base 2 (Encontrado):** Se o valor procurado for igual ao `raiz->valor`, o nó foi encontrado (retorna a `raiz` atual).
3.  **Recursão para a Esquerda:** Se o valor procurado for **menor** que o valor do nó atual, a busca continua apenas na subárvore esquerda.
4.  **Recursão para a Direita:** Se o valor procurado for **maior**, a busca continua na subárvore direita.



### 3. A Importância da Propagação do Retorno
Um dos pontos mais reforçados na aula é a necessidade de usar a palavra-chave `return` antes das chamadas recursivas:
* **O erro comum:** Chamar a função recursivamente sem retornar seu resultado faz com que o valor encontrado (ou o `NULL`) se perca dentro da pilha de recursão.
* **A solução:** Deve-se fazer `return buscar_versao_1(...)`. Isso garante que o resultado encontrado nas folhas ou subárvores "suba" de volta por todas as chamadas anteriores até chegar à função original (como a `main`).



### 4. Árvores Degeneradas
O professor menciona o conceito de **árvore degenerada**:
* Ocorre quando os elementos são inseridos de forma que a árvore se comporta como uma lista encadeada (ex: inserindo 500, 700, 850, 1000... sempre para a direita).
* Nesses casos, a eficiência da busca cai, pois ela precisará percorrer todos os elementos de forma linear.

### 5. Implementação na Prática (`main`)
No código de teste, os seguintes passos são seguidos:
* Criação de uma variável `busca` para armazenar o resultado.
* Leitura do valor desejado pelo usuário.
* Verificação do resultado:
    * `if(busca)`: Se o ponteiro não for nulo, imprime o valor encontrado.
    * `else`: Informa que o valor não existe na árvore.

---

### Resumo do Código Implementado:

```c
NoArv* buscar_versao_1(NoArv *raiz, int num) {
    if (raiz) {
        if (num == raiz->valor)
            return raiz; // Encontrou!
        else if (num < raiz->valor)
            return buscar_versao_1(raiz->esquerda, num); // Vai para esquerda
        else
            return buscar_versao_1(raiz->direita, num); // Vai para direita
    }
    return NULL; // Chegou ao fim e não encontrou
}
```

A aula termina validando a função com diversos testes (buscando valores existentes e inexistentes) e preparando o terreno para a próxima aula, onde será ensinada a **versão iterativa** (sem recursão), que é mais eficiente por não sobrecarregar a pilha de memória.