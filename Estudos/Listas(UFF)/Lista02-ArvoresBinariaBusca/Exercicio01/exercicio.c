


#include <stdio.h>
#include <stdlib.h>

/*

Dada a seguinte representação de uma árvore binária de busca (ABB):

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TABBB;

Escreva as seguintes funções:

(Q1) maior elemento da árvore: TABBB* maior(TABB *a);

*/


// sae -> subárvore da esquerda
// sad -> subárvore da direita

typedef struct ab{
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

// Função auxiliar baseada no seu material para inserir respeitando a ordem de busca
TABB *insere_ABB(TABB *a, int info) {
    if (!a) return Cria(info, NULL, NULL);
    if (info < a->info)
        a->esq = insere_ABB(a->esq, info);
    else if (info > a->info)
        a->dir = insere_ABB(a->dir, info);
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

TABB* maior(TABB *a) {
    // Se a árvore estiver vazia, retorna NULL
    if (!a) return NULL;

    // Enquanto houver um filho à direita, o maior estará lá
    while (a->dir != NULL) {
        a = a->dir;
    }

    // Retorna o nó que contém o maior valor
    return a;
}

TABB* Maior(TABB *a) {
    // Caso base: árvore vazia
    if (!a) return NULL;

    // Se não houver mais nada à direita, este é o maior
    if (!a->dir) return a;

    // Caso contrário, continua procurando na subárvore direita
    return Maior(a->dir);
}

void ImpPre(TABB *a){
    if(a){
        printf("%d ",a->info);
        ImpPre(a->esq);
        ImpPre(a->dir);
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
    TABB *a8 = Cria(8, NULL, NULL);
    TABB *a7 = Cria(7, NULL, NULL);
    TABB *a6 = Cria(6, a7, a8);
    TABB *a5 = Cria(5, NULL, NULL);
    TABB *a4 = Cria(40, NULL, NULL);
    TABB *a3 = Cria(3, a4, a5);
    TABB *a2 = Cria(2, a3, a6);
    TABB *a1 = Cria(1, a2, a3);
    TABB *raiz = Cria(0, a1, NULL);

    TABB *raiz2 = reorganiza_para_ABB(raiz);

    TABB *maior_da_arvore = Maior(raiz2);

    
   // Testando a Original
    printf("Original (Pre-ordem): ");
    ImpPre(raiz);
    printf("\nReorg (Pre-ordem): ");
    ImpPre(raiz2);
    
    printf("\n\n------------------------------\n\n");

    // Testando a Copiada
    printf("Maior: %d", maior_da_arvore->info);

    return 0;
}