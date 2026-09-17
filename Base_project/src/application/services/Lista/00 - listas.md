# Tipos de Listas em Estruturas de Dados

As **listas** são uma das estruturas de dados mais importantes da computação. Elas servem para armazenar elementos de forma organizada e permitir operações como **inserção, remoção, busca e percurso**.

Existem vários tipos de listas, cada uma com características próprias dependendo de **como os elementos são armazenados e conectados na memória**.

---

# 1. Lista Sequencial (Array List)

A **lista sequencial** é a forma mais simples de lista.
Os elementos são armazenados **em posições consecutivas da memória**, como um vetor (array).

## Representação

```
[10][20][30][40][50]
```

Cada elemento possui um **índice**:

```
0   1   2   3   4
```

## Exemplo em C

```c
int lista[5] = {10, 20, 30, 40, 50};
```

## Características

* Os elementos ficam em **memória contínua**
* Permite acesso direto por índice
* Inserir ou remover no meio exige mover elementos

## Complexidade

| Operação | Complexidade |
| -------- | ------------ |
| Acesso   | O(1)         |
| Inserção | O(n)         |
| Remoção  | O(n)         |

---

# 2. Lista Encadeada Simples (Singly Linked List)

A **lista encadeada simples** é composta por elementos chamados **nós (nodes)**.

Cada nó contém:

* um valor
* um ponteiro para o próximo nó

## Representação

```
[10] -> [20] -> [30] -> NULL
```

O último nó aponta para **NULL**, indicando o fim da lista.

## Estrutura em C

```c
typedef struct Node {
    int valor;
    struct Node* proximo;
} Node;
```

## Características

* Memória **dinâmica**
* Inserção rápida no início
* Percurso apenas em um sentido

## Complexidade

| Operação          | Complexidade |
| ----------------- | ------------ |
| Inserir no início | O(1)         |
| Buscar            | O(n)         |
| Remover           | O(n)         |

---

# 3. Lista Duplamente Encadeada (Doubly Linked List)

A **lista duplamente encadeada** possui dois ponteiros em cada nó:

* um para o próximo elemento
* um para o elemento anterior

## Representação

```
NULL <- [10] <-> [20] <-> [30] -> NULL
```

## Estrutura em C

```c
typedef struct Node {
    int valor;
    struct Node* proximo;
    struct Node* anterior;
} Node;
```

## Características

* Permite percorrer a lista **para frente e para trás**
* Facilita operações de remoção
* Consome mais memória

---

# 4. Lista Circular (Circular Linked List)

Na **lista circular**, o último elemento aponta novamente para o primeiro.

## Representação

```
[10] -> [20] -> [30]
  ↑              |
  └──────────────┘
```

Não existe `NULL`.

## Características

* A lista nunca termina
* Percurso pode continuar indefinidamente
* Muito usada em sistemas que precisam de ciclos

## Aplicações

* escalonamento de processos
* buffers circulares
* jogos e simulações

---

# 5. Lista Duplamente Circular

Combina duas ideias:

* lista duplamente encadeada
* lista circular

## Representação

```
[10] <-> [20] <-> [30]
 ↑                ↓
 └────────────────┘
```

Cada nó possui:

* ponteiro para o próximo
* ponteiro para o anterior

E a lista forma um **ciclo completo**.

## Aplicações

Muito usada em:

* kernels de sistemas operacionais
* estruturas internas de bibliotecas
* gerenciamento de tarefas

---

# 6. Lista com Nó Cabeça (Header List)

Nesse tipo de lista existe um **nó especial no início**, chamado **nó cabeça**.

Ele não guarda dados reais, apenas ajuda na organização da lista.

## Representação

```
[HEAD] -> [10] -> [20] -> [30]
```

## Vantagens

* simplifica inserções
* reduz casos especiais na implementação

---

# 7. Lista Ordenada

Uma **lista ordenada** mantém os elementos sempre em ordem.

Exemplo:

```
[5] -> [10] -> [20] -> [30]
```

Se inserirmos o valor **15**, ele será colocado automaticamente na posição correta:

```
[5] -> [10] -> [15] -> [20] -> [30]
```

## Aplicações

* algoritmos de busca
* estruturas de dados avançadas
* bancos de dados

---

# 8. Lista Genérica

Uma **lista genérica** pode armazenar **qualquer tipo de dado**, não apenas inteiros.

Em C isso normalmente é feito usando **ponteiros genéricos**.

## Exemplo

```c
void* dado;
```

Assim é possível armazenar:

* inteiros
* strings
* estruturas
* qualquer tipo de dado

---

# 9. Skip List

A **Skip List** é uma estrutura avançada usada em sistemas reais.

Ela utiliza **vários níveis de listas** para acelerar buscas.

## Representação simplificada

```
Nivel 2:  10 ---------> 30
Nivel 1:  10 -> 20 -> 30 -> 40
```

Isso permite que as buscas sejam muito mais rápidas.

## Complexidade média

```
O(log n)
```

## Aplicações

* bancos de dados
* sistemas distribuídos
* Redis

---

# Comparação entre os Tipos de Lista

| Tipo             | Memória  | Acesso       | Inserção     |
| ---------------- | -------- | ------------ | ------------ |
| Lista Sequencial | Contínua | Muito rápido | Lento        |
| Lista Simples    | Dinâmica | Lento        | Rápido       |
| Lista Dupla      | Dinâmica | Médio        | Rápido       |
| Lista Circular   | Dinâmica | Médio        | Rápido       |
| Skip List        | Dinâmica | Muito rápido | Muito rápido |

---

# Conclusão

As listas são estruturas fundamentais que servem como base para muitas outras estruturas de dados.

Elas são utilizadas na implementação de:

* filas
* pilhas
* grafos
* árvores
* tabelas hash
* sistemas operacionais

Cada tipo de lista existe para resolver **diferentes problemas de desempenho e organização de dados**.

Compreender essas variações é essencial para dominar **estruturas de dados e algoritmos**.
