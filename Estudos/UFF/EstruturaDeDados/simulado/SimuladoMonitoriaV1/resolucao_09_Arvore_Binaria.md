# SimulEDA P1 — Exercício 9

---

## Enunciado

A estrutura de árvore binária (TAB) possui um campo `prox` que aponta para o **nó ao lado** (mesmo nível, vizinho da direita).

```c
typedef struct arv {
    int info;
    struct arv *esq, *dir, *prox;
} TAB;
```

Crie uma função que receba uma árvore binária e faça as mudanças necessárias para retorná-la **"encadeada"** — ou seja, preencher o campo `prox` de cada nó para apontar para o vizinho do mesmo nível.

**Assinatura:** `TAB* encadeador(TAB* a);`

---

## 📚 Entendendo o problema visualmente

**Antes (Figure A):** os campos `prox` de todos os nós são NULL (ignorados).
```
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

**Depois (Figure B):** cada nó aponta para o vizinho à sua direita no mesmo nível. O último de cada nível aponta para NULL.
```
1 → NULL
2 → 3 → NULL
4 → 5 → 6 → 7 → NULL
```

Ou seja, cada nível vira uma **lista encadeada horizontal**!

---

## 📚 Conceitos importantes antes de resolver

**Por que usar BFS (Busca em Largura)?**

O BFS processa os nós **nível por nível**, que é exatamente o que precisamos! Se processamos todos os nós de um nível juntos, conseguimos encadear um no próximo facilmente.

**Ideia central:**
> Para cada nó num nível, seu `prox` aponta para o próximo nó que entrar na fila — que será exatamente seu vizinho da direita no mesmo nível.

---

## 💡 Estratégia de solução

Vamos usar uma **fila** para fazer o BFS. O truque é:

1. Colocar a raiz na fila
2. Para cada nível, processar todos os nós daquele nível de uma vez
3. Para cada nó do nível, fazer `nó->prox` apontar para o próximo da fila
4. O último nó do nível aponta para `NULL`

```c
TAB* encadeador(TAB* a) {
    // Árvore vazia: nada a fazer
    if (a == NULL) return NULL;

    // Fila simples usando um array de ponteiros
    // (Em produção, usaria a biblioteca de fila)
    TAB *fila[1000];
    int inicio = 0, fim = 0;

    // Coloca a raiz na fila
    fila[fim++] = a;

    while (inicio < fim) {
        // Quantos nós existem NESTE nível?
        int tamanho_nivel = fim - inicio;

        // Processa todos os nós do nível atual
        for (int i = 0; i < tamanho_nivel; i++) {
            TAB *atual = fila[inicio++];

            // Se não é o último do nível: prox aponta para o próximo da fila
            if (i < tamanho_nivel - 1) {
                atual->prox = fila[inicio]; // próximo na fila = vizinho direito
            } else {
                // Último do nível: prox = NULL
                atual->prox = NULL;
            }

            // Adiciona filhos na fila para o próximo nível
            if (atual->esq) fila[fim++] = atual->esq;
            if (atual->dir) fila[fim++] = atual->dir;
        }
    }

    return a;
}
```

---

## 🔍 Passo a passo com o exemplo

**Árvore:**
```
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

---

### Passo 1 — Inicialização
```
Fila: [1]
```
Raiz (1) entra na fila.

---

### Passo 2 — Processando nível 0

`tamanho_nivel = 1` (só o nó 1)

| Nó | É o último do nível? | prox recebe | Filhos adicionados à fila |
|---|---|---|---|
| 1 | ✅ Sim (i=0, tam=1) | NULL | 2, 3 |

```
Após nível 0:   1 → NULL
Fila agora:     [2, 3]
```

---

### Passo 3 — Processando nível 1

`tamanho_nivel = 2` (nós 2 e 3)

| Nó | i | É o último? | prox recebe | Filhos adicionados |
|---|---|---|---|---|
| 2 | 0 | ❌ Não | fila[inicio] = **3** | 4, 5 |
| 3 | 1 | ✅ Sim | NULL | 6, 7 |

```
Após nível 1:   2 → 3 → NULL
Fila agora:     [4, 5, 6, 7]
```

---

### Passo 4 — Processando nível 2

`tamanho_nivel = 4` (nós 4, 5, 6, 7)

| Nó | i | É o último? | prox recebe | Filhos |
|---|---|---|---|---|
| 4 | 0 | ❌ Não | **5** | nenhum |
| 5 | 1 | ❌ Não | **6** | nenhum |
| 6 | 2 | ❌ Não | **7** | nenhum |
| 7 | 3 | ✅ Sim | NULL | nenhum |

```
Após nível 2:   4 → 5 → 6 → 7 → NULL
Fila agora:     [] (vazia, fim!)
```

---

### Resultado final

```
Nível 0:  1 ──────────────────→ NULL
Nível 1:  2 ──────→ 3 ────────→ NULL
Nível 2:  4 → 5 → 6 → 7 ──────→ NULL
```

Exatamente como mostrado na **Figure B** do enunciado! ✅

---

## 🧠 Por que o truque `fila[inicio]` funciona?

Quando estamos processando o nó `atual` e queremos saber quem é o seu vizinho da direita, basta olhar o **próximo elemento da fila** — porque o BFS garante que os nós de um mesmo nível ficam em sequência na fila!

```
Fila no nível 1:  [2, 3]
                   ↑  ↑
               atual  próximo = vizinho direito de 2!
```

Isso só funciona porque adicionamos os filhos **depois** de processar o nó atual — os filhos vão pro nível seguinte, não interferem no nível atual.

---

## ✅ Resumo

| Conceito | Detalhe |
|---|---|
| Algoritmo usado | BFS (Busca em Largura) |
| Por que BFS? | Processa nó por nó dentro do mesmo nível |
| Truque principal | O próximo na fila = vizinho direto no mesmo nível |
| Último de cada nível | `prox = NULL` |
| Complexidade | O(n) — visita cada nó exatamente uma vez |