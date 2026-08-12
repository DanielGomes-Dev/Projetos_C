#include <stdio.h>
#include <stdlib.h>

#define QTD_VERTICES 4 //Criacao de constantes

//Estrutura grafo

typedef struct {
    int matriz[QTD_VERTICES][QTD_VERTICES];
    int num_vertices;
} Grafo;


// Iniciar o grafo com toda a matriz sendo 0;
// Funcao != de procedimento (nao tem retorno)
void inicializarGrafo(Grafo *g){
    g->num_vertices = 0;
    for (int i = 0; i < QTD_VERTICES; i++)
    {
        for (int j = 0; j < QTD_VERTICES; j++)
        {
            g->matriz[i][j] = 0;
        }
    }
}

void adicionarVertice(Grafo *g){
    if(g->num_vertices < QTD_VERTICES){
        printf("Vertice %d adicionado com sucesso!\n", g->num_vertices);
        g->num_vertices++;
    }
    else {
        printf("Nao foi possivel adicionar mais vertices. O limite foi atingido");
    }
}

int verticeExiste(int v, int numV){
    if(v>=0 && v<numV){
        return 1;
    }
    else{
        return 0;
    }
}


// procedimento para adicionar aresta entre dois vertices
void adicionarAresta(Grafo *g, int v1, int v2){
    if(verticeExiste(v1, g->num_vertices) && verticeExiste(v2, g->num_vertices)){
        g->matriz[v1][v2] = 1; //Adiciona aresta de v1 para v2;
        g->matriz[v2][v1] = 1; //Como o grafo é nao direcionado, adiciona tambem a aresta de v2 para v1;
        printf("Aresta entre %d e %d adicionada com sucesso.\n", v1, v2);
    } else {
        printf("Vertices invalidos! Aresta nao adicionada");
    }
}

// procedimento para remover aresta entre dois vértices
void removerAresta(Grafo *g, int v1, int v2){
    if(verticeExiste(v1, g->num_vertices) && verticeExiste(v2, g->num_vertices)){
        g->matriz[v1][v2] = 0; //Remove a aresta do vertice v1 para o vertice v2
        g->matriz[v2][v1] = 0; //Remove a aresta do vertice v2 para o vertice v1
        printf("Aresta entre %d e %d removida com sucesso.\n", v1, v2);
    }
    else {
        printf("Vertices invalidos! Aresta nao removida");
    }
}

void exibirMatriz(Grafo *g){
    printf("\nMatriz de Adjacencia do Grafo:\nVertices---");
    for(int i = 0; i < g->num_vertices; i++) printf("%d ", i);
    printf("\n");
    for (int i = 0; i < g->num_vertices; i++){
        printf("Vertice %d: ", i);
        for(int j = 0; j < g->num_vertices; j++){
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    Grafo g;
    inicializarGrafo(&g);

    // Adicionando vertices
    adicionarVertice(&g); // Vertice 0
    adicionarVertice(&g); // Vertice 1
    adicionarVertice(&g); // Vertice 2
    adicionarVertice(&g); // Vertice 3

    //Adicionando Aresta
    adicionarAresta(&g, 0, 1);
    adicionarAresta(&g, 1, 2);
    adicionarAresta(&g, 2, 3);
    adicionarAresta(&g, 0, 3);

    //exibindo
    exibirMatriz(&g);
    removerAresta(&g, 0, 3);
    exibirMatriz(&g);

    return 0;
}
