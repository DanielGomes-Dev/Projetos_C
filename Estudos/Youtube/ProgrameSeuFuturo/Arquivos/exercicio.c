#include <stdio.h>
#include <stdlib.h>

void escrever_fputc(char f[]) // Escreve Caracter
{
    FILE *file = fopen(f, "w");
    char letra;
    if (file)
    {
        printf("\n Digite um texto e pressione ENTER ao Finalizar! \n");
        scanf("%c", &letra);
        while (letra != '\n')
        {
            fputc(letra, file);
            scanf("%c", &letra);
        }
        fclose(file);
    }
    else
        printf("\nErro ao Abrir o Arquivo\n");
}

void escrever_fputs(char f[]) // Escreve String Completa
{
    FILE *file = fopen(f, "w");
    char letra;
    if (file)
    {
        printf("\n Digite um texto e pressione ENTER ao Finalizar! \n");
        scanf("%c", &letra);
        while (letra != '\n')
        {
            fputc(letra, file);
            scanf("%c", &letra);
        }
        fclose(file);
    }
    else
        printf("\nErro ao Abrir o Arquivo\n");
}

void ler(char f[])
{
    FILE *file = fopen(f, "r");
    char letra;

    if(file){
        printf("\n\t Texto lido do arquivo: \n");
        while (!feof(file))
        {
            letra = fgetc(file);
            printf("%c", letra);
        }
        
        fclose(file);
    }
    else
        printf("\nErro ao Abrir o Arquivo\n");
}

// rewind(file); // Volta pro inicio do arquivo (o ponteiro volta para o inicio do arquivo);

int main()
{
    // char file[10] = "conto.txt";
    // char file[] = "conto.txt";
    char file[] = {"conto.txt"};


    escrever(file);
    ler(file);

}
