#include <stdio.h>

/* ============================================================
   CONTROLE DE FLUXO: LAÇOS (while, for, do-while, break, continue)
   ============================================================
   Procedimentos ITERATIVOS são aqueles que repetem uma sequência
   de comandos várias vezes. O exemplo clássico é o cálculo de
   fatorial:

       0! = 1
       n! = n × (n-1) × (n-2) × ... × 2 × 1

   Vamos implementar o fatorial de três formas diferentes (while,
   for, do-while) para comparar as construções de laço da
   linguagem C.
   ============================================================ */


/* ============================================================
   1) while — teste de encerramento no INÍCIO do laço
   ============================================================
   Forma geral:
       while (expr_booleana) {
           bloco de comandos;
       }

   Funcionamento: antes de CADA execução do bloco, expr_booleana
   é avaliada. Enquanto for verdadeira (diferente de 0), o bloco
   roda. Quando for falsa (igual a 0), o laço para e a execução
   segue no comando logo após o bloco.

   IMPORTANTE: como o teste é feito ANTES, se a condição já for
   falsa na primeira avaliação, o bloco não executa nenhuma vez.
   ============================================================ */
void fatorial_while() {
    int i;
    int n;
    int f = 1;

    printf("Digite um numero inteiro nao negativo: ");
    scanf("%d", &n);

    // Calcula o fatorial
    i = 1;
    while (i <= n) {   // repete enquanto i for menor ou igual a n
        f = f * i;     // acumula o produto
        i++;           // ATENÇÃO: se esquecermos disso, o laço nunca termina!
    }

    printf("Fatorial = %d\n", f);
}

/* ============================================================
   2) for — mais compacto, muito usado quando sabemos quantas
      vezes o laço deve rodar
   ============================================================
   Forma geral:
       for (expr_inicial; expr_booleana; expr_incremento) {
           bloco de comandos;
       }

   É EQUIVALENTE a este while:
       expr_inicial;
       while (expr_booleana) {
           bloco de comandos;
           expr_incremento;
       }

   Ou seja:
   - expr_inicial roda 1 vez, antes de tudo (normalmente inicializa
     a variável de controle do laço, ex.: i = 1)
   - expr_booleana é testada antes de cada iteração
   - expr_incremento roda ao FINAL de cada iteração, antes do
     próximo teste da condição (normalmente incrementa/decrementa
     a variável de controle)
   ============================================================ */
void fatorial_for() {
    int i;
    int n;
    int f = 1;

    printf("Digite um numero inteiro nao negativo: ");
    scanf("%d", &n);

    // As três partes do for ficam juntas, deixando claro de cara
    // qual é a variável de controle do laço e seus limites.
    for (i = 1; i <= n; i++) {
        f = f * i;
    }
    // Se o corpo tivesse um único comando, as chaves seriam
    // opcionais, assim como no if — mas usá-las deixa o código
    // mais fácil de manter (por exemplo, se depois quisermos
    // adicionar um printf de depuração dentro do laço).

    printf("Fatorial = %d\n", f);
}

/* ============================================================
   3) do-while — teste de encerramento no FIM do laço
   ============================================================
   Forma geral:
       do {
           bloco de comandos;
       } while (expr_booleana);

   Diferença crucial em relação a while/for: o bloco de comandos
   SEMPRE executa pelo menos UMA vez, porque a condição só é
   testada DEPOIS da primeira execução.

   Muito útil para validar entradas do usuário: queremos pedir o
   valor pelo menos uma vez, e repetir o pedido só se o valor for
   inválido.
   ============================================================ */
void fatorial_do_while() {
    int i;
    int n;
    int f = 1;

    // Repete a pergunta enquanto o usuário digitar um valor
    // negativo (fatorial de negativo não é definido)
    do {
        printf("Digite um valor inteiro nao negativo: ");
        scanf("%d", &n);
    } while (n < 0);
    // A leitura acontece pelo menos uma vez, e só se repete se
    // a validação (n < 0) falhar.

    for (i = 1; i <= n; i++) {
        f = f * i;
    }

    printf("Fatorial = %d\n", f);
}

/* ============================================================
   4) while vs. for vs. do-while — quando usar cada um
   ============================================================
   - for:       quando sabemos (ou conseguimos calcular) de
                antemão quantas vezes o laço deve rodar, ou temos
                uma variável de controle clara (ex.: percorrer um
                vetor de índice 0 a n-1).
   - while:     quando a condição de parada não está ligada a um
                contador simples, e pode não ser conhecida antes
                de começar (ex.: ler valores até encontrar um
                sentinela).
   - do-while:  quando o bloco PRECISA rodar pelo menos uma vez
                antes de qualquer teste (ex.: menus, validação de
                entrada do usuário).
   ============================================================ */
void exemplo_soma_ate_zero() {
    // Exemplo de while "puro": não sabemos quantas iterações
    // serão necessárias — depende do que o usuário digitar.
    int valor;
    int soma = 0;

    printf("Digite numeros inteiros (0 para parar):\n");
    scanf("%d", &valor);

    while (valor != 0) {
        soma += valor;
        scanf("%d", &valor);
    }

    printf("Soma total: %d\n", soma);
}

/* ============================================================
   5) break — interrompe e finaliza o laço imediatamente
   ============================================================
   Quando o comando break é executado dentro de um laço (while,
   for ou do-while), o laço é interrompido NA HORA, e a execução
   continua no primeiro comando logo APÓS o laço.
   ============================================================ */
void exemplo_break() {
    int i;

    for (i = 0; i < 10; i++) {
        if (i == 5) {
            break;   // ao chegar em i==5, sai do for imediatamente
        }
        printf("%d ", i);
    }
    printf("fim\n");

    // Saída: 0 1 2 3 4 fim
    // Repare que o 5 nunca chega a ser impresso: o break acontece
    // ANTES do printf daquela iteração.
}

/* ============================================================
   6) continue — pula para a PRÓXIMA iteração, sem finalizar o laço
   ============================================================
   Diferente do break: o continue não termina o laço. Ele apenas
   interrompe a iteração ATUAL (pulando o restante do bloco) e
   faz o laço avançar para a próxima iteração normalmente.
   ============================================================ */
void exemplo_continue() {
    int i;

    for (i = 0; i < 10; i++) {
        if (i == 5) {
            continue;   // pula o printf só quando i==5, mas o for continua
        }
        printf("%d ", i);
    }
    printf("fim\n");

    // Saída: 0 1 2 3 4 6 7 8 9 fim
    // O 5 é o único número que "falta": ele não foi impresso,
    // mas o laço seguiu rodando normalmente até i chegar a 10.
}

/* ============================================================
   7) CUIDADO: continue dentro de while pode causar loop infinito
   ============================================================
   No for, o continue pula para expr_incremento antes de testar
   a condição de novo — então a variável de controle continua
   avançando normalmente.

   Já no while, NÃO existe uma "expr_incremento" automática: o
   continue pula direto para o teste da condição booleana. Se o
   incremento da variável de controle estiver DEPOIS do continue
   no corpo do laço, ele nunca vai ser executado quando a condição
   do continue for satisfeita — e o laço pode nunca terminar.
   ============================================================ */
void exemplo_continue_incorreto_NAO_EXECUTAR() {
    // ATENÇÃO: esta função tem um loop infinito DE PROPÓSITO,
    // só para fins didáticos. NÃO a chame no main sem entender
    // o problema, ou o programa vai travar!

    int i = 0;
    while (i < 10) {
        if (i == 5) {
            continue;   // BUG: pula o i++ lá embaixo sempre que i==5
        }
        printf("%d ", i);
        i++;            // nunca executa quando i chega a 5!
    }
    // Quando i chega a 5: entra no if, executa continue, volta
    // para o "while (i < 10)". Mas i AINDA VALE 5 (o i++ foi
    // pulado), então a condição continua verdadeira, e caímos
    // no if de novo, indefinidamente. Loop infinito!
    printf("fim\n"); // esta linha NUNCA é alcançada
}

/* ------------------------------------------------------------
   Versão corrigida do exemplo acima: basta garantir que o
   incremento aconteça ANTES do continue, ou usar uma estrutura
   que não dependa da ordem (como o for, que sempre roda o
   incremento antes do próximo teste).
   ------------------------------------------------------------ */
void exemplo_continue_corrigido() {
    int i = 0;
    while (i < 10) {
        if (i == 5) {
            i++;        // incrementa ANTES do continue
            continue;
        }
        printf("%d ", i);
        i++;
    }
    printf("fim\n");
    // Saída: 0 1 2 3 4 6 7 8 9 fim  (mesmo resultado do exemplo_continue)
}

int main(void) {
    // Descomente a função que quiser testar (a maioria pede entrada pelo teclado):
    // fatorial_while();
    // fatorial_for();
    // fatorial_do_while();
    // exemplo_soma_ate_zero();
    exemplo_break();
    exemplo_continue();
    // exemplo_continue_incorreto_NAO_EXECUTAR(); // CUIDADO: loop infinito proposital!
    exemplo_continue_corrigido();

    return 0;
}