#include <stdio.h>
#include <stdlib.h> // Necessário para o malloc

typedef struct arvbin {
    int info;
    struct arvbin *esq;
    struct arvbin *dir;
} TAB;

// Retorna um ponteiro vazio (pé no chão para começar)
TAB* inicializa(void) {
    return NULL;
}




TAB* cria(int r, TAB *sae, TAB *sad) {
    // Cria um nó "pai" e já pendura dois "filhos" nele
    TAB *novo = (TAB *)malloc(sizeof(TAB)); 
    if (novo == NULL) return NULL; // Boa prática: checar se a memória acabou
    

    // Esta função utiliza um caminhamento Pré-ordem (Raiz, Esquerda, Direita).
    /*
    
    O caminhamento pré-ordem, também conhecido como percurso em profundidade, visita primeiro o nó **raiz**, em seguida, percorre recursivamente a **subárvore esquerda** e, por fim, percorre recursivamente a **subárvore direita**. Essa ordem é útil quando você deseja processar o nó pai antes de seus filhos, como na cópia de uma árvore ou na geração de um código prefixo para uma expressão.
    
    */
    novo->info = r;
    novo->esq = sae;
    novo->dir = sad;
    return novo;
}



TAB* copia(TAB *a){
    if(a==NULL){
        // 1. Caso Base: Se a árvore original for vazia, a cópia também é.
        return NULL;
    }

    // 2. Aloca memória para o novo nó que será a "raiz" da cópia atual
    // (TAB *) diz ao compilador para tratar o ponteiro genérico retornado por malloc como um ponteiro para TAB.
    TAB *novo = (TAB *)malloc(sizeof(TAB));
    novo->info = a->info;
    novo->esq = copia(a->esq);
    novo->dir = copia(a->dir);

    return novo;

}

TAB* espelho(TAB *a) {
    // 1. Caso Base: Se a árvore original for nula, o espelho dela também é.
    if (a == NULL) {
        return NULL;
    }

    // 2. Aloca memória para o novo nó do espelho
    TAB *novo = (TAB *)malloc(sizeof(TAB));
    if (novo == NULL) return NULL; // Segurança

    // 3. Copia a informação original
    novo->info = a->info;

    // 4. A MÁGICA DO ESPELHO:
    // O braço ESQUERDO do novo nó recebe o espelho da DIREITA da original.
    novo->esq = espelho(a->dir);

    // O braço DIREITO do novo nó recebe o espelho da ESQUERDA da original.
    novo->dir = espelho(a->esq);

    // 5. Retorna o nó espelhado
    return novo;
}

TAB* maior(TAB *a) {
    // 1. Se a árvore está vazia, não há maior
    if (a == NULL) return NULL;

    // 2. Começamos assumindo que a raiz atual é o maior nó
    TAB *max = a;

    // 3. Procuramos os "campeões" das subárvores
    TAB *maior_esq = maior(a->esq);
    TAB *maior_dir = maior(a->dir);

    // 4. Comparamos com o campeão da esquerda
    if (maior_esq != NULL && maior_esq->info > max->info) {
        max = maior_esq;
    }

    // 5. Comparamos com o campeão da direita
    if (maior_dir != NULL && maior_dir->info > max->info) {
        max = maior_dir;
    }

    // 6. Retornamos o ponteiro do nó que venceu a disputa
    return max;
}

TAB* menor(TAB *a) {
    if(a == NULL) return NULL;
    TAB *min = a;

    TAB *menor_esq = menor(a->esq);
    TAB *menor_dir = menor(a->dir);

    if(menor_esq != NULL && min->info > menor_esq->info){
        min = menor_esq;
    }

    if(menor_dir != NULL && min->info > menor_dir->info){
        min = menor_dir;
    }

    return min;

}

int igual (TAB* a1, TAB* a2) {
    // 1. Caso Base: Ambas são nulas? (Chegamos ao fim de um ramo juntas)
    if (a1 == NULL && a2 == NULL) {
        return 1;
    }

    // 2. Caso Base: Uma é nula e a outra não? (Estruturas diferentes)
    if (a1 == NULL || a2 == NULL) {
        return 0;
    }

    // 3. Verificação de Conteúdo: Os valores nos nós atuais são diferentes?
    if (a1->info != a2->info) {
        return 0;
    }

    // 4. Recursão: A árvore só é igual se a esquerda E a direita também forem.
    // Usamos o operador '&&' (E lógico)
    return igual(a1->esq, a2->esq) && igual(a1->dir, a2->dir);
}


/*

(Q6) uma função em C que, dada uma árvore binária qualquer, retire todos os elementos pares da árvore original. A função deve ter o seguinte protótipo: TAB* retira_pares (TAB* arv);

(Q7) se esta estrutura TAB tivesse um campo cor (int cor), defina uma função em C que, ao
receber uma árvore binária “sem cor” e totalmente balanceada (isto é, a distância da raiz a qualquer folha da árvore é sempre a mesma), retorne esta árvore com os nós coloridos somente de vermelho e preto, sendo que o nó pai NUNCA pode ter a mesma cor de seus filhos. A função deve possuir o eguinte protótipo: void colore (TAB* arv);

(Q8) descubra a quantidade de nós internos: int ni(TAB *a);

(Q9) ache a quantidade de nós folha: int nf(TAB *a);

*/

int main() {
    printf("Criando uma arvore binaria...\n");

    // Passo 1: Inicializar ponteiros vazios para as folhas
    TAB *folha_esq = inicializa(); // NULL
    TAB *folha_dir = inicializa(); // NULL

    // Passo 2: Criar um nó que aponta para esses NULLs
    // Esse será o nosso nó com o valor 2
    TAB *no_dois = cria(2, folha_esq, folha_dir);
    TAB *no_treis = cria(3, inicializa(), folha_dir);


    // Passo 3: Criar a raiz da árvore (valor 1) 
    // que tem o 'no_dois' como filho da esquerda
    TAB *raiz = cria(1, no_dois, no_treis);

    // Teste de impressão
    printf("Raiz: %d\n", raiz->info);
    printf("Filho Esquerdo da Raiz: %d\n", raiz->esq->info);
    printf("Filho Direito da Raiz: %d\n", raiz->dir->info);
    printf("---\n");



    // Copiando
    TAB *raiz_copia = copia(raiz);

    // Teste de impressão
    printf("Raiz Copia: %d\n", raiz_copia->info);
    printf("Filho Esquerdo da Raiz Copia: %d\n", raiz_copia->esq->info);
    printf("Filho Direito da Raiz Copia: %d\n", raiz_copia->dir->info);
    printf("---\n");



    //Espelho
    TAB *raiz_espelho = espelho(raiz);

    // Teste de impressão
    printf("Raiz Copia: %d\n", raiz_espelho->info);
    printf("Filho Esquerdo da Raiz Espelho: %d\n", raiz_espelho->esq->info);
    printf("Filho Direito da Raiz Espelho: %d\n", raiz_espelho->dir->info);
    printf("---\n");


    // Maior

    TAB *maior_number = maior(raiz);
    printf("O maior da lista e: %d\n", maior_number->info);
    printf("---\n");

    
    // Menor

    TAB *menor_number = menor(raiz);
    printf("O menor da lista e: %d\n", menor_number->info);
    printf("---\n");

    //Igual

    int ab_is_equal = igual(raiz, raiz_copia); 
    if(ab_is_equal == 0) printf("Raizes nao sao iguais");
    else printf("Raizes sao iguais");
    printf("\n---\n");

    int ab_is_equal_espelho = igual(raiz, raiz_espelho); 
    if(ab_is_equal_espelho == 0) printf("Raizes nao sao iguais");
    else printf("Raizes sao iguais");


    


    return 0;
}