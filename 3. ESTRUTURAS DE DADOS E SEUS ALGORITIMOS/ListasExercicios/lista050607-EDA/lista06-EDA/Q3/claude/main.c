#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================= *
 * LISTA 06 - Q3
 *
 * "Receba o arquivo de clientes do Q2 e produza um arquivo binario
 *  de indices 'indices.bin', onde a sequencia de indices descreve os
 *  registros do arquivo de clientes ORDENADOS PELO SALDO."
 *
 * ----------------------------------------------------------------- *
 * O QUE E UM "ARQUIVO DE INDICES"
 *   Em vez de reordenar fisicamente 'clientes.bin' (caro: mexeria
 *   em registros grandes), criamos um arquivo pequeno so com as
 *   POSICOES (0, 1, 2, ...) dos registros, mas na ORDEM do saldo.
 *
 *   Exemplo: se o registro 3 tem o menor saldo, o registro 1 o
 *   segundo menor, etc., entao 'indices.bin' = [3, 1, ...].
 *   Para listar os clientes por saldo crescente basta ler
 *   'indices.bin' em ordem e, para cada indice i, dar
 *   fseek(clientes, i * sizeof(Cliente), SEEK_SET) e ler o registro.
 *
 * PASSO A PASSO de gera_indices:
 *   1. abro 'clientes.bin' e descubro quantos registros ha
 *      (tamanho do arquivo / sizeof(Cliente)).
 *   2. leio APENAS o saldo de cada registro para um vetor 'saldo[]'
 *      e inicializo 'idx[] = {0,1,2,...,n-1}'.
 *      (carrego so os saldos + os indices, nao os registros
 *       inteiros).
 *   3. ordeno 'idx[]' de forma que saldo[idx[0]] <= saldo[idx[1]]
 *      <= ...  -> usei INSERTION SORT comparando pelos saldos.
 *   4. gravo 'idx[]' (n inteiros) em 'indices.bin'.
 *
 * CUSTO: O(n^2) na ordenacao (facil de trocar por algo O(n log n));
 *        memoria O(n) - so saldos e indices, nunca os registros.
 * ================================================================= */

#define TAM_NOME 40
#define TAM_CPF  11
#define MAXREG   100000

typedef struct {
    char  nome[TAM_NOME];
    char  cpf[TAM_CPF];
    int   conta_corrente;
    int   agencia;
    float saldo;
} Cliente;

void gera_indices(const char *arqClientes, const char *arqIndices) {
    FILE *fc = fopen(arqClientes, "rb");
    if (!fc) { printf("gera_indices: nao abriu '%s'.\n", arqClientes); return; }

    /* (1) quantos registros? */
    fseek(fc, 0, SEEK_END);
    long bytes = ftell(fc);
    rewind(fc);
    int n = (int)(bytes / (long)sizeof(Cliente));
    if (n <= 0 || n > MAXREG) {
        printf("gera_indices: nada a fazer (n = %d).\n", n);
        fclose(fc);
        return;
    }

    /* (2) le apenas os saldos + monta idx = 0..n-1 */
    static float saldo[MAXREG];
    static int   idx[MAXREG];
    Cliente c;
    for (int i = 0; i < n; i++) {
        fread(&c, sizeof(Cliente), 1, fc);
        saldo[i] = c.saldo;
        idx[i]   = i;
    }
    fclose(fc);

    /* (3) insertion sort de idx[] usando saldo[] como chave */
    for (int i = 1; i < n; i++) {
        int chave = idx[i];
        int j = i - 1;
        while (j >= 0 && saldo[idx[j]] > saldo[chave]) {
            idx[j + 1] = idx[j];
            j--;
        }
        idx[j + 1] = chave;
    }

    /* (4) grava os indices */
    FILE *fi = fopen(arqIndices, "wb");
    if (!fi) { printf("gera_indices: nao abriu '%s'.\n", arqIndices); return; }
    fwrite(idx, sizeof(int), n, fi);
    fclose(fi);
}

/* ---- utilitarios de teste ------------------------------------- */

static Cliente novo(const char *nome, const char *cpf, float s) {
    Cliente c;
    memset(&c, 0, sizeof c);
    snprintf(c.nome, TAM_NOME, "%s", nome);
    memcpy(c.cpf, cpf, TAM_CPF);
    c.conta_corrente = 0;
    c.agencia = 0;
    c.saldo = s;
    return c;
}

/* percorre indices.bin e mostra os clientes na ordem do saldo,
 * lendo cada registro sob demanda com fseek (nao carrega tudo).  */
static void lista_por_indice(const char *arqClientes, const char *arqIndices) {
    FILE *fi = fopen(arqIndices, "rb");
    FILE *fc = fopen(arqClientes, "rb");
    if (!fi || !fc) { printf("(falha ao abrir arquivos)\n"); return; }

    int i;
    while (fread(&i, sizeof(int), 1, fi) == 1) {
        Cliente c;
        fseek(fc, (long)i * (long)sizeof(Cliente), SEEK_SET);
        fread(&c, sizeof(Cliente), 1, fc);
        printf("  indice %d -> %-14.*s  saldo %8.2f\n",
               i, TAM_NOME, c.nome, c.saldo);
    }
    fclose(fi);
    fclose(fc);
}

int main(void) {
    FILE *fp = fopen("clientes.bin", "wb");
    Cliente cs[] = {
        novo("Ana Souza",   "11111111111", 1500.00f),  /* indice 0 */
        novo("Bruno Lima",  "22222222222",  300.50f),  /* indice 1 */
        novo("Carla Dias",  "33333333333", 9800.75f),  /* indice 2 */
        novo("Diego Alves", "44444444444",   45.20f),  /* indice 3 */
    };
    fwrite(cs, sizeof(Cliente), 4, fp);
    fclose(fp);

    gera_indices("clientes.bin", "indices.bin");

    printf("Clientes por saldo CRESCENTE (via indices.bin):\n");
    lista_por_indice("clientes.bin", "indices.bin");
    printf("\nOrdem de indices esperada: 3 (45.20), 1 (300.50), 0 (1500.00), 2 (9800.75)\n");

    return 0;
}
