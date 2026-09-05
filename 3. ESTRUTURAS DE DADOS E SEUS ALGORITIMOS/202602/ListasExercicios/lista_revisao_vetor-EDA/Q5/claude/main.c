#include <stdio.h>

/* ------------------------------------------------------------------ *
 * Q5) Infinitamente, receba um numero n e retorne a representacao
 * binaria de n. Ex.: n = 12  ->  "1100". Para quando n < 0.
 *
 * Guarda os restos das divisoes sucessivas por 2 num vetor de bits e
 * imprime na ordem inversa.
 * ------------------------------------------------------------------ */

int main(void) {
    int n;

    while (scanf("%d", &n) == 1 && n >= 0) {
        char bits[32];
        int k = 0;

        if (n == 0)
            bits[k++] = '0';
        while (n > 0) {
            bits[k++] = (char) ('0' + (n & 1));
            n >>= 1;
        }

        for (int i = k - 1; i >= 0; i--)
            putchar(bits[i]);
        putchar('\n');
    }

    return 0;
}
