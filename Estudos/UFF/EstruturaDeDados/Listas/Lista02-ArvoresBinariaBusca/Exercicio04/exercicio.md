Para resolver este exercício, precisamos de uma estratégia em três passos, já que em C a alocação de vetores exige que saibamos o tamanho antecipadamente (ou que usemos realocação dinâmica).

A estratégia será:
1.  **Contar** quantos elementos na ABB são menores que $N$.
2.  **Alocar** um vetor com o tamanho exato encontrado.
3.  **Preencher** o vetor percorrendo a árvore de forma ordenada (percurso simétrico).

### Implementação em C

```c
#include <stdio.h>
#include <stdlib.h>

// Estrutura fornecida
typedef struct ab {
    int info;
    struct ab *esq, *dir;
} TABB;

// Função auxiliar para contar quantos nós são menores que N
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
```

### Explicação baseada no material

* **Aproveitamento da Propriedade da ABB:** Nas funções auxiliares, utilizamos a lógica de busca do **Slide 7**. Se o nó atual possui um valor maior ou igual a $N$, não perdemos tempo visitando a subárvore direita, pois todos os valores lá serão obrigatoriamente maiores que $N$ (definição de ABB do **Slide 4**).
* **Percurso Simétrico:** Ao preencher o vetor seguindo a ordem `esquerda -> raiz -> direita`, garantimos que o vetor final contenha os elementos menores que $N$ em **ordem crescente**.
* **Alocação Dinâmica:** Como destacado no material, operações de busca e manipulação devem ser eficientes. Usamos o `malloc` para criar o vetor exatamente com o tamanho dos dados úteis, evitando desperdício de memória.

**Importante:** Quem chamar a função `mN` deve ser responsável por dar um `free()` no ponteiro retornado para evitar vazamento de memória.

---

Este código realiza uma tarefa sofisticada: ele pega uma árvore binária que pode estar "bagunçada" (sem ordem específica), transforma-a em uma **Árvore Binária de Busca (ABB)** e, em seguida, extrai todos os valores menores que um número $N$ para dentro de um vetor dinâmico.

Vamos dividir a explicação por "blocos de responsabilidade":

---

## 1. A Estrutura e Criação
O `typedef struct ab` define o nó da árvore com um valor (`info`) e dois ponteiros para os filhos. A função `Cria` apenas aloca a memória e inicializa esses valores.

## 2. O Motor de Reorganização (`reorganiza_para_ABB`)
Esta parte é interessante porque ela "limpa" a estrutura da árvore:
* **`insere_ABB`**: É a função clássica. Se o novo valor for menor que a raiz, vai para a esquerda; se for maior, vai para a direita. Isso garante a propriedade fundamental da ABB.
* **`percorre_e_insere`**: Ela visita cada nó da árvore original (usando percurso pré-ordem) e insere esse valor na **nova** árvore.
* **Resultado**: Mesmo que a árvore `raiz` no `main` tenha sido montada de forma aleatória, a `raiz2` será uma ABB perfeitamente ordenada.

## 3. Extração dos Elementos Menores que $N$
Este é o objetivo da questão **Q4**. Como vetores em C precisam de um tamanho fixo, o processo é feito em duas passagens:

### Passo A: Contagem (`conta_menores`)
Antes de criar o vetor, precisamos saber o tamanho dele.
* Se o valor atual (`a->info`) for menor que $N$, contamos `1` e somamos com o que vier da esquerda e da direita.
* **Otimização de ABB**: Se o valor atual for **maior ou igual** a $N$, sabemos que ninguém na subárvore direita servirá (pois na ABB a direita é sempre maior). Então, o código inteligentemente ignora o lado direito, economizando processamento.



### Passo B: Preenchimento (`preenche`)
Esta função usa o **Percurso Simétrico (In-order)**:
1.  Vai todo para a **esquerda**.
2.  Processa a **raiz** (insere no vetor).
3.  Vai para a **direita**.
* **Vantagem**: Usando essa ordem, o seu vetor resultante já sairá **ordenado de forma crescente**, sem que você precise usar um algoritmo de ordenação (como o Bubble Sort) depois.



### Passo C: A Função Principal `mN`
Ela coordena tudo:
1.  Chama `conta_menores` para obter o tamanho.
2.  Usa `malloc` para reservar o espaço exato na memória.
3.  Chama `preenche` para colocar os dados lá.
4.  Retorna o ponteiro do vetor.

---

## 4. O Fluxo no `main` e a Impressão
No `main`, o código:
1.  Monta uma árvore de teste.
2.  Gera a versão ABB (`raiz2`).
3.  Chama `mN` para buscar valores menores que 5.
4.  **O Laço `for`**: Como `mN` retorna um ponteiro (`int*`), o código usa um laço para percorrer as posições da memória e imprimir cada número.
5.  **`free(vetor_menor_n)`**: Essencial! Como o vetor foi criado com `malloc`, se não liberarmos a memória, ocorre um *memory leak*.

---

### Resumo Visual das Impressões:
* **ImpPre (Pré-ordem)**: Raiz -> Esq -> Dir (útil para ver a hierarquia).
* **ImpSim (Simétrico)**: Esq -> Raiz -> Dir (em uma ABB, isso sempre mostra os números em ordem crescente).
* **ImpPos (Pós-ordem)**: Esq -> Dir -> Raiz (comumente usada para deletar árvores da memória).

Este código é um excelente exemplo de como usar as propriedades de uma estrutura de dados (a ordem da ABB) para tornar um algoritmo de busca e extração muito mais rápido do que se estivéssemos usando uma lista comum.