#include "TAV.h"
#include "TAB.h"

//TAB* av2ab(TAV *a, int *n);

int main(void){
  int no, pai;
  printf("Digite a raiz da arvore... ");
  scanf("%d", &no);
  TAV *a = TAV_cria(no);
  char repete;
  do{
    printf("Quer continuar inserindo nos na árvore (digite N ou n para parar)? ");
    scanf(" %c", &repete);
    if((repete == 'N') || (repete == 'n')) break;
    printf("Digite o pai (que deve existir) e o filho a ser inserido na arvore... ");
    scanf("%d%d", &pai, &no);
    TAV_insere(a, pai, no);
  }while(1);
  TAV_imprime(a);
  printf("\n");
  int n;
  TAB *resp = NULL;
  //resp = av2ab(a, &n);
  printf("%d\n", n);
  if(n <= 2){
    TAB_imprime(resp);
    TAB_libera(resp);
  }
  TAV_libera(a);
  return 0;
}
