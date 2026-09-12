# Teoria 01 — As duas diferenças estruturais entre árvore B e árvore B+

> **Onde isto entra:** árvore B+ não é uma estrutura nova do zero — é a árvore B (5.1) com
> duas mudanças de regra, cada uma resolvendo uma limitação específica. Sem entender essas
> duas mudanças, tudo que vem depois (busca, range query) parece "regra decorada".
> **Antes:** [[../../5.1 Árvores B/Teoria - passo a passo/Teoria 05 - Merge e redistribuição na remoção|5.1 Teoria 05]] (a árvore B completa).
> **Fonte:** síntese do `README.md` deste subtópico (que já consolidou SZ e a menção de CO,
> cap. 18, sobre variantes de árvore B) — nem SZ nem CO têm, confirmadamente, um capítulo
> **dedicado** a B+ nesta sessão (não foi possível abrir os PDFs para conferir; ver aviso
> equivalente na Teoria 01 de 5.1). Não invente página a partir disto.

## 1. A ideia em uma frase

Árvore B+ é uma árvore B (5.1) onde **os dados só existem nas folhas** (nunca em nó
interno), e **as folhas são ligadas entre si** numa lista encadeada, na ordem das chaves.

## 2. De onde vem / por que mudar a árvore B

A árvore B (5.1) já resolve bem a busca por uma chave exata. Mas ela tem duas limitações
quando o uso real é um índice de banco de dados:

1. **Nós internos "gastam espaço" com dados.** Num bloco de disco de tamanho fixo, se cada
   chave de um nó interno também carrega um dado (registro) associado, sobra menos espaço
   para chaves-separadoras — a árvore fica mais alta do que precisaria.
2. **Buscar um intervalo de valores é caro.** Bancos de dados fazem `WHERE data BETWEEN x
   AND y` o tempo todo. Numa árvore B comum, não existe um jeito direto de ir de uma chave
   para "a próxima maior" sem re-navegar pela árvore.

> **Pergunta que motiva a árvore B+:** e se eu **tirasse** os dados dos nós internos
> (deixando ali só os separadores) e **ligasse** as folhas entre si, na ordem? Os nós
> internos ficariam mais "magros" (cabe mais separador por bloco → árvore mais rasa), e
> percorrer um intervalo viraria "achar o início, depois seguir a corrente" — sem nunca
> mais precisar olhar para cima.

## 3. As duas diferenças — lidas devagar

> 📖 **Diferença 1 — onde ficam os dados:**
> - Árvore B (5.1): um registro pode estar em **qualquer** nó — raiz, meio ou folha. A
>   chave `30`, por exemplo, pode estar guardada na raiz, junto com o dado associado a ela.
> - Árvore B+: **todo** dado mora numa folha. Um nó interno guarda a chave `30` só como
>   **separador** (para saber que filho seguir) — o dado de verdade associado a `30` está
>   em alguma folha, possivelmente **repetido** ali (a chave existe duas vezes: uma como
>   separador acima, outra com o dado de verdade embaixo).

> 📖 **Diferença 2 — folhas encadeadas:**
> - Árvore B: as folhas não se conhecem — não há como ir de uma folha para a vizinha sem
>   subir até um ancestral comum e descer de novo.
> - Árvore B+: cada folha tem um ponteiro para a **próxima** folha (em ordem de chave) —
>   como um `próximo` de lista encadeada, só que "amarrado" nas folhas de uma árvore.

## 4. Conferindo com a árvore concreta do README

```
                 [10 | 20]
                /     |     \
           [3,5] → [10,15] → [20,25,30]     (setas = encadeamento entre folhas)
```

- **Diferença 1 conferida:** o nó raiz `[10|20]` guarda só as chaves `10` e `20` como
  separadores — nenhum dado. O dado de verdade associado à chave `10` está na folha
  `[10,15]` (repetida ali), não na raiz.
- **Diferença 2 conferida:** as três folhas `[3,5]`, `[10,15]`, `[20,25,30]` estão ligadas
  em sequência (as setas) — a partir de `[3,5]`, dá pra alcançar `[10,15]` e depois
  `[20,25,30]` sem nunca voltar à raiz.

## 5. Por que isso importa na prática

| Consequência da diferença | O que ela resolve |
|---|---|
| Nó interno sem dado → cabem mais separadores por bloco | árvore mais **rasa** (menor altura) para o mesmo número de chaves → menos acessos a disco (mesma lógica de "nó gordo" da Teoria 01 de 5.1, levada um passo adiante) |
| Folhas encadeadas | busca por **intervalo** vira "achar o início + percorrer a lista" (Teoria 03), sem re-subir na árvore |

É exatamente por isso que **índices reais de bancos de dados (MySQL, PostgreSQL, etc.) usam
B+, não B pura** — `WHERE data BETWEEN x AND y` e `ORDER BY` são operações de intervalo,
extremamente comuns em SQL.

## 6. Letra miúda

**"A chave aparece duas vezes" não é um bug, é a regra.** Quando uma chave usada como
separador num nó interno também existe (com o dado de verdade) numa folha, isso é
**esperado** em árvore B+ — diferente de árvore B, onde cada chave existe uma única vez em
algum nível. Se um exercício de prova perguntar "quantas vezes a chave X aparece na
árvore?", a resposta em B+ pode ser "mais de uma", e isso está certo.

## 7. 📌 O que você está REALMENTE fazendo

| A escolha de design | O que ela realmente resolve |
|---|---|
| tirar dado de nó interno, deixar só separador | libero espaço no bloco de disco do nó interno para mais chaves → árvore mais rasa |
| ligar as folhas numa lista | crio um "atalho" que evita ter que voltar à raiz para ir de uma folha para a vizinha |
| aceitar repetir a chave (separador + folha) | pago um pequeno custo de espaço/duplicação em troca de nós internos mais simples e magros |

## 8. Exercícios de fixação

1. Numa árvore B+ de ordem m=3, o nó interno `[15|30]` aparece na árvore. Isso significa
   que o dado associado à chave `15` está guardado nesse nó interno? Justifique.
2. Por que uma árvore B+ com a mesma ordem `m` que uma árvore B tende a ter altura **igual
   ou menor**, nunca maior?
3. Se eu quisesse, numa árvore B+, "listar todas as chaves em ordem crescente", eu
   precisaria fazer um percurso em-ordem pela árvore inteira (como faria numa árvore B), ou
   existe um jeito mais direto?

### Gabarito

1. Não. Em árvore B+, nós internos guardam só separadores, nunca dados. O dado de `15` está
   em alguma folha (onde `15` também aparece, "repetida").
2. Porque nós internos de B+, sem carregar dado, cabem mais chaves-separadoras no mesmo
   espaço de bloco — mais filhos por nó → árvore mais rasa para o mesmo `n`. Na pior
   hipótese (quando não há economia de espaço nenhuma), a altura é igual à de uma B
   equivalente; nunca é preciso mais níveis.
3. Existe um jeito mais direto: descer até a folha mais à esquerda (a de menores chaves) e
   depois **seguir o encadeamento de folhas** até o fim — sem nunca visitar um nó interno de
   novo. É a mesma ideia da Teoria 03 (range query), só que sem limite superior.

## Resumo

- Árvore B+ = árvore B (5.1) + duas mudanças: dados só em folha; folhas encadeadas em lista.
- Nó interno guarda só separadores — a mesma chave pode aparecer também numa folha, com o
  dado de verdade.
- As duas mudanças juntas tornam a árvore mais rasa e a busca por intervalo muito mais
  barata — é por isso que índices reais de banco de dados usam B+.

**Próximo:** [[Teoria 02 - Busca por igualdade numa árvore B+]].
