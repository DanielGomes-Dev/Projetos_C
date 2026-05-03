#include <stdio.h>
#include <stdlib.h>

/*

(b) Dada a seguinte representação de uma árvore binária:

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TAB;

Escreva as seguintes funções:

(Q5) uma função que, dadas duas árvores deste tipo, testa se estas árvores são iguais. A função
retorna um se elas são iguais e zero, caso contrário. A função deve obedecer ao seguinte protótipo:
int igual (TAB* a1, TAB* a2);

*/



// sae -> subárvore da esquerda
// sad -> subárvore da direita

typedef struct AB {
    int info;
    struct AB *esq;
    struct AB *dir;
} TAB;

TAB* Cria (int info, TAB *sae, TAB *sad){

    TAB *novo =  (TAB *)malloc(sizeof(TAB));
    
    novo->info = info;
    novo->esq = sae;
    novo->dir = sad;

    return novo;
}

TAB* Copia(TAB *a) {
    if (a == NULL) {
        return NULL;
    }

    TAB *novo = (TAB *)malloc(sizeof(TAB));
    if (novo == NULL) return NULL; 

    novo->info = a->info;

    novo->esq = Copia(a->esq);
    novo->dir = Copia(a->dir);
    return novo;
}

TAB* Espelha(TAB *a){
    if(a == NULL){
        return NULL;
    }

    TAB *novo = (TAB *)malloc(sizeof(TAB));
    if(novo == NULL) return NULL;

    novo->info = a->info;

    novo->esq = Espelha(a->dir);
    novo->dir = Espelha(a->esq);

    return novo;
}



int Igual (TAB* a1, TAB* a2) {
    if (a1 == NULL && a2 == NULL) {
        return 1;
    }
    if (a1 == NULL || a2 == NULL) {
        return 0;
    }
    if (a1->info != a2->info) {
        return 0;
    }

    return Igual(a1->esq, a2->esq) && Igual(a1->dir, a2->dir);
}

void ImpPre(TAB *a){
    if(a){
        printf("%d ",a->info);
        ImpPre(a->esq);
        ImpPre(a->dir);
    }
}

void ImpSim(TAB *a){
    if(a){
        ImpSim(a->esq);
        printf("%d ",a->info);
        ImpSim(a->dir);
    }
}

void ImpPos(TAB *a){
    if(a){
        ImpPos(a->esq);
        ImpPos(a->dir);
        printf("%d ",a->info);
    }
}

int main (){
    TAB *a8 = Cria(8, NULL, NULL);
    TAB *a7 = Cria(7, NULL, NULL);
    TAB *a6 = Cria(6, a7, a8);
    TAB *a5 = Cria(5, NULL, NULL);
    TAB *a4 = Cria(40, NULL, NULL);
    TAB *a3 = Cria(-3, a4, a5);
    TAB *a2 = Cria(2, a3, a6);
    TAB *a1 = Cria(1, a2, a3);
    TAB *raiz = Cria(0, a1, NULL);

    TAB *copiada = Copia(raiz);
    TAB *espelhada = Espelha(raiz);

    int igual = Igual(raiz, copiada);
    int not_igual = Igual(raiz, espelhada);


    
    printf("Original: ");
    ImpPre(raiz);
    printf("\n\n------------------------------\n\n");
    printf("\nCopiada: ");
    ImpPre(copiada);
    printf("\n");
    printf("%d", igual);

    printf("\n\n------------------------------\n\n");
    printf("\nEspelhada: ");
    ImpPre(espelhada);
    printf("\n");
    printf("%d", not_igual);
    printf("\n\n------------------------------\n\n");

    // Testando a Copiada

    return 0;
}