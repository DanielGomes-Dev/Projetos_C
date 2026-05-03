#include <stdio.h>  // Biblioteca para funções de entrada/saída (printf, scanf)
#include <stdlib.h> // Biblioteca para alocação de memória (malloc, free)


/* =========================================================
   ESTRUTURA DO NÓ DA ÁRVORE AVL
   Cada "nó" é uma caixinha que guarda:
     - Um valor inteiro
     - Um ponteiro para o filho da esquerda (valores menores)
     - Um ponteiro para o filho da direita (valores maiores)
     - A altura desse nó na árvore
   ========================================================= */
typedef struct no {
    int valor;                      // O dado guardado nesse nó (ex: 42)
    struct no *esquerdo, *direito;  // Ponteiros para os filhos esquerdo e direito
    short altura;                   // Altura do nó (folha = 0, sobe +1 a cada nível)
} No;


/* ---------------------------------------------------------
   FUNÇÃO: novoNo
   OBJETIVO: Criar e inicializar um novo nó com um dado valor.
   PARÂMETRO: valor — o inteiro que será guardado no nó.
   RETORNO: Ponteiro para o novo nó criado.
   --------------------------------------------------------- */
No* novoNo(int valor){
    No *novo = malloc(sizeof(No)); // Reserva espaço na memória para o novo nó

    if(novo){                      // Se malloc teve sucesso (não retornou NULL)...
        novo->valor = valor;       // Guarda o valor recebido
        novo->esquerdo = NULL;     // Ainda não tem filho à esquerda
        novo->direito = NULL;      // Ainda não tem filho à direita
        novo->altura = 0;          // Nó recém-criado é uma folha, altura = 0
    }
    else {
        // malloc retornou NULL: memória insuficiente
        printf("\nErro ao criar novo no.");
    }

    return novo; // Retorna o ponteiro para o nó (ou NULL se falhou)
}


/* ---------------------------------------------------------
   FUNÇÃO: maior
   OBJETIVO: Retornar o maior entre dois números do tipo short.
   Usada para calcular alturas dos nós.
   --------------------------------------------------------- */
short maior(short a, short b){
    return (a > b) ? a : b; // Operador ternário: se a > b retorna a, senão retorna b
}


/* ---------------------------------------------------------
   FUNÇÃO: alturaNo
   OBJETIVO: Retornar a altura de um nó com segurança.
   IMPORTANTE: Nós NULL (inexistentes) retornam -1, não 0,
   para que a conta de altura de folhas fique correta:
       max(-1, -1) + 1 = 0  ← altura de uma folha real
   --------------------------------------------------------- */
short alturaNo(No *no){
    if(no == NULL) return -1;  // Nó inexistente: convenção -1
    else return no->altura;    // Nó existe: retorna a altura armazenada
}


/* =========================================================
   ROTAÇÕES
   Rotações são reorganizações locais da árvore usadas para
   restaurar o balanceamento sem quebrar a ordem dos valores.
   ========================================================= */

/* ---------------------------------------------------------
   FUNÇÃO: rotacaoEsquerda
   QUANDO USAR: Árvore pesada para a DIREITA (FB < -1)
                e o filho direito também pesa para a direita.

   ANTES:          DEPOIS:
       r               y
      / \             / \
     A   y    →      r   C
        / \         / \
       f   C       A   f

   r  = raiz atual (desce)
   y  = filho direito de r (sobe, vira nova raiz)
   f  = filho esquerdo de y (fica "órfão", adotado por r)
   --------------------------------------------------------- */
No* rotacaoEsquerda(No *r){
    No *y, *f; // Variáveis auxiliares

    y = r->direito;  // y é o filho direito de r — vai subir
    f = y->esquerdo; // f é o filho esquerdo de y — ficará órfão na rotação

    // --- Faz a rotação ---
    y->esquerdo = r;  // r desce: vira filho esquerdo de y
    r->direito = f;   // f (órfão) é adotado como filho direito de r

    // Recalcula alturas — r primeiro, pois agora está abaixo de y
    r->altura = maior(alturaNo(r->esquerdo), alturaNo(r->direito)) + 1;
    y->altura = maior(alturaNo(y->esquerdo), alturaNo(y->direito)) + 1;

    return y; // y é a nova raiz desta subárvore
}


/* ---------------------------------------------------------
   FUNÇÃO: rotacaoDireita
   QUANDO USAR: Árvore pesada para a ESQUERDA (FB > 1)
                e o filho esquerdo também pesa para a esquerda.

   ANTES:          DEPOIS:
       r               y
      / \             / \
     y   C    →      A   r
    / \                 / \
   A   f               f   C

   Espelho exato de rotacaoEsquerda.
   --------------------------------------------------------- */
No* rotacaoDireita(No *r){
    No *y, *f; // Variáveis auxiliares

    y = r->esquerdo; // y é o filho esquerdo de r — vai subir
    f = y->direito;  // f é o filho direito de y — ficará órfão

    // --- Faz a rotação ---
    y->direito = r;  // r desce: vira filho direito de y
    r->esquerdo = f; // f (órfão) é adotado como filho esquerdo de r

    // Recalcula alturas — r primeiro, pois agora está abaixo de y
    r->altura = maior(alturaNo(r->esquerdo), alturaNo(r->direito)) + 1;
    y->altura = maior(alturaNo(y->esquerdo), alturaNo(y->direito)) + 1;

    return y; // y é a nova raiz desta subárvore
}


/* ---------------------------------------------------------
   FUNÇÃO: rotacaoDireitaEsquerda (Rotação Dupla)
   QUANDO USAR: Árvore pesada para a DIREITA (FB < -1)
                mas o filho direito pesa para a ESQUERDA.
   Desequilíbrio em "joelho" para a direita:

   ANTES:       PASSO 1 (rot. direita no filho):    PASSO 2 (rot. esquerda na raiz):
     r                  r                                  y
      \                  \                                / \
       z       →          y             →               r   z
      /                    \
     y                      z
   --------------------------------------------------------- */
No* rotacaoDireitaEsquerda(No *r){
    r->direito = rotacaoDireita(r->direito); // Passo 1: rotaciona o filho direito para direita
    return rotacaoEsquerda(r);               // Passo 2: rotaciona a raiz para esquerda
}


/* ---------------------------------------------------------
   FUNÇÃO: rotacaoEsquerdaDireita (Rotação Dupla)
   QUANDO USAR: Árvore pesada para a ESQUERDA (FB > 1)
                mas o filho esquerdo pesa para a DIREITA.
   Desequilíbrio em "joelho" para a esquerda.

   ⚠️ ATENÇÃO — BUG NO CÓDIGO ORIGINAL:
   A linha abaixo deveria ser:
       r->esquerdo = rotacaoEsquerda(r->esquerdo);
   O código original usa r->direito por engano.
   --------------------------------------------------------- */
No* rotacaoEsquerdaDireita(No *r){
    r->direito = rotacaoEsquerda(r->esquerdo); // ⚠️ BUG: deveria ser r->esquerdo
    return rotacaoDireita(r);                  // Passo 2: rotaciona a raiz para direita
}


/* ---------------------------------------------------------
   FUNÇÃO: fatorDeBalanceamento
   OBJETIVO: Calcular o fator de balanceamento (FB) de um nó.

   FB = altura(subárvore esquerda) - altura(subárvore direita)

   Interpretação:
     FB =  0      → perfeitamente balanceado
     FB = +1/-1   → levemente desbalanceado (aceitável)
     FB > +1      → muito pesado à esquerda → precisa rotação
     FB < -1      → muito pesado à direita  → precisa rotação
   --------------------------------------------------------- */
short fatorDeBalanceamento(No *no){
    if(no){
        return alturaNo(no->esquerdo) - alturaNo(no->direito); // Esquerda menos Direita
    }
    else {
        return 0; // Nó nulo é considerado balanceado
    }
}


/* ---------------------------------------------------------
   FUNÇÃO: balancear
   OBJETIVO: Verificar se um nó está desbalanceado e aplicar
             a rotação correta para reequilibrá-lo.

   Os 4 casos possíveis:
   ┌────────────┬──────────────────┬──────────────────────────┐
   │ FB da raiz │ FB do filho      │ Rotação aplicada         │
   ├────────────┼──────────────────┼──────────────────────────┤
   │   < -1     │ <= 0 (dir. dir.) │ Simples à esquerda       │
   │   > +1     │ >= 0 (esq. esq.) │ Simples à direita        │
   │   > +1     │ > 0  (esq. dir.) │ Dupla esquerda-direita   │
   │   < -1     │ > 0  (dir. esq.) │ Dupla direita-esquerda   │
   └────────────┴──────────────────┴──────────────────────────┘
   --------------------------------------------------------- */
No* balancear(No *raiz){
    short fb = fatorDeBalanceamento(raiz); // Calcula o FB da raiz atual

    // CASO 1: Pesado à direita, filho direito também pesa à direita → rotação simples à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // CASO 2: Pesado à esquerda, filho esquerdo também pesa à esquerda → rotação simples à direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0)
        raiz = rotacaoDireita(raiz);

    // CASO 3: Pesado à esquerda, mas filho esquerdo pesa à direita → rotação dupla esq-dir
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) > 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // CASO 4: Pesado à direita, mas filho direito pesa à esquerda → rotação dupla dir-esq
    else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz; // Retorna a raiz (pode ser nova, caso tenha ocorrido rotação)
}


/* ---------------------------------------------------------
   FUNÇÃO: inserir
   OBJETIVO: Inserir um novo valor na árvore AVL, mantendo:
     1. A propriedade de busca (menores à esq, maiores à dir)
     2. O balanceamento AVL (rebalanceia após cada inserção)

   COMO FUNCIONA (recursivo):
     - Desce pela árvore até achar o lugar certo (NULL)
     - Cria o novo nó naquele lugar
     - Na VOLTA da recursão, atualiza alturas e balanceia
       cada nó do caminho de volta até a raiz
   --------------------------------------------------------- */
No* inserir(No *raiz, int valor){
    if(raiz == NULL)
        return novoNo(valor); // Lugar encontrado! Cria o nó aqui.
    else {
        if(valor < raiz->valor)
            // Valor menor → vai para a subárvore esquerda
            raiz->esquerdo = inserir(raiz->esquerdo, valor);
        else if(valor > raiz->valor)
            // Valor maior → vai para a subárvore direita
            raiz->direito = inserir(raiz->direito, valor);
        else
            // Valor já existe → AVL não aceita duplicatas
            printf("\nInsercao nao realizada!\nO elemento %d ja existe!\n", valor);
    }

    // Atualiza a altura deste nó após a inserção na subárvore
    // (+1 porque este nó está um nível acima dos filhos)
    raiz->altura = maior(alturaNo(raiz->esquerdo), alturaNo(raiz->direito)) + 1;

    // Verifica e corrige possível desequilíbrio neste nó
    raiz = balancear(raiz);

    return raiz; // Retorna a raiz (pode ter mudado após rotação)
}


/* ---------------------------------------------------------
   FUNÇÃO: remover
   OBJETIVO: Remover um nó da árvore AVL mantendo as
             propriedades de busca e balanceamento.

   TRÊS CASOS de remoção:
   ┌──────────────────┬────────────────────────────────────────────┐
   │ Caso             │ Estratégia                                 │
   ├──────────────────┼────────────────────────────────────────────┤
   │ Nó folha         │ Deleta diretamente                         │
   │ Nó com 1 filho   │ O filho assume o lugar do nó removido      │
   │ Nó com 2 filhos  │ Substitui pelo maior da subárvore esquerda │
   └──────────────────┴────────────────────────────────────────────┘
   --------------------------------------------------------- */
No* remover(No *raiz, int chave) {
    if(raiz == NULL){
        // Chegou em NULL sem achar o valor: ele não existe na árvore
        printf("Valor nao encontrado!\n");
        return NULL;
    } else {
        if(raiz->valor == chave) { // Encontrou o nó a ser removido!

            // ── CASO 1: Nó folha (sem filhos) ──────────────────────────
            if(raiz->esquerdo == NULL && raiz->direito == NULL) {
                free(raiz);  // Libera a memória do nó
                printf("Elemento folha removido: %d !\n", chave);
                return NULL; // O pai deste nó passará a apontar para NULL
            }
            else{
                // ── CASO 2: Nó com DOIS filhos ─────────────────────────
                if(raiz->esquerdo != NULL && raiz->direito != NULL){
                    No *aux = raiz->esquerdo;

                    // Encontra o maior nó da subárvore esquerda
                    // (o mais à direita dentro da subárvore esquerda)
                    while(aux->direito != NULL)
                        aux = aux->direito;

                    // Copia o valor do sucessor para este nó
                    raiz->valor = aux->valor;

                    // Coloca a chave original no sucessor para removê-lo recursivamente
                    aux->valor = chave;
                    printf("Elemento trocado: %d !\n", chave);

                    // Remove o nó que agora contém a chave (lá na subárvore esquerda)
                    raiz->esquerdo = remover(raiz->esquerdo, chave);
                    return raiz;
                }
                else{
                    // ── CASO 3: Nó com apenas UM filho ─────────────────
                    No *aux;

                    // Identifica qual filho existe (esquerdo ou direito)
                    if(raiz->esquerdo != NULL)
                        aux = raiz->esquerdo; // Filho esquerdo assume o lugar
                    else
                        aux = raiz->direito;  // Filho direito assume o lugar

                    free(raiz); // Libera o nó removido
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux; // O filho sobe para ocupar o lugar do pai
                }
            }
        } else {
            // Ainda não achou o nó — continua buscando na direção correta
            if(chave < raiz->valor)
                raiz->esquerdo = remover(raiz->esquerdo, chave); // Busca à esquerda
            else
                raiz->direito = remover(raiz->direito, chave);   // Busca à direita
        }

        // Na volta da recursão: recalcula a altura deste nó
        raiz->altura = maior(alturaNo(raiz->esquerdo), alturaNo(raiz->direito)) + 1;

        // Verifica e corrige possível desequilíbrio causado pela remoção
        raiz = balancear(raiz);

        return raiz;
    }
}


/* ---------------------------------------------------------
   FUNÇÃO: imprimir
   OBJETIVO: Exibir a árvore no terminal de forma visual,
             deitada 90° (direita em cima, esquerda embaixo).
             A indentação (tabs) representa a profundidade.

   Exemplo — árvore com raiz 20, filhos 10 e 30:
       30        ← nível 2 (2 tabs)
   20            ← nível 1 (1 tab)
       10        ← nível 2 (2 tabs)

   Para "ler" a árvore: vire a cabeça para a direita. 😄
   --------------------------------------------------------- */
void imprimir(No *raiz, int nivel){
    int i;
    if(raiz){ // Só imprime se o nó existir (condição de parada da recursão)
        imprimir(raiz->direito, nivel + 1);  // Imprime subárvore DIREITA primeiro (ficará em cima)
        printf("\n\n");
        for(i = 0; i < nivel; i++){
            printf("\t"); // Indenta de acordo com a profundidade
        }
        printf("%d", raiz->valor);           // Imprime o valor do nó atual
        imprimir(raiz->esquerdo, nivel + 1); // Imprime subárvore ESQUERDA depois (ficará embaixo)
    }
}


/* ---------------------------------------------------------
   FUNÇÃO: main
   OBJETIVO: Ponto de entrada do programa.
             Exibe um menu interativo para o usuário
             inserir, remover e visualizar a árvore AVL.
   --------------------------------------------------------- */
int main(){
    int opcao, valor;
    No *raiz = NULL; // Começa com árvore vazia

    do{
        // Exibe o menu de opções
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
        scanf("%d", &opcao);

        switch(opcao){
        case 0:
            printf("Saindo!!!");
            break;

        case 1:
            printf("\tDigite o valor a ser inserido: ");
            scanf("%d", &valor);
            raiz = inserir(raiz, valor); // raiz pode mudar após rotações!
            break;

        case 2:
            printf("\tDigite o valor a ser removido: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor); // raiz pode mudar após rotações!
            break;

        case 3:
            imprimir(raiz, 1); // Começa no nível 1 para ter 1 tab de margem
            break;

        default:
            printf("\nOpcao invalida!!!\n");
        }

    } while(opcao != 0); // Repete o menu até o usuário escolher sair

    return 0; // Programa encerrado com sucesso
}