# Conceitos — Tipos Primitivos de Dados

## A ideia em uma frase

O tipo de uma variável diz ao compilador **quantos bytes reservar** para ela e **como
interpretar** os bits guardados ali (número inteiro, número com fração, caractere).

## O conceito

Em C, toda variável precisa ser declarada com um tipo antes de usar. Os tipos básicos:

| Tipo | Guarda | Tamanho típico | Precisão / faixa aproximada |
|---|---|---|---|
| `char` | um caractere (na verdade, um inteiro pequeno) | 1 byte | -128 a 127 |
| `int` | inteiro | 4 bytes | ~ -2,1 bi a 2,1 bi |
| `float` | número real | 4 bytes | ~6-7 dígitos significativos |
| `double` | número real (precisão dupla) | 8 bytes | ~15-16 dígitos significativos |

Qualificadores mudam faixa e representação:

- `short` / `long` — pedem menos / mais bytes (`short int`, `long int`).
- `unsigned` — abre mão do sinal e dobra o limite positivo (`unsigned int`: 0 a ~4,2 bi).

**Duas verdades que causam bug:**

1. **O tamanho não é garantido pela linguagem.** `int` costuma ter 4 bytes hoje, mas já
   teve 2. Quando o tamanho importa, use `sizeof`.
2. **`char` é um número.** Ele guarda o código do caractere na tabela ASCII (`'A'` é 65).
   Por isso `'A' + 1` vale `'B'`, e `digito - '0'` converte o caractere `'7'` no inteiro `7`.

## Sintaxe / ferramentas

```c
int    idade = 30;
char   inicial = 'M';       // aspas simples: um caractere
double altura = 1.75;       // constante real sem sufixo é double
float  peso = 80.5f;        // sufixo f: constante float
long   populacao = 8000000000L;   // sufixo L: constante long
unsigned int codigo = 4000000000u; // sufixo u: sem sinal
```

Sufixos de constante: `L` (long), `U` (unsigned), `F` (float). Sem sufixo, um número com
ponto é `double` e um número inteiro é `int`.

`sizeof` devolve um `size_t` (inteiro sem sinal) — imprima com `%zu`.

## Exemplos passo a passo

### Exemplo 1 — ver os tamanhos na sua máquina

```c
#include <stdio.h>

int main(void) {
    printf("char:   %zu byte(s)\n", sizeof(char));
    printf("int:    %zu byte(s)\n", sizeof(int));
    printf("float:  %zu byte(s)\n", sizeof(float));
    printf("double: %zu byte(s)\n", sizeof(double));
    return 0;
}
```

**O que observar:** `sizeof(char)` é sempre `1` por definição. Os outros dependem do
compilador/máquina — rode e confirme, não decore.

### Exemplo 2 — `char` é um inteiro

```c
#include <stdio.h>

int main(void) {
    char c = 'A';
    printf("%c vale %d\n", c, c);       // A vale 65
    printf("%c\n", c + 1);              // B  (66)

    char digito = '7';
    int  n = digito - '0';             // '7'(55) - '0'(48) = 7
    printf("%d\n", n * 2);             // 14
    return 0;
}
```

**Passo a passo de `digito - '0'`:** `'7'` é o código 55, `'0'` é o código 48.
`55 - 48 = 7`. Esse é o truque padrão para transformar um dígito-caractere no seu valor
numérico.

### Exemplo 3 — divisão inteira e perda de precisão

```c
#include <stdio.h>

int main(void) {
    int a = 7, b = 2;
    printf("%d\n", a / b);            // 3  (a parte fracionária é descartada)
    printf("%.1f\n", a / (double) b); // 3.5 (cast força divisão real)

    float x = 0.1f;
    printf("%.10f\n", x);            // 0.1000000015  (float não representa 0,1 exato)
    return 0;
}
```

**O que observar:**

- `a / b` com dois `int` dá um `int`: `7 / 2` é `3`, não `3.5`. Para o resultado real,
  pelo menos um operando precisa ser `double` (aqui, via `(double) b`).
- `float` tem só ~7 dígitos de precisão; para dinheiro e cálculos sensíveis, use `double`.

### Exemplo 4 — variável não inicializada e overflow

```c
#include <stdio.h>
#include <limits.h>

int main(void) {
    int lixo;                      // não inicializada
    printf("%d\n", lixo);          // imprime um valor imprevisível (bits que estavam ali)

    int max = INT_MAX;             // maior int possível
    printf("%d\n", max + 1);       // overflow: "dá a volta" para um valor negativo
    return 0;
}
```

**O que observar:** só variáveis globais e `static` começam zeradas. Uma variável local
sem valor inicial contém lixo — a causa clássica de bugs "que funcionam às vezes".

## Erros comuns / pegadinhas

- **Usar variável local antes de atribuir um valor** — lixo, não zero.
- **`int / int` esperando fração** — `media = soma / n` trunca; faça `soma / (double) n`.
- **Guardar `getchar()` em `char`** — use `int`, senão o valor `EOF` não é representável.
- **`%d` para `sizeof`** — o tipo é `size_t`; o especificador certo é `%zu`.
- **Comparar `float` com `==`** — por causa do arredondamento, `0.1f + 0.2f != 0.3f`.
  Compare pela diferença: `fabs(a - b) < 1e-6`.
- **Assumir que `int` tem 4 bytes** em código que precisa de tamanho exato — use `sizeof`
  ou os tipos de `<stdint.h>` (`int32_t`).

## Resumo / checklist

- [ ] Sei o que cada tipo básico guarda e seu tamanho típico
- [ ] Sei que `sizeof` é a única forma confiável de saber o tamanho
- [ ] Entendo que `char` é um inteiro e sei converter dígito↔número
- [ ] Sei prever o resultado de `int / int` e como forçar divisão real
- [ ] Conheço os sufixos `L`, `U`, `F` e o tipo padrão de cada constante
- [ ] Sei por que não se compara `float` com `==`
