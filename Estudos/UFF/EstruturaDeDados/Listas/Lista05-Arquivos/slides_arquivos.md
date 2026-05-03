



(Q1) Desenvolva um procedimento que receba o nome de um arquivo texto e retire deste texto
palavras consecutivas repetidas. O seu programa deve retornar, no arquivo de saída, informado
como parâmetro dessa função, a resposta desta questão. Por exemplo, se o conteúdo de um arquivo
texto for: "Isto e um texto texto repetido repetido repetido . Com as repeticoes
repeticoes fica fica sem sem sentido . Sem elas elas elas melhora melhora um um
pouco .", a saída do seu programa será um arquivo com o seguinte texto: "Isto e um texto
repetido . Com as repeticoes fica sem sentido . Sem elas melhora um um pouco ."
- void RetRepet(char *ArqEnt, char *ArqSaida).


---

Resolva o Exercicio Acima com base no texto abaixo;

---

Arquivos

2
Arquivos

→ Definição:
– Conjunto de dados armazenados em memória secundária

→ Tipos: binários e de texto
– Binários:
• Armazenam informações usando o sistema de numeração;
• Menor unidade de leitura: registro
• Registros são escritos/recuperados como representados em memória;
• Registros dispostos de maneira sequencial, mas podem ser acessados de maneira aleatória;
• Exemplos: <.doc>, <.ppt>, <.zip>, <.jpg>, entre outros.

– Texto:
• Dados representados como caracteres;
• Menor unidade de leitura: caracter;
• Em geral, maiores que os binários;
• Dados organizados sequencialmente;
• Exemplos: <.html>, <.c>, <.txt>, entre outros.

3
Outra classificação de arquivos

→ Outra classificação: sequenciais e em série

– Sequenciais:

• Registros acessados linearmente: i acessado após i-1;
• Aplicações: percorrimento de todos os registros;
• Exemplos: folha de pagamento, balance line em aplicações de
bancos, entre outros.

– Serializados:

• Registros armazenados segundo um critério de ordenação com
base no valor de uma chave (ou um subconjunto delas);
• Aplicações: baseadas em operações de seleção de chaves;
• Exemplos: banco de dados, entre outros.

4
Stream (Fluxo)

→ Programas interagem com fontes de dados
distintas:
– DVD, WEB, Pen-drives, arquivos em Memória
Secundária.

→ Stream: mecanismo para lidar com essas fontes

→ Fluxo ou Stream: caminho atravessado por
dados em um programa

5
Cursor e Buffer

→ Um cursor é associado ao arquivo de forma a indicar
a próxima posição a ser lida ou gravada

→ Cursor é inicializado com 0 na abertura do arquivo

→ Cursor é incrementado a cada operação de leitura
ou escrita no arquivo

→ Buffer: área da memória principal usada como meio
de transferência de informações de/para memória
secundária

6
Buffer

→ Fechamento de um arquivo: buffer
descarregado

→ Término da main com return 0 ou exit(): todos
os arquivos são fechados de maneira correta

→ abort(): sem garantias do fechamento correto
dos arquivos

---

Manipulação de Arquivos Texto

3
Algumas operações em arquivos (stdio.h)

→ Abertura:

FILE *fopen(char *nome_arq, char *modo);
Retorno: ou ≠ 0, se estiver tudo certo, ou NULL, indicando erro

Modo Significado
“r” Abre um arquivo texto para leitura. O arquivo deve existir antes de ser aberto.
“w” Abrir um arquivo texto para gravação. Se ele não existir, será criado. Se já existir, o conteúdo anterior será destruído.
“a” Abrir um arquivo texto para gravação. Os dados serão adicionados no fim do arquivo ("append"), se ele já existir, ou um novo
arquivo será criado, no caso de arquivo não existente anteriormente.
“r+” Abre um arquivo texto para leitura e gravação. O arquivo deve existir e pode ser modificado.
“w+” Cria um arquivo texto para leitura e gravação. Se o arquivo existir, o conteúdo anterior será destruído. Se não existir, será
criado.
“a+” Abre um arquivo texto para gravação e leitura. Os dados serão adicionados no fim do arquivo se ele já existir, ou um novo
arquivo será criado, no caso de arquivo não existente anteriormente.

4
→ Fechamento:

int fclose(FILE *fp);
Retorno: ou = 0, se estiver tudo certo, ou EOF, indicando erro

→ Leitura de dados:

int fscanf(FILE *fp, char *formato, <lista_endereços_variáveis>);
Retorno: número de variáveis lidas com sucesso

→ Escrita de dados:

int fprintf(FILE *fp, char *formato, <variáveis>);
Retorno: número de bytes escritos no arquivo

Algumas operações em arquivos (stdio.h)

5
Exemplo

void merge(char *a1, char *a2, char *s);
int main(int argc, char **argv){
if(argc != 4){
printf(“Erro: argumentos\n”);
exit(1);
}
merge(argv[1], argv[2], argv[3]);
return 0;
}
void merge(char *a1, char *a2, char *s){
FILE *fp1 = fopen(a1, “r”),
*fp2 = fopen(a2, “r”),
*fpo = fopen(s, “w”);
if((!fp1)||(!fp2)||(!fpo)) exit(1);
int r1, n1, r2, n2;
.
.
.

r1 = fscanf(fp1, “%d”, &n1);
r2 = fscanf(fp2, “%d”, &n2);
while((r1 == 1) || (r2 == 1)){
if((r2 != 1) || (n1 <= n2)){
fprintf(fpo, “%d\n”, n1);
r1 = fscanf(fp1, “%d”, &n1);
if(r1 != 1) n1 = INT_MAX;
}
else if((r1 != 1) || (n2 < n1)){
fprintf(fpo, “%d\n”, n2);
r2 = fscanf(fp2, “%d”, &n2);
if(r2 != 1) n2 = INT_MAX;
}
}
fclose(fp1);
fclose(fp2);
fclose(fpo);
}

---

Manipulação de Arquivos Binários

3
Algumas operações em arquivos (stdio.h)

→ Fechamento:

int fclose(FILE *fp);
Retorno: ou = 0, se estiver tudo certo, ou EOF, indicando erro

→ Abertura:

FILE *fopen(char *nome_arq, char *modo);
Retorno: ou ≠ 0, se estiver tudo certo, ou NULL, indicando erro

Modo Significado
“rb” Abre um arquivo binário para leitura. O arquivo deve existir antes de ser aberto.
“wb” Abrir um arquivo binário para gravação. Se ele não existir, será criado. Se já existir, o conteúdo anterior será destruído.
“ab” Abrir um arquivo binário para gravação. Os dados serão adicionados no fim do arquivo ("append"), se ele já existir, ou um
novo arquivo será criado, no caso de arquivo não existente anteriormente.
“rb+” Abre um arquivo binário para leitura e gravação. O arquivo deve existir e pode ser modificado.
“wb+” Cria um arquivo binário para leitura e gravação. Se o arquivo existir, o conteúdo anterior será destruído. Se não existir, será
criado.
“ab+” Abre um arquivo binário para gravação e leitura. Os dados serão adicionados no fim do arquivo se ele já existir, ou um novo
arquivo será criado, no caso de arquivo não existente anteriormente.

4
→ Leitura de dados:

int fread(void *ptr, int tam_cada_elem, int nelem, FILE *fp);
ptr? Conteúdo do arquivo é copiado para o ponteiro
tam_cada_elem? Tamanho em bytes de cada elemento
nelem? Número de elementos
Retorno: ou nelem, se estiver tudo certo, ou < nelem, indicando erro

→ Escrita de dados:

int fwrite(void *ptr, int tam_cada_elem, int nelem, FILE *fp);
Retorno: ou nelem, se estiver tudo certo, ou < nelem, indicando erro
Algumas operações em arquivos (stdio.h)

5
Algumas operações em arquivos (stdio.h)

→ Movendo o ponteiro de um arquivo binário:
int fseek(FILE *fp, long int offset, int CTE_ORIGEM);
CTE_ORIGEM:
• SEEK_CUR (= 1): posição atual
• SEEK_SET (= 0): início do arquivo
• SEEK_END (= 2): fim do arquivo
Posição final? (offset + CTE_ORIGEM) bytes
Retorno: ou = 0, se estiver tudo certo, ou ≠0, indicando erro

→ Inicializa ponteiro:
void rewind(FILE *fp); f ≡ seek(fp, 0L, SEEK_SET);

→ Obtém a posição do ponteiro:
long int ftell(FILE *fp);
Retorno: ou posição corrente, se estiver tudo certo, ou -1L, indicando erro

6
Exemplo

#include <stdio.h>
#include <stdlib.h>
int prox_mult(int elem, int pot){
int resp = 0;
while(resp <= elem) resp += pot;
return resp;
}
int bb(FILE *fp, int elem, int tipo){
int ini, fim, meio, elem_meio;
ini = ftell(fp);
fseek(fp, 0L, SEEK_END);
fim = ftell(fp) - tipo;
while(ini <= fim){
meio = (fim + ini) / 2;
if((meio % tipo) != 0) meio = prox_mult(meio, tipo);
fseek(fp, meio, SEEK_SET);
fread(&elem_meio, tipo, 1, fp);
printf("ini = %d\tfim = %d\tmeio = %d\telem = %d\n", ini, fim, meio, elem_meio);
if(elem_meio == elem) return meio;
if(elem_meio < elem) ini = meio + tipo;
if(elem_meio > elem) fim = meio - tipo;
}
return -1;
}

int main (int argc, char** argv) {
while(1){
FILE *fp = fopen(argv[1], "wb");
if(!fp) exit (1);
int n;
scanf("%d", &n);
if(n <= 0) exit(1);
int i = 1, vet[n], elem;
scanf("%d", &vet[0]);
while(i < n){
scanf("%d", &elem);
if(elem > vet[i-1]) vet[i++] = elem;
}
fwrite(vet, sizeof(int), n, fp);
fclose(fp);
printf("Digite o valor a ser procurado.\n");
scanf("%d", &elem);
fp = fopen(argv[1], "rb");
int pos = bb (fp, elem, sizeof(int));
fclose(fp);
if (pos >= 0) printf("%d\n", pos/4);
else printf("Elemento nao encontrado.\n");
}
}

---

Ordenação Externa de Arquivos

2
Ordenação externa de arquivos

→ Motivação:

– Busca binária exige que arquivo esteja ordenado
– Como ordená-lo?

→ Métodos de ordenação de arquivos?
– Ordenação em memória: Como funciona?
• Dados são lidos para um array de memória;
• Usar algum algoritmo de ordenação já existente na
literatura; e
• Gravar novo arquivo com os dados ordenados.

3
Alguns algoritmos da literatura

→ SelectionSort:
void ord_sel_sort(int *vet, int n){
int i;
for(i = 0; i < n; i++){
int j, menor = i;
for(j = i + 1; j < n; j++)
if(vet[j] < vet[menor])
menor = j;
if(menor != i){
int temp = vet[i];
vet[i] = vet[menor];
vet[menor] = temp;
}
}
}

4
Alguns algoritmos da literatura

→ Tempo gasto em ord_sel_sort é proporcional ao número de
comparações:
Primeira passada: (n – 1)
Segunda passada: (n – 2)
Terceira passada: (n – 3)
...
Última passada: 1

→ A soma desses termos supracitados é proporcional a n2. Portanto, sua
complexidade é O(n2)

→ QuickSort:
- Algoritmo mais rápido que existe: geralmente, O(n log n)
- Algoritmo recursivo
- ord_sel_sort coloca o menor elemento na primeira posição → QuickSort faz
isso com um elemento arbitrário chamado pivô

5
Ideia do QuickSort

→ Suponha que o pivô deva ocupar a posição i do vetor.

→ Suponha também que v[0] ... v[i – 1] são menores que o pivô, e v[i +
1] ... v[n – 1] sejam maiores que o pivô.

→ Posiciona-se o pivô em v[i]

→ Ordenam-se os vetores v[0] ... v[i – 1] e v[i + 1] ... v[n – 1]

→ Esses dois vetores são ordenados recursivamente. Quando os vetores
tiverem zero elementos, a ordenação está concluída.

→ Para a maioria das entradas, QuickSort é O(n log n)

→ Entradas que fazem a complexidade desse algoritmo ser O(n2)?

6
Ideia do QuickSort

→ Versão usada: pivô igual à v[0] = x

→ Início do vetor: Comparam-se v[1], v[2],... até v[a] > x

→ Final do vetor: comparam-se os elementos v[n - 1], v[n – 2], ... até encontrar v[b] ≤ x

→ Troca-se v[a] e v[b] e as buscas continuam com v[a + 1] (do início do vetor) e v[b – 1] (do
final do vetor)

→ Em algum momento, as buscas terminam porque os índices se cruzam, isto é, a > b

→ Nesse momento, a posição correta de x está definida e os valores de v[0] e v[b] são
trocados.

→ O vetor v[0] ... v[b – 1] possui somente elementos menores ou iguais a x e o vetor
v[b + 1] ... v[n – 1] possui somente elementos maiores ou iguais a x

→ Ordenam-se recursivamente os vetores v[0] ... v[b – 1] e v[b + 1] ... v[n – 1]

7
Exemplo

8
Algoritmo QuickSort (qs)

void qs(int *v, int n){
if(n <= 1) return;
int x = v[0], a = 1, b = n - 1;
do{
while((a < n) && (v[a] <= x)) a++;
while(v[b] > x) b--;
if(a < b){
int temp = v[a];
v[a++] = v[b];
v[b--] = temp;
}
}while(a <= b);
v[0] = v[b];
v[b] = x;
qs(v, b);
qs(&v[b + 1], n – b - 1);
}

9
Ordenação externa de arquivos

→ Se o arquivo cabe todo em memória principal?
- Usar ordenação em memória mesmo
- Se quiser economizar memória? Ordenar arquivo binário

→ Se o arquivo não cabe todo?
- Ordenar arquivo binário

→ Por que só pode ser feito em arquivos
binários?
- Necessário usar fseek para se deslocar

10
void ord_sel_sort_Bin(FILE *fp){
int i, j, r, s, elem_menor, menor, elem, aux;
i = ftell(fp);
r = fread(&elem_menor, sizeof(int), 1, fp);
while(r == 1){
menor = i;
aux = elem_menor;
j = ftell(fp);
s = fread(&elem, sizeof(int), 1, fp);
while(s == 1){
if(elem < elem_menor){
menor = j;
elem_menor = elem;
}
j = ftell(fp);
s = fread(&elem, sizeof(int), 1, fp);
}
SelectionSort em arquivo binário

if(menor != i){
printf("Trocar %d(%d) por %d(%d)\n", aux,
i, elem_menor, menor);
fseek(fp, menor, SEEK_SET);
fwrite(&aux, sizeof(int), 1, fp);
fseek(fp, i, SEEK_SET);
fwrite(&elem_menor, sizeof(int), 1, fp);
}
else{
fseek(fp, (i + sizeof(int)), SEEK_SET);
}
i = ftell(fp);
r = fread(&elem_menor, sizeof(int), 1, fp);
}
}

11
QuickSort em arquivo binário

---

ORDENAÇÃO EXTERNA DE ARQUIVOS: GERAÇÃO DE PARTIÇÕES
CLASSIFICADAS

Material baseado nos
slides
gentilmente cedidos pela
Professora Vanessa
Braganholo

ORDENAÇÃO DE ARQUIVOS
GRANDES

2

Para arquivos binários, é possível implementar o algoritmo de
ordenação diretamente em disco

Para arquivos texto (arquivos de acesso sequencial), acesso não
pode ser feito em posições aleatórias do arquivo
– Para ler o 10o. item é necessário antes ler os 9 itens anteriores
– Portanto, não é possível implementar a ordenação direto em disco

INSTITUTO DE COMPUTAÇÃO - UFF 3

Como ordenar arquivos de
acesso sequencial que não
cabem na memória?

TIPOS DE CLASSIFICAÇÃO

4
Classificação interna: utilização exclusiva de memória principal
– Todo o conteúdo do arquivo cabe em memória principal

Classificação externa: utilização de memória secundária
– Há mais conteúdo a ser classificado do que é possível manter na memória
principal em qualquer momento

ATENÇÃO: Nessa disciplina usamos o termo classificação como

sinônimo de ordenação

CONCEITO DE
CLASSIFICAÇÃO EXTERNA

5
Na classificação externa o parâmetro fundamental é o número de
operações de entrada e saída
– Deve ser o menor possível

DISCUSSÃO

6
Como poderíamos resolver o problema de ordenar um arquivo texto
muito grande, que não cabe em memória?

IDEIA BÁSICA DA
CLASSIFICAÇÃO EXTERNA

7
A Classificação Externa divide os arquivos em pequenas frações
que são ordenadas e intercaladas em duas etapas:
– Geração de partições classificadas
– Intercalação

MODELO DA CLASSIFICAÇÃO
EXTERNA

8

Arquivo não
Ordenado

Geração
de Partições
Classificadas

Partições

Intercalação Arquivo
Ordenado

NESSA AULA: ETAPA DE
GERAÇÃO DE PARTIÇÕES
CLASSIFICADAS

9

Arquivo não
Ordenado

Geração
de Partições
Classificadas

Partições

Intercalação Arquivo
Ordenado

ETAPA DE GERAÇÃO DE
PARTIÇÕES CLASSIFICADAS

10

Partição: sequência ordenada de n registros.
– Registros (ou strings para arquivos texto) são lidos de arquivos de entrada
(não ordenados)

– Estes registros (ou strings) são ordenados e gravados em arquivos de saída
ou partições ordenadas

OBS: A partir de agora vamos usar registro para nos referir a um dado do arquivo
(registro ou string)

GERAÇÃO DE PARTIÇÕES
CLASSIFICADAS

MÉTODOS DE GERAÇÃO DE
PARTIÇÕES CLASSIFICADAS

12

Métodos:
– Classificação interna
– Seleção com substituição
– Seleção natural

Considera-se que a memória principal tenha capacidade para
armazenar M registros do arquivo a classificar

CLASSIFICAÇÃO
INTERNA

CLASSIFICAÇÃO INTERNA

14

Consiste na leitura de M registros para a memória;

Classificação desses registros por qualquer processo de classificação
interna; e

Gravação desses registros classificados em uma partição

Todas as partições classificadas contêm M registros, exceto, talvez, a
última

Algoritmos: Bolha, SelectionSort, QuickSort, HeapSort, entre outros.

VISÃO GERAL DA GERAÇÃO DE
PARTIÇÕES CLASSIFICADAS

15

Entrada

Memória Partição de

Saída

M

M

EXEMPLO

16

Chaves do arquivo a ordenar (Sequência de leitura: 29, 14, 76,...)

Assumir que na memória cabem 6 registros simultaneamente

29 14 76 75 59 6 7 74 48 46 10 18
56 20 26 4 21 65 22 49 11 16 8 15
5 19 50 55 25 66 57 77 12 30 17 9
54 78 43 38 51 32 58 13 73 79 27 1
3 60 36 47 31

EXEMPLO

17

29 14 76 75 59 6 7 74 48 46 10 18
56 20 26 4 21 65 22 49 11 16 8 15
5 19 50 55 25 66 57 77 12 30 17 9
54 78 43 38 51 32 58 13 73 79 27 1
3 60 36 47 31

EXEMPLO

18

29 14 76 75 59 6 7 74 48 46 10 18
56 20 26 4 21 65 22 49 11 16 8 15
5 19 50 55 25 66 57 77 12 30 17 9
54 78 43 38 51 32 58 13 73 79 27 1
3 60 36 47 31

29 14 76 75 59 6
Memória Principal

Leitura

EXEMPLO

19

29 14 76 75 59 6 7 74 48 46 10 18
56 20 26 4 21 65 22 49 11 16 8 15
5 19 50 55 25 66 57 77 12 30 17 9
54 78 43 38 51 32 58 13 73 79 27 1
3 60 36 47 31

29 14 76 75 59 6

Ordenação
Memória Principal

EXEMPLO

20

29 14 76 75 59 6 7 74 48 46 10 18
56 20 26 4 21 65 22 49 11 16 8 15
5 19 50 55 25 66 57 77 12 30 17 9
54 78 43 38 51 32 58 13 73 79 27 1
3 60 36 47 31

6 14 29 69 75 76

Ordenação
Memória Principal

EXEMPLO

21

29 14 76 75 59 6 7 74 48 46 10 18
56 20 26 4 21 65 22 49 11 16 8 15
5 19 50 55 25 66 57 77 12 30 17 9
54 78 43 38 51 32 58 13 73 79 27 1
3 60 36 47 31

6 14 29 69 75 76

6 14 29 69 75 76
Partição 1 (em disco) ordenada

Memória PrincipalMemória Principal

EXEMPLO

22

29 14 76 75 59 6 7 74 48 46 10 18
56 20 26 4 21 65 22 49 11 16 8 15
5 19 50 55 25 66 57 77 12 30 17 9
54 78 43 38 51 32 58 13 73 79 27 1
3 60 36 47 31

6 14 29 69 75 76
Partição 1 (em disco) ordenada

Área de trabalho Partições obtidas
Memória 29 14 76 75 59 6 6 14 29 59 75 76

Memória 7 74 48 46 10 18 7 10 18 46 48 74

Memória 56 20 26 4 21 65 4 20 21 26 56 65

Memória 22 49 11 16 8 15 8 11 15 16 22 49

Memória 5 19 50 55 25 66 5 19 25 50 55 66

Memória 57 77 12 30 17 9 9 12 17 30 57 77

Memória 54 78 43 38 51 32 32 38 43 51 54 78

Memória 58 13 73 79 27 1 1 13 27 58 73 79

Memória 3 60 36 47 31 3 31 36 47 60

CLASSIFICAÇÃO INTERNA

int compara(const void *p1,const void *p2){
int *i1 = (int *)p1, *i2 = (int *)p2;
if((*i1) > (*i2))return 1;
if((*i1) < (*i2))return -1;
return 0;
}
int classInterna(char *nome, char *parte){
int n;
while(1){
scanf("%d", &n);
if(n > 0) break;
}
int vet[n];
int r, i, aux, particoes=0;
char aux2[41], num[5];
FILE *fp = fopen(nome,"rt"), *fp2;
if(!fp) exit(1);
while(1){
i=0;

while(i < n){
r = fscanf(fp,"%d",&aux);
if(r != 1)break;
vet[i++]=aux;
}
if(!i) break;
qsort(vet,i,sizeof(int),compara);
particoes++;
strcpy(aux2,parte);
sprintf(num,"%d",particoes);
strcat(aux2,num);
strcat(aux2,".txt");
fp2 = fopen(aux2,"wt");
if(!fp2)exit(1);
int j;
for(j=0;j<i;j++)fprintf(fp2,"%d\n",vet[j]);
fclose(fp2);
}
fclose(fp);
return particoes;
}

SELEÇÃO COM
SUBSTITUIÇÃO

SELEÇÃO COM
SUBSTITUIÇÃO

26

Aproveita a possível classificação parcial do arquivo de entrada

ALGORITMO

1. Ler M registros do arquivo para a memória
2. Selecionar, no array em memória, o registro r com menor chave
3. Gravar o registro r na partição de saída
4. Substituir, no array em memória, o registro r pelo próximo registro do arquivo de entrada
5. Caso a chave deste último seja menor do que a chave recém gravada, considerá-lo
congelado e ignorá-lo no restante do processamento
6. Caso existam em memória registros não congelados, voltar ao passo 2
7. Caso contrário:
– fechar a partição de saída
– descongelar os registros congelados
– abrir nova partição de saída
– voltar ao passo 2

27

EXEMPLO

28

Chaves do arquivo a ordenar (Sequência de leitura: 29, 14, 76,...)

Assumir que na memória cabem 6 registros simultaneamente

29 14 76 75 59 6 7 74 48 46 10 18
56 20 26 4 21 65 22 49 11 16 8 15
5 19 50 55 25 66 57 77 12 30 17 9
54 78 43 38 51 32 58 13 73 79 27 1
3 60 36 47 31 80

1

Área de trabalho Partições obtidas
Registros 1 2 3 4 5 6 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
3
a
substituição 20
2a
substituição 10 18 74
1
a
substituição 46 48 4 26 56 7
Memória 29 14 76 75 59 6 6 7 14 29 46 48 59 74 75 76

A 1a
partição ficou com 10 registros

2
a
substituição 19 16 11 15
1a
substituição 65 22 21 8 5 49
Memória 10 18 4 26 56 20 4 10 18 20 21 22 26 49 56 65

A 2a
partição ficou com 10 registros

3
a
substituição 43
2
a
substituição 78 9 12 17 30 54
1a
substituição 77 57 25 55 50 66
Memória 19 16 11 8 5 15 5 8 11 15 16 19 25 50 55 57 66 77 78

A 3a
partição ficou com 13 registros

3a
substituição 60
2a
substituição 36 73 27 13 3
1a
substituição 79 38 51 32 58 1
Memória 43 9 12 17 30 54 9 12 17 30 32 38 43 51 54 58 73 79

A 4a
partição ficou com 12 registros

1a
substituição 80 31 47
Memória 36 60 27 13 3 1 1 3 13 27 31 36 47 60 80

A 5a
partição ficou com 9 registros

Legenda

Registros congelados Divisão de regiões na tabela

TAMANHO DAS PARTIÇÕES
GERADAS

30

Em média, o tamanho das partições obtidas pelo processo de
seleção com substituição é de 2 * M

SELEÇÃO COM
SUBSTITUIÇÃO

---

SELEÇÃO NATURAL

SELEÇÃO NATURAL

33
Desvantagem da seleção com substituição: no final da partição grande parte do espaço em
memória principal está ocupado com registros congelados

Na seleção natural, reserva-se um espaço de memória secundária (o reservatório) para
abrigar os registros congelados num processo de substituição

A formação de uma partição se encerra quando o reservatório estiver cheio ou quando
terminarem os registros de entrada

Para a memória comportando M registros supõe-se um reservatório comportando n registros

Para M = n o comprimento médio das partições é de M * e, onde e = 2,718... .

ALGORITMO

1. Ler M registros do arquivo para a memória
2. Selecionar, no array em memória, o registro r com menor chave
3. Gravar o registro r na partição de saída
4. Substituir, no array em memória, o registro r pelo próximo registro do arquivo de entrada
5. Caso a chave deste último seja menor do que a chave recém gravada, gravá-lo no reservatório
e substituir, no array em memória, o registro r pelo próximo registro do arquivo de entrada
6. Caso ainda exista espaço livre no reservatório, voltar ao passo 2
7. Caso contrário:
– fechar a partição de saída
– copiar os registros do reservatório para o array em memória
– esvaziar o reservatório
– abrir nova partição de saída
– voltar ao passo 2

34

EXEMPLO

35

Chaves do arquivo a ordenar (Sequência de leitura: 29, 14, 76,...)

Assumir que na memória cabem 6 registros simultaneamente (M =
6), e que o tamanho do reservatório também é 6 (n = 6)

29 14 76 75 59 6 7 74 48 46 10 18
56 20 26 4 21 65 22 49 11 16 8 15
5 19 50 55 25 66 57 77 12 30 17 9
54 78 43 38 51 32 58 13 73 79 27 1
3 60 36 47 31 80

36

Área de trabalho Partições obtidas
Registros 1 2 3 4 5 6 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
2a
substituição 56 74
1a
substituição 46 48 7
Memória 29 14 76 75 59 6 6 7 14 29 46 48 56 59 74 75 76
Reservatório 10 18 20 26 4 21

A 1a
partição ficou com 11 registros

1a
substituição 22 49 65
Memória 10 18 20 26 4 21 4 10 18 20 21 22 26 49 65
Reservatório 11 16 8 15 5 19

A 2a
partição ficou com 9 registros

3a
substituição 54
2a
substituição 30 78
1a
substituição 25 57 55 66 50 77
Memória 11 16 8 15 5 19 5 8 11 15 16 19 25 30 50 54 55 57 66 77 78
Reservatório 12 17 9 43 38 51

A 3a
partição ficou com 15 registros

2a
substituição 79
1a
substituição 58 73 32 47 60
Memória 12 17 9 43 38 51 9 12 17 32 38 43 47 51 58 60 73 79
Reservatório 13 27 1 3 36 31

A 4a
partição ficou com 12 registros

1a
substituição 80
Memória 13 27 1 3 36 31 1 3 13 27 31 36 80
Reservatório A 5a

partição ficou com 7 registros

SELEÇÃO NATURAL

COMPARAÇÃO DOS
PROCESSOS

38
A classificação interna gera as menores partições, o que implica em
mais arquivos a intercalar

Os processos de seleção geram partições maiores, reduzindo o
tempo total de processamento

A seleção natural sofre o ônus adicional de utilizar mais operações
de entrada e saída (devido ao reservatório estar em memória
secundária)

REFERÊNCIA

Ferraz, I. N. Programação com Arquivos. Editora Manole Ltda.
Barueri, 2003.

---

ORDENAÇÃO EXTERNA DE ARQUIVOS: INTERCALAÇÃO DE PARTIÇÕES
ORDENADAS
Material baseado nos
slides
gentilmente cedidos pela
Professora Vanessa
Braganholo
RELEMBRANDO MODELO DA
CLASSIFICAÇÃO EXTERNA
2
Arquivo não
Ordenado
Geração de
Partições
Classificadas
Partições
Intercalação Arquivo
Ordenado
NESSA AULA: ETAPA DE
INTERCALAÇÃO
3
Arquivo não
Ordenado
Geração de
Partições
Classificadas
Partições
Intercalação Arquivo
Ordenado
OBJETIVO DA ETAPA DE
INTERCALAÇÃO
4
→ Transformar um conjunto de partições classificadas por
determinado critério, em um único arquivo contendo todos os
registros de todas as partições originais do conjunto
→ O arquivo gerado deve estar classificado pelo mesmo critério de
classificação das partições iniciais
PROBLEMA
5
→ Considere a existência de R partições geradas pelo processo de
geração de partições
→ Como gerar o arquivo a partir das R partições?
ALGORITMO BÁSICO
→ De cada um dos arquivos a intercalar basta ter em memória um registro
→ Considera-se cada arquivo como uma pilha
– Topo da pilha: registro em memória
→ Em cada iteração do algoritmo, o topo da pilha com menor chave é gravado no
arquivo de saída e é substituído pelo seu sucessor
→ Pilhas vazias têm topo igual a high value
→ O algoritmo termina quando todos os topos da pilha tiverem high value
6
ESQUEMA BÁSICO DE
INTERCALAÇÃO
Livro pág. 55 7
2
6
10
13
15
20
31
40
41
51
60
69
70
76
31 76 41 69 13 2 6
70 40 20 10
51 15
60
Arquivos por intercalar
(cada coluna representa um arquivo)
Programa de Intercalação
NÚMERO DE ITERAÇÕES
→ A cada iteração, encontra-se a menor chave (O(n))
– n é o número de arquivos a intercalar
→ Número de iterações = número total de registros a serem
ordenados
8
31 76 41 69 13 2 6
70 40 20 10
51 15
60
MAS…
→ E se a quantidade de arquivos a intercalar for muito grande?
– Encontrar o menor valor de chave pode ser uma tarefa custosa
– Operação de busca da menor chave tem que ser repetida várias e várias
vezes, até os arquivos terminarem
10
OTIMIZAÇÃO DO
ALGORITMO
Árvore Binária de Vencedores
11
ÁRVORE BINÁRIA DE
VENCEDORES
INSTITUTO DE COMPUTAÇÃO - UFF 12
ÁRVORE BINÁRIA DE
VENCEDORES
→ Nós folha representam as chaves que estão nos topos das pilhas
dos arquivos a intercalar
→ Cada nó interno representa o menor de seus dois filhos
→ A raiz representa o menor nó da árvore
13
ÁRVORE BINÁRIA DE
VENCEDORES
→ Cada nó da árvore tem os seguintes componentes
– vencedor: valor da menor chave daquela sub-árvore
– f: variável FILE atrelada ao arquivo do vencedor
– esq: ponteiro para o filho da esquerda
– dir: ponteiro para o filho da direita
14
EXEMPLO
→ Arquivos a serem ordenados
– Cada coluna abaixo representa um arquivo com suas respectivas chaves
– As variáveis FILE associadas a cada arquivo nesse exemplo são f1, f2, ...,
f7
15
31 76 41 69 13 2 6
70 40 20 10
51 15
60
f1 f2 f3 f4 f5 f6 f7
ÁRVORE BINÁRIA DE
VENCEDORES
Criar os nós folha da árvore contendo a primeira chave de cada
arquivo
16
31 76 41 69 13 2 6
70 40 20 10
51 15
60
31 76 41 69 13 2 6
f1 f2 f3 f4 f5 f6 f7
ÁRVORE BINÁRIA DE
VENCEDORES
Criar um nó raiz para cada 2 nós folha, com o menor dos dois
valores
17
31 76 41 69 13 2 6
70 40 20 10
51 15
60
31 76 41 69 13 2 6
31 41 2
f1 f2 f3 f4 f5 f6 f7
ÁRVORE BINÁRIA DE
VENCEDORES
Representação do nó interno 41
– Vencedor: 41
– f: f3
– esq: ptr 41
– dir: ptr 69
18
31 76 41 69 13 2 6
70 40 20 10
51 15
60
31 76 41 69 13 2 6
31 41 2
f1 f2 f3 f4 f5 f6 f7
ÁRVORE BINÁRIA DE
VENCEDORES
19
31 76 41 69 13 2 6
70 40 20 10
51 15
60
31 76 41 69 13 2 6
31 41 2
31 2
Atenção: valores de
chave se repetem
em vários níveis
f1 f2 f3 f4 f5 f6 f7
ÁRVORE BINÁRIA DE
VENCEDORES
20
31 76 41 69 13 2 6
70 40 20 10
51 15
60
31 76 41 69 13 2 6
31 41 2
31 2
2
Raiz tem chave de
menor valor
f1 f2 f3 f4 f5 f6 f7
USO DA ÁRVORE DE VENCEDORES
NO ALGORITMO DE INTERCALAÇÃO
→ Chave da raiz é retirada e registro correspondente é inserido no
arquivo
21
31 76 41 69 13 2 6
31 41 2
31 2
2
ÁRVORE BINÁRIA DE
VENCEDORES
22
31 76 41 69 13 2 6
70 40 20 10
51 15
60
2
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
23
31 76 41 69 13 20 6
70 40 51 10
15
60
Só é necessário
comparar 20 com os
nós que fazem parte
daquele ramo da
árvore até chegar na
raiz
31 76 41 69 13 20 6
31 41
31
2
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
24
31 76 41 69 13 20 6
70 40 51 10
15
60
31 76 41 69 13 20 6
31 41 13
31 6
6
2
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
25
31 76 41 69 13 20 6
70 40 51 10
15
60
31 76 41 69 13 20 6
31 41 13
31 6
6
2
6
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
26
31 76 41 69 13 20 10
70 40 51 15
60
31 76 41 69 13 20 10
31 41 13
31
2
6
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
27
31 76 41 69 13 20 10
70 40 51 15
60
31 76 41 69 13 20 10
31 41 13
31 10
10
2
6
10
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
28
31 76 41 69 13 20 15
70 40 51 60
31 76 41 69 13 20 15
31 41 13
31 13
13
2
6
10
13
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
29
31 76 41 69 40 20 15
70 51 60
31 76 41 69 40 20 15
31 41 20
31 15
15
2
6
10
13
15
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
30
31 76 41 69 40 20 60
70 51
31 76 41 69 40 20 60
31 41 20
31 20
20
2
6
10
13
15
20
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
31
31 76 41 69 40 51 60
70
31 76 41 69 40 51 60
31 41 40
31 40
31
2
6
10
13
15
20
31
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
32
70 76 41 69 40 51 60
70 76 41 69 40 51 60
70 41 40
41 40
40
2
6
10
13
15
20
31
40
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
33
70 76 41 69 51 60
70 76 41 69 HV 51 60
70 41 51
41 51
41
2
6
10
13
15
20
31
40
41
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
34
70 76 69 51 60
70 76 HV 69 HV 51 60
70 69 51
69 51
51
2
6
10
13
15
20
31
40
41
51
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
35
70 76 69 60
70 76 HV 69 HV HV 60
70 69 HV
69 60
60
2
6
10
13
15
20
31
40
41
51
60
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
36
70 76 69
70 76 HV 69 HV HV HV
70 69 HV
69 HV
69
2
6
10
13
15
20
31
40
41
51
60
69
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
37
70 76
70 76 HV HV HV HV HV
70 HV HV
70 HV
70
2
6
10
13
15
20
31
40
41
51
60
69
70
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
38
76
HV 76 HV HV HV HV HV
76 HV HV
76 HV
76
2
6
10
13
15
20
31
40
41
51
60
69
70
76
Arquivo de saída
ÁRVORE BINÁRIA DE
VENCEDORES
39
HV HV HV HV HV HV HV
HV HV HV
HV HV
HV
2
6
10
13
15
20
31
40
41
51
60
69
70
76
Arquivo de saída
DISCUSSÃO
→ Montagem da árvore: O(n)
→ A cada iteração, faz-se log n comparações (n é o número de
arquivos a comparar)
→ Número de iterações: número total de registros a serem
ordenados
