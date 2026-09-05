# Resumo dos Livros — 2.3 Ponteiros

## Celes — Introdução a Estruturas de Dados (Cap. 4 "Funções", seção "Ponteiro de variáveis"; Cap. 5 "Vetores e alocação dinâmica")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção de estrutura: ponteiros **não** têm capítulo isolado dedicado só a eles — Celes os introduz dentro do Cap. 4 (motivado pelo problema de uma função retornar mais de um valor, ver [[../../1 INTRODUÇÃO A LINGUAGEM C/1.7 PASSAGEM DE PARÂMETROS POR VALOR E POR REFERÊNCIA/Resumo dos Livros|1.7]]) e amplia a discussão no Cap. 5, conectando ponteiros a vetores e à alocação dinâmica ([[../2.2 LOCAÇÃO DINÂMICA/Resumo dos Livros|2.2]]).

**Fundamentos (Cap. 4)**: `int *p;` declara um ponteiro para `int` (a linguagem não tem palavra reservada própria — usa o mesmo tipo, precedido de `*`). Operador `&` ("endereço de") e operador `*` ("conteúdo de" / indireção) — exemplo: `p = &a; *p = 6;` altera `a` indiretamente através de `p`. O livro é explícito sobre o perigo de escrever através de um ponteiro **não inicializado** (`int *p; *p = 3;` sem `p` apontar para nada válido) — chama isso de "ERRO típico" que "às vezes pode funcionar", tornando o bug traiçoeiro.

**Ponteiros e vetores (Cap. 5)**: aqui Celes formaliza exatamente a mesma equivalência que o K&R (5.3) apresenta com mais rigor — "o símbolo `v`, o qual representa o vetor, é uma constante que representa seu endereço inicial" — e monta a mesma tabela de correspondência: `v+0` aponta para o 1º elemento, `v+1` para o 2º, ..., com a nota de que a aritmética é escalada pelo tamanho do tipo (`p+1` avança 4 bytes se `p` é `int*`, assumindo `int` de 4 bytes). Conclui, no mesmo espírito do K&R: `&v[i]` ⟺ `(v+i)`, e `v[i]` ⟺ `*(v+i)` — "é lógico que a forma indexada é mais clara e adequada" (ou seja: a equivalência existe, mas o livro recomenda preferir a notação `[i]` na prática).

**Passagem de vetor para função**: como um nome de vetor "é" o endereço do primeiro elemento, passar um vetor para uma função é sempre passar um ponteiro — por isso uma função como `void incr_vetor(int n, int *v)` pode alterar os elementos do vetor original do chamador (não faz cópia dos dados, só do endereço).

## K&R — C: A Linguagem de Programação (Cap. 5)

## K&R — C: A Linguagem de Programação (Cap. 5)
O capítulo abre com uma frase que resume a filosofia do livro sobre o assunto: "Apontadores têm sido comparados ao comando `goto` como uma forma maravilhosa de se criar programas impossíveis de entender [...] Com disciplina, entretanto, apontadores podem ser usados para se obter clareza e simplicidade."

**5.1 Apontadores e Endereços.** Define que "o operador unário `&` fornece o endereço de um objeto" e que "o operador unário `*` trata seu operando como um endereço, e acessa este endereço para buscar o conteúdo do objeto alvo". A declaração `int *px;` é lida como um mnemônico: "a combinação `*px` é um `int`". O livro chama atenção para a precedência (`*px + 1` soma 1 ao valor apontado, não ao ponteiro) e para o cuidado com parênteses em `(*px)++` versus `*px++`, já que operadores unários como `*` e `++` são avaliados da direita para a esquerda.

**5.3 Apontadores e Arranjos.** Esta é a seção mais citada do capítulo, por formalizar a equivalência entre indexação e aritmética de ponteiros: "uma referência a `a[i]` pode ser escrita como `*(a + i)`. [...] as duas formas são completamente equivalentes." Consequentemente, "`&a[i]` e `a + i` são idênticas", e, na direção oposta, se `pa` é um ponteiro, "`pa[i]` é idêntico a `*(pa + i)`". O texto também explica que "uma referência para um arranjo é convertida pelo compilador a um apontador para o início do arranjo" — por isso `pa = a;` funciona sem precisar de `&a[0]` — e que a aritmética de ponteiros é sempre escalada pelo `sizeof` do tipo apontado (`pa + i` avança `i` objetos, não `i` bytes).

```c
int a[10];
int *pa = a;        /* nome do vetor decai para ponteiro ao 1º elemento */

x = *(pa + 3);       /* equivale a a[3] */
y = pa[3];            /* também equivale a a[3] */
```

## Síntese
K&R fornece a formalização mais precisa da equivalência `v[i] ≡ *(v+i)` que sustenta toda a manipulação de vetores e strings em C; Celes chega à mesma equivalência por um caminho mais gradual (primeiro `&`/`*` isolados no Cap. 4, depois a conexão com vetores no Cap. 5), com bastante peso didático nos diagramas de memória — e os dois livros concordam explicitamente que a notação `v[i]` deve ser preferida a `*(v+i)` no código real, mesmo sendo equivalentes.

## Exemplos em C

**`&` e `*`, e o perigo de ponteiro não inicializado:**
```c
#include <stdio.h>

int main(void) {
    int a = 10;
    int *p;       /* p ainda não aponta para nada válido — "lixo" */

    p = &a;       /* agora p aponta para a */
    printf("a = %d, *p = %d\n", a, *p);  /* os dois imprimem 10 */

    *p = 20;      /* altera a INDIRETAMENTE, através de p */
    printf("a = %d\n", a);               /* imprime 20 */

    /* int *q; *q = 99;  <-- NUNCA fazer isto: q não aponta para lugar válido */

    return 0;
}
```

**Equivalência ponteiro/vetor — mesmo acesso, três notações:**
```c
#include <stdio.h>

int main(void) {
    int v[5] = {10, 20, 30, 40, 50};
    int *p = v;    /* nome do vetor "decai" para ponteiro ao 1º elemento — sem & */

    for (int i = 0; i < 5; i++) {
        printf("v[%d]=%d  *(v+%d)=%d  p[%d]=%d  *(p+%d)=%d\n",
               i, v[i], i, *(v + i), i, p[i], i, *(p + i));
        /* as 4 expressões acessam exatamente o mesmo elemento */
    }
    return 0;
}
```

**Ponteiro como parâmetro de função para alterar o vetor original:**
```c
#include <stdio.h>

void dobra_elementos(int n, int *v) {   /* v recebe apenas o ENDEREÇO do vetor */
    for (int i = 0; i < n; i++)
        v[i] *= 2;                       /* altera o vetor ORIGINAL do chamador */
}

int main(void) {
    int a[] = {1, 2, 3};
    dobra_elementos(3, a);
    printf("%d %d %d\n", a[0], a[1], a[2]);  /* 2 4 6 */
    return 0;
}
```
