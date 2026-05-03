Nesta aula, o professor ensina como realizar a busca de um elemento em uma **Árvore Binária de Busca (BST)** de forma **iterativa**, ou seja, utilizando um laço de repetição (`while`) em vez de recursão. Essa abordagem é mais eficiente em termos de memória, pois não consome espaço na pilha de execução.

Aqui está o resumo detalhado dos tópicos abordados:

---

### 1. Motivação: Iteração vs. Recursão
* **Custo da Recursão:** O professor relembra que cada chamada recursiva cria um novo "estado" na memória (pilha), o que pode ser custoso em árvores muito grandes.
* **Vantagem da Iteração:** Ao usar um loop, o programa utiliza apenas uma variável de controle que vai se deslocando pela árvore, economizando recursos do computador.

---

### 2. A Lógica da Busca Iterativa
A função `buscar_versao_2` funciona movendo o ponteiro pela árvore até encontrar o valor ou chegar a um nó vazio (`NULL`).

* **O Laço `while`:** A repetição continua enquanto a `raiz` (o ponteiro atual) não for nula.
* **Navegação Inteligente:**
    * Se o número procurado for **menor** que o valor do nó atual: O ponteiro local `raiz` passa a apontar para o filho da esquerda.
    * Se o número for **maior**: O ponteiro local `raiz` passa a apontar para o filho da direita.
    * **Caso de Sucesso:** Se não for menor nem maior, significa que o valor é **igual**. A função então retorna o ponteiro para esse nó imediatamente usando `return raiz;`.



---

### 3. Manipulação de Variáveis Locais
Um ponto técnico importante explicado é que a alteração da variável `raiz` dentro da função **não estraga a árvore original**.
* **Variável Local:** A `raiz` recebida como parâmetro é apenas uma cópia do endereço. Ao fazer `raiz = raiz->esquerda`, você está apenas mudando para onde essa "cópia" aponta localmente para percorrer a estrutura.
* **Segurança:** Isso é diferente de usar ponteiro duplo (`**raiz`), onde você alteraria a árvore permanentemente. Aqui, apenas "caminhamos" pela árvore.

---

### 4. Casos de Parada e Retorno
* **Encontrado:** O retorno ocorre dentro do `while` assim que a igualdade é detectada.
* **Não Encontrado / Árvore Vazia:** Se o `while` chegar ao fim (quando `raiz` se torna `NULL`), significa que percorremos o caminho e não achamos nada. Nesse caso, a função retorna `NULL` fora do laço.



---

### 5. Comparação da Implementação (Código)

| Versão 1 (Recursiva) | Versão 2 (Iterativa) |
| :--- | :--- |
| Usa `if` e chamadas de si mesma. | Usa `while(raiz != NULL)`. |
| Gasta memória da pilha (`stack`). | Gasta memória constante (mais eficiente). |
| Precisa propagar o `return` em todas as chamadas. | Retorna diretamente de dentro do loop ou ao final. |

---

### Exemplo de Código da Aula:

```c
NoArv* buscar_versao_2(NoArv *raiz, int num) {
    while (raiz != NULL) {
        if (num < raiz->valor)
            raiz = raiz->esquerda; // Move para a esquerda
        else if (num > raiz->valor)
            raiz = raiz->direita;  // Move para a direita
        else
            return raiz;           // Encontrou!
    }
    return NULL; // Não encontrou ou árvore vazia
}
```

Ao final, o professor demonstra na prática que a função funciona corretamente tanto para encontrar a raiz, elementos nas extremidades (mínimos e máximos) e identificar corretamente quando um valor não existe na árvore.

Ficou clara a diferença de como o ponteiro "viaja" pela árvore no `while` em vez de criar novas funções?