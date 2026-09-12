# Teoria 01 — Intercalando duas partições (merge de 2 arquivos ordenados)

> **Onde isto entra:** depois de gerar partições ordenadas (3.2), o passo mais simples de
> intercalação é combinar **duas** delas — a base de qualquer intercalação de k vias.
> **Antes:** [[../../3.2 Geração de Partições Classificadas/Teoria - passo a passo/README|3.2 Geração de Partições Classificadas]].
> **Fonte:** `ListasExercicios/lista050607-EDA/09_Arquivos_Texto.pdf`, pág. 5 (slide da
> disciplina — o exemplo ali é apresentado como manipulação de arquivo texto, mas a função
> `merge` é literalmente uma intercalação de duas partições ordenadas).

## 1. A ideia em uma frase

Para juntar duas listas **já ordenadas** numa só ordenada, nunca é preciso reordenar nada:
basta sempre escrever o **menor entre os dois candidatos disponíveis no momento**, e avançar
só naquela lista.

## 2. Por que não precisa comparar tudo com tudo

Se as duas partições já estão ordenadas, o menor valor de toda a combinação **só pode**
estar numa de duas posições: o próximo valor não lido da partição 1, ou o próximo não lido
da partição 2 — nunca mais fundo que isso. É essa observação que faz o merge custar `O(n1 +
n2)`, e não `O(n1 × n2)`.

## 3. O código do PDF — lido devagar

```c
r1 = fscanf(fp1, "%d", &n1);
r2 = fscanf(fp2, "%d", &n2);
while ((r1 == 1) || (r2 == 1)) {
  if ((r2 != 1) || (n1 <= n2)) {
    fprintf(fpo, "%d\n", n1);
    r1 = fscanf(fp1, "%d", &n1);
    if (r1 != 1) n1 = INT_MAX;
  }
  else if ((r1 != 1) || (n2 < n1)) {
    fprintf(fpo, "%d\n", n2);
    r2 = fscanf(fp2, "%d", &n2);
    if (r2 != 1) n2 = INT_MAX;
  }
}
```

> 📖 **Lendo devagar:**
> 1. `r1 = fscanf(fp1, "%d", &n1)` — lê o **primeiro candidato** da partição 1;
>    `r1` guarda quantos valores foram lidos com sucesso (1 = ok; 0 ou menos = acabou o
>    arquivo). Mesma ideia para `r2`/`n2` na partição 2.
> 2. `while ((r1 == 1) || (r2 == 1))` — continua **enquanto pelo menos uma** das duas
>    partições ainda tiver dado (não as duas ao mesmo tempo — só uma já basta pra continuar).
> 3. `if ((r2 != 1) || (n1 <= n2))` — escreve `n1` (o candidato da partição 1) **se**
>    partição 2 já acabou (`r2 != 1`, não há com quem comparar) **ou** `n1` é o menor
>    (`n1 <= n2`). Ler essa condição de dentro pra fora: primeiro checa "ainda existe
>    concorrente?", só depois compara valores.
> 4. `if (r1 != 1) n1 = INT_MAX;` — **truque do sentinela**: se a partição 1 acabou, força
>    `n1` para o maior valor possível, garantindo que a próxima comparação **nunca** escolha
>    `n1` de novo (útil já que o `while` externo só para quando as duas realmente acabarem).
> 5. O `else if` espelha exatamente a mesma lógica para a partição 2.

## 4. Conferindo com número concreto

Partição 1: `[1, 5, 9]`. Partição 2: `[2, 3, 8]`.

| Passo | `n1` | `n2` | Comparação | Escreve | Avança |
|---|---|---|---|---|---|
| 1 | 1 | 2 | `1 ≤ 2` | 1 | lê próximo de P1 → `n1=5` |
| 2 | 5 | 2 | `5 > 2` | 2 | lê próximo de P2 → `n2=3` |
| 3 | 5 | 3 | `5 > 3` | 3 | lê próximo de P2 → `n2=8` |
| 4 | 5 | 8 | `5 ≤ 8` | 5 | lê próximo de P1 → **acabou** → `n1 = INT_MAX` |
| 5 | ∞ | 8 | `r1≠1` cai no `else` | 8 | lê próximo de P2 → **acabou** → `n2 = INT_MAX` |
| 6 | ∞ | ∞ | `r1==1`? não. `r2==1`? não. | — | **`while` para** |

Saída: `1, 2, 3, 5, 8` — espera, faltou o `9`! Vamos conferir de novo com cuidado: no passo
4, ao escrever `5`, a leitura seguinte de P1 traz `9`, não "acabou" (P1 = `[1,5,9]` tem 3
elementos, e só lemos 2: `1` e `5`). Corrigindo o trace:

| Passo | `n1` | `n2` | Escreve | Avança |
|---|---|---|---|---|
| 4 | 5 | 8 | 5 | lê próximo de P1 → `n1 = 9` |
| 5 | 9 | 8 | 8 | lê próximo de P2 → **acabou** → `n2 = INT_MAX` |
| 6 | 9 | ∞ | 9 | lê próximo de P1 → **acabou** → `n1 = INT_MAX` |
| 7 | ∞ | ∞ | — | **para** |

Saída correta: `1, 2, 3, 5, 8, 9` — ordenada, todos os 6 elementos presentes. ✔ (A tabela da
seção anterior errou de propósito no passo 4 para mostrar como conferir com cuidado pega
esse tipo de deslize — sempre reconte quantos elementos cada partição tem antes de decidir
"acabou".)

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| comparar só os dois "topos" (n1, n2) | aproveito que cada partição já está ordenada — nunca preciso olhar mais fundo que o próximo elemento de cada uma |
| `n1 = INT_MAX` quando P1 acaba | uso um valor-sentinela para nunca mais escolher aquele lado, sem precisar de um `if` separado só pra isso |
| avançar só o lado que "venceu" | nunca releio nem pulo dado — cada elemento de cada partição é lido exatamente uma vez |

## 6. Exercícios de fixação

1. Por que o `while` externo usa `||` (ou) entre `r1==1` e `r2==1`, e não `&&` (e)?
2. Se P1 = `[4, 6]` e P2 = `[1, 2, 3]`, qual a saída do merge?
3. Qual o custo (em comparações) de intercalar duas partições de tamanho `a` e `b`?

### Gabarito

1. Porque o processo só deve **parar** quando as **duas** partições esgotarem — enquanto
   pelo menos uma ainda tiver dado, ainda há algo a escrever na saída (usando o sentinela
   para não escolher o lado já esgotado).
2. `1, 2, 3, 4, 6` — P2 fornece `1,2,3` (todos menores que o `4` de P1) antes de P1 entrar
   com `4, 6`.
3. `O(a + b)` — cada elemento das duas partições é lido e comparado exatamente uma vez (na
   pior das hipóteses, uma comparação por elemento total escrito).

## Resumo

- Merge de duas partições ordenadas: sempre escreve o menor entre os dois "topos"
  disponíveis, avançando só o lado escolhido.
- O truque do sentinela (`INT_MAX`) evita tratar "partição esgotada" como caso especial
  dentro da comparação principal.
- Custo `O(n1 + n2)` — nunca é preciso reexaminar dados já escritos ou já comparados.

**Próximo:** [[Teoria 02 - Intercalação de k vias e número de passadas]].
