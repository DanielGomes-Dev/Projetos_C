#include <stdio.h>
#include <stdlib.h>

/* ================================================================= *
 * LISTA 07 - Q2
 *
 * "Escreva o algoritmo de ordenacao POR INSERCAO em arquivos
 *  binarios."
 *
 *      void insertSort(char *nomeArq);
 *
 *  Igual a Q1: arquivo binario de int, ordenado in-place, usando
 *  apenas variaveis simples como memoria de trabalho.
 *
 * ----------------------------------------------------------------- *
 * INSERTION SORT RELEMBRANDO
 *   Mantem um prefixo v[0..i-1] ja ordenado. A cada passo pega
 *   chave = v[i] e "abre espaco" deslocando para a direita todos os
 *   elementos do prefixo que sao MAIORES que a chave, ate achar a
 *   posicao certa; entao grava a chave ali.
 *
 *       para i de 1 ate n-1:
 *          chave = v[i]
 *          j = i - 1
 *          enquanto j >= 0 e v[j] > chave:
 *              v[j+1] = v[j]     // desloca para a direita
 *              j = j - 1
 *          v[j+1] = chave
 *
 * VERSAO EM ARQUIVO BINARIO
 *   Cada v[k] esta no byte k * sizeof(int). Funcoes auxiliares
 *   deixam o codigo legivel:
 *       le(fp, k)        -> fseek + fread  : devolve v[k]
 *       grava(fp, k, x)  -> fseek + fwrite : escreve x em v[k]
 *   O arquivo e aberto em "rb+" (leitura e escrita). Entre um
 *   fread e um fwrite (ou vice-versa) sempre ha um fseek, como
 *   exige a biblioteca padrao.
 *
 * PASSO A PASSO de insertSort:
 *   1. abre nomeArq em "rb+";
 *   2. n = (tamanho do arquivo) / sizeof(int);
 *   3. for i de 1 a n-1:
 *        chave = le(i);
 *        j = i - 1;
 *        while (j >= 0 && le(j) > chave):
 *             grava(j+1, le(j));   // desloca
 *             j--;
 *        grava(j+1, chave);
 *   4. fecha o arquivo.
 *
 * CUSTO: O(n^2) acessos a disco no pior caso; O(n) no melhor
 *        (arquivo quase ordenado); memoria O(1).
 * ================================================================= */

static int le(FILE *fp, long k) {
    int x;
    fseek(fp, k * (long)sizeof(int), SEEK_SET);
    fread(&x, sizeof(int), 1, fp);
    return x;
}

static void grava(FILE *fp, long k, int x) {
    fseek(fp, k * (long)sizeof(int), SEEK_SET);
    fwrite(&x, sizeof(int), 1, fp);
}

void insertSort(char *nomeArq) {
    FILE *fp = fopen(nomeArq, "rb+");
    if (!fp) {
        printf("insertSort: nao consegui abrir '%s'.\n", nomeArq);
        return;
    }

    fseek(fp, 0, SEEK_END);
    long n = ftell(fp) / (long)sizeof(int);

    for (long i = 1; i < n; i++) {
        int chave = le(fp, i);
        long j = i - 1;

        while (j >= 0 && le(fp, j) > chave) {
            grava(fp, j + 1, le(fp, j));   /* desloca v[j] p/ direita */
            j--;
        }
        grava(fp, j + 1, chave);           /* insere a chave no lugar */
    }

    fclose(fp);
}

/* ---- utilitarios de teste ------------------------------------- */

static void cria_bin(const char *nome, const int *v, int n) {
    FILE *fp = fopen(nome, "wb");
    fwrite(v, sizeof(int), n, fp);
    fclose(fp);
}

static void mostra_bin(const char *nome) {
    FILE *fp = fopen(nome, "rb");
    if (!fp) { printf("(nao abriu %s)\n", nome); return; }
    int x;
    while (fread(&x, sizeof(int), 1, fp) == 1)
        printf("%d ", x);
    printf("\n");
    fclose(fp);
}

int main(void) {
    int v[] = {29, 10, 14, 37, 13, 1, 8, 25, 3};
    int n = (int)(sizeof(v) / sizeof(v[0]));

    cria_bin("dados_q2.bin", v, n);

    printf("antes : ");
    mostra_bin("dados_q2.bin");

    insertSort("dados_q2.bin");

    printf("depois: ");
    mostra_bin("dados_q2.bin");
    printf("(esperado: 1 3 8 10 13 14 25 29 37)\n");

    return 0;
}
