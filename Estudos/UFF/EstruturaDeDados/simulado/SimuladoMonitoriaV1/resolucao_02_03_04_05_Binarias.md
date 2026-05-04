

# SimulEDA P1 — Exercícios 2, 3, 4 e 5


## Exercício 2

**Enunciado:** Faça uma função que verifique se uma árvore binária é simétrica.

**Exemplo dado:**
```
        20
       /  \
      10   10
     / \  / \
    1   9 9   1
```
Esta árvore É simétrica (espelho perfeito).

**Assinatura:** `int eh_simetrica(TAB *a);`

---

### 📚 O que é uma árvore simétrica?

Uma árvore é simétrica quando a subárvore esquerda é o **espelho** da subárvore direita. Ou seja:
- Os valores dos nós espelhados são iguais
- O filho esquerdo de um nó corresponde ao filho direito do nó espelhado, e vice-versa

---

### 💡 Estratégia de solução

Criamos uma função auxiliar recursiva que compara dois nós simultaneamente — um "caminhando" pela esquerda e outro pela direita, em direções opostas.

```c
// Função auxiliar: compara dois nós como espelhos
int espelho(TAB *esq, TAB *dir) {
    // Caso base 1: ambos são NULL → simétrico ✓
    if (esq == NULL && dir == NULL)
        return 1;

    // Caso base 2: só um é NULL → assimétrico ✗
    if (esq == NULL || dir == NULL)
        return 0;

    // Verifica: valores iguais E filhos cruzados simétricos
    return (esq->valor == dir->valor) &&
           espelho(esq->esquerda, dir->direita) &&
           espelho(esq->direita,  dir->esquerda);
}

// Função principal
int eh_simetrica(TAB *a) {
    if (a == NULL)
        return 1; // Árvore vazia é simétrica por definição

    return espelho(a->esquerda, a->direita);
}
```

---

### 🔍 Como funciona passo a passo com o exemplo?

```
        20          ← raiz
       /  \
      10   10       ← esq->valor == dir->valor? 10 == 10 ✓
     / \  / \
    1   9 9   1     ← cruzado: esq->esq(1) vs dir->dir(1) ✓
                        e: esq->dir(9) vs dir->esq(9) ✓
```

**Chamadas recursivas:**
1. `espelho(nó10_esq, nó10_dir)` → 10 == 10 ✓
2. `espelho(nó1_esq, nó1_dir_dir)` → 1 == 1 ✓ e ambos sem filhos ✓
3. `espelho(nó9_esq_dir, nó9_dir_esq)` → 9 == 9 ✓ e ambos sem filhos ✓
4. Todos retornam 1 → **árvore simétrica!**

---

### ✅ Resumo da lógica

| Situação | Retorna |
|---|---|
| Ambos os nós são NULL | 1 (simétrico) |
| Só um é NULL | 0 (assimétrico) |
| Valores diferentes | 0 (assimétrico) |
| Valores iguais + filhos espelhados | 1 (simétrico) |


---

## Exercício 3

**Enunciado:** Faça uma função que verifique se todas as folhas de uma árvore binária estão no mesmo nível.
**Assinatura:** `int mesmo_nivel(TAB *a);`

---

### 📚 Conceitos importantes antes de resolver

**O que é uma folha?**
> Um nó folha é aquele que **não tem filhos** — nem esquerdo, nem direito.

**O que é nível?**
> O nível (ou profundidade) de um nó é a distância dele até a raiz. A raiz está no nível 0, seus filhos no nível 1, e assim por diante.

```
        20        ← nível 0
       /  \
      10   30     ← nível 1
     / \
    5  15         ← nível 2  → folhas (não têm filhos)
```

Nesse exemplo, 30 está no nível 1 e também é folha, enquanto 5 e 15 estão no nível 2. As folhas estão em **níveis diferentes** → função retorna 0.

---

### 💡 Estratégia de solução

A ideia é:
1. Percorrer a árvore recursivamente
2. Quando encontrar uma folha, registrar seu nível
3. Se encontrar outra folha em nível **diferente**, retorna 0
4. Se todas as folhas tiverem o mesmo nível, retorna 1

Usamos uma variável estática (ou um ponteiro) para guardar o nível da **primeira folha** encontrada e comparar com as seguintes.

```c
// Função auxiliar recursiva
// nivel_folha: ponteiro para guardar o nível da 1ª folha encontrada
// nivel_atual: profundidade do nó atual
int verificar_folhas(TAB *a, int *nivel_folha, int nivel_atual) {
    // Caso base: árvore vazia — ok, não faz nada
    if (a == NULL)
        return 1;

    // Se é uma folha (sem filhos)
    if (a->esquerda == NULL && a->direita == NULL) {
        if (*nivel_folha == -1) {
            // Primeira folha encontrada: registra o nível
            *nivel_folha = nivel_atual;
            return 1;
        } else {
            // Compara com o nível da primeira folha
            return (*nivel_folha == nivel_atual);
        }
    }

    // Não é folha: desce para os filhos, aumentando o nível
    return verificar_folhas(a->esquerda, nivel_folha, nivel_atual + 1) &&
           verificar_folhas(a->direita,  nivel_folha, nivel_atual + 1);
}

// Função principal
int mesmo_nivel(TAB *a) {
    int nivel_folha = -1; // -1 significa "ainda não encontrei nenhuma folha"
    return verificar_folhas(a, &nivel_folha, 0);
}
```

---

### 🔍 Passo a passo com exemplo

Vamos usar esta árvore:
```
        20        ← nível 0
       /  \
      10   30     ← nível 1
     / \  / \
    5  15 25  35  ← nível 2 (todas folhas!)
```

| Chamada | Nó | Nível | É folha? | nivel_folha | Retorna |
|---|---|---|---|---|---|
| 1ª | 20 | 0 | Não | -1 | desce |
| 2ª | 10 | 1 | Não | -1 | desce |
| 3ª | 5 | 2 | ✅ Sim | -1 → **vira 2** | 1 |
| 4ª | 15 | 2 | ✅ Sim | 2 == 2 ✓ | 1 |
| 5ª | 30 | 1 | Não | 2 | desce |
| 6ª | 25 | 2 | ✅ Sim | 2 == 2 ✓ | 1 |
| 7ª | 35 | 2 | ✅ Sim | 2 == 2 ✓ | 1 |

Todas as folhas no nível 2 → **retorna 1 ✅**

---

---

## Exercício 4

**Enunciado:** Faça uma função que verifique se uma árvore binária de busca segue o padrão AVL.
**Assinatura:** `int eh_avl(TAB *a);`

---

### 📚 Conceitos importantes antes de resolver

**O que é Fator de Balanceamento (FB)?**
> FB de um nó = altura da subárvore esquerda − altura da subárvore direita

**Regra AVL:**
> Para **todo** nó da árvore, o FB deve estar entre **-1, 0 ou +1**.

Se qualquer nó tiver FB = 2 ou FB = -2 (ou pior), a árvore **não é AVL**.

```
      10          FB(10) = altura(esq) - altura(dir)
     /  \                = 1 - 1 = 0  ✅
    5   15
   /
  3             FB(5) = 1 - 0 = 1  ✅
                FB(15) = 0 - 0 = 0  ✅
                FB(3) = 0 - 0 = 0  ✅
→ É AVL!

      10
     /
    5           FB(10) = 2 - 0 = 2  ❌
   /
  3
→ NÃO é AVL!
```

---

### 💡 Estratégia de solução

1. Criar uma função que calcula a **altura** de um nó
2. Para cada nó, verificar se |FB| ≤ 1
3. Fazer isso **recursivamente** para toda a árvore

```c
// Calcula a altura de um nó
// Retorna -1 se a árvore não for AVL (truque: altura negativa = inválida)
int altura_avl(TAB *a) {
    // Caso base: nó vazio tem altura -1
    if (a == NULL)
        return -1; // convenção: nulo = -1, folha = 0

    // Calcula altura dos filhos
    int alt_esq = altura_avl(a->esquerda);
    int alt_dir = altura_avl(a->direita);

    // Se algum filho já detectou desequilíbrio, propaga o erro
    if (alt_esq == -2 || alt_dir == -2)
        return -2; // código de erro

    // Calcula o fator de balanceamento deste nó
    int fb = alt_esq - alt_dir;

    // Verifica a regra AVL
    if (fb > 1 || fb < -1)
        return -2; // desequilibrado! código de erro

    // Retorna a altura deste nó (maior filho + 1)
    int maior = (alt_esq > alt_dir) ? alt_esq : alt_dir;
    return maior + 1;
}

// Função principal
int eh_avl(TAB *a) {
    // Se altura_avl retornar -2, não é AVL
    // Qualquer outro valor (>= -1) significa que é AVL
    return (altura_avl(a) != -2);
}
```

---

### 🔍 Passo a passo com exemplo

**Árvore balanceada:**
```
      20
     /  \
    10   30
   / \
  5  15
```

| Nó | alt_esq | alt_dir | FB | Válido? | Altura retornada |
|---|---|---|---|---|---|
| 5 | -1 | -1 | 0 | ✅ | 0 |
| 15 | -1 | -1 | 0 | ✅ | 0 |
| 10 | 0 | 0 | 0 | ✅ | 1 |
| 30 | -1 | -1 | 0 | ✅ | 0 |
| 20 | 1 | 0 | **1** | ✅ | 2 |

Nenhum FB violou a regra → **retorna 1 (é AVL) ✅**

**Árvore desbalanceada:**
```
      20
     /
    10
   /
  5
```

| Nó | alt_esq | alt_dir | FB | Válido? |
|---|---|---|---|---|
| 5 | -1 | -1 | 0 | ✅ |
| 10 | 0 | -1 | **1** | ✅ |
| 20 | 1 | -1 | **2** | ❌ |

FB = 2 no nó 20 → retorna -2 → **retorna 0 (não é AVL) ❌**

---

---

## Exercício 5

**Enunciado:** Faça uma função que retorne todos os caminhos que somam `n` em uma árvore binária de busca. Use a biblioteca de lista encadeada e retorne um vetor com todas as listas de caminhos.
**Assinatura:** `TLSE** caminhos(TAB *a, int n);`

---

### 📚 Conceitos importantes antes de resolver

**O que é um caminho?**
> Um caminho é uma sequência de nós da **raiz até uma folha** (ou qualquer nó), passando pelos filhos.

**O que queremos?**
> Encontrar todos os caminhos onde a **soma dos valores dos nós** seja igual a `n`.

**Exemplo:** árvore abaixo, buscando caminhos que somam **25**:
```
        10
       /  \
      5    15
     / \
    3   7
```
- Caminho 10 → 5 → 3 = 18 ❌
- Caminho 10 → 5 → 7 = **22** ❌
- Caminho 10 → 15 = **25** ✅
- Caminho 5 → 3 = 8 ❌

**`TLSE`** é o tipo de lista encadeada da biblioteca. **`TLSE**`** é um vetor de ponteiros para listas.

---

### 💡 Estratégia de solução

Usamos uma técnica chamada **backtracking**:
1. Percorremos a árvore do nó atual em diante
2. Vamos acumulando os nós visitados em uma lista (o "caminho atual")
3. A cada nó, subtraímos seu valor de `n`
4. Se `n` chegar a 0 num nó folha → **encontramos um caminho válido!**
5. Ao voltar da recursão, **removemos** o nó da lista (backtrack)

```c
#include "listaSE.h" // biblioteca de lista encadeada

// Conta quantos caminhos existem (para alocar o vetor)
int contar_caminhos(TAB *a, int n) {
    if (a == NULL) return 0;

    // Chegou ao fim com soma zerada: caminho válido!
    if (a->esquerda == NULL && a->direita == NULL && n == a->valor)
        return 1;

    // Conta nos dois lados, subtraindo o valor atual
    return contar_caminhos(a->esquerda, n - a->valor) +
           contar_caminhos(a->direita,  n - a->valor);
}

// Função auxiliar de busca com backtracking
void buscar(TAB *a, int n, TLSE *atual, TLSE **resultado, int *indice) {
    if (a == NULL) return;

    // Adiciona o nó atual ao caminho
    inserirFinal(atual, a->valor);

    // Subtrai o valor do nó de n
    int resto = n - a->valor;

    // Se é folha e a soma bate: salvamos este caminho!
    if (a->esquerda == NULL && a->direita == NULL && resto == 0) {
        resultado[*indice] = copiarLista(atual); // salva uma cópia
        (*indice)++;
    } else {
        // Continua descendo na árvore
        buscar(a->esquerda, resto, atual, resultado, indice);
        buscar(a->direita,  resto, atual, resultado, indice);
    }

    // BACKTRACK: remove o nó atual antes de voltar
    removerFinal(atual);
}

// Função principal
TLSE** caminhos(TAB *a, int n) {
    // 1. Conta quantos caminhos existem para alocar o vetor
    int total = contar_caminhos(a, n);

    // 2. Aloca o vetor de listas (+ 1 posição NULL como sentinela)
    TLSE **resultado = malloc((total + 1) * sizeof(TLSE*));
    resultado[total] = NULL; // marca o fim do vetor

    // 3. Lista auxiliar que representa o caminho atual
    TLSE *atual = criarLista();

    // 4. Busca todos os caminhos
    int indice = 0;
    buscar(a, n, atual, resultado, &indice);

    // 5. Libera a lista auxiliar
    liberarLista(atual);

    return resultado;
}
```

---

### 🔍 Passo a passo com exemplo

**Árvore:** soma buscada = **25**
```
        10
       /  \
      5    15
     / \
    3   7
```

| Passo | Nó visitado | Lista atual | Resto (n) | É folha? | Soma = 0? |
|---|---|---|---|---|---|
| 1 | 10 | [10] | 25-10=15 | Não | — |
| 2 | 5 | [10,5] | 15-5=10 | Não | — |
| 3 | 3 | [10,5,3] | 10-3=7 | ✅ Sim | 7≠0 ❌ |
| 4 | *backtrack* | [10,5] | — | — | — |
| 5 | 7 | [10,5,7] | 10-7=3 | ✅ Sim | 3≠0 ❌ |
| 6 | *backtrack* | [10] | — | — | — |
| 7 | 15 | [10,15] | 15-15=0 | ✅ Sim | **0=0 ✅** |
| 8 | **Salva** [10,15] | — | — | — | — |

**Resultado:** `[[10, 15]]` — um único caminho que soma 25!

---

### ✅ Resumo dos 3 exercícios

| Exercício | Técnica usada | Ideia central |
|---|---|---|
| 3 - Folhas no mesmo nível | Recursão + variável compartilhada | Guardar o nível da 1ª folha e comparar com as demais |
| 4 - Verificar se é AVL | Recursão + cálculo de altura | Se algum nó tiver FB fora de [-1, 1], não é AVL |
| 5 - Caminhos com soma n | Recursão + Backtracking | Acumular caminho, subtrair valor, salvar se a soma bater |