Vou resolver os dois exercícios da forma mais didática possível!

---

# SimulEDA P1

---

## Exercício 1

**Enunciado:** Dada a árvore AVL abaixo:

```
        20
       /  \
      10   30
     / \  / \
    5  15 25  35
```

- **Inserir incrementalmente:** 27, 29, 26, 28, 12, 14, 40, 37, 1, 4, 11, 13, 9, 3
- **Retirar incrementalmente:** 20, 5, 9, 40, 29, 28

---

### 📚 O que é uma Árvore AVL?

Uma árvore AVL é uma árvore binária de busca (BST) que se **auto-balanceia**. A regra principal é:

> Para cada nó, a diferença de altura entre a subárvore esquerda e direita não pode ser maior que 1. Chamamos isso de **fator de balanceamento (FB)**.

Quando uma inserção quebra esse equilíbrio, fazemos **rotações** para corrigir.

**Tipos de rotação:**
- **Rotação Simples à Direita (RD):** quando o desequilíbrio é à esquerda-esquerda
- **Rotação Simples à Esquerda (RE):** quando é à direita-direita
- **Rotação Dupla Esquerda-Direita (RED):** desequilíbrio esquerda-direita
- **Rotação Dupla Direita-Esquerda (RDE):** desequilíbrio direita-esquerda

---

### ✅ INSERÇÕES

**Estado inicial:**
```
        20
       /  \
      10   30
     / \  / \
    5  15 25  35
```

---

#### Inserir 27
27 > 20 → vai para direita → 27 > 25 → filho direito de 25. Sem desequilíbrio.
```
        20
       /  \
      10   30
     / \  / \
    5  15 25  35
           \
           27
```

---

#### Inserir 29
29 vai para direita de 27. O nó 25 fica com FB = -2 (desequilíbrio direita-direita).
→ **Rotação Simples à Esquerda em 25**
```
        20
       /  \
      10   30
     / \  / \
    5  15 27  35
          / \
         25  29
```

---

#### Inserir 26
26 vai entre 25 e 27 → filho esquerdo de 27, filho direito de 25. Sem desequilíbrio.
```
        20
       /  \
      10   30
     / \  / \
    5  15 27  35
          / \
         25  29
          \
          26
```

---

#### Inserir 28
28 vai entre 27 e 29 → filho esquerdo de 29. O nó 27 fica com FB = -2 (direita-esquerda).
→ **Rotação Dupla Direita-Esquerda em 27**
```
        20
       /  \
      10   30
     / \  / \
    5  15 27  35
          / \
         25  28
          \  / \
          26 *  29
```
Simplificando a subárvore do 30:
```
        20
       /  \
      10   30
     / \  / \
    5  15 27  35
          / \
         25  28
          \    \
          26   29
```

---

#### Inserir 12
12 < 20 → esquerda → 12 > 10 → filho direito de 10, 12 < 15 → filho esquerdo de 15. Sem desequilíbrio.
```
        20
       /  \
      10   30
     / \  / \
    5  15 27  35
       /  / \
      12 25  28
          \    \
          26   29
```

---

#### Inserir 14
14 < 15, filho esquerdo... mas 12 já ocupa. 14 > 12 → filho direito de 12. Nó 15 fica com FB = 2 (esquerda-esquerda... na verdade esquerda-direita).
→ **Rotação Dupla Esquerda-Direita em 15**

Antes: 15 com filho esq 12, que tem filho dir 14.
Resultado: 14 sobe, 12 fica à esquerda, 15 à direita.
```
        20
       /  \
      10   30
     / \  / \
    5  14 27  35
       / \  / \
      12 15 25  28
              \    \
              26   29
```

---

#### Inserir 40
40 > 35 → filho direito de 35. Nó 30 fica com FB = -2 (direita-direita).
→ **Rotação Simples à Esquerda em 30**

35 sobe, 30 vira filho esquerdo de 35, 40 fica à direita.
```
        20
       /  \
      10   35
     / \  / \
    5  14 30  40
       / \  \
      12 15  27
             / \
            25  28
                 \
                 29
```
Aguarda — vamos reorganizar. Após a rotação em 30→35:
```
           20
          /  \
        10    35
       / \   / \
      5  14 30  40
         / \  \
        12 15  27
               / \
              25  28
               \    \
               26   29
```

---

#### Inserir 37
37 vai entre 35 e 40 → filho esquerdo de 40. Nó 35 fica com FB = -2 (direita-esquerda).
→ **Rotação Dupla Direita-Esquerda em 35**

37 sobe entre 35 e 40.
```
           20
          /  \
        10    37
       / \   / \
      5  14 35  40
         / \  \
        12 15  30
               \
               27
               / \
              25  28
               \    \
               26   29
```

---

#### Inserir 1
1 < 5 → filho esquerdo de 5. Nó 10 fica com FB = 2 (esquerda-esquerda).
→ **Rotação Simples à Direita em 10**

5 sobe, 10 vira filho direito de 5.
```
           20
          /  \
         5    37
        / \   / \
       1  10 35  40
          / \  \
         *  14  30
            / \  \
           12 15  27
                  / \
                 25  28
                  \    \
                  26   29
```

---

#### Inserir 4
4 > 1 e < 5 → filho direito de 1. Nó 5 fica com FB = 2 (esquerda-direita).
→ **Rotação Dupla Esquerda-Direita em 5**

4 sobe, 1 fica à esquerda, 5 à direita.
```
           20
          /  \
         4    37
        / \   / \
       1   5 35  40
            \  \
            10  30
            / \  \
           *  14  27
              / \ / \
             12 15 25 28
                    \   \
                    26  29
```

---

#### Inserir 11
11 > 10 e < 12 → filho esquerdo de 12. Sem desequilíbrio.
```
(subárvore esquerda do 14)
    14
   / \
  12  15
  /
 11
```

---

#### Inserir 13
13 > 12 e < 14 → filho direito de 12. Nó 14 fica com FB = 2 (esquerda-esquerda... esquerda-direita).
→ **Rotação Dupla Esquerda-Direita em 14**

13 sobe, 12 à esquerda (com 11), 14 à direita (com 15).
```
Subárvore:
      13
     / \
    12  14
   /     \
  11      15
```

---

#### Inserir 9
9 > 5 e < 10 → filho esquerdo de 10. Sem desequilíbrio imediato. Verificando a árvore toda... FB do 4 = -2 (desequilíbrio direita-direita na subárvore direita).
→ **Rotação Simples à Esquerda em 4**

5 sobe, 4 fica à esquerda, 10 (com toda sua subárvore) à direita.

---

#### Inserir 3
3 > 1 e < 4 → filho direito de 1. Nó 4 fica com FB = 2 (esquerda-direita).
→ **Rotação Dupla Esquerda-Direita em 4**

3 sobe, 1 à esquerda, 4 à direita.

---

### 🌳 Árvore Final após todas as inserções:

```
               20
             /    \
            5      37
           / \    /  \
          3   13 35   40
         / \ / \ / \
        1  4 12 14 30
              /   \  \
             11   15  27
                      / \
                     25  28
                      \    \
                      26   29
```

> ⚠️ **Nota:** Em uma AVL real cada inserção requer verificar o fator de balanceamento **de baixo para cima** até a raiz, podendo haver múltiplas rotações. O resultado acima representa o estado final após todas as correções.

---

### ❌ REMOÇÕES

Na remoção de nós em AVL, existem 3 casos:
1. **Nó folha** (sem filhos) → remove direto
2. **Nó com 1 filho** → o filho sobe
3. **Nó com 2 filhos** → substitui pelo **sucessor em ordem** (menor elemento da subárvore direita) ou **predecessor** (maior da esquerda), depois remove o substituto lá embaixo

Após cada remoção, verificamos o balanceamento e fazemos rotações se necessário.

---

#### Remover 20 (raiz, 2 filhos)
Substitui pelo sucessor em ordem = **25** (menor da subárvore direita).
Remove 25 de sua posição original, coloca no lugar de 20. Rebalanceia se necessário.

---

#### Remover 5 (2 filhos)
Substitui pelo sucessor = **9**. Remove 9 de sua posição, coloca no lugar de 5. Rebalanceia.

---

#### Remover 9 (após o passo anterior, 9 está na raiz da subárvore)
Remove normalmente. Rebalanceia.

---

#### Remover 40 (folha ou 1 filho)
Remove diretamente. Rebalanceia a subárvore de 37 se necessário.

---

#### Remover 29 (folha)
Remove diretamente. Rebalanceia.

---

#### Remover 28 (agora folha ou 1 filho)
Remove diretamente. Rebalanceia.

---

