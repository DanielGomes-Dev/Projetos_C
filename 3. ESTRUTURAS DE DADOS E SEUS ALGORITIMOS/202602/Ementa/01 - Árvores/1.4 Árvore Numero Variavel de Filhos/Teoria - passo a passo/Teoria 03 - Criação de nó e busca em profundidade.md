# Teoria 03 — Criação de nó e busca em profundidade

> **Onde isto entra:** as duas primeiras operações da lista pedida em `conteudo.md`: "(a)
> criação de um nó" e "(b) busca em profundidade de uma informação nesta árvore".
> **Antes:** [[Teoria 02 - Definição por lista de filhos (prim_filho e prox_irmao)]].
> **Fonte:** código real em `TAVAR/TAV.c`; comparar com `arvv_cria`/`arvv_pertence` do
> Celes (págs. 201-203).

## 1. A ideia em uma frase

Criar um nó é só alocar e zerar os dois ponteiros (o nó nasce como uma folha isolada);
buscar uma informação é percorrer a árvore **testando a raiz primeiro, depois cada filho,
recursivamente**, até achar ou esgotar todos os nós.

## 2. Criação de um nó — `TAV_cria`

```c
TAV* TAV_cria (int raiz){
  TAV *novo = (TAV *) malloc(sizeof(TAV));
  novo->info = raiz;
  novo->prim_filho = novo->prox_irmao = NULL;
  return novo;
}
```

> **Lendo devagar:**
> - `malloc(sizeof(TAV))` — pede ao sistema um bloco de memória do tamanho exato de um
>   `TAV` (um `int` + 2 ponteiros) e devolve o **endereço** desse bloco.
> - `novo->prim_filho = novo->prox_irmao = NULL;` — atribuição encadeada: primeiro
>   `novo->prox_irmao = NULL`, depois `novo->prim_filho` recebe o **resultado** dessa
>   atribuição (que também é `NULL`). Equivale a escrever as duas atribuições em linhas
>   separadas; é só mais compacto.
> - Depois de criado, o nó é uma **folha isolada**: sem filhos (`prim_filho == NULL`) e sem
>   irmão (`prox_irmao == NULL`) — ele só passa a fazer parte de uma árvore maior quando
>   [[Teoria 04 - Inserção na árvore variável|`TAV_insere`]] o encadear a um pai.

Compare com o Celes (`arvv_cria`): mesmíssima lógica, só com nomes de campos abreviados
(`prim`, `prox` em vez de `prim_filho`, `prox_irmao`) e `char` no lugar de `int` para a
informação.

**Complexidade:** `O(1)` — uma alocação e duas atribuições, não importa o tamanho da
árvore.

## 3. Busca em profundidade — `TAV_busca`

```c
TAV* TAV_busca (TAV *a, int info){
  if(a->info == info) return a;
  TAV *p;
  for(p = a->prim_filho; p; p = p->prox_irmao){
    TAV *resp = TAV_busca(p, info);
    if(resp) return resp;
  }
  return NULL;
}
```

> **Lendo devagar, de dentro pra fora:**
> - `if(a->info == info) return a;` — primeiro testa a **própria raiz** (do nó/subárvore
>   `a`, que aqui pode ser a árvore inteira ou qualquer subárvore, já que a função é
>   recursiva). Se bater, já devolve o próprio nó — não precisa olhar os filhos.
> - `for(p = a->prim_filho; p; p = p->prox_irmao)` — percorre a **lista de filhos** de `a`,
>   um a um: começa em `a->prim_filho`; a condição de parada `p` (verdadeiro enquanto `p`
>   não for `NULL`) é o "enquanto ainda houver irmão"; `p = p->prox_irmao` avança para o
>   próximo filho a cada volta.
> - `TAV *resp = TAV_busca(p, info);` — a **chamada recursiva**: busca `info` dentro de
>   toda a subárvore enraizada no filho `p` (que, por sua vez, vai testar `p` e depois os
>   filhos de `p`, e assim por diante — profundidade primeiro, um ramo inteiro antes do
>   próximo).
> - `if(resp) return resp;` — se a busca dentro dessa subárvore **já achou** a informação
>   (retornou um ponteiro não-`NULL`), a função para imediatamente e propaga esse resultado
>   para cima, **sem olhar os irmãos seguintes** — é um "short-circuit": achou, não precisa
>   continuar procurando.
> - `return NULL;` — só é alcançado se nenhum filho (nem as subárvores deles) continha a
>   informação.

### Conferindo com uma árvore concreta

Considere a árvore já construída (a construção via `TAV_insere` é o assunto da Teoria 04;
aqui ela já está pronta):

```
              1
        ┌─────┼─────┐
        4      3      2
        │            ┌─┴─┐
        7            6   5
```

Ou seja: `1->prim_filho = 4`, `4->prox_irmao = 3`, `3->prox_irmao = 2`; `4->prim_filho = 7`;
`2->prim_filho = 6`, `6->prox_irmao = 5`.

**Chamando `TAV_busca(raiz=1, 6)`** — trace completo:

1. `busca(1, 6)`: `1 != 6`. Entra no `for`, `p = 4`.
2. `busca(4, 6)`: `4 != 6`. Entra no `for`, `p = 7`.
3. `busca(7, 6)`: `7 != 6`. `7->prim_filho == NULL` → o `for` nem executa. `return NULL`.
4. De volta em `busca(4,...)`: `resp = NULL`, não retorna ainda. `p = 7->prox_irmao = NULL`
   → `for` termina. `return NULL`.
5. De volta em `busca(1,...)`: `resp = NULL` (veio da chamada com `4`). `p = 4->prox_irmao = 3`.
6. `busca(3, 6)`: `3 != 6`, sem filhos, `return NULL`.
7. De volta em `busca(1,...)`: `resp = NULL`. `p = 3->prox_irmao = 2`.
8. `busca(2, 6)`: `2 != 6`. Entra no `for`, `p = 6`.
9. `busca(6, 6)`: `6 == 6` → **`return a`** (o próprio nó `6`), imediatamente, sem olhar
   filhos de `6`.
10. De volta em `busca(2,...)`: `resp` = ponteiro para o nó `6`, que é **verdadeiro** →
    `return resp` imediatamente. **Nunca chega a testar o irmão `5`.**
11. De volta em `busca(1,...)`: `resp` = ponteiro para `6` → `return resp` imediatamente.

Nós efetivamente visitados: `1, 4, 7, 3, 2, 6` — nessa ordem. O nó `5` nunca é tocado,
porque a busca já tinha achado o que procurava.

**Se buscássemos um valor que não existe** (ex.: `TAV_busca(1, 99)`), o mesmo percurso
aconteceria, mas **sem** o corte do passo 10 — a função visitaria **todos** os 7 nós
(`1, 4, 7, 3, 2, 6, 5`) antes de finalmente retornar `NULL` na chamada mais externa.

## 4. Letra miúda

**Por que não há checagem `if (a == NULL)` no início de `TAV_busca`?** Porque, pela
definição de Teoria 02, uma árvore nunca é vazia — `TAV_busca` sempre recebe um nó real
(a raiz da árvore, ou uma subárvore dentro da recursão, mas nunca `NULL`), já que o `for`
que chama recursivamente só passa `p` quando `p != NULL`.

**Essa busca é O(log n), como a busca numa BST (1.2)?** **Não.** Esta árvore não tem
nenhuma propriedade de ordenação (não é uma árvore de busca) — não há como saber, olhando
só a raiz, se a informação procurada está "à esquerda" ou "à direita", porque não existe
esquerda/direita aqui, só uma lista de filhos sem ordem definida por valor. No pior caso
(informação não existe, ou está na última folha visitada), a busca precisa visitar **todos
os `n` nós** da árvore: complexidade `O(n)`, não `O(log n)`.

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `if(a->info == info) return a;` | testo a raiz da subárvore atual antes de gastar tempo olhando os filhos |
| `for (p = a->prim_filho; p; p = p->prox_irmao)` | visito, um a um, todos os filhos diretos de `a` |
| `TAV_busca(p, info)` dentro do laço | repito o processo inteiro (testar raiz, depois filhos) dentro de **cada** subárvore filha — é isso que faz a busca ser "em profundidade": desço até o fundo de um ramo antes de ir para o próximo |
| `if(resp) return resp;` | corto a busca assim que alguém, em qualquer profundidade, já achou — não continuo checando os irmãos restantes |

## 6. Exercícios de fixação

1. Na árvore do exemplo (`1` com filhos `4,3,2`; `4` com filho `7`; `2` com filhos `6,5`),
   liste, na ordem exata em que seriam visitados, os nós tocados por `TAV_busca(1, 5)`.
2. Por que `TAV_busca(1, 99)` (valor inexistente) precisa visitar **todos** os nós, mas
   `TAV_busca(1, 4)` pode retornar depois de visitar só **um** nó?
3. Qual é a complexidade de pior caso de `TAV_busca` numa árvore com `n` nós? E por que ela
   não pode ser melhor que isso, em geral, para esta estrutura (sem propriedade de busca)?

### Gabarito

1. `1, 4, 7, 3, 2, 6, 5` — precisa visitar `6` primeiro (ele não bate), só então `5` bate.
2. Porque `4` é filho direto da raiz (`1->prim_filho == 4`): a primeira comparação depois
   da raiz já acha. Já `99` não existe em lugar nenhum, então nenhuma comparação nunca dá
   certo, e o algoritmo só desiste depois de esgotar todos os nós (nenhum `if(resp)` nunca
   dispara).
3. `O(n)` — no pior caso (valor não existe, ou está na última posição visitada), todo nó é
   testado exatamente uma vez. Não dá para fazer melhor **em geral** porque não há nenhuma
   propriedade que permita descartar ramos inteiros sem olhar (diferente da BST em 1.2,
   onde a propriedade de ordenação permite descartar metade da árvore a cada passo).

## Resumo

- `TAV_cria` é `O(1)`: aloca e inicializa um nó como folha isolada (`prim_filho` e
  `prox_irmao` ambos `NULL`).
- `TAV_busca` é uma busca em profundidade recursiva: testa a raiz, depois cada filho (e,
  dentro de cada filho, recursivamente, os netos), com corte antecipado (`if(resp) return
  resp;`) assim que a informação é encontrada em qualquer profundidade.
- Sem propriedade de ordenação, o pior caso de `TAV_busca` é `O(n)` — precisa poder visitar
  todos os nós, diferente da busca `O(log n)` de uma BST balanceada.

**Próximo:** [[Teoria 04 - Inserção na árvore variável]].
