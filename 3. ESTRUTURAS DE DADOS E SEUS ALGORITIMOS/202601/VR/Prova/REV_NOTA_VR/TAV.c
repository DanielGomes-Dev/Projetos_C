#include "TAV.h"

TAV* TAV_cria (int raiz){
  TAV *novo = (TAV *) malloc(sizeof(TAV));
  novo->info = raiz;
  novo->prim_filho = novo->prox_irmao = NULL;
  return novo;
}

TAV* TAV_busca (TAV *a, int info){
  if((!a) || (a->info == info)) return a;
  TAV *p;
  for(p = a->prim_filho; p; p = p->prox_irmao){
    TAV *resp = TAV_busca(p, info); 
    if(resp) return resp;
  }
  return NULL;
}

void TAV_insere (TAV* a, int pai, int info){
  TAV *meu_pai = TAV_busca(a, pai);
  if(!meu_pai) return;
  TAV *novo = TAV_cria(info);
  novo->prox_irmao = meu_pai->prim_filho;
  meu_pai->prim_filho = novo; 
}

void TAV_imprime (TAV *a){
  if(a){
    printf("%d ", a->info);
    TAV *p;
    for(p = a->prim_filho; p; p = p->prox_irmao) TAV_imprime(p);
  }
}

void TAV_libera (TAV *a){
  if(a){
    TAV *p = a->prim_filho, *temp;
    while(p){
      temp = p->prox_irmao;
      TAV_libera(p);
      p = temp;
    }
    free(a);
  }
}
