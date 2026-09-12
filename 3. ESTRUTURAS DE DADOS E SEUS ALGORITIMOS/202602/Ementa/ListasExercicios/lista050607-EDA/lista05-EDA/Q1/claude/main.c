#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================= *
 * LISTA 05 - Q1
 *
 * "Desenvolva um procedimento que receba o nome de um arquivo texto e
 *  retire deste texto palavras consecutivas repetidas. O programa deve
 *  gravar o resultado no arquivo de saida (tambem informado como
 *  parametro)."
 *
 *      void RetRepet(char *ArqEnt, char *ArqSaida);
 *
 * EXEMPLO DO ENUNCIADO
 *   entrada : "Isto e um texto texto repetido repetido repetido . Com
 *              as repeticoes repeticoes fica fica sem sem sentido .
 *              Sem elas elas elas melhora melhora um um pouco ."
 *   saida   : "Isto e um texto repetido . Com as repeticoes fica sem
 *              sentido . Sem elas melhora um um pouco ."
 *
 *   OBS. sobre o "um um" no final: pela regra "remover toda palavra
 *   igual a anterior" o resultado seria "... melhora um pouco .".
 *   O gabarito do PDF mantem "um um", o que parece ser uma
 *   INCONSISTENCIA do proprio enunciado. Implementei a regra
 *   coerente (colapsar QUALQUER repeticao consecutiva); isso
 *   diverge do exemplo somente nesse ponto.
 *
 * ----------------------------------------------------------------- *
 * COMO A SOLUCAO FUNCIONA
 *   1. Abro o arquivo de entrada em modo texto ("r") e o de saida
 *      em modo texto ("w").
 *   2. Leio o arquivo PALAVRA A PALAVRA com fscanf(fp, "%s", buf).
 *      O "%s" pula automaticamente qualquer espaco/tab/quebra de
 *      linha e le a proxima sequencia de nao-brancos. Isso resolve
 *      de graca a tokenizacao (inclusive o "." isolado, que conta
 *      como uma "palavra").
 *   3. Mantenho em 'anterior' a ultima palavra ESCRITA na saida.
 *      - Para a primeira palavra: escrevo e guardo em 'anterior'.
 *      - Para as demais: se for igual a 'anterior' (strcmp == 0),
 *        IGNORO; senao escrevo um espaco separador + a palavra e
 *        atualizo 'anterior'.
 *   4. A comparacao e sensivel a maiusculas/minusculas (padrao em C).
 *
 * CUSTO: O(n) no numero de palavras; memoria O(1) (so dois buffers).
 * ================================================================= */

#define MAXPAL 256   /* tamanho maximo de uma palavra + '\0' */

void RetRepet(char *ArqEnt, char *ArqSaida) {
    FILE *fe = fopen(ArqEnt, "r");
    if (!fe) {
        printf("RetRepet: nao consegui abrir '%s' para leitura.\n", ArqEnt);
        return;
    }
    FILE *fs = fopen(ArqSaida, "w");
    if (!fs) {
        printf("RetRepet: nao consegui abrir '%s' para escrita.\n", ArqSaida);
        fclose(fe);
        return;
    }

    char atual[MAXPAL];
    char anterior[MAXPAL] = "";   /* "" garante diferente da 1a palavra */
    int primeira = 1;

    while (fscanf(fe, "%255s", atual) == 1) {
        if (primeira) {
            fputs(atual, fs);            /* 1a palavra: escreve direto  */
            primeira = 0;
        } else if (strcmp(atual, anterior) != 0) {
            fputc(' ', fs);             /* separador entre palavras     */
            fputs(atual, fs);
        }
        /* se for igual a anterior: nao faz nada (remove a repeticao)   */

        if (strcmp(atual, anterior) != 0)
            strcpy(anterior, atual);    /* atualiza a ultima escrita    */
    }

    fclose(fe);
    fclose(fs);
}

/* ---- utilitario de teste: joga o conteudo de um arquivo na tela -- */
static void mostra_arquivo(const char *nome) {
    FILE *fp = fopen(nome, "r");
    if (!fp) { printf("(nao abriu %s)\n", nome); return; }
    int c;
    while ((c = fgetc(fp)) != EOF) putchar(c);
    putchar('\n');
    fclose(fp);
}

int main(void) {
    const char *ent = "entrada_q1.txt";
    const char *sai = "saida_q1.txt";

    /* cria o arquivo de entrada com o exemplo do enunciado */
    FILE *fp = fopen(ent, "w");
    fputs("Isto e um texto texto repetido repetido repetido . "
          "Com as repeticoes repeticoes fica fica sem sem sentido . "
          "Sem elas elas elas melhora melhora um um pouco .\n", fp);
    fclose(fp);

    printf("--- ENTRADA ---\n");
    mostra_arquivo(ent);

    RetRepet((char *)ent, (char *)sai);

    printf("\n--- SAIDA (repeticoes consecutivas removidas) ---\n");
    mostra_arquivo(sai);

    printf("\nEsperado (gabarito, a menos do \"um um\" - ver comentario):\n");
    printf("Isto e um texto repetido . Com as repeticoes fica sem sentido . "
           "Sem elas melhora um um pouco .\n");

    return 0;
}
