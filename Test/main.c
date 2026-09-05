
#include <stdio.h>

#define MAX 100

/* insere v na posição pos, deslocando os elementos seguintes uma casa à direita */
int insere(int vet[], int *n, int pos, int v) {
    printf("%d", *n);
    
    if (*n >= MAX || pos < 0 || pos > *n)
        return 0;   /* falha: sem espaço ou posição inválida */

    for (int i = *n; i > pos; i--)
        vet[i] = vet[i - 1];   /* desloca à direita, de trás para frente */

    vet[pos] = v;
    (*n)++;
    return 1;
}

/* remove o elemento da posição pos, deslocando os seguintes uma casa à esquerda */
int remove_pos(int vet[], int *n, int pos) {
    if (pos < 0 || pos >= *n)
        return 0;

    for (int i = pos; i < *n - 1; i++)
        vet[i] = vet[i + 1];   /* desloca à esquerda */

    (*n)--;
    return 1;
}

int main(void) {
    int vet[MAX] = {10, 20, 30, 40};
    int n = 4;

    insere(vet, &n, 2, 99);         /* 10 20 99 30 40 */
    // for (int i = 0; i < n; i++) printf("%d ", vet[i]);
    // printf("\n");

    // remove_pos(vet, &n, 0);         /* 20 99 30 40 */
    // for (int i = 0; i < n; i++) printf("%d ", vet[i]);
    // printf("\n");

    // return 0;
}