

#include <stdio.h>
#include <stdlib.h>

/*

Dada a seguinte representação de uma árvore binária de busca (ABB):

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TABB;

Escreva as seguintes funções:

(Q4) uma função em C que, dada uma árvore binária de busca qualquer, retorne, num vetor, todos
os elementos menores que N. A função deve ter o seguinte protótipo: int* mN(TABB*a, int
N);

*/


typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TABB;

TABB* Cria (int info, TABB *sae, TABB *sad){

    TABB *novo =  (TABB *)malloc(sizeof(TABB));
    
    novo->info = info;
    novo->esq = sae;
    novo->dir = sad;

    return novo;
}

// Função auxiliar baseada no seu material para inserir respeitando a ordem de busca
TABB *insere_ABB(TABB *a, int info) {
    if (!a) return Cria(info, NULL, NULL);
    if (info < a->info)
        a->esq = insere_ABB(a->esq, info);
    else if (info > a->info)
        a->dir = insere_ABB(a->dir, info);
    return a;
}

// Função que percorre a árvore original e insere os elementos na nova árvore
void percorre_e_insere(TABB *original, TABB **nova_raiz) {
    if (original) {
        // Insere o valor do nó atual na nova ABB
        *nova_raiz = insere_ABB(*nova_raiz, original->info);
        
        // Continua o percurso para os filhos
        percorre_e_insere(original->esq, nova_raiz);
        percorre_e_insere(original->dir, nova_raiz);
    }
}

// Função principal de reorganização
TABB* reorganiza_para_ABB(TABB *a) {
    TABB *nova_raiz = NULL;
    percorre_e_insere(a, &nova_raiz);
    return nova_raiz;
}

int conta_menores(TABB *a, int N) {
    if (!a) return 0;
    
    // Se o valor atual é menor que N, contamos ele e buscamos nos dois lados
    if (a->info < N) {
        return 1 + conta_menores(a->esq, N) + conta_menores(a->dir, N);
    } 
    // Se o valor atual é >= N, apenas o lado esquerdo pode ter valores menores que N
    else {
        return conta_menores(a->esq, N);
    }
}

// Função auxiliar para preencher o vetor usando percurso simétrico (in-order)
// para que o vetor resultante já saia ordenado
void preenche(TABB *a, int N, int *vet, int *pos) {
    if (!a) return;
    
    // Visita subárvore esquerda
    preenche(a->esq, N, vet, pos);
    
    // Visita a raiz (se for menor que N, adiciona ao vetor)
    if (a->info < N) {
        vet[*pos] = a->info;
        (*pos)++;
        // Só visita a direita se houver chance de ter menores que N
        preenche(a->dir, N, vet, pos);
    }
}

// Função principal solicitada (Q4)
int* mN(TABB *a, int N) {
    // 1. Descobre o tamanho necessário
    int n_elementos = conta_menores(a, N);
    
    if (n_elementos == 0) return NULL;
    
    // 2. Aloca o vetor dinamicamente
    int *vetor = (int *)malloc(n_elementos * sizeof(int));
    if (!vetor) return NULL;
    
    // 3. Preenche o vetor
    int posicao = 0;
    preenche(a, N, vetor, &posicao);
    
    return vetor;
}

void ImpPre(TABB *a){
    if(a){
        printf("%d ",a->info);
        ImpPre(a->esq);
        ImpPre(a->dir);
    }
}

void ImpSim(TABB *a){
    if(a){
        ImpSim(a->esq);
        printf("%d ",a->info);
        ImpSim(a->dir);
    }
}

void ImpPos(TABB *a){
    if(a){
        ImpPos(a->esq);
        ImpPos(a->dir);
        printf("%d ",a->info);
    }
}

int main (){
    TABB *a8 = Cria(8, NULL, NULL);
    TABB *a7 = Cria(7, NULL, NULL);
    TABB *a6 = Cria(6, a7, a8);
    TABB *a5 = Cria(5, NULL, NULL);
    TABB *a4 = Cria(40, NULL, NULL);
    TABB *a3 = Cria(-3, a4, a5);
    TABB *a2 = Cria(2, a3, a6);
    TABB *a1 = Cria(1, a2, a3);
    TABB *raiz = Cria(0, a1, NULL);

    TABB *raiz2 = reorganiza_para_ABB(raiz);
    int n = 5;
    int *vetor_menor_n = mN(raiz2, n);
    int total = conta_menores(raiz2, n);

    
   // Testando a Original
    printf("Original (Pre-ordem): ");
    ImpPre(raiz);
    printf("\nReorg (Pre-ordem): ");
    ImpPre(raiz2);
    printf("\n\n------------------------------\n\n");
    printf("\nVetor menor que N (%d) : \n", n);
    if (vetor_menor_n) {
        printf("Elementos menores que %d encontrados: %d\n", n, total);
        printf("Vetor: ");
        for (int i = 0; i < total; i++) {
            printf("%d ", vetor_menor_n[i]);
        }
        // Sempre libere a memória alocada por malloc
        free(vetor_menor_n);
    } else {
        printf("Nenhum elemento menor que %d foi encontrado.", n);
    }
    

    // Testando a Copiada

    return 0;
}