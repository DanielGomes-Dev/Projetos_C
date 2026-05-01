#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  
    int valor;
    struct no *direita;
    struct no *esquerda;

} NoArv;



NoArv* inserir_v1(NoArv *raiz, int num){

    if(raiz == NULL){
        NoArv *aux = (NoArv*)malloc(sizeof(NoArv));
        aux->esquerda = NULL;
        aux->direita = NULL;
        aux->valor = num;  

        return aux;

    }
    else{

        if(num < raiz->valor){
            raiz->esquerda = inserir_v1(raiz->esquerda, num);
        }
        else {
            raiz->direita = inserir_v1(raiz->direita, num);
        }

        return raiz;

    }
}

NoArv* buscar_versao_2(NoArv *raiz, int num){ // Não recursiva
    while(raiz){
        if(num < raiz->valor){
            raiz = raiz->esquerda;
        }
        else if(num > raiz->valor){
            raiz = raiz->direita;
        }
        else {
            return raiz;
        }
    }
    return NULL;

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
    NoArv *busca;

    raiz = inserir_v1(raiz, 50);
    raiz = inserir_v1(raiz, 25);
    raiz = inserir_v1(raiz, 80);
    raiz = inserir_v1(raiz, 30);

    int opcao, num;

    do {

        printf("\n\nDigite: \n1: Para inserir elementos na arvore.\n2: Para imprimir a arvore.\n3: Para buscar a arvore.\n0: Para sair.\n\n");
        scanf("%d", &opcao);
        switch(opcao){
            case(1):
                printf("\nDigite o numero que deseja inserir: ");
                scanf("%d", &num);
                printf("\n\nInserindo: %d\n\n", num);
                raiz = inserir_v1(raiz, num);
                break;
            case(2):
                printf("\n\nImprimindo Arvore pre-order\n\n");
                imp_pre(raiz);
                printf("\n\nImprimindo Arvore simetrica\n\n");
                imp_sim(raiz);
                break;
            case(3):
                printf("\nDigite o numero que deseja buscar: ");
                scanf("%d", &num);
                busca = buscar_versao_2(raiz, num);
                if(busca){
                    printf("\nValor encontrado: %d\n", busca->valor);
                }
                else{
                    printf("\nValor Nao encontrado.\n");
                }
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

    printf("\nHello Arvore Binaria: Busca Num\n");

    
    return 0;
}