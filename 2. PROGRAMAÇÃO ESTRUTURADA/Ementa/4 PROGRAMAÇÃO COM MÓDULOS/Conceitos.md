# Conceitos — Programação com Módulos

## A ideia em uma frase

Um módulo é um par de arquivos: um `.h` que diz **o que** o módulo oferece (a interface) e
um `.c` que diz **como** aquilo é feito (a implementação) — quem usa o módulo só precisa
conhecer o `.h`.

## O conceito

Programas grandes não cabem num arquivo só. Você quebra o programa em módulos, cada um
responsável por uma parte, e o compilador junta tudo no final.

- **`arquivo.h` (cabeçalho / interface):** protótipos das funções públicas, `typedef`s,
  `#define`s. É o "contrato". Não contém código executável.
- **`arquivo.c` (implementação):** o código das funções. Inclui o próprio `.h`.
- **`#include "arquivo.h"`** copia o texto do cabeçalho para dentro de quem incluir.
  `" "` procura primeiro na pasta local; `< >` procura nas pastas do sistema (bibliotecas
  padrão).
- **Compilação separada:** cada `.c` vira um `.o` (objeto). Depois o *linker* junta os
  `.o` num executável. Trocar um `.c` só exige recompilar aquele `.o`.
- **`static` no `.c`:** funções/variáveis que são detalhe interno, não parte da interface,
  são marcadas `static` para ficarem invisíveis aos outros arquivos.

**TAD (Tipo Abstrato de Dados):** um módulo que define um tipo novo **e** as operações
sobre ele, escondendo a `struct` por trás. O cliente usa `Ponto *p = pto_cria(...)` mas
**não** pode acessar `p->x` — a struct só existe dentro do `.c`. Assim a implementação
pode mudar sem quebrar quem usa. Convenção: prefixar as funções com o nome do tipo
(`pto_cria`, `pto_distancia`), porque C não tem sobrecarga.

## Sintaxe / ferramentas

**Include guard** — impede que o mesmo `.h`, incluído duas vezes, cause erro de
redefinição:

```c
#ifndef PONTO_H
#define PONTO_H
/* ... conteúdo do cabeçalho ... */
#endif
```

**Compilar:**

```
gcc -Wall -c ponto.c -o ponto.o     # cada .c vira um .o
gcc -Wall -c main.c  -o main.o
gcc -o programa ponto.o main.o      # linka os .o num executável
```

## Exemplos passo a passo

### Exemplo — um TAD `Contador` em três arquivos

**`contador.h` — a interface (o que o cliente vê):**

```c
#ifndef CONTADOR_H
#define CONTADOR_H

typedef struct contador Contador;   // nome do tipo, SEM revelar os campos

Contador *cnt_cria(void);
void      cnt_incrementa(Contador *c);
int       cnt_valor(Contador *c);
void      cnt_libera(Contador *c);

#endif
```

**`contador.c` — a implementação (só este arquivo conhece a struct):**

```c
#include <stdlib.h>
#include "contador.h"

struct contador {        // definição completa fica escondida aqui
    int valor;
};

Contador *cnt_cria(void) {
    Contador *c = malloc(sizeof(Contador));
    if (c != NULL) c->valor = 0;
    return c;
}
void cnt_incrementa(Contador *c) { c->valor++; }
int  cnt_valor(Contador *c)      { return c->valor; }
void cnt_libera(Contador *c)     { free(c); }
```

**`main.c` — o cliente (só inclui o `.h`):**

```c
#include <stdio.h>
#include "contador.h"

int main(void) {
    Contador *c = cnt_cria();
    cnt_incrementa(c);
    cnt_incrementa(c);
    printf("%d\n", cnt_valor(c));   // 2
    // c->valor;  <- ERRO de compilação: struct contador é incompleta aqui
    cnt_libera(c);
    return 0;
}
```

**Passo a passo do build:**

1. `gcc -c contador.c` → `contador.o`. Aqui `struct contador` é conhecida por inteiro.
2. `gcc -c main.c` → `main.o`. Aqui só o `typedef` (ponteiro opaco) é conhecido — por isso
   `c->valor` não compila neste arquivo.
3. `gcc -o programa contador.o main.o` → o linker resolve as chamadas de `main` para as
   funções que estão em `contador.o`.

**O que observar:** se amanhã `struct contador` ganhar um campo `passo` e `cnt_incrementa`
passar a somar `passo`, **nada** em `main.c` muda. Essa é a vantagem do encapsulamento.

## Erros comuns / pegadinhas

- **`.h` sem include guard** — incluído por dois caminhos, causa "redefinition of ...".
- **Definir função (com corpo) no `.h`** — cada `.c` que incluir gera sua cópia; o linker
  reclama de "multiple definition". No `.h` vão só protótipos.
- **Definir variável global no `.h`** — mesmo problema. Use `extern int x;` no `.h` e
  `int x;` em um único `.c`.
- **Esquecer de linkar um `.o`** — "undefined reference to `cnt_cria`".
- **Cliente acessando `p->campo` de um TAD** — quebra o encapsulamento (e nem compila se o
  tipo for opaco, que é o certo).
- **Editar um `.h` e não recompilar quem o inclui** — comportamento inconsistente; num
  `Makefile` isso é automático.

## Resumo / checklist

- [ ] Sei o papel do `.h` (interface) e do `.c` (implementação)
- [ ] Uso include guard em todo `.h`
- [ ] Sei a diferença entre `#include "..."` e `#include <...>`
- [ ] Sei compilar separado (`-c`) e linkar os `.o`
- [ ] Uso `static` no `.c` para o que é detalhe interno
- [ ] Entendo um TAD: tipo opaco no `.h`, `struct` completa só no `.c`
