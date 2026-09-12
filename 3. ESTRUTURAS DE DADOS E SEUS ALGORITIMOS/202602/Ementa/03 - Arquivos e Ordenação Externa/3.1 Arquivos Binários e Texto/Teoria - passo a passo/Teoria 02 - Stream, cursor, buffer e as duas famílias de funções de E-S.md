# Teoria 02 — Stream, cursor, buffer, e as duas famílias de funções de E/S

> **Onde isto entra:** o vocabulário (stream, cursor, buffer) que qualquer função de
> arquivo em C pressupõe, e o motivo de existirem duas famílias de funções — uma para
> texto, outra para binário — em vez de uma só.
> **Antes:** [[Teoria 01 - O que é um arquivo, e por que binário ou texto]].
> **Fonte:** `08_Arquivos.pdf` (págs. 4–6) e `09_Arquivos_Texto.pdf` (págs. 3–5), slides da
> disciplina.

## 1. A ideia em uma frase

**Stream** é o caminho por onde os dados fluem entre seu programa e o arquivo; **cursor** é
a posição atual nesse caminho; **buffer** é uma área de RAM que serve de ponte, para não
transferir byte a byte diretamente com o disco (lento).

## 2. Por que precisamos desses três conceitos

Programas conversam com fontes de dados muito diferentes (disco, pen-drive, rede, DVD —
pág. 4 do PDF). Em vez de cada função de I/O saber lidar com cada fonte específica, C
padroniza tudo atrás de uma única abstração: o **stream** (tipo `FILE *`). Não importa se é
disco ou pen-drive — o código que lê/escreve é o mesmo, porque conversa só com o stream.

## 3. Cursor — lido devagar

> 📖 Um **cursor** é associado ao stream para indicar a **próxima posição** a ser lida ou
> gravada. Começa em `0` na abertura do arquivo, e **avança automaticamente** a cada
> operação de leitura/escrita.

**Conferindo com número:** um arquivo binário guardando 3 valores `int` (4 bytes cada).
Cursor começa em `0`. Depois de ler o 1º `int`: cursor vai para `4` (avançou 4 bytes). Depois
do 2º: cursor em `8`. Depois do 3º: cursor em `12` (fim do arquivo). Cada leitura avança o
cursor exatamente pelo tamanho do que foi lido — é por isso que ler "o próximo" nunca exige
dizer de onde começar: o cursor já sabe.

## 4. Buffer — lido devagar

> 📖 **Buffer**: área de **memória principal** usada como intermediária na transferência
> de dados de/para memória secundária. Ao fechar o arquivo (`fclose`), o buffer é
> **descarregado** (tudo que estava esperando ali é finalmente escrito no disco).

**Por que isso importa na prática:** se o programa terminar de forma anormal (`abort()`),
não há garantia de que o buffer tenha sido descarregado — dados podem ser **perdidos**,
mesmo que o código tenha "escrito" no arquivo (na verdade só escreveu no buffer, que ainda
não foi para o disco). Terminar com `return 0` ou `exit()` garante o fechamento correto de
todos os arquivos abertos.

## 5. Por que existem duas famílias de funções (não uma só)

Como o **formato dos bytes** é diferente entre texto e binário (Teoria 01), a forma de
ler/escrever também precisa ser diferente:

| | Texto | Binário |
|---|---|---|
| Abrir | `fopen(nome, "r")`, `"w"`, `"a"`, `"r+"`, `"w+"`, `"a+"` | `fopen(nome, "rb")`, `"wb"`, `"ab"`, `"rb+"`, `"wb+"`, `"ab+"` (mesmo `"..."` + `b`) |
| Ler | `fscanf(fp, "%d", &n)` — interpreta caracteres como número | `fread(&n, sizeof(int), 1, fp)` — copia bytes crus direto pra variável |
| Escrever | `fprintf(fp, "%d\n", n)` — converte número em caracteres | `fwrite(&n, sizeof(int), 1, fp)` — copia bytes crus da variável pro arquivo |
| Fechar | `fclose(fp)` (igual nos dois) | `fclose(fp)` |

> 📖 **Lendo `fread(&elem_menor, sizeof(int), 1, fp)` de dentro pra fora (Teoria 3.1,
> ligando com Teoria 05 de árvores — mesma técnica de "ler devagar"):**
> 1. `&elem_menor` — endereço de uma variável **já existente**, onde o dado lido será
>    copiado (não é o `fp` que "vira" o valor — é o conteúdo do arquivo que é copiado **para
>    dentro** dessa variável).
> 2. `sizeof(int)` — quantos bytes tem **cada elemento** (aqui, o tamanho de um `int`).
> 3. `1` — quantos elementos ler de uma vez (aqui, só 1).
> 4. `fp` — de qual stream ler.
> 5. O retorno de `fread` é quantos elementos **de fato** foram lidos — se vier `1`, deu
>    certo; se vier `0`, não tinha mais nada pra ler (fim do arquivo) ou deu erro.

## 6. Conferindo: por que `fscanf`/`fprintf` não servem para binário

Tente ler um arquivo binário com `fscanf(fp, "%d", &n)`: `fscanf` espera **caracteres
representando dígitos** (`'4'`, `'2'`) e os converte para número. Mas um `int` binário não
tem dígitos — são bytes crus (ex.: o valor 42 vira os bytes `0x2A 0x00 0x00 0x00`, não os
caracteres `'4'` e `'2'`). `fscanf` tentaria interpretar esses bytes crus como se fossem
texto e provavelmente falharia ou leria lixo. Por isso a regra é rígida: **binário usa
`fread`/`fwrite`; texto usa `fscanf`/`fprintf`** — misturar as duas famílias no arquivo
errado é um erro clássico.

## 7. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `fopen(nome, "rb")` em vez de `"r"` | aviso o sistema que os bytes daqui pra frente são crus, não caracteres — muda como `fread` os interpreta |
| cursor avançando sozinho a cada leitura | não preciso calcular "onde estou" manualmente — o stream já sabe, a não ser que eu use `fseek` (Teoria 03) pra pular |
| `fclose` no fim do programa | garanto que o buffer (RAM) seja de fato gravado no disco — sem isso, dado pode "sumir" |

## 8. Exercícios de fixação

1. Por que `fopen("dados.bin", "r")` (sem o `b`) é um erro comum ao trabalhar com arquivo
   binário, mesmo que às vezes "pareça funcionar" em alguns sistemas?
2. Um arquivo binário tem 5 valores `int` (4 bytes cada). Depois de ler os 3 primeiros com
   `fread`, em que posição está o cursor?
3. O que acontece com os dados "escritos" com `fwrite` se o programa travar antes de
   `fclose` ser chamado?

### Gabarito

1. Porque sem o `b`, alguns sistemas (notavelmente Windows) fazem tradução de fim-de-linha
   (`\n` ↔ `\r\n`) — tradução que faz sentido para texto, mas **corrompe** dados binários
   crus caso algum byte do dado coincida com esses códigos de controle.
2. Cursor em `12` (3 valores × 4 bytes cada = 12 bytes já lidos).
3. Podem ser perdidos — `fwrite` escreve no **buffer** (RAM), e só `fclose` (ou término
   normal do programa) garante o descarregamento (flush) desse buffer para o disco de fato.

## Resumo

- Stream (`FILE *`) é a abstração única para "conversar" com qualquer fonte de dados.
- Cursor = posição atual no stream, avança sozinho a cada leitura/escrita.
- Buffer = intermediário em RAM; só é gravado no disco de fato ao fechar o arquivo.
- Duas famílias de função, nunca misturadas: texto → `fscanf`/`fprintf`; binário →
  `fread`/`fwrite`, com `"b"` no modo de `fopen`.

**Próximo:** [[Teoria 03 - Acesso aleatório em arquivo binário (fseek, ftell, rewind)]].
