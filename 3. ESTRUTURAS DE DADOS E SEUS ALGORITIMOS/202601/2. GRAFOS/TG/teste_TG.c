#include "TG.h"

int main(void){
  TG *g = TG_inicializa();
  int n;
  printf("Digite nos do grafo... Pare quando o no for menor ou igual a zero...\n");
  do{
    scanf("%d", &n);
    if(n <= 0) break;
    g = TG_ins_no(g, n);
  }while(1);
  TG_imp_rec(g);
  
  int m;
  printf("Digite arestas do grafo... Pare quando os nos forem menores ou iguais a zero...\n");
  do{
    scanf("%d%d", &n, &m);
    if((n <= 0) || (m <= 0)) break;
    TG_ins_aresta(g, n, m);
  }while(1);
  TG_imp_rec(g);
  
  char op;
  printf("Digite n ou a para retirar nos ou arestas...\n");
  do{
    scanf(" %c", &op);
    if(op == 'n'){
      printf("Digite o no do grafo... ");
      scanf("%d", &n);
      g = TG_retira_no(g, n);
      TG_imprime(g);
    }
    else if(op == 'a'){
      printf("Digite os nos do grafo... ");
      scanf("%d%d", &n, &m);
      TG_retira_aresta(g, n, m);
      TG_imprime(g);
    }
    else break;
  }while(1);
  TG_libera(g);
  return 0;
}

