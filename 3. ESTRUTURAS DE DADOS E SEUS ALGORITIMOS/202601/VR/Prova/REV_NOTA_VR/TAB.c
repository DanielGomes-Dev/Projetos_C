#include "TAB.h"

void TAB_libera(TAB* t){
  if(t){
    TAB_libera(t->esq);
    TAB_libera(t->dir);
    free(t);
  }
}

TAB* TAB_busca(int e, TAB* t){
  if((!t) || (t->info == e)) return t;
  TAB *resp = TAB_busca(e, t->esq);
  if(resp) return resp;
  return TAB_busca(e, t->dir);
}

void imprime_aux(TAB* a, int andar){
  if(a){
    int j;
    imprime_aux(a->esq, andar + 1);
    for(j = 0; j <= andar; j++) printf("   ");
    printf("%d\n", a->info);
    imprime_aux(a->dir, andar + 1);
  }
}

void TAB_imprime(TAB* a){
  imprime_aux(a, 1);
}

TAB* TAB_cria(int x, TAB* e, TAB* d){
  TAB* a = (TAB*) malloc(sizeof(TAB));
  a->info = x;
  a->esq = e;
  a->dir = d;
  return a;
}
