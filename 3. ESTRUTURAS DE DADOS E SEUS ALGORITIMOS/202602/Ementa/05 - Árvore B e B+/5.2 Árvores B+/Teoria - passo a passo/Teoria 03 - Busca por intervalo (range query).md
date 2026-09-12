# Teoria 03 — Busca por intervalo (range query): a razão de existir da árvore B+

> **Onde isto entra:** esta é a operação que justifica toda a complicação extra da árvore
> B+ (Teoria 01) — é aqui que o encadeamento de folhas realmente compensa.
> **Antes:** [[Teoria 02 - Busca por igualdade numa árvore B+]].
> **Fonte:** síntese do `README.md` deste subtópico, seção "Passo a passo: range query numa
> B+" — o exemplo abaixo é o mesmo do README, expandido em passo a passo completo.

## 1. A ideia em uma frase

Buscar todos os valores entre `X` e `Y` numa árvore B+ é: descer **uma vez** até achar onde
`X` começaria, e depois **percorrer a lista encadeada de folhas** coletando tudo até passar
de `Y` — nunca mais subindo na árvore.

## 2. De onde vem / por que isso é possível só em B+

Numa árvore B comum (5.1), depois de achar `X`, não existe um jeito direto de ir para "a
próxima chave maior" sem re-navegar pela árvore a partir de algum ancestral — as folhas não
se conhecem. É exatamente essa lacuna que a Teoria 01 motivou preencher com o encadeamento
de folhas: uma vez que você está numa folha, a **próxima** (em ordem de chave) está a um
ponteiro de distância, sem precisar saber nada sobre a estrutura da árvore acima dela.

## 3. O algoritmo — lido pedaço por pedaço

> 📖 **Lendo devagar — range query `[X, Y]`:**
>
> 1. **Fase 1 (descida, uma vez só):** desça pela árvore como na busca por igualdade
>    (Teoria 02), procurando onde `X` **estaria** — chegue numa folha, mesmo que `X` não
>    exista exatamente ali.
> 2. **Fase 2 (percorrer a lista):** a partir dessa folha, ande pelas chaves dela da
>    esquerda para a direita, **coletando** toda chave que esteja no intervalo `[X, Y]`.
> 3. Quando as chaves da folha atual acabarem (ou passarem de `Y`), siga o **ponteiro de
>    encadeamento** para a próxima folha — sem tocar em nenhum nó interno.
> 4. Repita o passo 2–3 até encontrar uma chave maior que `Y`, ou até a lista de folhas
>    acabar (`próxima == NULL`).

## 4. Conferindo com a árvore concreta, passo a passo completo

```
                 [10 | 20]
                /     |     \
           [3,5] → [10,15] → [20,25,30]
```

**Range query `[8, 22]`:**

### Fase 1 — descida (uma vez)

| Nó visitado | Comparação | Decisão |
|---|---|---|
| `[10\|20]` | `8 < 10` | desce para o filho da esquerda... |

> 📖 **Pausa importante:** por que não vamos para `[3,5]`, se `8 < 10`? Porque o objetivo da
> descida não é achar `8` exatamente — é achar **a primeira folha que pode conter valores ≥
> 8**. Como `8` cairia, em valor, **depois** de `[3,5]` (que só tem `3` e `5`, ambos < 8) e
> **antes ou dentro** de `[10,15]`, a folha certa para **começar a fase 2** é `[10,15]`. Uma
> implementação cuidadosa desce comparando com `X` e escolhe a folha onde `X` se encaixaria
> — aqui, isso aponta para `[10,15]`.

### Fase 2 — percorrer a lista de folhas, coletando

| Folha atual | Chaves da folha | O que é coletado (∈ [8,22]) | Próximo passo |
|---|---|---|---|
| `[10,15]` | `10, 15` | `10` ✔ (≥8), `15` ✔ (≤22) — ambos coletados | acabaram as chaves desta folha, nenhuma passou de 22 → segue o encadeamento |
| `[20,25,30]` | `20, 25, 30` | `20` ✔ (≤22) coletado; `25` — **25 > 22**, passou do limite | **para aqui**, não precisa olhar `30` nem seguir mais adiante |

**Resultado:** `10, 15, 20`. ✔ (mesmo resultado do README, agora com cada comparação
explícita).

**Conferindo o custo:** a fase 1 visitou 1 nó interno (a raiz). A fase 2 visitou 2 folhas e
fez 5 comparações de chave (`10,15` na primeira folha, `20,25` na segunda, parando em `25`).
Em nenhum momento a busca voltou a olhar `[10|20]` depois da fase 1 — é exatamente essa
ausência de "re-subida" que torna range query em B+ mais barata que em árvore B comum.

## 5. Letra miúda

**"Para assim que passar de Y" é o que garante que o custo não explode.** Sem essa condição
de parada, a fase 2 percorreria a lista de folhas **inteira**, mesmo que o intervalo pedido
fosse pequeno. A condição `chave > Y → return` (visível no código de `busca_intervalo` no
`README.md` deste subtópico) é o que faz o custo da fase 2 ser proporcional a `k` (o número
de resultados), não a `n` (o total de chaves na árvore).

## 6. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| descer só até achar a folha de `X` (fase 1) | pago o custo de navegação **uma única vez**, O(log_m n) |
| seguir o encadeamento em vez de re-subir | uso a estrutura extra (Teoria 01) que troquei espaço/complexidade por velocidade de percurso sequencial |
| parar assim que uma chave > `Y` aparece | evito percorrer folhas que já sei que não têm nada de interesse |

## 7. Complexidade

| Fase | Custo |
|---|---|
| Fase 1 (descida) | O(log_m n) — mesma altura de uma busca por igualdade |
| Fase 2 (percorrer folhas) | O(k) — proporcional ao número de resultados coletados, não ao tamanho da árvore |
| **Total** | O(log_m n + k) |

Compare com árvore B comum (5.1): sem encadeamento de folhas, um range query exigiria, no
pior caso, múltiplas descidas/travessias internas repetidas — não há uma fórmula tão limpa
quanto `O(log_m n + k)`.

## 8. Exercícios de fixação

Usando a mesma árvore da seção 4:

1. Trace a range query `[12, 26]`. Quais chaves são coletadas?
2. Trace a range query `[1, 4]`. Em quantas folhas ela precisa entrar?
3. O que aconteceria (em termos de custo) se `Y` fosse maior que todas as chaves da árvore
   (ex.: `[8, 1000]`)? A busca ainda para "cedo"?

### Gabarito

1. Fase 1: desce até `[10,15]` (onde `12` se encaixaria). Fase 2: em `[10,15]`, coleta `15`
   (`10 < 12`, não entra; `15` está em `[12,26]`, entra). Segue para `[20,25,30]`: coleta
   `20` e `25` (ambos ≤ 26); `30 > 26`, para. Resultado: `15, 20, 25`.
2. Fase 1 leva até `[3,5]` (onde `1` se encaixaria, à esquerda de tudo). Fase 2: em `[3,5]`,
   `3` e `5` — `3` está em `[1,4]` (coleta), `5` não está (`5 > 4`, já passou do limite) →
   **para na primeira folha**, nem precisa seguir o encadeamento. Visitou 1 folha.
3. Não para cedo — teria que percorrer **todas** as folhas até o fim da lista (`próxima ==
   NULL`), porque nunca encontraria uma chave maior que `Y=1000`. Custo vira O(log_m n + n)
   no pior caso (praticamente, percorrer a árvore inteira pela lista de folhas) — é o preço
   de um intervalo "aberto" que cobre quase tudo.

## Resumo

- Range query = uma descida (fase 1, O(log_m n)) + um percurso pela lista de folhas (fase
  2, O(k)), nunca voltando a subir na árvore.
- A fase 2 para assim que encontra uma chave maior que `Y` — é isso que mantém o custo
  proporcional ao tamanho do resultado, não ao tamanho da árvore.
- Esta é a operação que **só** a árvore B+ faz de forma eficiente — é o motivo real de ela
  existir sobre a árvore B comum.

**Próximo:** [[Teoria 04 - Complexidade e quando usar B vs. B+]].
