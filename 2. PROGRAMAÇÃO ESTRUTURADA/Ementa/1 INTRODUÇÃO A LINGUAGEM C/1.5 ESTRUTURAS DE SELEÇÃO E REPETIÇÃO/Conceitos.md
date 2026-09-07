# Conceitos — Estruturas de Seleção e Repetição

## A ideia em uma frase

Seleção (`if`, `switch`) escolhe **qual** bloco de código roda; repetição (`while`, `for`,
`do-while`) faz um bloco rodar **várias vezes**.

## O conceito

**Seleção:**

- `if (cond) { ... } else { ... }` — decisão simples. Encadeando `else if` você trata
  vários casos.
- `switch (expr) { case v1: ...; break; ... default: ...; }` — compara `expr` (um inteiro
  ou `char`) contra valores constantes. Sem `break`, a execução **"cai"** para o próximo
  `case` (*fall-through*).

**Repetição:**

- `while (cond) { ... }` — testa **antes**; o corpo pode não rodar nenhuma vez.
- `for (init; cond; passo) { ... }` — mesma coisa que `while`, com as três partes juntas
  no topo. Equivale a: `init; while (cond) { ...; passo; }`.
- `do { ... } while (cond);` — testa **depois**; o corpo roda **pelo menos uma vez**.
  Ótimo para validar entrada do usuário.

**Controle dentro do laço:**

- `break` — sai do laço (ou `switch`) imediatamente.
- `continue` — pula para a próxima iteração.

Os três laços são intercambiáveis; escolha pelo que fica mais legível: `for` quando há
contador claro, `while` quando a parada depende de uma condição, `do-while` quando o corpo
tem que rodar ao menos uma vez.

## Exemplos passo a passo

### Exemplo 1 — os três laços somando 1..n

```c
#include <stdio.h>

int main(void) {
    int n = 5, soma, i;

    soma = 0; i = 1;
    while (i <= n) { soma += i; i++; }
    printf("while:    %d\n", soma);          // 15

    soma = 0;
    for (i = 1; i <= n; i++) soma += i;
    printf("for:      %d\n", soma);          // 15

    soma = 0; i = 1;
    do { soma += i; i++; } while (i <= n);
    printf("do-while: %d\n", soma);          // 15
    return 0;
}
```

**Passo a passo do `while`:** `i=1,soma=1` → `i=2,soma=3` → `i=3,soma=6` → `i=4,soma=10`
→ `i=5,soma=15` → `i=6`: `6 <= 5` falso, para.

**Diferença com `n = 0`:** o `while` e o `for` não somariam nada (`soma = 0`); o `do-while`
somaria `i=1` uma vez antes de testar, dando `soma = 1`.

### Exemplo 2 — `do-while` para validar entrada

```c
#include <stdio.h>

int main(void) {
    int idade;
    do {
        printf("Idade (0 a 130): ");
        scanf("%d", &idade);
    } while (idade < 0 || idade > 130);

    printf("Ok: %d\n", idade);
    return 0;
}
```

**O que observar:** a pergunta precisa aparecer pelo menos uma vez, então `do-while` é
natural. Com `while` seria preciso duplicar o `printf`/`scanf` antes do laço.

### Exemplo 3 — `switch` com fall-through proposital e o `break` que falta

```c
#include <stdio.h>

int main(void) {
    char c = '\t';
    int brancos = 0, outros = 0;

    switch (c) {
        case ' ':
        case '\t':
        case '\n':
            brancos++;      // os três casos caem aqui de propósito
            break;
        default:
            outros++;
    }
    printf("brancos=%d outros=%d\n", brancos, outros);   // brancos=1 outros=0
    return 0;
}
```

**O que observar:** empilhar `case` sem código entre eles é o uso *bom* do fall-through.
O uso *ruim* é esquecer um `break` no fim de um caso com código — aí ele executa o
próximo caso sem querer.

### Exemplo 4 — o bug clássico do `continue` no `while`

```c
// ERRADO: loop infinito
int i = 0;
while (i < 10) {
    if (i == 5) continue;   // pula o resto do corpo -> pula o i++ -> i trava em 5
    printf("%d ", i);
    i++;
}
```

```c
// CERTO: em for, o "i++" roda fora do corpo, então continue não o pula
for (int i = 0; i < 10; i++) {
    if (i == 5) continue;
    printf("%d ", i);
}
```

**Por que acontece:** `continue` volta ao teste do laço sem executar o que vem depois dele
no corpo. No `while`, o incremento está no corpo; no `for`, está no cabeçalho.

## Erros comuns / pegadinhas

- **`;` logo depois do `for`/`while`.** `while (i < 10);` cria um laço de corpo vazio.
- **`=` em vez de `==` no teste.** `if (x = 0)` atribui e é sempre falso.
- **`switch` sem `break`.** Fall-through acidental executa casos seguintes.
- **`continue` no `while` pulando o incremento** — loop infinito (Exemplo 4).
- **Alterar a variável de controle dentro do corpo do `for`** sem perceber que o passo
  também mexe nela.
- **Comparar `float` no teste do laço** (`for (f = 0; f != 1.0; f += 0.1)`) — o
  arredondamento faz `f` nunca ser exatamente `1.0`.

## Resumo / checklist

- [ ] Sei quando o corpo de cada laço pode rodar zero vezes (`while`/`for`) e quando roda
  ao menos uma (`do-while`)
- [ ] Sei reescrever um `for` como `while` equivalente
- [ ] Sei o que é fall-through no `switch` e quando ele é proposital
- [ ] Sei explicar o loop infinito do `continue` no `while`
- [ ] Uso `do-while` para validar entrada
- [ ] Não deixo `;` sobrando depois de `for`/`while`
