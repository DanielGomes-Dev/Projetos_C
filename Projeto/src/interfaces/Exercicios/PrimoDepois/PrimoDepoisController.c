#include <stdio.h>

int verifyPrimoDepois(int num) {

    if (num < 2)
        return 0;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

int get_entryDepois(){
    int n;
    printf("Digite n: ");
    scanf("%d", &n);
    return n;
}

int generatePrimoDepois() {

    while (1) {

        int n = get_entry();

        if (n <= 0) {
            printf("Programa encerrado.\n");
            break;
        }

        int contador = 0;
        int numero = n + 1;   // começa depois de n

        printf("Primos: ");

        while (contador < n) {

            if (verifyPrimo(numero)) {
                printf("%d ", numero);
                contador++;
            }

            numero++;
        }

        printf("\n");
    }

    return 0;
}