#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RetRepet(char *ArqEnt, char *ArqSaida) {
    FILE *fpIn = fopen(ArqEnt, "r");
    FILE *fpOut = fopen(ArqSaida, "w");
    
    // Verifica se os arquivos foram abertos corretamente
    if (fpIn == NULL || fpOut == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        if (fpIn) fclose(fpIn);
        if (fpOut) fclose(fpOut);
        return;
    }

    char atual[100];
    char anterior[100];

    // Tenta ler a primeira palavra do arquivo
    if (fscanf(fpIn, "%s", anterior) == 1) {
        // Escreve a primeira palavra no arquivo de saída
        fprintf(fpOut, "%s", anterior);

        // Enquanto conseguir ler a próxima palavra
        while (fscanf(fpIn, "%s", atual) == 1) {
            // Se a palavra atual for diferente da anterior, ela é gravada
            if (strcmp(atual, anterior) != 0) {
                fprintf(fpOut, " %s", atual); // Adiciona um espaço antes da nova palavra
                strcpy(anterior, atual);     // Atualiza a "anterior" para a próxima comparação
            }
        }
    }

    fclose(fpIn);
    fclose(fpOut);
}

int main(){

    RetRepet("arquivo_entrada.txt", "arquivo_saida.txt");

    return 0;
}