# Resumo dos Livros — 2.1 Alocação Estática

## Celes — Introdução a Estruturas de Dados (Cap. 5, "Vetores e alocação dinâmica" — seção "Uso da memória")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

O livro é bem mais explícito do que o resumo original supunha: dedica uma seção inteira ("Uso da memória") a comparar formalmente as **três** formas de reservar memória, exatamente na transição entre vetores estáticos e alocação dinâmica — e a motivação concreta usada é um vetor de notas de alunos, cujo tamanho (número de alunos da turma) só é conhecido em tempo de execução.

1. **Globais (e estáticas)** — espaço existe durante todo o programa.
2. **Locais (automáticas)** — espaço existe só enquanto a função que a declarou está executando; por isso a função chamadora não pode referenciar o espaço local de uma função chamada.
3. **Alocação dinâmica** (tema de [[../2.2 LOCAÇÃO DINÂMICA/Resumo dos Livros|2.2]]) — reservada explicitamente em tempo de execução, e liberada explicitamente pelo programa.

Ponto que o Celes deixa muito concreto e o K&R não: para vetores globais **ou** locais declarados estaticamente (`int v[10];`), **é preciso informar o número máximo de elementos na declaração** — "caso contrário, o compilador não saberia o tamanho do espaço a ser reservado". Essa é exatamente a limitação que motiva a alocação dinâmica: se o tamanho real só é conhecido em tempo de execução (ex. número de alunos digitado pelo usuário), um vetor estático obriga a **superdimensionar** (desperdício de memória) ou a aceitar um limite arbitrário (funcionalidade limitada).

O livro também descreve, com um diagrama de memória (Fig. 5.2), o layout típico de um processo em execução: código do programa, variáveis globais/estáticas, pilha de execução (que cresce a cada chamada de função e "estoura" se crescer demais — *stack overflow*) e a área de memória livre, de onde vem tanto o espaço não usado pela pilha quanto a memória alocada dinamicamente.

Quanto a `struct` (tipos estruturados) declarados sem ponteiro — outro caso de alocação estática — Celes trata no Cap. 8, coberto em [[../../1 INTRODUÇÃO A LINGUAGEM C/1.2 TIPOS ESTRUTURADOS DE DADOS/Resumo dos Livros|1.2 Tipos Estruturados]].

## K&R — C: A Linguagem de Programação (Cap. 4, seção 4.6)
A seção 4.6 (Variáveis Estáticas) define `static` como uma terceira classe de armazenamento, além de `extern` (externa) e automática. O texto explica que variáveis estáticas "podem tanto ser internas como externas": as internas "são locais a uma função particular como variáveis automáticas, mas, ao contrário destas, continuam a existir independentemente da ativação ou desativação da função" — ou seja, fornecem "armazenamento privado e permanente" dentro de uma função. Um exemplo citado é que cadeias de caracteres literais usadas como argumento de `printf` são estáticas internas por natureza.

Já uma variável estática **externa** (declarada fora de qualquer função, com `static` na frente) "é conhecida no resto do arquivo-fonte onde é declarada mas não em qualquer outro arquivo" — o mecanismo que K&R usa para dar privacidade a um "módulo" dentro de um único arquivo `.c`. O exemplo do livro é o par de rotinas `getch`/`ungetch`, que compartilham um buffer (`buf`) e um índice (`abuf`) declarados `static` para que nenhuma outra rotina do programa possa acessá-los ou conflitar com nomes iguais em outros arquivos. O texto observa ainda que funções também podem ser declaradas `static`, tornando-se "desconhecidas fora do arquivo em que foi declarada" — reforçando a ideia de que `static` em C carrega tanto permanência (tempo de vida) quanto privacidade (escopo de arquivo).

O capítulo também contrasta isso, en passant, com vetores de tamanho fixo declarados normalmente (`int v[10]`), cujo espaço é reservado em tempo de compilação e cujo tamanho não pode mudar em tempo de execução — a outra face da alocação estática.

## Síntese
K&R fornece o texto mais preciso sobre o mecanismo `static` em si (tempo de vida e escopo); Celes é mais explícito sobre a motivação estrutural — as 3 formas de reservar memória (global, local, dinâmica) e o layout de memória de um processo (código, globais, pilha, heap) — e usa isso diretamente para justificar a necessidade da alocação dinâmica que vem a seguir.

## Exemplos em C

**Vetor estático — tamanho fixo em tempo de compilação, a limitação que a seção do Celes descreve:**
```c
#include <stdio.h>

#define MAX_ALUNOS 10   /* tem que ser conhecido ANTES de compilar */

int main(void) {
    float notas[MAX_ALUNOS];
    int i, n;

    printf("Quantos alunos (máx %d)? ", MAX_ALUNOS);
    scanf("%d", &n);
    if (n > MAX_ALUNOS) {
        printf("Excede o limite estático de %d.\n", MAX_ALUNOS);
        return 1;
    }

    for (i = 0; i < n; i++)
        scanf("%f", &notas[i]);

    /* v[10], por exemplo, aqui seria acesso fora dos limites: comportamento indefinido */
    return 0;
}
```
A alternativa — não precisar de um `MAX_ALUNOS` arbitrário — é exatamente o assunto de [[../2.2 LOCAÇÃO DINÂMICA/Resumo dos Livros|2.2 Alocação Dinâmica]].

**As 3 formas de memória lado a lado (global, local/automática, e uma prévia da dinâmica):**
```c
#include <stdio.h>
#include <stdlib.h>

int global[5];   /* 1) global: existe durante TODO o programa */

void exemplo(void) {
    int local[5];               /* 2) local/automática: só existe durante esta chamada */
    int *dinamico = malloc(5 * sizeof(int));  /* 3) dinâmica: existe até free() */
    /* ... usa local e dinamico ... */
    free(dinamico);
}   /* aqui 'local' deixa de existir; 'dinamico' já foi liberado manualmente */

int main(void) {
    exemplo();
    return 0;
}
```
