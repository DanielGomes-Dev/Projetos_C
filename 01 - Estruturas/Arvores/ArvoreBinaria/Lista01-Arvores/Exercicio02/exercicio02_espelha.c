#include <stdio.h>
#include <stdlib.h>

/*

(b) Dada a seguinte representação de uma árvore binária:

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TAB;

Escreva as seguintes funções:

(Q2) espelho de uma árvore (o que está a esquerda na árvore original, estará a direita no espelho, e
vice-versa): TAB* espelho (TAB *a);

*/


typedef struct AB {
    int info;
    struct AB *esq;
    struct AB *dir;
}TAB;

TAB* Cria (int r, TAB *sae, TAB *sad){
    TAB *novo = (TAB *)malloc(sizeof(TAB));
    novo->info = r;
    novo->esq = sae;
    novo->dir = sad;
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

void ImpPre(TAB *a){
    if(a != NULL){
        printf("%d ", a->info);
        ImpPre(a->esq);
        ImpPre(a->dir);
    }
}

void ImpSim(TAB *a){
    if(a != NULL){
        ImpSim(a->esq);
        printf("%d ", a->info);
        ImpSim(a->dir);
    }
}

void ImpPos(TAB *a){
    if(a != NULL){
        ImpPos(a->dir);
        ImpPos(a->esq);
        printf("%d ", a->info);
    }
}

int main (){
    TAB *a4 = Cria(1, NULL, NULL);
    TAB *a3 = Cria(2, NULL, NULL);
    TAB *a2 = Cria(3, a4, NULL);
    TAB *a1 = Cria(4, NULL, a3);
    TAB *raiz = Cria(10, a1, a2);


    TAB *arvore_Espelhada = Espelha(raiz);

    // Testando a Original
    printf("Original (Pre-ordem): ");
    ImpPre(raiz);
    printf("\nOriginal (Simetrica): ");
    ImpSim(raiz);
    
    printf("\n\n------------------------------\n\n");

    // Testando a Copiada
    printf("Copiada  (Pre-ordem): ");
    ImpPre(arvore_Espelhada);
    printf("\nCopiada  (Simetrica): ");
    ImpSim(arvore_Espelhada);
    printf("\n");
    return 0;
}