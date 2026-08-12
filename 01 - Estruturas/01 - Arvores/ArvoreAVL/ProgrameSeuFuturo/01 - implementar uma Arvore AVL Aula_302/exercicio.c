#include <stdio.h> // NULL
#include <stdlib.h> //malloc


typedef struct no {
    int valor;
    struct no *esquerdo, *direito;
    short altura;
}No;


No* novoNo(int valor){
    No *novo = malloc(sizeof(No));

    if(novo){
        novo->valor = valor;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;

    }
    else {
        printf("\nErro ao criar novo no.");
    }

    return novo;
}

short maior (short a, short b){
    return (a > b) ? a : b;
}

short alturaNo(No *no){
    if(no == NULL) return -1;
    else return no->altura;
}

short fatorDeBalanceamento(No *no){
    if(no){
        return alturaNo(no->esquerdo) - alturaNo(no->direito); 
    }
    else {
        return 0;
    }
}

int main(){
    printf("Hello AVL.");
    return 0;
}