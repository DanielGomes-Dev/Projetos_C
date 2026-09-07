# Conceitos — Recursividade

## A ideia em uma frase

Uma função recursiva resolve um problema chamando a si mesma para resolver uma versão
**menor** do mesmo problema, até chegar a um caso tão pequeno que a resposta é imediata.

## O conceito

Todo algoritmo recursivo tem duas partes:

1. **Caso base** — a situação mínima, respondida sem recursão. É a condição de parada.
2. **Passo recursivo** — resolve o problema atual supondo que a chamada menor "já
   funciona", e combina o resultado dela.

Exemplo com fatorial. A definição matemática já é recursiva:

```
0! = 1                  <- caso base
n! = n * (n-1)!         <- passo recursivo
```

Traduzindo direto para C:

```c
int fatorial(int n) {
    if (n == 0) return 1;            // caso base
    return n * fatorial(n - 1);      // passo recursivo
}
```

**Por que funciona:** cada chamada de função tem seu próprio espaço na
[[../2 GERÊNCIA DE MEMÓRIA/2.1 ALOCAÇÃO ESTÁTICA/Conceitos|pilha]] — um "quadro" com
suas próprias variáveis e seu próprio `n`. `fatorial(3)` e `fatorial(2)` não colidem:
são quadros separados, empilhados um sobre o outro. Quando o caso base é atingido, os
quadros vão sendo desempilhados e cada um devolve seu resultado para quem o chamou.

## Sintaxe / ferramentas

Não há sintaxe especial: recursão é só uma função que se chama. O que você controla:

| Elemento | Papel | Se faltar / errar |
|---|---|---|
| caso base | encerra a recursão | recursão infinita → *stack overflow* |
| passo que **diminui** o argumento | garante que o caso base é alcançado | recursão infinita mesmo com caso base |
| protótipo antes do uso | necessário na recursão **indireta** (A↔B) | erro de compilação |

- **Recursão direta:** a função chama a si mesma (`fatorial` → `fatorial`).
- **Recursão indireta (mútua):** `A` chama `B`, que chama `A` de volta.

## Exemplos passo a passo

### Exemplo 1 — `fatorial(4)`: traçando a pilha

```c
#include <stdio.h>

int fatorial(int n) {
    if (n == 0) return 1;
    return n * fatorial(n - 1);
}

int main(void) {
    printf("%d\n", fatorial(4));   // 24
    return 0;
}
```

**Descida (empilhando):**

```
fatorial(4) = 4 * fatorial(3)      ... precisa de fatorial(3)
  fatorial(3) = 3 * fatorial(2)    ... precisa de fatorial(2)
    fatorial(2) = 2 * fatorial(1)
      fatorial(1) = 1 * fatorial(0)
        fatorial(0) = 1            <- CASO BASE, para de descer
```

**Subida (desempilhando, cada um devolve para o de cima):**

```
        fatorial(0) devolve 1
      fatorial(1) devolve 1 * 1 = 1
    fatorial(2) devolve 2 * 1 = 2
  fatorial(3) devolve 3 * 2 = 6
fatorial(4) devolve 4 * 6 = 24
```

**O que observar:** a multiplicação `n * ...` só acontece **na volta**, depois que a
chamada interna já devolveu seu valor. Existem 5 quadros na pilha ao mesmo tempo no ponto
mais fundo.

### Exemplo 2 — somar um vetor recursivamente

**Problema:** somar `v[0..n-1]` sem laço.

Ideia: "a soma dos `n` primeiros é `v[n-1]` mais a soma dos `n-1` primeiros".

```c
#include <stdio.h>

int soma(int *v, int n) {
    if (n == 0) return 0;                 // caso base: vetor vazio soma 0
    return v[n - 1] + soma(v, n - 1);     // último elemento + soma do resto
}

int main(void) {
    int a[] = {5, 2, 9, 1};
    printf("%d\n", soma(a, 4));           // 17
    return 0;
}
```

**Passo a passo:**

```
soma(a,4) = a[3] + soma(a,3) = 1 + soma(a,3)
soma(a,3) = a[2] + soma(a,2) = 9 + soma(a,2)
soma(a,2) = a[1] + soma(a,1) = 2 + soma(a,1)
soma(a,1) = a[0] + soma(a,0) = 5 + soma(a,0)
soma(a,0) = 0                              <- caso base
-> 5 + 0 = 5 -> 2 + 5 = 7 -> 9 + 7 = 16 -> 1 + 16 = 17
```

### Exemplo 3 — quando a recursão é a forma natural: Torre de Hanói

**Problema:** mover `n` discos do pino `A` para o `C`, usando `B` como apoio, movendo um
disco por vez e nunca pondo um disco maior sobre um menor.

Ideia recursiva: para mover `n` discos de `A` para `C`:
1. mova `n-1` discos de `A` para `B` (recursão);
2. mova o disco `n` de `A` para `C` (um movimento);
3. mova `n-1` discos de `B` para `C` (recursão).

```c
#include <stdio.h>

void hanoi(int n, char origem, char apoio, char destino) {
    if (n == 0) return;                          // caso base: nada a mover
    hanoi(n - 1, origem, destino, apoio);        // passo 1
    printf("disco %d: %c -> %c\n", n, origem, destino);  // passo 2
    hanoi(n - 1, apoio, origem, destino);        // passo 3
}

int main(void) {
    hanoi(3, 'A', 'B', 'C');
    return 0;
}
```

Saída:

```
disco 1: A -> C
disco 2: A -> B
disco 1: C -> B
disco 3: A -> C
disco 1: B -> A
disco 2: B -> C
disco 1: A -> C
```

**O que observar:** a versão iterativa disso é bem mais difícil de escrever. Quando o
problema já se define em termos de si mesmo, a recursão é o caminho mais curto.

### Exemplo 4 — recursão indireta (mútua)

```c
#include <stdio.h>

int eh_impar(int n);            // protótipo necessário: eh_par usa eh_impar antes de ele existir

int eh_par(int n) {
    if (n == 0) return 1;
    return eh_impar(n - 1);
}
int eh_impar(int n) {
    if (n == 0) return 0;
    return eh_par(n - 1);
}

int main(void) {
    printf("%s\n", eh_par(7) ? "par" : "impar");   // impar
    return 0;
}
```

`eh_par(7)` → `eh_impar(6)` → `eh_par(5)` → ... → `eh_par(1)` → `eh_impar(0)` → `0`.

## Recursão x iteração

Todo algoritmo recursivo tem uma versão iterativa equivalente (com laço e, às vezes, uma
pilha explícita). Comparando:

| | Recursão | Iteração |
|---|---|---|
| Código | mais curto, colado na definição do problema | mais verboso às vezes |
| Custo | um quadro de pilha por chamada (memória + tempo de chamada) | sem esse custo |
| Natural para | árvores, divisão e conquista, Hanói, backtracking | somatórios, varreduras lineares |

O `fatorial` iterativo (`for` acumulando um produto) é mais eficiente. Já um percurso em
árvore recursivo é muito mais simples que o iterativo.

## Erros comuns / pegadinhas

- **Sem caso base** (ou caso base inalcançável): a pilha cresce até estourar
  (*stack overflow*) e o programa é morto pelo sistema.
- **Passo que não reduz o problema:** `return f(n)` em vez de `return f(n - 1)` — tem caso
  base, mas nunca chega nele.
- **Fibonacci ingênuo é exponencial.** `fib(n) = fib(n-1) + fib(n-2)` recalcula os mesmos
  valores um número enorme de vezes; `fib(50)` trava na prática. Use iteração ou
  memoização para Fibonacci.
- **Esquecer o protótipo na recursão mútua** — erro de compilação, porque a primeira
  função referencia a segunda antes de ela ser declarada.
- **Achar que recursão "economiza memória".** Ela troca um laço por uma pilha de quadros —
  geralmente gasta *mais*.

## Resumo / checklist

- [ ] Identifico caso base e passo recursivo em qualquer função recursiva
- [ ] Sei traçar a descida (empilha) e a subida (desempilha e combina) de `fatorial(4)`
- [ ] Garanto que o passo recursivo caminha em direção ao caso base
- [ ] Sei por que falta de caso base causa *stack overflow*
- [ ] Sei dizer quando recursão é mais natural e quando iteração é melhor
- [ ] Sei por que `fib` recursivo ingênuo é inviável
