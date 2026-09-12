#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================= *
 * LISTA 05 - Q2
 *
 * "Receba o nome de um arquivo texto cujo conteudo sao o nome do
 *  aluno e as duas notas, um aluno por linha, e gere um arquivo de
 *  saida ordenado em ordem CRESCENTE pela MEDIA do aluno."
 *
 *      void media(char *ArqEnt, char *ArqSaida);
 *
 * FORMATO ADOTADO (a partir do exemplo do enunciado)
 *   entrada, uma linha por aluno:   nome/nota1/nota2
 *       P C/10.0/10.0
 *       J J/3.0/4.0
 *       G G/7.0/7.0
 *       A A/0.5/1.5
 *       I I/5.0/6.0
 *   saida, uma linha por aluno, ja ordenada:   nome/media
 *       A A/1.0
 *       J J/3.5
 *       I I/5.5
 *       G G/7.0
 *       P C/10.0
 *   (o nome pode conter espacos; as notas usam ponto decimal)
 *
 * ----------------------------------------------------------------- *
 * PASSO A PASSO
 *   1. Leio o arquivo de entrada linha a linha com fgets.
 *   2. Para cada linha faco o PARSING pelos separadores '/':
 *        - a ULTIMA '/' separa nota2 do resto;
 *        - a PENULTIMA '/' separa nota1 do nome.
 *      Uso strrchr (busca da direita p/ esquerda) para achar as duas
 *      barras sem me preocupar se o nome tem espacos.
 *   3. Guardo (nome, media) num vetor de structs, com
 *        media = (nota1 + nota2) / 2.0
 *   4. Ordeno o vetor por media crescente. Usei INSERTION SORT
 *      escrito a mao (estavel e simples) para deixar o algoritmo
 *      visivel; qsort da <stdlib.h> tambem serviria.
 *   5. Escrevo o arquivo de saida no formato "nome/media" com uma
 *      casa decimal (%.1f), como no gabarito.
 *
 * CUSTO: O(a^2) na ordenacao (a = numero de alunos); trivial para
 *        turmas reais. Leitura/escrita O(tamanho do arquivo).
 * ================================================================= */

#define MAXLIN 512
#define MAXALU 1000

typedef struct {
    char  nome[MAXLIN];   /* mesmo tamanho do buffer de leitura */
    double media;
} Aluno;

/* extrai nome e as duas notas de uma linha "nome/n1/n2".
 * retorna 1 em caso de sucesso, 0 se a linha estiver malformada.   */
static int parse_linha(char *linha, Aluno *a) {
    /* remove '\n' / '\r' do final */
    linha[strcspn(linha, "\r\n")] = '\0';
    if (linha[0] == '\0')
        return 0;                       /* linha em branco           */

    char *barra2 = strrchr(linha, '/'); /* ultima  '/'  -> antes de n2 */
    if (!barra2) return 0;
    *barra2 = '\0';                      /* corta: agora linha = "nome/n1" */
    char *barra1 = strrchr(linha, '/'); /* penultima '/' -> antes de n1 */
    if (!barra1) return 0;
    *barra1 = '\0';                      /* agora linha = "nome"      */

    double n1 = atof(barra1 + 1);
    double n2 = atof(barra2 + 1);

    snprintf(a->nome, sizeof(a->nome), "%s", linha);
    a->media = (n1 + n2) / 2.0;
    return 1;
}

void media(char *ArqEnt, char *ArqSaida) {
    FILE *fe = fopen(ArqEnt, "r");
    if (!fe) { printf("media: nao abriu '%s'.\n", ArqEnt); return; }

    static Aluno v[MAXALU];   /* 'static': evita vetor grande na pilha */
    int n = 0;
    char linha[MAXLIN];

    while (n < MAXALU && fgets(linha, sizeof(linha), fe))
        if (parse_linha(linha, &v[n]))
            n++;
    fclose(fe);

    /* --- insertion sort por media crescente --- */
    for (int i = 1; i < n; i++) {
        Aluno chave = v[i];
        int j = i - 1;
        while (j >= 0 && v[j].media > chave.media) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }

    FILE *fs = fopen(ArqSaida, "w");
    if (!fs) { printf("media: nao abriu '%s'.\n", ArqSaida); return; }
    for (int i = 0; i < n; i++)
        fprintf(fs, "%s/%.1f\n", v[i].nome, v[i].media);
    fclose(fs);
}

/* ---- teste ------------------------------------------------------- */
static void mostra_arquivo(const char *nome) {
    FILE *fp = fopen(nome, "r");
    if (!fp) { printf("(nao abriu %s)\n", nome); return; }
    int c;
    while ((c = fgetc(fp)) != EOF) putchar(c);
    fclose(fp);
}

int main(void) {
    const char *ent = "entrada_q2.txt";
    const char *sai = "saida_q2.txt";

    FILE *fp = fopen(ent, "w");
    fputs("P C/10.0/10.0\n"
          "J J/3.0/4.0\n"
          "G G/7.0/7.0\n"
          "A A/0.5/1.5\n"
          "I I/5.0/6.0\n", fp);
    fclose(fp);

    printf("--- ENTRADA (nome/nota1/nota2) ---\n");
    mostra_arquivo(ent);

    media((char *)ent, (char *)sai);

    printf("\n--- SAIDA (nome/media, ordenada por media crescente) ---\n");
    mostra_arquivo(sai);

    printf("\nEsperado:\nA A/1.0\nJ J/3.5\nI I/5.5\nG G/7.0\nP C/10.0\n");
    return 0;
}
