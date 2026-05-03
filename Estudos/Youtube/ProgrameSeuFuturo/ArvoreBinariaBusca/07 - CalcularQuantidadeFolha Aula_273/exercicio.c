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

void imp_pre(NoArv *a){

    if(a){
        printf("%d ", a->valor);
        imp_pre(a->esquerda);
        imp_pre(a->direita);
    }

}

int calcula_quantidade_folha (NoArv *raiz){ //A Altura é a maior distancia entre a raiz e um nó folha
    if(raiz == NULL) return 0;
    if(raiz->direita == NULL && raiz->esquerda==NULL) return 1;
    
    return calcula_quantidade_folha(raiz->esquerda) + calcula_quantidade_folha(raiz->direita);
}

int calcula_quantidade_folha_ternario (NoArv *raiz){ //A Altura é a maior distancia entre a raiz e um nó folha
    return raiz == NULL ? 0 : (raiz->direita == NULL && raiz->esquerda==NULL) ? 1 : calcula_quantidade_folha(raiz->esquerda) + calcula_quantidade_folha(raiz->direita);
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
    raiz = inserir_v1(raiz, 50);
    raiz = inserir_v1(raiz, 25);
    raiz = inserir_v1(raiz, 80);
    raiz = inserir_v1(raiz, 30);

    int opcao;

    do {

        printf("\n\nDigite: \n1: Para inserir elementos na arvore.\n2: Para imprimir a arvore.\n3: Para calcular Quantidade de folha.\n0: Para sair.\n\n");
        scanf("%d", &opcao);
        switch(opcao){
            case(1):
                printf("\nDigite o numero que deseja inserir: ");
                int num;
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
                printf("\n\nCalculando Quantidade de Folhas: \n\n");
                int quantidade_folha = calcula_quantidade_folha_ternario(raiz);
                printf("\n\nQuantidade de folha: %d \n\n", quantidade_folha);
                break;
            default:
                if(opcao!=0){
                    printf("\nValor Invalido\n");
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