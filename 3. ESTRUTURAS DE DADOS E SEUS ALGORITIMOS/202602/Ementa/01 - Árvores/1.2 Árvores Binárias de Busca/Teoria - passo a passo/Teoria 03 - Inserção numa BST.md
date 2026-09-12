# Teoria 03 — Inserção numa BST: sempre vira folha nova

> **Onde isto entra:** como construir uma BST elemento por elemento, mantendo a propriedade
> da Teoria 01 a cada inserção.
> **Antes:** [[Teoria 02 - Busca numa BST]].
> **Fonte:** `lista02-EDA/06_ArvoresBinariasBusca.pdf`, págs. 9–12.

## 1. A ideia em uma frase

Inserir um valor numa BST é **repetir a lógica da busca** até cair numa posição vazia — e
colocar o valor novo ali, sempre como **folha**.

## 2. Por que "sempre vira folha" (motivação antes do código)

Se o valor não está na árvore, a busca da Teoria 02 eventualmente chega numa subárvore
vazia (`NULL`) — foi exatamente ali que ela "desistiu". Esse é o **único** lugar onde o
valor novo pode entrar sem violar a ordem de ninguém: qualquer outro lugar exigiria
reorganizar nós já existentes.

## 3. O código — lido devagar

```c
TAB *insere_ABB(TAB *a, int info) {
  if (!a) return cria(info, NULL, NULL);
  if (info < a->info)
    a->esq = insere_ABB(a->esq, info);
  else if (info > a->info)
    a->dir = insere_ABB(a->dir, info);
  return a;
}
```

> 📖 **Lendo devagar:**
> 1. `if (!a) return cria(info, NULL, NULL);` — **caso base**: achou o lugar vazio certo —
>    cria um nó novo aqui, folha (sem filhos), e devolve.
> 2. `if (info < a->info) a->esq = insere_ABB(a->esq, info);` — se o valor é menor, ele
>    **tem** que ir para a subárvore esquerda (senão quebraria a BST) — chama recursivamente
>    lá, e **reconecta** o resultado em `a->esq` (importante: mesmo quando `a->esq` já não
>    era `NULL`, essa atribuição não faz mal — a função devolve a mesma subárvore, só que
>    com o novo nó inserido dentro dela).
> 3. `else if (info > a->info) ...` — espelhado à direita.
> 4. **Não há `else` para "valor igual"** — o código do slide assume chaves distintas (ver
>    letra miúda da Teoria 01); se o valor já existe, nenhum dos dois `if` dispara e a
>    função só devolve `a` sem alterar nada.
> 5. `return a;` — devolve a raiz da subárvore (inalterada em valor, só possivelmente com
>    mais um descendente).

## 4. Conferindo: construindo uma BST do zero, passo a passo

O slide (pág. 10-12) usa o exercício de inserir, numa BST inicialmente vazia:
`25, 22, 40, 30, 45, 27, 20, 21, 48`.

> **Trace, inserção por inserção:**
>
> | Inserir | Caminho até o lugar vazio | Árvore depois |
> |---|---|---|
> | `25` | (vazia) → raiz | `25` |
> | `22` | `25`: `22<25`→esq (vazia) | `25` com esq `22` |
> | `40` | `25`: `40>25`→dir (vazia) | `25`(esq `22`, dir `40`) |
> | `30` | `25`:`30>25`→dir(`40`); `40`:`30<40`→esq(vazia) | `30` entra como esq de `40` |
> | `45` | `25`→dir(`40`); `40`:`45>40`→dir(vazia) | `45` entra como dir de `40` |
> | `27` | `25`→esq(`22`); `22`:`27>22`→dir(vazia) | `27` entra como dir de `22` |
> | `20` | `25`→esq(`22`); `22`:`20<22`→esq(vazia) | `20` entra como esq de `22` |
> | `21` | `25`→esq(`22`)→esq(`20`); `20`:`21>20`→dir(vazia) | `21` entra como dir de `20` |
> | `48` | `25`→dir(`40`)→dir(`45`); `45`:`48>45`→dir(vazia) | `48` entra como dir de `45` |

Árvore final:
```
                25
             /      \
           22         40
          /  \       /  \
        20    27   30    45
          \                \
           21                48
```

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| descer comparando `info < a->info` / `>` | executo a **mesma lógica de decisão** da busca — inserção é "buscar até falhar" |
| `return cria(...)` no caso base | o novo valor sempre nasce **folha** — nunca aparece "no meio" da árvore empurrando outros nós |
| `a->esq = insere_ABB(a->esq, info)` | reconecto o ponteiro mesmo quando ele "não muda de fato" — é assim que a mudança lá embaixo (a folha nova) se propaga de volta até a raiz |

## 6. Letra miúda

**A ordem de inserção muda a forma da árvore.** Compare: inserir `25,22,40,30,45,27,20,21,48`
(acima) produz uma árvore diferente de inserir os mesmos 9 valores em outra ordem — o
slide (pág. 11-12) mostra isso com `40,25,20,30,45,27,22,21,48`, que produz uma árvore mais
alta de um lado. Mesmo conjunto de valores, formas diferentes — é o que abre espaço para o
problema tratado na Teoria 05 (e resolvido pela AVL, em 1.3).

## 7. Exercícios de fixação

1. Insira, numa BST vazia, os valores `10, 5, 15, 3, 7` nessa ordem. Desenhe o resultado.
2. Insira os mesmos valores da questão 1, mas na ordem `3, 5, 7, 10, 15`. Compare as formas.
3. Ao inserir um valor que **já existe** na árvore, o que o código faz? Isso é sempre o
   comportamento desejado?

### Gabarito

1.
   ```
        10
       /  \
      5    15
     / \
    3   7
   ```
2.
   ```
   3
    \
     5
      \
       7
        \
         10
          \
           15
   ```
   Mesmos 5 valores, formas radicalmente diferentes — a segunda é uma "fila" (altura 4), a
   primeira é balanceada (altura 2).
3. Nenhum dos dois `if` (`<` ou `>`) dispara, então a função só devolve `a` sem criar nada
   novo — a inserção de um duplicado é silenciosamente ignorada. Se a aplicação precisar
   contar repetições ou substituir dados associados, esse comportamento precisa ser
   alterado explicitamente (não é o que este código faz).

## Resumo

- Inserção reaproveita a lógica de busca (Teoria 02); o valor novo sempre entra como
  **folha**, no primeiro lugar vazio encontrado no caminho.
- A ordem de inserção determina a forma final da árvore — o mesmo conjunto de valores pode
  gerar árvores balanceadas ou degeneradas (fila), dependendo só da ordem.
- O código deste curso não trata duplicatas — inserir um valor repetido não faz nada.

**Próximo:** [[Teoria 04 - Remoção numa BST (os três casos)]].
