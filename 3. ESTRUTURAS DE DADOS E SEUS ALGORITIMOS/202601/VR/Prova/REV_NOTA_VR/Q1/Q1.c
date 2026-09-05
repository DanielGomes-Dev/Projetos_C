#include "TG.h"
#include "TLSE.h"
#include "TLSEG.h"

//TLSEG* Ponte (TG* g);

int main(void){
  TG *g = TG_inicializa();
  printf("Digite os nos do grafo (pare quando um numero menor ou igual a zero for fornecido)...\n");
  int no1, no2;
  while(1){
    scanf("%d", &no1);
    if(no1 <= 0) break;
    g = TG_ins_no(g, no1);    
  }
 
  printf("Digite as arestas (pare quando um dos nos nao pertencer ao grafo)...\n");
  while(1){
    scanf("%d%d", &no1, &no2);
    if(!TG_busca_no(g, no1) || !TG_busca_no(g, no2)) break;
    TG_ins_aresta(g, no1, no2);
  }
  TG_imprime(g);
   
  //RETIRAR OS COMENTARIOS ABAIXO PARA TESTAR:
  /*
  TLSEG *l = Ponte(g);
  printf("Pontes:\n");   
  TLSEG_imprime(l);
  TLSEG_libera(l)
  */

  TG_libera(g);
  return 0;
}

