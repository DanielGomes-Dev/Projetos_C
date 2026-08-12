#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  
    int valor;
    struct no *direita;
    struct no *esquerda;

} NoArv;



NoArv* inserir_v2(NoArv **raiz, int num){ // **raiz -> ponteiro para ponteiro

    if(*raiz == NULL){
        *raiz = (NoArv*)malloc(sizeof(NoArv));
        (*raiz)->valor = num;  
        (*raiz)->esquerda = NULL;
        (*raiz)->direita = NULL;

    }
    else{

        if(num < (*raiz)->valor){
            inserir_v2(&((*raiz)->esquerda), num);
        }
        else {
            inserir_v2(&((*raiz)->direita), num);
        }


    }
}

void imp_pre(NoArv *a){

    if(a){
        printf("%d ", a->valor);
        imp_pre(a->esquerda);
        imp_pre(a->direita);
    }

}

void imp_sim(NoArv *a){

    if(a){
        imp_sim(a->esquerda);
        printf("%d ", a->valor);
        imp_sim(a->direita);
    }

}



int main (){
    
    NoArv *raiz = NULL;
    // raiz = inserir_v2(raiz, 50);
    // raiz = inserir_v2(raiz, 25);
    // raiz = inserir_v2(raiz, 80);
    // raiz = inserir_v2(raiz, 30);

    int opcao;

    do {

        printf("\n\nDigite: \n1: Para inserir elementos na arvore.\n2: Para imprimir a arvore.\n0: Para sair.\n\n");
        scanf("%d", &opcao);
        switch(opcao){
            case(1):
                printf("\nDigite o numero que deseja inserir: ");
                int num;
                scanf("%d", &num);
                printf("\n\nInserindo: %d\n\n", num);
                inserir_v2(&raiz, num);
                break;
            case(2):
                printf("\n\nImprimindo Arvore pre-order\n\n");
                imp_pre(raiz);
                printf("\n\nImprimindo Arvore simetrica\n\n");
                imp_sim(raiz);
                break;
            default:
                if(opcao!=0){
                    printf("Valor Invalido2");
                }
                break;
            
        }

    } while (opcao!=0);



    printf("\nHello Arvore Binaria: Simetrica\n");
    imp_sim(raiz);

    printf("Hello Arvore Binaria: Pre Order\n");
    imp_pre(raiz);

    
    return 0;
}