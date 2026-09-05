#include <stdio.h>
#include <stdlib.h>


void ponteiro_inteiro(){

    int *valor1, valor2 = 50;
    valor1 = &valor2;

    printf("Conteudo da variavel valor2: %d\n", valor2);
    printf("Endereço da variavel valor2: %p\n", &valor2);
    printf("Conteudo da variavel valor1: %p\n", valor1);
    printf("Conteudo apontado pela variavel valor1: %d\n", *valor1);
}


void ponteiro_char(){

    char *letra1, letra2 = 'a';
    letra1 = &letra2;

    printf("Conteudo da variavel letra2: %c\n", letra2);
    printf("Endereço da variavel letra2: %p\n", &letra2);
    printf("Conteudo da variavel letra1: %p\n", letra1);
    printf("Conteudo apontado pela variavel letra1: %c\n", *letra1);
}


int main(){

    // ponteiro_inteiro();
    ponteiro_char();

    return 0;
}