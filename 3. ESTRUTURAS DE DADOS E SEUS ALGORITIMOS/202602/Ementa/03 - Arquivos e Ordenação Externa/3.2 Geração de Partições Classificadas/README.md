# 3.2 Geração de Partições Classificadas

## Objetivo de aprendizagem

- Entender por que arquivos grandes (que não cabem em RAM) exigem uma fase de geração de partições ordenadas (runs) antes de poder ordenar o todo.
- Comparar a geração simples de partições (ordenar blocos do tamanho da memória) com a seleção por substituição (replacement selection).
- Entender por que a seleção por substituição usa um heap e por que ela gera, em média, partições maiores que a memória disponível.

## Roteiro de leitura

- **SZ (livro-base):** capítulo de Ordenação Externa, seção de geração de partições / seleção por substituição (conferir página exata) — é a fonte principal e praticamente única entre os 4 livros para este subtópico.
- **CO (Cormen):** não trata geração de partições/ordenação externa como tópico dedicado. O que é reaproveitável do CLRS é o cap. 6 (Heapsort/heaps), já que a seleção por substituição usa exatamente a estrutura de heap descrita lá.
- **CE (Celes):** não cobre ordenação externa — foco do livro é memória principal.
- **KR:** não se aplica diretamente; a implementação usa a E/S de arquivo já vista em 3.1 (cap. 7 do KR) combinada com um heap em memória.

## Notas de estudo elaboradas

### Por que ordenação externa

Quando o arquivo a ordenar é muito maior que a RAM disponível, não é possível carregar tudo de uma vez e aplicar um algoritmo de ordenação em memória (quicksort, heapsort etc.) diretamente. A estratégia geral tem duas fases:

1. **Geração de partições (este subtópico):** dividir o arquivo em blocos ordenados (chamados *runs* ou *partições classificadas*), cada um pequeno o suficiente (ou não, no caso da seleção por substituição) para caber na memória durante sua geração.
2. **Intercalação (subtópico 3.3):** combinar as partições geradas até restar uma única partição — o arquivo ordenado.

### Geração simples de partições

A técnica mais direta: ler blocos de tamanho igual à memória disponível (M registros), ordenar cada bloco inteiramente em memória (com quicksort/heapsort, O(M log M)), e escrever o bloco ordenado como uma partição no disco. Se o arquivo tem N registros, isso gera **⌈N / M⌉** partições, cada uma de exatamente M registros (exceto possivelmente a última).

### Seleção por substituição (replacement selection)

Técnica mais sofisticada que gera, **em média, partições de tamanho 2M** (o dobro da memória disponível), reduzindo o número de partições a intercalar depois. Funciona assim:

1. Mantém-se um **heap mínimo** (heap de seleção) com M registros em memória.
2. Repetidamente: remove-se o menor elemento do heap e escreve-se na partição de saída atual.
3. Lê-se um novo registro do arquivo de entrada:
   - Se o novo registro é **maior ou igual** ao último escrito na partição atual, ele pode entrar no heap normalmente (ainda pertence à partição corrente).
   - Se o novo registro é **menor** que o último escrito, ele não pode entrar na partição atual (quebraria a ordenação) — é marcado e mantido no heap, mas "congelado" para a **próxima** partição.
4. Quando o heap fica cheio só de elementos congelados, a partição atual é fechada e uma nova começa.

Por que gera partições maiores que M, em média: à medida que a leitura avança em dados com alguma ordem residual (ou até aleatórios), boa parte dos novos elementos lidos ainda cabe na partição corrente antes que o heap fique saturado de elementos "congelados". Para dados já parcialmente ordenados, o tamanho médio da partição pode ser muito maior que 2M.

### Custo (I/O)

A métrica central em ordenação externa não é o número de comparações, mas o **número de acessos a disco** (leituras/escritas de blocos). A geração de partições custa uma leitura + uma escrita de todo o arquivo (2 passadas de I/O), independente da técnica usada — a diferença entre geração simples e seleção por substituição não está no custo desta fase, mas no **número de partições resultantes**, que impacta diretamente o custo da fase de intercalação (3.3): menos partições = menos passadas de merge.

### Exemplo passo a passo: seleção por substituição com M=3

Entrada, na ordem lida: `6, 2, 9, 4, 1, 8, 12, 3, 10, 5, 7, 11` (12 valores, memória cabe M=3 registros).

**Inicialização:** lê os 3 primeiros valores pro heap → heap ativo = `{2, 6, 9}`, congelados = `{}`, último escrito = −∞.

| Passo | Saída (min do heap ativo) | Último escrito | Novo valor lido | Vai pra... | Heap ativo depois | Congelados depois |
|---|---|---|---|---|---|---|
| 1 | 2 | 2 | 4 | 4 ≥ 2 → ativo | {4, 6, 9} | {} |
| 2 | 4 | 4 | 1 | 1 < 4 → **congela** | {6, 9} | {1} |
| 3 | 6 | 6 | 8 | 8 ≥ 6 → ativo | {8, 9} | {1} |
| 4 | 8 | 8 | 12 | 12 ≥ 8 → ativo | {9, 12} | {1} |
| 5 | 9 | 9 | 3 | 3 < 9 → **congela** | {12} | {1, 3} |
| 6 | 12 | 12 | 10 | 10 < 12 → **congela** | {} | {1, 3, 10} |

No passo 6, o heap ativo esvaziou e os congelados completaram M=3 elementos → **fecha a partição 1** = `[2, 4, 6, 8, 9, 12]` (6 elementos = 2M, o comportamento médio esperado). Os congelados `{1, 3, 10}` viram o heap ativo da partição 2, e o "último escrito" reseta para −∞.

**Partição 2** (heap ativo inicial = `{1, 3, 10}`, sem mais congelados):

| Passo | Saída | Último escrito | Novo valor lido | Vai pra... | Heap ativo depois |
|---|---|---|---|---|---|
| 7 | 1 | 1 | 5 | 5 ≥ 1 → ativo | {3, 5, 10} |
| 8 | 3 | 3 | 7 | 7 ≥ 3 → ativo | {5, 7, 10} |
| 9 | 5 | 5 | 11 | 11 ≥ 5 → ativo | {7, 10, 11} |
| 10 | 7 | 7 | *(fim da entrada)* | — | {10, 11} |
| 11 | 10 | — | — | — | {11} |
| 12 | 11 | — | — | — | {} |

Sem mais entrada, o heap ativo apenas esvazia: **partição 2** = `[1, 3, 5, 7, 10, 11]`.

Resultado: **2 partições de 6 elementos cada**, a partir de M=3 — exatamente o comportamento esperado de ~2M por partição, contra `⌈12/3⌉ = 4` partições que a geração simples produziria com o mesmo M.

## Exemplos em C

Implementação simplificada de seleção por substituição, usando um heap mínimo em array (heap implícito, mesma técnica do módulo 5) e a lógica de "congelar" elementos menores que o último escrito. Simula o exemplo acima (M=3):

```c
#include <stdio.h>

#define M 3  /* tamanho da memória disponível, em registros */

/* --- heap mínimo simples em array (0-indexado) --- */
int heap[M];
int tam_heap = 0;

void heap_troca(int *a, int *b) { int t = *a; *a = *b; *b = t; }

void heap_desce(int i) {
    int menor = i, e = 2*i + 1, d = 2*i + 2;
    if (e < tam_heap && heap[e] < heap[menor]) menor = e;
    if (d < tam_heap && heap[d] < heap[menor]) menor = d;
    if (menor != i) { heap_troca(&heap[i], &heap[menor]); heap_desce(menor); }
}

void heap_insere(int valor) {
    int i = tam_heap++;
    heap[i] = valor;
    while (i > 0 && heap[(i-1)/2] > heap[i]) {
        heap_troca(&heap[i], &heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

int heap_remove_min(void) {
    int min = heap[0];
    heap[0] = heap[--tam_heap];
    heap_desce(0);
    return min;
}

/* --- seleção por substituição --- */
void selecao_por_substituicao(int *entrada, int n) {
    int congelados[M], n_congelados = 0;
    int pos = 0;                 /* próxima posição a ler de 'entrada' */
    int ultimo_escrito = -1;     /* -infinito, pois valores aqui são >= 0 */

    /* carrega o heap inicial com os M primeiros valores */
    tam_heap = 0;
    for (int i = 0; i < M && pos < n; i++) heap_insere(entrada[pos++]);

    printf("Partição: ");
    while (tam_heap > 0 || n_congelados > 0) {
        if (tam_heap == 0) {
            /* heap ativo esvaziou: fecha partição e "descongela" os frios */
            printf("\nPartição: ");
            for (int i = 0; i < n_congelados; i++) heap_insere(congelados[i]);
            n_congelados = 0;
            ultimo_escrito = -1;
            continue;
        }

        int menor = heap_remove_min();
        printf("%d ", menor);
        ultimo_escrito = menor;

        if (pos < n) {
            int novo = entrada[pos++];
            if (novo >= ultimo_escrito)
                heap_insere(novo);              /* ainda cabe na partição atual */
            else
                congelados[n_congelados++] = novo;  /* vai pra próxima partição */
        }
    }
    printf("\n");
}

int main(void) {
    int entrada[] = {6, 2, 9, 4, 1, 8, 12, 3, 10, 5, 7, 11};
    selecao_por_substituicao(entrada, 12);
    /* saída esperada: Partição: 2 4 6 8 9 12  seguido de  Partição: 1 3 5 7 10 11 */
    return 0;
}
```

Note que `ultimo_escrito` é exatamente o critério que decide se um valor recém-lido entra no heap ativo (partição atual) ou vai para `congelados` (próxima partição) — é a tradução direta em código da tabela do exemplo acima.

## Pontos de atenção / pegadinhas comuns de prova

- Confundir "tamanho da memória M" (número de registros que cabem em RAM) com "tamanho da partição gerada" — na seleção por substituição eles não são iguais.
- Esquecer que a estrutura de dados usada na seleção por substituição é um **heap mínimo**, não um array ordenado ou lista — isso é o que dá eficiência O(log M) por elemento processado.
- Achar que a seleção por substituição sempre gera partições de tamanho exatamente 2M — na prática é uma média (para entrada aleatória); pode variar bastante conforme a ordem dos dados de entrada.
- Confundir esta fase (gerar partições ordenadas) com a fase de intercalação (3.3) — são etapas distintas com objetivos e custos diferentes.

## Anotações pessoais

## Exercícios resolvidos
