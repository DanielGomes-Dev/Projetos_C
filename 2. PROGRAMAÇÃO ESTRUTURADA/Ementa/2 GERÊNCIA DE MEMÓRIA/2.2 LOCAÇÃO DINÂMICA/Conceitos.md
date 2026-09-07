# Conceitos — Alocação Dinâmica

## A ideia em uma frase

Alocação dinâmica é pedir memória ao sistema **durante a execução**, na quantidade exata
que você só descobre naquele momento, e devolvê-la quando não precisar mais.

## O conceito

A [[../2.1 ALOCAÇÃO ESTÁTICA/Conceitos|alocação estática]] exige decidir o tamanho antes
de compilar. Muitas vezes isso é impossível: quantos números o usuário vai digitar?
quantas linhas tem o arquivo? quantos nós a lista vai ter?

A resposta é uma região de memória chamada **heap** (ou "memória livre"). Você pede um
pedaço com `malloc`, o sistema separa esse pedaço e te devolve **o endereço do início
dele**. Esse pedaço fica reservado — mesmo depois que a função que o pediu termina — até
você devolvê-lo explicitamente com `free`.

Duas casas, não uma:

```
PILHA                         HEAP
+----------------+            +------------------------------+
| v (ponteiro)   | ---------> | ? | ? | ? | ? | ? | ? | ...  |
| = endereço 4096|            | (n inteiros contíguos)       |
+----------------+            +------------------------------+
```

- `v` é uma variável ponteiro comum: mora na pilha, some quando a função retorna.
- A área apontada por `v` mora no heap: **não** some sozinha. Se você perder o endereço
  sem dar `free`, aquele espaço fica ocupado até o programa acabar — é um *vazamento*.

## Sintaxe / ferramentas

Tudo em `<stdlib.h>`.

| Função | O que faz | Observação |
|---|---|---|
| `malloc(nbytes)` | reserva `nbytes` e devolve o endereço; conteúdo é **lixo** | `NULL` se falhar |
| `calloc(qtd, tam)` | reserva `qtd * tam` bytes e **zera tudo** | mais lento; útil quando quer zeros |
| `realloc(p, novo)` | redimensiona o bloco de `p` para `novo` bytes, preservando o conteúdo | pode mover o bloco e devolver outro endereço |
| `free(p)` | devolve ao sistema o bloco que `p` aponta | só em endereço vindo de `malloc`/`calloc`/`realloc` |

Forma idiomática:

```c
int n = 10;
int *v = malloc(n * sizeof(int));   // n inteiros; sizeof torna portável
if (v == NULL) {                    // SEMPRE checar
    printf("Memoria insuficiente.\n");
    return 1;
}
// ... usa v[0] .. v[n-1] normalmente ...
free(v);                            // devolve
v = NULL;                           // evita usar o endereço velho por engano
```

Use `n * sizeof(int)`, nunca `n * 4` — o tamanho de `int` muda entre compiladores.
O *cast* `(int *) malloc(...)` é opcional em C (não em C++); pode omitir.

## Exemplos passo a passo

### Exemplo 1 — vetor do tamanho exato que o usuário pediu

**Problema:** ler `n` valores (com `n` digitado) e imprimir a média.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    printf("Quantos valores? ");
    scanf("%d", &n);

    float *v = malloc(n * sizeof(float));   // 1
    if (v == NULL) return 1;                // 2

    for (int i = 0; i < n; i++)             // 3
        scanf("%f", &v[i]);

    float soma = 0;
    for (int i = 0; i < n; i++)
        soma += v[i];
    printf("Media: %.2f\n", soma / n);

    free(v);                                // 4
    return 0;
}
```

**Passo a passo:**

1. O usuário digita `n = 3`. `malloc(3 * 4)` reserva 12 bytes no heap e devolve, digamos,
   o endereço `5000`. `v` (na pilha) passa a valer `5000`.
2. Se o sistema não tivesse 12 bytes livres, `malloc` devolveria `NULL` e o programa
   encerraria antes de usar `v` — nunca desreferencie um ponteiro sem checar.
3. `v[i]` funciona exatamente como num vetor estático: `v[0]` é o endereço `5000`,
   `v[1]` é `5004`, `v[2]` é `5008`.
4. `free(v)` devolve os 12 bytes. A variável `v` ainda existe e ainda contém `5000`, mas
   aquele endereço não é mais seu — não pode ler nem escrever lá.

**O que observar:** troque `n` de 3 para 3000 e o programa continua correto sem mudar uma
linha. Com vetor estático seria preciso escolher um limite.

### Exemplo 2 — crescer o vetor conforme os dados chegam, com `realloc`

**Problema:** ler números até o usuário digitar `0`, sem saber quantos serão.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int capacidade = 2;                         // começa pequeno
    int tamanho = 0;
    int *v = malloc(capacidade * sizeof(int));

    int x;
    while (scanf("%d", &x) == 1 && x != 0) {
        if (tamanho == capacidade) {            // encheu: dobra o espaço
            capacidade *= 2;
            int *novo = realloc(v, capacidade * sizeof(int));
            if (novo == NULL) { free(v); return 1; }
            v = novo;                           // realloc pode ter movido o bloco
        }
        v[tamanho++] = x;
    }

    printf("Li %d numeros: ", tamanho);
    for (int i = 0; i < tamanho; i++) printf("%d ", v[i]);
    printf("\n");

    free(v);
    return 0;
}
```

**Passo a passo (entrada `7 8 9 0`):**

1. Capacidade 2, tamanho 0. Lê `7` → `v[0]=7`, tamanho 1.
2. Lê `8` → `v[1]=8`, tamanho 2.
3. Lê `9`: `tamanho == capacidade`. `realloc` amplia para 4 posições, preservando `7` e `8`.
   `v[2]=9`, tamanho 3.
4. Lê `0`: sai do laço.
5. Imprime `Li 3 numeros: 7 8 9`.

**O que observar:** sempre atribua o retorno de `realloc` a uma variável nova e só depois
copie para `v`. Se `realloc` falhar, ele devolve `NULL` **sem** liberar o bloco antigo —
escrever `v = realloc(v, ...)` direto perderia o endereço original e vazaria.

### Exemplo 3 — os dois erros clássicos (o que NÃO fazer)

```c
#include <stdlib.h>

// (a) vazamento de memoria: aloca e nunca libera
void vazamento(void) {
    int *p = malloc(100 * sizeof(int));
    p[0] = 1;
    // faltou free(p): a cada chamada, 400 bytes "somem" ate o programa acabar
}

// (b) uso apos free (dangling pointer)
void uso_apos_free(void) {
    int *p = malloc(sizeof(int));
    *p = 42;
    free(p);
    *p = 7;          // ERRO: a memoria ja foi devolvida ao sistema
}
```

**Como evitar:**

- Para cada `malloc`, exista exatamente um `free` no caminho de saída — inclusive nos
  caminhos de erro (`return` no meio da função).
- Depois de `free(p)`, faça `p = NULL;`. Assim um uso acidental vira uma falha imediata e
  fácil de achar, em vez de um bug silencioso.
- `free(p)` duas vezes no mesmo endereço também é erro grave (*double free*).

## Erros comuns / pegadinhas

- **Não checar `NULL`.** Se `malloc` falha e você usa `v[0]`, o programa trava.
- **`n * 4` em vez de `n * sizeof(int)`.** Quebra onde `int` não tem 4 bytes.
- **Esquecer `free`** (vazamento) ou **usar depois do `free`** (dangling pointer).
- **`v = realloc(v, ...)` sem variável intermediária.** Vaza o bloco antigo se `realloc`
  falhar.
- **`free` num ponteiro que não veio de `malloc`** — endereço de variável local, ponteiro
  já liberado, ou ponteiro no meio de um bloco (`free(v + 2)`). Todos são erro grave.
- **Achar que `free` apaga o valor de `v`.** `v` continua contendo o endereço velho; o que
  mudou é que aquele endereço não é mais seu.

## Resumo / checklist

- [x] Sei diferenciar a variável ponteiro (pilha) da área apontada (heap)
- [x] Uso `malloc(n * sizeof(tipo))` e checo o retorno `NULL`
- [x] Sei quando usar `calloc` (quero zeros) e `realloc` (redimensionar)
- [x] Dou um `free` para cada `malloc`, inclusive nos caminhos de erro
- [x] Faço `p = NULL` depois do `free`
- [x] Sei o que é vazamento de memória e dangling pointer, e como cada um acontece
