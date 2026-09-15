# Teoria 05 — Impressão e liberação em profundidade

> **Onde isto entra:** item "(d)" do `conteudo.md`: "impressão e liberação, em
> profundidade, dessa árvore" — as duas últimas operações, e a mais fácil de errar
> (liberação de memória mexe com ponteiros que estão prestes a deixar de existir).
> **Antes:** [[Teoria 04 - Inserção na árvore variável]].
> **Fonte:** código real em `TAVAR/TAV.c`; comparar com `arvv_imprime`/`arvv_libera` do
> Celes (págs. 202-203).

## 1. A ideia em uma frase

Imprimir percorre a árvore **de cima para baixo** (mostra o nó, depois entra nos filhos);
liberar faz o **caminho inverso** (livra-se de tudo dentro de um nó antes de livrar-se do
próprio nó) — e essa inversão de ordem não é estética, é **obrigatória** para não perder
ponteiros no meio do caminho.

## 2. Impressão — `TAV_imprime` (pré-ordem)

```c
void TAV_imprime (TAV *a){
  if(a){
    printf("< ");
    printf("%d ", a->info);
    TAV *p;
    for(p = a->prim_filho; p; p = p->prox_irmao) TAV_imprime(p);
    printf("> ");
  }
}
```

> **Lendo devagar:** primeiro imprime `"< "`, depois o valor do próprio nó, **depois** entra
> no `for` que chama `TAV_imprime` recursivamente em cada filho (na ordem da lista, a
> partir de `prim_filho`), e só ao final imprime `"> "` fechando o nó. É a mesma ordem da
> notação `<raiz sa1 sa2 ...>` de Teoria 02 — daí o nome **pré-ordem**: a raiz é processada
> antes (pré-) das subárvores.

**Conferindo** na árvore construída em Teoria 04 (`1` com filhos `4,3,2`; `4` com filho
`7`; `2` com filhos `6,5`):

```
              1
        ┌─────┼─────┐
        4      3      2
        │            ┌─┴─┐
        7            6   5
```

`TAV_imprime(a)` produz, exatamente:

```
< 1 < 4 < 7 > > < 3 > < 2 < 6 > < 5 > >
```

Lendo de fora para dentro: `< 1 ...>` é a árvore inteira; dentro dela, `< 4 < 7 > >` é a
subárvore de `4` (que por sua vez contém `< 7 >`, folha); depois `< 3 >`, folha; depois
`< 2 < 6 > < 5 > >`, a subárvore de `2` com suas duas folhas `6` e `5` — **nessa ordem**,
porque é essa a ordem de `2->prim_filho → 6 → prox_irmao → 5` (a ordem inversa de inserção,
vista em Teoria 04).

## 3. Liberação — `TAV_libera` (pós-ordem)

```c
void TAV_libera (TAV *a){
  if(a){
    TAV *p = a->prim_filho, *temp;
    while(p){
      temp = p->prox_irmao;
      TAV_libera(p);
      p = temp;
    }
    free(a);
  }
}
```

> **Lendo devagar:**
> - `TAV *p = a->prim_filho, *temp;` — `p` percorre os filhos de `a`; `temp` é uma variável
>   auxiliar só para guardar um ponteiro temporariamente (ver o porquê logo abaixo).
> - `temp = p->prox_irmao;` — **antes de fazer qualquer coisa com `p`**, guarda-se o
>   endereço do próximo irmão.
> - `TAV_libera(p);` — libera **toda a subárvore** enraizada em `p` (recursivamente: os
>   filhos de `p` primeiro, depois o próprio `p`, via `free(a)` dentro dessa chamada).
> - `p = temp;` — só agora `p` avança, usando o valor **guardado antes** — não
>   `p->prox_irmao`, porque nesse ponto `p` (o nó antigo) **já foi desalocado** pela linha
>   anterior.
> - `free(a);` — só depois que o `while` termina (ou seja, depois que **todos** os filhos
>   de `a`, e as subárvores deles, já foram completamente liberados), o próprio nó `a` é
>   devolvido ao sistema.

### Por que não dá para escrever igual ao `TAV_imprime`

Uma tentação natural seria copiar a estrutura do `for` de `TAV_imprime`:

```c
/* ERRADO — não faça isso */
for(p = a->prim_filho; p; p = p->prox_irmao)
  TAV_libera(p);
```

Isso **quebra**: `TAV_libera(p)` termina com `free(p)` (o nó `p` é desalocado — a memória
onde ele vivia pode ser reaproveitada a qualquer momento). A instrução seguinte do `for`,
`p = p->prox_irmao`, tentaria **ler um campo de um bloco de memória já liberado** — um
ponteiro *dangling* (pendurado). Isso é comportamento indefinido: às vezes "funciona por
acidente" (o valor antigo ainda está lá, por sorte), às vezes corrompe a árvore ou derruba
o programa, dependendo do alocador de memória. É exatamente por isso que o código real
guarda `temp = p->prox_irmao` **antes** de chamar `TAV_libera(p)` — o mesmo cuidado que se
toma ao liberar uma lista encadeada.

### Conferindo com a mesma árvore

Chamando `TAV_libera(1)` na árvore do exemplo, a ordem em que os `free()` realmente
acontecem é:

```
free(7), free(4), free(3), free(6), free(5), free(2), free(1)
```

Trace resumido: entra em `1`, guarda `temp=3` (irmão de `4`), desce em `4` — dentro de `4`,
guarda `temp=NULL` (irmão de `7`), desce em `7` (folha: `free(7)` direto), sobe e dá
`free(4)`; volta para `1`, avança `p=temp=3`, desce em `3` (folha: `free(3)`), avança
`p=temp=2` (irmão de `3`), desce em `2` — dentro de `2`, guarda `temp=5` (irmão de `6`),
`free(6)`, avança `p=temp=5`, `free(5)`, sobe e dá `free(2)`; finalmente, de volta em `1`,
o `while` termina (não há mais irmãos) e acontece `free(1)`. Cada nó só é liberado **depois
que toda a sua própria subárvore já foi liberada** — por isso essa ordem se chama
**pós-ordem**.

## 4. Letra miúda

**Por que `TAV_imprime` pode usar `for` direto (sem guardar nada antes), mas `TAV_libera`
precisa da variável `temp`?** Porque `TAV_imprime` **não destrói** nenhum nó — depois de
imprimir a subárvore de `p`, o nó `p` continua existindo, intacto, e `p->prox_irmao` ainda
é uma leitura válida. Já `TAV_libera(p)` desaloca `p`; depois disso, qualquer leitura em
cima de `p` (inclusive `p->prox_irmao`) é inválida — daí a necessidade de guardar o próximo
antes de destruir o atual.

**A ordem dos `free()` importa para o resultado final?** Não muda o que sobra na memória
(todo mundo é liberado, de qualquer forma), mas a ordem **importa para a corretude**: se
você tentasse `free(a)` **antes** do `while` (libertando o pai antes dos filhos), perderia
o acesso a `a->prim_filho` assim que `a` fosse desalocado — os filhos ficariam inacessíveis
e vazariam memória (memory leak). É por isso que a liberação **tem que ser** pós-ordem, e
não poderia ser pré-ordem como a impressão.

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `TAV_imprime`: mostra o nó, **depois** entra nos filhos | pré-ordem — preciso ver o pai primeiro para a notação `<raiz sa1 ...>` fazer sentido visualmente |
| `TAV_libera`: entra nos filhos (e nos filhos dos filhos...), **só então** `free(a)` | pós-ordem — preciso destruir de baixo para cima, porque destruir o pai primeiro me faria perder o caminho para os filhos |
| `temp = p->prox_irmao;` antes de `TAV_libera(p);` | guardo o "próximo passo" antes de queimar a ponte que levaria até ele |

## 6. Exercícios de fixação

1. Na árvore `<1 <2 <4>> <3>>` (1 com filhos 2 e 3; 2 com filho 4), qual é a saída exata de
   `TAV_imprime`?
2. Na mesma árvore, em que ordem `TAV_libera` chama `free()` em cada nó?
3. Se `TAV_libera` fosse escrita com o `for` "errado" da seção 3 (sem guardar `temp`), em
   qual chamada exatamente (qual nó) o programa leria memória já liberada pela primeira
   vez, nesta árvore de 4 nós?
4. Por que `TAV_imprime(NULL)` não quebra o programa (não dá erro de acesso inválido)?

### Gabarito

1. `< 1 < 2 < 4 > > < 3 > >`.
2. `free(4), free(2), free(3), free(1)` — pós-ordem: a subárvore de `2` (que inclui `4`) é
   totalmente liberada antes de `2`; depois `3` (folha); só por último, `1`.
3. Ao processar o primeiro filho de `1`, isto é, `TAV_libera(2)`: depois de `free(2)`
   (chamada de dentro do `for` errado), a linha seguinte do `for`, `p = p->prox_irmao`,
   tentaria ler o campo `prox_irmao` de um `TAV` que **já foi liberado** — leitura de
   memória inválida logo na primeira iteração do laço em `1`.
4. Por causa do `if(a){...}` no início: quando `a == NULL`, o corpo inteiro é pulado e a
   função simplesmente retorna sem fazer nada — não chega a acessar `a->info` nem nenhum
   outro campo de um ponteiro nulo.

## Resumo

- `TAV_imprime` é pré-ordem (nó antes dos filhos) — natural para reproduzir a notação
  `<raiz sa1 sa2 ...>` de Teoria 02.
- `TAV_libera` é pós-ordem (filhos antes do nó) — obrigatório, porque `free(a)` destrói o
  acesso a `a->prim_filho`; fazer isso antes de liberar os filhos vazaria memória.
- Padrão essencial em `TAV_libera`: guardar `temp = p->prox_irmao` **antes** de chamar
  `TAV_libera(p)`, porque depois dessa chamada `p` já foi desalocado e não pode mais ser
  lido — o mesmo cuidado usado para liberar uma lista encadeada.
- Ambas as funções são `O(n)`: visitam cada um dos `n` nós exatamente uma vez.

Isto fecha as 4 operações pedidas em `conteudo.md` (criação, busca, inserção, impressão +
liberação). Para ver tudo funcionando junto, ver `TAVAR/teste_arv_gen.c` (um `main` que lê
a árvore interativamente do teclado).
