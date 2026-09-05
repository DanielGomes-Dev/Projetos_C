#include <stdio.h>
#include <stdlib.h>
#include "../../TAVL/TAVL.h"

/* ------------------------------------------------------------------ *
 * Q1) Partindo de uma AVL que e uma folha com a informacao 50:
 *   (a) inserir {1, 64, 12, 18, 66, 38, 95, 58, 59, 70, 68, 39, 62,
 *       7, 60, 43, 16, 67, 34, 35} indicando as rotacoes;
 *   (b) retirar {50, 95, 70, 60, 35} explicitando as rotacoes.
 *
 * A propria TAVL_insere / TAVL_retira imprimem a rotacao aplicada:
 *   RSD = rotacao simples a direita     RSE = rotacao simples a esquerda
 *   RED = rotacao dupla esquerda-direita  RDE = rotacao dupla direita-esquerda
 * O numero entre parenteses e o no que era a raiz do sub-ramo
 * desbalanceado.
 * ------------------------------------------------------------------ */

int main(void) {
    int ins[] = {1, 64, 12, 18, 66, 38, 95, 58, 59, 70,
                 68, 39, 62, 7, 60, 43, 16, 67, 34, 35};
    int rem[] = {50, 95, 70, 60, 35};
    int qi = sizeof(ins) / sizeof(ins[0]);
    int qr = sizeof(rem) / sizeof(rem[0]);

    TAVL *t = TAVL_insere(50, NULL);         /* folha inicial */

    printf("=========== (a) INSERCOES ===========\n");
    for (int i = 0; i < qi; i++) {
        printf("\n--- insere %d ---\n", ins[i]);
        t = TAVL_insere(ins[i], t);
        TAVL_imprime(t);
    }

    printf("\n\n=========== (b) REMOCOES ===========\n");
    for (int i = 0; i < qr; i++) {
        printf("\n--- retira %d ---\n", rem[i]);
        t = TAVL_retira(rem[i], t);
        TAVL_imprime(t);
    }

    TAVL_libera(t);
    return 0;
}
