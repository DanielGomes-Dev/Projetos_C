#include <stdio.h>
#include <stdlib.h>
#include "../../TAVL/TAVL.h"

/* ------------------------------------------------------------------ *
 * Q2) Partindo da AVL dada:
 *
 *                       61
 *              34                 78
 *          19      47         64      87
 *        15   29  42  53        76      84
 *       13 17  32
 *
 *   (a) inserir {1, 65, 12, 18, 66, 38, 95, 58, 59, 70, 68, 39, 62,
 *       60, 43, 16, 67, 36, 35} indicando as rotacoes;
 *   (b) retirar {35, 34, 67, 16, 42, 60, 62, 39, 68, 70, 59, 58, 95,
 *       38, 66, 18, 12, 64, 1} explicitando as rotacoes.
 *
 * A arvore inicial e montada inserindo seus nos em ordem de nivel
 * (BFS): como ela ja e uma AVL valida, essa ordem reconstroi
 * exatamente a mesma forma, sem disparar rotacoes.
 *
 * TAVL_insere / TAVL_retira imprimem a rotacao aplicada:
 *   RSD / RSE = rotacao simples direita / esquerda
 *   RED / RDE = rotacao dupla esquerda-direita / direita-esquerda
 * ------------------------------------------------------------------ */

int main(void) {
    int base[] = {61, 34, 78, 19, 47, 64, 87,
                  15, 29, 42, 53, 76, 84, 13, 17, 32};
    int ins[]  = {1, 65, 12, 18, 66, 38, 95, 58, 59, 70,
                  68, 39, 62, 60, 43, 16, 67, 36, 35};
    int rem[]  = {35, 34, 67, 16, 42, 60, 62, 39, 68, 70,
                  59, 58, 95, 38, 66, 18, 12, 64, 1};
    int qb = sizeof(base) / sizeof(base[0]);
    int qi = sizeof(ins)  / sizeof(ins[0]);
    int qr = sizeof(rem)  / sizeof(rem[0]);

    TAVL *t = NULL;
    for (int i = 0; i < qb; i++)
        t = TAVL_insere(base[i], t);

    printf("=========== ARVORE INICIAL ===========\n");
    TAVL_imprime(t);

    printf("\n\n=========== (a) INSERCOES ===========\n");
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
