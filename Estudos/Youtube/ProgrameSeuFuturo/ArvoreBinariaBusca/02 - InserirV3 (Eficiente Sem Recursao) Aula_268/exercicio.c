#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  
    int valor;
    struct no *direita;
    struct no *esquerda;

} NoArv;



NoArv* inserir_v3(NoArv **raiz, int num){ // **raiz -> ponteiro para ponteiro
    // Inserir de forma iterativa sem recursao e sem retorno
    NoArv *aux = *raiz;
    while (aux){
        if(num < aux->valor){
            raiz = &aux->esquerda;
        }
        else{
            raiz = &aux->direita;
        }
        aux = *raiz;
    }
    aux = malloc(sizeof(NoArv));
    aux->valor = num;
    aux->esquerda = NULL;
    aux->direita = NULL;
    *raiz = aux;

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
    // raiz = inserir_v3(raiz, 50);
    // raiz = inserir_v3(raiz, 25);
    // raiz = inserir_v3(raiz, 80);
    // raiz = inserir_v3(raiz, 30);

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
                inserir_v3(&raiz, num);
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

    printf("\nHello Arvore Binaria: Pre Order\n");
    imp_pre(raiz);

    
    return 0;
}