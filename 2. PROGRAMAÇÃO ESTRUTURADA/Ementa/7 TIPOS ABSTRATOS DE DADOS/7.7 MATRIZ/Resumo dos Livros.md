# Resumo dos Livros — 7.7 Matriz

## Celes — Introdução a Estruturas de Dados (Cap. 6, "Matrizes")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção: matrizes têm capítulo próprio (Cap. 6), não fazem parte do capítulo geral de tipos — e o livro vai além do que o resumo anterior previa, apresentando **três** estratégias de representação, não duas.

**Matriz estática**: `float m[4][3];` — `m[i]` (sem segundo índice) representa um ponteiro para o "vetor-linha" `i`; passagem para função exige a sintaxe (reconhecidamente "obscura", nas palavras do livro) `float (*mat)[3]` ou `float mat[][3]` — o número de colunas **precisa** aparecer no tipo do parâmetro, só o de linhas pode ser omitido.

**Estratégia 1 — matriz dinâmica como vetor simples**: `float *mat = malloc(m*n*sizeof(float));`, acessando `mat[i][j]` conceitual através de `mat[i*n+j]` (linearização row-major, mesma ordem que o K&R descreve para a versão estática). O livro é honesto sobre a desvantagem: "somos obrigados a usar uma notação desconfortável... o que pode deixar o código pouco legível".

**Estratégia 2 — matriz dinâmica como vetor de ponteiros**: aloca primeiro um vetor de `m` ponteiros (`float **mat = malloc(m*sizeof(float*));`), depois aloca cada linha separadamente num laço (`for (i=0;i<m;i++) mat[i] = malloc(n*sizeof(float));`). Vantagem destacada: recupera a sintaxe convencional `mat[i][j]` (sem a conta manual `i*n+j`). Desvantagem simétrica: liberar a matriz também exige um laço — liberar cada linha **antes** de liberar o vetor de ponteiros (ordem inversa da alocação), senão os ponteiros das linhas são perdidos (vazamento de memória).

**Exemplo desenvolvido — matriz transposta**, implementada nas duas estratégias dinâmicas para comparação direta: `float* transposta(int m, int n, float* mat)` (vetor simples, `trp[j*m+i] = mat[i*n+j]`) e `float** transposta(int m, int n, float** mat)` (vetor de ponteiros, `trp[j][i] = mat[i][j]`) — o mesmo algoritmo, duas sintaxes de acesso.

**Estratégia 3 — matriz simétrica**: só armazena a metade inferior (incluindo diagonal), economizando de `n²` para `s = n(n+1)/2` elementos — motivado pela observação de que numa matriz simétrica `mat[i][j] == mat[j][i]`, então armazenar os dois é redundante. A função de acesso "esconde" essa economia: se `i < j` (acima da diagonal), redireciona internamente para o elemento espelhado `(j,i)`, de forma que o código cliente continua enxergando uma matriz completa normal.

## K&R — C: A Linguagem de Programação (Cap. 5, Seções 5.7 e 5.10)

## K&R — C: A Linguagem de Programação (Cap. 5, Seções 5.7 e 5.10)
A Seção 5.7 ("Arranjos Multidimensionais") introduz o tema com o exemplo clássico de conversão de datas (dia do mês ↔ dia do ano), usando uma tabela `tab_dia[2][13]` — duas linhas (ano normal / bissexto) por treze colunas (posição 0 descartada para os meses irem de 1 a 12). O ponto conceitual central do livro é enfatizado explicitamente: "em C, por definição, um arranjo bidimensional é na realidade um arranjo unidimensional, onde cada elemento é um arranjo. Por isso índices são escritos como `tab_dia[i][j]`" — nunca `tab_dia[i, j]`, como em outras linguagens. Decorre daí a ordem de armazenamento **row-major**: "elementos são armazenados por linha, isto é, o índice mais à direita varia mais rapidamente quando os elementos são acessados na ordem de armazenamento." A inicialização segue a mesma lógica: cada linha é inicializada por uma sublista entre chaves dentro da lista externa.

A Seção 5.10 ("Apontadores Versus Arranjos Multidimensionais") contrasta diretamente `int a[10][10]` com `int *b[10]`. Embora `a[5][5]` e `b[5][5]` sejam sintaticamente equivalentes, a semântica é diferente: `a` é "verdadeiramente um arranjo" — 100 células contíguas, com "o cálculo convencional retangular de índices [...] para se encontrar um dado elemento" (aritmética de deslocamento feita pelo compilador). Já `b` aloca apenas 10 ponteiros, cada um devendo ser inicializado para apontar para seu próprio vetor de inteiros — exigindo mais memória total (100 células + 10 ponteiros) e inicialização explícita, mas com duas vantagens citadas pelo livro: acesso "indiretamente através de um apontador ao invés de usar uma multiplicação e uma adição", e a possibilidade de **linhas de tamanhos diferentes** (algumas podem apontar para vetores maiores, menores, ou nem apontar para nada) — propriedade impossível numa matriz estática retangular.

## Síntese
K&R estabelece a base conceitual que qualquer implementação de matriz em C precisa respeitar: um `int m[L][C]` é indexado como arranjo de arranjos e armazenado em row-major, enquanto um vetor de ponteiros para linhas troca simplicidade de acesso por flexibilidade (linhas de tamanhos distintos, um nível extra de indireção). Celes aplica exatamente essas duas estratégias dinâmicas na prática — nomeando explicitamente a versão "vetor simples" (linearizada, `i*n+j`) como a contrapartida direta da ordem row-major que o K&R descreve para a matriz estática — e acrescenta uma terceira técnica que nenhum dos dois cobre no restante da bibliografia: a matriz simétrica com armazenamento reduzido.

## Exemplos em C

**As duas estratégias dinâmicas lado a lado (o exemplo do Celes):**
```c
#include <stdio.h>
#include <stdlib.h>

/* Estratégia 1: vetor simples, linearizado — mat[i][j] vira mat[i*n+j] */
float* cria_matriz_linear(int m, int n) {
    return malloc(m * n * sizeof(float));
}
void set_linear(float *mat, int n, int i, int j, float v) { mat[i*n + j] = v; }
float get_linear(float *mat, int n, int i, int j)         { return mat[i*n + j]; }

/* Estratégia 2: vetor de ponteiros — permite a sintaxe mat[i][j] direta */
float** cria_matriz_ponteiros(int m, int n) {
    float **mat = malloc(m * sizeof(float*));
    for (int i = 0; i < m; i++)
        mat[i] = malloc(n * sizeof(float));
    return mat;
}
void libera_matriz_ponteiros(float **mat, int m) {
    for (int i = 0; i < m; i++)
        free(mat[i]);      /* libera cada LINHA primeiro */
    free(mat);              /* só então o vetor de ponteiros */
}

int main(void) {
    int lin = 2, col = 3;

    float *m1 = cria_matriz_linear(lin, col);
    set_linear(m1, col, 1, 2, 42.0f);
    printf("%.1f\n", get_linear(m1, col, 1, 2));   /* 42.0 */
    free(m1);

    float **m2 = cria_matriz_ponteiros(lin, col);
    m2[1][2] = 42.0f;
    printf("%.1f\n", m2[1][2]);                     /* 42.0 — sintaxe direta */
    libera_matriz_ponteiros(m2, lin);

    return 0;
}
```

**Matriz simétrica — armazenamento reduzido (`n(n+1)/2` em vez de `n²`):**
```c
#include <stdio.h>
#include <stdlib.h>

float* simetrica_cria(int n) {
    int s = n * (n + 1) / 2;
    return malloc(s * sizeof(float));
}

/* mapeia (i,j) para o índice linear correto, sempre trabalhando na metade i>=j */
static int indice(int i, int j) {
    if (i < j) { int t = i; i = j; j = t; }   /* espelha para a metade armazenada */
    return i * (i + 1) / 2 + j;
}

void simetrica_atribui(float *mat, int i, int j, float v) { mat[indice(i, j)] = v; }
float simetrica_acessa(float *mat, int i, int j)           { return mat[indice(i, j)]; }

int main(void) {
    float *m = simetrica_cria(4);       /* matriz 4x4 simétrica: só 10 floats, não 16 */
    simetrica_atribui(m, 2, 1, 7.5f);
    printf("%.1f\n", simetrica_acessa(m, 1, 2));  /* 7.5 — mesmo valor, índices trocados */
    free(m);
    return 0;
}
```
