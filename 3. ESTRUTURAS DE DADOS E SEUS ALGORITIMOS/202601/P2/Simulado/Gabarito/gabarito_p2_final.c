/*
 * SimulEDA P2 – Gabarito (questoes 3 a 9)
 *
 * Como compilar (separado por modulo):
 *
 *   Q3 e Q4:  gcc -Wall -o q34  gabarito_q34.c  TARVB.c TLSE.c
 *   Q5:       gcc -Wall -o q5   gabarito_q5.c   TARVBM.c
 *   Q6,7,8:   gcc -Wall -o q678 gabarito_q678.c
 *   Q9:       gcc -Wall -o q9   gabarito_q9.c
 *
 * IMPORTANTE: TARVB.c e TARVBM.c possuem ambos uma funcao global chamada
 * "remover", por isso nao podem ser ligados na mesma unidade de compilacao.
 */

/* ===================================================================
 * ARQUIVO: gabarito_q34.c
 * Questoes 3 e 4 – usa TARVB.h / TARVB.c  +  TLSE.h / TLSE.c
 * =================================================================== */

#include "TARVB.h"   /* TARVB, TARVB_Inicializa, TARVB_Insere,
                        TARVB_Libera, TARVB_Imprime2             */
#include "TLSE.h"    /* TLSE, TLSE_insere, TLSE_imprime,
                        TLSE_libera                              */

/* ------------------------------------------------------------------
 * QUESTAO 3 – TARVB* espelha(TARVB *a)
 *
 * Espelhar uma Arvore B significa inverter, em CADA no, tanto o
 * vetor de chaves quanto o vetor de filhos.  A operacao e feita
 * recursivamente de baixo para cima.
 *
 * Antes (nchaves = 2):
 *   filho[0] chave[0] filho[1] chave[1] filho[2]
 *
 * Depois:
 *   filho[2] chave[1] filho[1] chave[0] filho[0]
 * ------------------------------------------------------------------ */
TARVB* espelha(TARVB *a) {
    if (!a) return NULL;

    int i, j;

    /* 1) Espelha todos os filhos primeiro (pos-ordem) */
    for (i = 0; i <= a->nchaves; i++)
        a->filho[i] = espelha(a->filho[i]);

    /* 2) Inverte o vetor de chaves */
    for (i = 0, j = a->nchaves - 1; i < j; i++, j--) {
        int tmp     = a->chave[i];
        a->chave[i] = a->chave[j];
        a->chave[j] = tmp;
    }

    /* 3) Inverte o vetor de filhos (nchaves + 1 ponteiros) */
    for (i = 0, j = a->nchaves; i < j; i++, j--) {
        TARVB *tmp  = a->filho[i];
        a->filho[i] = a->filho[j];
        a->filho[j] = tmp;
    }

    return a;
}

/* ------------------------------------------------------------------
 * QUESTAO 4 – TLSE* arvore_pra_lista(TARVB *a)
 *
 * Percurso in-order CRESCENTE inserindo sempre no INICIO da lista.
 * Como TLSE_insere coloca o novo elemento na frente, percorrer em
 * ordem crescente produz uma lista em ordem DECRESCENTE.
 *
 * In-order de Arvore B (para nchaves = k):
 *   visita filho[0]
 *   visita chave[0]   <- insere no inicio da lista
 *   visita filho[1]
 *   visita chave[1]   <- insere no inicio da lista
 *   ...
 *   visita filho[k]
 * ------------------------------------------------------------------ */
static TLSE* inorder_para_lista(TARVB *a, TLSE *l) {
    if (!a) return l;
    int i;
    for (i = 0; i < a->nchaves; i++) {
        l = inorder_para_lista(a->filho[i], l);
        l = TLSE_insere(l, a->chave[i]);   /* insere no inicio */
    }
    l = inorder_para_lista(a->filho[i], l); /* ultimo filho */
    return l;
}

TLSE* arvore_pra_lista(TARVB *a) {
    return inorder_para_lista(a, NULL);
}

/* --- main de teste para Q3 e Q4 --- */
int main_q34(void) {   /* renomeie para main() ao compilar isolado */
    int t = 2, i;
    int ins[] = {22,50,60,74,100,80,37,12,19,53,63,71,81,98,51};
    int ni    = sizeof(ins) / sizeof(ins[0]);

    TARVB *arv = TARVB_Inicializa();
    for (i = 0; i < ni; i++) arv = TARVB_Insere(arv, ins[i], t);

    printf("=== Q3: Arvore original ===\n");
    TARVB_Imprime2(arv);
    arv = espelha(arv);
    printf("\n=== Q3: Arvore espelhada ===\n");
    TARVB_Imprime2(arv);

    /* Nova arvore para Q4 (a original foi espelhada) */
    TARVB *arv2 = TARVB_Inicializa();
    for (i = 0; i < ni; i++) arv2 = TARVB_Insere(arv2, ins[i], t);
    TLSE *l = arvore_pra_lista(arv2);
    printf("\n=== Q4: Lista decrescente ===\n");
    TLSE_imprime(l);
    printf("\n");

    TLSE_libera(l);
    TARVB_Libera(arv2);
    TARVB_Libera(arv);
    return 0;
}


/* ===================================================================
 * ARQUIVO: gabarito_q5.c
 * Questao 5 – usa TARVBM.h / TARVBM.c
 * =================================================================== */

/* #include "TARVBM.h" */   /* TARVBM, TARVBM_inicializa, TARVBM_insere,
                                TARVBM_imprime, TARVBM_imprime_chaves,
                                TARVBM_libera                          */
#include <string.h>

/* ------------------------------------------------------------------
 * QUESTAO 5 – char* caminho(TARVBM *a, int x)
 *
 * Percorre a Arvore B+ da raiz ate a folha que contem x, registrando
 * em cada nivel o INDICE DO FILHO escolhido no vetor filho[].
 *
 * Regra de navegacao (identica a TARVBM_busca do professor):
 *   i = primeiro indice tal que x <= chave[i], ou i = nchaves
 *   Se achou chave[i] == x num no INTERNO, vai para filho[i+1]
 *     (porque na B+ a chave fica copiada no no da direita)
 *   Caso contrario vai para filho[i]
 *
 * O indice "i" escolhido em cada nivel e concatenado na string
 * separado por '-'.  Ex: "0-2-1"
 * ------------------------------------------------------------------ */
char* caminho(TARVBM *a, int x) {
    char *path   = (char*) malloc(512 * sizeof(char));
    path[0]      = '\0';
    char buf[16];
    TARVBM *atual = a;
    int primeiro  = 1;

    while (atual && !atual->folha) {
        int i = 0;
        while (i < atual->nchaves && x > atual->chave[i]) i++;
        /* Chave exata em no interno: x esta no filho da direita */
        if (i < atual->nchaves && atual->chave[i] == x) i++;

        if (!primeiro) strcat(path, "-");
        sprintf(buf, "%d", i);
        strcat(path, buf);
        primeiro = 0;

        atual = atual->filho[i];
    }
    return path;
}

/* --- main de teste para Q5 --- */
int main_q5(void) {   /* renomeie para main() ao compilar isolado */
    int t = 2, i;
    int ins[] = {15,42,88,7,63,29,91,55,12,34,76,50,5,23,68};
    int ni    = sizeof(ins) / sizeof(ins[0]);

    TARVBM *bm = TARVBM_inicializa();
    for (i = 0; i < ni; i++) bm = TARVBM_insere(bm, ins[i], t);

    printf("=== Q5: Arvore B+ ===\n");
    TARVBM_imprime(bm);
    printf("\nFolhas (esq->dir): ");
    TARVBM_imprime_chaves(bm);

    int busca[] = {5, 23, 63, 91, 68};
    int nb = sizeof(busca)/sizeof(busca[0]);
    for (i = 0; i < nb; i++) {
        char *c = caminho(bm, busca[i]);
        printf("Caminho ate %2d: \"%s\"\n", busca[i], c);
        free(c);
    }
    TARVBM_libera(bm);
    return 0;
}


/* ===================================================================
 * ARQUIVO: gabarito_q678.c
 * Questoes 6, 7, 8 – sem dependencias externas do professor
 * =================================================================== */

/* ------------------------------------------------------------------
 * QUESTAO 6 – int moda(int *vet, int tam_vet, int N)
 *
 * Usa tabela hash de ENDERECAMENTO DIRETO (direct-address table):
 *   funcao hash: h(v) = v   (sem colisao para valores 0..N)
 *   tabela[v] armazena a frequencia de v
 *
 * Complexidade: O(N + tam_vet)
 * ------------------------------------------------------------------ */
int moda(int *vet, int tam_vet, int N) {
    int *tabela = (int*) calloc(N + 1, sizeof(int));

    /* Fase 1 – contagem (equivale a inserir na hash e incrementar) */
    int i;
    for (i = 0; i < tam_vet; i++)
        tabela[vet[i]]++;          /* h(v) = v */

    /* Fase 2 – busca do maximo */
    int moda_val = 0, max_freq = 0;
    for (i = 0; i <= N; i++) {
        if (tabela[i] > max_freq) {
            max_freq = tabela[i];
            moda_val = i;
        }
    }
    free(tabela);
    return moda_val;
}

/* ------------------------------------------------------------------
 * QUESTAO 7 – void soma_k(char *arqA, char *arqB, char *saida, int k)
 *
 * Para cada valor "a" em A e "b" em B, escreve o par (a,b) em saida
 * se:  a%k + b%k == k
 *
 * Estrategia:
 *   1. Le todos os valores de B em memoria.
 *   2. Para cada "a" lido de A:
 *        resto_a = a % k
 *        need_b  = k - resto_a   (resto que "b" precisa ter)
 *      Percorre B procurando b tal que b%k == need_b.
 * ------------------------------------------------------------------ */
void soma_k(char *arqA, char *arqB, char *saida, int k) {
    FILE *fa = fopen(arqA, "r");
    FILE *fb = fopen(arqB, "r");
    FILE *fs = fopen(saida, "w");
    if (!fa || !fb || !fs) exit(1);

    /* Carrega B em vetor dinamico */
    int capB = 1024, tamB = 0, val;
    int *vetB = (int*) malloc(capB * sizeof(int));
    while (fscanf(fb, "%d", &val) == 1) {
        if (tamB == capB) {
            capB *= 2;
            vetB  = (int*) realloc(vetB, capB * sizeof(int));
        }
        vetB[tamB++] = val;
    }
    fclose(fb);

    int a, i;
    while (fscanf(fa, "%d", &a) == 1) {
        int need_b = k - (a % k);
        for (i = 0; i < tamB; i++)
            if (vetB[i] % k == need_b)
                fprintf(fs, "(%d, %d)\n", a, vetB[i]);
    }
    free(vetB);
    fclose(fa);
    fclose(fs);
}

/* ------------------------------------------------------------------
 * QUESTAO 8 – void min_heapify(int *vet, int tam)
 *
 * Constroi um MIN-HEAP in-place usando o algoritmo de Floyd:
 * comeca no ultimo no interno (tam/2 - 1) e desce cada elemento.
 *
 * Propriedade do min-heap: vet[pai] <= vet[filho]
 *   pai(i)   = (i-1)/2
 *   filhoE   = 2i+1
 *   filhoD   = 2i+2
 * ------------------------------------------------------------------ */
static void afunda_min(int *vet, int tam, int i) {
    int menor = i;
    int esq   = 2 * i + 1;
    int dir   = 2 * i + 2;

    if (esq < tam && vet[esq] < vet[menor]) menor = esq;
    if (dir < tam && vet[dir] < vet[menor]) menor = dir;

    if (menor != i) {
        int tmp    = vet[i];
        vet[i]     = vet[menor];
        vet[menor] = tmp;
        afunda_min(vet, tam, menor);  /* desce recursivamente */
    }
}

void min_heapify(int *vet, int tam) {
    int i;
    for (i = tam / 2 - 1; i >= 0; i--)
        afunda_min(vet, tam, i);
}


/* ===================================================================
 * ARQUIVO: gabarito_q9.c
 * Questao 9 – Heap N-ARIA em memoria secundaria
 * =================================================================== */

/*
 * Formato do arquivo binario:
 *   bytes 0..3   : aridade n  (int)
 *   bytes 4..7   : tamanho atual tam (int)
 *   bytes 8..    : elementos (array de int)
 *
 * Relacoes de parentesco (indice base 0, n-ario):
 *   pai(i)             = (i - 1) / n
 *   primeiro filho(i)  = n * i + 1
 *   ultimo  filho(i)   = n * i + n
 *
 * API:
 *   heap_n_cria       (arq, n)     – cria arquivo heap vazio de aridade n
 *   heap_n_insere     (arq, val)   – insere "val" e restaura heap (sobe)
 *   heap_n_extrai_min (arq)        – remove e retorna o minimo (desce)
 *   heap_n_imprime    (arq)        – exibe o conteudo
 */

#define HEAP_HEADER_SZ (2 * sizeof(int))

static void _ler_header(FILE *f, int *n, int *tam) {
    rewind(f);
    fread(n,   sizeof(int), 1, f);
    fread(tam, sizeof(int), 1, f);
}

static void _escrever_header(FILE *f, int n, int tam) {
    rewind(f);
    fwrite(&n,   sizeof(int), 1, f);
    fwrite(&tam, sizeof(int), 1, f);
}

/* Offset em bytes do elemento i no arquivo */
static long _offset(int i) {
    return (long)HEAP_HEADER_SZ + (long)i * sizeof(int);
}

static int _ler_elem(FILE *f, int i) {
    int v;
    fseek(f, _offset(i), SEEK_SET);
    fread(&v, sizeof(int), 1, f);
    return v;
}

static void _escrever_elem(FILE *f, int i, int v) {
    fseek(f, _offset(i), SEEK_SET);
    fwrite(&v, sizeof(int), 1, f);
}

/* Sobe o elemento na posicao "i" ate sua posicao correta */
static void _sobe(FILE *f, int n, int i) {
    while (i > 0) {
        int pai = (i - 1) / n;
        int vi  = _ler_elem(f, i);
        int vp  = _ler_elem(f, pai);
        if (vi < vp) {
            _escrever_elem(f, i,   vp);
            _escrever_elem(f, pai, vi);
            i = pai;
        } else break;
    }
}

/* Desce o elemento na posicao "i" ate sua posicao correta */
static void _desce(FILE *f, int n, int tam, int i) {
    while (1) {
        int menor   = i;
        int v_menor = _ler_elem(f, i);
        int fc      = n * i + 1;   /* primeiro filho */
        int k;
        for (k = 0; k < n && (fc + k) < tam; k++) {
            int vf = _ler_elem(f, fc + k);
            if (vf < v_menor) { v_menor = vf; menor = fc + k; }
        }
        if (menor == i) break;
        int vi = _ler_elem(f, i);
        _escrever_elem(f, i,     v_menor);
        _escrever_elem(f, menor, vi);
        i = menor;
    }
}

void heap_n_cria(const char *arq, int n) {
    FILE *f = fopen(arq, "wb");
    int tam = 0;
    fwrite(&n,   sizeof(int), 1, f);
    fwrite(&tam, sizeof(int), 1, f);
    fclose(f);
}

void heap_n_insere(const char *arq, int val) {
    FILE *f = fopen(arq, "r+b");
    int n, tam;
    _ler_header(f, &n, &tam);
    _escrever_elem(f, tam, val);
    tam++;
    _escrever_header(f, n, tam);
    _sobe(f, n, tam - 1);
    fclose(f);
}

int heap_n_extrai_min(const char *arq) {
    FILE *f = fopen(arq, "r+b");
    int n, tam;
    _ler_header(f, &n, &tam);
    if (tam == 0) { fclose(f); return -1; }
    int minv   = _ler_elem(f, 0);
    int ultimo = _ler_elem(f, tam - 1);
    tam--;
    _escrever_header(f, n, tam);
    if (tam > 0) {
        _escrever_elem(f, 0, ultimo);
        _desce(f, n, tam, 0);
    }
    fclose(f);
    return minv;
}

void heap_n_imprime(const char *arq) {
    FILE *f = fopen(arq, "rb");
    int n, tam, i;
    _ler_header(f, &n, &tam);
    printf("Heap %d-aria (%d elementos): ", n, tam);
    for (i = 0; i < tam; i++)
        printf("%d ", _ler_elem(f, i));
    printf("\n");
    fclose(f);
}

/* --- main de teste para Q9 --- */
int main(void) {   /* renomeie para main() ao compilar isolado */
    int vals[] = {10,3,7,1,5,8,2,9,4,6};
    int i;

    printf("=== Q9: Heap 3-aria ===\n");
    heap_n_cria("/tmp/h3.bin", 3);
    for (i = 0; i < 10; i++) heap_n_insere("/tmp/h3.bin", vals[i]);
    heap_n_imprime("/tmp/h3.bin");
    printf("Extraindo em ordem crescente: ");
    for (i = 0; i < 10; i++) printf("%d ", heap_n_extrai_min("/tmp/h3.bin"));
    printf("\n");

    printf("\n=== Q9: Heap 4-aria ===\n");
    heap_n_cria("/tmp/h4.bin", 4);
    for (i = 0; i < 10; i++) heap_n_insere("/tmp/h4.bin", vals[i]);
    heap_n_imprime("/tmp/h4.bin");
    printf("Extraindo em ordem crescente: ");
    for (i = 0; i < 10; i++) printf("%d ", heap_n_extrai_min("/tmp/h4.bin"));
    printf("\n");

    return 0;
}
