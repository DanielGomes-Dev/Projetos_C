# Teoria 04 — Inserção na árvore variável

> **Onde isto entra:** item "(c)" do `conteudo.md`: "inserção de um elemento nessa árvore
> variável, sendo que o pai já deve estar inserido na árvore".
> **Antes:** [[Teoria 03 - Criação de nó e busca em profundidade]] (a inserção **usa**
> `TAV_busca` e `TAV_cria` por dentro).
> **Fonte:** código real em `TAVAR/TAV.c`; comparar com `arvv_insere` do Celes (pág. 202).

## 1. A ideia em uma frase

Para inserir um valor como filho de um nó existente, primeiro **acha-se o pai pelo valor
dele** (com a busca de Teoria 03), depois **encaixa-se o novo nó no início da lista de
filhos** do pai — exatamente como inserir no início de uma lista encadeada.

## 2. O código, lido pedaço por pedaço

```c
void TAV_insere (TAV* a, int pai, int info){
  TAV *meu_pai = TAV_busca(a, pai);
  if(!meu_pai) return;
  TAV *novo = TAV_cria(info);
  novo->prox_irmao = meu_pai->prim_filho;
  meu_pai->prim_filho = novo;
}
```

> **Lendo devagar:**
> - `TAV *meu_pai = TAV_busca(a, pai);` — reaproveita a busca de Teoria 03 para achar,
>   dentro da árvore inteira `a`, o nó cujo valor é `pai`. Esse é o nó que vai **ganhar**
>   um novo filho.
> - `if(!meu_pai) return;` — se a busca não achou (o valor `pai` não existe na árvore),
>   a função simplesmente **desiste, sem avisar nada** (nem mensagem de erro, nem valor de
>   retorno diferente — a função é `void`). Ver a letra miúda na seção 4.
> - `TAV *novo = TAV_cria(info);` — cria o novo nó (Teoria 03): nasce como folha isolada,
>   com `prim_filho == prox_irmao == NULL`.
> - `novo->prox_irmao = meu_pai->prim_filho;` — o novo nó "aponta para a frente" para quem
>   **hoje** é o primeiro filho do pai (pode ser outro nó, ou `NULL` se o pai ainda não
>   tinha filhos).
> - `meu_pai->prim_filho = novo;` — o pai passa a apontar para o **novo** nó como seu
>   primeiro filho.

Essas duas últimas linhas são exatamente o padrão de **inserir no início de uma lista
encadeada**: religar primeiro o ponteiro do novo elemento para o antigo início da lista, só
depois mover o ponteiro de "início" para o novo elemento — na ordem inversa, o antigo
início da lista se perderia antes de o novo nó conseguir apontar para ele.

## 3. Conferindo com uma construção passo a passo

Partindo de `TAV *a = TAV_cria(1);` (só a raiz `1`, sem filhos), aplicando, nesta ordem:

```c
TAV_insere(a, 1, 2);   /* 2 vira filho de 1 */
TAV_insere(a, 1, 3);   /* 3 vira filho de 1 */
TAV_insere(a, 1, 4);   /* 4 vira filho de 1 */
TAV_insere(a, 2, 5);   /* 5 vira filho de 2 */
TAV_insere(a, 2, 6);   /* 6 vira filho de 2 */
TAV_insere(a, 4, 7);   /* 7 vira filho de 4 */
```

**Passo a passo do `prim_filho` de `1`** (o que muda a cada inserção de filho de `1`):

1. Antes de tudo: `1->prim_filho = NULL`.
2. `TAV_insere(a, 1, 2)`: acha `1` (busca visita só o nó `1`). `novo(2)->prox_irmao =
   1->prim_filho = NULL`. `1->prim_filho = 2`. Estado: `1 → prim_filho → 2`.
3. `TAV_insere(a, 1, 3)`: acha `1`. `novo(3)->prox_irmao = 1->prim_filho = 2` (o `2` de
   antes!). `1->prim_filho = 3`. Estado: `1 → prim_filho → 3 → prox_irmao → 2`.
4. `TAV_insere(a, 1, 4)`: acha `1`. `novo(4)->prox_irmao = 1->prim_filho = 3`.
   `1->prim_filho = 4`. Estado: `1 → prim_filho → 4 → prox_irmao → 3 → prox_irmao → 2`.

Depois de `TAV_insere(a, 2, 5)` e `TAV_insere(a, 2, 6)` (mesma lógica, agora encaixando em
`2`) e `TAV_insere(a, 4, 7)` (encaixando em `4`), a árvore final é:

```
              1
        ┌─────┼─────┐
        4      3      2
        │            ┌─┴─┐
        7            6   5
```

(Este é exatamente o mesmo exemplo usado em Teoria 03 — agora você viu como ele foi
construído.) Repare que os filhos de `1` aparecem **na ordem inversa** da inserção
(`4, 3, 2`, mas foram inseridos `2, 3, 4`) — cada inserção nova empurra as anteriores para
depois de si, porque a inserção é sempre "no início" da lista de filhos.

## 4. Letra miúda

**"O pai já deve estar inserido na árvore" — o que acontece se não estiver?**
`TAV_busca` retorna `NULL`, `if(!meu_pai) return;` dispara, e a função termina **sem
inserir nada e sem avisar nada** — nem o valor `info` chega a ser criado com `TAV_cria`.
Chamar `TAV_insere(a, 999, 5)` numa árvore onde `999` não existe é, na prática, um no-op
silencioso. Isso é diferente de "dar erro": o programa continua rodando normalmente, só que
o `5` nunca aparece na árvore — é um erro fácil de não perceber ao testar o código.

**Por que a inserção é sempre "no início" da lista de filhos, e não "no fim"?** Porque
inserir no início de uma lista encadeada simples é `O(1)` (só precisa do ponteiro
`meu_pai->prim_filho`); inserir no fim exigiria percorrer toda a lista de filhos até achar
o último (aquele com `prox_irmao == NULL`), o que seria `O(número de filhos já existentes)`.
O `conteudo.md` não exige uma posição específica para o novo filho, então a implementação
escolhe a mais simples e barata.

**Complexidade de `TAV_insere` como um todo:** a parte de "encaixar o nó" (as duas últimas
linhas) é `O(1)`, mas a função inteira faz `TAV_busca` primeiro, que é `O(n)` no pior caso
(Teoria 03) — então `TAV_insere` é `O(n)`, dominada pelo custo de achar o pai, não pelo
custo de encaixar o filho.

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `TAV_busca(a, pai)` | localizo, em qualquer profundidade da árvore, o nó que vai receber o novo filho |
| `if(!meu_pai) return;` | recuso a inserção se o "endereço" pedido (o valor `pai`) não existir — silenciosamente |
| `novo->prox_irmao = meu_pai->prim_filho;` seguido de `meu_pai->prim_filho = novo;` | encaixo o novo nó **na frente** da lista de filhos já existente, sem perder nenhum filho antigo |

## 6. Exercícios de fixação

1. Partindo de uma árvore com só a raiz `10`, aplique `TAV_insere(a,10,20)`, depois
   `TAV_insere(a,10,30)`. Qual nó é `10->prim_filho` ao final? E `10->prim_filho->prox_irmao`?
2. O que `TAV_imprime` (Teoria 05) mostraria para a árvore do item 1: `<10 <20> <30> >` ou
   `<10 <30> <20> >`?
3. Se você chamar `TAV_insere(a, 30, 40)` **antes** de `30` ter sido inserido na árvore, o
   que acontece? Isso gera algum erro visível?
4. Por que inserir no início da lista de filhos é `O(1)`, mas inserir no fim exigiria
   percorrer a lista inteira?

### Gabarito

1. `10->prim_filho == 30` (o último inserido fica na frente); `10->prim_filho->prox_irmao
   == 20`.
2. `<10 <30> <20> >` — ordem inversa à de inserção, pelo mesmo motivo do item 1.
3. `TAV_busca(a, 30)` retorna `NULL` (30 ainda não existe), `if(!meu_pai) return;` dispara,
   e a chamada não faz **nada** — nenhum nó `40` é criado, e não há nenhuma mensagem de
   erro. O programa simplesmente continua como se a chamada nunca tivesse acontecido.
4. Inserir no início só precisa reatribuir 2 ponteiros (`prox_irmao` do novo nó, e
   `prim_filho` do pai) — não importa quantos filhos já existem. Inserir no fim exigiria
   percorrer a lista de filhos, nó por nó, seguindo `prox_irmao`, até achar aquele cujo
   `prox_irmao` já é `NULL` — um trabalho proporcional ao número de filhos existentes.

## Resumo

- `TAV_insere` reaproveita `TAV_busca` para achar o pai pelo valor, e `TAV_cria` para criar
  o novo nó — depois liga os dois com uma inserção no início da lista de filhos (`O(1)`).
- Se o valor do pai não existir na árvore, a função retorna silenciosamente, sem inserir
  nada e sem erro visível — é responsabilidade de quem chama garantir que o pai já existe.
- Como cada inserção entra na frente da lista de filhos, a ordem dos filhos impressa depois
  (Teoria 05) é a **ordem inversa** da ordem de inserção.

**Próximo:** [[Teoria 05 - Impressão e liberação em profundidade]].
