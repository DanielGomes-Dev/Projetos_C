#include <stdio.h>

/* ------------------------------------------------------------------ *
 * Q7) [URI 1533] Dada uma lista com N inteiros distintos (o quao
 * suspeita cada pessoa e), o assassino nao e o mais suspeito, e sim
 * o SEGUNDO mais suspeito. Imprima o indice (1-based) do assassino.
 *
 * Uma unica passada mantendo o indice do maior e do segundo maior
 * valor lidos ate o momento.
 * Varios casos de teste; termina quando N = 0.
 *
 *   Entrada        Saida
 *   3              1
 *   3 5 2          4
 *   5
 *   1 15 3 5 2
 *   0
 * ------------------------------------------------------------------ */

int main(void) {
    int n;

    while (scanf("%d", &n) == 1 && n != 0) {
        int idx_maior = 0, idx_segundo = 0;
        int val_maior = 0, val_segundo = 0;

        for (int i = 1; i <= n; i++) {
            int v;
            scanf("%d", &v);

            if (v > val_maior) {
                val_segundo = val_maior;
                idx_segundo = idx_maior;
                val_maior = v;
                idx_maior = i;
            } else if (v > val_segundo) {
                val_segundo = v;
                idx_segundo = i;
            }
        }

        printf("%d\n", idx_segundo);
    }

    return 0;
}
