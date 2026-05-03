#include <stdio.h>
#include <stdlib.h>

/*

(b) Dada a seguinte representação de uma árvore binária:

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TAB;

Escreva as seguintes funções:

(Q4) menor elemento da árvore: TAB* menor(TAB *a);

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

TAB* Menor (TAB *a){

    if(a == NULL) return a;
    TAB *min = a;
    TAB *menor_esq = Menor(a->esq);
    TAB *menor_dir = Menor(a->dir);

    if(menor_esq != NULL && min->info > menor_esq->info){
        min = menor_esq;
    }

    if(menor_dir != NULL && min->info > menor_dir->info){
        min = menor_dir;
    }
    
    return min;

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

    TAB *menor_da_arvore = Menor(raiz);

    
   // Testando a Original
    printf("Original (Pre-ordem): ");
    ImpPre(raiz);
    printf("\nOriginal (Simetrica): ");
    ImpSim(raiz);
    
    printf("\n\n------------------------------\n\n");

    // Testando a Copiada
    printf("Menor: %d", menor_da_arvore->info);

    return 0;
}