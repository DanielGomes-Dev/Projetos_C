#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Função: escrever_fputc
 * Uso: Gravando o arquivo "no braço", caractere por caractere.
 */
void escrever_fputc(char f[]) 
{
    // "w" abre para escrita: se o arquivo existe, ele limpa; se não, cria.
    FILE *file = fopen(f, "w");
    char letra;

    if (file) 
    {
        printf("\n Digite um texto e pressione ENTER ao Finalizar! \n");
        
        // Lê apenas o primeiro caractere digitado
        scanf("%c", &letra);
        
        // Loop continua enquanto o caractere lido não for a quebra de linha (Enter)
        while (letra != '\n')
        {
            // fputc coloca fisicamente aquele caractere dentro do arquivo
            fputc(letra, file);
            // Lê o próximo caractere para continuar a verificação no while
            scanf("%c", &letra);
        }
        
        // fclose é obrigatório: ele "empurra" os dados do buffer para o disco rígido
        fclose(file);
    }
    else
        printf("\nErro ao Abrir o Arquivo\n");
}

/**
 * Função: ler_fgetc
 * Uso: Lendo o arquivo caractere por caractere (útil para processar cada símbolo).
 */
void ler_fgetc(char f[])
{
    FILE *file = fopen(f, "r"); // "r" = read (apenas leitura)
    char letra;

    if(file){
        printf("\nTexto lido do arquivo: \n\n");
        
        // Enquanto o ponteiro interno do arquivo não atingir o EOF (End Of File)
        while (!feof(file))
        {
            // fgetc extrai o caractere atual e move o cursor para o próximo
            letra = fgetc(file);
            // Imprime o que acabou de ler na tela
            printf("%c", letra);
        }
        
        fclose(file);
    }
    else
        printf("\nErro ao Abrir o Arquivo\n");
}

/**
 * Função: escrever_fputs
 * Uso: Gravando strings (frases) inteiras. Mais eficiente que o fputc.
 */
void escrever_fputs(char f[]) 
{
    FILE *file = fopen(f, "w");
    char texto[500]; 
    if (file)
    {
        printf("\n Digite uma frase e digite apenas 1 caracter para Finalizar! \n");
        // [^\n] faz o scanf ler espaços vazios, parando apenas no Enter
        scanf("%500[^\n]", texto);
        // Consome o '\n' que sobrou no buffer do teclado para não travar o próximo scanf
        scanf("%c"); 
        
        // Se a string tiver mais de 1 caractere, ela é gravada
        while(strlen(texto) > 1){
            fputs(texto, file);      // Grava a string
            fputc('\n', file);       // Adiciona manualmente uma quebra de linha no arquivo
            scanf("%500[^\n]", texto); // Pede a próxima frase
            scanf("%c");             // Limpa o Enter novamente
        }

        fclose(file);
    }
    else
        printf("\nErro ao Abrir o Arquivo\n");
}

/**
 * Função: escrever_fprintf
 * Uso: Grava dados formatados, como se fosse uma planilha CSV (Campos separados por vírgula).
 */
void escrever_fprintf(char f[]){
    FILE *file = fopen(f, "w");
    char nome[100];
    int idade, opcao;
    float altura;

    if(file){
        do {
            printf("Digite nome, idade e altura: ");
            // Lê o nome (com espaços), depois busca o inteiro e o float
            scanf(" %99[^\n]%d%f", nome, &idade, &altura);
            
            // Grava no arquivo separando por vírgulas: Nome,Idade,Altura
            fprintf(file, "%s,%d,%.2f\n", nome, idade, altura);

            printf("Digite 1 para continuar adicionando: ");
            scanf("%d", &opcao);  
            // Limpa o buffer: sem isso, o próximo %[^\n] leria o Enter anterior e ficaria vazio
            scanf("%c");
        } while(opcao == 1);
    
        fclose(file);
    }
    else{
        printf("\nErro ao abrir arquivo!\n");
    }
}

/**
 * Função: ler_fscanf
 * Uso: Recupera dados estruturados. É o "par" do fprintf.
 */
void ler_fscanf(char f[]){
    FILE *file = fopen(f, "r");
    char nome[100];
    int idade;
    float altura;

    if(file){
        printf("Dados lidos do arquivo:\n\n");

        /**
         * EXPLICANDO O FORMATO " %99[^,],%d,%f":
         * 1. O espaço inicial ' ' manda o C ignorar qualquer \n (Enter) da linha anterior.
         * 2. %99[^,] lê tudo até encontrar a primeira vírgula (o nome composto).
         * 3. a vírgula ',' literal após o ] pula a vírgula do arquivo.
         * 4. %d e %f leem os números ignorando as vírgulas subsequentes.
         * 5. == 3 garante que o loop só rode se ele encontrar os 3 campos (evita lixo no fim do arquivo).
         */
        while (fscanf(file, " %99[^,],%d,%f", nome, &idade, &altura) == 3)
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

int main()
{
    // Nome do arquivo físico que será manipulado
    char file[] = {"conto.txt"};
    
    // Escolha qual função testar descomentando abaixo:
    // escrever_fprintf(file);
    ler_fscanf(file);

    return 0; 
}