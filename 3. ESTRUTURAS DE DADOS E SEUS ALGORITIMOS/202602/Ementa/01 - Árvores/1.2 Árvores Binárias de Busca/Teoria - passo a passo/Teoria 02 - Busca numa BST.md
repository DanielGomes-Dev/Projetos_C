# Teoria 02 — Busca numa BST: usando a ordem para nunca olhar os dois lados

> **Onde isto entra:** é a razão de existir da BST — transformar busca O(n) em busca
> proporcional à altura da árvore.
> **Antes:** [[Teoria 01 - A propriedade de árvore binária de busca]].
> **Fonte:** `lista02-EDA/06_ArvoresBinariasBusca.pdf`, pág. 7.

## 1. A ideia em uma frase

Como toda subárvore respeita "esquerda menor, direita maior" (Teoria 01), buscar um valor
é decidir, em cada nó, **um único lado** para continuar — nunca os dois.

## 2. O código — comparado lado a lado com a busca de 1.1

```c
// 1.1 — força bruta, sem ordenação: precisa tentar os dois lados
TAB *busca(TAB *a, int info) {
  if ((!a) || (a->info == info)) return a;
  TAB *resp = busca(a->esq, info);
  if (resp) return resp;
  return busca(a->dir, info);
}

// 1.2 — usando a propriedade de BST
TAB *busca_ABB(TAB *a, int info) {
  if ((!a) || (a->info == info)) return a;
  if (a->info > info)
    return busca_ABB(a->esq, info);
  return busca_ABB(a->dir, info);
}
```

> 📖 **Lendo `busca_ABB` devagar, comparando com `busca`:**
> 1. `if ((!a) || (a->info == info)) return a;` — **igual** à versão força bruta: parada por
>    árvore vazia ou valor achado.
> 2. `if (a->info > info) return busca_ABB(a->esq, info);` — **a diferença central**: se o
>    nó atual é maior que o que eu procuro, e a BST garante que tudo à **direita** é ainda
>    maior, então **não adianta olhar a direita** — o valor, se existir, só pode estar à
>    esquerda.
> 3. `return busca_ABB(a->dir, info);` — só chega aqui se `a->info <= info` (e já não é
>    igual, pelo passo 1) — ou seja, `a->info < info`, e por BST tudo à esquerda é ainda
>    menor, então só resta a direita.
> 4. **Note:** não existe `if (resp) ...` como na força bruta — não há "tentar os dois e ver
>    qual funcionou", porque só **um** dos dois pode conter a resposta.

## 3. Conferindo com a árvore de referência

```
              500
           /       \
         300         800
        /   \       /   \
      150   400   600   900
```

**Busca de `600`:**
> | Passo | Nó atual | Comparação | Decisão |
> |---|---|---|---|
> | 1 | `500` | `500 < 600` (não é `>`) | vai para a **direita** |
> | 2 | `800` | `800 > 600` | vai para a **esquerda** |
> | 3 | `600` | `600 == 600` | **achou**, retorna o nó |

3 comparações — e note que **nunca** olhou `300`, `150`, `400` ou `900`: metade da árvore
foi descartada de cara ao ir para a direita no passo 1.

## 4. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `if (a->info > info)` | pergunto "o que eu procuro é menor que aqui?" — se sim, uso a garantia de BST para eliminar o lado direito inteiro sem olhar nele |
| só uma chamada recursiva (nunca as duas) | decido, decido de vez — diferente da força bruta, aqui não existe "tentar os dois e ver qual deu certo" |
| parar em `!a` | cheguei numa subárvore vazia sem achar — o valor não está na árvore |

## 5. Exercícios de fixação

Usando a árvore de referência da seção 3:

1. Faça o trace de `busca_ABB` procurando `150`. Quantas comparações?
2. Faça o trace procurando `700`. O que acontece quando a busca chega numa subárvore vazia?
3. Por que a versão `busca_ABB` **não pode** ser usada numa árvore binária qualquer (sem a
   propriedade de BST, como as de 1.1)?

### Gabarito

1. `500`: `500 > 150` → esquerda. `300`: `300 > 150` → esquerda. `150`: achou. 3
   comparações.
2. `500`: `500<700`→direita. `800`: `800>700`→esquerda. `600`: `600<700`→direita. Chega em
   `NULL` (subárvore vazia à direita de `600`) → `busca_ABB(NULL, 700)` cai no
   `if ((!a) || ...)`, retorna `NULL` (não achou).
3. Porque o algoritmo **assume** que "menor está à esquerda, maior à direita" para decidir
   qual lado descartar — numa árvore sem essa garantia, o valor procurado poderia estar do
   lado que o algoritmo decidiu ignorar, e a busca erraria silenciosamente (diria "não
   encontrado" mesmo que o valor exista, só que do lado errado).

## Resumo

- `busca_ABB` decide **um único lado** em cada nó, usando a comparação com a chave atual —
  nunca tenta os dois.
- Isso só é seguro **porque** a propriedade de BST (Teoria 01) garante onde cada valor pode
  estar.
- Custo: proporcional à altura da árvore percorrida, não ao número total de nós — mas isso
  só é bom se a árvore for balanceada (ver Teoria 05).

**Próximo:** [[Teoria 03 - Inserção numa BST]].
