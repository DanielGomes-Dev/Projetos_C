#include "TH.h"

typedef struct par{
  int num1, num2;
}TPAR;

void misc(char *arq_entrada1, char *arq_entrada2, char *saida, int k){
  //Complete...
}
  
int main(void){
  int ant, num;
  char nome_dados1[31];
  printf("Digite o nome do primeiro arquivo de dados... ");
  scanf("%s", nome_dados1);

/*
  //ARQS. BINÁRIOS
  FILE *fp = fopen(nome_dados1, "wb");
  if(!fp) exit(1);  
  printf("Digite um numero... Pare quando o numero for menor ou igual ao anterior...\n");
  do{
    scanf("%d", &ant);
    if(ant >= 0){
      fwrite(&ant, sizeof(int), 1, fp);
      break;
    }
  }while(1);
  do{
    scanf("%d", &num);
    if(num <= ant) break;
    fwrite(&num, sizeof(int), 1, fp);
    ant = num;
  }while(1);
  fclose(fp);

  char nome_dados2[31];
  printf("Digite o nome do segundo arquivo de dados... ");
  scanf("%s", nome_dados2);
  fp = fopen(nome_dados2, "wb");
  if(!fp) exit(1);
  printf("Digite um numero... Pare quando o numero for menor ou igual ao anterior...\n");
  do{
    scanf("%d", &ant);
    if(ant >= 0){
      fwrite(&ant, sizeof(int), 1, fp);
      break;
    }
  }while(1);
  do{
    scanf("%d", &num);
    if(num <= ant) break;
    fwrite(&num, sizeof(int), 1, fp);
    ant = num;
  }while(1);
  fclose(fp);
  */
  
  //ARQS. TEXTO
  FILE *fp = fopen(nome_dados1, "w");
  if(!fp) exit(1);  
  printf("Digite um numero... Pare quando o numero for menor ou igual ao anterior...\n");
  do{
    scanf("%d", &ant);
    if(ant >= 0){
      fprintf(fp, "%d\n", ant);
      break;
    }
  }while(1);
  do{
    scanf("%d", &num);
    if(num <= ant) break;
      fprintf(fp, "%d\n", num);
    ant = num;
  }while(1);
  fclose(fp);

  char nome_dados2[31];
  printf("Digite o nome do segundo arquivo de dados... ");
  scanf("%s", nome_dados2);
  fp = fopen(nome_dados2, "wb");
  if(!fp) exit(1);
  printf("Digite um numero... Pare quando o numero for menor ou igual ao anterior...\n");
  do{
    scanf("%d", &ant);
    if(ant >= 0){
      fprintf(fp, "%d\n", ant);
      break;
    }
  }while(1);
  do{
    scanf("%d", &num);
    if(num <= ant) break;
    fprintf(fp, "%d\n", num);
    ant = num;
  }while(1);
  fclose(fp);

  int k;
  printf("Digite o valor de k... ");
  scanf("%d", &k);  
  
  char nome_saida[31];
  printf("Digite o nome do arquivo de dados de saida... ");  
  scanf("%s", nome_saida);
  misc(nome_dados1, nome_dados2, nome_saida, k);  
  
  /*
  //ARQ. BINÁRIO
  fp = fopen(nome_saida, "rb");
  if(!fp) exit(1);  
  int r;
  do{
    TPAR p;
    r = fread(&p, sizeof(TPAR), 1, fp);
    if(r != 1) break;
    printf("(%d,%d)\n", p.num1, p.num2);
  }while(1);
  fclose(fp);
  */

  //ARQ. TEXTO
  fp = fopen(nome_saida, "r");
  if(!fp) exit(1);  
  int r;
  do{
    TPAR p;
    r = fscanf(fp,"%d%d", &p.num1, &p.num2);
    if(r != 2) break;
    printf("(%d,%d)\n", p.num1, p.num2);
  }while(1);
  fclose(fp);

  return 0;
}
