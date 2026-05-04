Vou decompor o código em blocos lógicos e explicar o que cada linha faz, focando na finalidade técnica e na lógica de programação utilizada.

---

## 1. Cabeçalho e Definições
```c
#include <stdio.h>
#include <stdlib.h>

#define QTD_VERTICES 4 // Criação de constante
```
* **`#include`**: Importa as bibliotecas padrão de entrada/saída (`stdio.h`) e funções utilitárias (`stdlib.h`).
* **`#define QTD_VERTICES 4`**: Define uma constante global. Se você precisar de um grafo com 100 vértices, basta mudar esse número aqui e todo o código se adaptará automaticamente.

## 2. Estrutura do Grafo
```c
typedef struct {
    int matriz[QTD_VERTICES][QTD_VERTICES];
    int num_vertices;
} Grafo;
```
* **`typedef struct`**: Cria um novo tipo de dado chamado `Grafo`.
* **`matriz[...][...]`**: Uma matriz quadrada onde as linhas e colunas representam os vértices.
* **`num_vertices`**: Uma variável inteira que conta quantos vértices estão ativos no momento (importante para não tentar usar vértices que ainda não foram "adicionados").



---

## 3. Inicialização
```c
void inicializarGrafo(Grafo *g){
    g->num_vertices = 0;
    for (int i = 0; i < QTD_VERTICES; i++) {
        for (int j = 0; j < QTD_VERTICES; j++) {
            g->matriz[i][j] = 0;
        }
    }
}
```
* **`Grafo *g`**: Recebe um ponteiro para o grafo, permitindo que a função modifique o grafo original criado na `main`.
* **Laços `for` aninhados**: Percorrem cada célula da matriz (linhas `i` e colunas `j`) definindo o valor como **0**, o que indica que inicialmente não existe nenhuma conexão (aresta) entre os vértices.

---

## 4. Gerenciamento de Vértices
```c
void adicionarVertice(Grafo *g){
    if(g->num_vertices < QTD_VERTICES){
        printf("Vertice %d adicionado com sucesso!\n", g->num_vertices);
        g->num_vertices++;
    }
    else {
        printf("Nao foi possivel adicionar mais vertices. O limite foi atingido");
    }
}
```
* **Lógica**: Esta função apenas "habilita" o próximo índice disponível. Se `num_vertices` é 0, ela adiciona o vértice 0 e aumenta o contador para 1. Ela impede que você use mais vértices do que o tamanho definido na constante.

```c
int verticeExiste(int v, int numV){
    if(v >= 0 && v < numV) return 1;
    else return 0;
}
```
* **Função Auxiliar**: Retorna **1 (Verdadeiro)** se o número do vértice solicitado estiver dentro da faixa de vértices que já foram adicionados ao grafo. Caso contrário, retorna **0 (Falso)**.

---

## 5. Gerenciamento de Arestas (Conexões)
```c
void adicionarAresta(Grafo *g, int v1, int v2){
    if(verticeExiste(v1, g->num_vertices) && verticeExiste(v2, g->num_vertices)){
        g->matriz[v1][v2] = 1;
        g->matriz[v2][v1] = 1;
        printf("Aresta entre %d e %d adicionada com sucesso.\n", v1, v2);
    } else {
        printf("Vertices invalidos! Aresta nao adicionada");
    }
}
```
* **`g->matriz[v1][v2] = 1`**: Marca que existe uma conexão. 
* **Simetria**: Note que o código marca tanto de `v1` para `v2` quanto de `v2` para `v1`. Isso ocorre porque o grafo é **não direcionado** (se existe estrada da cidade A para B, também existe de B para A).

```c
void removerAresta(Grafo *g, int v1, int v2){
    if(verticeExiste(v1, g->num_vertices) && verticeExiste(v2, g->num_vertices)){
        g->matriz[v1][v2] = 0;
        g->matriz[v2][v1] = 0;
        printf("Aresta entre %d e %d removida com sucesso.\n", v1, v2);
    }
    // ... else com erro ...
}
```
* Faz exatamente o oposto da anterior: volta os valores na matriz para **0**.



---

## 6. Visualização
```c
void exibirMatriz(Grafo *g){
    // ... código de formatação ...
    for (int i = 0; i < g->num_vertices; i++){
        printf("Vertice %d: ", i);
        for(int j = 0; j < g->num_vertices; j++){
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}
```
* Percorre a matriz e imprime os valores. Isso permite ver o estado atual do grafo no console de forma tabular.

---

## 7. Execução Principal (`main`)
```c
int main(){
    Grafo g;                   // Declara o grafo
    inicializarGrafo(&g);      // Limpa a memória

    adicionarVertice(&g);      // Cria 4 pontos no mapa (0 a 3)
    adicionarVertice(&g);
    adicionarVertice(&g);
    adicionarVertice(&g);

    adicionarAresta(&g, 0, 1); // Conecta 0-1
    adicionarAresta(&g, 1, 2); // Conecta 1-2
    adicionarAresta(&g, 2, 3); // Conecta 2-3
    adicionarAresta(&g, 0, 3); // Conecta 0-3 (fecha um quadrado)

    exibirMatriz(&g);          // Mostra o quadrado
    removerAresta(&g, 0, 3);   // Quebra uma conexão
    exibirMatriz(&g);          // Mostra o resultado final

    return 0;
}
```
* A `main` organiza o fluxo: limpa, adiciona a estrutura, faz as conexões e exibe o resultado para o usuário. O uso do operador `&` (ex: `&g`) é necessário para passar o **endereço** da memória para as funções, permitindo que elas alterem a variável `g` diretamente.