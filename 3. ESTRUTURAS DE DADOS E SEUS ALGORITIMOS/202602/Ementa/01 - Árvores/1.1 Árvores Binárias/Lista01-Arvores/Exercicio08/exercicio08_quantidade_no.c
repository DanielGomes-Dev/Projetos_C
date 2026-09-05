#include <stdio.h>
#include <stdlib.h>

/*

(b) Dada a seguinte representação de uma árvore binária:

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TAB;

Escreva as seguintes funções:

(Q8) descubra a quantidade de nós internos: int ni(TAB *a);

*/



typedef struct ab {
    int info;
    struct ab *esq, *dir;
} TAB;

TAB* Cria(int info, TAB *sae, TAB *sad){
    TAB *novo = (TAB*)malloc(sizeof(TAB));

    novo->info = info;
    novo->esq = sae;
    novo->dir = sad;

    return novo;
}

int ni(TAB *a) {
    // Caso base: se a árvore está vazia, não há nós
    if (a == NULL) {
        return 0;
    }

    // Verifica se o nó atual é uma folha (não tem filhos)
    if (a->esq == NULL && a->dir == NULL) {
        return 0;
    }

    // Se chegou aqui, o nó tem pelo menos um filho, logo é interno.
    // Retornamos 1 (o nó atual) + a soma dos nós internos das subárvores.
    return 1 + ni(a->esq) + ni(a->dir);
}

void ImpPre(TAB *a){
    if(a){
        printf("%d\n",a->info);
        ImpPre(a->esq);
        ImpPre(a->dir);
    }
}


void ImpSim(TAB *a){
    if(a){
        ImpPre(a->esq);
        printf("%d\n",a->info);

        ImpPre(a->dir);
    }
}


void ImpPos(TAB *a){
    if(a){
        ImpPre(a->esq);
        ImpPre(a->dir);

    }
}

int main(){
    printf("Hello\n\n");
    TAB *a5 = Cria(6, NULL, NULL); // Folha
    TAB *a4 = Cria(5, NULL, NULL); // Folha

    TAB *a3 = Cria(7, a4, a5);
    TAB *a2 = Cria(3, NULL, NULL); // Folha
    TAB *a1 = Cria(2, a2, NULL);

    TAB *raiz = Cria(1, a3, a1);

    int ni_count = ni(raiz);

    printf("Existem %d nós na arvore", ni_count);


    return 0;
}