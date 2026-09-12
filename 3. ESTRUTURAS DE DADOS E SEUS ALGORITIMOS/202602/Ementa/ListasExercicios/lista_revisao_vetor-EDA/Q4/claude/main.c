#include <stdio.h>

/* ------------------------------------------------------------------ *
 * Q4) Infinitamente, teste se um numero e palindromo. Imprima
 * "VERDADEIRO" ou "FALSO". Para quando o numero for negativo.
 *
 * Inverte os digitos do numero (rev = rev*10 + digito) e compara com
 * o numero original.
 * ------------------------------------------------------------------ */

int main(void) {
    long long n;

    while (scanf("%lld", &n) == 1 && n >= 0) {
        long long rev = 0, x = n;
        while (x > 0) {
            rev = rev * 10 + x % 10;
            x /= 10;
        }
        printf("%s\n", (rev == n) ? "VERDADEIRO" : "FALSO");
    }

    return 0;
}
