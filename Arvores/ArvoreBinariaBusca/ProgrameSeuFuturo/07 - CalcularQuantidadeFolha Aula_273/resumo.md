Este é um resumo detalhado da vídeo-aula sobre como implementar uma função para contar a **quantidade de folhas** em uma árvore binária utilizando a linguagem C e o conceito de recursão.

---

## 1. Conceito de Nó Folha
O instrutor inicia revisando a definição teórica: um nó é considerado uma **folha** quando ele **não possui nenhum filho**, ou seja, tanto seu ponteiro para a subárvore esquerda quanto para a direita são nulos (`NULL`).

---

## 2. Lógica e Possibilidades (Análise no Paint)
Para construir o algoritmo, são analisados três cenários principais:

*   **Cenário 1: Árvore Vazia:** Se a raiz for nula, a função deve retornar **0**, pois não existem nós, logo, não há folhas.
*   **Cenário 2: O Nó é uma Folha:** Se a raiz não for nula, mas seus filhos à esquerda e à direita forem nulos, o algoritmo identificou uma folha e deve retornar **1**.
*   **Cenário 3: O Nó não é uma Folha:** Se o nó possuir ao menos um filho, ele não é uma folha (retorna **0** para si mesmo). Nesse caso, a função deve realizar chamadas recursivas para somar as folhas encontradas na subárvore esquerda e na subárvore direita.

O instrutor reforça que desenhar a árvore e simular as chamadas no papel ajuda a entender como os valores (0 e 1) "sobem" na pilha de recursão até o resultado final.

---

## 3. Implementação Técnica
A função `quantidade_folhas` recebe o ponteiro para a raiz e retorna um `int`.

### Estrutura do Código:
1.  **Primeiro teste:** `if(raiz == NULL)` $\rightarrow$ `return 0;`
2.  **Segundo teste (É folha?):** `else if(raiz->esquerda == NULL && raiz->right == NULL)` $\rightarrow$ `return 1;`
3.  **Recursão:** `else` $\rightarrow$ `return quantidade_folhas(raiz->esquerda) + quantidade_folhas(raiz->direita);`

---

## 4. Integração e Testes Práticos
O instrutor adiciona a **Opção 6** ao menu do programa e realiza testes em tempo real para validar a lógica:

*   **Árvore Vazia:** O sistema retorna 0 folhas.
*   **Apenas Raiz (500):** O sistema retorna 1 folha (a própria raiz).
*   **Inserção do 750 (Direita):** A árvore agora tem dois nós, mas continua com apenas 1 folha (o 750), pois o 500 passou a ser um nó pai.
*   **Inserção do 250 (Esquerda):** A árvore passa a ter 2 folhas (250 e 750), enquanto o 500 permanece como raiz/pai.
*   **Crescimento da Árvore:** É demonstrado que ao inserir filhos nos nós 250 ou 750, eles deixam de ser folhas, e os novos nós inseridos assumem esse papel, alterando dinamicamente o contador.

A aula encerra enfatizando a importância da recursão para navegar em estruturas de dados dinâmicas e convidando o aluno a praticar com desenhos e simulações manuais.