#include <stdio.h>
#include <stdlib.h>

/* ================================================================= *
 * LISTA 07 - Q1
 *
 * "Escreva o algoritmo de ordenacao POR BOLHA em arquivos binarios."
 *
 *      void BolhaBin(char *nomeArq);
 *
 *  O arquivo binario contem uma sequencia de int (4 bytes cada) e
 *  deve ser ordenado NO PROPRIO ARQUIVO (in-place, em memoria
 *  secundaria): a "memoria" usada sao apenas algumas variaveis int.
 *
 * ----------------------------------------------------------------- *
 * BOLHA (bubble sort) RELEMBRANDO
 *   A cada passada percorre o vetor comparando pares vizinhos
 *   (v[j], v[j+1]); se estiverem fora de ordem, troca. A cada
 *   passada o maior elemento restante "borbulha" ate o fim, entao
 *   a passada seguinte pode parar 1 posicao antes. Se uma passada
 *   inteira nao faz nenhuma troca, o arquivo ja esta ordenado.
 *
 * COMO ACESSAR A "POSICAO j" NUM ARQUIVO BINARIO
 *   O elemento de indice j comeca no byte  j * sizeof(int).
 *     fseek(fp, (long)j * sizeof(int), SEEK_SET);  // posiciona
 *     fread (&x, sizeof(int), 1, fp);              // le v[j]
 *   Depois de ler v[j], o cursor ja esta em v[j+1], entao um
 *   segundo fread le v[j+1] sem novo fseek.
 *   Para gravar a troca: fseek de volta para j e fwrite de v[j+1]
 *   seguido de v[j].
 *   IMPORTANTE: abrir o arquivo em "rb+" (leitura E escrita), e
 *   chamar fseek entre um fread e um fwrite (exigencia da stdio).
 *
 * PASSO A PASSO de BolhaBin:
 *   1. abre nomeArq em "rb+";
 *   2. descobre n = (tamanho do arquivo) / sizeof(int);
 *   3. for i de 0 a n-2:
 *        trocou = 0;
 *        for j de 0 a n-2-i:
 *           le a = v[j], b = v[j+1];
 *           se a > b: grava b em j e a em j+1; trocou = 1;
 *        se trocou == 0: encerra (ja ordenado);
 *   4. fecha o arquivo.
 *
 * CUSTO: O(n^2) comparacoes/acessos a disco; memoria O(1).
 * ================================================================= */

void BolhaBin(char *nomeArq) {
    FILE *fp = fopen(nomeArq, "rb+");
    if (!fp) {
        printf("BolhaBin: nao consegui abrir '%s'.\n", nomeArq);
        return;
    }

    /* numero de inteiros no arquivo */
    fseek(fp, 0, SEEK_END);
    long n = ftell(fp) / (long)sizeof(int);

    for (long i = 0; i < n - 1; i++) {
        int trocou = 0;

        for (long j = 0; j < n - 1 - i; j++) {
            int a, b;
            fseek(fp, j * (long)sizeof(int), SEEK_SET);
            fread(&a, sizeof(int), 1, fp);   /* v[j]                     */
            fread(&b, sizeof(int), 1, fp);   /* v[j+1] (cursor seguinte) */

            if (a > b) {                     /* fora de ordem -> troca   */
                fseek(fp, j * (long)sizeof(int), SEEK_SET);
                fwrite(&b, sizeof(int), 1, fp);
                fwrite(&a, sizeof(int), 1, fp);
                trocou = 1;
            }
        }

        if (!trocou)        /* passada sem trocas => arquivo ordenado */
            break;
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

    cria_bin("dados_q1.bin", v, n);

    printf("antes : ");
    mostra_bin("dados_q1.bin");

    BolhaBin("dados_q1.bin");

    printf("depois: ");
    mostra_bin("dados_q1.bin");
    printf("(esperado: 1 3 8 10 13 14 25 29 37)\n");

    return 0;
}
