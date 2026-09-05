#include <limits.h>
#include "TARVB.h"

//char* codif (TARVB* a, int k);

int main(int argc, char *argv[]){
  TARVB *arvore = TARVB_Inicializa();
  int t;
  do{
    printf("t = ");
    scanf("%d", &t);
  }while((t < 2) || (t > 4));

  int num;
  do{
    scanf("%d", &num);
    if(num <= 0) break;
    arvore = TARVB_Insere(arvore, num, t);
  }while(1);
  TARVB_Imprime(arvore);
  
  if(arvore){
    char repete;
    do{
      scanf("%d", &num);
      /*
      char *resp = codif (arvore, num);
      printf("%s\n", resp);
      free(resp);
      */
      printf("Quer continuar? ");
      scanf(" %c", &repete);
    }while((repete != 'N') && (repete != 'n'));
  }
  TARVB_Libera(arvore);
  return 0;
}
