#include <stdio.h>
#include <stdlib.h>

//int fseek(FILE *stream, long int offset, int source);
//long int ftell(FILE *stream);
//void rewind(FILE *stream);

/*
void ss(int *vet, int n){
  int i;
  for(i = 0; i < n; i++){
    int j, menor = i;
    for(j = i + 1; j < n; j++)
      if(vet[j] < vet[menor]) menor = j;
    if(menor != i){
      int temp = vet[i];
      vet[i] = vet[menor];
      vet[menor] = temp;
    }
  }
}
*/
void selSortBin(FILE *fp){
  int i, j, r, s, elem_menor, menor, elem, aux;

  i = ftell(fp);
  r = fread(&elem_menor, sizeof(int), 1, fp);
  while(r == 1){
    menor = i;
    aux = elem_menor;
    j = ftell(fp);
    s = fread(&elem, sizeof(int), 1, fp);
    while(s == 1){
      if(elem < elem_menor){
        menor = j;
        elem_menor = elem;
      }
      j = ftell(fp);
      s = fread(&elem, sizeof(int), 1, fp); 
    }
    if(menor != i){
      printf("Trocar %d(%d) por %d(%d)\n", aux, i, elem_menor, menor);
      fseek(fp, menor, SEEK_SET);
      fwrite(&aux, sizeof(int), 1, fp);
      fseek(fp, i, SEEK_SET);
      fwrite(&elem_menor, sizeof(int), 1, fp);
    }
    else
      fseek(fp, (i + sizeof(int)), SEEK_SET);

    i = ftell(fp);
    r = fread(&elem_menor, sizeof(int), 1, fp);
  } 
}

int main(int argc, char** argv){
  if(argc != 2){
    printf("ERRO: <executavel> <nome_arq_bin>\n");
    exit(1);  
  }
  int n;
  printf("Digite o tamanho VALIDO do vetor... ");
  do{
    scanf("%d", &n);
  }while(n <= 0);
  int i, vet[n];
  printf("Digite os n elementos do vetor... \n");
  scanf("%d", &vet[0]);
  i = 1;
  while (i < n){
    int j, aux;
    scanf("%d", &aux);
    //for(j = 0; j < i; j++) if (vet[j] == aux) break;
    //if(j == i) vet[i++] = aux;
    vet[i++] = aux;
  }

  //char nome[31];
  //printf("Digite o nome do arquivo binario... ");
  //scanf("%s", nome);
  //FILE *fp = fopen(nome, "wb");  

  FILE *fp = fopen(argv[1], "wb");
  if(!fp) exit(1);
  fwrite(vet, sizeof(int), n, fp);
  fclose(fp);

  for(i = 0; i < n; i++) printf("%d ", vet[i]);
  printf("\n");

  //fp = fopen(nome, "rb+");
  fp = fopen(argv[1], "rb+");
  if(!fp) exit(1);
  selSortBin(fp);
  fclose(fp);

  int resp[n];
  //fp = fopen(nome, "rb+");
  fp = fopen(argv[1], "rb+");
  if(!fp) exit(1);
  fread(resp, sizeof(int), n, fp);
  fclose(fp);

  for(i = 0; i < n; i++) printf("vet[%d] = %d -> resp[%d] = %d\n", i, vet[i], i, resp[i]);
  return 0;    
}
