#include <stdio.h>
#include <stdlib.h>

typedef struct lseg{
  int no1, no2;
  struct lseg *prox;
} TLSEG;

TLSEG* TLSEG_insere(TLSEG *l, int no1, int no2);
void TLSEG_imprime(TLSEG *l);
void TLSEG_libera(TLSEG *l);
TLSEG* TLSEG_busca(TLSEG *l, int no1, int no2);

