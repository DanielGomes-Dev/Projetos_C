# Conceitos — Strings

## A ideia em uma frase

Em C não existe um tipo "string": uma string é apenas um **vetor de `char`** que termina
com o caractere nulo `'\0'`, e é esse `'\0'` que marca onde o texto acaba.

## O conceito

`"Rio"` na memória ocupa **4** bytes: `'R'`, `'i'`, `'o'`, `'\0'`. Todas as funções de
texto param quando encontram o `'\0'`.

Consequências:

- **Não dá para copiar string com `=`.** `s1 = s2;` copia um ponteiro, não o conteúdo. Use
  `strcpy`.
- **Não dá para comparar com `==`.** `s1 == s2` compara endereços. Use `strcmp`.
- **Sempre reserve espaço para o `'\0'`.** Uma string de `n` caracteres precisa de `n + 1`
  bytes.

Duas formas de declarar — parecidas, comportamento diferente:

```c
char  s1[] = "Rio";   // VETOR local, 4 bytes, mutável:   s1[0] = 'X'  -> OK ("Xio")
char *s2   = "Rio";   // PONTEIRO para literal constante: s2[0] = 'X'  -> comportamento indefinido
```

`sizeof(s1)` é 4 (o vetor); `sizeof(s2)` é 8 (um ponteiro).

## Sintaxe / ferramentas (`<string.h>`)

| Função | O que faz |
|---|---|
| `strlen(s)` | número de caracteres antes do `'\0'` |
| `strcpy(dest, orig)` | copia `orig` (com o `'\0'`) para `dest` |
| `strncpy(dest, orig, n)` | copia no máximo `n` bytes (mais seguro) |
| `strcat(dest, orig)` | anexa `orig` ao final de `dest` |
| `strcmp(a, b)` | `0` se iguais; `<0` se `a` vem antes; `>0` se depois |
| `strchr(s, c)` | ponteiro para a 1ª ocorrência de `c` em `s`, ou `NULL` |

`dest` precisa ter espaço suficiente — as funções não verificam.

## Exemplos passo a passo

### Exemplo 1 — percorrer caractere a caractere

**Problema:** contar as vogais de uma palavra, sem `strlen`.

```c
#include <stdio.h>

int main(void) {
    char palavra[] = "programacao";
    int vogais = 0;

    for (int i = 0; palavra[i] != '\0'; i++) {   // para no terminador
        char c = palavra[i];
        if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u')
            vogais++;
    }
    printf("%d vogais\n", vogais);   // 5
    return 0;
}
```

**Passo a passo:** o `for` avança `i` enquanto `palavra[i]` não for `'\0'`. Em
`"programacao"`: `o,a,a,a,o` são vogais → 5. Quando `i` chega ao `'\0'` (índice 11), o
teste falha e o laço para.

### Exemplo 2 — reimplementar `strlen`, `strcpy`, `strcmp`

Fazer à mão uma vez ajuda a entender o que as de biblioteca fazem. **No código de
verdade, use as de `<string.h>`.**

```c
#include <stdio.h>

int meu_strlen(const char *s) {
    int n = 0;
    while (s[n] != '\0') n++;
    return n;
}

void minha_strcpy(char *dest, const char *orig) {
    int i;
    for (i = 0; orig[i] != '\0'; i++)
        dest[i] = orig[i];
    dest[i] = '\0';                 // fecha a cópia — erro clássico esquecer isto
}

int minha_strcmp(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && a[i] == b[i]) i++;
    return a[i] - b[i];            // diferença no 1º caractere distinto
}

int main(void) {
    char buf[20];
    minha_strcpy(buf, "teste");
    printf("%s (%d)\n", buf, meu_strlen(buf));     // teste (5)
    printf("%d\n", minha_strcmp("abc", "abd"));    // 'c'-'d' = -1
    return 0;
}
```

**Passo a passo de `minha_strcmp("abc","abd")`:** `i=0`: `'a'=='a'` → `i=1`. `i=1`:
`'b'=='b'` → `i=2`. `i=2`: `'c' != 'd'`, sai. Retorna `'c' - 'd'` = `99 - 100` = `-1`
(negativo → `"abc"` vem antes).

### Exemplo 3 — string dinâmica do tamanho exato

**Problema:** guardar uma cópia de uma string sem desperdiçar memória.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *duplica(const char *s) {
    char *novo = malloc(strlen(s) + 1);   // +1 para o '\0'
    if (novo != NULL) strcpy(novo, s);
    return novo;                            // quem chamar precisa dar free
}

int main(void) {
    char *c = duplica("Salvador");
    printf("%s\n", c);
    free(c);
    return 0;
}
```

**O que observar:** `strlen("Salvador")` é 8; `malloc(9)` reserva os 8 caracteres mais o
terminador. Esquecer o `+ 1` é o bug mais comum com strings dinâmicas — `strcpy` grava o
`'\0'` fora do bloco.

### Exemplo 4 — vetor de strings: matriz fixa x vetor de ponteiros

```c
#include <stdio.h>

int main(void) {
    // matriz fixa: simples, mas cada nome ocupa 20 bytes mesmo sendo curto
    char fixo[3][20] = {"Ana", "Bruno", "Carla"};

    // vetor de ponteiros: cada string ocupa só o que precisa
    const char *ponteiros[3] = {"Ana", "Bruno", "Carla"};

    for (int i = 0; i < 3; i++)
        printf("%s | %s\n", fixo[i], ponteiros[i]);
    return 0;
}
```

## Erros comuns / pegadinhas

- **Copiar/comparar string com `=` / `==`.** Use `strcpy` / `strcmp`.
- **Esquecer o `+ 1` do `'\0'`** ao alocar (`malloc(strlen(s))`).
- **`strcpy`/`strcat` para um buffer pequeno demais** — estouro de buffer, corrupção de
  memória. Garanta o tamanho ou use as versões `strn*`.
- **Modificar uma string literal** via `char *s = "..."; s[0] = 'X';` — comportamento
  indefinido. Use `char s[] = "..."`.
- **Esquecer de fechar a cópia com `'\0'`** ao copiar manualmente.
- **`printf(s)`** com `s` vindo do usuário — se `s` tiver um `%`, quebra. Use
  `printf("%s", s)`.

## Resumo / checklist

- [ ] Sei que string = vetor de `char` + `'\0'`, e que o `'\0'` marca o fim
- [ ] Sei por que `=` e `==` não servem para strings
- [ ] Reservo sempre `strlen + 1` bytes
- [ ] Sei a diferença entre `char s[]` e `char *s` (mutável x literal, `sizeof`)
- [ ] Sei o que `strcmp` devolve e como o sinal se interpreta
- [ ] Uso `printf("%s", s)`, nunca `printf(s)`
