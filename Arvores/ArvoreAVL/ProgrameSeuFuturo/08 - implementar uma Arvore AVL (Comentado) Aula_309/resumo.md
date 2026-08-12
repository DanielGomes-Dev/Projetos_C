# Resumo da Aula — Teste da Árvore AVL

## 🎯 Objetivo da Aula
Testar na prática o código da Árvore AVL, realizando **inserções**, **remoções** e **impressões** para confirmar que o balanceamento está funcionando corretamente.

---

## 📋 Revisão Rápida do Código

O professor passou rapidamente pelas funções já vistas em aulas anteriores:

- **Estrutura `No`** — valor, ponteiros esquerdo/direito e campo `altura`
- **`novoNo`** — aloca memória e retorna um novo nó inicializado
- **`maior`** — retorna o maior entre dois valores de altura
- **`alturaNo`** — retorna a altura de um nó (ou -1 se for NULL)
- **`fatorDeBalanceamento`** — altura esquerda menos altura direita
- **Rotações** — simples à esquerda, simples à direita, dupla esquerda-direita e dupla direita-esquerda
- **`balancear`** — função separada do inserir e remover para evitar repetição de código, já que **tanto inserção quanto remoção podem desbalancear a árvore**
- **`inserir` e `remover`** — iguais às da árvore binária de busca comum, com duas adições no final: recalcular a altura e chamar `balancear`

---

## 🧪 Testes Realizados

### Teste 1 — Inserção simples (10, 20, 30)
- Inseriu 10, depois 20 (foi para a direita do 10), depois 30
- A árvore ficou **desbalanceada** com fator -2 na raiz (muito pesada à direita)
- A AVL aplicou uma **rotação simples à esquerda**
- Resultado: **20 virou a raiz**, 10 foi para a esquerda e 30 para a direita ✅

---

### Teste 2 — Inserção ordenada (10 ao 90)
Inseriu: 10, 20, 30, 40, 50, 60, 70, 80, 90

Numa árvore sem balanceamento isso viraria uma lista encadeada. Com a AVL, o resultado foi uma árvore **perfeitamente balanceada**:

```
Nível 0 (raiz): 40
Nível 1:        20 | 60
Nível 2:        10 | 30 | 50 | 80
Nível 3:                      70 | 90
```
✅ Balanceamento na inserção confirmado.

---

### Teste 3 — Remoção com rotação simples à esquerda
- Removeu 70 (folha — árvore continua balanceada)
- Removeu 50 — o nó 60 ficou desbalanceado (só tinha filho à direita, o 80 com o 90)
- AVL aplicou **rotação simples à esquerda**
- Resultado: **80 subiu para raiz** e 60 foi para a esquerda do 80 ✅

---

### Teste 4 — Remoção com rotação simples à direita
- Removeu 90, 60 e 80 em sequência
- A árvore ficou desbalanceada pesada à esquerda
- AVL aplicou **rotação simples à direita**
- Resultado: **20 virou a nova raiz**, com 10 à esquerda e 40 à direita (30 filho esquerdo do 40) ✅

---

### Teste 5 — Remoção com rotação dupla
- Removeu 10 — a árvore ficou com 20 na raiz, filho direito 40, e filho esquerdo do 40 era o 30 (formato de "joelho")
- AVL aplicou **rotação dupla**
- Resultado: **30 subiu para raiz**, com 20 à esquerda e 40 à direita ✅

---

### Teste 6 — Remoções finais
- Removeu 30 (raiz) → 20 virou raiz, 40 filho esquerdo
- Removeu 20 → sobrou só o 40
- Removeu 40 → **árvore completamente vazia**
- Tentativa de remover qualquer valor → mensagem "valor não encontrado" ✅

---

## ✅ Conclusão
Todos os tipos de rotação foram testados e funcionaram corretamente:

| Situação | Rotação aplicada | Resultado |
|---|---|---|
| Inserção ordenada 10→20→30 | Simples à esquerda | ✅ |
| Inserção de 10 a 90 | Várias automáticas | ✅ |
| Remoção do 50 | Simples à esquerda | ✅ |
| Remoção de 90, 60 e 80 | Simples à direita | ✅ |
| Remoção do 10 (joelho) | Dupla | ✅ |

A Árvore AVL foi considerada **funcionando perfeitamente**.