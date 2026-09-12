#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================= *
 * LISTA 05 - Q3
 *
 * "Receba o nome de um arquivo texto cujo conteudo sao valores
 *  inteiros e IMPRIMA NA TELA o numero de vezes que cada elemento
 *  aparece e EM QUAIS LINHAS."
 *
 *      void resumo(char *Arq);
 *
 * ----------------------------------------------------------------- *
 * PASSO A PASSO
 *   1. Abro o arquivo em modo texto.
 *   2. Percorro LINHA A LINHA com fgets, mantendo um contador
 *      'nlinha' (1, 2, 3, ...).
 *   3. Dentro de cada linha extraio TODOS os inteiros com strtol
 *      num laco (a linha pode ter varios numeros ou nenhum).
 *   4. Para cada inteiro lido procuro-o numa tabela de ocorrencias:
 *        - se ja existe, incremento a contagem e anexo o numero da
 *          linha na sua lista de linhas;
 *        - se e novo, crio uma entrada.
 *      A tabela e um vetor simples percorrido linearmente (busca
 *      O(k)); para volumes pequenos e o suficiente e mantem o
 *      codigo legivel.
 *   5. No fim imprimo, para cada valor DISTINTO (na ordem em que
 *      apareceu pela primeira vez): o valor, a contagem e a lista
 *      de linhas.
 *
 *   Observacao: se o mesmo valor aparece 2x na mesma linha, a linha
 *   e listada 2x (reflete "quantas vezes aparece").
 *
 * CUSTO: O(N * k) no pior caso (N numeros, k valores distintos).
 * ================================================================= */

#define MAX_DISTINTOS 1000
#define MAX_LINHAS_POR_VALOR 1000
#define MAXLIN 1024

typedef struct {
    long valor;
    int  contagem;
    int  linhas[MAX_LINHAS_POR_VALOR];
} Ocorrencia;

void resumo(char *Arq) {
    FILE *fp = fopen(Arq, "r");
    if (!fp) {
        printf("resumo: nao consegui abrir '%s'.\n", Arq);
        return;
    }

    /* 'static' para NAO ocupar a pilha: a tabela e grande
     * (MAX_DISTINTOS * MAX_LINHAS_POR_VALOR inteiros) e um vetor
     * automatico desse tamanho estouraria o stack.               */
    static Ocorrencia tab[MAX_DISTINTOS];
    int ndist = 0;

    char linha[MAXLIN];
    int nlinha = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        nlinha++;

        char *p = linha;
        while (1) {
            char *fim;
            long x = strtol(p, &fim, 10);
            if (fim == p)               /* nao havia mais numero      */
                break;
            p = fim;                    /* avanca alem do numero lido  */

            /* procura x na tabela */
            int i;
            for (i = 0; i < ndist; i++)
                if (tab[i].valor == x)
                    break;

            if (i == ndist) {           /* valor novo                  */
                if (ndist == MAX_DISTINTOS) { printf("(tabela cheia)\n"); break; }
                tab[i].valor = x;
                tab[i].contagem = 0;
                ndist++;
            }
            if (tab[i].contagem < MAX_LINHAS_POR_VALOR)
                tab[i].linhas[tab[i].contagem] = nlinha;
            tab[i].contagem++;
        }
    }
    fclose(fp);

    printf("Resumo de '%s':\n", Arq);
    for (int i = 0; i < ndist; i++) {
        printf("  valor %ld -> aparece %d vez(es), na(s) linha(s): ",
               tab[i].valor, tab[i].contagem);
        int lim = tab[i].contagem < MAX_LINHAS_POR_VALOR
                      ? tab[i].contagem : MAX_LINHAS_POR_VALOR;
        for (int j = 0; j < lim; j++)
            printf("%d%s", tab[i].linhas[j], (j + 1 < lim) ? ", " : "");
        printf("\n");
    }
}

/* ---- teste ------------------------------------------------------- */
int main(void) {
    const char *arq = "numeros_q3.txt";

    /* arquivo de exemplo:
     *   linha 1: 10
     *   linha 2: 20
     *   linha 3: 10 30
     *   linha 4: 20
     *   linha 5: 10
     *   linha 6: 40
     */
    FILE *fp = fopen(arq, "w");
    fputs("10\n20\n10 30\n20\n10\n40\n", fp);
    fclose(fp);

    printf("--- ARQUIVO DE ENTRADA ---\n");
    fp = fopen(arq, "r");
    int c; while ((c = fgetc(fp)) != EOF) putchar(c);
    fclose(fp);
    printf("\n--- SAIDA ---\n");

    resumo((char *)arq);

    printf("\nEsperado:\n"
           "  10 -> 3 vez(es), linhas 1, 3, 5\n"
           "  20 -> 2 vez(es), linhas 2, 4\n"
           "  30 -> 1 vez,     linha  3\n"
           "  40 -> 1 vez,     linha  6\n");
    return 0;
}
