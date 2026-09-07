# Conceitos — Alocação Estática

## A ideia em uma frase

Alocação estática é quando o **tamanho e o tempo de vida** da memória já estão decididos
quando o programa é compilado — você não pede nem devolve esse espaço em tempo de execução.

## O conceito

Todo programa em execução usa a memória dividida em regiões. Três delas guardam variáveis:

```
+-----------------------------+  endereços baixos
|  código do programa         |
+-----------------------------+
|  variáveis globais/estáticas|  <- existem do início ao fim do programa
+-----------------------------+
|            ...              |
|      MEMÓRIA LIVRE (heap)    |  <- cresce para baixo com malloc  (assunto de 2.2)
|            ...              |
|      PILHA (stack)          |  <- cresce para cima a cada chamada de função
+-----------------------------+  endereços altos
```

- **Variáveis globais e `static`** ficam num espaço fixo ("segmento de dados"). Nascem
  quando o programa começa e só morrem quando ele termina.
- **Variáveis locais comuns** ficam na **pilha**. A cada chamada de função, um "quadro"
  é empilhado com as variáveis daquela função; quando a função retorna, o quadro é
  desempilhado e aquele espaço some. Por isso uma função não pode acessar as variáveis
  locais de outra.
- **Vetores de tamanho fixo** (`int v[10];`) são alocados junto com a variável — na pilha
  se forem locais, no segmento de dados se forem globais.

Nos três casos o compilador precisa saber **quantos bytes reservar** antes de rodar. É daí
que vem a limitação: se o tamanho só é conhecido em tempo de execução (por exemplo, o
número de alunos que o usuário vai digitar), a alocação estática obriga a escolher um
limite máximo arbitrário. Resolver isso é o papel da
[[../2.2 LOCAÇÃO DINÂMICA/Conceitos|alocação dinâmica]].

## Sintaxe / ferramentas

```c
int   g;              // global: segmento de dados, vive o programa todo, começa zerada
static int contador;  // como global, mas visível só neste arquivo .c

void f(void) {
    int x;            // local: pilha, vive só durante esta chamada, começa com LIXO
    static int n = 0; // local em escopo, mas vive o programa todo e mantém o valor
    int v[100];       // vetor fixo na pilha: 100 ints reservados agora
    n++;              // n lembra quantas vezes f foi chamada
}
```

| Forma | Onde fica | Tempo de vida | Valor inicial |
|---|---|---|---|
| global / `static` | segmento de dados | programa inteiro | zero |
| local | pilha | a chamada da função | lixo (indefinido) |
| `int v[N]` (N constante) | junto da variável | igual ao da variável | lixo, se local |

## Exemplos passo a passo

### Exemplo 1 — a limitação do vetor fixo

**Problema:** ler notas de uma turma. Não sabemos quantos alunos há.

```c
#include <stdio.h>

#define MAX_ALUNOS 50    // precisa ser escolhido ANTES de compilar

int main(void) {
    float notas[MAX_ALUNOS];
    int n;

    printf("Quantos alunos? ");
    scanf("%d", &n);

    if (n > MAX_ALUNOS) {              // e se a turma tiver 60?
        printf("Nao suporto mais de %d alunos.\n", MAX_ALUNOS);
        return 1;
    }

    for (int i = 0; i < n; i++)
        scanf("%f", &notas[i]);

    return 0;
}
```

**O que observar:**

- Se `MAX_ALUNOS` for grande demais, o programa desperdiça memória em quase toda execução.
- Se for pequeno demais, o programa simplesmente não atende turmas maiores.
- Não existe um valor "certo" — o problema é estrutural. Só a alocação dinâmica
  (`malloc(n * sizeof(float))`) permite reservar exatamente `n` posições.

### Exemplo 2 — `static` local: memória que lembra entre chamadas

**Problema:** contar quantas vezes uma função foi chamada.

```c
#include <stdio.h>

void registra(void) {
    static int chamadas = 0;   // inicializada UMA vez, na primeira execução
    int atual = 0;             // recriada a cada chamada, sempre 0 aqui

    chamadas++;
    atual++;
    printf("chamada #%d (atual = %d)\n", chamadas, atual);
}

int main(void) {
    registra();   // chamada #1 (atual = 1)
    registra();   // chamada #2 (atual = 1)
    registra();   // chamada #3 (atual = 1)
    return 0;
}
```

**Passo a passo:**

1. Primeira chamada: `chamadas` é criada no segmento de dados e recebe `0`; vira `1`.
   `atual` é criada na pilha, vira `1`, e some no fim da função.
2. Segunda chamada: `chamadas` **não** é reinicializada (a linha `= 0` só vale uma vez);
   continua de `1` e vira `2`. `atual` nasce de novo do zero.
3. Terceira chamada: `chamadas` vira `3`.

**O que observar:** `static` dá a uma variável local o *tempo de vida* de uma global,
mantendo o *escopo* restrito à função.

### Exemplo 3 — as três formas lado a lado

```c
#include <stdio.h>
#include <stdlib.h>

int global[5];                 // (1) estática: existe o programa todo

void exemplo(void) {
    int local[5];              // (2) pilha: existe só nesta chamada
    int *din = malloc(5 * sizeof(int));  // (3) heap: existe até free()

    local[0] = 1;
    din[0] = 2;
    global[0] = 3;
    printf("%d %d %d\n", local[0], din[0], global[0]);

    free(din);                 // (3) devolvida manualmente
}                              // (2) 'local' some aqui automaticamente

int main(void) {
    exemplo();
    return 0;
}
```

**O que observar:** só a forma (3) exige que **você** peça e devolva a memória. As formas
(1) e (2) são gerenciadas pelo compilador.

## Erros comuns / pegadinhas

- **Usar variável local sem inicializar.** `int x; printf("%d", x);` imprime lixo. Só
  globais e `static` começam zeradas.
- **Estourar a pilha (`stack overflow`).** Vetores locais gigantes (`int v[10000000];`) ou
  recursão profunda demais esgotam a pilha e o programa é encerrado pelo sistema.
- **Acessar `v[i]` fora dos limites.** `float notas[50]; notas[60] = 9;` é comportamento
  indefinido — C não verifica índices.
- **Retornar o endereço de um vetor local.** Ele deixa de existir quando a função retorna.
- **Esperar que `int v[n]` com `n` variável seja portável.** VLAs (vetores de tamanho
  variável) existem em C99, mas são opcionais em C11 e proibidos em muitos contextos;
  prefira `malloc` quando o tamanho é dinâmico.

## Resumo / checklist

- [ ] Sei diferenciar pilha (stack) e segmento de dados
- [x] Sei que local comum começa com lixo e global/`static` começa zerada
- [x] Entendo por que uma função não enxerga as locais de outra
- [ ] Sei explicar por que vetor fixo obriga a superdimensionar
- [x] Sei o que `static` faz numa variável local (tempo de vida x escopo)
