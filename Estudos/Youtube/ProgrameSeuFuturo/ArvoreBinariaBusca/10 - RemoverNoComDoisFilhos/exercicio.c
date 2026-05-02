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

NoArv* remover_no_folha (NoArv *raiz, int chave){ 
    if(raiz == NULL){
        printf("\nValor nao encontrado.\n");
        return NULL;
    } else {
        if(raiz->valor == chave){

            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                printf("\nNo '%d' Removido Com Sucesso\n", chave);
                return NULL;
            }else{

                // No com Filhos
            }

        }
        else{
            if(chave < raiz->valor){
                raiz->esquerda = remover_no_folha(raiz->esquerda, chave);
            }else {
                raiz->direita = remover_no_folha(raiz->direita, chave);
            }
            return raiz;
        }
    }
}

NoArv* remover_no_um_filho (NoArv *raiz, int chave){
    if(raiz == NULL) return NULL;
    else{
        if(raiz->valor == chave){

            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                printf("\nNo Folha Removido Com Sucesso.\n");
                return NULL;
            }
            else{
                if(raiz->esquerda != NULL && raiz->direita != NULL){
                    // Remover com 2 Filhos
                }
                else {
                    if(raiz->esquerda == NULL){
                        NoArv *aux = raiz->direita;
                        free(raiz);
                        printf("\nNo Com Um Filho a Direita Removido Com Sucesso.\n");
                        return aux;
                    }
                    else if(raiz->direita == NULL){
                        NoArv *aux = raiz->esquerda;
                        printf("\nNo Com Um Filho a esquerda Removido Com Sucesso.\n");
                        free(raiz);
                        return aux;
                    }
                }
            }

        }else{
            raiz->esquerda = remover_no_um_filho(raiz->esquerda, chave);
            raiz->direita = remover_no_um_filho(raiz->direita, chave);
        }

        return raiz;
    }
}

NoArv* remover_qualquer_no(NoArv *raiz, int chave){
    if(raiz == NULL) return NULL;
    else {
        if(raiz->valor == chave){
            if(raiz->direita == NULL && raiz->esquerda == NULL){
                free(raiz);
                printf("\nNo Folha Removido com Sucesso\n");
                return NULL;
            }
            else {
                if(raiz->direita != NULL && raiz->esquerda != NULL){
                     // Remover Nó com Dois Filhos
                    NoArv *aux = raiz->esquerda; //Busca pela esquer, mas poderia ir pela direita
                    while (aux->direita != NULL) // Caso decida escolher a esquer ir totalmente para direita;
                    {
                        aux = aux->direita;
                    }

                    raiz->valor = aux->valor;
                    printf("Aux: valor", aux->valor);
                    aux->valor = chave; // Troca de valores
                    printf("Aux valor: %d", aux->valor);
                    raiz->esquerda = remover_qualquer_no(raiz->esquerda, chave); //Apos fazer a troca dos no, percorrer a arvore escolhida para remover o no substituido
                    return raiz;
                }
                else {
                    if(raiz->direita != NULL){
                        NoArv *aux = raiz->direita;
                        free(raiz);
                        printf("\nNo Com Um Filho a Direita Removido com Sucesso\n");
                        return aux;
                    }
                    else if(raiz->esquerda!=NULL){
                        NoArv *aux = raiz->esquerda;
                        free(raiz);
                        printf("\nNo Com Um Filho a Esquerda Removido com Sucesso\n");
                        return aux;
                    }

                }
            }

        }
        else {
            raiz->esquerda = remover_qualquer_no(raiz->esquerda, chave);
            raiz->direita = remover_qualquer_no(raiz->direita, chave);
        }
        return raiz;
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
    raiz = inserir_v1(raiz, 50);
    raiz = inserir_v1(raiz, 25);
    raiz = inserir_v1(raiz, 80);
    raiz = inserir_v1(raiz, 30);

    int opcao, num;

    do {

        printf("\n\nDigite: \n1: Para inserir elementos na arvore.\n2: Para imprimir a arvore.\n3: Remover Qualquer No.\n0: Para sair.\n\n");
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
                printf("\n\nRemover Qualquer No: \n\n");
                scanf("%d", &num);
                raiz = remover_qualquer_no(raiz, num);
                imp_sim(raiz);

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