# Conceitos — Ponteiros

## A ideia em uma frase

Um ponteiro é uma variável que, em vez de guardar um valor, guarda o **endereço** de
onde outro valor está na memória.

## O conceito

Pense na memória do computador como uma rua muito comprida de casas, todas numeradas em
sequência: casa 1000, casa 1001, casa 1002...

- Uma **variável comum** é uma casa com um nome. Quando você escreve `int x = 42;`, o
  compilador reserva uma casa, dá a ela o apelido `x` e coloca o valor `42` lá dentro.
- Um **ponteiro** é uma casa que guarda **o número de outra casa**. Se `p` guarda `1000`
  e a casa `1000` é onde mora `x`, dizemos que "`p` aponta para `x`".

Por que isso é útil? Porque com o endereço de uma variável você consegue:

1. **Alterar a variável de fora** — uma função que recebe o endereço de `x` pode mudar o
   valor de `x` do chamador (é assim que `scanf` escreve nas suas variáveis).
2. **Trabalhar com blocos de memória sem copiá-los** — passar um vetor de 1 milhão de
   posições para uma função custa o mesmo que passar um único endereço.
3. **Construir estruturas que crescem** — listas, árvores e filas encadeadas são feitas de
   nós que guardam o endereço do próximo nó (ver [[../../7 TIPOS ABSTRATOS DE DADOS/7.3 LISTA SIMPLESMENTE ENCADEADA/Conceitos|listas encadeadas]]).

## Sintaxe / ferramentas

```c
int  x = 42;
int *p;        // "p é um ponteiro para int" — p pode guardar o endereço de um int
p = &x;        // & = "endereço de": p agora aponta para x
int y = *p;    // * = "conteúdo de": vai até o endereço em p e lê o valor lá (42)
*p = 10;       // escreve 10 no endereço apontado por p  ->  x agora vale 10
```

| Símbolo | Nome | O que faz |
|---|---|---|
| `int *p;` | declaração | cria um ponteiro; o `*` diz "guarda endereço", não é operação |
| `&x` | endereço de | devolve o endereço da variável `x` |
| `*p` | desreferência | devolve (ou grava) o valor que está no endereço guardado em `p` |
| `NULL` | ponteiro nulo | valor especial que significa "não aponta para nada"; está em `<stdlib.h>` |
| `p->campo` | acesso via ponteiro | quando `p` aponta para uma `struct`, `p->campo` é `(*p).campo` |

Regra de leitura da declaração: `int *p;` — a expressão `*p` tem tipo `int`, logo `p` é
"ponteiro para int".

## Exemplos passo a passo

### Exemplo 1 — `&` e `*` na prática

**Problema:** mostrar que alterar `*p` altera a variável apontada.

```c
#include <stdio.h>

int main(void) {
    int a = 10;
    int *p = &a;          // p aponta para a

    printf("a = %d\n", a);       // 10
    printf("*p = %d\n", *p);     // 10  (mesmo valor: p aponta para a)

    *p = 20;                     // escreve 20 no endereço de a
    printf("a = %d\n", a);       // 20  <- a mudou sem escrevermos "a ="

    return 0;
}
```

**Passo a passo (com endereços fictícios):**

| Linha | Memória | Comentário |
|---|---|---|
| `int a = 10;` | casa 1000: `a = 10` | reserva a casa de `a` |
| `int *p = &a;` | casa 1004: `p = 1000` | `p` guarda o número da casa de `a` |
| `*p = 20;` | casa 1000: `a = 20` | "vá até 1000 e grave 20" |

**O que observar:** `p` e `a` são duas casas diferentes. `p` não contém `10` nem `20` —
contém `1000`, o endereço. `*p` é o caminho que leva de `p` até `a`.

### Exemplo 2 — passar o endereço para uma função poder alterar a variável

**Problema:** escrever uma função `troca` que troque os valores de duas variáveis do
chamador. Sem ponteiros isso é impossível, porque C copia os argumentos.

```c
#include <stdio.h>

void troca(int *x, int *y) {   // recebe ENDEREÇOS, não cópias
    int tmp = *x;              // guarda o valor apontado por x
    *x = *y;                   // grava no lugar de x o valor apontado por y
    *y = tmp;                  // grava no lugar de y o valor antigo de x
}

int main(void) {
    int a = 1, b = 2;
    troca(&a, &b);             // passa os endereços de a e b
    printf("a = %d, b = %d\n", a, b);   // a = 2, b = 1
    return 0;
}
```

**Passo a passo:**

1. `main` tem `a = 1` (casa 1000) e `b = 2` (casa 1004).
2. `troca(&a, &b)` chama a função com `x = 1000` e `y = 1004`.
3. `tmp = *x;` → `tmp = 1` (lê a casa 1000).
4. `*x = *y;` → grava `2` na casa 1000. Agora `a` vale 2.
5. `*y = tmp;` → grava `1` na casa 1004. Agora `b` vale 1.
6. A função retorna; `a` e `b` de `main` ficaram trocados.

**O que observar:** se a função fosse `void troca(int x, int y)`, ela trocaria apenas as
cópias locais `x` e `y`, e `a`/`b` de `main` não mudariam. É a diferença entre passagem
por valor e "por referência" — ver [[../../1 INTRODUÇÃO A LINGUAGEM C/1.7 PASSAGEM DE PARÂMETROS POR VALOR E POR REFERÊNCIA/Conceitos|1.7]].

### Exemplo 3 — ponteiros e vetores: `v[i]` é o mesmo que `*(v + i)`

**Problema:** entender por que o nome de um vetor pode ser usado como ponteiro.

```c
#include <stdio.h>

int main(void) {
    int v[5] = {10, 20, 30, 40, 50};
    int *p = v;        // o nome do vetor "decai" para o endereço de v[0] — repare: sem &

    for (int i = 0; i < 5; i++) {
        printf("v[%d]=%d   *(v+%d)=%d   p[%d]=%d\n",
               i, v[i], i, *(v + i), i, p[i]);
    }
    return 0;
}
```

Saída:

```
v[0]=10   *(v+0)=10   p[0]=10
v[1]=20   *(v+1)=20   p[1]=20
...
```

**Passo a passo da expressão `*(v + 2)`:**

1. `v` é o endereço do primeiro elemento, digamos `2000`.
2. `v + 2` **não** soma 2 bytes: soma `2 * sizeof(int)` = 8 bytes → endereço `2008`.
   A aritmética de ponteiro anda "de elemento em elemento", não de byte em byte.
3. `*(v + 2)` lê o `int` que está em `2008` → `30`, que é exatamente `v[2]`.

Por isso `v[i]`, `*(v + i)`, `p[i]` e `*(p + i)` acessam o mesmo elemento.

> Cuidado: um vetor **não é** um ponteiro. Ele *decai* para um ponteiro ao ser usado numa
> expressão. Diferenças reais: `sizeof(v)` dá o tamanho do vetor inteiro (20 bytes),
> `sizeof(p)` dá o tamanho de um ponteiro (8 bytes); e você não pode fazer `v = outra_coisa;`.

### Exemplo 4 — ponteiro para `struct` e o operador `->`

```c
#include <stdio.h>

typedef struct {
    char nome[30];
    int  idade;
} Pessoa;

void faz_aniversario(Pessoa *p) {
    p->idade++;             // p->idade é o mesmo que (*p).idade
}

int main(void) {
    Pessoa joao = {"Joao", 29};
    faz_aniversario(&joao);
    printf("%s tem %d anos\n", joao.nome, joao.idade);   // Joao tem 30 anos
    return 0;
}
```

**Passo a passo:**

1. `joao` é uma `struct` na pilha de `main`.
2. `faz_aniversario(&joao)` passa o endereço da struct (a struct inteira **não** é copiada).
3. Dentro da função, `p` aponta para `joao`. `p->idade++` incrementa o campo `idade` da
   struct original.
4. `(*p).idade` funcionaria igual, mas precisa dos parênteses (`.` tem prioridade sobre `*`);
   `->` existe justamente para escrever isso de forma limpa.

## Erros comuns / pegadinhas

- **Desreferenciar ponteiro não inicializado.** `int *p; *p = 3;` grava num endereço
  aleatório (lixo). Pode "funcionar" por acaso hoje e travar amanhã — bug traiçoeiro.
  Inicialize sempre: com um `&`, com `malloc`, ou com `NULL`.
- **Esquecer o `&` no `scanf`.** `scanf("%d", n)` em vez de `scanf("%d", &n)` passa o valor
  de `n` (lixo) como se fosse endereço. Compila com aviso, quebra em execução.
- **Confundir `*p++` com `(*p)++`.** `*p++` incrementa o **ponteiro** e devolve o valor
  antigo apontado; `(*p)++` incrementa o **valor apontado**. Os operadores unários se
  associam da direita para a esquerda.
- **Achar que "vetor é ponteiro".** Vetor decai para ponteiro em expressões, mas
  `sizeof` e atribuição se comportam diferente (ver o aviso no Exemplo 3).
- **Desreferenciar `NULL`.** `p = NULL; *p;` trava o programa. Antes de usar um ponteiro
  que pode não ter sido preenchido, teste `if (p != NULL)`.
- **Retornar o endereço de uma variável local.** `int *f(void){ int x = 5; return &x; }` —
  `x` deixa de existir quando `f` retorna; o endereço devolvido é inválido.

## Resumo / checklist

- [ ] Sei a diferença entre `&x` (endereço de `x`) e `*p` (valor no endereço `p`)
- [ ] Consigo desenhar `p` e a variável apontada como duas casas separadas
- [ ] Sei por que uma função que altera o chamador precisa receber ponteiro
- [ ] Sei que `v[i]` ≡ `*(v + i)` e que a aritmética anda de elemento em elemento
- [ ] Sei quando usar `.` e quando usar `->`
- [ ] Sempre inicializo ponteiros e testo `NULL` antes de desreferenciar
