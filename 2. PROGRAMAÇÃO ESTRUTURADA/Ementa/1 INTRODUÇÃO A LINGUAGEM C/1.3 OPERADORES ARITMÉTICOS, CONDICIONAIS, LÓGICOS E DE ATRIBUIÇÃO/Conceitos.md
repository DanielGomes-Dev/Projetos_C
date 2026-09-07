# Conceitos — Operadores

## A ideia em uma frase

Operadores combinam valores para produzir novos valores; o resultado depende do **tipo dos
operandos**, da **precedência** (quem age primeiro) e, nos lógicos, do **curto-circuito**.

## O conceito

Grupos principais:

- **Aritméticos:** `+  -  *  /  %` (e `-` unário). `/` entre inteiros **trunca**; `%` é o
  resto e só funciona com inteiros.
- **Relacionais e lógicos:** `<  >  <=  >=  ==  !=` e `&&  ||  !`. C **não tem tipo
  booleano**: `0` é falso, qualquer outro valor é verdadeiro, e uma comparação produz
  sempre `0` ou `1`.
- **Atribuição:** `=` e os compostos `+=  -=  *=  /=  %=`. Atribuição em C é uma
  **expressão com valor**, o que permite `a = b = 0;`.
- **Incremento/decremento:** `++` e `--`, nas formas prefixada e pós-fixada.
- **Ternário:** `condição ? valor_se_verdadeiro : valor_se_falso`.
- **`sizeof`:** tamanho em bytes de um tipo ou variável.

Três regras que evitam a maioria dos bugs:

1. **A conta é feita na precisão dos operandos.** `5 / 2` é `2`; `5.0 / 2` é `2.5`.
2. **`&&` e `||` avaliam da esquerda para a direita e param assim que o resultado é
   conhecido** (curto-circuito).
3. **`op=` põe parênteses implícitos na direita.** `x *= a + b;` é `x = x * (a + b)`.

## Sintaxe / ferramentas

Precedência (do que age primeiro para o que age por último), simplificada:

| Nível | Operadores |
|---|---|
| mais forte | `()` `[]` `.` `->` `++`/`--` pós-fixados |
| | `!` `-` unário `*` (deref) `&` (endereço) `sizeof` `++`/`--` prefixados |
| | `*` `/` `%` |
| | `+` `-` |
| | `<` `<=` `>` `>=` |
| | `==` `!=` |
| | `&&` |
| | `||` |
| | `?:` |
| mais fraco | `=` `+=` `-=` ... |

Armadilhas de precedência que **exigem parênteses**:

- `(x & MASCARA) == 0` — `&` bit a bit é mais fraco que `==`.
- `(c = getchar()) != '\n'` — `=` é mais fraco que `!=`.

## Exemplos passo a passo

### Exemplo 1 — divisão inteira x divisão real

```c
#include <stdio.h>

int main(void) {
    int a = 3.5;             // trunca na atribuição: a = 3
    double b = a / 2.0;      // a vira double: b = 1.5
    double c = 1 / 3 + b;    // 1/3 são dois int -> 0, ANTES de somar: c = 1.5

    printf("a=%d b=%.1f c=%.1f\n", a, b, c);
    printf("7 %% 3 = %d\n", 7 % 3);     // 1
    return 0;
}
```

**Passo a passo de `c`:** `1 / 3` é avaliado primeiro, com dois inteiros → `0` (trunca).
Só depois soma-se `b` (1.5). O tipo `double` de `c` não "conserta" o `1/3` que já virou
zero.

### Exemplo 2 — pré x pós-incremento

```c
#include <stdio.h>

int main(void) {
    int n = 5, x;

    x = n++;    // x recebe 5 (valor ANTES); depois n vira 6
    printf("x=%d n=%d\n", x, n);   // x=5 n=6

    n = 5;
    x = ++n;    // n vira 6 PRIMEIRO; x recebe 6
    printf("x=%d n=%d\n", x, n);   // x=6 n=6
    return 0;
}
```

**O que observar:** `n++` e `++n` deixam `n` no mesmo estado final. A diferença é só o
**valor da expressão** no momento: o antigo (`n++`) ou o novo (`++n`).

### Exemplo 3 — curto-circuito protege um acesso inválido

```c
#include <stdio.h>

int main(void) {
    int v[5] = {10, 20, 30, 40, 50};
    int alvo = 30, i = 0;

    while (i < 5 && v[i] != alvo)   // se i vira 5, "i < 5" é falso e v[i] NEM é lido
        i++;

    if (i < 5) printf("achei no indice %d\n", i);
    else       printf("nao achei\n");
    return 0;
}
```

**Passo a passo:** `i=0`: `0<5` verdadeiro, `v[0]=10 != 30` verdadeiro → `i=1`. `i=1`:
`v[1]=20 != 30` → `i=2`. `i=2`: `v[2]=30 != 30` é **falso** → sai do laço com `i=2`.

Se o alvo não existisse, `i` chegaria a `5`, `5 < 5` seria falso, e `v[5]` (fora do vetor)
**não** seria avaliado graças ao `&&`. Inverter a ordem (`v[i] != alvo && i < 5`) quebraria
isso.

### Exemplo 4 — ternário e atribuição composta

```c
#include <stdio.h>

int main(void) {
    int a = 7, b = 12;
    int maior = (a > b) ? a : b;      // 12
    printf("%d\n", maior);

    int x = 10;
    x *= 2 + 1;                       // x = x * (2 + 1) = 30
    printf("%d\n", x);
    return 0;
}
```

## Erros comuns / pegadinhas

- **`=` no lugar de `==`.** `if (x = 5)` atribui 5 a `x` e sempre é verdadeiro. Compila.
- **Esperar fração de `int / int`.** `float m = soma / n;` trunca antes de virar `float`.
  Faça `soma / (double) n`.
- **`%` com `float`.** Não compila; use `fmod` de `<math.h>` se precisar.
- **Precedência de `&`/`|`.** `if (x & 1 == 0)` é `x & (1 == 0)` = `x & 0` = 0. Use
  `(x & 1) == 0`.
- **Contar com a ordem de avaliação dos operandos.** `f() + g()` não garante qual roda
  primeiro; `v[i] = i++` é comportamento indefinido.
- **`&&`/`||` sem parênteses junto de `=`.** `while (c = getchar() != EOF)` compara antes
  de atribuir.

## Resumo / checklist

- [ ] Sei prever `int / int`, `%`, e como forçar divisão real
- [ ] Sei a diferença de valor entre `n++` e `++n`
- [ ] Entendo curto-circuito e sei usá-lo para evitar acesso inválido
- [ ] Sei as duas armadilhas de precedência (`&` vs `==`, `=` vs `!=`)
- [ ] Não confundo `=` com `==`
- [ ] Sei que C não tem booleano: `0` falso, resto verdadeiro
