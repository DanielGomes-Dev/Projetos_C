#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Função: escrever_fputc
 * Objetivo: Grava um texto no arquivo caractere por caractere.
 * Parâmetro: f[] (nome do arquivo)
 */
void escrever_fputc(char f[]) 
{
    // Abre o arquivo para escrita ("w" - write). Se o arquivo existir, ele é sobrescrito.
    FILE *file = fopen(f, "w");
    char letra;

    if (file) // Verifica se o ponteiro do arquivo foi criado com sucesso
    {
        printf("\n Digite um texto e pressione ENTER ao Finalizar! \n");
        
        // Lê o primeiro caractere digitado pelo usuário
        scanf("%c", &letra);
        
        // Enquanto o usuário não apertar ENTER ('\n'), continua gravando
        while (letra != '\n')
        {
            // fputc grava UM único caractere por vez no arquivo apontado por 'file'
            fputc(letra, file);
            // Lê o próximo caractere do buffer do teclado
            scanf("%c", &letra);
        }
        
        // Fecha o arquivo para salvar as alterações e liberar memória
        fclose(file);
    }
    else
        printf("\nErro ao Abrir o Arquivo\n");
}

/**
 * Função: ler_fgetc
 * Objetivo: Lê o conteúdo do arquivo caractere por caractere e exibe no console.
 * Parâmetro: f[] (nome do arquivo)
 */
void ler_fgetc(char f[])
{
    // Abre o arquivo apenas para leitura ("r" - read)
    FILE *file = fopen(f, "r");
    char letra;

    if(file){
        printf("\nTexto lido do arquivo: \n\n");
        
        // feof(file) verifica se o ponteiro chegou ao "End Of File" (Fim do Arquivo)
        while (!feof(file))
        {
            // fgetc lê UM único caractere do arquivo
            letra = fgetc(file);
            // Imprime o caractere lido na tela do console
            printf("%c", letra);
        }
        
        fclose(file); // Fecha o arquivo após a leitura
    }
    else
        printf("\nErro ao Abrir o Arquivo\n");
}

/**
 * Função: escrever_fputs
  nome sugira fputs (que escreve strings), 
 */
void escrever_fputs(char f[]) 
{
    FILE *file = fopen(f, "w");
    char texto[500]; 
    if (file)
    {
        printf("\n Digite uma frase e digite apenas 1 caracter para Finalizar! \n");
        scanf("%500[^\n]", texto);
        scanf("%c"); //ler o caracter sem salvar em nenhum lugar consumindo o enter
        while(strlen(texto)>1){
            fputs(texto, file);
            fputc('\n', file);
            scanf("%500[^\n]", texto);
            scanf("%c"); //ler o caracter sem salvar em nenhum lugar consumindo o enter
            //loop infinito por causa do buffer do teclado o \n

        }

        fclose(file);
    }
    else
        printf("\nErro ao Abrir o Arquivo\n");
}


void ler_fgets(char f[]){
    FILE *file = fopen(f, "r");
    char texto[500];

    if(file){
        printf("\nTexto lido do arquivo:\n");
        while(!feof(file)){
            if(fgets(texto, 500, file)){
                printf("\n%s\n", texto);
            }
        }
        fclose(file);
    }
    else{
        printf("\nErro ao abrir arquivo!\n");
    }
}

void escrever_fprintf(char f[]){
    FILE *file = fopen(f, "w");
    char nome[100];
    int idade, opcao;
    float altura;
    if(file){
        do {
            printf("Digite nome, idade e altura: ");
            scanf("%100[^\n]%d%f", nome, &idade, &altura);
            // fprintf(file, "nome: %s, idade: %d, Altura: %.2f\n", nome, idade, altura);
            fprintf(file, "%s,%d,%.2f\n", nome, idade, altura);

            printf("Digite 1 para continuar adicionando.\n");
            scanf("%d", &opcao);  
            scanf("%c");
        } while(opcao == 1);
    
        fclose(file);
    }
    else{
        printf("\nErro ao abrir arquivo!\n");
    }
}


void ler_fscanf(char f[]){
    FILE *file = fopen(f, "r");
    char nome[100];
    int idade;
    float altura;

    if(file){


        printf("Dados lido do arquivo:\n\n");

        // int count = 0;
        // while(!feof(file)){
        //     if(count <= fscanf(file, "%s%d%f", nome, &idade, &altura)){
        //         printf("Nome: %s, Idade: %d, Altura: %.2f\n", nome, idade, altura);
        //     }
        //     ++count;
        // }

        while (fscanf(file, " %99[^,],%d,%f", nome, &idade, &altura)!= -1)
        {
             printf("Nome: %s, Idade: %d, Altura: %.2f\n", nome, idade, altura);
        }
        
        printf("\n");
        

        fclose(file);
    }
    else {
        printf("Arquivo não foi aberto com sucesso.");
    }
}


/* Nota sobre rewind(file): 
   Esta função move o cursor de leitura/escrita de volta para o início do arquivo.
   Útil quando você escreve algo e quer ler logo em seguida sem fechar e abrir de novo.
*/

int main()
{
    // Declaração da string com o nome do arquivo físico no disco
    char file[] = {"conto.txt"};
    
    // escrever_fprintf(file);
    ler_fscanf(file);

    return 0; // Indica que o programa terminou com sucesso
}