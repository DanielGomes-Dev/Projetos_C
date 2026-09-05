## 1. Mapeamento e Identificação

* **O Problema**: Trata-se do desenvolvimento de um software em linguagem C encomendado por agências de talentos de Hollywood. O objetivo é processar um arquivo de dados estruturado que contém informações de nós (entidades) como Filmes (`Movie`) e Pessoas (`Person` — diretores, atores, produtores), mapeando seus atributos (títulos, nomes, anos de lançamento/nascimento e taglines).
* **Tópico da Matéria**: **Estruturas de Dados e Seus Algoritmos** (especificamente processamento de arquivos textuais, modelagem de nós/estruturas de dados homogêneas ou heterogêneas e representação de Grafos/Redes de Relacionamento através de listas ou matrizes de adjacência).

---

## 2. Transcrição Fiel

> **Trabalho Computacional de Estruturas de Dados e Seus Algoritmos**
> * A implementacao deve ser feita em C
> 
> 
> Considere que você seja contratado pelas agências de talentos de Hollywood para gerar algumas informações relacionadas a filmes.
> Seu software deve ler um arquivo informações de atores, produtores e filmes.

---

## 3. Resolução Baseada no Texto e Passo a Passo Detalhado

O texto fornecido (`Nodes.txt`) simula uma base de dados em formato de nós brutos (comum em bancos de dados orientados a grafos, como o Neo4j). Para resolver e implementar esse sistema em C, dividiremos o raciocínio em etapas microscópicas, respeitando o rastro de transformação de dados e a anatomia de cada passo.

### Passo 1: Anatomia e Modelagem das Estruturas de Dados (`struct`)

Antes de abrir o arquivo, precisamos definir como a memória do computador armazenará os dois tipos de entidades identificados no arquivo: `Movie` (Filme) e `Person` (Pessoa).

Aplicando o **Pilar da Anatomia**, criaremos uma estrutura de dados explícita para cada entidade em C.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar dados de um Filme
typedef struct {
    char titulo[100];
    int ano_lancamento;
    char tagline[200];
} Filme;

// Estrutura para armazenar dados de uma Pessoa
typedef struct {
    char nome[100];
    int ano_nascimento; // Definiremos -1 se for "(no birth year)"
} Pessoa;

// Enumerador para rastreamento de tipo de nó sem computação implícita
typedef enum { TYP_MOVIE, TYP_PERSON } TipoNo;

// Estrutura Nó que engloba as entidades
typedef struct {
    TipoNo tipo;
    union {
        Filme filme;
        Pessoa pessoa;
    } dado;
} No;

```

### Passo 2: O Mecanismo de Leitura e Tokenização (Análise de Linhas)

O arquivo enviado possui linhas delimitadas pelo caractere pipe (`|`). Vamos demonstrar como rastrear os símbolos e extraí-los explicitamente.

Análise visual da taxa de conversão da string bruta do texto para variáveis:

* `[Linha Exemplo]` $\rightarrow$ `Movie | The Matrix | 1999 | [cite_start]Welcome to the Real World` 


* Ao encontrar o token `Movie`, o programa direciona a extração para os campos correspondentes à struct `Filme`.


* Ao encontrar o token `Person`, direciona para `Pessoa`.



**Tratamento de Exceções Explicitadas no Texto:**

* Exemplo de linha incompleta ou sem ano: `Person | Naomie Harris | (no birth year)[cite_start]`. O programa deve testar essa condição e atribuir um valor neutro padrão (como `0` ou `-1`).



### Passo 3: Implementação do Algoritmo de Leitura em C

Abaixo está o algoritmo completo passo a passo. Ele lê o arquivo linha por linha, limpa as tags de marcação de origem fornecidas no arquivo (ex: ``), divide os campos usando `strtok` e armazena os dados.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINHA 512

// Função auxiliar para remover espaços em branco do início e fim de uma string
void limpar_espacos(char *str) {
    int inicio = 0;
    while (isspace((unsigned char)str[inicio])) {
        inicio++;
    }
    
    int fim = strlen(str) - 1;
    while (fim >= inicio && isspace((unsigned char)str[fim])) {
        fim--;
    }
    
    int i;
    for (i = inicio; i <= fim; i++) {
        str[i - inicio] = str[i];
    }
    str[i - inicio] = '\0';
}

// Função auxiliar para remover marcações do tipo "" caso existam na linha
void remover_source(char *linha) {
    char *ptr = strchr(linha, ']');
    if (ptr != NULL && linha[0] == '[') {
        // Move o ponteiro para o início real do dado após o conteúdo de source
        memmove(linha, ptr + 1, strlen(ptr + 1) + 1);
    }
}

int main() {
    FILE *arquivo = fopen("Nodes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo Nodes.txt\n");
        return 1;
    }

    char linha[MAX_LINHA];
    
    printf("--- PROCESSANDO REGISTROS HOLLYWOOD ---\n\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        // 1. Limpeza inicial do rastro de tags do arquivo
        remover_source(linha);
        limpar_espacos(linha);
        
        // Se a linha ficou vazia após a limpeza, pula
        if (strlen(linha) == 0) continue;

        // 2. Extração do primeiro token (Tipo do Nó)
        char *token = strtok(linha, "|");
        if (token == NULL) continue;
        
        char tipo[20];
        strcpy(tipo, token);
        limpar_espacos(tipo);

        // 3. Processamento condicional explícito baseado no tipo verificado
        if (strcmp(tipo, "Movie") == 0) {
            char titulo[100] = "";
            char ano_str[10] = "";
            char tagline[200] = "";

            // Captura o Título
            token = strtok(NULL, "|");
            if (token) { strcpy(titulo, token); limpar_espacos(titulo); }

            // Captura o Ano
            token = strtok(NULL, "|");
            if (token) { strcpy(ano_str, token); limpar_espacos(ano_str); }

            // Captura a Tagline
            token = strtok(NULL, "|");
            if (token) { strcpy(tagline, token); limpar_espacos(tagline); }

            int ano = atoi(ano_str);

            // Exibição formatada do dado estruturado resultante
            printf("[FILME] Título: %s | Ano: %d | Slogan: %s\n", titulo, ano, tagline);
            
        } else if (strcmp(tipo, "Person") == 0) {
            char nome[100] = "";
            char nasc_str[50] = "";

            // Captura o Nome
            token = strtok(NULL, "|");
            if (token) { strcpy(nome, token); limpar_espacos(nome); }

            // Captura o Ano de Nascimento
            token = strtok(NULL, "|");
            if (token) { strcpy(nasc_str, token); limpar_espacos(nasc_str); }

            int ano_nasc = 0;
            if (strstr(nasc_str, "no birth year") != NULL || strlen(nasc_str) == 0) {
                ano_nasc = -1; // Código padrão para ano não informado
            } else {
                ano_nasc = atoi(nasc_str);
            }

            // Exibição formatada do dado estruturado resultante
            if (ano_nasc != -1) {
                printf("[PESSOA] Nome: %s | Nascimento: %d\n", nome, ano_nasc);
            } else {
                printf("[PESSOA] Nome: %s | Nascimento: Não Informado\n", nome);
            }
        }
    }

    fclose(arquivo);
    return 0;
}

```

---

## 4. Fórmula de Resposta Final

Abaixo encontra-se o escopo formal da transformação matemática e lógica da conversão de uma cadeia de caracteres (`string`) do arquivo para uma entrada na tabela de dados em memória:

$$\text{Dado Bruto} \xrightarrow{\text{Sanitização}} \text{Linha Limpa} \xrightarrow{\text{Tokenização (}\vert\text{)}} \sum_{i=1}^{n} \text{Campos da Estrutura Encontrada}$$

Onde cada elemento do arquivo $\mathcal{A}$ obedece rigorosamente à regra de mapeamento sintático:

$$\mathcal{A}_i = \begin{cases}
\text{Filme}(\text{Título}, \text{Ano}, \text{Tagline}), & \text{se Tipo} = \text{"Movie"} \
\text{Pessoa}(\text{Nome}, \text{Ano Nascimento}), & \text{se Tipo} = \text{"Person"}
\end{cases}$$