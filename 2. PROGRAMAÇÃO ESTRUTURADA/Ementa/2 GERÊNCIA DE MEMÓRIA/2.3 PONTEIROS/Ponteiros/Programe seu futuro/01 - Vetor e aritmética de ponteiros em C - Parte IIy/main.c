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

// void imprimirVetor(int v[]){

// }

void imprimirVetor(int *v, int tam){
    int i;
    for (i = 0; i < tam; i++)
    {
        printf("%d ", *(v + i));
    }
    
}

void imprimirVetorLetras(char *v, int tam){
    int i;
    for (i = 0; i < tam; i++)
    {
        printf("%c ", *(v + i));
    }
    
}

void preencherVetorInt(int *v, int tam){
    int i;
    for (i = 0; i < tam; i++)
    {
        printf("Digite um valor qualquer: ");

        // scanf("%d", &v[i]);
        scanf("%d", v + i);

    }
    
}


void ponteiro_vetor(){
    int i, vet[10] = {1,2,3,4,5,6,7,8,9,11};

    char letras[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    printf("%p %p\n", vet, &vet[0]);

    printf("%d %d\n", *vet, vet[0]);
    printf("---\n");

    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", vet[i]);
        printf("%d\n", *(vet + i)); // Aritimetica de ponteiros
        // printf("%d\n", *vet + i); // Nao funciona (aqui soma o valor da primeira mais o valor da variavel i)
        printf("---\n");

    }

    preencherVetorInt(vet, 10);
    imprimirVetor(vet, 10);
    printf("\n---\n");
    imprimirVetorLetras(letras, 10);
    printf("\n---\n");

    // Passagem de valor
    // Passagem por referencia
    

}


int main(){

    // ponteiro_inteiro();
    // ponteiro_char();
    ponteiro_vetor();

    return 0;
}