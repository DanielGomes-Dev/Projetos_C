#include <stdio.h>
#include <stdlib.h>

/*

(b) Dada a seguinte representação de uma árvore binária:

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TAB;

Escreva as seguintes funções:

(Q6) uma função em C que, dada uma árvore binária qualquer, retire todos os elementos pares da
árvore original. A função deve ter o seguinte protótipo: TAB* retira_pares (TAB* arv);


A remoção em uma árvore binária comum (que não é necessariamente de busca) é um pouco mais complexa, 
pois quando removemos um nó que não é uma folha, precisamos decidir qual filho subirá para o seu lugar ou como reorganizar a estrutura. 
Uma estratégia comum e eficiente é:

    1. Tratar primeiro as subárvores (esquerda e direita) recursivamente.
    2. Verificar se a raiz atual é par.
    3. Se for par, devemos removê-la e retornar um de seus filhos (ou reorganizar).

*/

typedef struct AB {
    int info;
    struct AB *esq;
    struct AB *dir;
}TAB;

TAB* Cria(int info, TAB *sae, TAB *sad){
    TAB *novo = (TAB*)malloc(sizeof(TAB));

    novo->info = info;
    novo->esq = sae;
    novo->dir = sad;

    return novo;
}

TAB* RetiraPares(TAB *arv){
    if (arv == NULL) return NULL;
    // 1. Processa recursivamente as subárvores primeiro (pós-ordem)
    arv->esq = RetiraPares(arv->esq);
    arv->dir = RetiraPares(arv->dir);

    // 2. Verifica se o nó atual deve ser removido
    if (arv->info % 2 == 0) {
        TAB *aux;
        
        // Caso 1: Nó folha
        if (arv->esq == NULL && arv->dir == NULL) {
            free(arv);
            return NULL;
        }
        
        // Caso 2: Possui apenas um dos filhos
        if (arv->esq == NULL) {
            aux = arv->dir;
            free(arv);
            return aux;
        }
        if (arv->dir == NULL) {
            aux = arv->esq;
            free(arv);
            return aux;
        }

        /* 
        Caso 3: Possui dois filhos. 
        Estratégia: Substituir a info do nó atual pela info do nó mais à direita 
        da subárvore esquerda (ou mais à esquerda da direita) e remover esse sucessor.
        No entanto, como a árvore NÃO é de busca (BST), podemos apenas subir um dos filhos 
        e "re-pendurar" a outra subárvore em uma extremidade livre.

        */
        aux = arv->esq;
        TAB *p = aux;
        while (p->dir != NULL) p = p->dir; // Busca o extremo da subárvore esquerda
        p->dir = arv->dir; // Pendura a subárvore direita original lá
        
        TAB *temp = arv->esq;
        free(arv);
        return temp;
    }

    return arv;

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
        ImpPre(a->esq);
        printf("%d ",a->info);
        ImpPre(a->dir);
    }
}


void ImpPos(TAB *a){
    if(a){
        ImpPre(a->esq);
        ImpPre(a->dir);
        printf("%d ",a->info);
    }
}

int main(){
    printf("Hello\n\n");
    TAB *a5 = Cria(6, NULL, NULL);
    TAB *a4 = Cria(5, NULL, NULL);
    TAB *a3 = Cria(7, a4, a5);
    TAB *a2 = Cria(3, NULL, NULL);
    TAB *a1 = Cria(2, a2, NULL);

    TAB *raiz = Cria(1, a3, a1);

    ImpPre(raiz);
    printf("\n\n");
    ImpSim(raiz);
    printf("\n\n");
    
    TAB *sa_impar = RetiraPares(raiz);

    printf("\n\n");
    ImpPre(sa_impar);
    printf("\n\n");
    ImpSim(sa_impar);

    return 0;
}

