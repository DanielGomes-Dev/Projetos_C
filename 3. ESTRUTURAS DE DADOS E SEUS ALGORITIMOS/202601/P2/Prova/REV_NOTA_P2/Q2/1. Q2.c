#include <limits.h>
#include "TARVB.h"

//int* todos_ind(TARVB *a, int ind, int *tam_vet){}

int main(int argc, char *argv[]){
  TARVB *arvore = TARVB_Inicializa();
  int t;
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num;
  do{
    scanf("%d", &num);
    if(num <= 0) break;
    arvore = TARVB_Insere(arvore, num, t);
  }while(1);

  /*
  if(arvore){
    int ind, tam_vet;
    scanf("%d", &ind);
    int *resp = todos_ind(arvore, ind, &tam_vet);
    if(tam_vet){
      int i;
      for(i = 0; i < tam_vet; i++) printf("resp[%d] = %d\n", i, resp[i]);
      free(resp);
    }
  }
  */
  TARVB_Libera(arvore);
  return 0;
}
