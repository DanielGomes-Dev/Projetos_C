#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================= *
 * LISTA 06 - Q2
 *
 * "Receba um arquivo binario de clientes 'clientes.bin' e, SEM LER
 *  TODOS OS REGISTROS PARA A MEMORIA, permita consultar os dados de
 *  um cliente pelo seu CPF."
 *
 *  Formato do registro:
 *      nome            char[40]
 *      cpf             char[11]   (11 digitos, sem '\0')
 *      conta_corrente  int
 *      agencia         int
 *      saldo           float
 *
 * ----------------------------------------------------------------- *
 * IDEIA
 *   "Sem ler todos os registros para a memoria" => faco uma BUSCA
 *   SEQUENCIAL lendo UM registro por vez do arquivo (fread de 1
 *   struct), comparo o CPF e paro assim que encontrar. No pior caso
 *   (CPF inexistente) percorro o arquivo todo, mas em RAM fica
 *   somente 1 registro de cada vez - O(1) de memoria.
 *
 *   Como o CPF tem exatamente 11 bytes e pode nao ter terminador,
 *   comparo com memcmp sobre 11 bytes (nao strcmp).
 *
 * PASSO A PASSO de consulta_cpf:
 *   1. abre 'clientes.bin' em "rb";
 *   2. le registros num laco while(fread(&c,sizeof(c),1,fp)==1);
 *   3. se memcmp(c.cpf, alvo, 11) == 0  -> achou: imprime e retorna;
 *   4. terminou o arquivo sem achar -> informa "nao encontrado".
 *
 * CUSTO: O(N) leituras no pior caso; O(1) de memoria.
 *   (Um indice em arquivo - ver Q3 - permitiria busca mais rapida.)
 * ================================================================= */

#define TAM_NOME 40
#define TAM_CPF  11

typedef struct {
    char  nome[TAM_NOME];
    char  cpf[TAM_CPF];
    int   conta_corrente;
    int   agencia;
    float saldo;
} Cliente;

/* busca por CPF (string de 11 caracteres) lendo 1 registro por vez */
void consulta_cpf(const char *arq, const char *cpf_alvo) {
    FILE *fp = fopen(arq, "rb");
    if (!fp) {
        printf("consulta_cpf: nao abriu '%s'.\n", arq);
        return;
    }

    Cliente c;
    long pos = 0;
    while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
        if (memcmp(c.cpf, cpf_alvo, TAM_CPF) == 0) {
            char cpf[TAM_CPF + 1];
            memcpy(cpf, c.cpf, TAM_CPF);
            cpf[TAM_CPF] = '\0';
            printf("CPF %s encontrado (registro %ld):\n", cpf, pos);
            printf("   nome           : %.*s\n", TAM_NOME, c.nome);
            printf("   conta_corrente : %d\n", c.conta_corrente);
            printf("   agencia        : %d\n", c.agencia);
            printf("   saldo          : %.2f\n", c.saldo);
            fclose(fp);
            return;
        }
        pos++;
    }
    fclose(fp);

    char cpf[TAM_CPF + 1];
    memcpy(cpf, cpf_alvo, TAM_CPF);
    cpf[TAM_CPF] = '\0';
    printf("CPF %s NAO encontrado em '%s'.\n", cpf, arq);
}

/* ---- utilitarios de teste ------------------------------------- */

static Cliente novo(const char *nome, const char *cpf, int cc, int ag, float s) {
    Cliente c;
    memset(&c, 0, sizeof c);
    snprintf(c.nome, TAM_NOME, "%s", nome);
    memcpy(c.cpf, cpf, TAM_CPF);          /* cpf tem exatamente 11 chars */
    c.conta_corrente = cc;
    c.agencia = ag;
    c.saldo = s;
    return c;
}

int main(void) {
    /* cria clientes.bin com 4 registros */
    FILE *fp = fopen("clientes.bin", "wb");
    Cliente cs[] = {
        novo("Ana Souza",     "11111111111", 1001, 55, 1500.00f),
        novo("Bruno Lima",    "22222222222", 1002, 55,  300.50f),
        novo("Carla Dias",    "33333333333", 1003, 77, 9800.75f),
        novo("Diego Alves",   "44444444444", 1004, 77,   45.20f),
    };
    fwrite(cs, sizeof(Cliente), 4, fp);
    fclose(fp);

    printf("Consultas em clientes.bin:\n\n");
    consulta_cpf("clientes.bin", "33333333333");   /* existe   */
    printf("\n");
    consulta_cpf("clientes.bin", "99999999999");   /* nao existe */

    return 0;
}
