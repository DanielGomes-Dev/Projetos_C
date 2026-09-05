

#include <stdio.h>
#include <stdlib.h>

/*

(b) Dada a seguinte representação de uma árvore binária:

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TAB;

Escreva as seguintes funções:

(Q9) ache a quantidade de nós folha: int nf(TAB *a);

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

int nf(TAB *a) {
    // 1. Caso base: se a árvore está vazia, não há folhas
    if (a == NULL) {
        return 0;
    }

    // 2. Verifica se o nó atual é uma folha
    // (Não tem filho à esquerda E não tem filho à direita)
    if (a->esq == NULL && a->dir == NULL) {
        return 1;
    }

    // 3. Se não for folha, continua a busca nas subárvores
    // A soma das folhas da árvore é a soma das folhas das subárvores
    return nf(a->esq) + nf(a->dir);
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

    int ni_count = nf(raiz);

    printf("Existem %d folhas na arvore", ni_count);


    return 0;
}