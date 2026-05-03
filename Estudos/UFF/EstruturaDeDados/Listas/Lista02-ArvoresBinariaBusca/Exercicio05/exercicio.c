#include <stdio.h>
#include <stdlib.h>




/*

Dada a seguinte representação de uma árvore binária de busca (ABB):

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TABB;

Escreva as seguintes funções:

(Q5) Reescreva as operações básicas da ABB para poder armazenar as figuras geométricas
quadrado, triângulo, retângulo e trapézio. A área da figura será usada para definir os elementos
pertencentes a sub-árvore esquerda e a sub-árvore direita. A impressão será em ordem simétrica e,
além da área, devem ser informadas as dimensões da figura.

*/

// Definição dos tipos de figuras
typedef enum { QUADRADO, TRIANGULO, RETANGULO, TRAPEZIO } T_FIG;

// Estrutura para armazenar as dimensões e o tipo da figura
typedef struct {
    T_FIG tipo;
    float d1, d2, d3; // d1: base/lado, d2: altura/base_menor, d3: base_maior (trapézio)
    float area;
} TFIGURA;

// Função auxiliar para traduzir o enum para texto
const char* nome_figura(T_FIG tipo) {
    switch (tipo) {
        case QUADRADO:  return "Quadrado";
        case TRIANGULO: return "Triangulo";
        case RETANGULO: return "Retangulo";
        case TRAPEZIO:  return "Trapezio";
        default: return "Desconhecido";
    }
}

typedef struct ab{
    TFIGURA fig;
    int info;
    struct ab *esq, *dir;
}TABB;

TABB* Cria (int info, TABB *sae, TABB *sad){

    TABB *novo =  (TABB *)malloc(sizeof(TABB));
    
    novo->info = info;
    novo->esq = sae;
    novo->dir = sad;

    return novo;
}

float calcula_area(T_FIG tipo, float d1, float d2, float d3) {
    switch (tipo) {
        case QUADRADO:  return d1 * d1;
        case TRIANGULO: return (d1 * d2) / 2.0;
        case RETANGULO: return d1 * d2;
        case TRAPEZIO:  return ((d1 + d3) * d2) / 2.0;
        default: return 0;
    }
}

// Operação Básica: Criação de Nó
TABB* cria_no(T_FIG tipo, float d1, float d2, float d3) {
    TABB *novo = (TABB*)malloc(sizeof(TABB));
    novo->fig.tipo = tipo;
    novo->fig.d1 = d1;
    novo->fig.d2 = d2;
    novo->fig.d3 = d3;
    novo->fig.area = calcula_area(tipo, d1, d2, d3);
    novo->esq = novo->dir = NULL;
    return novo;
}



// Função auxiliar baseada no seu material para inserir respeitando a ordem de busca
TABB *insere_ABB(TABB *a, int info) {
    if (!a) return Cria(info, NULL, NULL);
    if (info < a->info)
        a->esq = insere_ABB(a->esq, info);
    else if (info > a->info)
        a->dir = insere_ABB(a->dir, info);
    return a;
}

// Operação Básica: Inserção (Baseada na ÁREA)
TABB* insere_ABB_fig(TABB *a, T_FIG tipo, float d1, float d2, float d3) {
    float area_nova = calcula_area(tipo, d1, d2, d3);
    
    if (!a) return cria_no(tipo, d1, d2, d3);
    
    if (area_nova < a->fig.area)
        a->esq = insere_ABB_fig(a->esq, tipo, d1, d2, d3);
    else if (area_nova > a->fig.area)
        a->dir = insere_ABB_fig(a->dir, tipo, d1, d2, d3);
        
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




void ImpPre(TABB *a){
    if(a){
        printf("%d ",a->info);
        ImpPre(a->esq);
        ImpPre(a->dir);
    }
}

// Operação Básica: Impressão Simétrica (In-order)
void imprime_simetrico(TABB *a) {
    if (a) {
        imprime_simetrico(a->esq);
        
        printf("Figura: %-10s | Area: %7.2f | Dims: [%.1f, %.1f, %.1f]\n", 
               nome_figura(a->fig.tipo), 
               a->fig.area, 
               a->fig.d1, a->fig.d2, a->fig.d3);
               
        imprime_simetrico(a->dir);
    }
}

void ImpSim(TABB *a){
    if(a){
        ImpSim(a->esq);
        printf("%d ",a->info);
        ImpSim(a->dir);
    }
}

void ImpPos(TABB *a){
    if(a){
        ImpPos(a->esq);
        ImpPos(a->dir);
        printf("%d ",a->info);
    }
}

int main (){
//     TABB *a8 = Cria(8, NULL, NULL);
//     TABB *a7 = Cria(7, NULL, NULL);
//     TABB *a6 = Cria(6, a7, a8);
//     TABB *a5 = Cria(5, NULL, NULL);
//     TABB *a4 = Cria(40, NULL, NULL);
//     TABB *a3 = Cria(-3, a4, a5);
//     TABB *a2 = Cria(2, a3, a6);
//     TABB *a1 = Cria(1, a2, a3);
//     TABB *raiz = Cria(0, a1, NULL);

//     TABB *raiz2 = reorganiza_para_ABB(raiz);

//     TABB *arvore_par = retira_impares(raiz2);

    
//    // Testando a Original
//     printf("Original (Pre-ordem): ");
//     ImpPre(raiz);
//     printf("\nReorg (Pre-ordem): ");
//     ImpPre(raiz2);
//     printf("\n\n------------------------------\n\n");
//     printf("\nArvore Par (Pre-ordem): ");
//     ImpPre(arvore_par);
    

    // Testando a Copiada

    TABB *raiz = NULL;

    // Inserindo figuras variadas
    raiz = insere_ABB_fig(raiz, QUADRADO, 4, 0, 0);       // Area: 16
    raiz = insere_ABB_fig(raiz, TRIANGULO, 10, 5, 0);    // Area: 25
    raiz = insere_ABB_fig(raiz, RETANGULO, 2, 3, 0);     // Area: 6
    raiz = insere_ABB_fig(raiz, TRAPEZIO, 4, 5, 6);      // Area: 25 (Não insere se duplicado ou vai p/ dir)

    printf("ABB de Figuras Geometricas (Ordem Simetrica por Area):\n");
    imprime_simetrico(raiz);

    return 0;
}