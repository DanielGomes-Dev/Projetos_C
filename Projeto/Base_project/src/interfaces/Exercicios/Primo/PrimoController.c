// #include "application/services/Lista/ListaService.h"
#include <stdio.h>

int verifyPrimo(int num) {

    if (num < 2)
        return 0;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

int get_entry(){
    int n;
    printf("Digite n: ");
    scanf("%d", &n);
    return n;
}

int generatePrimo() {
    while (1) {

        int n = get_entry();

        if (n <= 0) {
            printf("Programa encerrador.\n");
            break;
        }

        int contador = 0;
        int numero = 2;

        while (contador < n) {

            if (verifyPrimo(numero)) {
                printf("%d ", numero);
                contador++;
            }

            numero++;
        }

        printf("\n");
    }
}


// int verifyPrimo() {
//     return 0;
// }

// int get_entry(){
//     return 0;
// }

// int generatePrimo() {
//     int n;
//     printf("Digite n: ");
//     scanf("%d", &n);
//     while (n!=0){
//         printf("oi");
//         printf("\n");
//         printf("Digite n: ");
//         scanf("%d", &n);
//         int count = 0;
//         int numero = 2;
//         while (count < n){
//             if(num % i == 0){
//                 printf("%d ", numero);
//                 count++;
//             }
//         }
//     }
//     return n;
// }