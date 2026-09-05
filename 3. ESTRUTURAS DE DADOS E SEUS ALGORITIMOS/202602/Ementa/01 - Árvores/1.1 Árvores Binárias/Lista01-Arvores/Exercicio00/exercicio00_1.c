#include <stdio.h>

#include "TAB/TAB.h"

// typedef struct ab{
//     int info;
//     struct ab *esq, *dir
// } TAB;

/*

(a) Implemente o tipo abstrato de dados lista simplesmente encadeada genérica, usando void *.

*/


TAB* copia_01(TAB *ab){

    if(!ab) return NULL;

    TAB *copia_ab = (TAB*)(malloc(sizeof(TAB)));
    
    copia_ab->info = ab->info;
    copia_ab->esq = copia_01(ab->esq);
    copia_ab->dir = copia_01(ab->dir);

    return copia_ab;
}


TAB* copia_02(TAB *ab){
    if(!ab) return NULL;
    return TAB_cria(ab->info, copia_02(ab->esq), copia_02(ab->dir));
}

int main(){

    // TAB *ab_05 =  TAB_cria(5, folha_01, folha_02);
    // TAB *ab_04 =  TAB_cria(4, folha_01, folha_02);
    TAB *ab_03 =  TAB_cria(3, TAB_inicializa(), TAB_inicializa());
    TAB *ab_02 =  TAB_cria(2, TAB_inicializa(), TAB_inicializa());
    TAB *ab_01 =  TAB_cria(1, ab_02, ab_03);
    printf("Original: ");
    TAB_imp_pre(ab_01);
    printf("\n");

    TAB *copia_ab_01 = copia_01(ab_01);

    printf("Copia 01: ");
    TAB_imp_pre(copia_ab_01);
    printf("\n");

    TAB *copia_ab_02 = copia_02(ab_01);

    printf("Copia 02: ");
    TAB_imp_pre(copia_ab_02);
    printf("\n");


    
    return 0;
}