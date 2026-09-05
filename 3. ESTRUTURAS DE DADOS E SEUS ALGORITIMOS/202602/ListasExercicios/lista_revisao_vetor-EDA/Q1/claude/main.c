#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------------------ *
 * Q1) Implemente a Peneira de Eratosthenes. Leia o valor n e mostre
 * todos os numeros primos encontrados ate n.
 *
 * Usa um vetor "composto" de tamanho n+1. Para cada i a partir de 2
 * ainda nao marcado, risca (marca) todos os multiplos de i a partir
 * de i*i. Ao final, os indices nao marcados sao os primos.
 * ------------------------------------------------------------------ */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 2) {
        printf("\n");
        return 0;
    }

    char *composto = calloc((size_t) n + 1, sizeof(char));

    for (int i = 2; (long) i * i <= n; i++)
        if (!composto[i])
            for (int j = i * i; j <= n; j += i)
                composto[j] = 1;

    for (int i = 2; i <= n; i++)
        if (!composto[i])
            printf("%d ", i);
    printf("\n");

    free(composto);
    return 0;
}
