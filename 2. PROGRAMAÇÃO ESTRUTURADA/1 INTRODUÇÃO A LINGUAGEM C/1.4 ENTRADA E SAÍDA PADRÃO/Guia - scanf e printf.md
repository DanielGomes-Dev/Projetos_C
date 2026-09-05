# Guia de referência — `scanf` e `printf`

Nota de uso pertinente ao tópico 1.4, reunindo num só lugar tudo que costuma gerar dúvida/bug em `scanf`: os especificadores por tipo, como buscar cada forma de dado, o problema clássico do `\n` que sobra no buffer, e uma alternativa mais segura. Todos os códigos abaixo são exemplos próprios (compiláveis), não transcrição do livro.

## 1. Por que `scanf` precisa de `&`

`printf` recebe **valores** (o que já está pronto para imprimir). `scanf` precisa **escrever de volta** na variável do chamador — e C passa tudo por valor, então a única forma de uma função alterar uma variável de quem a chamou é receber o **endereço** dela e escrever através de um ponteiro. Por isso todo argumento de `scanf` (exceto quando já é um ponteiro, como `char *nome` para `%s`) leva `&`:

```c
int idade;
scanf("%d", &idade);      // certo: passa o endereço de idade

char nome[50];
scanf("%s", nome);        // certo: nome já "é" um endereço (decai para ponteiro)
scanf("%s", &nome[0]);    // equivalente, mais explícito
```

Esquecer o `&` num tipo escalar (`scanf("%d", idade);`) é o erro mais comum: compila com aviso, mas em geral gera *undefined behavior* (o `scanf` tenta escrever no endereço que por acaso está guardado em `idade`, que é lixo).

## 2. Tabela de especificadores

### `printf` (saída — recebe valores)

| Especificador | Tipo | Observação |
|---|---|---|
| `%d`, `%i` | `int` | decimal com sinal |
| `%u` | `unsigned int` | decimal sem sinal |
| `%ld`, `%lu` | `long`, `unsigned long` | |
| `%lld`, `%llu` | `long long`, `unsigned long long` | (C99) |
| `%f` | `double` (também serve para `float`, que é promovido) | ponto fixo, 6 casas por padrão |
| `%e` / `%E` | `double` | notação científica (`1.234560e+02`) |
| `%g` / `%G` | `double` | escolhe `%f` ou `%e`, o que for mais compacto |
| `%c` | `int` (char promovido) | um caractere |
| `%s` | `char *` | string terminada em `\0` |
| `%x` / `%X` | `unsigned int` | hexadecimal minúsculo/maiúsculo |
| `%o` | `unsigned int` | octal |
| `%p` | `void *` | endereço de ponteiro |
| `%%` | — | imprime um `%` literal |

### `scanf` (entrada — recebe **endereços**)

| Especificador | Escreve em | Observação |
|---|---|---|
| `%d`, `%i` | `int *` | `%i` também aceita `0x`/`0` como prefixo hex/octal na entrada; `%d` não |
| `%u` | `unsigned int *` | |
| `%ld` / `%lu` | `long *` / `unsigned long *` | |
| `%f`, `%e`, `%g` | `float *` | **os três são idênticos em `scanf`** |
| `%lf`, `%le`, `%lg` | `double *` | o `l` é obrigatório para `double` (diferente de `printf`, onde `%f` já serve para os dois) |
| `%Lf` | `long double *` | |
| `%c` | `char *` | lê **1 caractere, inclusive espaço/`\n`** — não pula brancos |
| `%s` | `char *` (vetor) | lê uma "palavra" (pula brancos antes, para no próximo espaço/`\n`/EOF) — **sem checar limite do vetor** |
| `%Ns` | `char *` | com `N` = número de colunas, ex. `%19s` lê no máximo 19 chars + `\0` — forma segura de usar `%s` |
| `%x`, `%o` | `unsigned int *` | hexadecimal / octal |
| `%[...]` | `char *` | conjunto de caracteres aceitos (ver seção 6) |
| `%p` | `void **` | lê um endereço |
| `%n` | `int *` | não lê nada; grava quantos caracteres já foram consumidos até aqui |

> Erro clássico do especificador errado: `int n; float f; scanf("%f", &n);` compila, mas grava bytes de ponto flutuante sobre um `int` — lixo garantido. E `scanf("%d", &f)` na direção oposta é igualmente errado. O tipo do especificador **tem que bater exatamente** com o tipo do ponteiro.

## 3. Largura de campo e precisão

```c
printf("%5d\n", 42);      // "   42"  (largura mínima 5, alinhado à direita)
printf("%-5d|\n", 42);    // "42   |" (- alinha à esquerda)
printf("%05d\n", 42);     // "00042"  (0 preenche com zeros)
printf("%.2f\n", 3.14159);// "3.14"   (2 casas decimais)
printf("%8.2f\n", 3.14159); // "    3.14" (largura 8, 2 casas)

scanf("%5d", &n);         // lê no máximo 5 dígitos
scanf("%19s", buf);       // lê no máximo 19 caracteres (+ '\0'), evita overflow em buf[20]
```

## 4. Sequências de escape usadas em `printf`/strings

| Escape | Significado |
|---|---|
| `\n` | nova linha |
| `\t` | tabulação |
| `\r` | retorno de carro |
| `\"` | aspas duplas literais |
| `\\` | barra invertida literal |
| `\0` | caractere nulo (fim de string) |

## 5. O retorno de `scanf` — a forma certa de validar entrada

`scanf` devolve **quantos itens ele conseguiu ler com sucesso** (ou `EOF` se nada pôde ser lido por fim de entrada). Ignorar esse retorno é a causa mais comum de loop infinito quando o usuário digita algo que não é número:

```c
#include <stdio.h>

int main(void) {
    int n;

    printf("Digite um número inteiro: ");
    while (scanf("%d", &n) != 1) {
        // entrada inválida: o token errado ainda está no buffer, tem que descartar
        printf("Valor inválido, tente de novo: ");
        while (getchar() != '\n')   // descarta o resto da linha ruim
            ;
    }
    printf("Você digitou %d\n", n);
    return 0;
}
```

Padrão muito comum para ler *até o fim da entrada* (Ctrl+D / Ctrl+Z ou fim de arquivo):

```c
int x, soma = 0;
while (scanf("%d", &x) == 1)
    soma += x;
printf("Soma = %d\n", soma);
```

Lendo vários valores na mesma chamada — todos precisam ser lidos para o retorno ser `2`:

```c
int a, b;
if (scanf("%d %d", &a, &b) == 2)
    printf("Produto = %d\n", a * b);
```

## 6. O problema clássico: `\n` residual no buffer

`%d`, `%f`, `%u` etc. **pulam espaços em branco antes** de ler o número, mas **não consomem o `\n`** deixado depois que o usuário aperta Enter. `%c` e `%[...]`, ao contrário, **não pulam brancos automaticamente** — então o próximo `%c` depois de um `%d` costuma "ler" esse `\n` sobrando em vez de esperar um caractere novo:

```c
int idade;
char sexo;

printf("Idade: ");
scanf("%d", &idade);
printf("Sexo (M/F): ");
scanf("%c", &sexo);      // BUG: lê o '\n' deixado pelo scanf("%d") anterior, não espera digitação
```

Três formas de resolver, da mais simples à mais explícita:

```c
// 1) espaço antes de %c no formato: pula QUALQUER quantidade de brancos (inclusive nenhum)
scanf(" %c", &sexo);

// 2) descartar explicitamente 1 caractere (o \n) antes de ler o char
getchar();
scanf("%c", &sexo);

// 3) descartar tudo que sobrou até (e incluindo) a próxima nova linha
int c;
while ((c = getchar()) != '\n' && c != EOF)
    ;
```

> **Nunca use `fflush(stdin)`** para "limpar" o teclado — `fflush` só tem comportamento definido para streams de **saída**; em `stdin` é comportamento indefinido (funciona por acidente em alguns compiladores Windows, mas não é C padrão).

O mesmo problema aparece entre `%d`/`%f` e `%s` misturado com leitura de linha inteira — `%s` também pula brancos antes de começar, então ele "engole" o `\n` residual normalmente; o caso realmente perigoso é sempre **`%c` logo depois de `%d`/`%f`/`%s`**.

## 7. `%[...]` — conjuntos de caracteres (lendo texto com espaços)

`%s` para no primeiro espaço — não serve para ler uma linha inteira como "João da Silva". `%[...]` (ou melhor, `fgets`, seção 8) resolve isso:

```c
char linha[100];

scanf(" %99[^\n]", linha);   // lê tudo até (sem incluir) o próximo '\n'
// %[^\n]  = "aceite qualquer caractere que NÃO seja \n"
// o espaço antes do % pula o \n residual de uma leitura anterior

char letras[50];
scanf("%49[a-zA-Z]", letras); // lê só sequências de letras (maiúsculas ou minúsculas)
```

`^` logo após `[` **nega** o conjunto (“qualquer coisa exceto”); sem `^`, é uma lista de aceitação (“só isto”). Sempre informe uma largura máxima (`%99[^\n]`) — sem largura, `%[...]` também estoura buffer como `%s`.

## 8. Separadores customizados no formato

Qualquer caractere no formato que não seja `%` nem espaço tem que **casar literalmente** com a entrada:

```c
int h, m;
scanf("%d:%d", &h, &m);      // aceita só "14:30", não aceita "14 30" nem "14-30"

int dia, mes, ano;
scanf("%d/%d/%d", &dia, &mes, &ano); // "25/12/2024"
```

Um espaço em branco no formato (não confundir com o `%` de conversão) casa com **zero ou mais** brancos na entrada — por isso `scanf("%d %d", &a, &b)` aceita tanto `"3 4"` quanto `"3\n4"` quanto `"3    4"`.

## 9. Alternativa mais segura: `fgets` + `sscanf`/`strtol`/`strtod`

Para entrada vinda de usuário (não de arquivo confiável), o padrão recomendado é ler a linha inteira com `fgets` (que respeita o tamanho do buffer) e só então interpretar o conteúdo — assim um erro de formato nunca deixa lixo no `stdin` para a próxima leitura:

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char linha[100];
    int idade;

    printf("Idade: ");
    if (fgets(linha, sizeof linha, stdin) != NULL) {
        if (sscanf(linha, "%d", &idade) == 1)
            printf("Você tem %d anos.\n", idade);
        else
            printf("Entrada inválida.\n");
    }

    // strtol/strtod detectam erro de conversão de forma mais fina que sscanf
    char *fim;
    long valor = strtol(linha, &fim, 10);
    if (fim == linha)
        printf("Nenhum número encontrado.\n");
    else
        printf("Número lido: %ld\n", valor);

    return 0;
}
```

`fgets(buf, tamanho, stdin)` **inclui o `\n` no buffer** se ele coube (diferente de `gets`, que é inseguro e foi removida do padrão C11 — nunca usar); é comum remover esse `\n` manualmente:

```c
linha[strcspn(linha, "\n")] = '\0';  // strcspn acha a posição do \n (ou do fim da string)
```

## 10. Exemplo completo — menu que lê tipos variados

Programa único juntando `int`, `float`/`double`, `char` e string, mostrando os três pontos de atenção (retorno de `scanf`, `\n` residual, largura em `%s`):

```c
#include <stdio.h>

int main(void) {
    char nome[50];
    int idade;
    double altura;
    char inicial;

    printf("Nome: ");
    scanf("%49s", nome);              // string, sem estourar o buffer

    printf("Idade: ");
    while (scanf("%d", &idade) != 1) {
        while (getchar() != '\n') ;
        printf("Digite um inteiro válido: ");
    }

    printf("Altura (m): ");
    scanf("%lf", &altura);            // double exige %lf em scanf

    printf("Inicial do sobrenome: ");
    scanf(" %c", &inicial);           // espaço antes de %c descarta o \n residual

    printf("\n--- Resumo ---\n");
    printf("%-10s %3d anos, %.2fm, inicial '%c'\n", nome, idade, altura, inicial);

    return 0;
}
```

## 11. Checklist rápido de erros comuns

- [ ] Esqueceu o `&` num tipo escalar (`int`, `float`, `char`, mas não em vetor/`char[]`)
- [ ] Usou `%f` para ler `double` em vez de `%lf`
- [ ] Colocou `%c` logo depois de `%d`/`%f`/`%s` sem tratar o `\n` residual
- [ ] Usou `%s` sem limite de largura (`%s` em vez de `%49s`) — risco de estouro de buffer
- [ ] Ignorou o valor de retorno de `scanf` (não detecta entrada inválida → loop infinito ou lixo)
- [ ] Usou `gets` (removida do C11; usar `fgets`)
- [ ] Tentou `fflush(stdin)` para limpar o buffer (comportamento indefinido)
