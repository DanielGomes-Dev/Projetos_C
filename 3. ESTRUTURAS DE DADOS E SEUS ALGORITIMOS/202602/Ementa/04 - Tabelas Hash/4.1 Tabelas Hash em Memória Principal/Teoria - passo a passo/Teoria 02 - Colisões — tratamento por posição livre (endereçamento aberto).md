# Teoria 02 — Colisões: tratamento por posição livre (endereçamento aberto)

> **Onde isto entra:** a Teoria 01 mostrou que colisão é inevitável. Aqui vemos a primeira
> (e mais simples) estratégia para lidar com ela.
> **Antes:** [[Teoria 01 - Por que precisamos de uma função hash]].
> **Fonte:** CE (Celes), Cap. 18 "Tabelas de dispersão", pág. 275–276.

## 1. A ideia em uma frase

Quando a posição calculada pelo hash já está ocupada por outra chave, procura-se **a
próxima posição livre**, andando pela tabela (e voltando ao início se chegar ao fim).

## 2. Por que essa estratégia, especificamente

É a solução mais direta que não exige nenhuma estrutura extra: tudo continua guardado
**dentro do próprio vetor** (por isso o nome "endereçamento aberto" — o endereço final de
um elemento pode ser diferente do endereço que o hash calculou, mas ainda é um endereço
**dentro da tabela**). O livro chama isso de "uso da posição consecutiva livre".

## 3. Declarando a tabela

```c
#define N 127
typedef Aluno* Hash[N];
```

> 📖 **Lendo devagar:** `Hash` é um apelido para "vetor de `N` ponteiros para `Aluno`". Cada
> posição vazia guarda `NULL`. `N = 127` (primo) é escolhido de propósito — valores primos
> ajudam a espalhar melhor as chaves (menos padrões de colisão sistemática).

## 4. Busca — lida devagar

```c
Aluno *hsh_busca(Hash tab, int mat) {
  int h = hash(mat);
  while (tab[h] != NULL) {
    if (tab[h]->mat == mat)
      return tab[h];
    h = (h + 1) % N;
  }
  return NULL;
}
```

> 📖 **Lendo devagar:**
> 1. `h = hash(mat)` — calcula a posição "de origem" da chave.
> 2. `while (tab[h] != NULL)` — enquanto a posição atual **tiver alguém** (não necessariamente
>    quem procuramos ainda).
> 3. `if (tab[h]->mat == mat) return tab[h];` — se for a chave certa, achou, devolve.
> 4. `h = (h + 1) % N;` — senão, **avança uma posição**; o `% N` faz "dar a volta" quando
>    passa do final da tabela (incremento circular).
> 5. Se o `while` parar porque achou `NULL` (posição vazia), a chave **não está na tabela**
>    — `return NULL`.

**Por que precisa continuar comparando, e não só checar "tem alguém aqui"?** Porque a
posição `h` original pode estar ocupada por **outra** chave que também colidiu ali — a
simples presença de alguém não confirma que é quem procuramos.

## 5. Conferindo com números concretos

Tabela pequena, `N = 7` (para caber no papel), `hash(k) = k % 7`. Inserindo, nesta ordem:
`10, 3, 17, 5, 24, 12, 21` (mesmos valores usados no README deste subtópico, para comparar
com encadeamento separado na Teoria 04).

| Chave | `hash(k) = k % 7` |
|---|---|
| 10 | 3 |
| 3 | 3 |
| 17 | 3 |
| 5 | 5 |
| 24 | 3 |
| 12 | 5 |
| 21 | 0 |

> **Trace da inserção (posição livre mais próxima, andando pra frente):**
>
> | Inserindo | Posição de origem | O que encontra | Onde acaba ocupando |
> |---|---|---|---|
> | 10 | 3 | livre | **3** |
> | 3  | 3 | ocupada (10) | tenta 4 → livre → **4** |
> | 17 | 3 | ocupada (10) | tenta 4 (ocupada), tenta 5 → livre → **5** |
> | 5  | 5 | ocupada (17!) | tenta 6 → livre → **6** |
> | 24 | 3 | ocupada (10) | tenta 4,5,6 (todas ocupadas) → tenta 0 → livre → **0** |
> | 12 | 5 | ocupada (17) | tenta 6 (ocupada), tenta 0 (ocupada) → tenta 1 → livre → **1** |
> | 21 | 0 | ocupada (24!) | tenta 1 (ocupada), tenta 2 → livre → **2** |

Tabela final:
```
0: 24    1: 12    2: 21    3: 10    4: 3    5: 17    6: 5
```

**O efeito colateral (clustering):** repare que o bloco ocupado — posições `3,4,5,6,0,1,2`
— acabou sendo **quase a tabela inteira**, um único aglomerado contínuo. Chaves que
nem sequer colidiam originalmente com `10` (como `5`, que mapeia pra posição `5`) foram
empurradas para longe (posição `6`) só porque o cluster já tinha crescido até lá. Esse
efeito cascata se chama **clustering primário**, e é a principal fraqueza deste método
(motiva double hashing, Teoria 03).

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `h = (h+1) % N` repetido | ando pela tabela até achar espaço, tratando-a como circular |
| comparar `tab[h]->mat == mat` a cada posição | confirmo identidade, não só presença — várias chaves diferentes podem ter passado pela mesma posição de origem |
| parar em `NULL` na busca | uso "vazio" como sinal de "nunca ninguém chegou até aqui" — o que só funciona se toda inserção seguir a mesma regra de avanço |

## 7. Letra miúda: por que não dá pra simplesmente esvaziar na remoção

Se remover uma chave só fizesse `tab[h] = NULL`, uma busca futura por uma chave que "passou
por ali" durante sua própria inserção (por causa de colisão) pararia cedo demais, achando
`NULL` antes de chegar onde a chave realmente está. A solução usual é um marcador especial
de "removido" (*tombstone*) — diferente de "nunca ocupado" — mas o livro não implementa
remoção nesta seção; fica registrado aqui como cuidado, não como código pronto.

## 8. Exercícios de fixação

1. Usando a tabela de `N = 7` da seção 5, insira a chave `31` (`31 % 7 = 3`) na tabela
   final mostrada. Em qual posição ela acaba?
2. Rode `hsh_busca(tab, 12)` mentalmente sobre a tabela final da seção 5: por quais
   posições passa, e por quê, até achar `12`?
3. Por que a busca por uma chave que **nunca foi inserida** (ex.: `18`, que mapeia pra
   posição 3) ainda precisa percorrer várias posições antes de retornar `NULL`?

### Gabarito

1. `31 % 7 = 3` (ocupada por 10) → tenta 4 (3, ocupada) → tenta 5 (17, ocupada) → tenta 6
   (5, ocupada) → tenta 0 (24, ocupada) → tenta 1 (12, ocupada) → tenta 2 (21, ocupada) →
   tenta 3 de novo?? Não — com `N=7` e a tabela cheia (7 posições, 7 chaves já inseridas),
   **não há posição livre**: a tabela está 100% ocupada, o que nunca deveria acontecer numa
   tabela hash bem dimensionada (violaria a regra de manter ocupação ≤ 75% da Teoria 01).
2. `hash(12) = 5`. Posição 5 tem `17` (≠ 12) → avança pra 6. Posição 6 tem `5` (≠ 12) →
   avança pra 0. Posição 0 tem `24` (≠ 12) → avança pra 1. Posição 1 tem `12` — **achou**.
3. Porque, com endereçamento aberto, "vazio" só existe **depois** do fim de qualquer cluster
   que passou por aquela posição de origem — a busca precisa seguir a mesma trilha de
   sondagem que uma inserção (hipotética) da chave `18` teria seguido, até encontrar de
   fato uma posição `NULL` que confirme "ninguém chegou até aqui".

## Resumo

- Endereçamento aberto: toda chave mora dentro do próprio vetor; colisão resolve-se
  avançando (circularmente) até achar posição livre.
- Busca e inserção precisam seguir **a mesma trilha** de sondagem, comparando a chave real
  em cada posição visitada (presença não basta).
- O efeito colateral é o **clustering primário**: blocos de posições ocupadas crescem e se
  fundem, piorando sondagens futuras mesmo para chaves sem relação com as que já colidiram.

**Próximo:** [[Teoria 03 - Dispersão dupla (double hashing)]].
