# Teoria 01 — O que é um arquivo, e por que binário ou texto

> **Onde isto entra:** primeira ideia do módulo — antes de ler/escrever qualquer coisa, é
> preciso saber que tipo de arquivo se está manipulando, porque isso muda **todas** as
> funções usadas depois.
> **Antes:** nenhum pré-requisito específico de estruturas de dados.
> **Fonte:** `ListasExercicios/lista050607-EDA/08_Arquivos.pdf` (slide da disciplina).

## 1. A ideia em uma frase

Um arquivo é só um **conjunto de dados guardado em memória secundária** (disco) — a
diferença entre "binário" e "texto" é **como esse dado fica escrito** ali dentro, o que
muda tanto o tamanho quanto o jeito de ler/escrever.

## 2. Por que essa distinção existe (motivação)

Até aqui no curso, todo dado vivia em memória principal (RAM) — quando o programa termina,
some. Arquivo é a forma de fazer o dado **sobreviver** ao fim do programa. Mas guardar em
disco levanta uma pergunta que RAM não levanta: **em que formato** os bytes ficam escritos?
Duas respostas possíveis, cada uma com vantagens diferentes — é isso que os dois tipos são.

## 3. As duas famílias — lidas devagar

> 📖 **Arquivo binário:** guarda os dados **usando o sistema de numeração** — ou seja, um
> `int` de 4 bytes vira 4 bytes crus no disco, exatamente como está na memória. A menor
> unidade de leitura é o **registro** (um bloco de tamanho conhecido). Exemplos citados no
> slide: `.doc`, `.ppt`, `.zip`, `.jpg`.
>
> 📖 **Arquivo texto:** guarda os dados como **caracteres** (o número `1234` vira os 4
> caracteres `'1'`, `'2'`, `'3'`, `'4'`, cada um ocupando 1 byte). A menor unidade de leitura
> é o **caractere**. Em geral é maior que a versão binária do mesmo dado. Exemplos: `.html`,
> `.c`, `.txt`.

### Conferindo com número concreto

O valor inteiro `1234` (4 bytes num `int` de 32 bits):
- **Em binário:** ocupa exatamente `sizeof(int)` = 4 bytes — os mesmos 4 bytes que ele
  ocupa na RAM, copiados direto pro disco.
- **Em texto:** ocupa 4 **caracteres** (`'1'`, `'2'`, `'3'`, `'4'`) = 4 bytes também **neste
  caso específico** — mas o valor `123456789` (9 dígitos) ocuparia 9 bytes em texto e ainda
  assim só 4 bytes em binário (um `int` continua sendo 4 bytes, não importa quantos dígitos
  o número decimal tem). É por isso que o slide diz "texto, em geral, é maior".

## 4. Outra classificação, ortogonal a essa: sequencial vs. serializado

O mesmo PDF (pág. 3) dá uma segunda forma de classificar, que **não** é sobre o formato dos
bytes, mas sobre **a ordem de acesso**:

| Tipo | Definição | Exemplo do slide |
|---|---|---|
| **Sequencial** | registro `i` é acessado depois do `i-1`, em ordem, sem pular | folha de pagamento |
| **Serializado** | registros guardados segundo um critério de **ordenação por chave** | banco de dados |

> **Letra miúda:** "binário/texto" (formato dos bytes) e "sequencial/serializado" (ordem de
> acesso) são **classificações independentes** — um arquivo binário pode ser sequencial ou
> serializado, e o mesmo vale para texto. Não confundir os dois eixos.

## 5. 📌 O que você está REALMENTE escolhendo

| A escolha | O que ela realmente decide |
|---|---|
| abrir como texto ou binário | se o dado no disco vira "dígitos legíveis" ou "os bytes crus da RAM" — muda tamanho e as funções de I/O usadas (Teoria 02) |
| arquivo sequencial ou serializado | se a aplicação só precisa "passar por tudo uma vez" ou precisa "achar rápido por uma chave" |

## 6. Exercícios de fixação

1. Um arquivo `.txt` com o número `42` escrito nele — quantos bytes esse número ocupa
   dentro do arquivo?
2. O mesmo número `42`, guardado como `int` num arquivo binário — quantos bytes ocupa?
3. Um arquivo de folha de pagamento, processado sempre "de cima pra baixo", é sequencial ou
   serializado?
4. Um arquivo de banco de dados, onde os registros ficam ordenados por CPF para permitir
   busca rápida, é sequencial ou serializado?

### Gabarito

1. 2 bytes — os caracteres `'4'` e `'2'`.
2. 4 bytes (assumindo `int` de 32 bits) — os bytes crus do número, não seus dígitos.
3. Sequencial — a aplicação percorre registro por registro, na ordem em que estão.
4. Serializado — a ordem dos registros segue um critério (a chave CPF), pensado para
   permitir operações de busca por essa chave.

## Resumo

- Arquivo = dado que sobrevive ao fim do programa, guardado em disco.
- Binário: bytes crus da memória, unidade = registro. Texto: caracteres legíveis, unidade =
  caractere, geralmente maior.
- Sequencial vs. serializado é um eixo **independente**: sobre ordem de acesso, não sobre
  formato dos bytes.

**Próximo:** [[Teoria 02 - Stream, cursor, buffer e as duas famílias de funções de E-S]].
