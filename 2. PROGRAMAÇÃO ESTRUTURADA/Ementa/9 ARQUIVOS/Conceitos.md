# Conceitos — Arquivos

## A ideia em uma frase

Um arquivo é acessado por um cursor que caminha por ele: você **abre** (`fopen`), lê ou
escreve a partir da posição atual do cursor, e **fecha** (`fclose`) — o fechar é o que
garante que o que estava no buffer chegue ao disco.

## O conceito

**Stream e cursor.** Ao abrir um arquivo, você recebe um `FILE *` — um "canal" com um
cursor apontando para uma posição. Cada leitura/escrita avança o cursor. `EOF` (fim de
arquivo) é o sinal de que o cursor chegou ao fim.

**Buffer.** O que você escreve fica primeiro numa área de memória (buffer) e só vai ao
disco em blocos, ou quando você dá `fclose` (ou `fflush`). **Se o programa termina sem
fechar, dados podem se perder.**

**Modos de abertura** (`fopen(nome, modo)`):

| Modo | Efeito |
|---|---|
| `"r"` | leitura; falha se o arquivo não existe |
| `"w"` | escrita; **cria, ou apaga todo o conteúdo** se já existe |
| `"a"` | escrita ao final (*append*); cria se não existe, preserva o conteúdo |
| `"r+"`, `"w+"` | leitura E escrita |
| `+"b"` (ex. `"rb"`, `"wb"`) | modo binário |

`fopen` devolve `NULL` em caso de erro — **sempre cheque**.

**Texto x binário:**

- **Texto:** números viram dígitos legíveis; `fprintf`/`fscanf`, `fgets`/`fputs`,
  `fgetc`/`fputc`. Cada registro tem tamanho variável em bytes.
- **Binário:** os bytes da memória são copiados como estão; `fwrite`/`fread`. Registros
  de tamanho fixo → permite pular direto para o i-ésimo com `fseek`.

## Sintaxe / ferramentas

| Função | Uso |
|---|---|
| `fopen`, `fclose` | abrir / fechar |
| `fgetc(fp)` / `fputc(c, fp)` | um caractere (devolve `int` por causa do `EOF`) |
| `fgets(buf, n, fp)` / `fputs(s, fp)` | uma linha (respeita o tamanho `n`) |
| `fscanf(fp, ...)` / `fprintf(fp, ...)` | formatado, como `scanf`/`printf` com o arquivo à frente |
| `fread(p, tam, qtd, fp)` / `fwrite(...)` | blocos binários |
| `fseek(fp, offset, origem)` | move o cursor (`SEEK_SET`, `SEEK_CUR`, `SEEK_END`) |

## Exemplos passo a passo

### Exemplo 1 — contar linhas de um arquivo (caractere a caractere)

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("entrada.txt", "r");
    if (fp == NULL) { printf("nao abriu\n"); return 1; }

    int c, linhas = 0;
    while ((c = fgetc(fp)) != EOF)     // lê até o cursor chegar ao fim
        if (c == '\n') linhas++;

    fclose(fp);
    printf("%d linhas\n", linhas);
    return 0;
}
```

**Passo a passo:** `fgetc` devolve o próximo byte e avança o cursor. Ao chegar ao fim,
devolve `EOF` e o laço para. `c` é `int` (não `char`) porque precisa distinguir todo
byte possível do valor `EOF`.

### Exemplo 2 — copiar um arquivo convertendo para maiúsculas

```c
#include <stdio.h>
#include <ctype.h>

int main(void) {
    FILE *e = fopen("entrada.txt", "r");
    if (e == NULL) { printf("erro entrada\n"); return 1; }
    FILE *s = fopen("saida.txt", "w");        // cuidado: apaga saida.txt se existir
    if (s == NULL) { fclose(e); printf("erro saida\n"); return 1; }

    int c;
    while ((c = fgetc(e)) != EOF)
        fputc(toupper(c), s);

    fclose(e);
    fclose(s);                                 // <- sem isto, saida.txt pode ficar vazio
    return 0;
}
```

**O que observar:** dois streams abertos ao mesmo tempo. O `fclose(s)` esvazia o buffer —
é ele que garante a gravação real.

### Exemplo 3 — ler registros com `fscanf` linha a linha

Arquivo `notas.txt`:

```
Ana 8.5
Bruno 7.0
Carla 9.2
```

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("notas.txt", "r");
    if (fp == NULL) return 1;

    char nome[50];
    float nota, soma = 0;
    int n = 0;
    while (fscanf(fp, "%49s %f", nome, &nota) == 2) {   // 2 = leu os dois campos
        printf("%s: %.1f\n", nome, nota);
        soma += nota;
        n++;
    }
    fclose(fp);
    if (n > 0) printf("media: %.2f\n", soma / n);
    return 0;
}
```

**O que observar:** o laço testa `fscanf(...) == 2`, não `!feof(fp)`. `fscanf` devolve
quantos campos conseguiu ler; quando chega ao fim (ou acha lixo), devolve menos que 2 e o
laço para na hora certa. Usar `while (!feof(fp))` lê o último registro duas vezes.

### Exemplo 4 — binário e acesso aleatório com `fseek`

```c
#include <stdio.h>

typedef struct { float x, y, z; } Ponto;

int main(void) {
    Ponto v[3] = {{1,1,1}, {2,2,2}, {3,3,3}};

    FILE *fp = fopen("pontos.bin", "wb");
    fwrite(v, sizeof(Ponto), 3, fp);        // grava os 3 de uma vez
    fclose(fp);

    fp = fopen("pontos.bin", "rb");
    Ponto p;
    fseek(fp, 1 * sizeof(Ponto), SEEK_SET); // pula direto para o registro 1
    fread(&p, sizeof(Ponto), 1, fp);
    printf("%.0f %.0f %.0f\n", p.x, p.y, p.z);   // 2 2 2
    fclose(fp);
    return 0;
}
```

**Passo a passo do `fseek`:** cada `Ponto` ocupa `sizeof(Ponto)` bytes fixos. O registro
`i` começa no byte `i * sizeof(Ponto)`. `fseek` move o cursor para lá sem ler nada no
caminho — impossível em modo texto, onde cada linha tem um número diferente de bytes.

## Erros comuns / pegadinhas

- **Não checar `fopen` retornando `NULL`** — o primeiro `fgetc`/`fscanf` trava.
- **`while (!feof(fp))`** — lê o último item duas vezes. Teste o retorno de
  `fgetc`/`fscanf`/`fgets`.
- **Abrir com `"w"` sem querer** — apaga o arquivo. Para adicionar, use `"a"`.
- **Esquecer `fclose`** — dados no buffer não chegam ao disco.
- **`fscanf("%s")` sem largura** — estoura o buffer. Use `%49s`.
- **Ler binário gravado em outra máquina** — tamanho de tipos e ordem de bytes podem
  diferir.
- **Misturar texto e binário no mesmo arquivo sem cuidado.**

## Resumo / checklist

- [ ] Entendo stream, cursor, buffer e por que `fclose` importa
- [ ] Sei o efeito de cada modo (`r`, `w`, `a`, `+`, `b`) — em especial que `"w"` apaga
- [ ] Sempre checo `fopen != NULL`
- [ ] Testo o retorno de `fscanf`/`fgets`/`fgetc`, nunca `!feof`
- [ ] Sei a diferença texto x binário e quando usar `fread`/`fwrite`
- [ ] Sei usar `fseek` para acesso aleatório com registros de tamanho fixo
