#include <stdio.h>
#include <stdlib.h>

/*

(b) Dada a seguinte representação de uma árvore binária:

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TAB;

Escreva as seguintes funções:

(Q7) se esta estrutura TAB tivesse um campo cor (int cor), defina uma função em C que, ao
receber uma árvore binária “sem cor” e totalmente balanceada (isto é, a distância da raiz a qualquer
folha da árvore é sempre a mesma), retorne esta árvore com os nós coloridos somente de vermelho e
preto, sendo que o nó pai NUNCA pode ter a mesma cor de seus filhos. A função deve possuir o
seguinte protótipo: void colore (TAB* arv);

*/

typedef struct ab {
    int info;
    int cor; // Campo adicionado conforme o enunciado
    struct ab *esq, *dir;
} TAB;

TAB* Cria(int info, TAB *sae, TAB *sad){
    TAB *novo = (TAB*)malloc(sizeof(TAB));

    novo->info = info;
    novo->esq = sae;
    novo->dir = sad;
    novo->cor = 0;

    return novo;
}

// Função auxiliar que realiza a coloração recursiva
void colore_aux(TAB* a, int cor_atual) {
    if (a == NULL) return;

    // Atribui a cor ao nó atual
    a->cor = cor_atual;

    // Chama para os filhos invertendo a cor (1 - cor_atual faz: 0->1 ou 1->0)
    colore_aux(a->esq, 1 - cor_atual);
    colore_aux(a->dir, 1 - cor_atual);
}

// Função principal solicitada no exercício
void Colore(TAB* arv) {
    if (arv == NULL) return;
    
    // Iniciamos a raiz com uma cor (ex: 0 para Preto)
    colore_aux(arv, 0);
}


void ImpPre(TAB *a){
    if(a){
        printf("%d : %d \n",a->info, a->cor);
        ImpPre(a->esq);
        ImpPre(a->dir);
    }
}


void ImpSim(TAB *a){
    if(a){
        ImpPre(a->esq);
        printf("%d : %d \n",a->info, a->cor);

        ImpPre(a->dir);
    }
}


void ImpPos(TAB *a){
    if(a){
        ImpPre(a->esq);
        ImpPre(a->dir);
        printf("%d : %d \n",a->info, a->cor);

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

    printf("Pre \n\n");

    ImpPre(raiz);
    printf("\n\n");

    printf("Sim \n\n");
    ImpSim(raiz);
    printf("\n\n");
    
    Colore(raiz);

    printf("\n\n");

    printf("Pre \n\n");
    ImpPre(raiz);

    printf("\n\n");
    printf("Sim \n\n");
    ImpSim(raiz);

    return 0;
}