# 3.1 Arquivos Binários e Texto

## Objetivo de aprendizagem

- Entender a diferença estrutural entre arquivo texto e arquivo binário (representação, portabilidade, tamanho).
- Distinguir acesso sequencial de acesso direto (randômico) e saber quando usar cada um.
- Saber implementar E/S de arquivos em C (modos de abertura, leitura/escrita de registros, posicionamento com `fseek`).
- Entender registros de tamanho fixo vs variável e o impacto disso no acesso direto.

## Roteiro de leitura

- **SZ (livro-base):** capítulo de Arquivos — organização de arquivos, tipos de registro, modos de acesso (conferir página exata).
- **CO (Cormen):** não tem capítulo dedicado a organização de arquivos — este subtópico é essencialmente ausente do CLRS.
- **CE (Celes):** não cobre arquivos/E-S de arquivo como tópico de estrutura de dados (o livro foca em estruturas de memória principal) — não usar como referência aqui.
- **KR:** cap. 7 "Entrada e Saída", especialmente as seções de acesso a arquivo (`fopen`, `fclose`, `fread`, `fwrite`, `fseek`, `ftell`) (conferir página exata) — esta é a referência prática mais direta para implementar este subtópico.

## Notas de estudo elaboradas

### Arquivo texto vs arquivo binário

| Aspecto | Arquivo texto | Arquivo binário |
|---|---|---|
| Representação | Caracteres legíveis (ASCII/UTF-8), números convertidos para string | Bytes crus, representação em memória do dado (ex.: `int` como 4 bytes) |
| Portabilidade | Alta (independe de arquitetura, mas pode variar quebra de linha `\n` vs `\r\n`) | Baixa (depende de endianness, tamanho de tipos, alinhamento de struct) |
| Tamanho em disco | Maior (um número como `12345` vira 5 bytes de caracteres) | Menor (o mesmo `int` sempre ocupa `sizeof(int)` bytes) |
| Acesso | Tipicamente sequencial (linhas de tamanho variável) | Pode ser direto (registros de tamanho fixo têm offset previsível) |
| Uso típico | Configuração, logs, dados legíveis por humanos | Registros de banco de dados, estruturas ordenadas para ordenação externa |

Para ordenação externa (módulos 3.2 e 3.3), o padrão é usar **arquivo binário com registros de tamanho fixo**, porque isso permite calcular o offset de qualquer registro `i` como `i * sizeof(registro)`, viabilizando acesso direto.

### Acesso sequencial vs acesso direto (randômico)

- **Sequencial:** lê-se do início ao fim, sem pular posições. É o único modo viável em arquivos texto com registros de tamanho variável (não dá pra saber o offset do registro N sem ler os N-1 anteriores).
- **Direto (randômico):** salta-se diretamente para uma posição via `fseek(f, offset, SEEK_SET)`. Só é eficiente com registros de tamanho fixo, onde `offset = numero_do_registro * sizeof(registro)`.

### Registros de tamanho fixo vs variável

- **Fixo:** todo registro ocupa o mesmo número de bytes (ex.: `struct { int id; char nome[30]; float nota; }` sempre ocupa `sizeof(struct)`). Permite acesso direto trivial, mas desperdiça espaço se os dados variam muito de tamanho (ex.: nome curto ainda reserva 30 bytes).
- **Variável:** cada registro ocupa um tamanho diferente (ex.: strings terminadas em `\0` sem padding, ou um campo de tamanho no início do registro indicando quantos bytes seguem). Economiza espaço, mas exige acesso sequencial ou uma estrutura auxiliar de índice (offsets) para acesso direto.

### E/S de arquivos em C

```c
FILE *f = fopen("dados.bin", "rb");   // "rb" = read binary; "wb" = write binary; "r+b" = read/write binary
if (f == NULL) { /* tratar erro */ }

struct Registro r;
fread(&r, sizeof(struct Registro), 1, f);   // lê 1 registro
fwrite(&r, sizeof(struct Registro), 1, f);  // escreve 1 registro

fseek(f, n * sizeof(struct Registro), SEEK_SET);  // pula para o registro n (acesso direto)
long pos = ftell(f);                               // posição atual em bytes

fclose(f);
```

Modos de abertura relevantes: `"r"`/`"w"`/`"a"` (texto), `"rb"`/`"wb"`/`"ab"` (binário), e as variantes `"+"` para leitura e escrita simultâneas (`"r+b"`, `"w+b"`).

### Exemplo concreto: mesmo registro, texto vs binário

Considere o registro `{ id: 7, nome: "Ana", nota: 8.5 }` com `struct Registro { int id; char nome[30]; float nota; };`.

**Em arquivo texto (CSV)**, uma linha ficaria:
```
7,Ana,8.5
```
Isso ocupa **10 bytes** (contando a vírgula e sem quebra de linha) — mas o tamanho varia registro a registro: um nome mais longo gera uma linha maior. Para achar o registro de `id=7` você precisaria ler linha por linha até encontrá-lo (busca sequencial O(n)) — não dá pra calcular onde ele começa sem antes ler tudo que veio antes.

**Em arquivo binário**, o mesmo registro ocupa sempre `sizeof(struct Registro)` = 4 (int) + 30 (char[30]) + 4 (float) = **38 bytes** (podendo variar com padding de alinhamento do compilador), *independente* do conteúdo — o campo `nome` sempre reserva os 30 bytes completos, mesmo para "Ana" (3 caracteres + `\0` + 26 bytes de lixo/zeros). Isso desperdiça espaço comparado ao CSV, mas em compensação: se esse for o registro de índice 7 (contando do 0) no arquivo, seu offset é exatamente `7 * 38 = 266` bytes — dá pra saltar direto pra lá com `fseek(f, 266, SEEK_SET)` sem ler nada antes, o que é o que viabiliza ordenação externa eficiente (módulos 3.2/3.3): acessar/reescrever qualquer registro em O(1) de I/O, não O(n).

## Exemplos em C

Programa completo que grava um vetor de registros em arquivo binário, depois lê de volta o k-ésimo registro por acesso direto — sem percorrer os anteriores:

```c
#include <stdio.h>

typedef struct {
    int id;
    char nome[30];
    float nota;
} Registro;

/* Grava um vetor de registros no arquivo binário, um após o outro,
   cada um ocupando exatamente sizeof(Registro) bytes. */
void grava_registros(const char *caminho, Registro *v, int n) {
    FILE *f = fopen(caminho, "wb");
    if (f == NULL) { perror("fopen"); return; }

    fwrite(v, sizeof(Registro), n, f);  /* escreve os n registros de uma vez */
    fclose(f);
}

/* Lê diretamente o registro de índice k (0-based), sem ler os anteriores.
   Retorna 1 em sucesso, 0 se k está fora do arquivo. */
int le_registro_direto(const char *caminho, int k, Registro *saida) {
    FILE *f = fopen(caminho, "rb");
    if (f == NULL) { perror("fopen"); return 0; }

    /* offset em bytes até o registro k */
    long offset = (long) k * sizeof(Registro);
    fseek(f, offset, SEEK_SET);

    size_t lidos = fread(saida, sizeof(Registro), 1, f);
    fclose(f);
    return lidos == 1;  /* fread retorna quantos itens completos leu */
}

int main(void) {
    Registro alunos[3] = {
        {1, "Bruno", 7.0f},
        {2, "Carla", 9.2f},
        {3, "Diego", 6.5f}
    };

    grava_registros("alunos.bin", alunos, 3);

    Registro r;
    if (le_registro_direto("alunos.bin", 1, &r))  /* pula direto pro índice 1, sem ler o índice 0 */
        printf("Registro 1: id=%d nome=%s nota=%.1f\n", r.id, r.nome, r.nota);

    return 0;
}
```

O ponto central: `le_registro_direto` nunca lê o registro de índice 0 pra chegar ao de índice 1 — o `fseek` calcula a posição exata em bytes e salta direto. Isso só é possível porque todo `Registro` tem tamanho fixo (`sizeof(Registro)`); com registros de tamanho variável (texto, ou binário com campos de tamanho dinâmico), seria necessário ler sequencialmente ou manter um índice auxiliar de offsets.

## Pontos de atenção / pegadinhas comuns de prova

- Confundir "arquivo binário" com "arquivo compactado" — binário aqui só significa "bytes crus da memória", não implica compressão.
- Esquecer que `fwrite`/`fread` retornam o número de itens efetivamente lidos/escritos — não checar esse valor pode mascarar erros de I/O.
- Assumir que structs com padding (alinhamento de memória) têm sempre o mesmo `sizeof` entre arquiteturas/compiladores diferentes — isso quebra portabilidade de arquivos binários entre sistemas.
- Tentar fazer acesso direto (`fseek` calculado) em arquivo de registros de tamanho variável sem um índice auxiliar — não funciona.

## Anotações pessoais

## Exercícios resolvidos
