Vou transcrever e explicar todos os códigos do documento.

---

## Estrutura do Nó

```c
typedef struct no {
    int valor;
    struct no *direita;
    struct no *esquerda;
} NoArv;
```

Define o bloco básico da árvore. Cada nó tem um valor inteiro e dois ponteiros para os filhos esquerdo e direito.

---

## Inserção

```c
NoArv* inserir_v1(NoArv *raiz, int num){
    if(raiz == NULL){
        NoArv *aux = (NoArv*)malloc(sizeof(NoArv));
        aux->esquerda = NULL;
        aux->direita = NULL;
        aux->valor = num;
        return aux;
    }
    else{
        if(num < raiz->valor)
            raiz->esquerda = inserir_v1(raiz->esquerda, num);
        else
            raiz->direita = inserir_v1(raiz->direita, num);
        return raiz;
    }
}
```

**Como funciona:** desce recursivamente pela árvore comparando o valor. Menores vão para esquerda, maiores ou iguais para direita. Quando chega em NULL, cria o nó novo ali.

---

## Impressões

```c
void imp_pre(NoArv *a){
    if(a){
        printf("%d ", a->valor);
        imp_pre(a->esquerda);
        imp_pre(a->direita);
    }
}
```
Pré-ordem: imprime **raiz → esquerda → direita**

```c
void imp_sim(NoArv *a){
    if(a){
        imp_sim(a->esquerda);
        printf("%d ", a->valor);
        imp_sim(a->direita);
    }
}
```
Simétrica: imprime **esquerda → raiz → direita**, que numa BST resulta em ordem crescente.

---

## Remoção de Nó Folha

```c
NoArv* remover_no_folha(NoArv *raiz, int chave){
    if(raiz == NULL){
        printf("\nValor nao encontrado.\n");
        return NULL;
    } else {
        if(raiz->valor == chave){
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                printf("\nNo '%d' Removido Com Sucesso\n", chave);
                return NULL;
            } else {
                // Nó com filhos — NÃO IMPLEMENTADO
            }
        } else {
            if(chave < raiz->valor)
                raiz->esquerda = remover_no_folha(raiz->esquerda, chave);
            else
                raiz->direita = remover_no_folha(raiz->direita, chave);
            return raiz;
        }
    }
}
```

**Como funciona:** busca o nó pela chave. Se encontrar e for folha, libera e retorna NULL. Se tiver filhos, não faz nada — função incompleta. A busca está correta, escolhendo esquerda ou direita pela comparação.

---

## Remoção com Um Filho

```c
NoArv* remover_no_um_filho(NoArv *raiz, int chave){
    if(raiz == NULL) return NULL;
    else{
        if(raiz->valor == chave){
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                printf("\nNo Folha Removido Com Sucesso.\n");
                return NULL;
            }
            else{
                if(raiz->esquerda != NULL && raiz->direita != NULL){
                    // Dois filhos — NÃO IMPLEMENTADO
                }
                else {
                    if(raiz->esquerda == NULL){
                        NoArv *aux = raiz->direita;
                        free(raiz);
                        printf("\nNo Com Um Filho a Direita Removido Com Sucesso.\n");
                        return aux;
                    }
                    else if(raiz->direita == NULL){
                        NoArv *aux = raiz->esquerda;
                        free(raiz);
                        printf("\nNo Com Um Filho a Esquerda Removido Com Sucesso.\n");
                        return aux;
                    }
                }
            }
        } else {
            // ❌ BUG: desce pelos dois lados
            raiz->esquerda = remover_no_um_filho(raiz->esquerda, chave);
            raiz->direita = remover_no_um_filho(raiz->direita, chave);
        }
        return raiz;
    }
}
```

**Como funciona:** trata folha e um filho corretamente. Quando tem um filho, salva o filho em `aux`, libera o nó atual e retorna `aux` para o pai — fazendo o filho subir no lugar.

**Bug:** quando o valor não é encontrado no nó atual, desce pelos dois lados simultaneamente em vez de escolher só um pela comparação.

---

## Remoção Completa

```c
NoArv* remover_qualquer_no(NoArv *raiz, int chave){
    if(raiz == NULL) return NULL;
    else {
        if(raiz->valor == chave){

            // Caso 1: folha
            if(raiz->direita == NULL && raiz->esquerda == NULL){
                free(raiz);
                printf("\nNo Folha Removido com Sucesso\n");
                return NULL;
            }
            else {
                // Caso 3: dois filhos
                if(raiz->direita != NULL && raiz->esquerda != NULL){
                    NoArv *aux = raiz->esquerda;
                    while(aux->direita != NULL)
                        aux = aux->direita;

                    raiz->valor = aux->valor;
                    printf("Aux: valor", aux->valor); // ❌ falta %d
                    aux->valor = chave;
                    raiz->esquerda = remover_qualquer_no(raiz->esquerda, chave);
                    return raiz;
                }
                // Caso 2: um filho
                else {
                    if(raiz->direita != NULL){
                        NoArv *aux = raiz->direita;
                        free(raiz);
                        printf("\nNo Com Um Filho a Direita Removido com Sucesso\n");
                        return aux;
                    }
                    else if(raiz->esquerda != NULL){
                        NoArv *aux = raiz->esquerda;
                        free(raiz);
                        printf("\nNo Com Um Filho a Esquerda Removido com Sucesso\n");
                        return aux;
                    }
                }
            }
        }
        else {
            // ❌ BUG: desce pelos dois lados
            raiz->esquerda = remover_qualquer_no(raiz->esquerda, chave);
            raiz->direita = remover_qualquer_no(raiz->direita, chave);
        }
        return raiz;
    }
}
```

**Caso 3 (dois filhos) explicado:**

```
      50
     /
    25  ← vai para o mais à direita
      \
      30  ← esse é o predecessor (maior da subárvore esquerda)
```

1. Encontra o **predecessor** (maior da subárvore esquerda) percorrendo sempre à direita
2. Copia o valor do predecessor para o nó a ser removido
3. Coloca a chave original no predecessor
4. Chama a remoção recursivamente na subárvore esquerda para remover a chave que foi colocada lá

---

## Main

```c
int main(){
    NoArv *raiz = NULL;
    raiz = inserir_v1(raiz, 50);
    raiz = inserir_v1(raiz, 25);
    raiz = inserir_v1(raiz, 80);
    raiz = inserir_v1(raiz, 30);
    // ...menu com do-while...
}
```

Monta a árvore inicial:
```
    50
   /  \
  25   80
    \
    30
```

Depois entra num loop com menu de opções: inserir, imprimir ou remover qualquer nó.

---

## Resumo dos bugs

| Função | Problema |
|---|---|
| `remover_no_folha` | Não trata nó com filhos |
| `remover_no_um_filho` | No `else` desce pelos dois lados |
| `remover_qualquer_no` | No `else` desce pelos dois lados |
| `remover_qualquer_no` | `printf("Aux: valor", aux->valor)` sem `%d` |