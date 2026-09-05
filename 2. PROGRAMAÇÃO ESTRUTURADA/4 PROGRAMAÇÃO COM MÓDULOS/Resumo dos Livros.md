# Resumo dos Livros — 4. Programação com Módulos

## Celes — Introdução a Estruturas de Dados (Cap. 9, "Tipos abstratos de dados" — seção "Módulos e compilação em separado")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção importante: ao contrário do que a síntese anterior desta nota afirmava, **Celes cobre módulos de forma mais completa e mais prática que o K&R** — é literalmente a abertura do Cap. 9, com um exemplo de ponta a ponta usando `gcc` de verdade.

**O exemplo condutor**: um módulo `str.c` com as funções `comprimento`/`copia`/`concatena` do Cap. 7 ([[../3 STRINGS/Resumo dos Livros|3 Strings]]), usado por um programa `prog1.c`. O livro mostra a sequência de comandos reais de compilação separada:
```
gcc -c str.c              (gera str.o)
gcc -c prog1.c             (gera prog1.o)
gcc -o prog1.exe str.o prog1.o     (liga os dois .o num executável)
```

**Por que `.h`**: a primeira versão de `prog1.c` repete manualmente os protótipos das 3 funções no topo do arquivo — o livro usa isso para motivar o problema ("para módulos com muitas funções, repetir protótipos manualmente é trabalhoso e sujeito a erro") e a solução: um arquivo `str.h` com só os protótipos (a **interface** do módulo), incluído com `#include "str.h"`. Documenta a convenção de nomenclatura das duas formas de `#include`: `<arquivo.h>` para bibliotecas padrão (procuradas nos diretórios do compilador), `"arquivo.h"` para módulos próprios (procurados primeiro no diretório local).

**Tipo Abstrato de Dados (TAD)** — a seção seguinte do mesmo capítulo, e um dos conceitos mais centrais do livro inteiro: um módulo que define um novo tipo **e** o conjunto de operações sobre ele, "esquecida a forma de implementação" (o cliente do módulo só conhece a interface, nunca a `struct` por trás dela). Convenção de nomenclatura recomendada: prefixar toda função exportada com um identificador do tipo (`pto_cria`, `pto_libera`, `pto_distancia` para um TAD `Ponto`) — evita colisão de nomes quando vários TADs coexistem no mesmo programa, já que C não tem sobrecarga de funções.

Exemplo completo desenvolvido no livro — TAD `Ponto`:
```c
/* ponto.h — INTERFACE: só o que o cliente precisa saber */
typedef struct ponto Ponto;   /* tipo exportado, SEM revelar os campos */

Ponto* pto_cria(float x, float y);
void   pto_libera(Ponto* p);
void   pto_acessa(Ponto* p, float* x, float* y);
void   pto_atribui(Ponto* p, float x, float y);
float  pto_distancia(Ponto* p1, Ponto* p2);
```
```c
/* ponto.c — IMPLEMENTAÇÃO: só este arquivo conhece os campos da struct */
#include <stdlib.h>
#include <math.h>
#include "ponto.h"

struct ponto { float x, y; };   /* privado — invisível para quem só incluiu ponto.h */

Ponto* pto_cria(float x, float y) {
    Ponto* p = (Ponto*) malloc(sizeof(Ponto));
    if (p == NULL) { exit(1); }
    p->x = x; p->y = y;
    return p;
}
void pto_libera(Ponto* p) { free(p); }
float pto_distancia(Ponto* p1, Ponto* p2) {
    float dx = p2->x - p1->x, dy = p2->y - p1->y;
    return sqrt(dx*dx + dy*dy);
}
```
O livro destaca a consequência prática desse encapsulamento: quem usa `ponto.h` **não pode** acessar `p->x` diretamente (a `struct ponto` completa só existe dentro de `ponto.c`) — e a implementação interna pode mudar por completo sem quebrar nenhum código cliente, desde que a interface (`ponto.h`) permaneça a mesma. Esse padrão — struct completa oculta na implementação (`.c`), só o nome do tipo e os protótipos na interface (`.h`) — é usado depois em **todo** TAD do restante do livro (pilha, fila, listas, árvores).

## K&R — C: A Linguagem de Programação (Cap. 4, seção 4.11 — Inclusão de Arquivos)
K&R não dedica uma seção isolada a "cabeçalhos" no sentido moderno (`.h` como contrato entre módulos); o assunto aparece disperso no capítulo 4, sob dois ângulos.

**Organização em múltiplos arquivos.** Logo na abertura do capítulo, o livro observa que "um programa pode residir em um ou mais arquivos-fonte de qualquer forma conveniente; os arquivos-fonte podem ser compilados separadamente e carregados juntos, junto com funções de bibliotecas previamente compiladas" — a ideia de compilação separada e posterior *linkagem*, sem entrar em detalhes de como o processo funciona ("os detalhes variam de acordo com o sistema local").

**Inclusão de arquivos (`#include`).** Dentro da seção sobre o pré-processador, o livro descreve a diretiva que sustenta a separação entre interface e implementação: "para simplificar o manuseio de coleções de `#define`'s e declarações [...], C fornece a facilidade de inclusão de arquivo. Qualquer linha parecida com `#include "arquivo"` é substituída pelo conteúdo do arquivo chamado `arquivo`." O texto recomenda o padrão que se tornaria universal em C: "uma ou duas linhas desta forma aparecem no início de cada arquivo-fonte, para incluir comandos `#define` comuns e declarações do tipo `extern` para variáveis globais." E justifica o porquê: "`#include` é a forma preferida de se juntar declarações para um grande programa. Ela garante que todos os arquivos-fonte serão supridos com as mesmas definições e declarações de variáveis e elimina assim um tipo de erro particularmente desagradável" — isto é, evita que duas partes do programa discordem sobre a assinatura de uma função ou o layout de uma `struct`. O livro alerta ainda para a consequência prática: "quando um arquivo de inclusão é alterado, todos os arquivos que dependem dele devem ser recompilados."

**`static` como ocultamento de módulo.** A seção 4.6 (Variáveis Estáticas), tratada em detalhe no resumo de [2.1 Alocação Estática](<../2 GERÊNCIA DE MEMÓRIA/2.1 ALOCAÇÃO ESTÁTICA/Resumo dos Livros.md>), é o complemento natural do `#include`: variáveis e funções `static` em nível de arquivo "fornecem um modo de esconder objetos de dados e rotinas internas que as manipulam, de modo que outras rotinas e dados não possam conflitar". O próprio livro usa o termo "módulo" para descrever esse padrão: *"getch e ungetch formam um 'módulo' para a entrada e devolução de caracteres e `buf` e `abuf` devem ser estáticas para que sejam inacessíveis externamente."* Isto é, a organização em módulos em C clássico combina duas ferramentas: `#include` de um `.h` para expor a interface pública, e `static` no `.c` para esconder os detalhes de implementação que não fazem parte dela.

## Síntese
Ao contrário do que se pensava, este é um dos tópicos onde **Celes é a referência principal**, não o K&R: dedica uma seção completa e prática (com comandos `gcc` reais) a módulos e compilação separada, e desenvolve o conceito de TAD com um exemplo de ponta a ponta (`Ponto`) que se torna o molde de todas as estruturas de dados do resto do livro. O K&R descreve o mecanismo de baixo nível (`#include` textual + `static` para ocultar detalhes) sem nomear "TAD" explicitamente; Celes usa esse mesmo mecanismo, mas dá a ele um nome, uma convenção de projeto (prefixo de função, `.h` público / `.c` privado) e um objetivo declarado — esconder a implementação para que ela possa mudar sem quebrar quem usa o módulo.

## Exemplos em C

**Compilando o exemplo do Celes de verdade (comandos reais de terminal):**
```
gcc -Wall -c str.c -o str.o
gcc -Wall -c prog1.c -o prog1.o
gcc -o prog1 str.o prog1.o
./prog1
```

**TAD mínimo, no espírito de `Ponto` — um `Contador` que esconde sua representação:**
```c
/* contador.h — interface pública */
typedef struct contador Contador;

Contador* cnt_cria(void);
void      cnt_incrementa(Contador* c);
int       cnt_valor(Contador* c);
void      cnt_libera(Contador* c);
```
```c
/* contador.c — implementação privada */
#include <stdlib.h>
#include "contador.h"

struct contador {       /* só este arquivo enxerga isto */
    int valor;
};

Contador* cnt_cria(void) {
    Contador* c = malloc(sizeof(Contador));
    c->valor = 0;
    return c;
}
void cnt_incrementa(Contador* c) { c->valor++; }
int  cnt_valor(Contador* c)      { return c->valor; }
void cnt_libera(Contador* c)     { free(c); }
```
```c
/* main.c — cliente: só conhece contador.h, nunca o campo 'valor' diretamente */
#include <stdio.h>
#include "contador.h"

int main(void) {
    Contador* c = cnt_cria();
    cnt_incrementa(c);
    cnt_incrementa(c);
    printf("valor = %d\n", cnt_valor(c));   /* c->valor seria erro de compilação aqui */
    cnt_libera(c);
    return 0;
}
```
