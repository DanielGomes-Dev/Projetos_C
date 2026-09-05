#include <stdlib.h>

/* representação dos nós*/

typedef struct arvbin{
int info;
struct arvbin *esq, *dir;
}TAB;

TAB* inicializa(void){
    return NULL;
}

TAB* cria(int r, TAB *sae, TAB *sad){

    TAB *novo;
    novo = (TAB *)malloc(sizeof(TAB));
    novo->info = r;
    novo->esq = sae;
    novo->dir = sad;
    return novo;
}

