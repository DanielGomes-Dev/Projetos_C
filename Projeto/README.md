# Guia Completo do Projeto de Estruturas de Dados em C

- docker compose run --rm estrutura-de-dados


## Introdução

Neste projeto você começou a construir **estruturas de dados em C** utilizando uma arquitetura organizada semelhante a sistemas backend modernos.

Mesmo sendo C (uma linguagem de baixo nível), você organizou o código de forma profissional separando responsabilidades em camadas.

O objetivo foi implementar uma **Lista Encadeada** com:

* inicialização
* inserção de elementos
* impressão da lista

Tudo isso dentro de uma **arquitetura modular**.

---

# 1. Estrutura de Pastas do Projeto

Seu projeto ficou organizado assim:

```
estrutura-de-dados
│
├── main.c
├── Dockerfile
│
└── src
    ├── application
    │   └── services
    │       └── Lista
    │           ├── Lista.h
    │           ├── lista_init.c
    │           ├── lista_insert.c
    │           └── lista_print.c
    │
    ├── interfaces
    │   └── ListaController
    │       ├── ListaController.c
    │       └── ListaController.h
```

Cada pasta tem uma responsabilidade.

### application/services

Contém a **lógica da estrutura de dados**.

### interfaces

Contém **controllers**, responsáveis por chamar os serviços.

### main.c

É o **ponto de entrada do programa**.

---

# 2. O que é uma Lista Encadeada

Uma lista encadeada é uma estrutura onde cada elemento aponta para o próximo.

Exemplo:

```
[10] -> [20] -> [30] -> NULL
```

Cada elemento contém:

* um valor
* um ponteiro para o próximo elemento

---

# 3. Estrutura da Lista

Arquivo:

```
Lista.h
```

Nele definimos as estruturas.

```c
typedef struct Node {
    int valor;
    struct Node* proximo;
} Node;

typedef struct {
    Node* inicio;
    int tamanho;
} Lista;
```

## Explicação

### Node

Representa **um elemento da lista**

```
Node
 ├ valor
 └ ponteiro para próximo
```

Exemplo:

```
[10 | *] -> aponta para próximo
```

---

### Lista

Representa a **lista inteira**

```
Lista
 ├ inicio
 └ tamanho
```

* `inicio` aponta para o primeiro elemento
* `tamanho` guarda quantos elementos existem

---

# 4. Inicializando a Lista

Arquivo:

```
lista_init.c
```

Código:

```c
void lista_init(Lista* lista) {

    lista->inicio = NULL;
    lista->tamanho = 0;

}
```

## O que acontece

Quando criamos uma lista:

```
Lista lista;
```

Ela pode conter lixo de memória.

Então precisamos inicializar.

Após `lista_init`:

```
lista.inicio = NULL
lista.tamanho = 0
```

Isso significa:

```
lista vazia
```

---

# 5. Inserindo Elementos

Arquivo:

```
lista_insert.c
```

Código simplificado:

```c
Node* novo = malloc(sizeof(Node));
```

Isso cria um novo nó na memória.

Depois:

```
novo->valor = valor
```

Guardamos o valor.

---

### Conectando o nó

```
novo->proximo = lista->inicio
```

Antes:

```
10 -> 20 -> NULL
```

Depois de inserir 30:

```
30 -> 10 -> 20 -> NULL
```

---

### Atualizando início

```
lista->inicio = novo
```

Agora o novo nó vira o primeiro da lista.

---

### Atualizando tamanho

```
lista->tamanho++
```

Isso mantém controle da quantidade de elementos.

---

# 6. Imprimindo a Lista

Arquivo:

```
lista_print.c
```

Código:

```c
Node* atual = lista->inicio;

while(atual != NULL) {
    printf("%d -> ", atual->valor);
    atual = atual->proximo;
}

printf("NULL\n");
```

---

## Como funciona

Começamos no primeiro elemento.

```
lista->inicio
```

Exemplo:

```
30 -> 20 -> 10 -> NULL
 ^
 atual
```

Depois avançamos:

```
atual = atual->proximo
```

Isso percorre toda a lista.

---

# 7. Controller

Arquivo:

```
ListaController.c
```

Ele controla o fluxo.

```c
Lista lista;

lista_init(&lista);

lista_insert(&lista, 10);
lista_insert(&lista, 20);
lista_insert(&lista, 30);

lista_print(&lista);
```

Resultado:

```
30 -> 20 -> 10 -> NULL
```

---

# 8. main.c

O `main` é o ponto inicial do programa.

```c
int main() {

    iniciar_lista();

    return 0;
}
```

Fluxo completo:

```
main
 ↓
controller
 ↓
service
 ↓
estrutura de dados
```

---

# 9. Compilação com Docker

Seu Docker compila o projeto com:

```
gcc main.c $(find src -name "*.c") -Isrc -o app
```

Isso significa:

* compilar `main.c`
* compilar todos arquivos `.c`
* usar `src` como pasta de include

---

# 10. O que você já implementou

Sua lista já possui:

```
lista_init
lista_insert
lista_print
```

Isso já permite:

```
criar lista
inserir valores
visualizar lista
```

---

# 11. Próximas funções recomendadas

Para completar uma lista encadeada:

```
lista_remove
lista_buscar
lista_insert_fim
lista_clear
```

---

# 12. Como adicionar novos services

Suponha que você queira criar uma **Pilha**.

## Passo 1 — criar pasta

```
src/application/services/Pilha
```

---

## Passo 2 — criar header

```
Pilha.h
```

Exemplo:

```c
typedef struct {
    int topo;
} Pilha;

void pilha_init(Pilha* p);
void pilha_push(Pilha* p, int valor);
void pilha_pop(Pilha* p);
```

---

## Passo 3 — implementar funções

Criar arquivos:

```
pilha_init.c
pilha_push.c
pilha_pop.c
```

---

## Passo 4 — criar controller

```
src/interfaces/PilhaController
```

Arquivo:

```
PilhaController.c
```

Exemplo:

```c
void iniciar_pilha() {

    Pilha p;

    pilha_init(&p);

}
```

---

## Passo 5 — chamar no main

```
iniciar_pilha();
```

---

# 13. Arquitetura final

Seu projeto segue a ideia:

```
main
 ↓
controllers
 ↓
services
 ↓
estruturas de dados
```

Isso é muito parecido com arquitetura usada em:

* backends
* microserviços
* sistemas grandes

---

# Conclusão

Você criou:

* uma arquitetura modular em C
* uma lista encadeada funcional
* um sistema organizado em camadas
* compilação automatizada com Docker

Isso já é uma base excelente para estudar:

* estruturas de dados
* organização de projetos grandes
* programação em C de forma profissional
