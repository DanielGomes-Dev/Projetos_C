#include "TLSEG.h"

TLSEG* TLSEG_insere(TLSEG *l, int no1, int no2){
  TLSEG *novo = (TLSEG *) malloc(sizeof(TLSEG));
  novo->prox = l;
  novo->no1 = no1;
  novo->no2 = no2;
  return novo;
}

void TLSEG_imprime(TLSEG *l){
  TLSEG *p = l;
  while(p){
    printf("%d - %d\n", p->no1, p->no2);
    p = p->prox;
  } 
}

void TLSEG_libera(TLSEG *l){
  TLSEG *p = l, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  } 
}

TLSEG* TLSEG_busca(TLSEG *l, int no1, int no2){
  TLSEG *p = l;
  while(p){
    if((p->no1 == no1) && (p->no2 == no2)) return p;
    if((p->no1 == no2) && (p->no2 == no1)) return p;
    p = p->prox;
  } 
  return NULL;
}
