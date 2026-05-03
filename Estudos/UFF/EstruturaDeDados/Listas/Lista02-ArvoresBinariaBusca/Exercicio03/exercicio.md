Para resolver a questão **(Q3)**, utilizaremos como base a função `retira_ABB` fornecida no seu material (Slide 15). A grande diferença é que, em vez de remover um valor específico passado por parâmetro, a função deve percorrer toda a árvore e disparar a lógica de remoção sempre que encontrar um número cujo resto da divisão por 2 seja diferente de zero (`info % 2 != 0`).

Aqui está a implementação da função:

### Solução em C

```c
TABB* retira_impares(TABB* a) {
    if (!a) return NULL;

    // 1. Primeiro, processamos as subárvores (Recursão)
    // Precisamos garantir que os filhos também sejam limpos
    a->esq = retira_impares(a->esq);
    a->dir = retira_impares(a->dir);

    // 2. Verificamos se o nó atual é ímpar
    if (a->info % 2 != 0) {
        // Se for ímpar, aplicamos a lógica de retirada de ABB do seu material:
        
        // CASO 1 e 2: Nó folha ou com apenas um filho
        if (!a->esq || !a->dir) {
            TABB *temp = a;
            if (!a->esq) a = a->dir;
            else a = a->esq;
            free(temp);
        } 
        // CASO 3: Nó com dois filhos
        else {
            // Procuramos o maior elemento da subárvore esquerda (predecessor)
            TABB *filho = a->esq;
            while (filho->dir) filho = filho->dir;
            
            // Troca as informações
            int info_temp = a->info;
            a->info = filho->info;
            filho->info = info_temp;
            
            // Agora que o valor ímpar "desceu", chamamos a remoção na subárvore
            a->esq = retira_impares(a->esq);
        }
    }

    return a;
}
```

---

### Explicação Detalhada (Baseada no Material)

De acordo com o material da Professora Vanessa Braganholo, remover um nó de uma ABB é complexo porque não podemos "quebrar" a árvore. A função acima segue os três casos descritos no Slide 13:

1.  **A Varredura**: A função começa chamando a si mesma para `a->esq` e `a->dir`. Isso garante que estamos analisando todos os nós da árvore original.
2.  **Identificação**: O teste `a->info % 2 != 0` identifica se o número é ímpar.
3.  **Tratamento de Filhos (Casos 1 e 2)**: Se o nó ímpar for uma folha ou tiver apenas um caminho (esquerda ou direita), nós simplesmente "puxamos" o filho para o lugar do pai e liberamos a memória do nó ímpar com `free`.
4.  **O Desafio dos Dois Filhos (Caso 3)**: Se o nó ímpar tiver dois filhos, não podemos simplesmente deletá-lo, ou os filhos ficariam órfãos. 
    * Procuramos o **maior elemento da esquerda** (o predecessor).
    * Trocamos o valor ímpar com esse valor (que é garantidamente par, se a recursão estiver subindo, ou será tratado na próxima chamada).
    * Chamamos a função novamente para remover o valor ímpar de sua nova posição.

### Visualização do Processo


Ao final da execução, a função retorna a nova raiz da árvore, que agora contém apenas valores pares, mantendo todas as propriedades de uma Árvore Binária de Busca (todos à esquerda menores que a raiz, todos à direita maiores).

Este código é uma solução completa para transformar uma árvore genérica em uma **Árvore Binária de Busca (ABB)** e, em seguida, realizar uma operação complexa: a remoção seletiva de todos os nós ímpares, mantendo a árvore balanceada e ordenada.

Aqui está a explicação detalhada dividida por módulos:

---

## 1. O Motor de Reorganização
Nas funções `reorganiza_para_ABB` e `percorre_e_insere`, o código resolve o problema de uma árvore inicial "bagunçada".
* **Estratégia:** Ele não tenta mover os nós existentes. Em vez disso, ele percorre a árvore original e, para cada valor encontrado, chama a função `insere_ABB`.
* **Resultado:** Como a função `insere_ABB` sempre coloca valores menores à esquerda e maiores à direita, a nova árvore resultante (`raiz2`) é uma ABB perfeita, independentemente de como a original era.

---

## 2. A Função `retira_impares` (O Coração do Desafio)
Esta função é complexa porque a remoção em uma ABB não pode deixar "buracos" ou desconectar galhos. Ela utiliza a lógica de **pós-ordem** (processa os filhos antes da raiz) para garantir que a árvore seja limpa de baixo para cima.

### A. A Fase de Descida (Recursão)
```c
a->esq = retira_impares(a->esq);
a->dir = retira_impares(a->dir);
```
Antes de decidir se o nó atual deve ser removido, a função vai até as folhas. Isso é importante porque, se um filho for removido, o ponteiro do pai precisa ser atualizado imediatamente com o que a função retornar.

### B. Identificação e Remoção
Quando o código encontra um nó ímpar (`a->info % 2 != 0`), ele aplica os três casos clássicos de remoção de nós em ABB:

#### **Caso 1 e 2: Zero ou Um Filho**
Se o nó ímpar não tem filho à esquerda ou não tem filho à direita, a solução é simples:
1.  Salvamos o endereço do nó atual em um ponteiro temporário (`temp`).
2.  Fazemos o pai apontar diretamente para o "único neto" (ou para `NULL`, se for folha).
3.  Liberamos a memória do nó ímpar com `free(temp)`.



#### **Caso 3: Dois Filhos (O mais complexo)**
Se o nó ímpar tem dois filhos, não podemos simplesmente deletá-lo, pois perderíamos o acesso às suas subárvores.
1.  **Localizar o Substituto:** O código procura o **Predecessor** (o maior valor da subárvore esquerda). Isso é feito indo uma vez para a esquerda e depois tudo para a direita (`while (filho->dir)`).
2.  **Troca de Valores:** O valor ímpar do nó atual é trocado pelo valor par do predecessor.
3.  **Remoção do "Novo" Ímpar:** Agora que o valor ímpar foi "empurrado" para baixo na árvore (onde ele terá, no máximo, um filho), chamamos a remoção novamente na subárvore esquerda para deletá-lo definitivamente.



---

## 3. Fluxo de Execução no `main`

1.  **Criação:** Uma árvore é montada manualmente com valores como `7`, `5`, `-3` e `1` (todos ímpares).
2.  **Conversão:** `reorganiza_para_ABB` cria uma nova estrutura onde o `-3` estará no extremo esquerdo e o `40` no extremo direito.
3.  **Filtragem:** `retira_impares` percorre essa nova ABB. 
    * O `-3` será removido.
    * O `1` será removido.
    * O `5` e o `7` serão removidos.
4.  **Resultado:** Ao imprimir `arvore_par`, você verá apenas os valores `0, 2, 6, 8, 40`.

---

## Resumo das Funções de Impressão
* **`ImpPre`**: Raiz -> Esq -> Dir (mostra como a árvore está estruturada no topo).
* **`ImpSim`**: Esq -> Raiz -> Dir (em uma ABB, mostra os números em ordem crescente).
* **`ImpPos`**: Esq -> Dir -> Raiz (mostra a ordem em que os nós são liberados da memória).

### Ponto de Atenção
O uso de `free(temp)` é fundamental. Sem ele, o programa teria um "vazamento de memória" (*memory leak*), ocupando espaço no computador com dados que já pedimos para excluir.

O que acontece se a árvore inteira for composta por números ímpares? A função retornará `NULL` e a memória será totalmente liberada.