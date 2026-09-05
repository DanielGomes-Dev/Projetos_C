#include <stdio.h>

/* ============================================================
   1) VARIÁVEIS
   ============================================================
   Uma variável é um espaço na memória com um nome, um tipo
   e um valor. O tipo define quanto espaço ela ocupa e que
   tipo de dado pode guardar.
   ============================================================ */
void variaveis() {
    int idade = 25;              // número inteiro (sem casas decimais)
    float altura = 1.75f;        // ponto flutuante, precisão simples (~7 dígitos)
    double peso = 68.523;        // ponto flutuante, precisão dupla (~15 dígitos)
    char inicial = 'M';          // um único caractere (entre aspas simples)
    char nome[20] = "Maria";     // string = vetor (array) de caracteres
    int aprovado = 1;            // em C não existe "bool" nativo; usa-se int (0 = falso, != 0 = verdadeiro)

    printf("Idade: %d\n", idade);
    printf("Altura: %.2f\n", altura);      // %.2f = 2 casas decimais
    printf("Peso: %.3lf\n", peso);         // %lf também funciona com printf (double)
    printf("Inicial: %c\n", inicial);
    printf("Nome: %s\n", nome);
    printf("Aprovado? %d\n", aprovado);

    // Declarar sem inicializar é perigoso: a variável fica com "lixo de memória"
    int x;
    // printf("%d", x); // NÃO faça isso: valor indefinido, comportamento imprevisível
    x = 0; // sempre inicialize antes de usar
    printf("x inicializado: %d\n", x);
}

/* ============================================================
   2) OPERADORES ARITMÉTICOS  (+  -  *  /  %)
   ============================================================ */
void operadores_aritmeticos() {
    int a;
    double b, c;

    // ATENÇÃO: 3.5 é double, mas 'a' é int -> o valor é TRUNCADO (não arredondado)
    a = 3.5; // a passa a valer 3 (a parte decimal é descartada)

    b = a / 2.0; // 3 / 2.0 = 1.5  (2.0 é double, então a divisão é "verdadeira")

    // Cuidado: 1/3 com dois inteiros faz DIVISÃO INTEIRA -> resultado 0 (trunca)
    // Para obter 0.333..., pelo menos um dos operandos precisa ser float/double
    c = 1 / 3 + b;       // 0 + 1.5 = 1.5
    double c_correto = 1.0 / 3.0 + b; // 0.333... + 1.5 = 1.833...

    printf("a=%d  b=%f  c=%f  c_correto=%f\n", a, b, c, c_correto);

    // ----- Operador módulo (%) -----
    // Só funciona com inteiros. Retorna o RESTO da divisão.
    int x = 7;
    printf("7 %% 2 = %d (resto)\n", x % 2); // 7 % 2 = 1

    // Truque clássico: verificar se um número é par ou ímpar
    int numero = 10;
    if (numero % 2 == 0) {
        printf("%d é par\n", numero);
    } else {
        printf("%d é ímpar\n", numero);
    }

    // Outro exemplo útil: módulo "dá a volta" em ciclos (ex.: dias da semana)
    int dia = 8;
    printf("Dia %d cai no dia da semana %d (0=Dom...6=Sab)\n", dia, dia % 7);
}

/* ============================================================
   3) OPERADORES DE ATRIBUIÇÃO  (=  +=  -=  *=  /=  %=  ++  --)
   ============================================================ */
void operadores_atribuicao() {
    int a, x, y;
    a = 5;

    // Atribuição em cadeia: avalia da direita pra esquerda
    y = x = 5; // primeiro x recebe 5, depois y recebe o valor de x (5)
    printf("a=%d  x=%d  y=%d\n", a, x, y);

    x += 1;      // equivale a: x = x + 1;
    y = y + 2;   // forma "manual" do mesmo tipo de operação
    printf("a=%d  x=%d  y=%d\n", a, x, y);

    x *= 2;      // equivale a: x = x * 2;
    printf("a=%d  x=%d  y=%d\n", a, x, y);

    // ----- Pré e pós incremento/decremento -----
    // --y   -> decrementa PRIMEIRO, depois usa o valor
    // y--   -> usa o valor PRIMEIRO, depois decrementa
    //
    // CUIDADO: modificar e atribuir a MESMA variável na mesma instrução
    // (ex.: y = --y;  ou  x = ++x * 2;) é tecnicamente comportamento
    // indefinido em C — o compilador pode até avisar sobre isso
    // (warning: operation on 'y' may be undefined [-Wsequence-point]).
    // Funciona "por sorte" na maioria dos compiladores, mas o certo é
    // NUNCA misturar ++ / -- com atribuição à própria variável na mesma
    // expressão. Vamos ver a forma correta:

    --y;              // decrementa y separadamente (equivale a y = y - 1)
    printf("y após --y: %d\n", y);

    ++x;              // incrementa x primeiro...
    x = x * 2;        // ...depois multiplica, em instruções separadas
    printf("x após ++x; x*2: %d\n", x);

    // O mesmo cuidado vale para pós-incremento: x = x++ * 2; também é
    // comportamento indefinido. Separe sempre em passos:
    int temp = x;   // guarda o valor atual (comportamento do pós-incremento)
    x = x + 1;       // agora sim incrementa
    x = temp * 2;    // usa o valor ANTIGO na conta, como o pós-incremento faria

    printf("a=%d  x=%d  y=%d\n", a, x, y);
}

/* ============================================================
   4) OPERADORES RELACIONAIS E LÓGICOS
   ============================================================
   Relacionais:  <   >   <=   >=   ==   !=
   Lógicos:      &&  (E)   ||  (OU)   !  (NÃO)
   Em C, o resultado de uma comparação é sempre um int: 0 (falso)
   ou 1 (verdadeiro).
   ============================================================ */
void operadores_relacionais_logicos() {
    int a, b, negacao;
    int c = 23;
    int d = c + 4; // 27

    a = (c < 20) || (d > c); // falso || verdadeiro -> 1 (verdadeiro)
    b = (c < 20) && (d > c); // falso && verdadeiro -> 0 (falso)
    negacao = !(c == 23);    // !(verdadeiro) -> 0 (falso)

    printf("a=%d  b=%d  negacao=%d\n", a, b, negacao);

    // Mais exemplos:
    printf("c == 23 ? %d\n", c == 23); // 1 (verdadeiro)
    printf("c != 23 ? %d\n", c != 23); // 0 (falso)
    printf("c >= d  ? %d\n", c >= d);  // 0 (falso, pois 23 < 27)

    // Curto-circuito: em (X && Y), se X já é falso, Y nem é avaliado.
    // Em (X || Y), se X já é verdadeiro, Y nem é avaliado.
    // Isso é usado, por exemplo, para evitar erros:
    int vetor[3] = {1, 2, 3};
    int indice = 5;
    if (indice >= 0 && indice < 3 && vetor[indice] > 0) {
        printf("Acesso seguro\n");
    } else {
        printf("Índice fora do intervalo, acesso evitado\n");
    }
}

/* ============================================================
   5) OPERADOR sizeof
   ============================================================
   sizeof retorna o tamanho (em bytes) que um tipo ou variável
   ocupa na memória. O resultado é do tipo size_t (inteiro sem
   sinal), então o format specifier correto no printf é %zu.
   ============================================================ */
void operador_sizeof() {
    int a;
    char c;
    float f;
    double d;
    long l;

    printf("sizeof(int)    = %zu bytes\n", sizeof(a));
    printf("sizeof(char)   = %zu bytes\n", sizeof(c));
    printf("sizeof(float)  = %zu bytes\n", sizeof(f));
    printf("sizeof(double) = %zu bytes\n", sizeof(d));
    printf("sizeof(long)   = %zu bytes\n", sizeof(l));

    // sizeof também funciona direto com o nome do tipo
    printf("sizeof(int) direto no tipo = %zu bytes\n", sizeof(int));

    // Útil para descobrir quantos elementos tem um array estático
    int vetor[10];
    int quantidade = sizeof(vetor) / sizeof(vetor[0]);
    printf("Quantidade de elementos no vetor: %d\n", quantidade);
}

/* ============================================================
   6) CONVERSÃO DE TIPO (CASTING)
   ============================================================
   Implícita: o compilador converte automaticamente (ex.: int
   vira float numa atribuição ou expressão).
   Explícita: o programador força a conversão usando (tipo).
   ============================================================ */
void conversao_tipo() {
    // Conversão implícita: 3 (int) é convertido automaticamente pra float
    float a = 3;
    printf("Conversao implicita int->float: %f\n", a);

    // Conversão explícita (cast): forçamos int -> double
    int inteiro = 7;
    double resultado = (double) inteiro / 2; // sem o cast, seria divisão inteira = 3
    printf("Com cast (double)7 / 2 = %f\n", resultado);

    double semCast = inteiro / 2; // divisão inteira primeiro (=3), depois vira double (3.0)
    printf("Sem cast, inteiro/2 vira double so no final = %f\n", semCast);

    // Cast de double pra int trunca a parte decimal (não arredonda!)
    double pi = 3.99;
    int piTruncado = (int) pi;
    printf("Cast (int)3.99 = %d (trunca, nao arredonda)\n", piTruncado);

    // Cast de char <-> int: char é internamente um número (código ASCII)
    char letra = 'A';
    int codigoAscii = (int) letra;
    printf("Codigo ASCII de '%c' = %d\n", letra, codigoAscii);

    int codigo = 66;
    char letraConvertida = (char) codigo;
    printf("Caractere do codigo %d = '%c'\n", codigo, letraConvertida);
}

int main(void) {
    // Descomente a função que quiser testar:
    variaveis();
    // operadores_aritmeticos();
    // operadores_atribuicao();
    // operadores_relacionais_logicos();
    // operador_sizeof();
    // conversao_tipo();

    return 0; // main deve retornar int (não void) segundo o padrão C
}