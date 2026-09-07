# Conceitos — Procedimentos e Funções

## A ideia em uma frase

Uma função é um pedaço de código com nome, que recebe entradas (parâmetros), faz uma
tarefa e (opcionalmente) devolve um resultado — permitindo dividir o programa em peças
pequenas, testáveis e reutilizáveis.

## O conceito

Três coisas envolvem uma função:

1. **Protótipo (declaração)** — anuncia a assinatura antes do primeiro uso, terminado em
   `;`. Serve para o compilador conferir os tipos das chamadas.
   `int fatorial(int n);`
2. **Definição** — o código de verdade.
   `int fatorial(int n) { ... return f; }`
3. **Chamada** — onde a função é usada: `int x = fatorial(5);`

Detalhes que importam:

- **`void`**: uma função sem retorno tem tipo `void` (um "procedimento"). Uma função que
  não recebe nada declara `(void)` na lista de parâmetros — inclusive `main(void)`.
- **`return`**: encerra a função e devolve o valor. Uma função não-`void` deve retornar em
  todos os caminhos.
- **Passagem por valor**: a função recebe **cópias** dos argumentos. Alterar um parâmetro
  dentro da função **não** afeta a variável de quem chamou. A exceção prática é o nome de
  um vetor, que é passado como endereço (ver
  [[../1.7 PASSAGEM DE PARÂMETROS POR VALOR E POR REFERÊNCIA/Conceitos|1.7]]).
- **Boa prática**: separar quem *calcula* de quem *imprime*. Uma função que calcula e
  retorna pode ser reaproveitada; uma que já imprime, não.

## Exemplos passo a passo

### Exemplo 1 — protótipo, definição, reúso

```c
#include <stdio.h>

int fatorial(int n);              // protótipo
int arranjo(int n, int k);        // protótipo

int main(void) {
    printf("%d\n", fatorial(5));        // 120
    printf("%d\n", arranjo(5, 2));      // 5!/3! = 20
    return 0;
}

int fatorial(int n) {             // definição
    int f = 1;
    for (int i = 2; i <= n; i++) f *= i;
    return f;                     // calcula e devolve — não imprime
}

int arranjo(int n, int k) {
    return fatorial(n) / fatorial(n - k);   // reaproveita fatorial
}
```

**O que observar:** `main` chama `fatorial` e `arranjo` que são definidas *depois* no
arquivo — funciona porque os protótipos lá em cima já contam ao compilador as assinaturas.
`arranjo` chama `fatorial` duas vezes; como `fatorial` retorna um valor, dá para compor.

### Exemplo 2 — `void` (procedimento) x função com retorno

```c
#include <stdio.h>

void imprime_linha(int n) {        // procedimento: faz um efeito, não devolve nada
    for (int i = 0; i < n; i++) putchar('-');
    putchar('\n');
}

int dobro(int x) {                 // função: devolve um valor
    return 2 * x;
}

int main(void) {
    imprime_linha(10);             // usada como comando
    int y = dobro(21);             // usada como valor
    printf("%d\n", y);             // 42
    return 0;
}
```

### Exemplo 3 — passagem por valor: a função não muda o original

```c
#include <stdio.h>

void tenta_zerar(int n) {
    n = 0;                 // altera só a cópia local
}

int main(void) {
    int x = 5;
    tenta_zerar(x);
    printf("%d\n", x);     // 5 — x não mudou
    return 0;
}
```

**Passo a passo:**

1. `x = 5` em `main`.
2. `tenta_zerar(x)` cria um novo `n` (cópia) valendo `5`, na pilha da função.
3. `n = 0` mexe nessa cópia.
4. A função retorna; a cópia some. O `x` de `main` nunca foi tocado.

Para a função **realmente** alterar `x`, ela precisa receber `&x` (um ponteiro) — assunto
de [[../1.7 PASSAGEM DE PARÂMETROS POR VALOR E POR REFERÊNCIA/Conceitos|1.7]].

## Erros comuns / pegadinhas

- **Chamar a função antes de declará-la.** Sem protótipo (nem definição acima), o
  compilador C moderno acusa erro.
- **Esquecer `return` numa função não-`void`** — devolve lixo; o programa segue com um
  valor sem sentido.
- **Achar que alterar um parâmetro muda o argumento** — não muda (passagem por valor).
- **`main()` sem `void`** em C — prefira `int main(void)`.
- **Função que calcula *e* imprime** — dificulta reúso e teste. Devolva o resultado.
- **Nomes de parâmetro iguais aos de variáveis globais** — a local "esconde" a global e
  gera confusão (ver [[../1.8 ESCOPO E VARIÁVEIS GLOBAIS/Conceitos|1.8]]).

## Resumo / checklist

- [ ] Sei escrever protótipo, definição e chamada
- [ ] Sei quando usar `void` (sem retorno) e `(void)` (sem parâmetros)
- [ ] Garanto `return` em todos os caminhos de uma função não-`void`
- [ ] Entendo passagem por valor: a função mexe em cópias
- [ ] Separo cálculo de impressão
