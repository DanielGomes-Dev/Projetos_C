Esta aula foca na otimização da inserção em Árvores Binárias de Busca (BST) através da criação de um **procedimento (`void`)** que utiliza **ponteiros para ponteiros**.

Aqui está o resumo detalhado, tópico por tópico:

---

## 1. Motivação: Por que uma Versão 2?
A Versão 1 (recursiva com retorno) funciona bem, mas possui um custo computacional:
* **Custo de Memória e Tempo:** Cada `return` e cada atribuição na recursão consome recursos e acessos à memória.
* **Objetivo:** Criar um procedimento mais eficiente que altere a árvore diretamente na memória original, sem a necessidade de retornar ponteiros ou fazer atribuições na função `main`.

## 2. A Estratégia: Ponteiro para Ponteiro (`**raiz`)
Para que um procedimento (`void`) consiga modificar o ponteiro `raiz` da função `main`, ele não pode receber apenas o valor do endereço (ponteiro simples).
* **Conceito:** Ao passar o endereço da variável raiz (`&raiz`), a função recebe um **ponteiro para ponteiro**.
* **Vantagem:** Isso permite que o código "abra a caixa" onde o ponteiro está guardado e troque o seu conteúdo (por exemplo, de `NULL` para o endereço de um novo nó) de forma permanente.

## 3. Implementação do Caso Base (Árvore Vazia)
O teste para verificar se a árvore está vazia muda ligeiramente:
* **Verificação:** Usa-se `if(*raiz == NULL)`. Aqui, `*raiz` acessa o conteúdo do endereço recebido.
* **Alocação Direta:** A memória é alocada diretamente no conteúdo da raiz: `*raiz = malloc(sizeof(NoArv))`.
* **Inicialização:** Os campos são acessados usando parênteses para garantir a precedência: `(*raiz)->valor = num`, `(*raiz)->esquerda = NULL`, etc.



## 4. Lógica de Recursão e Navegação
Quando a raiz não é nula, a função precisa decidir para qual lado navegar, mantendo a regra da BST (menores à esquerda, maiores à direita):
* **Comparação:** Compara-se o número com o valor do nó atual: `if(num < (*raiz)->valor)`.
* **Chamada Recursiva Complexa:** Este é o ponto mais técnico. Para continuar a recursão enviando o endereço do próximo ponteiro, usa-se a sintaxe:
  `inserir_version2(&((*raiz)->esquerda), num);`
* **Por que o `&` e o `*`?** 1. `(*raiz)` acessa o nó atual.
    2. `->esquerda` acessa o ponteiro do filho.
    3. `&(...)` captura o endereço desse ponteiro específico para que a próxima chamada possa modificá-lo.

## 5. Mudanças na Função `main`
A forma de chamar a função no menu do programa também muda:
* **Sem atribuição:** Não se usa mais `raiz = inserir(...)`.
* **Passagem por referência:** A chamada agora é `inserir_version2(&raiz, num)`.
* **Resultado:** A variável `raiz` da `main` é atualizada "silenciosamente" pela função.

## 6. Testes e Verificação
O instrutor demonstra a inserção de vários elementos (500, 250, 750, 650) para validar:
* **Ordenação:** Através da impressão simétrica, confirma-se que os elementos foram inseridos nos lugares corretos.
* **Integridade:** O uso de ponteiro duplo não corrompe a estrutura da árvore, apenas torna a operação de inserção mais direta e tecnicamente elegante.

---

### Tabela Comparativa: Versão 1 vs. Versão 2

| Característica | Versão 1 (Anterior) | Versão 2 (Esta aula) |
| :--- | :--- | :--- |
| **Tipo de Retorno** | `NoArv*` | `void` |
| **Parâmetro da Raiz** | `NoArv *raiz` (Ponteiro simples) | `NoArv **raiz` (Ponteiro duplo) |
| **Chamada na `main`** | `raiz = inserir(raiz, num);` | `inserir(&raiz, num);` |
| **Desempenho** | Ligeiramente menor (devido aos retornos) | Otimizado (alteração direta na memória) |

Ficou clara a razão de usarmos tantos parênteses e asteriscos nessa versão, ou você gostaria de ver um desenho da "pilha de recursão" com esses ponteiros duplos?