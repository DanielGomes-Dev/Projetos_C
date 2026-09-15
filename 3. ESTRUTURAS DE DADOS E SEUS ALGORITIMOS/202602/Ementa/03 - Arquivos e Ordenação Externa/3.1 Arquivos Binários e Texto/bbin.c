#include <stdio.h>
#include <stdlib.h>

int bb_aux(FILE *fp, int ini, int fim, int x){
  int meio, elem;
  while(ini <= fim){
    meio = (((ini + fim) / sizeof(int)) / 2) * sizeof(int);
    fseek(fp, meio, SEEK_SET);
    fread(&elem, sizeof(int), 1, fp);
    if(elem == x) return meio;
    if(elem < x) ini = meio + sizeof(int);
    else fim = meio - sizeof(int);
  }
  return -1;
}

int bb_arq(char *arq, int x){
  FILE *fp = fopen(arq, "rb");
  if(!fp) exit(1);
  int resp, fim, ini = 0;
  fseek(fp, 0L, SEEK_END);
  fim = ftell(fp) - sizeof(int);
  resp = bb_aux(fp, ini, fim, x);
  fclose(fp);
  return resp;
}

int main(void){
  int n = 5, i, num, ant;
  int *vet = (int *)malloc(sizeof(int) * n);
  printf("Digite elementos em ordem crescente... ");
  scanf("%d", &ant);
  vet[0] = ant;
  i = 1;
  while(i < n){
    scanf("%d", &num);
    if(num < ant) continue;
    ant = vet[i++] = num;
    if(i == n){
      char resp;
      printf("Quer aumentar o tamanho do seu vetor? ");
      scanf(" %c", &resp);
      if((resp != 'N') && (resp != 'n')){
        n *= 2;
        vet = (int *) realloc(vet, sizeof(int) * n);
      } 
    }
  }
  
  FILE *fp = fopen("ord.txt", "wb");
  if(!fp) exit(1);
  fwrite(vet, sizeof(int), n, fp);
  fclose(fp);
  
  fp = fopen("ord.txt", "rb");
  if(!fp) exit(1);
  int outro[n];
  fread(outro, sizeof(int), n, fp);
  fclose(fp);
  
  for(i = 0; i < n; i++)
    printf("vet[%d] = %d\toutro[%d] = %d\n", i, vet[i], i, outro[i]);

  printf("Digite um numero... ");
  scanf("%d", &num);
  printf("%d\n", bb_arq("ord.txt", num));

  free(vet);
  return 0;
}

