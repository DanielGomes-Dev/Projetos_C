#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================= *
 * LISTA 06 - Q1
 *
 * "Leia dois arquivos binarios 'a.bin' e 'b.bin' contendo palavras
 *  distintas de 10 caracteres e produza 'c.bin'. Cada registro de
 *  'c.bin' contem um PAR ORDENADO (palavra de a.bin, palavra de
 *  b.bin). 'c.bin' deve conter TODOS os pares -> PRODUTO CARTESIANO.
 *  Todo o processamento deve ser feito em MEMORIA SECUNDARIA."
 *
 * ----------------------------------------------------------------- *
 * MODELAGEM DOS REGISTROS
 *   a.bin / b.bin : blocos de PALAVRA = 10 bytes (char[10]).
 *                   Nao ha '\0' garantido -> trato sempre 10 bytes
 *                   fixos.
 *   c.bin         : blocos de 20 bytes = PALAVRA de a  seguida da
 *                   PALAVRA de b (o "par ordenado").
 *
 * "EM MEMORIA SECUNDARIA" = nao posso carregar os arquivos inteiros
 *   para vetores na RAM. Uso somente 1 registro de cada por vez e
 *   os proprios arquivos como armazenamento.
 *
 * ALGORITMO (dois lacos aninhados, como um produto cartesiano)
 *   abre a.bin (rb), b.bin (rb), c.bin (wb)
 *   enquanto conseguir ler 1 palavra 'pa' de a.bin:
 *       rewind(b)                         // volta b.bin ao inicio
 *       enquanto conseguir ler 1 palavra 'pb' de b.bin:
 *           escreve pa em c.bin           // 10 bytes
 *           escreve pb em c.bin           // + 10 bytes  => registro
 *   fecha tudo
 *
 *   Leituras: |A| * |B| em b.bin + |A| em a.bin.
 *   Escritas: |A| * |B| registros em c.bin.
 *   RAM usada: O(1) (duas palavras de 10 bytes).
 *
 * CUSTO: O(|A| * |B|) acessos a disco - inevitavel, pois a saida
 *        tem esse tamanho.
 * ================================================================= */

#define TAM_PALAVRA 10

void produto_cartesiano(const char *arqA, const char *arqB, const char *arqC) {
    FILE *fa = fopen(arqA, "rb");
    FILE *fb = fopen(arqB, "rb");
    FILE *fc = fopen(arqC, "wb");
    if (!fa || !fb || !fc) {
        printf("produto_cartesiano: falha ao abrir arquivos.\n");
        if (fa) fclose(fa);
        if (fb) fclose(fb);
        if (fc) fclose(fc);
        return;
    }

    char pa[TAM_PALAVRA], pb[TAM_PALAVRA];

    /* laco externo: cada palavra de A */
    while (fread(pa, TAM_PALAVRA, 1, fa) == 1) {
        rewind(fb);                       /* reposiciona B no inicio   */
        /* laco interno: cada palavra de B */
        while (fread(pb, TAM_PALAVRA, 1, fb) == 1) {
            fwrite(pa, TAM_PALAVRA, 1, fc);   /* 1a metade do par      */
            fwrite(pb, TAM_PALAVRA, 1, fc);   /* 2a metade do par      */
        }
    }

    fclose(fa);
    fclose(fb);
    fclose(fc);
}

/* ---- utilitarios de teste -------------------------------------- */

/* grava um vetor de palavras (strings) como blocos de 10 bytes    */
static void cria_bin(const char *nome, const char *palavras[], int n) {
    FILE *fp = fopen(nome, "wb");
    for (int i = 0; i < n; i++) {
        char bloco[TAM_PALAVRA];
        memset(bloco, ' ', TAM_PALAVRA);            /* preenche c/ espaco */
        size_t len = strlen(palavras[i]);
        if (len > TAM_PALAVRA) len = TAM_PALAVRA;
        memcpy(bloco, palavras[i], len);
        fwrite(bloco, TAM_PALAVRA, 1, fp);
    }
    fclose(fp);
}

/* imprime os pares de c.bin (20 bytes por registro) */
static void mostra_pares(const char *nome) {
    FILE *fp = fopen(nome, "rb");
    if (!fp) { printf("(nao abriu %s)\n", nome); return; }
    char par[2 * TAM_PALAVRA];
    int k = 0;
    while (fread(par, 2 * TAM_PALAVRA, 1, fp) == 1) {
        printf("  par %2d: (\"%.*s\", \"%.*s\")\n", ++k,
               TAM_PALAVRA, par, TAM_PALAVRA, par + TAM_PALAVRA);
    }
    fclose(fp);
    printf("  total de registros em c.bin: %d\n", k);
}

int main(void) {
    const char *A[] = {"casa", "sol", "rua"};       /* 3 palavras */
    const char *B[] = {"gato", "peixe"};            /* 2 palavras */

    cria_bin("a.bin", A, 3);
    cria_bin("b.bin", B, 2);

    produto_cartesiano("a.bin", "b.bin", "c.bin");

    printf("A = {casa, sol, rua}   B = {gato, peixe}\n");
    printf("Produto cartesiano A x B (esperado 3 x 2 = 6 pares):\n");
    mostra_pares("c.bin");

    return 0;
}
