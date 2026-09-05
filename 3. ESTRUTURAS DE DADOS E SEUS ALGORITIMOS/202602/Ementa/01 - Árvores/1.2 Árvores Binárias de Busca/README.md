# 1.2 Árvores Binárias de Busca (BST)

## Objetivo de aprendizagem

- Enunciar a propriedade de BST e explicar por que ela permite busca eficiente.
- Implementar busca, inserção e remoção (os 3 casos de remoção).
- Explicar por que uma BST pode degenerar para O(n) no pior caso e o que isso motiva (AVL, 1.3).

## Roteiro de leitura

- **SZ (livro-base):** capítulo/seção "Árvores Binárias de Busca" (conferir página exata) — cobre a propriedade, operações e análise de complexidade no caso médio vs. pior caso.
- **CO (Cormen):** cap. 12 "Árvores Binárias de Busca" — é a referência mais rigorosa para prova de corretude dos algoritmos de busca/inserção/remoção e para a análise de que a altura esperada de uma BST construída com inserções aleatórias é O(log n) (conferir página exata).
- **CE (Celes):** capítulo de árvores binárias de busca com implementação completa em C — usar para a fase de codar (structs, funções recursivas de busca/inserção/remoção) (conferir página exata).
- **KR:** não precisa de capítulo específico além do já citado em 1.1 (structs e ponteiros); a lógica de remoção com sucessor costuma ser o ponto onde vale revisar ponteiros duplos (`Nó **`) se a implementação usar esse padrão.

## Notas de estudo elaboradas

### Propriedade de BST

Para todo nó *n*: todas as chaves na subárvore esquerda de *n* são menores que a chave de *n*, e todas as chaves na subárvore direita são maiores (assumindo chaves distintas — tratamento de duplicatas é uma decisão de projeto, geralmente vão para a direita por convenção).

Essa propriedade é o que faz o **percurso em-ordem** produzir as chaves em ordem crescente.

### Operações

**Busca(nó, chave):** compara chave com a do nó atual; se igual, achou; se menor, desce à esquerda; se maior, desce à direita. Recursiva ou iterativa, ambas O(h) onde h é a altura da árvore.

**Inserção(chave):** faz uma busca até achar uma posição nula (folha "vazia") e insere ali. Sempre insere como folha nova — nunca no meio da árvore.

**Remoção(chave):** 3 casos:
1. **Nó folha** — remove diretamente (aponta o pai para NULL).
2. **Nó com um filho** — substitui o nó pelo seu único filho (o pai passa a apontar para o filho, "pulando" o nó removido).
3. **Nó com dois filhos** — não dá para simplesmente remover; substitui a chave do nó pelo **sucessor** (menor chave da subárvore direita, achado descendo sempre à esquerda a partir do filho direito) ou pelo **predecessor** (maior chave da subárvore esquerda), e então remove o sucessor/predecessor de sua posição original (que cai em caso 1 ou 2, nunca em caso 3, porque sucessor/predecessor tem no máximo um filho).

### Complexidade

| Operação | Caso médio (árvore aleatória) | Pior caso |
|---|---|---|
| Busca | O(log n) | O(n) |
| Inserção | O(log n) | O(n) |
| Remoção | O(log n) | O(n) |

O pior caso O(n) acontece quando a árvore **degenera** para algo equivalente a uma lista encadeada — por exemplo, inserindo chaves já ordenadas (1, 2, 3, 4, 5...) em uma BST sem balanceamento: cada nó novo vira filho direito do anterior, e a altura vira n em vez de log n.

Essa degeneração é exatamente o problema que a árvore AVL (1.3) resolve, forçando balanceamento após cada inserção/remoção.

### Passo a passo: inserção e remoção com um exemplo concreto

Inserindo, nesta ordem, `10, 5, 15, 3, 7, 12`:

```
insere 10 → raiz
insere 5  → 5 < 10, vira filho esquerdo de 10
insere 15 → 15 > 10, vira filho direito de 10
insere 3  → 3 < 10 (esq), 3 < 5 (esq), vira filho esquerdo de 5
insere 7  → 7 < 10 (esq), 7 > 5 (dir), vira filho direito de 5
insere 12 → 12 > 10 (dir), 12 < 15 (esq), vira filho esquerdo de 15
```

Árvore final:
```
            10
          /    \
         5      15
        / \     /
       3   7  12
```
Em-ordem confirma a propriedade de BST: `3, 5, 7, 10, 12, 15` (ordem crescente).

Agora **remova 5** (caso 3 — dois filhos): pega o sucessor (menor da subárvore direita de 5, que é `7`, já que `5→dir = 7` e `7` não tem filho esquerdo), copia `7` para o lugar de `5`, e remove o `7` original de sua posição (que é caso 1, folha, remoção trivial):
```
            10
          /    \
         7      15
        /       /
       3      12
```

E se removêssemos usando o **predecessor** em vez do sucessor? Pegaria o maior da subárvore esquerda de 5, que é `3` — o resultado seria estruturalmente diferente (raiz da subárvore esquerda vira `3`, não `7`), mas igualmente válido como BST. A implementação de `TABB_retira` (ver "Exemplos em C" abaixo) usa o **predecessor**.

## Exemplos em C

Trecho abaixo adaptado de uma implementação real e testada de BST, disponível completa em `ListasExercicios/lista02-EDA/TABB/` (`TABB.h` + `TABB.c`).

```c
// TABB.h
typedef struct arvbinbusca {
  int info;
  struct arvbinbusca *esq, *dir;
} TABB;

TABB *TABB_inicializa(void);
TABB *TABB_cria(int raiz, TABB *esq, TABB *dir);
TABB *TABB_busca(TABB *a, int elem);
TABB *TABB_insere(TABB *a, int elem);
TABB *TABB_retira(TABB *a, int info);
```

```c
// TABB.c

// Busca aproveita a propriedade de BST: a cada passo elimina metade
// da árvore (no caso balanceado) — O(h), h = altura.
TABB *TABB_busca(TABB *a, int elem) {
  if ((!a) || (a->info == elem)) return a;
  if (a->info > elem) return TABB_busca(a->esq, elem);
  return TABB_busca(a->dir, elem);
}

// Inserção: desce como uma busca até achar posição vazia (NULL) e cria o nó ali.
// Retorna a subárvore (com o novo nó já ligado) para o pai reatribuir seu ponteiro —
// é o padrão "retorna a raiz da subárvore modificada", evita precisar de ponteiro duplo.
TABB *TABB_insere(TABB *a, int elem) {
  if (!a) return TABB_cria(elem, NULL, NULL);
  if (a->info > elem) a->esq = TABB_insere(a->esq, elem);
  else if (a->info < elem) a->dir = TABB_insere(a->dir, elem);
  return a;
}

// Remoção com os 3 casos clássicos.
TABB *TABB_retira(TABB *a, int info) {
  if (!a) return a;
  if (info < a->info)
    a->esq = TABB_retira(a->esq, info);
  else if (info > a->info)
    a->dir = TABB_retira(a->dir, info);
  else { // achou o nó a remover
    if ((!a->esq) && (!a->dir)) {           // CASO 1: folha
      free(a);
      a = NULL;
    }
    else if ((!a->esq) || (!a->dir)) {      // CASO 2: um filho só
      TABB *temp = a;
      a = a->esq ? a->esq : a->dir;         // "pula" o nó removido
      free(temp);
    }
    else {                                  // CASO 3: dois filhos → usa o PREDECESSOR
      TABB *filho = a->esq;
      while (filho->dir) filho = filho->dir;  // maior da subárvore esquerda
      a->info = filho->info;                  // copia o valor do predecessor
      filho->info = info;                     // "marca" o antigo p/ a recursão remover
      a->esq = TABB_retira(a->esq, info);     // remove o predecessor (cai em caso 1 ou 2)
    }
  }
  return a;
}
```

Código completo e testado em `ListasExercicios/lista02-EDA/TABB/`. Note que esta implementação escolheu o **predecessor** para o caso de dois filhos — o sucessor (menor da subárvore direita) é a alternativa simétrica, igualmente correta, mais comum nos livros-texto.

## Pontos de atenção / pegadinhas comuns de prova

- BST sem balanceamento **não garante** O(log n) — isso só vale no caso médio com inserções aleatórias. Prova costuma cobrar o pior caso separadamente.
- No caso de remoção com dois filhos, tanto usar sucessor quanto predecessor está correto — mas seja consistente dentro da mesma questão/implementação.
- Duplicatas: decida e documente a convenção (geralmente vão para a subárvore direita) — provas às vezes testam se você trata esse caso.
- Busca em BST é O(h), não O(log n) diretamente — só é O(log n) quando a árvore está balanceada. Confundir h (altura real) com log n (altura mínima possível) é um erro comum.

## Anotações pessoais

## Exercícios resolvidos
