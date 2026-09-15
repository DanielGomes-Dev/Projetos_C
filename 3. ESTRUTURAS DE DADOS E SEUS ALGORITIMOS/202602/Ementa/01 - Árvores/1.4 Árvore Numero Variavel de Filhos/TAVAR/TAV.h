#include <stdio.h>
#include <stdlib.h>

typedef struct arv_var{
  int info;
  struct arv_var *prim_filho, *prox_irmao;
}TAV;

TAV* TAV_cria (int elem);
TAV* TAV_busca (TAV *a, int info);
void TAV_insere (TAV* a, int pai, int info);
void TAV_imprime (TAV *a);
void TAV_libera (TAV *a);
