#include <stdio.h>
#include <stdlib.h>
#include "TLSE/TLSE.h"

/*

Q4) Implemente uma função que copie uma lista. A lista original deve permanecer
inalterada. O protótipo da função é o seguinte: TLSE *copia (TLSE *l).

*/



TLSE *copia (TLSE *l, int *size_le){
    printf("copiando...: \n");
    // printf("Size: %d \n", size_le); 


    if(l == NULL) return NULL;
    
    
    copia(l->prox, size_le + 1);

    // TLSE *copia =
    
    return l;
}


int main (){

    TLSE *le = TLSE_inicializa();
    le = TLSE_insere(le, 1); 
    // printf("le: %d", &le);
    TLSE_insere_void(&le, 2); 
    
    printf("Test ok\n");

    TLSE_imp_rec(le);
    printf("\n");
    int size_le = 0;
    printf("Size 1: %d \n", size_le); 
    printf("Size 1: %p \n", &size_le); 
    // printf("Size: %p \n", *size_le); 

    // copia(le, size_le);
    return 0;
}