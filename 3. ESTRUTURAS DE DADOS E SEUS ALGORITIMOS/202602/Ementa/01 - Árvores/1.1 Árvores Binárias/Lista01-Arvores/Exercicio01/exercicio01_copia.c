
#include <stdio.h>
#include <stdlib.h>

/*


(b) Dada a seguinte representação de uma árvore binária:

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TAB;

Escreva as seguintes funções:

(Q1) cópia de uma árvore: TAB* Copia (TAB *a);

*/



// sae -> subárvore da esquerda
// sad -> subárvore da direita*/

typedef struct AB{
    int info;
    struct AB *esq;
    struct AB *dir;
}TAB;

// Função auxiliar fornecida no material da UFF para facilitar a criação
TAB* Cria(int r, TAB *sae, TAB *sad) {
    TAB *novo = (TAB *)malloc(sizeof(TAB));
    novo->info = r;
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


// --- FUNÇÕES DE IMPRESSÃO (BASE UFF) ---



// Raiz -> Esquerda -> Direita
void ImpPre(TAB *a) {
    if (a != NULL) {
        printf("%d ", a->info);
        ImpPre(a->esq);
        ImpPre(a->dir);
    }
}

// Esquerda -> Raiz -> Direita (Simétrica)
void ImpSim(TAB *a) {
    if (a != NULL) {
        ImpSim(a->esq);
        printf("%d ", a->info);
        ImpSim(a->dir);
    }
}

// Esquerda -> Direita -> Raiz
void ImpPos(TAB *a) {
    if (a != NULL) {
        ImpPos(a->esq);
        ImpPos(a->dir);
        printf("%d ", a->info);
    }
}


int main (){
    printf("Hellow World!");

    TAB *a5 = Cria(5, NULL, NULL);
    TAB *a4 = Cria(4, NULL, NULL);
    TAB *a2 = Cria(2, NULL, NULL);
    TAB *a3 = Cria(3, a4, a5);
    TAB *raiz = Cria(1, a2, a3);

    TAB *arvore_Copiada = Copia(raiz);

   // Testando a Original
    printf("Original (Pre-ordem): ");
    ImpPre(raiz);
    printf("\nOriginal (Simetrica): ");
    ImpSim(raiz);
    
    printf("\n\n------------------------------\n\n");

    // Testando a Copiada
    printf("Copiada  (Pre-ordem): ");
    ImpPre(arvore_Copiada);
    printf("\nCopiada  (Simetrica): ");
    ImpSim(arvore_Copiada);
    printf("\n");

    return 0;
}