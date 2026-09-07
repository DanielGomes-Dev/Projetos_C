# Resumo dos Livros — 1.2 Tipos Estruturados de Dados

## Celes — Introdução a Estruturas de Dados (Cap. 8, "Tipos estruturados")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido — a subseção específica sobre `union`/`enum` não apareceu de forma legível na extração; os pontos sobre esses dois tipos abaixo seguem o conhecimento geral da linguagem, não uma citação direta do livro.

Correção de número de capítulo: é o **Cap. 8** (não o 2), com exemplo condutor idêntico em espírito ao do K&R — uma estrutura `ponto` (`float x, y;`) em vez de `data`.

**`struct` básica**: `struct ponto { float x; float y; };` define o "gabarito"; `struct ponto p;` declara a variável. Acesso a campo com `.` (`p.x = 10.0;`), com a observação de que `&p.x` funciona sem parênteses porque **o operador `.` tem precedência maior que `&`**.

**Ponteiro para struct**: `struct ponto *pp;`. Acessar um campo através do ponteiro exige o operador de indireção `*` **com parênteses obrigatórios** — `(*pp).x = 12.0;`, já que `.` tem precedência maior que `*` (o oposto do caso anterior). A linguagem oferece o operador `->` como atalho exatamente para evitar esse parêntese: `pp->x = 12.0;` é equivalente e é a forma idiomática.

**Passagem de struct para função — o ponto mais insistido do capítulo**: o livro mostra as duas versões de uma função `imprime`, uma recebendo `struct ponto p` (por valor) e outra `struct ponto *pp` (por ponteiro), e argumenta por que a segunda é preferível **mesmo quando a função não precisa alterar nada**: passar a struct inteira por valor copia todos os seus campos para a pilha a cada chamada (caro se a struct for grande), enquanto passar um ponteiro copia só o endereço (tipicamente 4 ou 8 bytes) — a mesma conclusão prática do K&R (que, na sua variante de C, nem permite passar struct por valor).

**`typedef`**: tratado com mais profundidade que em muitos livros introdutórios — mostra `typedef float Real;`, `typedef int* PInt;`, `typedef float Vetor[4];` e explica a regra mnemônica: "escreva a declaração de uma variável normal com esse tipo; o nome dessa variável é o novo nome do tipo". Cobre a forma combinada `typedef struct ponto Ponto, *PPonto;` (dois nomes num só `typedef`) e recomenda **não** criar mnemônico para o tipo ponteiro (`PPonto`), preferindo escrever `Ponto*` explicitamente no código — mais legível, na opinião do livro.

## K&R — C: A Linguagem de Programação (Cap. 6, "Estruturas")

## K&R — C: A Linguagem de Programação (Cap. 6, "Estruturas")
O Capítulo 6 trata de `struct`, com um exemplo condutor de uma estrutura `data` (dia, mês, ano, dia do ano, nome do mês). A seção 6.1 (Elementos Básicos) mostra a sintaxe: `struct data { int dia; int mes; ...};` — a palavra-chave `struct` seguida de uma *etiqueta* opcional (aqui `data`) e uma lista de membros entre chaves. Uma declaração de estrutura sem lista de variáveis não aloca nada; ela só descreve o "gabarito". Membros são acessados com o operador ponto: `d.ano`, e estruturas podem ser aninhadas (`emp.nascimento.mes`). Estruturas externas ou estáticas podem ser inicializadas com uma lista entre chaves, como `struct data d = {7, 9, 1822, 250, "set"};`.

A seção 6.2 (Estruturas e Funções) explica uma restrição central do C do livro (K&R "clássico", pré-ANSI): as únicas operações permitidas diretamente sobre uma estrutura são obter seu endereço com `&` e acessar um membro — **não** se pode atribuir, copiar, passar ou retornar uma struct inteira por valor de/para uma função (isso é levantado só em versões posteriores da linguagem). Na prática, isso força passar um ponteiro para a estrutura, usando o operador `->`: se `ad` é `struct data *ad`, então `ad->ano` acessa o membro `ano` através do ponteiro (equivalente a `(*ad).ano`). O livro reescreve a função `dia_do_ano` para receber `struct data *ad` em vez dos campos separados, ilustrando o padrão "passa ponteiro, acessa com `->`" que se tornará constante no restante do curso.

O K&R também cobre neste capítulo (não detalhado aqui) arranjos de estruturas, estruturas auto-referenciadas (base para listas encadeadas), campos de bits, uniões e `typedef`.

Sobre vetores: o Capítulo 1 (seção 1.6) já havia introduzido a ideia central — `int ndigito[10];` declara um bloco de 10 inteiros indexados de 0 a 9, e o índice pode ser qualquer expressão inteira.

## Síntese
O ponto crítico deste tópico é que, na variante de C do K&R, uma `struct` não é um valor "de primeira classe" como em linguagens modernas: ela só circula entre funções via ponteiro (daí o operador `->`), o que conecta diretamente este tópico ao de passagem de parâmetros (1.7). Celes chega à mesma prática (preferir ponteiro para struct) por um caminho ligeiramente diferente — não por restrição da linguagem (no C do Celes, já é permitido passar struct por valor), mas por argumento de eficiência — e cobre `typedef` com mais profundidade que o resumo do K&R aqui. Essas construções (vetor e struct) são os blocos de montagem para todas as estruturas de dados do restante do curso.

## Exemplos em C

**`struct`, `.`  e `->` lado a lado (o exemplo do Celes, `ponto`):**
```c
#include <stdio.h>

struct ponto {
    float x;
    float y;
};

int main(void) {
    struct ponto p;
    p.x = 10.0f;
    p.y = 5.0f;

    struct ponto *pp = &p;
    (*pp).x = 12.0f;    /* parênteses obrigatórios: . tem precedência maior que * */
    pp->y = 7.0f;        /* forma idiomática, equivalente a (*pp).y */

    printf("(%.1f, %.1f)\n", p.x, p.y);
    return 0;
}
```

**Por que passar ponteiro para struct em vez da struct inteira:**
```c
#include <stdio.h>

struct ponto { float x, y; };

/* por valor: copia os 8 bytes da struct inteira a cada chamada */
void imprime_valor(struct ponto p) {
    printf("(%.1f, %.1f)\n", p.x, p.y);
}

/* por ponteiro: copia só o endereço (4/8 bytes) — mais barato, escala melhor */
void imprime_ponteiro(const struct ponto *pp) {
    printf("(%.1f, %.1f)\n", pp->x, pp->y);
}

int main(void) {
    struct ponto p = {3.0f, 4.0f};
    imprime_valor(p);
    imprime_ponteiro(&p);
    return 0;
}
```

**`typedef` — os padrões do Celes, incluindo a forma combinada:**
```c
typedef struct ponto {
    float x, y;
} Ponto;             /* struct e typedef juntos, num só comando */

typedef Ponto *PPonto;   /* o livro prefere Ponto* explícito, mas o mnemônico existe */

int soma_pontos(Ponto a, Ponto b, Ponto *resultado) {
    resultado->x = a.x + b.x;
    resultado->y = a.y + b.y;
    return 0;
}

int main(void) {
    Ponto p1 = {1.0f, 2.0f}, p2 = {3.0f, 4.0f}, soma;
    soma_pontos(p1, p2, &soma);
    printf("(%.1f, %.1f)\n", soma.x, soma.y);
    return 0;
}
```

**`union` e `enum` (não cobertos com clareza na extração OCR — exemplo padrão da linguagem, para completar o tópico da ementa):**
```c
#include <stdio.h>

/* union: todos os campos compartilham o MESMO espaço de memória (tamanho = o maior campo) */
union valor {
    int i;
    float f;
    char c;
};

/* enum: nomes simbólicos para uma sequência de constantes inteiras (0, 1, 2, ... por padrão) */
enum dia_semana { DOM, SEG, TER, QUA, QUI, SEX, SAB };

int main(void) {
    union valor v;
    v.i = 42;
    printf("%zu bytes (tamanho do maior campo)\n", sizeof(v));

    enum dia_semana hoje = QUA;
    printf("hoje = %d\n", hoje);   /* imprime 3 */
    return 0;
}
```
