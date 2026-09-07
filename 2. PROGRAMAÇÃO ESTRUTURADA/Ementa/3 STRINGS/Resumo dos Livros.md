# Resumo dos Livros — 3. Strings

## Celes — Introdução a Estruturas de Dados (Cap. 7, "Cadeias de caracteres")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção: strings **têm** capítulo próprio no Celes (Cap. 7), e é um dos mais ricos do livro — segue a mesma estratégia pedagógica de "implementar a função à mão, depois mostrar a equivalente da biblioteca padrão" usada em outros capítulos.

**Convenção básica**: uma cadeia é um vetor de `char` terminado em `'\0'`; percorrer caractere a caractere até achar o `'\0'` é o padrão universal (`for (i=0; s[i]!='\0'; i++) ...`).

**Implementações à mão, depois substituídas pela função padrão equivalente**:
| Função própria do livro | Equivalente em `string.h` |
|---|---|
| `comprimento(s)` | `strlen` |
| `copia(dest, orig)` | `strcpy` |
| `concatena(dest, orig)` | `strcat` |
| `compara(s1, s2)` | `strcmp` |

Cada uma é implementada primeiro de forma iterativa e depois **recursiva** (usando a definição recursiva de string: "vazia, ou um caractere seguido de uma subcadeia") — inclusive uma versão que imprime a cadeia **de trás para a frente** só invertendo a ordem de duas linhas (`imprime_inv`, chama a recursão *antes* de imprimir o caractere atual). O livro explicitamente recomenda usar as funções de `string.h` no código real — as implementações são só para entender a mecânica.

**Constante string vs. vetor local** — distinção que o livro trata com bastante cuidado, incluindo um "gotcha" clássico:
```c
char s1[] = "Rio de Janeiro";   /* vetor local, 15 bytes, MUTÁVEL: s1[0]='X' é válido */
char *s2  = "Rio de Janeiro";   /* ponteiro para constante, 4/8 bytes: s2[0]='X' é ERRO */
```
`sizeof(s1)` (tamanho do vetor, 15) e `sizeof(s2)` (tamanho de um ponteiro) dão valores completamente diferentes — o livro usa isso para mostrar concretamente a diferença entre "é um vetor" e "aponta para uma constante".

**Vetor de strings**: duas estratégias comparadas — matriz fixa `char alunos[50][81]` (simples, mas desperdiça memória se os nomes forem curtos ou a turma pequena) vs. vetor de ponteiros com cada string alocada dinamicamente do tamanho exato (`char *alunos[50]`, cada `alunos[i] = malloc(strlen(nome)+1)`) — a estratégia preferida do livro, pela economia de memória.

**Alocação dinâmica de string**: função `duplica(char *s)` que aloca `strlen(s)+1` bytes (o `+1` para o `'\0'`) e usa `strcpy` para copiar — deixando explícito que quem chama `duplica` é responsável por dar `free` depois.

## K&R — C: A Linguagem de Programação (Cap. 5, seção 5.5)
A seção "Apontadores de Caractere e Funções" abre com a definição central: uma cadeia como `"Eu sou uma cadeia"` é "um arranjo de caracteres. Na representação interna, o compilador termina o arranjo com o caractere `\0` para que programas possam encontrar o fim." Isso implica que "o tamanho de armazenamento é [...] um a mais do que o número de caracteres entre aspas".

O texto distingue explicitamente dois usos de `char *`: quando uma cadeia literal aparece como argumento (`printf("primeiro programa\n")`), o que é passado é um apontador para o arranjo de caracteres; e quando se escreve `char *mensagem; mensagem = "...";`, "isto não é uma cópia da cadeia; somente apontadores estão envolvidos" — o livro frisa que "C não fornece qualquer operador para processar uma cadeia de caracteres como um todo", daí a necessidade das funções de `string.h`.

O capítulo então desenvolve `strcpy(s, t)` (copia `t` em `s`) em três versões progressivas — com índices de arranjo, com ponteiros, e com o incremento movido para dentro do teste do laço (`while ((*s++ = *t++) != '\0')`) — e `strcmp(s, t)`, que "retorna um valor negativo, zero ou positivo se `s` é lexicograficamente menor, igual ou maior que `t`", obtido "pela subtração dos caracteres na primeira posição onde `s` e `t` são diferentes":

```c
strcmp(s, t)                    /* retorna <0 se s<t, 0 se s==t, >0 se s>t */
char *s, *t;
{
    for (; *s == *t; s++, t++)
        if (*s == '\0')
            return (0);
    return (*s - *t);
}
```

Em capítulo anterior (2), o livro também apresenta `strlen(s)`, que percorre o vetor contando caracteres até encontrar `'\0'` e devolve essa contagem — a base de todas as demais funções de string, que costumam usar `strlen` para saber quanto espaço alocar antes de copiar.

## Síntese
Os dois livros convergem no ponto essencial da linguagem C: string não é um tipo, é uma convenção (vetor de `char` + terminador `'\0'`), e por isso toda manipulação — cópia, comparação, concatenação — precisa ser feita caractere a caractere via função de biblioteca, nunca por atribuição direta (`s1 = s2;` copia o *ponteiro*, não o conteúdo). Os dois livros até convergem no mesmo conjunto de 4 funções centrais (`strlen`/`strcpy`/`strcat`/`strcmp`) e nas mesmas implementações de referência; Celes vai além ao mostrar cada uma também em versão recursiva e ao comparar duas estratégias de vetor de strings (matriz fixa vs. vetor de ponteiros alocados dinamicamente) — conectando o capítulo diretamente a [2.3 Ponteiros](<../2 GERÊNCIA DE MEMÓRIA/2.3 PONTEIROS/Resumo dos Livros.md>) e [2.2 Alocação Dinâmica](<../2 GERÊNCIA DE MEMÓRIA/2.2 LOCAÇÃO DINÂMICA/Resumo dos Livros.md>).

## Exemplos em C

**As 4 funções básicas, reimplementadas (o exercício que o Celes propõe, útil para realmente entender `string.h`):**
```c
#include <stdio.h>

int meu_strlen(const char *s) {
    int n = 0;
    while (s[n] != '\0')
        n++;
    return n;
}

void minha_strcpy(char *dest, const char *orig) {
    int i;
    for (i = 0; orig[i] != '\0'; i++)
        dest[i] = orig[i];
    dest[i] = '\0';      /* não esquecer de fechar a cópia */
}

void minha_strcat(char *dest, const char *orig) {
    int i = 0, j;
    while (dest[i] != '\0') i++;       /* acha o fim de dest */
    for (j = 0; orig[j] != '\0'; j++, i++)
        dest[i] = orig[j];
    dest[i] = '\0';
}

int minha_strcmp(const char *s1, const char *s2) {
    int i;
    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
    }
    return s1[i] - s2[i];   /* uma delas terminou: decide pelo '\0' vs. caractere restante */
}

int main(void) {
    char destino[50] = "Rio de ";
    printf("comprimento: %d\n", meu_strlen("Janeiro"));
    minha_strcat(destino, "Janeiro");
    printf("concatenado: %s\n", destino);
    printf("compara \"abc\" e \"abd\": %d\n", minha_strcmp("abc", "abd"));  /* negativo */
    return 0;
}
```

**Versão recursiva de `comprimento` e impressão invertida (o "truque" do Celes):**
```c
int comprimento_rec(char *s) {
    if (s[0] == '\0')
        return 0;
    return 1 + comprimento_rec(&s[1]);   /* &s[1] = endereço da subcadeia a partir do 2º char */
}

void imprime_invertido(char *s) {
    if (s[0] != '\0') {
        imprime_invertido(&s[1]);   /* imprime o RESTO primeiro */
        putchar(s[0]);              /* só então o caractere atual, "na volta" da recursão */
    }
}
```

**Vetor de strings: matriz fixa vs. vetor de ponteiros alocados sob medida:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    /* opção 1: matriz fixa — simples, mas desperdiça memória (todo nome "custa" 81 bytes) */
    char alunos_fixo[3][81] = {"Ana", "Bruno", "Carla"};

    /* opção 2: vetor de ponteiros, cada string alocada do tamanho exato */
    char *alunos_dinamico[3];
    char *nomes[] = {"Ana", "Bruno", "Carla"};
    for (int i = 0; i < 3; i++) {
        alunos_dinamico[i] = malloc(strlen(nomes[i]) + 1);  /* +1 para o '\0' */
        strcpy(alunos_dinamico[i], nomes[i]);
    }

    for (int i = 0; i < 3; i++)
        printf("%s / %s\n", alunos_fixo[i], alunos_dinamico[i]);

    for (int i = 0; i < 3; i++)
        free(alunos_dinamico[i]);   /* cada malloc precisa do seu free */

    return 0;
}
```

**O "gotcha" vetor-mutável vs. ponteiro-para-constante:**
```c
char s1[] = "Rio";   /* vetor local — mutável */
s1[0] = 'X';           /* OK: "Xio" */

char *s2 = "Rio";    /* ponteiro para string literal — NÃO mutável */
s2[0] = 'X';           /* comportamento indefinido — pode até travar o programa */

printf("%zu %zu\n", sizeof(s1), sizeof(s2));  /* 4 (bytes de "Rio\0") vs. 8 (tamanho de um ponteiro) */
```
