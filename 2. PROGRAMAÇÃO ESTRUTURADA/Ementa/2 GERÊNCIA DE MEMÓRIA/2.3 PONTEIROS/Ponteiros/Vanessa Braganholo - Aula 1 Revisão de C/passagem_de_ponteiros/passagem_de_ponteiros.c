#include <stdio.h>

void passagem_de_valor(int x){
/* 
C Usa passagem de parametros por valor

- Alteracoes nos valores dos parametros nao afetam as variaveis que foram usadas na chamada da funcao

*/
    x = 10;
}


void passagem_de_ponteiro(int *x){
/* 

C Usa passagem de parametros por valor

- Caso seja nescessario que as alterações sejam refletidas nas variaveis usadas na chamada, pode-se passar endereços das variaveis como parametro ao inves de variaveis comuns

- Nesse caso os parametros da funccao precisam ser ponteiros

*/
    *x = 5;
}


void troca (int *a, int *b){ // int *a (Significa que vai receber um ponteiro)
    int temp;

    temp = *a; //*pega o valor do ponteiro recebido
    *a = *b;
    *b = temp;

}

int passagem_valor_ponteiro (){
    printf("# Passagem de valor e ponteiro \n\n");

    int x = 10;
    passagem_de_valor(x);
    printf("%d\n",x);

    passagem_de_ponteiro(&x);
    printf("%d\n",x);

    int a, b;
    a = 20;
    b = 30;

    printf("a:%d\n",a);
    printf("b:%d\n",b);
    troca(&a, &b);
    printf("a:%d\n",a);
    printf("b:%d\n",b);

    printf("# ----------------- \n\n");





}