#include "TLSE.h"

int main(void){
  TLSE *l = TLSE_inicializa();
  int x;
  do{
    scanf("%d", &x);
    if(x < 0) break;
    if(x % 2) l = TLSE_insere(l, x);
    else TLSE_insere_void(&l, x);
  }while(1);
  TLSE_imprime(l);
  printf("\n");

  return 0;
}
