#include <stdio.h>
#include <string.h>

/* ------------------------------------------------------------------ *
 * Q6) [URI 1318] Bilhetes numerados de 1 a N. Dado o pacote com M
 * bilhetes coletados, diga quantos numeros da sequencia aparecem
 * repetidos (tem "clone").
 *
 * Vetor de contadores cont[1..N]: conta quantas vezes cada numero
 * aparece no pacote e conta quantos indices tem contador > 1.
 * Varios casos de teste; termina quando N = M = 0.
 *
 *   Entrada          Saida
 *   5 5              1
 *   3 3 1 2 4        4
 *   6 10
 *   6 1 3 6 6 4 2 3 1 2
 *   0 0
 * ------------------------------------------------------------------ */

int main(void) {
    int n, m;

    while (scanf("%d %d", &n, &m) == 2 && (n != 0 || m != 0)) {
        int cont[10001];
        memset(cont, 0, sizeof(cont));

        for (int i = 0; i < m; i++) {
            int t;
            scanf("%d", &t);
            if (t >= 1 && t <= n)
                cont[t]++;
        }

        int clones = 0;
        for (int i = 1; i <= n; i++)
            if (cont[i] > 1)
                clones++;

        printf("%d\n", clones);
    }

    return 0;
}
