Para resolver a questão **(Q1)** de encontrar o maior elemento em uma Árvore Binária de Busca (ABB), devemos utilizar a propriedade fundamental dessa estrutura: **os valores maiores que a raiz estão sempre à sua direita.**

Portanto, para encontrar o maior valor, não precisamos percorrer a árvore inteira. Basta "caminhar" para a direita sucessivamente até encontrar o último nó (aquele cujo ponteiro `dir` seja `NULL`).

Aqui estão as implementações sugeridas, tanto de forma iterativa quanto recursiva, utilizando a estrutura `TABB` fornecida:

---

### Solução Iterativa (Mais Eficiente)
Esta abordagem é geralmente preferida para encontrar o maior/menor elemento, pois economiza memória ao não empilhar chamadas de função.

```c
TABB* maior(TABB *a) {
    // Se a árvore estiver vazia, retorna NULL
    if (!a) return NULL;

    // Enquanto houver um filho à direita, o maior estará lá
    while (a->dir != NULL) {
        a = a->dir;
    }

    // Retorna o nó que contém o maior valor
    return a;
}
```

---

### Solução Recursiva
Segue a mesma lógica, mas utiliza a recursão para chegar ao nó mais à direita.

```c
TABB* maior(TABB *a) {
    // Caso base: árvore vazia
    if (!a) return NULL;

    // Se não houver mais nada à direita, este é o maior
    if (!a->dir) return a;

    // Caso contrário, continua procurando na subárvore direita
    return maior(a->dir);
}
```

---

### Explicação do Conceito

Em uma ABB, a organização dos dados segue uma regra rígida:
* **Subárvore Esquerda:** Apenas valores menores que o nó pai.
* **Subárvore Direita:** Apenas valores maiores que o nó pai.



Como visto no material de apoio (Slide 14, Caso 3), para encontrar o predecessor ou o sucessor, utilizamos essa exata lógica de navegar pelos extremos. Para o **maior elemento**, o caminho é sempre o extremo direito.

**Complexidade:**
* **Melhor Caso:** $O(1)$ (se a raiz não tiver filho à direita).
* **Pior Caso:** $O(h)$, onde $h$ é a altura da árvore. Em uma árvore equilibrada, isso equivale a $O(\log n)$.

---

Para reorganizar qualquer árvore binária comum para uma **Árvore Binária de Busca (ABB)**, a estratégia mais comum é percorrer a árvore original, extrair todos os seus valores e reinseri-los em uma nova árvore utilizando a lógica de inserção de ABB (onde valores menores vão para a esquerda e maiores para a direita).

Com base no código que você forneceu e no material de apoio, aqui está a implementação da função `reorganiza_para_ABB`:

### Implementação em C

```c
// Função auxiliar baseada no seu material para inserir respeitando a ordem de busca
TABB *insere_ABB(TABB *a, int info) {
    if (!a) return Cria(info, NULL, NULL);
    if (info < a->info)
        a->esq = insere_ABB(a->esq, info);
    else if (info > a->info)
        a->dir = insere_ABB(a->dir, info);
    return a;
}

// Função que percorre a árvore original e insere os elementos na nova árvore
void percorre_e_insere(TABB *original, TABB **nova_raiz) {
    if (original) {
        // Insere o valor do nó atual na nova ABB
        *nova_raiz = insere_ABB(*nova_raiz, original->info);
        
        // Continua o percurso para os filhos
        percorre_e_insere(original->esq, nova_raiz);
        percorre_e_insere(original->dir, nova_raiz);
    }
}

// Função principal de reorganização
TABB* reorganiza_para_ABB(TABB *a) {
    TABB *nova_raiz = NULL;
    percorre_e_insere(a, &nova_raiz);
    return nova_raiz;
}
```

---

### Como funciona a lógica?

1.  **Extração**: A função `percorre_e_insere` visita cada nó da sua árvore "desorganizada" (no seu código, a árvore `raiz` tem o valor 40 na esquerda do 3, o que quebra a regra de busca).
2.  **Reinserção Ordenada**: Para cada valor encontrado, chamamos a função `insere_ABB`. 
    * Ela verifica: "O novo valor é menor que a raiz atual?" Se sim, vai para a esquerda.
    * "É maior?" Se sim, vai para a direita.
3.  **Resultado**: O retorno é um ponteiro para uma nova árvore que contém exatamente os mesmos dados, mas estruturados de forma que a busca seja eficiente ($O(\log n)$ em árvores balanceadas).

### Exemplo Visual do Material


Se você aplicar essa função na sua árvore do `main`, o valor `40` que estava "perdido" em um nível baixo será movido para o extremo direito da nova árvore, tornando-se o novo maior elemento acessível corretamente pela função `Maior`.

**Nota importante**: No seu código original, dentro da função `Maior`, há um erro de digitação: você chamou `return maior(a->dir);` (com 'm' minúsculo), mas a função se chama `Maior` (com 'M' maiúsculo). Certifique-se de corrigir para que o compilador não aponte erro.

---

Esta é uma explicação detalhada do código, dividida por "responsabilidades". O objetivo principal aqui é entender como transformamos uma árvore binária qualquer (onde os números podem estar em qualquer lugar) em uma **Árvore Binária de Busca (ABB)** legítima.

---

## 1. A Estrutura de Dados (`TABB`)
A base de tudo é a `struct ab`. Ela define um nó que guarda um valor (`info`) e dois braços: `esq` (valores menores na ABB) e `dir` (valores maiores na ABB). A função `Cria` é apenas uma fábrica de nós, alocando memória e conectando os filhos.

## 2. O Coração da Reorganização
A reorganização acontece em três etapas lógicas:

### A. A Inserção Ordenada (`insere_ABB`)
Esta função é baseada no Slide 9 do seu material. Ela não apenas "coloca" o nó na árvore; ela **procura o lugar certo**.
* Se o valor é menor que a raiz, ela obriga o valor a ir para a esquerda.
* Se é maior, vai para a direita.
* Isso garante que a propriedade fundamental da ABB seja mantida.

### B. O Percurso e Extração (`percorre_e_insere`)
Para organizar uma árvore bagunçada, precisamos visitar cada nó dela. 
* O código usa um percurso (tipo pré-ordem) para ler o valor do nó atual da árvore original.
* Assim que lê o valor, ele chama `insere_ABB` para colocar esse valor em uma **nova** árvore, no lugar correto.
* **Importante:** Note o uso de `TABB **nova_raiz`. Usamos ponteiro para ponteiro para que a função consiga alterar o endereço da raiz da nova árvore conforme ela cresce.

### C. A Função Principal (`reorganiza_para_ABB`)
Ela serve como o ponto de entrada. Ela inicializa uma nova árvore como `NULL` (vazia) e inicia o processo de "leitura e colagem" da árvore antiga para a nova.

---

## 3. A Busca pelo Maior Elemento (`Maior`)
Esta função resolve a questão **(Q1)** de forma muito eficiente. 
Em uma ABB, você não precisa olhar para o lado esquerdo para achar o maior valor. O maior valor estará sempre no extremo direito. 

1. **`if (!a->dir) return a;`**: Se não tem ninguém à minha direita, eu sou o maior.
2. **`return Maior(a->dir);`**: Se tem alguém à direita, ignoro a mim mesmo e a todo o meu lado esquerdo e vou para a direita.



---

## 4. Análise do `main` (O Teste)
No seu `main`, você criou uma árvore manualmente que **não era uma ABB** (por exemplo, o nó com `40` foi colocado como filho à esquerda do `3`, o que viola a regra, já que $40 > 3$).

```text
Árvore Original (Bagunçada):
      0
     /
    1
   / \
  2   3
     / \
   40   5  <-- O 40 está "escondido" na esquerda!
```

Ao rodar `reorganiza_para_ABB(raiz)`, o código:
1. Pega o 0, coloca na nova raiz.
2. Pega o 1, coloca à direita do 0.
3. Pega o 2, coloca à direita do 1.
4. ...
5. Pega o **40** e, seguindo a lógica de `insere_ABB`, ele vai parar no **extremo direito** da nova árvore.

**Resultado final:** Quando você chama `Maior(raiz2)`, ele percorre todo o caminho da direita e encontra o `40` corretamente, algo que seria impossível na árvore original usando apenas a lógica de busca de ABB.

---

### Resumo das Funções de Impressão
* **`ImpPre`**: Imprime a Raiz, depois Esquerda, depois Direita. (Útil para ver a estrutura).
* **`ImpSim`**: Imprime Esquerda, Raiz, Direita. **Dica:** Em uma ABB, a impressão Simétrica sempre resulta nos números em ordem crescente!

Você gostaria de ver como implementar a remoção de um nó específico nessa nova árvore organizada?