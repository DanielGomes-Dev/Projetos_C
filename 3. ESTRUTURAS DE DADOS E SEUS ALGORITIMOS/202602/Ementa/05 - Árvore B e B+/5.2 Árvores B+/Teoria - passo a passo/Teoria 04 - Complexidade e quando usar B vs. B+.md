# Teoria 04 — Fechando a comparação: complexidade, e quando usar B ou B+

> **Onde isto entra:** último arquivo do subtópico — junta tudo (5.1 e 5.2) numa tabela de
> decisão, útil tanto para prova quanto para "qual estrutura eu escolheria nesse sistema".
> **Antes:** [[Teoria 03 - Busca por intervalo (range query)]].
> **Fonte:** síntese do `README.md` deste subtópico e do de 5.1 — comparação consolidada,
> sem número de página específico (ver aviso de fonte na Teoria 01 de 5.1).

## 1. A ideia em uma frase

Árvore B e árvore B+ têm a **mesma complexidade assintótica** para busca por igualdade,
inserção e remoção — a diferença real de desempenho aparece em **busca por intervalo**, e é
aí que B+ ganha.

## 2. Comparando lado a lado

| Operação | Árvore B (5.1) | Árvore B+ (5.2) |
|---|---|---|
| Busca por igualdade | O(log_m n) | O(log_m n) — igual, mas sempre termina na folha (Teoria 02) |
| Busca por intervalo de tamanho k | sem fórmula limpa — pode exigir múltiplas travessias internas | O(log_m n + k) (Teoria 03) |
| Inserção | O(log_m n), com split | O(log_m n), com split — mais o cuidado de manter o encadeamento de folhas consistente |
| Remoção | O(log_m n), com merge/redistribuição | O(log_m n) — mesma ideia, mais religar ponteiros de folha |
| Espaço por chave em nó interno | guarda chave **e** dado | guarda **só** separador — cabe mais por bloco |

> 📖 **Lendo a linha de "busca por igualdade" devagar:** as duas são `O(log_m n)` — a
> mesma notação, a mesma altura. A diferença não está em **quantos** nós são visitados, mas
> em **onde** a resposta pode ser encontrada (B: em qualquer nível; B+: só na folha,
> Teoria 02). Isso não muda a ordem de grandeza do custo.

## 3. Por que, então, quase todo banco de dados real usa B+ (e não B)?

Porque sistemas reais raramente fazem **só** busca por igualdade. Consultas com `BETWEEN`,
`ORDER BY`, paginação (`LIMIT`/`OFFSET` depois de um ponto), e varreduras de intervalo de
datas são extremamente comuns — e é exatamente aí que a árvore B comum não tem uma resposta
eficiente, enquanto B+ tem (Teoria 03). Como B+ não perde **nada** na busca por igualdade
(mesma complexidade) e ganha bastante em intervalo, ela se tornou a escolha padrão para
índices — não é um empate técnico, é uma vitória estrita de B+ no caso de uso real.

## 4. Quando árvore B "pura" ainda faz sentido

**Quando o padrão de acesso é só busca por igualdade, e nunca por intervalo**, a diferença
de espaço em nós internos (B+ cabe mais separadores) pode não compensar a complexidade
extra de manter uma lista encadeada consistente através de split/merge. Alguns sistemas de
arquivos ou estruturas auxiliares mais simples usam árvore B "pura" por essa razão — é
menos comum, mas não é errado.

## 5. 📌 O que você está REALMENTE decidindo, ao escolher entre B e B+

| A pergunta que você faz | Se a resposta for "sim" | Estrutura indicada |
|---|---|---|
| "Vou precisar de busca por intervalo com frequência?" | sim | B+ |
| "Só preciso de busca/inserção/remoção por chave exata, nunca intervalo?" | sim | B (mais simples de implementar, sem lista de folhas para manter) |
| "É um índice de banco de dados real?" | sim (praticamente sempre) | B+ (é o padrão da indústria) |

## 6. Exercícios de fixação

1. Verdadeiro ou falso: "árvore B+ é assintoticamente mais rápida que árvore B para busca
   por igualdade." Justifique.
2. Um sistema faz milhões de buscas `SELECT * FROM tabela WHERE id = ?` (sempre igualdade,
   nunca intervalo) e nunca faz `BETWEEN` ou `ORDER BY`. Isso muda a recomendação da seção
   4? Por quê?
3. Por que a pergunta certa para decidir entre B e B+ não é "qual é mais rápida?" (sem mais
   contexto), mas sim "qual é o padrão de consulta?"

### Gabarito

1. Falso. Ambas são O(log_m n) para busca por igualdade — a mesma ordem de grandeza. B+ não
   é assintoticamente mais rápida **nessa operação específica**; a vantagem dela é em busca
   por intervalo.
2. Sim, muda — nesse cenário específico (só igualdade, nunca intervalo), a vantagem
   característica de B+ nunca é usada, então a árvore B "pura" seria uma escolha
   igualmente válida (e um pouco mais simples de manter, sem lista de folhas).
3. Porque as duas estruturas empatam em quase tudo (mesma complexidade assintótica na
   maioria das operações) — a decisão real depende de **qual operação vai ser usada na
   prática**, não de uma estrutura ser "geralmente melhor" que a outra.

## Resumo

- B e B+ têm a mesma complexidade assintótica para busca por igualdade, inserção e remoção.
- B+ ganha especificamente em busca por **intervalo** (O(log_m n + k) vs. sem fórmula limpa
  em B) — é essa vantagem específica que a torna o padrão em índices de banco de dados reais.
- A escolha entre B e B+ depende do **padrão de uso** (precisa de range query ou não), não
  de uma ser universalmente "melhor".

---

Isso fecha a teoria de 5.2 e do módulo 05 (Árvore B e B+). Próximo módulo:
[[../../../06 - Heaps e Listas de Prioridade/README|06 - Heaps e Listas de Prioridade]].
