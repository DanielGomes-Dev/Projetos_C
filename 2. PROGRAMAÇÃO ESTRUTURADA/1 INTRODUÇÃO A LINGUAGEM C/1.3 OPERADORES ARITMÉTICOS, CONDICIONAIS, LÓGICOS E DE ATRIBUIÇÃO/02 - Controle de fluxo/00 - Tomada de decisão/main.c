#include <stdio.h>

/* ============================================================
   CONTROLE DE FLUXO: if / else
   ============================================================
   Até agora vimos programas que executam comandos em sequência,
   um atrás do outro. Para programas mais elaborados, precisamos
   de mecanismos que controlem O QUE é executado (decisões) e
   QUANTAS VEZES algo é executado (laços/repetição).

   Este arquivo cobre o comando de decisão: if / else.

   Forma geral:
       if (expressao) {
           bloco de comandos 1;
       } else {
           bloco de comandos 2;
       }

   Regra de ouro: se "expressao" for DIFERENTE DE ZERO (ou seja,
   "verdadeira"), o bloco 1 é executado. Se for ZERO ("falsa"), o
   bloco 2 (do else) é executado, se existir.

   Em C não existe tipo "bool" nativo (antes do C99/C23): qualquer
   valor inteiro diferente de 0 é tratado como verdadeiro, e 0 é
   sempre falso. Por isso "if (a)" é equivalente a "if (a != 0)".
   ============================================================ */


/* ------------------------------------------------------------
   1) if / else simples
   ------------------------------------------------------------ */
void par_ou_impar() {
    int a;

    printf("Digite um numero inteiro: ");
    scanf("%d", &a);

    if (a % 2 == 0) {
        printf("O numero fornecido e' par!\n");
    } else {
        printf("O numero fornecido e' impar!\n");
    }
}

/* ------------------------------------------------------------
   2) Chaves são opcionais para um único comando
   ------------------------------------------------------------
   Se o bloco tem só UM comando, as chaves podem ser omitidas:

       if (expr)
           comando1;
       else
           comando2;

   CUIDADO: isso é uma faca de dois gumes. Funciona, mas é fácil
   esquecer as chaves depois ao adicionar um segundo comando —
   veja o exemplo comentado mais abaixo, na seção "erro clássico".
   ------------------------------------------------------------ */
void maior_idade() {
    int idade;

    printf("Digite sua idade: ");
    scanf("%d", &idade);

    if (idade >= 18)
        printf("Maior de idade\n");   // sem chaves: só um comando
    else
        printf("Menor de idade\n");   // sem chaves: só um comando
}

/* ------------------------------------------------------------
   3) if aninhado (nested if)
   ------------------------------------------------------------
   Podemos colocar um if dentro de outro if. Aqui, o if de dentro
   só é avaliado se a condição do if de fora for verdadeira.
   ------------------------------------------------------------ */
void dois_numeros_pares_aninhado() {
    int a, b;

    printf("Digite dois numeros inteiros: ");
    scanf("%d %d", &a, &b);

    // Como cada if tem só UM comando associado, as chaves são
    // opcionais aqui — mas vamos usá-las para deixar claro.
    if (a % 2 == 0) {
        if (b % 2 == 0) {
            printf("Foram digitados dois numeros pares!\n");
        }
    }
    // Se 'a' for ímpar, o if de dentro nem chega a ser avaliado.
}

/* ------------------------------------------------------------
   4) A mesma lógica, usando && (E lógico)
   ------------------------------------------------------------
   O exemplo acima também pode ser escrito com uma única condição
   combinando as duas checagens com &&. Produz resultado idêntico
   e costuma ser mais legível para casos simples como este.
   ------------------------------------------------------------ */
void dois_numeros_pares_and() {
    int a, b;

    printf("Digite dois numeros inteiros: ");
    scanf("%d %d", &a, &b);

    if ((a % 2 == 0) && (b % 2 == 0)) {
        printf("Foram digitados dois numeros pares!\n");
    }
}

/* ------------------------------------------------------------
   5) O ERRO CLÁSSICO: "dangling else" (else "pendurado")
   ------------------------------------------------------------
   Regra da linguagem C: um "else" sempre se associa ao "if" mais
   PRÓXIMO que ainda não tem um else. Isso pode não bater com o
   que a IDENTAÇÃO (o recuo visual) do código sugere — e é uma
   fonte clássica de bugs.

   Objetivo pretendido: imprimir "agradavel" se 20 < temp < 30, e
   "muito quente" se temp >= 30.
   ------------------------------------------------------------ */
void temperatura_v1_incorreta() {
    int temp;

    printf("Digite a temperatura: ");
    scanf("%d", &temp);

    // A identação abaixo SUGERE que o else está ligado ao
    // "if (temp < 30)", mas na verdade, sem chaves, o else se
    // liga ao if MAIS PRÓXIMO: "if (temp > 20)".
    if (temp < 30)
        if (temp > 20)
            printf("Temperatura agradavel\n");
        else
            printf("Temperatura muito quente\n");

    // Teste mentalmente com temp = 5:
    //   temp < 30?  sim -> entra
    //   temp > 20?  nao -> vai para o else ATRELADO a este if
    //   Resultado: imprime "Temperatura muito quente"
    // ... só que 5 graus não tem nada de "muito quente"!
    // O programa está tecnicamente correto em C, mas
    // logicamente ERRADO em relação à intenção do programador.
    //
    // Boa notícia: compiladores modernos ajudam! O gcc, com
    // -Wall, emite justamente para este código o aviso:
    //   "warning: suggest explicit braces to avoid ambiguous
    //    'else' [-Wdangling-else]"
    // Ou seja, o próprio compilador sugere usar chaves explícitas
    // quando percebe esse tipo de ambiguidade.
}

/* ------------------------------------------------------------
   6) Corrigindo o dangling else com chaves explícitas
   ------------------------------------------------------------
   A lição: sempre que a associação entre if e else não for
   ÓBVIA, use chaves — mesmo que o bloco tenha um único comando.
   Isso remove qualquer ambiguidade visual e lógica.
   ------------------------------------------------------------ */
void temperatura_v2_correta() {
    int temp;

    printf("Digite a temperatura: ");
    scanf("%d", &temp);

    if (temp < 30) {
        if (temp > 20) {
            printf("Temperatura agradavel\n");
        }
    } else {
        printf("Temperatura muito quente\n");
    }

    // Agora, com temp = 5:
    //   temp < 30? sim -> entra no bloco externo
    //   temp > 20? nao -> não imprime nada aqui dentro
    //   o else agora pertence ao if de FORA, então não é
    //   executado (pois temp < 30 era verdadeiro)
    //   Resultado: nenhuma mensagem é impressa para temp = 5.
    // (ainda não é o comportamento "ideal" para temp bem baixo,
    // mas já bate com a lógica que o código aparenta ter — o
    // próximo exemplo com else-if resolve isso de vez)
}

/* ------------------------------------------------------------
   7) Cadeia else-if (não existe "elseif" como palavra reservada)
   ------------------------------------------------------------
   C não tem um comando "elseif" na gramática da linguagem. O que
   existe é um "else" seguido de outro "if" — e como cada if pode
   ter um único comando associado sem precisar de chaves, dá pra
   encadear várias condições em sequência, uma reaproveitando o
   "senão" da anterior.
   ------------------------------------------------------------ */
void temperatura_v3_faixas() {
    int temp;

    printf("Digite a temperatura: ");
    scanf("%d", &temp);

    if (temp < 10) {
        printf("Temperatura muito fria\n");
    } else if (temp < 20) {
        printf("Temperatura fria\n");
    } else if (temp < 30) {
        printf("Temperatura agradavel\n");
    } else {
        printf("Temperatura muito quente\n");
    }

    // Importante: as condições são testadas em ORDEM, e a
    // primeira que for verdadeira "ganha" — as seguintes nem
    // são avaliadas. Por isso "temp < 20" já garante, implicita-
    // mente, que temp >= 10 (senão já teria caído no primeiro if).
}

/* ------------------------------------------------------------
   8) Classificação de nota (outro exemplo de cadeia else-if)
   ------------------------------------------------------------ */
void classifica_nota() {
    double nota;

    printf("Digite uma nota de 0 a 10: ");
    scanf("%lf", &nota);

    if (nota < 0 || nota > 10) {
        printf("Nota invalida!\n");
    } else if (nota < 5.0) {
        printf("Reprovado\n");
    } else if (nota < 7.0) {
        printf("Recuperacao\n");
    } else if (nota < 9.0) {
        printf("Aprovado\n");
    } else {
        printf("Aprovado com destaque\n");
    }
}

/* ------------------------------------------------------------
   9) Escopo de bloco: variáveis "somem" fora das chaves
   ------------------------------------------------------------
   Cada par de chaves { } define um BLOCO. Uma variável declarada
   dentro de um bloco só existe (é "visível") dentro dele. Ao sair
   do bloco, a variável deixa de existir.
   ------------------------------------------------------------ */
void escopo_de_bloco() {
    int n = 5;

    if (n > 0) {
        int i = 10;               // 'i' só existe dentro deste bloco
        printf("Dentro do if, i = %d\n", i);
    }

    // printf("%d", i); // ERRO de compilação: 'i' não existe aqui fora

    printf("Fora do if, n ainda vale %d\n", n); // 'n' existe na função toda

    // Boa prática: declare cada variável o mais perto possível
    // de onde ela é usada, dentro do menor bloco necessário.
}

/* ------------------------------------------------------------
   10) Operador condicional (ternário) ?:
   ------------------------------------------------------------
   É um operador que "encaixa" um if-else simples dentro de uma
   expressão. Forma geral:

       condicao ? expressao_se_verdadeiro : expressao_se_falso

   Muito usado para atribuições curtas — mas não abuse dele em
   condições muito complexas, pois piora a legibilidade.
   ------------------------------------------------------------ */
void operador_ternario() {
    int a = 7, b = 12;

    // Forma tradicional com if-else:
    int maximo_if;
    if (a > b) {
        maximo_if = a;
    } else {
        maximo_if = b;
    }

    // Mesmo resultado, em uma linha, com o operador ternário:
    int maximo_ternario = (a > b) ? a : b;

    printf("Maximo (if-else):  %d\n", maximo_if);
    printf("Maximo (ternario):  %d\n", maximo_ternario);

    // Outro exemplo comum: mensagem par/ímpar em uma linha só
    int n = 15;
    printf("%d e' %s\n", n, (n % 2 == 0) ? "par" : "impar");

    // Também pode ser usado dentro de outra expressão, não só
    // em atribuições diretas:
    int x = 4, y = 9;
    printf("O maior entre %d e %d, ao quadrado, e' %d\n",
           x, y, (x > y ? x : y) * (x > y ? x : y));
}

int main(void) {
    // Descomente a função que quiser testar (a maioria pede entrada pelo teclado):
    // par_ou_impar();
    // maior_idade();
    // dois_numeros_pares_aninhado();
    // dois_numeros_pares_and();
    // temperatura_v1_incorreta();
    // temperatura_v2_correta();
    // temperatura_v3_faixas();
    // classifica_nota();
    escopo_de_bloco();
    // operador_ternario();

    return 0;
}