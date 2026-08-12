Este vídeo descreve a implementação de um procedimento para **exibir visualmente uma Árvore Binária de Busca (AVL)** no terminal, além de apresentar a estrutura básica da função principal (`main`) para gerenciar a árvore.

O grande desafio abordado é que imprimir os elementos em uma única linha não permite verificar se a árvore está realmente balanceada. Por isso, o professor propõe uma técnica de **impressão horizontal**.

---

## 1. O Procedimento de Impressão (`imprimir`)
A técnica utiliza uma abordagem recursiva que imprime a árvore "deitada" (rotacionada 90 graus para a esquerda).

### Lógica do Código:
* **Parâmetros:** Recebe a `raiz` do nó atual e o `nível` (inteiro que começa em 1).
* **Ordem de Visita:** O algoritmo utiliza uma variação do percurso **In-ordem Inverso**:
    1.  Caminha para a **Direita** primeiro (os maiores valores ficam no topo da tela).
    2.  Imprime o **Nó Atual** com recuo (tabulação).
    3.  Caminha para a **Esquerda** (os menores valores ficam na parte inferior).
* **O uso do `nível`:** A variável `nível` serve para controlar a **tabulação (`\t`)**. Quanto mais profundo o nó na árvore, mais espaços ele terá à esquerda no terminal. Isso cria uma hierarquia visual onde a raiz fica à esquerda e as folhas à direita.



---

## 2. Estrutura da Função `main`
Para testar a árvore AVL, o vídeo apresenta um menu interativo utilizando a estrutura `switch-case`. As funcionalidades principais são:

| Opção | Ação | Descrição |
| :--- | :--- | :--- |
| **0** | Sair | Finaliza a execução do programa. |
| **1** | Inserir | Solicita um valor ao usuário e chama a função de inserção com balanceamento. |
| **2** | Remover | Solicita um valor para excluir da árvore, seguido do rebalanceamento. |
| **3** | Imprimir | Chama o procedimento `imprimir(raiz, 1)`. |

---

## 3. Por que imprimir desta forma?
Imprimir a árvore horizontalmente facilita a identificação visual de:
1.  **A Raiz:** O elemento mais à esquerda no terminal (com apenas uma tabulação).
2.  **O Balanceamento:** É possível ver se as "folhas" estão em níveis de profundidade similares.
3.  **A Estrutura de Busca:** Valores acima da raiz (na tela) pertencem à subárvore direita, e valores abaixo pertencem à subárvore esquerda.

> **Dica do vídeo:** Ao iniciar a impressão da raiz com `nível = 1` em vez de `0`, garante-se que nenhum elemento fique colado na borda do terminal, melhorando a legibilidade.



O próximo passo indicado pelo professor é a execução prática de todo o código desenvolvido nas aulas anteriores (Inserção, Remoção e Balanceamento) para validar o comportamento da AVL.