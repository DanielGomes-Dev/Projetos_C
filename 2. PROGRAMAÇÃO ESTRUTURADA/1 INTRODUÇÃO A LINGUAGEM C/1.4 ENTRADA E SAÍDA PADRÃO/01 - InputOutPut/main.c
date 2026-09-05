#include <stdio.h>

/* ============================================================
   ENTRADA E SAÍDA EM C: printf() e scanf()
   ============================================================
   C não tem comandos de entrada/saída embutidos na linguagem
   (diferente de outras linguagens). Tudo é feito por FUNÇÕES da
   biblioteca padrão, declaradas em <stdio.h> (stdio = "standard
   input/output" = entrada/saída padrão).

   printf() -> imprime coisas na tela
   scanf()  -> lê coisas digitadas pelo usuário
   ============================================================ */


/* ============================================================
   1) printf() — especificadores de formato básicos
   ============================================================
   Forma geral:
       printf(formato, valor1, valor2, ...);

   O "formato" é uma string com texto normal + especificadores.
   Cada especificador (começa com %) é substituído, em ordem,
   pelo valor correspondente na lista de argumentos.

   Principais especificadores:
     %d  -> int (inteiro com sinal)
     %u  -> unsigned int (inteiro sem sinal)
     %c  -> char (um único caractere)
     %f  -> float ou double (formato decimal comum)
     %e  -> float ou double em notação científica (ex.: 1.5e+03)
     %g  -> float ou double, escolhe automaticamente %f ou %e
     %s  -> string (cadeia de caracteres)
     %%  -> imprime o caractere % literal
   ============================================================ */
void exemplo_printf_basico() {
    int idade = 33;
    double nota = 5.3;
    char letra = 'A';
    char nome[] = "Maria";

    // Vários especificadores numa única chamada
    printf("%d %g\n", idade, nota);              // 33 5.3

    // Misturando texto fixo com especificadores
    printf("Inteiro = %d  Real = %g\n", idade, nota);

    // %c para caractere, %s para string
    printf("Letra: %c   Nome: %s\n", letra, nome);

    // Apenas uma mensagem, sem especificadores
    printf("Curso de Estruturas de Dados\n");

    // %% imprime um % de verdade (não é especificador aqui)
    printf("Desconto de 10%% no total\n");
}

/* ============================================================
   2) Caracteres de escape
   ============================================================
   Servem para representar caracteres especiais dentro de uma
   string, já que não dá pra digitá-los diretamente.

     \n  -> nova linha
     \t  -> tabulação (um "tab")
     \r  -> retorno de carro (volta o cursor pro início da linha)
     \"  -> aspas duplas dentro de uma string
     \\  -> uma barra invertida "\"
   ============================================================ */
void exemplo_caracteres_escape() {
    printf("Linha 1\nLinha 2\n");             // \n pula linha
    printf("Nome:\tIdade:\n");                // \t alinha em colunas
    printf("Maria\t23\n");
    printf("Ele disse: \"Ola, mundo!\"\n");   // \" para exibir aspas
    printf("Caminho: C:\\Users\\Maria\n");    // \\ para exibir uma barra
}

/* ============================================================
   3) Controlando largura e casas decimais
   ============================================================
   %4d    -> reserva no mínimo 4 colunas para o inteiro (alinha à direita)
   %-4d   -> mesma coisa, mas alinhado à esquerda
   %7.2f  -> reserva 7 colunas no total, com 2 casas decimais
   %.2f   -> só fixa 2 casas decimais, sem se importar com a largura total
   ============================================================ */
void exemplo_formatacao() {
    int a = 3;
    double pi = 3.14159265;

    printf("[%4d]\n", a);        // "[   3]" -> 4 colunas, alinhado à direita
    printf("[%-4d]\n", a);       // "[3   ]" -> 4 colunas, alinhado à esquerda
    printf("[%7.2f]\n", pi);     // "[   3.14]" -> 7 colunas, 2 casas decimais
    printf("[%.2f]\n", pi);      // "[3.14]" -> só limita casas decimais

    // Útil, por exemplo, para imprimir uma tabela alinhada:
    printf("%-10s %5s\n", "Produto", "Preco");
    printf("%-10s %5.2f\n", "Cafe", 12.5);
    printf("%-10s %5.2f\n", "Bolo", 8.9);
}

/* ============================================================
   4) scanf() — lendo valores digitados pelo usuário
   ============================================================
   Forma geral:
       scanf(formato, lista de ENDEREÇOS de variáveis...);

   Diferença importante em relação ao printf: o scanf precisa do
   ENDEREÇO de memória de cada variável, não do valor. Por isso
   usamos o operador & (endereço de) na frente do nome da
   variável — exceto quando a variável já é um ponteiro/vetor,
   como é o caso de strings (char[]).

   Especificadores usados no scanf (repare que float e double
   são diferentes aqui, ao contrário do printf):
     %d          -> int
     %u          -> unsigned int
     %c          -> char
     %f  %e  %g  -> float
     %lf %le %lg -> double   (o "l" de "long" antes do especificador)
     %s          -> string (cadeia de caracteres, sem &)
   ============================================================ */
void exemplo_scanf_basico() {
    int idade;
    double altura;
    char inicial;
    char nome[50];

    printf("Digite sua idade: ");
    scanf("%d", &idade);              // & porque idade é int

    printf("Digite sua altura em metros: ");
    scanf("%lf", &altura);            // %lf para double (não %f!)

    printf("Digite a inicial do seu nome: ");
    scanf(" %c", &inicial);           // espaço antes do %c: veja explicação abaixo

    printf("Digite seu nome: ");
    scanf("%s", nome);                // sem &, pois nome[] já é o endereço do vetor

    printf("\nResumo:\n");
    printf("Nome: %s (%c)\n", nome, inicial);
    printf("Idade: %d anos\n", idade);
    printf("Altura: %.2f m\n", altura);
}

/* ============================================================
   5) Cuidado: espaços em branco no scanf
   ============================================================
   Os especificadores %d, %f, %e, %g e %s IGNORAM automaticamente
   espaços/quebras de linha que vierem antes do valor.

   Já o %c NÃO ignora — ele lê literalmente o próximo caractere
   disponível no buffer, mesmo que seja um espaço ou um "\n"
   deixado por uma leitura anterior. Por isso é comum colocar um
   espaço ANTES do %c no formato (" %c"): esse espaço no formato
   instrui o scanf a pular quaisquer brancos pendentes antes de
   ler o caractere de verdade.
   ============================================================ */
void exemplo_scanf_espacos() {
    int quantidade;
    char resposta;

    printf("Quantos itens? ");
    scanf("%d", &quantidade);   // usuário digita "3" e aperta Enter

    // Sem o espaço antes de %c, este scanf leria o "\n" deixado
    // pela leitura anterior, e não a letra que o usuário digitar!
    printf("Confirma? (s/n) ");
    scanf(" %c", &resposta);    // o espaço "engole" o \n pendente

    printf("Voce escolheu %d itens e respondeu '%c'\n", quantidade, resposta);
}

/* ============================================================
   6) scanf() com separadores fixos no formato
   ============================================================
   Caracteres do formato que não são especificadores servem para
   "casar" com a entrada exatamente como escritos. Por exemplo,
   scanf("%d:%d", &h, &m) exige que o usuário digite algo como
   "14:30", com os dois pontos entre os números.
   ============================================================ */
void exemplo_scanf_separador() {
    int horas, minutos;

    printf("Digite o horario (formato HH:MM): ");
    scanf("%d:%d", &horas, &minutos); // exige o ":" entre os números

    printf("Voce digitou %02d horas e %02d minutos\n", horas, minutos);
    // %02d -> preenche com zero à esquerda até completar 2 dígitos
}

/* ============================================================
   7) Programa completo de exemplo
   ============================================================
   Converte uma altura em metros para pés e polegadas.
   1 pé = 30,48 cm    |    1 polegada = 2,54 cm
   Ex.: digitando 1.8 (metros), o programa mostra algo como
   "Altura: 5ft 10.9pol"
   ============================================================ */
void converte_altura() {
    int pes;            // número de pés (inteiro)
    float polegadas;    // número de polegadas restantes
    float alturaMetros; // altura digitada, em metros

    printf("Digite a altura em metros: ");
    scanf("%f", &alturaMetros);

    float alturaCm = 100 * alturaMetros;      // converte metros -> centímetros

    pes = (int) (alturaCm / 30.48);            // quantos pés cabem (trunca o resto)
    polegadas = (alturaCm - pes * 30.48f) / 2.54f; // converte o restante em polegadas

    printf("Altura: %dft %.1fpol\n", pes, polegadas);
}

int main(void) {
    // Descomente a função que quiser testar (algumas pedem entrada pelo teclado):
    // exemplo_printf_basico();
    // exemplo_caracteres_escape();
    // exemplo_formatacao();
    // exemplo_scanf_basico();
    // exemplo_scanf_espacos();
    // exemplo_scanf_separador();
    // converte_altura();

    return 0;
}