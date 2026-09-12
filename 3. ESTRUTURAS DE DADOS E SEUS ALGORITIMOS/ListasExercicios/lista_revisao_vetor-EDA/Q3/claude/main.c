#include <stdio.h>

/* ------------------------------------------------------------------ *
 * Q3) Um numero a e permutacao de b se os digitos de a formam uma
 * permutacao dos digitos de b (o digito 0 nao aparece).
 *   Ex.: 5412434 e permutacao de 4321445
 *        5412434 NAO e permutacao de 4312455
 *
 * Conta a frequencia de cada digito (1..9) nos dois numeros usando
 * dois vetores de contadores e compara os vetores.
 * ------------------------------------------------------------------ */

static void conta_digitos(long long x, int cont[10]) {
    if (x < 0)
        x = -x;
    do {
        cont[x % 10]++;
        x /= 10;
    } while (x > 0);
}

int main(void) {
    long long a, b;
    if (scanf("%lld %lld", &a, &b) != 2)
        return 0;

    int ca[10] = {0}, cb[10] = {0};
    conta_digitos(a, ca);
    conta_digitos(b, cb);

    int permutacao = 1;
    for (int d = 1; d <= 9; d++)
        if (ca[d] != cb[d])
            permutacao = 0;

    printf("%s\n", permutacao ? "a e permutacao de b"
                              : "a nao e permutacao de b");
    return 0;
}
