## Struct

Imagine o `struct` como um **template** ou um **formulário personalizado**. Por padrão, o C só conhece tipos básicos (inteiros, caracteres, decimais). O `struct` permite que você crie seu próprio tipo de dado complexo.

Aqui está o que acontece nos "bastidores" do compilador:

---

### 1. Alocação de Memória Contígua
Diferente de uma lista ou array onde você tem vários itens do mesmo tipo, o `struct` agrupa tipos que podem ser diferentes em um único **bloco contíguo** de memória.

Quando você define:
```c
struct ab {
    int info;      // 4 bytes
    struct ab *esq; // 8 bytes (em sistemas 64-bits)
    struct ab *dir; // 8 bytes
};
```
O C reserva um espaço total (neste caso, aproximadamente 20 bytes, dependendo do *padding*) onde esses campos ficam colados um no outro.



---

### 2. O papel do `typedef`
No C original, para declarar uma variável, você teria que escrever `struct ab minha_arvore;`. É redundante. 

O `typedef` funciona como um "apelido":
* **Nome original:** `struct ab`
* **Apelido (Alias):** `TAB`

Agora o compilador entende que `TAB` é exatamente a mesma coisa que `struct ab`, deixando seu código mais limpo e legível.

---

### 3. Membros e Acesso (O operador `->`)
Como estamos lidando com árvores, quase sempre usaremos **ponteiros**. Existe uma diferença crucial na sintaxe do C aqui:

* **Se você tem a variável direta (`TAB nó;`):** Você acessa os dados com um ponto: `nó.info = 10;`.
* **Se você tem um ponteiro (`TAB *ponteiro;`):** Você usa a "setinha": `ponteiro->info = 10;`.

A setinha `->` é um atalho charmoso do C para fazer dois passos de uma vez: 
1.  **Desreferenciar** o ponteiro (ir até o endereço de memória).
2.  **Acessar** o campo específico lá dentro.
*(É o mesmo que escrever `(*ponteiro).info`)*.

---

### 4. Por que a estrutura aparece dentro dela mesma?
Isso é o que chamamos de **tipo recursivo**. 

```c
struct ab *esq;
```
O C permite isso porque ele não está tentando colocar uma "caixa dentro de outra caixa" (o que causaria um erro de tamanho infinito). Ele está colocando um **endereço** (ponteiro). O compilador sabe exatamente qual o tamanho de um endereço de memória, então ele aceita essa referência antes mesmo de terminar de definir o que é a `struct ab`.

Ficou mais claro como o C organiza esses dados na memória ou você quer ver como o `malloc` entra nessa história para criar os nós?

---

Agora você entrou na parte da **fábrica de nós**. Esse `TAB*` no início da função é o que chamamos de **tipo de retorno**.

Vamos dissecar o que está acontecendo linha por linha, porque aqui é onde o C mostra seu poder de manipulação de memória:

---

### 1. O que significa o `TAB*` na declaração?
Quando você vê um asterisco grudado no tipo de retorno de uma função, como em `TAB* cria(...)`, isso significa:
> "Esta função não vai me devolver um valor pronto (como um 10 ou 5.0). Ela vai me devolver um **endereço de memória** onde um nó do tipo `TAB` está escondido."

É como se a função te entregasse a chave de um armário, em vez de tentar carregar o armário inteiro para você.

---

### 2. Anatomia da Função `cria`

Esta é uma função clássica de construção de árvores binárias. Vamos aos detalhes:

* **Parâmetros (`int r, TAB *sae, TAB *sad`):** * `r`: O valor que você quer guardar.
    * `sae`: Ponteiro para a **S**ub-**A**rvore **E**squerda (já existente ou `NULL`).
    * `sad`: Ponteiro para a **S**ub-**A**rvore **D**ireita (já existente ou `NULL`).

* **A linha mágica: `malloc(sizeof(TAB))`**
    O `malloc` (Memory Allocation) pede ao sistema operacional: "Ei, reserve um espaço de memória exatamente do tamanho que uma `TAB` precisa". Sem isso, sua árvore morre assim que a função termina. O `malloc` garante que o nó continue vivo na memória (na área chamada *Heap*) até que você decida deletá-lo.



* **Preenchendo o nó (`novo->info = r;` etc.):**
    Aqui você usa a "setinha" para ir até o espaço que o `malloc` reservou e colocar os valores lá dentro. Você conecta os "braços" (`esq` e `dir`) às sub-árvores que recebeu como argumento.

* **`return novo;`**
    A função entrega o endereço desse novo nó para quem a chamou.

---

### 3. Visualizando o Processo
Imagine que você chama a função assim:
`TAB *raiz = cria(10, NULL, NULL);`

1.  **`malloc`** reserva um terreno vazio na memória.
2.  **`novo->info = 10`** constrói uma casa nesse terreno e coloca o número 10 lá dentro.
3.  **`novo->esq = NULL`** e **`novo->dir = NULL`** dizem que não há vizinhos por enquanto.
4.  **`return novo`** te dá o endereço (a "rua e número") dessa casa.



---

### Por que isso é importante?
Se você não usasse `TAB*` (o ponteiro) e tentasse retornar apenas `TAB` (o valor), o C criaria uma cópia local do nó dentro da função e, assim que a função chegasse no `}`, essa cópia seria destruída. O ponteiro é o que permite que a árvore "sobreviva" e cresça durante toda a execução do programa.

Você já tentou montar uma árvore com mais de um nível usando essa função, ou quer ver como encadear uma chamada dentro da outra?