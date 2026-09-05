# Árvores e Árvores Binárias — Resumo por Tópicos

> Fonte: aula baseada no livro *Estruturas de Dados e seus Algoritmos* (Cap. 3 na 3ª edição). Créditos aos slides originais da profa. Renata Galante (UCS).

---

## 1. Introdução: o que são árvores

Árvores são uma das estruturas de dados mais importantes da computação. Formalmente, uma árvore é um **conjunto finito de zero ou mais nós**, organizados por relações de hierarquia/subordinação entre eles. Cada nó é representado por um círculo, e as ligações (traços) entre eles indicam essa hierarquia — por exemplo, dizer que "B está subordinado a A" significa que B é filho de A na árvore.

**Aplicações citadas na aula:**
- **Sistema de arquivos**: pastas contêm pastas, que contêm arquivos — uma hierarquia natural representável por árvore.
- **Árvore de decisão**: usada para guiar escolhas passo a passo (o exemplo da aula é decidir se vai jogar tênis, avaliando clima, chuva e vento).
- **Árvore de derivação**: usada por compiladores para representar expressões aritméticas (ex.: `a × b + c / d`), respeitando a precedência dos operadores.

---

## 2. Definição formal e conceito de raiz

Uma árvore é definida recursivamente:
- Se o conjunto de nós tem **zero nós**, é uma árvore vazia.
- Se tem **um ou mais nós**, existe obrigatoriamente **um único nó especial chamado raiz**, e os demais nós formam subconjuntos que são, cada um, árvores por si mesmas — chamadas de **subárvores**.

Ou seja, toda árvore não vazia tem exatamente uma raiz, e cada subárvore dessa raiz também obedece à mesma definição — daí o caráter **recursivo** da estrutura.

No exemplo da aula: uma árvore com raiz A tem duas subárvores — uma enraizada em B e outra enraizada em C. A subárvore enraizada em B é, por sua vez, tratada como uma árvore independente, com sua própria estrutura interna.

---

## 3. Terminologia de parentesco

A aula usa uma nomenclatura baseada em relações familiares para descrever as posições dos nós:

- **Pai (ou mãe/ascendente)**: o nó imediatamente acima de um nó de referência.
- **Filho (ou filha/descendente/sucessor)**: o nó imediatamente abaixo.
- **Irmão(ã)**: nós que compartilham o mesmo pai.
- **Raiz**: o único nó que **não tem pai**. Todos os outros nós, obrigatoriamente, têm pai — caso contrário a estrutura não seria uma árvore.

**Ancestral e descendente** (conceito mais amplo que pai/filho):
- Se um nó X pertence a uma subárvore enraizada em V, então X é **descendente** de V, e V é **ancestral** de X.
- Se X for diferente de V, chama-se **descendente próprio** / **ancestral próprio**.
- Uma **folha** (nó sem filhos) não possui descendentes próprios.

---

## 4. Grau de um nó e grau da árvore

- **Grau de um nó** (ou grau de saída): número de subárvores (ou filhos) que aquele nó possui.
  - Exemplo: um nó com 3 filhos tem grau 3.
- **Grau da árvore**: o maior grau entre todos os nós da árvore. Se nenhum nó tem mais que 3 filhos, o grau da árvore é 3.
- **Nó interno (ou nó de ramificação)**: tem grau maior que zero, ou seja, possui ao menos um filho.
- **Nó folha (ou nó terminal/externo)**: tem grau igual a zero, ou seja, não possui filhos.

Na implementação em código, quando os ponteiros para os filhos de um nó apontam para `NULL`, isso indica que aquele nó é uma folha.

---

## 5. Caminhos, comprimento, nível e altura

Estes são conceitos fundamentais para entender a "geometria" da árvore:

- **Caminho**: sequência de nós consecutivos e distintos entre dois nós da árvore.
- **Comprimento do caminho**: número de ligações (arestas) entre os nós do caminho — não o número de nós.
- **Nível de um nó**: número de ligações entre a raiz e aquele nó, **mais uma unidade**.
  - A própria raiz tem nível 1 (zero ligações + 1).
  - Nós ligados diretamente à raiz têm nível 2, e assim por diante.
  - Nós "irmãos" (do mesmo pai) sempre estão no mesmo nível.
- **Altura (ou profundidade) de um nó**: número de ligações entre aquele nó e a folha descendente de maior nível, mais uma unidade.
  - Por definição, a altura de uma folha é sempre **1**.
- **Altura da árvore**: é igual ao maior nível entre todos os nós, o que equivale à altura da raiz.

> Observação da aula: nível e altura são conceitos "espelhados" — o nível cresce da raiz para as folhas, enquanto a altura cresce das folhas em direção à raiz.

---

## 6. Árvore ordenada, árvores isomorfas e floresta

- **Árvore ordenada**: os filhos de cada nó têm uma ordem definida (esquerda para direita). Duas árvores com os mesmos nós, mas em ordens diferentes de filhos, são consideradas **árvores diferentes**.
- **Árvores isomorfas**: duas árvores que podem se tornar idênticas apenas trocando a ordem das subárvores (ou seja, têm a mesma estrutura, só a ordem dos filhos muda).
- **Floresta**: simplesmente um **conjunto de árvores** (não conectadas entre si por uma raiz comum).

---

## 7. Formas de representar uma árvore

A aula mostra várias formas alternativas de desenhar/representar uma árvore, além do diagrama tradicional de círculos e ligações:

1. **Diagrama de inclusão**: o nó raiz "engloba" visualmente todos os outros nós (como caixas dentro de caixas), de forma recursiva.
2. **Diagrama de barras (indentação)**: os nós são listados com recuo (indentação) representando a hierarquia — útil, por exemplo, para imprimir a árvore via programa, sendo mais simples de implementar do que desenhar graficamente.
3. **Representação por níveis numerados**: a raiz recebe o número 1; cada filho recebe um número composto (ex.: 1.1, 1.2), permitindo localizar qualquer nó pela sua "coordenada" na árvore.
4. **Representação por parênteses**: aninha os nós usando parênteses para indicar a hierarquia de forma puramente textual.

---

## 8. Árvores binárias: definição

Uma **árvore binária** é um caso especial de árvore, extremamente usado em computação (por exemplo, para representar expressões aritméticas, já que cada operador tem exatamente dois operandos).

Definição formal:
- É um conjunto finito de zero ou mais nós.
- Se o número de nós for maior que zero, existe uma raiz, e os nós restantes formam **exatamente dois** conjuntos distintos de subárvores — a **subárvore esquerda** e a **subárvore direita** — cada uma sendo, também, uma árvore binária.
- Se o número de nós for zero, é uma árvore binária vazia.

A diferença central em relação à árvore genérica é que, na árvore binária, **o número máximo de subárvores por nó é fixado em 2** (e a ordem — esquerda/direita — importa).

---

## 9. Tipos de árvores binárias

A aula apresenta quatro classificações importantes:

- **Árvore estritamente binária**: todo nó tem **0 ou 2 filhos** — nunca apenas 1. Ou seja, um nó ou é folha (0 filhos) ou tem exatamente dois filhos.
- **Árvore binária completa**: as subárvores vazias só aparecem no **último ou penúltimo nível** da árvore.
- **Árvore binária cheia**: as subárvores vazias só aparecem no **último nível** — ou seja, todas as folhas estão no mesmo nível. É o tipo de árvore que aproveita melhor o espaço e, por isso, tem a **menor altura possível** para um dado número de nós.
- **Árvore Zig-Zag**: todo nó interno tem sempre uma subárvore vazia (alternando ou não entre esquerda e direita). É o tipo de árvore que tem a **maior altura possível**, pois "desperdiça" o espaço disponível, formando quase uma lista encadeada.

---

## 10. Implementação de árvores binárias em C

**Estrutura do nó:**
```c
typedef struct noh {
    char info;
    struct noh *esq;
    struct noh *dir;
} tnoh;
```
Cada nó guarda uma informação (`info`) e dois ponteiros: um para a subárvore esquerda (`esq`) e outro para a direita (`dir`).

**Função para criar um nó:**
A função recebe o valor de `info` como parâmetro, aloca memória dinamicamente (com `malloc`), preenche o campo `info`, inicializa os ponteiros `esq` e `dir` como `NULL` (indicando que o novo nó começa sem filhos) e retorna o ponteiro para o nó criado.

**Montagem da árvore:**
A árvore é construída encadeando chamadas dessa função de criação: o ponteiro da raiz recebe o retorno da criação do primeiro nó; em seguida, `raiz->esq` e `raiz->dir` recebem os retornos de novas chamadas, e assim sucessivamente, até formar toda a estrutura desejada.

---

## 11. Caminhamento (percurso) em árvores binárias

**Caminhamento** é o processo sistemático de visitar todos os nós de uma árvore, garantindo que **cada nó seja visitado exatamente uma vez**. A "visita" é a operação realizada sobre o nó (por exemplo, imprimir seu valor, ou realizar algum cálculo).

A aula apresenta quatro tipos principais de caminhamento:

### a) Caminhamento por largura (por nível)
Visita os nós nível a nível, da esquerda para a direita, usando uma estrutura auxiliar de **fila**.

### b) Pré-ordem (profundidade)
Ordem: **Raiz → Esquerda → Direita**.
Visita primeiro a raiz, depois percorre (recursivamente) toda a subárvore esquerda, e só então a subárvore direita.

### c) Ordem simétrica (in-order)
Ordem: **Esquerda → Raiz → Direita**.
Percorre primeiro toda a subárvore esquerda, depois visita a raiz, e por fim percorre a subárvore direita.

### d) Pós-ordem
Ordem: **Esquerda → Direita → Raiz**.
Percorre a subárvore esquerda, depois a direita, e só por último visita a raiz.

---

## 12. Implementação do caminhamento em profundidade com pilha (iterativo)

Usando uma **pilha** como estrutura auxiliar:
1. Empilha a raiz.
2. Repete até a pilha ficar vazia:
   - Desempilha o nó do topo.
   - Realiza a operação de visita nesse nó.
   - Empilha o filho direito (se não for nulo).
   - Empilha o filho esquerdo (se não for nulo).

A aula mostra um exemplo numérico simulando essa execução passo a passo, resultando em uma sequência de visita equivalente ao caminhamento em profundidade.

---

## 13. Implementação do caminhamento em largura com fila (iterativo)

Usando uma **fila** como estrutura auxiliar:
1. Adiciona a raiz na fila.
2. Repete até a fila ficar vazia:
   - Retira o primeiro elemento da fila.
   - Realiza a operação de visita nesse nó.
   - Adiciona o filho esquerdo (se não for nulo).
   - Adiciona o filho direito (se não for nulo).

Esse método garante que os nós sejam visitados **nível por nível**, respeitando a ordem da esquerda para a direita.

---

## 14. Implementações recursivas dos caminhamentos em profundidade

Como toda função recursiva, cada uma precisa de um **critério de parada**: se o nó for `NULL` (nó vazio), a função simplesmente não faz nada.

```c
// Pré-ordem: Raiz -> Esquerda -> Direita
void preOrdem(tnoh *no) {
    if (no != NULL) {
        printf("%c", no->info);
        preOrdem(no->esq);
        preOrdem(no->dir);
    }
}

// Ordem simétrica: Esquerda -> Raiz -> Direita
void emOrdem(tnoh *no) {
    if (no != NULL) {
        emOrdem(no->esq);
        printf("%c", no->info);
        emOrdem(no->dir);
    }
}

// Pós-ordem: Esquerda -> Direita -> Raiz
void posOrdem(tnoh *no) {
    if (no != NULL) {
        posOrdem(no->esq);
        posOrdem(no->dir);
        printf("%c", no->info);
    }
}
```

Repare que a diferença entre os três caminhamentos está **apenas na posição** da chamada `printf` (a "visita") em relação às duas chamadas recursivas para as subárvores esquerda e direita.

---

## Resumo visual dos conceitos-chave

| Conceito | Definição rápida |
|---|---|
| Raiz | Único nó sem pai |
| Folha | Nó sem filhos (grau 0) |
| Grau de um nó | Número de filhos |
| Grau da árvore | Maior grau entre os nós |
| Nível de um nó | Ligações até a raiz + 1 |
| Altura de um nó | Ligações até a folha mais distante + 1 |
| Árvore binária | Cada nó tem no máximo 2 subárvores (esq./dir.) |
| Pré-ordem | Raiz → Esquerda → Direita |
| Em ordem | Esquerda → Raiz → Direita |
| Pós-ordem | Esquerda → Direita → Raiz |
| Largura | Nível a nível, com fila |