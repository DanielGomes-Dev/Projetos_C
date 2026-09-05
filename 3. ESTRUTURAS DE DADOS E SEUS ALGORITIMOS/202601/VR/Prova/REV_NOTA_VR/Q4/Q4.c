#include "TH.h"
#include <string.h>

void misc(char **arqs, int n, int porc, char *saida){
}

int main(int argc, char **argv){
  if(argc == 1) printf("ERRO: <./nome_exec> <arq_saida> <porcentagem> <lista arquivos a serem pesquisados>\n");
  else{
    int n = argc - 3, i;
    char **arq = (char **)malloc(sizeof(char *) * n);
    for(i = 0; i < n; i++){
      arq[i] = (char *) malloc(sizeof(char) * 31);
      strcpy(arq[i], argv[i + 3]);
    }
    for(i = 0; i < n; i++) printf("arq[%d] = %s\n", i, arq[i]);
    misc(arq, n, atoi(argv[2]), argv[1]);
    
    /*
    FILE *fp = fopen(argv[1], "r");
    if(!fp) exit(1);
    int r, num;
    while(1){
      r = fscanf(fp, "%d", &num);
      if(r != 1){
        fclose(fp);
        break;
      }
      printf("%d ", num);
    }
    printf("\n");
    */
    
    for(i = 0; i < n; i++) free(arq[i]);
    free(arq);
  }  
  return 0;
}

