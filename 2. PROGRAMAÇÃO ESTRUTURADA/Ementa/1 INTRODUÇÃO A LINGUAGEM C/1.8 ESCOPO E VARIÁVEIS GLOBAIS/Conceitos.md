# Conceitos — Escopo e Variáveis Globais

## A ideia em uma frase

**Escopo** é *onde* um nome pode ser usado; **tempo de vida** é *por quanto tempo* a
variável existe na memória. As três classes de C — automática, global e `static` —
combinam esses dois eixos de jeitos diferentes.

## O conceito

| Classe | Onde declara | Escopo (quem enxerga) | Tempo de vida | Valor inicial |
|---|---|---|---|---|
| automática (local) | dentro de `{ }` | só aquele bloco/função | enquanto o bloco executa | lixo |
| global (externa) | fora de qualquer função | do ponto da declaração até o fim do arquivo (e outros arquivos com `extern`) | programa inteiro | zero |
| `static` local | dentro de função, com `static` | só aquela função | programa inteiro | zero |
| `static` global | fora de função, com `static` | só aquele arquivo `.c` | programa inteiro | zero |

Pontos-chave:

- Uma variável local "some" quando a função retorna. Duas funções com uma variável `i`
  cada têm dois `i` sem relação nenhuma.
- Uma variável global existe o tempo todo e é compartilhada por todas as funções — o que
  é conveniente e perigoso: cria dependência escondida entre funções.
- `static` numa variável local dá a ela o **tempo de vida** de uma global mantendo o
  **escopo** restrito à função. É a forma de uma função "lembrar" algo entre chamadas.
- `static` numa variável ou função **global** a esconde dos outros arquivos — é o
  mecanismo de privacidade de módulo (ver [[../../4 PROGRAMAÇÃO COM MÓDULOS/Conceitos|módulos]]).

**Recomendação prática:** evite variáveis globais. Prefira passar dados por parâmetro
(ver [[../1.7 PASSAGEM DE PARÂMETROS POR VALOR E POR REFERÊNCIA/Conceitos|1.7]]). Use
`static` para esconder o que só um trecho do programa precisa conhecer.

## Exemplos passo a passo

### Exemplo 1 — mesmo nome, três comportamentos

```c
#include <stdio.h>

int global = 0;                  // vive o programa todo, todos veem

void conta_global(void)   { global++; }

void conta_static(void) {
    static int s = 0;            // vive o programa todo, só esta função vê
    s++;
    printf("static: %d\n", s);
}

void conta_auto(void) {
    int a = 0;                   // recriada do zero a cada chamada
    a++;
    printf("auto:   %d\n", a);
}

int main(void) {
    for (int i = 0; i < 3; i++) {
        conta_global();
        conta_static();
        conta_auto();
    }
    printf("global final: %d\n", global);
    return 0;
}
```

Saída:

```
static: 1
auto:   1
static: 2
auto:   1
static: 3
auto:   1
global final: 3
```

**O que observar:** `s` acumula (1, 2, 3) porque persiste entre chamadas. `a` imprime
sempre `1` porque nasce zerada toda vez. `global` termina em `3` — foi incrementada em
todas as iterações.

### Exemplo 2 — `static` local para dar formato à saída

**Problema:** imprimir uma lista de valores quebrando a linha a cada 5.

```c
#include <stdio.h>

void imprime(float x) {
    static int n = 0;      // conta quantos já foram impressos, entre chamadas
    printf("%6.1f", x);
    n++;
    if (n % 5 == 0) printf("\n");
}

int main(void) {
    float v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    for (int i = 0; i < 11; i++) imprime(v[i]);
    printf("\n");
    return 0;
}
```

**O que observar:** `imprime` não recebe "quantos já saíram" como parâmetro — ela lembra
sozinha via `static int n`. Uma variável local comum voltaria a `0` a cada chamada e a
quebra de linha nunca aconteceria.

### Exemplo 3 — variável local "escondendo" a global

```c
#include <stdio.h>

int x = 100;          // global

void f(void) {
    int x = 1;        // local: dentro de f, este x "esconde" o global
    x++;
    printf("dentro de f: %d\n", x);      // 2
}

int main(void) {
    f();
    printf("global x: %d\n", x);         // 100 — nunca foi tocado
    return 0;
}
```

**O que observar:** quando existe um nome local igual ao global, o local vence dentro do
seu escopo. Isso é legal em C mas confunde — evite repetir nomes.

## Erros comuns / pegadinhas

- **Usar uma automática sem inicializar** achando que vale `0` — só global e `static`
  começam zeradas.
- **Depender de variável global** para comunicar funções — vira bug difícil quando duas
  funções mexem nela em ordem inesperada.
- **Esperar que uma local comum "lembre" o valor** entre chamadas — precisa ser `static`.
- **Nome local igual ao global** — o local esconde o global silenciosamente.
- **Definir uma global em um `.h`** — cada `.c` que incluir cria a sua; use `extern` no
  `.h` e a definição em um único `.c` (ver [[../../4 PROGRAMAÇÃO COM MÓDULOS/Conceitos|módulos]]).

## Resumo / checklist

- [ ] Sei diferenciar escopo (onde) de tempo de vida (por quanto tempo)
- [ ] Sei o comportamento das quatro combinações (auto, global, `static` local, `static` global)
- [ ] Sei por que `static` local "lembra" entre chamadas
- [ ] Sei que `static` global esconde a variável/função dos outros arquivos
- [ ] Prefiro parâmetros a variáveis globais
