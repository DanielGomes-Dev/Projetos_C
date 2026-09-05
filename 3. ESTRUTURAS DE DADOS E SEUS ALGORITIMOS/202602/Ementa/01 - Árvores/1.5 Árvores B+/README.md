# 1.5 Árvores B+

## Objetivo de aprendizagem

- Explicar as duas diferenças estruturais entre árvore B e árvore B+.
- Entender por que B+ é a escolha real em índices de bancos de dados e sistemas de arquivos.
- Executar busca por igualdade e por intervalo (range query) em uma B+.

## Roteiro de leitura

- **SZ (livro-base):** o Szwarcfiter costuma tratar árvore B+ como uma seção/extensão dentro do capítulo de Árvores B (1.4), não como capítulo totalmente separado — leia 1.4 primeiro e depois a seção específica de B+ na sequência (conferir página exata).
- **CO (Cormen):** o CLRS não tem uma seção dedicada a B+ em todas as edições — cobre árvore B "genérica" (cap. 18) e às vezes menciona B+ apenas en passant como variante usada em sistemas de banco de dados. Se não achar seção específica na sua edição, trate o cap. 18 (já lido em 1.4) como a base teórica e foque as diferenças estruturais na sua própria síntese (abaixo).
- **CE:** não se aplica — mesmo motivo de 1.4 (livro focado em memória principal).
- **KR:** não se aplica.

## Notas de estudo elaboradas

### As duas diferenças-chave entre B e B+

1. **Onde ficam os dados**: em árvore B, registros/dados podem estar em qualquer nó (interno ou folha). Em árvore B+, **todos os dados ficam exclusivamente nas folhas** — nós internos guardam só chaves-separadoras para navegação, sem dado associado.
2. **Folhas encadeadas**: as folhas de uma árvore B+ são ligadas entre si numa lista encadeada (geralmente duplamente encadeada), na ordem das chaves.

### Por que isso importa na prática

- **Nós internos mais "gordos" em chaves**: como nós internos de B+ não guardam dados, cabem mais chaves-separadoras por nó (mesmo tamanho de bloco de disco) → árvore mais "rasa" (menor altura) → menos acessos a disco para achar uma folha.
- **Range queries eficientes**: para buscar todos os valores entre X e Y, basta achar a folha onde X estaria (O(log_m n)) e depois percorrer a lista encadeada de folhas até passar de Y — **sem re-subir na árvore**. Em árvore B comum, uma busca por intervalo pode exigir múltiplas travessias internas, sendo bem menos eficiente.
- Isso é exatamente por que **índices de bancos de dados reais (B-tree index do MySQL/PostgreSQL, etc.) usam B+ e não B pura** — range queries (`WHERE data BETWEEN x AND y`, ORDER BY) são extremamente comuns em SQL.

### Busca

**Igualdade**: desce pela árvore como em B comum, usando as chaves dos nós internos só como guia de navegação (nunca encontra o dado num nó interno — sempre precisa chegar à folha, mesmo que a chave "apareça" replicada num nó interno como separador).

**Intervalo [X, Y]**: desce até a folha onde X estaria; percorre a lista encadeada de folhas a partir daí, coletando registros, até ultrapassar Y.

### Complexidade

| Operação | Complexidade |
|---|---|
| Busca por igualdade | O(log_m n) |
| Busca por intervalo de tamanho k | O(log_m n + k) — log para achar o início, k para percorrer a lista de folhas |
| Inserção / Remoção | O(log_m n), com split/merge análogos à árvore B, mas atuando também sobre a lista encadeada de folhas |

### Passo a passo: range query numa B+

Suponha uma árvore B+ de ordem m=3 já construída, com 3 folhas encadeadas contendo, em ordem: `[3, 5]`, `[10, 15]`, `[20, 25, 30]`, e nós internos guiando a navegação (chaves-separadoras `10` e `20`):

```
                 [10 | 20]
                /     |     \
           [3,5] → [10,15] → [20,25,30]     (setas = encadeamento entre folhas)
```

**Range query `[8, 22]`:**
1. Desce pela árvore comparando com as chaves internas: `8 < 10` → vai para a folha mais à esquerda que poderia conter 8, que é `[10,15]` (já que `8` cairia entre a primeira e a segunda folha — a navegação usa `10` como separador: valores `< 10` vão pra `[3,5]`, mas como estamos buscando o **início do intervalo** ≥ 8, a folha correta para começar é `[10,15]`).
2. A partir daí, **sem voltar a subir na árvore**, percorre a lista encadeada de folhas: coleta `10, 15` (ambos dentro de [8,22]), segue o ponteiro de encadeamento para a próxima folha `[20,25,30]`, coleta `20` (dentro do intervalo), encontra `25` (> 22, fora do intervalo) e para.
3. Resultado: `10, 15, 20`.

Compare com uma árvore B comum (sem encadeamento de folhas): para o mesmo range, seria necessário fazer buscas/travessias internas repetidas para "achar a próxima chave maior", já que não há um caminho direto entre folhas vizinhas.

## Exemplos em C

Não há implementação de árvore B+ nas listas de exercícios deste curso — exemplo abaixo é ilustrativo, focado em mostrar a diferença estrutural central: **nó interno** (só chaves-separadoras) vs. **nó folha** (dados + ponteiro para a próxima folha).

```c
#define M 3

// Nó interno: só chaves-separadoras + ponteiros para filhos, SEM dado associado.
typedef struct no_interno_bplus {
  int chaves[M - 1];
  void *filhos[M];            // aponta para NoInternoBPlus* ou FolhaBPlus*, conforme o nível
  int n_chaves;
} NoInternoBPlus;

// Nó folha: guarda os dados de fato (aqui simplificado como int),
// e um ponteiro para a PRÓXIMA folha — é isso que viabiliza range query
// sem re-subir na árvore.
typedef struct folha_bplus {
  int chaves[M - 1];
  int dados[M - 1];           // em um índice real, seria ponteiro/offset pro registro completo
  int n_chaves;
  struct folha_bplus *proxima;  // encadeamento entre folhas (a diferença-chave vs. árvore B)
} FolhaBPlus;

// Percorre a lista de folhas coletando tudo entre [x, y] — não toca
// mais em nós internos depois de achar a folha inicial.
void busca_intervalo(FolhaBPlus *folha_inicial, int x, int y) {
  FolhaBPlus *atual = folha_inicial;
  while (atual != NULL) {
    for (int i = 0; i < atual->n_chaves; i++) {
      if (atual->chaves[i] > y) return;              // passou do intervalo, encerra
      if (atual->chaves[i] >= x)
        printf("%d -> %d\n", atual->chaves[i], atual->dados[i]);
    }
    atual = atual->proxima;                           // segue o encadeamento, sem subir na árvore
  }
}
```

A função `busca_intervalo` acima é o que torna a árvore B+ superior à B pura para range queries: uma vez achada a folha inicial (com uma descida O(log_m n) por `NoInternoBPlus`, não mostrada aqui, análoga à busca de árvore B em 1.4), o resto é uma varredura linear O(k) na lista encadeada.

## Pontos de atenção / pegadinhas comuns de prova

- Não confundir: em B+, uma chave que aparece em nó interno **também** aparece replicada em alguma folha (as folhas contêm o conjunto completo de chaves+dados) — em árvore B pura, cada chave aparece uma única vez em algum nível.
- Range query é o argumento central de prova para "por que B+ em vez de B" — se a pergunta for sobre eficiência de busca por intervalo, a resposta quase sempre envolve mencionar o encadeamento de folhas.
- Inserção/remoção em B+ precisa manter tanto a estrutura de árvore quanto a lista encadeada de folhas consistentes — split de folha, por exemplo, precisa religar os ponteiros de lista, não só os ponteiros de árvore.
- Altura de B+ tende a ser igual ou menor que a de uma B equivalente com mesma ordem m, porque nós internos cabem mais separadores (não carregam dado).

## Anotações pessoais

## Exercícios resolvidos
