# Q3 — Contar ocorrências e linhas de cada número

> **Origem:** `lista05-EDA.pdf`, questão 3 · **Código resolvido:** [[../Q3/claude/main.c]]
> **Antes disto, veja:** [[Q2 - Ordenar alunos por média]].

## 1. O que o exercício pede

> Receba um arquivo texto com valores inteiros e imprima na tela o número de vezes que cada
> elemento aparece e em quais linhas — `void resumo(char *Arq)`.

## 2. A ideia geral

Diferente de Q1/Q2, aqui a saída não é outro arquivo — é uma **tabela de contagem**, onde a
chave é o valor numérico e o conteúdo é "quantas vezes" + "em quais linhas". É o mesmo
padrão de "tabela de ocorrências" que reaparece depois em Tabelas Hash (módulo 04) — aqui,
resolvido com busca linear (adequado para poucos valores distintos).

## 3. Resolução passo a passo

### Passo 1 — extrair todos os números de uma linha

```c
char *p = linha;
while (1) {
    char *fim;
    long x = strtol(p, &fim, 10);
    if (fim == p) break;     // não achou mais nenhum número nesta linha
    p = fim;                  // avança o cursor de leitura pra depois do número lido
    ...
}
```

> 📖 **Lendo `strtol(p, &fim, 10)` devagar:** converte o **início** da string apontada por
> `p` para um número inteiro (base 10), e faz `fim` apontar para **logo depois** do último
> dígito consumido. Se `fim == p`, nada foi consumido — não havia número ali. Repetir isso
> avançando `p = fim` a cada volta é como "ler todos os números da linha, um por um", sem
> saber de antemão quantos existem.

### Passo 2 — tabela de ocorrências (busca linear)

```c
int i;
for (i = 0; i < ndist; i++)
    if (tab[i].valor == x) break;

if (i == ndist) {           // não achou -> é um valor novo
    tab[i].valor = x;
    tab[i].contagem = 0;
    ndist++;
}
tab[i].linhas[tab[i].contagem] = nlinha;
tab[i].contagem++;
```

> **Tabela de trace**, para a entrada (linha a linha): `10` / `20` / `10 30` / `20` / `10` /
> `40`:

| Linha lida | Números na linha | Estado da tabela **depois** |
|---|---|---|
| 1 | 10 | `{10: [1]}` |
| 2 | 20 | `{10: [1], 20: [2]}` |
| 3 | 10, 30 | `{10: [1,3], 20: [2], 30: [3]}` |
| 4 | 20 | `{10: [1,3], 20: [2,4], 30: [3]}` |
| 5 | 10 | `{10: [1,3,5], 20: [2,4], 30: [3]}` |
| 6 | 40 | `{10: [1,3,5], 20: [2,4], 30: [3], 40: [6]}` |

## 4. Resultado final

```
valor 10 -> aparece 3 vez(es), na(s) linha(s): 1, 3, 5
valor 20 -> aparece 2 vez(es), na(s) linha(s): 2, 4
valor 30 -> aparece 1 vez(es), na(s) linha(s): 3
valor 40 -> aparece 1 vez(es), na(s) linha(s): 6
```

**Conferindo:** a soma das contagens (3+2+1+1 = 7) bate com o total de números lidos no
arquivo inteiro (7 números: `10,20,10,30,20,10,40`).

## 5. Habilidades necessárias

- [ ] `strtol` para extrair múltiplos números de uma linha de texto.
- [ ] Busca linear numa tabela de registros — `O(k)` por busca, `k` = valores distintos já
      vistos.

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — sem nenhuma repetição

Entrada: `"1\n2\n3"`. Cada valor é novo — tabela final: `{1:[1], 2:[2], 3:[3]}`, cada um
aparecendo 1 vez.

### Aquecimento 2 — tudo repetido

Entrada: `"5\n5\n5"`. Tabela final: `{5: [1,2,3]}` — 1 valor distinto, 3 ocorrências.
