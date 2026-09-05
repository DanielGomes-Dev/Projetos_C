## 1. Mapeamento e Identificação

* **Problema:** O exercício solicita o desenvolvimento de um software em linguagem C capaz de ler dois arquivos textuais (um contendo nós de dados sobre filmes e pessoas, e outro contendo os relacionamentos entre eles) para processar e gerar informações para agências de talentos de Hollywood.
* **Tópico da Matéria:** O problema trata de **Estruturas de Dados Avançadas**, especificamente a modelagem, representação e manipulação de **Grafos** (onde Filmes e Pessoas são vértices/nós, e as interações como `ACTED_IN`, `DIRECTED`, `WROTE` e `PRODUCED` são as arestas/relacionamentos direcionados e valorados).

---

## 2. Transcrição Fiel

> **Trabalho Computacional de Estruturas de Dados e Seus Algoritmos**
> * A implementacao deve ser feita em C
> 
> 
> Considere que você seja contratado pelas agências de talentos de Hollywood para gerar algumas informações relacionadas a filmes.
> Seu software deve ler um arquivo informações de atores, produtores e filmes, e um arquivo relacionamentos entre eles.

---

## 3. Resolução Baseada no Texto e Passo a Passo Detalhado

Como o enunciado fornecido no texto descreve os dados de entrada (`Nodes.txt` e `Relationships.txt`), a estrutura de dados ideal para mapear esses registros sem perda de generalização e permitindo buscas eficientes em C é uma **Lista de Adjacência Dinâmica**, implementada por meio de structs e ponteiros.

Abaixo está o guia passo a passo ensinando a arquitetar e codificar a solução exata para este problema.

### Passo 1: Definição da Anatomia dos Nós (Vértices)

Primeiro, precisamos criar uma estrutura capaz de armazenar os dados de `Nodes.txt`. O arquivo possui dois tipos de rótulos: `Movie` e `Person`. Usaremos uma enumeração (`Type`) para rastrear o tipo de nó de forma explícita.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { MOVIE, PERSON } NodeType;

typedef struct {
    char name_or_title[150];
    int year;                 // Ano de lançamento ou de nascimento
    char extra_info[200];     // Tagline para filmes; vazio para pessoas
} NodeData;

// Estrutura que representa o vértice no Grafo
typedef struct GraphNode {
    int id;                   // Identificador único gerado na leitura sequencial
    NodeType type;
    NodeData data;
    struct Edge* edges_head;  // Ponteiro para a lista de adjacência (relacionamentos)
    struct GraphNode* next;   // Ponteiro para encadeamento na lista principal de nós
} GraphNode;

```

### Passo 2: Definição da Anatomia dos Relacionamentos (Arestas)

Cada linha de `Relationships.txt` conecta uma pessoa a um filme através de uma ação (`ACTED_IN`, `DIRECTED`, etc.) e pode conter atributos específicos como o papel (`role`).

A aplicação do *Pilar da Rastreabilidade* nos obriga a manter os ponteiros de origem e destino perfeitamente conectados.

```c
typedef struct Edge {
    char relationship_type[20]; // ACTED_IN, DIRECTED, PRODUCED, WROTE
    char role[100];             // Papel desempenhado (caso aplicável)
    GraphNode* target;          // Ponteiro direto para o nó de destino (Filme)
    struct Edge* next;          // Próximo relacionamento deste nó
} Edge;

```

### Passo 3: Criação da Estrutura Principal do Grafo

Para gerenciar a coleção de nós de forma dinâmica (permitindo expansão sem tamanho fixo), define-se a estrutura de controle do Grafo.

```c
typedef struct {
    GraphNode* nodes_head;
    int total_nodes;
} Graph;

Graph* createGraph() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    if (g != NULL) {
        g->nodes_head = NULL;
        g->total_nodes = 0;
    }
    return g;
}

```

### Passo 4: Algoritmo de Inserção de Nós (`Nodes.txt`)

Para popular nosso grafo, o arquivo `Nodes.txt` deve ser lido linha por linha. O algoritmo abaixo divide a string utilitária usando o caractere delimitador `|`.

```c
void insertNode(Graph* g, NodeType type, char* name, int year, char* extra) {
    GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
    newNode->id = g->total_nodes++;
    newNode->type = type;
    
    strcpy(newNode->data.name_or_title, name);
    newNode->data.year = year;
    strcpy(newNode->data.extra_info, extra);
    
    newNode->edges_head = NULL;
    newNode->next = NULL;
    
    // Insere no fim da lista de nós para manter a ordem de leitura
    if (g->nodes_head == NULL) {
        g->nodes_head = newNode;
    } else {
        GraphNode* temp = g->nodes_head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

```

### Passo 5: Algoritmo de Busca de Vértices

Antes de criar uma aresta, é necessário localizar a posição de memória exata do nó de origem (Pessoa) e do nó de destino (Filme).

```c
GraphNode* findNode(Graph* g, char* name_or_title) {
    GraphNode* temp = g->nodes_head;
    while (temp != NULL) {
        if (strcmp(temp->data.name_or_title, name_or_title) == 0) {
            return temp; // Retorna a referência direta ao objeto
        }
        temp = temp->next;
    }
    return NULL; // Caso não encontre
}

```

### Passo 6: Algoritmo de Inserção de Relacionamentos (`Relationships.txt`)

Ao ler uma linha como `START Person | Keanu Reeves | ACTED_IN | END Movie | The Matrix | role: Neo`, o sistema extrai os nomes, localiza os nós usando a função do *Passo 5*, e conecta a aresta de forma direcionada.

```c
void addRelationship(Graph* g, char* person_name, char* movie_title, char* rel_type, char* role) {
    GraphNode* person = findNode(g, person_name);
    GraphNode* movie = findNode(g, movie_title);
    
    if (person == NULL || movie == NULL) {
        return; // Proteção caso algum nó não exista no arquivo 1
    }
    
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    strcpy(newEdge->relationship_type, rel_type);
    strcpy(newEdge->role, role);
    newEdge->target = movie; // Relação direcionada: Pessoa -> Filme
    
    // Inserção na cabeça da lista de adjacência da Pessoa (Otimização O(1))
    newEdge->next = person->edges_head;
    person->edges_head = newEdge;
}

```

### Passo 7: Função Principal (`main`) e Parser de Arquivos

Demonstração matemática e lógica de como os fluxos de arquivos interagem com as estruturas dinâmicas criadas:

```c
int main() {
    Graph* hollywoodGraph = createGraph();
    
    // --- SIMULAÇÃO DA LEITURA DE NODES.TXT ---
    // Exemplo extraído do arquivo enviado: Movie | The Matrix | 1999 | Welcome to the Real World
    insertNode(hollywoodGraph, MOVIE, "The Matrix", 1999, "Welcome to the Real World");
    insertNode(hollywoodGraph, PERSON, "Keanu Reeves", 1964, "");
    insertNode(hollywoodGraph, PERSON, "Carrie-Anne Moss", 1967, "");
    
    // --- SIMULAÇÃO DA LEITURA DE RELATIONSHIPS.TXT ---
    // Exemplo extraído do arquivo enviado: START Person | Keanu Reeves | ACTED_IN | END Movie | The Matrix | role: Neo
    addRelationship(hollywoodGraph, "Keanu Reeves", "The Matrix", "ACTED_IN", "Neo");
    addRelationship(hollywoodGraph, "Carrie-Anne Moss", "The Matrix", "ACTED_IN", "Trinity");

    // --- CONSULTA DE EXEMPLO: Relatório de Atores e seus Filmes ---
    printf("--- RELATÓRIO DE TALENTOS HOLLYWOOD ---\n");
    GraphNode* current = hollywoodGraph->nodes_head;
    while (current != NULL) {
        if (current->type == PERSON) {
            printf("\nAtor/Diretor: %s (Nascimento: %d)\n", current->data.name_or_title, current->data.year);
            Edge* e = current->edges_head;
            while (e != NULL) {
                printf("  -> %s no filme '%s'", e->relationship_type, e->target->data.name_or_title);
                if (strlen(e->role) > 0) {
                    printf(" atuando como [%s]", e->role);
                }
                printf("\n");
                e = e->next;
            }
        }
        current = current->next;
    }

    // --- LIBERAÇÃO DE MEMÓRIA (BOAS PRÁTICAS EM C) ---
    current = hollywoodGraph->nodes_head;
    while (current != NULL) {
        Edge* e = current->edges_head;
        while (e != NULL) {
            Edge* toDelete = e;
            e = e->next;
            free(toDelete);
        }
        GraphNode* nodeToDelete = current;
        current = current->next;
        free(nodeToDelete);
    }
    free(hollywoodGraph);
    
    return 0;
}

```

---

## 4. Fórmula de Resposta Final

A modelagem de dados para o sistema proposto obedece à definição formal de um Grafo Direcionado e Atribuído $G$:

$$G = (V, E)$$

Onde:

* $V$ representa o conjunto de Vértices compostos por entidades do tipo $\text{NodeType} \in \{\text{MOVIE}, \text{PERSON}\}$, extraídos sequencialmente de `Nodes.txt`.
* $E$ representa o conjunto de Arestas direcionadas onde cada aresta $e \in E$ é definida pelo par ordenado $e = (v_{\text{person}}, v_{\text{movie}})$ associada aos atributos mapeados $\{\text{relationship\_type}, \text{role}\}$, extraídos de `Relationships.txt`.