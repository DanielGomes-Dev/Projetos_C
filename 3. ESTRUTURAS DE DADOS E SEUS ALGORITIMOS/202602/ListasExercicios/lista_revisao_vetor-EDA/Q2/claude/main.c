#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------------------ *
 * Q2) Integre e derive polinomios. O polinomio e um vetor v de
 * coeficientes onde v[i] e o coeficiente de x^i.
 *   Ex.: 3x^2 + 2x + 12  ->  v = {12, 2, 3}
 *        integral        ->  I = {0, 12, 1, 1}   (0 + 12x + x^2 + x^3)
 *        derivada        ->  D = {2, 6}          (6x + 2)
 *
 * Integral: I[0] = 0 e I[i+1] = v[i] / (i+1).
 * Derivada: D[i-1] = v[i] * i.
 * Repete infinitamente; para quando o grau g for <= 0.
 * ------------------------------------------------------------------ */

static void imprime_polinomio(const char *nome, const long *v, int tam) {
    printf("%s = {", nome);
    for (int i = 0; i < tam; i++)
        printf("%ld%s", v[i], (i + 1 < tam) ? ", " : "");
    printf("}\n");
}

int main(void) {
    int g;

    while (scanf("%d", &g) == 1 && g > 0) {
        long *v = malloc((size_t) (g + 1) * sizeof(long));
        for (int i = 0; i <= g; i++)
            scanf("%ld", &v[i]);

        long *integral = malloc((size_t) (g + 2) * sizeof(long));
        integral[0] = 0;
        for (int i = 0; i <= g; i++)
            integral[i + 1] = v[i] / (i + 1);

        long *derivada = malloc((size_t) g * sizeof(long));
        for (int i = 1; i <= g; i++)
            derivada[i - 1] = v[i] * i;

        imprime_polinomio("I", integral, g + 2);
        imprime_polinomio("D", derivada, g);

        free(v);
        free(integral);
        free(derivada);
    }

    return 0;
}
