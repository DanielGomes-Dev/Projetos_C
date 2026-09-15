#include <stdio.h>
#include <stdlib.h>
#include "../../TAB/TAB.h"

/* ------------------------------------------------------------------ *
 * Q2) Calcule a media simples dos elementos de cada nivel de uma
 * arvore binaria simples.
 *     Prototipo: float *media(TAB *a, int *tam_vet).
 *
 * RACIOCINIO
 *   1. A quantidade de niveis e (altura + 1). TAB_altura ja existe
 *      pronta em TAB.h/TAB.c (convencao: arvore vazia tem altura -1),
 *      entao reaproveito ela em vez de calcular profundidade de novo.
 *   2. Aloco dois vetores auxiliares do tamanho "quantidade de
 *      niveis": soma[] e cont[] (quantos elementos entraram em cada
 *      nivel), ambos comecando zerados.
 *   3. Percorro a arvore (nivel como parametro, igual Q1) acumulando
 *      soma[nivel] += info e cont[nivel]++.
 *   4. Depois de percorrer tudo, media[i] = soma[i] / cont[i].
 *
 * CUSTO: O(n) para percorrer + O(niveis) para montar a media; memoria
 * extra O(niveis).
 * ------------------------------------------------------------------ */

static void acumula(TAB *a, int nivel, float *soma, int *cont) {
    if (!a) return;
    soma[nivel] += a->info;
    cont[nivel]++;
    acumula(a->esq, nivel + 1, soma, cont);
    acumula(a->dir, nivel + 1, soma, cont);
}

float *media(TAB *a, int *tam_vet) {
    int alt = TAB_altura(a);
    if (alt < 0) {                 /* arvore vazia */
        *tam_vet = 0;
        return NULL;
    }

    int n = alt + 1;               /* quantidade de niveis */
    float *soma = (float *) calloc(n, sizeof(float));
    int   *cont = (int   *) calloc(n, sizeof(int));
    acumula(a, 0, soma, cont);

    float *med = (float *) malloc(n * sizeof(float));
    for (int i = 0; i < n; i++)
        med[i] = soma[i] / cont[i];

    free(soma);
    free(cont);
    *tam_vet = n;
    return med;
}

/* ---- mesma arvore de exemplo da Q1 --------------------------------
 *   nivel 0: 130               -> media 130.0
 *   nivel 1: 100, 200          -> media 150.0
 *   nivel 2: 83,120,150,230    -> media 145.75
 * ------------------------------------------------------------------ */
static TAB *exemplo(void) {
    TAB *esq = TAB_cria(100, TAB_cria(83, NULL, NULL), TAB_cria(120, NULL, NULL));
    TAB *dir = TAB_cria(200, TAB_cria(150, NULL, NULL), TAB_cria(230, NULL, NULL));
    return TAB_cria(130, esq, dir);
}

int main(void) {
    TAB *a = exemplo();
    int tam;
    float *med = media(a, &tam);

    printf("Quantidade de niveis: %d  (esperado: 3)\n", tam);
    for (int i = 0; i < tam; i++)
        printf("media[nivel %d] = %.2f\n", i, med[i]);
    printf("(esperado: 130.00 / 150.00 / 145.75)\n");

    free(med);
    TAB_libera(a);
    return 0;
}
