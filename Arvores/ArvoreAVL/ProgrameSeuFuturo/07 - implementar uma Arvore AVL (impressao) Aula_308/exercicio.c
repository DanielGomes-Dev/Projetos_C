#include <stdio.h> // NULL
#include <stdlib.h> //malloc


typedef struct no {
    int valor;
    struct no *esquerdo, *direito;
    short altura;
}No;


No* novoNo(int valor){
    No *novo = malloc(sizeof(No));

    if(novo){
        novo->valor = valor;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;

    }
    else {
        printf("\nErro ao criar novo no.");
    }

    return novo;
}

short maior (short a, short b){
    return (a > b) ? a : b;
}

short alturaNo(No *no){
    if(no == NULL) return -1;
    else return no->altura;
}

// funcoes para rotação a esquerda;
No* rotacaoEsquerda(No *r){
    No *y, *f; // Variaveis aux

    y = r->direito;
    f = y->esquerdo; // rotação a esquerda devemos salvar o filho a esquerda do filho que se tornara a raiz;

    // Fazendo a rotacao

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaNo(r->esquerdo), alturaNo(r->direito) + 1);
    y->altura = maior(alturaNo(y->esquerdo), alturaNo(y->direito) + 1);

    return y;

}

// funcoes para rotação a esquerda;
No* rotacaoDireita(No *r){
    No *y, *f; // Variaveis aux

    y = r->esquerdo;
    f = y->direito; // rotação a direita devemos salvar o filho a direita do filho que se tornara a raiz;

    // Fazendo a rotacao

    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(alturaNo(r->esquerdo), alturaNo(r->direito) + 1);
    y->altura = maior(alturaNo(y->esquerdo), alturaNo(y->direito) + 1);

    return y;
}

No* rotacaoDireitaEsquerda(No *r){
    r->direito = rotacaoDireita(r->direito); // rotaciona o no filho a direita da subarvore desbalanceada para direita
    return rotacaoEsquerda(r); // rotaciona a subarvore desbalanceada para esquerda
}

No* rotacaoEsquerdaDireita(No *r){
    r->direito = rotacaoEsquerda(r->esquerdo); // rotaciona o no filho a esquerda da subarvore desbalanceada para esquerda
    return rotacaoDireita(r); // rotaciona a subarvore desbalanceada para direita
}

short fatorDeBalanceamento(No *no){
    if(no){
        return alturaNo(no->esquerdo) - alturaNo(no->direito); 
    }
    else {
        return 0;
    }
}

No* balancear(No *raiz){
    short fb = fatorDeBalanceamento(raiz);


    // Pesando Direita
    if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0) raiz = rotacaoEsquerda(raiz);
    // Pesando Esquerda  
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0) raiz = rotacaoDireita(raiz);
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) > 0) raiz = rotacaoEsquerdaDireita(raiz);
    else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0) raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}


No* inserir(No *raiz, int valor){
    if(raiz == NULL) return novoNo(valor);
    else {
        if(valor < raiz->valor) raiz->esquerdo = inserir(raiz->esquerdo, valor);
        else if(valor > raiz->valor) raiz->direito = inserir(raiz->direito, valor);
        else printf("\nInsercao nao realizada!\nO elemento %d ja existe!\n", valor);
    }
    raiz->altura = maior(alturaNo(raiz->esquerdo), alturaNo(raiz->direito)) + 1;
    raiz = balancear(raiz);
    return raiz;
}

No* remover(No *raiz, int chave) {
    if(raiz == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { // procura o nó a remover
        if(raiz->valor == chave) {
            // remove nós folhas (nós sem filhos)
            if(raiz->esquerdo == NULL && raiz->direito == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            }
            else{
                // remover nós que possuem 2 filhos
                if(raiz->esquerdo != NULL && raiz->direito != NULL){
                    No *aux = raiz->esquerdo;
                    while(aux->direito != NULL)
                        aux = aux->direito;
                    raiz->valor = aux->valor;
                    aux->valor = chave;
                    printf("Elemento trocado: %d !\n", chave);
                    raiz->esquerdo = remover(raiz->esquerdo, chave);
                    return raiz;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    No *aux;
                    if(raiz->esquerdo != NULL)
                        aux = raiz->esquerdo;
                    else
                        aux = raiz->direito;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->valor)
                raiz->esquerdo = remover(raiz->esquerdo, chave);
            else
                raiz->direito = remover(raiz->direito, chave);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(alturaNo(raiz->esquerdo), alturaNo(raiz->direito)) + 1;
        raiz = balancear(raiz);
        return raiz;
    }
}

void imprimir(No *raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");
        for (i=0; i<nivel; i++){
            printf("\t");
        }

        printf("%d", raiz->valor);
        imprimir(raiz->esquerdo, nivel + 1);
    }
}

int main(){

    int opcao, valor;
    No *raiz = NULL;

    do{
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
        scanf("%d", &opcao);

        switch(opcao){
        case 0:
            printf("Saindo!!!");
            break;
        case 1:
            printf("\tDigite o valor a ser inserido: ");
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
            break;
        case 2:
            printf("\tDigite o valor a ser removido: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        case 3:
            imprimir(raiz, 1);
            break;
        default:
            printf("\nOcao invalida!!!\n");
        }

    }while(opcao != 0);

    return 0;
}