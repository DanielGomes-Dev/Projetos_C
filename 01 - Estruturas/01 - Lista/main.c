#include <stdlib.h> 
// NULL


#include <stdio.h>

typedef struct lista {
    int info; // tipo info inteiro
    struct lista* prox; // ponteiro pro proximo

} TLSE; // Tipo Lista Simplemente Encadeada

// typedef struct lista TLSE // outra forma de tipar

TLSE* cria_lista (void){
    return NULL;
}

TLSE* insere_inicio(int el, TLSE *l){
    TLSE *novo = (TLSE*)(malloc(sizeof(TLSE)));
    novo->info = el;
    novo->prox = l;
    return novo;    
}

TLSE* insere_fim(int el, TLSE *l){
    TLSE *lista_nova;

    // 1º Jeito
    // lista_nova = cria_lista();
    // lista_nova = insere_inicio(el, lista_nova);
    
    // 2º Jeito
    // lista_nova = insere_inicio(el, NULL);

    // 3º Jeito
    lista_nova = (TLSE*)(malloc(sizeof(TLSE)));
    lista_nova->info = el;
    lista_nova->prox = NULL;


    TLSE *p = l;
    TLSE *ant = l;

    
    while(p != NULL){
        ant = p;
        p = p->prox;
    }

    if(ant != NULL)
        ant->prox = lista_nova;
    else
        l = lista_nova;


    return l;
}

TLSE* inserir_ordenada(){
    // Continuar aqui
}
TLSE* insere_fim_recursiva(){
    // Continuar aqui

}

TLSE* inserir_ordenada_recursiva(){
    // Continuar aqui
}

void imprime_lista(TLSE *l){

    TLSE *p; //cuidado ao percorrer uma lista 
    for (p = l; p != NULL; p= p->prox)
        printf("Info = %d\n", p->info);

}



// int main (){
//     TLSE *lista = cria_lista();
//     lista = insere_inicio(1, lista);
//     lista = insere_inicio(2, lista);
//     lista = insere_inicio(3, lista);

//     lista = insere_fim(4, lista);



//     // printf(lista);
//     // printf("Endereco da lista: %p\n", lista);
//     // printf("Valor do elemento: %d\n", lista->info);

//     imprime_lista(lista);

//     return 0;
// }

 
int main() {
 
    printf("Hello World!");
 
    return 0;
}