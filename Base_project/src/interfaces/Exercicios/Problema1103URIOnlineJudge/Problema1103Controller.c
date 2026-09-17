#include <stdio.h>
#include "Problema1103Controller.h"

int calcularMinutos(int H1, int M1, int H2, int M2) {

    int inicio = H1 * 60 + M1;
    int alarme = H2 * 60 + M2;

    if (alarme >= inicio)
        return alarme - inicio;

    return (1440 - inicio) + alarme;
}

int executarProblema1103() {

    int H1, M1, H2, M2;

    while (1) {

        if (scanf("%d %d %d %d", &H1, &M1, &H2, &M2) != 4)
            break;

        if (H1 == 0 && M1 == 0 && H2 == 0 && M2 == 0)
            break;

        int minutos = calcularMinutos(H1, M1, H2, M2);

        printf("%d\n", minutos);
    }

    return 0;
}