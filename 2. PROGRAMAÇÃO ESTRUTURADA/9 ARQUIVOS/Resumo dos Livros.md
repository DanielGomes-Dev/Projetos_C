# Resumo dos Livros — 9. Arquivos

## Celes — Introdução a Estruturas de Dados (Cap. 15, "Arquivos")
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido.

Correção importante: ao contrário do que a síntese anterior desta nota afirmava, **Celes cobre arquivos em detalhe** — capítulo inteiro (Cap. 15, abrindo a Parte III), mais completo em alguns pontos do que a seção do K&R (cobre também modo binário e acesso aleatório, que o K&R não desenvolve).

**Abrir/fechar**: `FILE* fopen(char* nome, char* modo);` retorna `NULL` em caso de falha — sempre checado antes de usar. Modos: `r`/`w`/`a` (leitura / escrita, destruindo conteúdo anterior / escrita ao final, preservando), combináveis com `t`/`b` (texto/binário) e com `+` (leitura e escrita simultâneas: `r+`, `w+`). `int fclose(FILE* fp);` retorna `0` em sucesso ou `EOF` em erro.

**Modo texto — leitura**: `fscanf(fp, formato, ...)` (igual a `scanf`, mas o primeiro parâmetro é o arquivo); `fgetc(fp)` lê 1 caractere (retorno `int`, por causa do `EOF` — mesma razão de `getchar`, ver [[../1 INTRODUÇÃO A LINGUAGEM C/1.4 ENTRADA E SAÍDA PADRÃO/Resumo dos Livros|1.4]]); `fgets(s, n, fp)` lê uma linha inteira, parando em `\n` ou em `n-1` caracteres — o livro reforça que o limite de tamanho existe **exatamente** para evitar estourar o buffer se a linha do arquivo for maior do que o esperado.

**Modo texto — escrita**: `fprintf(fp, formato, ...)` (= `printf` + arquivo); `fputc(c, fp)`.

**Três formas de estruturar dados em arquivo texto**, desenvolvidas com exemplos completos: (1) **caractere a caractere** — exemplo: contar linhas de um arquivo lendo com `fgetc` até `EOF` e contando `'\n'`; (2) **linha a linha**; (3) **por palavras-chave** — exemplo: um arquivo descrevendo formas geométricas (`RETANGULO`, `TRIANGULO`, `CIRCULO`, `POLIGONO` seguidos de seus parâmetros), interpretado com `fscanf(fp, "%120s", palavra)` + cadeia de `strcmp` para decidir o que fazer com cada palavra-chave.

**`ungetc`**: "devolve" o último caractere lido, permitindo espiar o próximo dado sem consumi-lo — o livro nota que essa função foi usada na calculadora pós-fixada do Cap. 11 ([[../7 TIPOS ABSTRATOS DE DADOS/7.6 FILA E PILHA/Resumo dos Livros|7.6]]).

**Modo binário**: `fwrite(void* p, int tam, int nelem, FILE* fp)` e `fread(void* p, int tam, int nelem, FILE* fp)` copiam bytes crus entre memória e disco — muito mais eficiente para grandes volumes de dados estruturados (o exemplo do livro salva/recupera um vetor inteiro de `struct Ponto` de uma vez, sem conversão texto↔número). **Acesso aleatório**: `fseek(FILE* fp, long offset, int origem)` reposiciona o cursor do arquivo (`SEEK_SET`/`SEEK_CUR`/`SEEK_END`) — combinado com registros de tamanho fixo (`sizeof(Ponto)`), permite calcular o offset exato do i-ésimo registro (`i*sizeof(Ponto)`) e lê-lo diretamente, sem percorrer o arquivo do início — algo impossível em modo texto, onde o tamanho de cada registro em bytes varia.

## K&R — C: A Linguagem de Programação (Cap. 7, seção 7.6)
A seção "Acesso a Arquivos" parte da constatação de que os programas do livro, até esse ponto, "têm lido da entrada padrão e gravado na saída padrão que assumimos como sendo predefinidas magicamente para o programa pelo sistema operacional" — e propõe o próximo passo: acessar um arquivo qualquer pelo nome, usando como fio condutor a implementação do utilitário `cat`.

O texto explica o modelo de acesso a arquivos da biblioteca padrão em camadas. Primeiro, `fopen`: *"antes de poder ser lido ou gravado, um arquivo deve ser aberto pela função `fopen` da biblioteca padrão. `fopen` aceita um nome externo [...] e retorna um nome interno que deve ser usado em leituras ou gravações subsequentes."* Esse "nome interno" é um apontador para uma `struct` chamada `FILE` (definida em `stdio.h`), que guarda "localização de um buffer, a posição do caractere corrente no buffer, se o arquivo está sendo lido ou gravado etc." — os detalhes ficam encapsulados, e o programador só precisa de `FILE *fopen(), *fp;`.

A chamada típica é `fp = fopen(nome, modo)`, onde o modo é uma string com os valores descritos no livro — leitura (`"r"`), gravação (`"w"`) ou adição (`"a"`) — com o comportamento explícito para cada caso: abrir para gravação um arquivo inexistente o cria; abrir para gravação um arquivo existente descarta seu conteúdo antigo; e ler um arquivo inexistente é erro. Em qualquer caso de erro, "`fopen` retorna o apontador nulo `NULL`" — daí a importância de sempre checar o retorno antes de usar `fp`.

Para ler/escrever, o texto apresenta `getc(fp)`/`putc(c, fp)` como o par mais simples (análogos a `getchar`/`putchar`, mas parametrizados pelo arquivo), e nota que todo programa em C já começa com três arquivos abertos automaticamente — `stdin`, `stdout` e `stderr` — que "normalmente [...] estão todos conectados ao terminal", mas podem ser redirecionados. Para I/O formatada em arquivo, `fscanf`/`fprintf` são apresentadas como equivalentes a `scanf`/`printf`, "exceto que o primeiro argumento é um apontador de arquivo".

O programa `cat` de exemplo amarra tudo isso:

```c
#include <stdio.h>

main(argc, argv)
int argc;
char *argv[];
{
    FILE *fp, *fopen();
    if (argc == 1)
        copia_arq(stdin);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("cat: nao pode abrir %s\n", *argv);
                break;
            } else {
                copia_arq(fp);
                fclose(fp);
            }
}

copia_arq(fp)              /* copia arquivo fp na saida padrao */
FILE *fp;
{
    int c;
    while ((c = getc(fp)) != EOF)
        putc(c, stdout);
}
```

Por fim, o livro fecha a seção com `fclose`, "a inversa de `fopen`": encerra a conexão entre o ponteiro de arquivo e o nome externo, liberando-o para outro uso, e — motivo prático citado no texto — "esvazia o buffer em que `putc` está colocando a saída", isto é, garante que dados ainda em buffer sejam de fato gravados em disco. O livro observa que `fclose` "é chamada automaticamente para cada arquivo aberto quando um programa termina normalmente", mas recomenda fechar explicitamente porque "a maioria dos sistemas operacionais tem algum limite no número de arquivos abertos simultaneamente".

## K&R — Cap. 8 (Interface com o Sistema UNIX) — menção breve
O capítulo 8 aprofunda o mesmo assunto em um nível mais baixo, específico do UNIX: em vez do ponteiro `FILE *` de alto nível do capítulo 7, descreve o acesso a arquivos via **descritor de arquivo** — "um pequeno inteiro positivo" retornado pelo sistema operacional ao abrir um arquivo, usado em chamadas de sistema como `open`/`read`/`write`/`close`. O livro é explícito sobre a relação entre os dois capítulos: "o Capítulo 7 lidou com uma interface de sistema uniforme numa variedade de sistemas. Em qualquer sistema particular, as rotinas da biblioteca padrão têm de ser escritas em termos das facilidades de entrada e saída atualmente disponíveis no sistema hospedeiro" — ou seja, `FILE *` e `fopen` são construídos, por baixo, sobre descritores de arquivo e chamadas de sistema como as descritas no capítulo 8.

## Síntese
Ao contrário do que se pensava, este é outro tópico onde **Celes é a referência mais completa**, não só o K&R: cobre tudo que o K&R cobre (`fopen`/`fclose`/leitura-escrita formatada) e vai além com modo binário (`fread`/`fwrite`) e acesso aleatório (`fseek`), que o K&R não desenvolve neste trecho. O K&R contribui o exemplo mais elegante e minimalista da interface de alto nível (`cat` reimplementado em ~15 linhas) e a ponte para a camada de baixo nível do sistema operacional (Cap. 8, descritores de arquivo) — algo fora do escopo do livro-base do curso.

## Exemplos em C

**Contagem de linhas de um arquivo (o primeiro exemplo do Celes, caractere a caractere):**
```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("entrada.txt", "rt");
    if (fp == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }

    int c, nlinhas = 0;
    while ((c = fgetc(fp)) != EOF)
        if (c == '\n')
            nlinhas++;

    fclose(fp);
    printf("Número de linhas: %d\n", nlinhas);
    return 0;
}
```

**Converter arquivo para maiúsculas (leitura + escrita simultâneas em dois arquivos, o segundo exemplo do Celes):**
```c
#include <stdio.h>
#include <ctype.h>

int main(void) {
    FILE *e = fopen("entrada.txt", "rt");
    if (e == NULL) { printf("Erro ao abrir entrada.\n"); return 1; }

    FILE *s = fopen("saida.txt", "wt");
    if (s == NULL) { printf("Erro ao abrir saída.\n"); fclose(e); return 1; }

    int c;
    while ((c = fgetc(e)) != EOF)
        fputc(toupper(c), s);

    fclose(e);
    fclose(s);
    return 0;
}
```

**Modo binário + acesso aleatório com `fseek` (salvar/carregar um vetor de structs, e ler só o i-ésimo registro):**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct { float x, y, z; } Ponto;

void salva(const char *arquivo, int n, Ponto *vet) {
    FILE *fp = fopen(arquivo, "wb");
    if (fp == NULL) { printf("Erro ao abrir arquivo.\n"); exit(1); }
    fwrite(vet, sizeof(Ponto), n, fp);   /* copia os bytes crus do vetor inteiro de uma vez */
    fclose(fp);
}

void carrega(const char *arquivo, int n, Ponto *vet) {
    FILE *fp = fopen(arquivo, "rb");
    if (fp == NULL) { printf("Erro ao abrir arquivo.\n"); exit(1); }
    fread(vet, sizeof(Ponto), n, fp);
    fclose(fp);
}

/* lê só o i-ésimo ponto, sem carregar o arquivo inteiro na memória */
Ponto le_ponto(FILE *fp, int i) {
    Ponto p;
    fseek(fp, i * sizeof(Ponto), SEEK_SET);   /* pula direto para o registro i */
    fread(&p, sizeof(Ponto), 1, fp);
    return p;
}

int main(void) {
    Ponto pontos[3] = {{1,1,1}, {2,2,2}, {3,3,3}};
    salva("pontos.bin", 3, pontos);

    FILE *fp = fopen("pontos.bin", "rb");
    Ponto p = le_ponto(fp, 1);          /* pega o 2º ponto direto, sem ler o 1º */
    printf("%.0f %.0f %.0f\n", p.x, p.y, p.z);
    fclose(fp);

    return 0;
}
```
