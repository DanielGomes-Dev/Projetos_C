Esta aula foca em um dos tópicos mais desafiadores na manipulação de **Árvores Binárias de Busca (BST)**: a **remoção de nós**. O professor divide o problema em três cenários lógicos, mas dedica esta aula especificamente ao caso mais simples: a remoção de um **nó folha**.

Aqui está o resumo detalhado de tudo o que foi abordado:

---

## 1. Os Três Cenários de Remoção
Antes de codificar, foi explicado que a dificuldade da remoção depende de quantos filhos o nó possui:
* **Caso 1: O nó é uma folha** (0 filhos). É o caso mais simples.
* **Caso 2: O nó possui um filho.** Exige que o avô "adote" o neto.
* **Caso 3: O nó possui dois filhos.** É o mais complexo, exigindo encontrar um substituto (sucessor ou antecessor).



---

## 2. A Lógica para Remover uma Folha
Para remover um nó que não tem filhos (folha), a estratégia consiste em:
1.  **Localizar o nó** na árvore (usando busca binária).
2.  **Liberar a memória** ocupada por esse nó (`free`).
3.  **Informar ao nó pai** que o ponteiro que apontava para aquele filho agora deve ser `NULL`.

> **Nota importante:** O uso da **recursão** é fundamental aqui. Quando a função de remoção retorna `NULL`, o nó pai recebe esse valor e atualiza seu ponteiro (`esquerda` ou `direita`), "desconectando" o nó removido da estrutura.

---

## 3. Implementação do Código
O professor detalhou a estrutura da função `remover`, que segue estes passos:

### A. Verificação de Árvore Vazia
Se a raiz for `NULL`, o valor não existe na árvore. A função avisa o usuário e retorna `NULL`.

### B. Busca pelo Nó
Se o valor atual não é o que buscamos, a função decide para qual lado ir:
* Se o valor buscado é **menor** que o atual: `raiz->esquerda = remover(raiz->esquerda, valor)`.
* Se o valor buscado é **maior** que o atual: `raiz->direita = remover(raiz->direita, valor)`.

### C. Execução da Remoção (O Nó foi encontrado)
Quando `raiz->valor == chave`, verifica-se se ele é uma folha:
```c
if(raiz->esquerda == NULL && raiz->direita == NULL) {
    free(raiz);
    return NULL; // Este NULL atualizará o ponteiro do pai
}
```

---

## 4. Demonstração Prática e Testes
No ambiente *Code::Blocks*, foi demonstrado o funcionamento real:
* **Remoção Seletiva:** Removendo folhas específicas (ex: 278, 893) e mostrando como o pai passa a apontar para nada.
* **Esvaziamento da Árvore:** O professor mostrou que, ao remover sucessivamente as folhas, é possível apagar a árvore inteira, incluindo a raiz principal, até que ela fique totalmente vazia.
* **Tratamento de Erros:** Ao tentar remover um valor que não existe, o sistema retorna corretamente a mensagem de "valor não encontrado".

---

## Resumo Visual da Estrutura de Remoção
| Passo | Ação | Resultado |
| :--- | :--- | :--- |
| **1** | Busca Recursiva | Navega até encontrar o nó com o valor igual à chave. |
| **2** | Verificação de Filhos | Checa se `esquerda` e `direita` são nulos. |
| **3** | Desalocação | Libera a memória com `free()`. |
| **4** | Atualização | Retorna `NULL` para o nível anterior da recursão (o pai). |

Esta base é essencial para entender as próximas aulas, onde serão tratados os casos de nós com um ou dois filhos, que reaproveitam essa lógica de busca e atualização de ponteiros.

Você ficou com alguma dúvida sobre como o ponteiro do "pai" é atualizado automaticamente pela recursão?