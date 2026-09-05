# 3.3 Intercalação de Partições

## Objetivo de aprendizagem

- Entender como combinar múltiplas partições ordenadas (geradas em 3.2) até obter um único arquivo ordenado.
- Comparar intercalação balanceada (balanced merge) e polifásica (polyphase merge).
- Saber calcular o número de passadas de intercalação em função do número de partições e do grau de intercalação (k-way merge), e o custo total em I/O.

## Roteiro de leitura

- **SZ (livro-base):** capítulo de Ordenação Externa, seção de intercalação/técnicas de merge (balanceada, polifásica) (conferir página exata) — fonte principal e praticamente única entre os 4 livros.
- **CO (Cormen):** o algoritmo de **merge** de duas sequências ordenadas (base do merge sort, cap. 2 do CLRS) é o fundamento teórico reaproveitado aqui — mas o CLRS não trata do problema específico de intercalar partições em disco com E/S limitada; é só a mecânica de "combinar duas sequências ordenadas em uma" que se generaliza para k vias.
- **CE (Celes):** não cobre este tópico.
- **KR:** não se aplica diretamente; a implementação reaproveita E/S de arquivo (3.1, cap. 7 do KR).

## Notas de estudo elaboradas

### Intercalação de k vias (k-way merge)

Dado um conjunto de partições ordenadas, a intercalação de k vias lê o primeiro registro de cada uma das k partições, escolhe o menor entre eles, escreve no arquivo de saída, e avança apenas na partição de onde veio o menor. Repete até esgotar todas as partições. Para escolher eficientemente o menor entre k candidatos a cada passo, usa-se um **heap mínimo (ou tournament tree/árvore de vencedores)** de tamanho k — sem isso, cada escolha custaria O(k) comparações; com heap, custa O(log k).

### Intercalação balanceada (balanced merge)

Estratégia direta: a cada **passada**, agrupa-se as partições em conjuntos de k e intercala-se cada grupo em uma nova partição maior, reduzindo o número total de partições por um fator de k. Repete-se até restar 1 partição.

- Se há P partições iniciais e o grau de intercalação é k, o **número de passadas** é `⌈log_k(P)⌉`.
- Cada passada lê e escreve o arquivo inteiro uma vez → custo de I/O por passada é proporcional a 2N (N = total de registros).
- **Custo total:** `O(N · log_k(P))` em I/O.
- Limitação prática: exige k arquivos/fitas de entrada + 1 de saída simultaneamente disponíveis (ou o dobro se alternando entre dois conjuntos de fitas a cada passada).

### Intercalação polifásica (polyphase merge)

Variante mais eficiente em uso de fitas/arquivos: em vez de separar estritamente "fitas de entrada" e "fitas de saída" por passada (como na balanceada), a polifásica distribui as partições de forma desigual entre um número fixo de fitas (baseado na sequência de Fibonacci generalizada), permitindo que a intercalação continue **usando as fitas que vão ficando livres como saída da próxima rodada**, sem esperar uma passada completa terminar. Isso reduz o número de fitas físicas necessárias para um dado número de partições, o que era historicamente importante quando fitas magnéticas eram caras/escassas. É mais complexa de implementar (a distribuição inicial de partições entre as fitas segue números de Fibonacci) mas tende a reduzir o número de passadas de I/O comparado à balanceada com o mesmo número de dispositivos.

| Aspecto | Balanceada | Polifásica |
|---|---|---|
| Distribuição de partições | Uniforme entre fitas de entrada | Desigual (baseada em Fibonacci) |
| Fitas necessárias para P partições | Mais fitas para mesmo desempenho | Menos fitas para mesmo desempenho |
| Complexidade de implementação | Mais simples | Mais complexa |
| Uso de dispositivos entre passadas | Entrada e saída bem separadas por passada | Fitas trocam de papel (entrada→saída) dinamicamente |

### Custo total em I/O

A métrica central deste módulo inteiro (3.1-3.3) é o **número de acessos a disco**, não o número de comparações — diferente de ordenação em memória, onde comparações dominam o custo. O custo total de ordenar externamente um arquivo de N registros é aproximadamente:

`custo_geração_partições (≈2N) + custo_intercalação (≈2N · número_de_passadas)`

Minimizar o número de passadas (maximizando k, o grau de intercalação, e/ou minimizando P, o número de partições — via seleção por substituição em 3.2) é o objetivo de projeto central deste módulo.

### Exemplo passo a passo: intercalação de 3 vias (k=3)

Três partições já ordenadas: `P1 = [1, 5, 9]`, `P2 = [2, 3, 8]`, `P3 = [4, 6, 7]`. Cada partição tem um "topo" (o próximo valor ainda não escrito); a cada passo, escolhe-se o menor entre os três topos, escreve-o na saída e avança **só** o ponteiro daquela partição.

| Passo | Topo P1 | Topo P2 | Topo P3 | Menor escolhido | Saída acumulada |
|---|---|---|---|---|---|
| 1 | 1 | 2 | 4 | **1** (P1) | 1 |
| 2 | 5 | 2 | 4 | **2** (P2) | 1, 2 |
| 3 | 5 | 3 | 4 | **3** (P2) | 1, 2, 3 |
| 4 | 5 | 8 | 4 | **4** (P3) | 1, 2, 3, 4 |
| 5 | 5 | 8 | 6 | **5** (P1) | 1, 2, 3, 4, 5 |
| 6 | 9 | 8 | 6 | **6** (P3) | 1, 2, 3, 4, 5, 6 |
| 7 | 9 | 8 | 7 | **7** (P3, esgota) | 1, 2, 3, 4, 5, 6, 7 |
| 8 | 9 | 8 | — | **8** (P2, esgota) | 1, 2, 3, 4, 5, 6, 7, 8 |
| 9 | 9 | — | — | **9** (P1, esgota) | 1, 2, 3, 4, 5, 6, 7, 8, 9 |

Repare que cada partição só "perde a vez" quando seu topo não é o menor — o ponteiro dela fica parado enquanto isso, sem custo extra de I/O (não se re-lê nada). Quando uma partição esgota, ela simplesmente sai da disputa pelas próximas rodadas.

## Exemplos em C

Intercalação de k vias em memória (simula os buffers de leitura de cada partição como vetores já carregados — na prática cada "topo" viria de um `fread` na partição correspondente). Usa busca linear entre os k topos para achar o menor a cada passo — didaticamente mais simples que manter um heap de tamanho k, mas O(k) por elemento escolhido; em ordenação externa real, com dezenas/centenas de partições, prefere-se um **heap mínimo de tamanho k** (ou uma tournament tree) para reduzir isso a O(log k) por escolha:

```c
#include <stdio.h>
#include <limits.h>

#define K 3  /* número de partições sendo intercaladas */

typedef struct {
    int *dados;
    int tam;
    int pos;   /* índice do próximo valor não consumido (o "topo") */
} Particao;

/* Intercala K partições ordenadas em 'saida'. Retorna quantos valores escreveu. */
int intercala_k_vias(Particao parts[K], int *saida) {
    int n_saida = 0;

    while (1) {
        int menor_valor = INT_MAX;
        int menor_idx = -1;

        /* busca linear: acha, entre os topos ainda não esgotados, o menor */
        for (int i = 0; i < K; i++) {
            if (parts[i].pos < parts[i].tam && parts[i].dados[parts[i].pos] < menor_valor) {
                menor_valor = parts[i].dados[parts[i].pos];
                menor_idx = i;
            }
        }

        if (menor_idx == -1) break;  /* todas as partições esgotaram */

        saida[n_saida++] = menor_valor;
        parts[menor_idx].pos++;      /* avança só o ponteiro da partição vencedora */
    }
    return n_saida;
}

int main(void) {
    int p1[] = {1, 5, 9};
    int p2[] = {2, 3, 8};
    int p3[] = {4, 6, 7};
    Particao parts[K] = {
        {p1, 3, 0},
        {p2, 3, 0},
        {p3, 3, 0}
    };

    int saida[9];
    int n = intercala_k_vias(parts, saida);

    printf("Saída: ");
    for (int i = 0; i < n; i++) printf("%d ", saida[i]);
    printf("\n");  /* esperado: 1 2 3 4 5 6 7 8 9 */
    return 0;
}
```

A troca de "busca linear entre K topos" por "heap mínimo de K elementos" é direta: em vez do laço `for` procurando o menor, faz-se `heap_remove_min()` (retorna de qual partição veio, junto com o valor) e, ao consumir aquele elemento, insere-se o próximo valor da mesma partição no heap — mesma ideia usada na seleção por substituição (3.2), só que aqui o heap tem tamanho K (número de partições) em vez de M (registros que cabem em memória).

## Pontos de atenção / pegadinhas comuns de prova

- Confundir custo em comparações com custo em I/O — em ordenação externa, I/O é o que domina e o que se otimiza; comparações em memória são desprezíveis pelo padrão.
- Esquecer que aumentar k (grau de intercalação) reduz o número de passadas mas aumenta o custo de escolha do mínimo a cada passo (mitigado com heap/tournament tree, não array).
- Confundir intercalação balanceada com polifásica na hora de calcular quantas fitas/arquivos são necessários para um dado número de partições.
- Não relacionar este subtópico com 3.2: o número de partições geradas em 3.2 é o P usado na fórmula de número de passadas aqui.

## Anotações pessoais

## Exercícios resolvidos
