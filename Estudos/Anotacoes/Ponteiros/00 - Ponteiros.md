Para entender ponteiros com precisão, você precisa parar de olhar para a **variável** e começar a olhar para a **memória RAM**.

Aqui está a explicação dividida em três níveis de profundidade:

---

## 1. O que é, fisicamente, um Ponteiro?
Imagine a memória RAM do seu computador como uma rua infinita cheia de casas. 
* Cada casa tem um **número** (o endereço, ex: `1008`).
* Dentro da casa, mora um **valor** (o conteúdo, ex: o número `42`).

Uma variável comum (como `int x = 42;`) é o nome que damos ao **conteúdo** da casa. 
Um **ponteiro**, por outro lado, é uma variável especial que armazena o **número da casa** (o endereço).



---

## 2. A Sintaxe: Os dois símbolos vitais (`*` e `&`)
Em C, você precisa dominar estes dois operadores para manipular ponteiros:

* **`&` (Endereço de):** "Me diga em qual casa esse valor mora".
* **`*` (Conteúdo de / Desreferenciação):** "Vá até a casa de número X e me diga o que tem lá dentro".

### Exemplo Prático:
```c
int x = 10;      // Uma variável normal.
int *p;          // Declarando um ponteiro (o '*' aqui diz: 'p vai guardar endereços').

p = &x;          // p agora guarda o ENDEREÇO de x (ex: 0x7ffd).

printf("%d", *p); // O '*' aqui diz: "Vá ao endereço guardado em p e mostre o valor".
                  // Resultado: 10.
```

---

## 3. Por que usamos Ponteiros em Árvores?
Você notou que na sua função `cria`, usamos `TAB *novo`. Sem ponteiros, as árvores seriam impossíveis. Aqui está o porquê:

1.  **Tamanho Dinâmico:** Se você declarar uma estrutura sem ponteiro, o computador precisa saber o tamanho exato dela na hora que você escreve o código. Mas uma árvore pode crescer de 1 para 1 milhão de nós enquanto o programa roda. O ponteiro permite que você aloque memória "sob demanda" com o `malloc`.
2.  **Conectividade:** Um nó de árvore não "contém" outro nó dentro dele. Ele contém o **endereço** de onde o próximo nó está na memória. É como um mapa do tesouro: o nó atual diz onde você deve cavar para achar o filho da esquerda.



---

## Resumo de "Ouro"
* `int x` : A caixa com o presente.
* `int *p` : Um papel com o endereço de onde a caixa está.
* `malloc` : Cria uma caixa nova no meio da rua e te entrega o endereço dela.

**Ficou mais claro agora o porquê de usarmos `TAB *` (ponteiro) em vez de apenas `TAB` (variável comum) no seu código de árvore?**