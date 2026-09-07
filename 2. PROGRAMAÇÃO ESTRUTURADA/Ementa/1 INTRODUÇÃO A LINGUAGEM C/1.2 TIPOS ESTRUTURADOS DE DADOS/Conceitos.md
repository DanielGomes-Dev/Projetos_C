# Conceitos — Tipos Estruturados de Dados

## A ideia em uma frase

Tipos estruturados agrupam vários dados num só nome: um **vetor** junta vários valores do
mesmo tipo; uma **`struct`** junta valores de tipos diferentes que descrevem uma mesma
coisa.

## O conceito

- **Vetor (`array`)** — uma sequência de elementos do mesmo tipo, guardados de forma
  contígua na memória, acessados por índice a partir de `0`. `int v[5];` são 5 inteiros:
  `v[0]` a `v[4]`.
- **`struct`** — um registro. `struct ponto { float x; float y; };` descreve um "gabarito";
  `struct ponto p;` cria uma variável com os campos `x` e `y` juntos.
- **`enum`** — nomes para uma sequência de inteiros: `enum { DOM, SEG, TER };` faz
  `DOM == 0`, `SEG == 1`, `TER == 2`. Deixa o código legível.
- **`union`** — como uma `struct`, mas todos os campos ocupam **o mesmo espaço**; só um
  vale por vez. Tamanho = o do maior campo. Uso raro (economia de memória, protocolos).
- **`typedef`** — cria um apelido para um tipo: `typedef struct ponto Ponto;` permite
  escrever `Ponto p;` em vez de `struct ponto p;`.

## Sintaxe / ferramentas

```c
int v[5] = {10, 20, 30};        // v[3] e v[4] ficam 0; v[5] NÃO existe

struct ponto { float x, y; };   // gabarito
struct ponto p;                 // variável
p.x = 1.0f;                     // acesso a campo com ponto

struct ponto *pp = &p;
pp->y = 2.0f;                   // via ponteiro: -> em vez de (*pp).y

typedef struct ponto Ponto;     // apelido
Ponto q = {3.0f, 4.0f};        // inicialização por lista

enum cor { VERMELHO, VERDE, AZUL };
enum cor c = VERDE;             // c vale 1
```

| Operador | Quando usar |
|---|---|
| `p.campo` | `p` é uma struct |
| `p->campo` | `p` é um **ponteiro** para struct; é `(*p).campo` |

`.` tem prioridade sobre `*` e sobre `&` — por isso `(*pp).x` precisa de parênteses e
`&p.x` não.

## Exemplos passo a passo

### Exemplo 1 — vetor: preencher, somar, achar o maior

```c
#include <stdio.h>

int main(void) {
    int v[5] = {4, 9, 2, 7, 1};
    int soma = 0, maior = v[0];

    for (int i = 0; i < 5; i++) {
        soma += v[i];
        if (v[i] > maior) maior = v[i];
    }
    printf("soma=%d  maior=%d\n", soma, maior);   // soma=23  maior=9
    return 0;
}
```

**Passo a passo:** `maior` começa com `v[0] = 4`. Percorrendo: `9 > 4` → `maior = 9`;
`2`, `7`, `1` não superam. `soma` acumula `4+9+2+7+1 = 23`.

**O que observar:** os índices válidos vão de `0` a `4`. `v[5]` está fora do vetor e é
comportamento indefinido — C não avisa.

### Exemplo 2 — `struct`: agrupar dados relacionados

```c
#include <stdio.h>
#include <string.h>

struct aluno {
    char nome[30];
    int  matricula;
    float media;
};

int main(void) {
    struct aluno a;
    strcpy(a.nome, "Ana");     // não se copia string com =; usa strcpy
    a.matricula = 12345;
    a.media = 8.7f;

    printf("%s (%d): %.1f\n", a.nome, a.matricula, a.media);
    return 0;
}
```

**O que observar:** os três campos ficam lado a lado na memória, sob o nome `a`. Um vetor
`struct aluno turma[40];` guarda 40 desses registros.

### Exemplo 3 — passar struct para função: por ponteiro

```c
#include <stdio.h>

typedef struct { float x, y; } Ponto;

// recebe ponteiros: pode alterar 'r' do chamador, e não copia structs grandes
void soma_pontos(const Ponto *a, const Ponto *b, Ponto *r) {
    r->x = a->x + b->x;
    r->y = a->y + b->y;
}

int main(void) {
    Ponto p = {1, 2}, q = {3, 4}, s;
    soma_pontos(&p, &q, &s);
    printf("(%.0f, %.0f)\n", s.x, s.y);   // (4, 6)
    return 0;
}
```

**Passo a passo:**

1. `soma_pontos(&p, &q, &s)` passa três endereços.
2. `a->x` lê o campo `x` de `p` (1), `b->x` lê o de `q` (3), soma dá 4, gravado em `r->x`
   — que é o campo `x` de `s`.
3. Mesma coisa para `y`. `s` de `main` sai preenchido.

**O que observar:** `const` nos parâmetros de entrada documenta que a função não vai
alterá-los. Passar `Ponto` por valor também funciona em C moderno, mas copia a struct
inteira a cada chamada.

### Exemplo 4 — `enum` deixando o código legível

```c
#include <stdio.h>

enum estado { PARADO, ANDANDO, CORRENDO };

const char *nome_estado(enum estado e) {
    switch (e) {
        case PARADO:   return "parado";
        case ANDANDO:  return "andando";
        case CORRENDO: return "correndo";
    }
    return "?";
}

int main(void) {
    enum estado s = ANDANDO;
    printf("%s (%d)\n", nome_estado(s), s);   // andando (1)
    return 0;
}
```

## Erros comuns / pegadinhas

- **Acessar índice fora do vetor** — `v[5]` num `int v[5]`. Sem erro do compilador, com
  corrupção de memória em execução.
- **Copiar string com `=`** — `a.nome = "Ana"` não compila; strings vão com `strcpy`.
- **Comparar structs com `==`** — não existe; compare campo a campo.
- **Esquecer o `;` depois de `}` na definição da `struct`** — erro de compilação confuso.
- **Usar `.` onde precisa de `->`** (e vice-versa) — `pp.x` num ponteiro não compila.
- **Achar que `union` guarda todos os campos** — guarda só um; ler um campo depois de
  gravar outro é reinterpretar os mesmos bits.

## Resumo / checklist

- [ ] Sei declarar e percorrer um vetor, ciente de que o índice vai de `0` a `n-1`
- [ ] Sei definir uma `struct` e acessar campos com `.` e com `->`
- [ ] Sei por que `->` existe (evita `(*p).campo`)
- [ ] Sei passar uma `struct` para função por ponteiro e por quê
- [ ] Sei para que servem `enum`, `union` e `typedef`
- [ ] Copio strings de campo com `strcpy`, nunca com `=`
