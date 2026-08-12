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

// Função para realizar a rotação simples à esquerda em um nó 'r'
// Essa operação é aplicada quando a subárvore direita está muito alta.
No* rotacaoEsquerda_comentado(No *r) {
    // Declaração de ponteiros auxiliares:
    // 'y' será o nó promovido a nova raiz (o atual filho direito de r).
    // 'f' será o "filho órfão" (a subárvore à esquerda de y que mudará de pai).
    No *y, *f; 

    // PASSO 1: Mapeamento dos nós
    // y aponta para o filho à direita de r (quem vai subir)
    y = r->direito; 
    
    // f captura a subárvore esquerda de y.
    // Isso é vital porque y terá r como seu novo filho esquerdo,
    // então precisamos salvar o antigo filho de y para não perdê-lo.
    f = y->esquerdo; 

    // PASSO 2: A Rotação (Troca de ponteiros)
    // O nó 'r' (antiga raiz) desce e torna-se filho ESQUERDO de 'y'.
    y->esquerdo = r; 
    
    // O nó 'f' (que estava à esquerda de y) agora é adotado por 'r'.
    // Como 'f' era maior que 'r' mas menor que 'y', ele se encaixa perfeitamente
    // como o novo filho DIREITO de 'r'.
    r->direito = f; 

    // PASSO 3: Atualização das Alturas
    // A ordem importa: atualizamos 'r' primeiro porque ele agora é filho de 'y'.
    // A altura de um nó é 1 + a maior altura entre seus dois filhos.
    
    // Atualiza r (o nó que desceu)
    r->altura = maior(alturaNo(r->esquerdo), alturaNo(r->direito)) + 1;
    
    // Atualiza y (a nova raiz) baseada na nova altura de r
    y->altura = maior(alturaNo(y->esquerdo), alturaNo(y->direito)) + 1;

    // Retornamos 'y', pois ele agora ocupa a posição onde 'r' estava originalmente.
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

// Função que recebe o nó desbalanceado 'r' e retorna a nova raiz da subárvore
No* rotacaoDireita_comentado(No *r) {
    // Declaração de ponteiros auxiliares para não perdermos as referências
    // y: será o nó que subirá para ser a nova raiz (atual filho esquerdo de r)
    // f: será o "filho órfão" que precisará trocar de pai
    No *y, *f; 

    // PASSO 1: Mapeamento (Identificar quem é quem)
    // y recebe o filho da esquerda de r. É ele quem vai "subir" na árvore.
    y = r->esquerdo;
    
    // f recebe o filho da direita de y. 
    // Por que? Porque y vai ganhar r como novo filho à direita, então 
    // o antigo filho direito de y (f) precisa de uma nova casa.
    f = y->direito; 

    // PASSO 2: A Rotação (Troca de ponteiros)
    // O nó 'r' desce para a direita, tornando-se filho de 'y'.
    y->direito = r;
    
    // O nó 'f' é adotado por 'r' como seu novo filho esquerdo.
    // Isso mantém a lógica da árvore: f era maior que y e menor que r.
    r->esquerdo = f;

    // PASSO 3: Atualização das Alturas
    // Como a estrutura mudou, as alturas gravadas nos nós estão obsoletas.
    // É CRUCIAL atualizar 'r' primeiro, pois ele agora é filho de 'y'.
    
    // Altura de r = 1 + a maior altura entre seus novos filhos
    r->altura = maior(alturaNo(r->esquerdo), alturaNo(r->direito)) + 1;
    
    // Altura de y = 1 + a maior altura entre seus novos filhos (incluindo o novo r)
    y->altura = maior(alturaNo(y->esquerdo), alturaNo(y->direito)) + 1;

    // Retornamos y, que agora é a raiz oficial dessa parte da árvore
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

/**
 * Função: balancear
 * -----------------
 * Recebe um nó (raiz) e verifica se ele está desbalanceado (FB > 1 ou FB < -1).
 * Se estiver, aplica a rotação correta baseada no sinal do FB do nó e de seu filho.
 */
No* balancear_comentado(No *raiz) {
    // Calcula a diferença de altura entre a subárvore esquerda e direita
    short fb = fatorDeBalanceamento(raiz);

    // --- CASO 1: DESBALANCEAMENTO À DIREITA (Linha Reta ou Nó Cheio) ---
    // Se fb < -1, a direita está muito mais alta que a esquerda.
    // Se o FB do filho for <= 0, significa que o filho também pende para a direita (ou está neutro).
    // Isso forma uma "linha reta" à direita. Uma rotação simples resolve.
    if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0) {
        raiz = rotacaoEsquerda(raiz);
    }

    // --- CASO 2: DESBALANCEAMENTO À ESQUERDA (Linha Reta ou Nó Cheio) ---
    // Se fb > 1, a esquerda está muito mais alta que a direita.
    // Se o FB do filho for >= 0, significa que o filho também pende para a esquerda (ou está neutro).
    // Isso forma uma "linha reta" à esquerda. Uma rotação simples resolve.
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0) {
        raiz = rotacaoDireita(raiz);
    }

    // --- CASO 3: ROTAÇÃO DUPLA ESQUERDA-DIREITA (O "Joelho" à Esquerda) ---
    // O nó pai pende para a esquerda (fb > 1), mas o filho pende para a DIREITA (fb < 0).
    // Existe uma "dobra" na árvore. Girar a raiz direto não resolveria o peso interno.
    // Primeiro giramos o filho para alinhar, depois a raiz para equilibrar.
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0) {
        raiz = rotacaoEsquerdaDireita(raiz);
    }

    // --- CASO 4: ROTAÇÃO DUPLA DIREITA-ESQUERDA (O "Joelho" à Direita) ---
    // O nó pai pende para a direita (fb < -1), mas o filho pende para a ESQUERDA (fb > 0).
    // Novamente, uma "dobra". Precisamos alinhar o filho à direita antes de
    // realizar a rotação principal para a esquerda.
    else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0) {
        raiz = rotacaoDireitaEsquerda(raiz);
    }

    // Retorna a nova raiz (que pode ter mudado após as rotações)
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


int main(){
    printf("Hello AVL.");
    return 0;
}