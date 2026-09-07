#include <stdio.h>

passagem_de_parametro_vetor(int *vetor){
    //Continuar Aqui 13:45
}

void media (){
    int tam_vetor = 4;
    float v[tam_vetor];
    float media = 0.0;
    int i;
    // Leitura dos Dados
    for(i=0; i<tam_vetor; i++){
        scanf("%f", &v[i]);
    }

    for(i=0; i<tam_vetor; i++){
        media = media + v[i];
    }

    media = media/tam_vetor;

    printf("Media = %.2f \n", media);

}



int vetores(){
/* 

Vetores são ponteiros

- Ventor v de 10 elementos inteiros
- Espaço de memoria de v=10 x valores inteiros de 4 bytes = 40 bytes

- Alocação estatica (Espaço de memoria é reservado no momento da da declaração do vetor)

- Nome do vetor é um ponteiro que aponta para o endereço inicial do vetor
    - Rosseti tinha falado q existeum tipo de vetor q nao tem essa alocação inicial

*/

/*

C Permite aritmética de ponteiros

Ex:

V + 0: primeiro elemento de v;
V + 1: segundo elemento de v;
....
V + 9: ultimo elemento de v;

Elementos do Vetor podem ser acessados usando colchetes v[0];


*/
    printf("# Vetores\n\n");

    media();

    return 0;

    printf("# -----------------\n\n");

}

