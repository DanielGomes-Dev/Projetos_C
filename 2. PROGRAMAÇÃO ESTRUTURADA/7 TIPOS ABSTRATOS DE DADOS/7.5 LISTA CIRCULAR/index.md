# 7.5 Lista Circular

## Resumo
Variante de lista encadeada (simples ou dupla) em que o último nó aponta de volta para o primeiro, formando um ciclo — não há `NULL` marcando o fim. Útil para estruturas que precisam "dar a volta" naturalmente (ex.: escalonamento round-robin, buffers circulares). Cuidado ao percorrer: a condição de parada não pode ser "até achar `NULL`" (nunca ocorre) — normalmente se guarda uma referência fixa (ex.: o nó inicial) e para quando se retorna a ela.

## Onde estudar
- **Szwarcfiter** — seção 2.7.3 (Listas circulares).
- **Celes** — cap. 10 ("Listas encadeadas"), seção "Listas circulares" — resolve o problema do critério de parada com `do-while` em vez de `while (p != NULL)`.

## Checklist
- [ ] Como detectar o "fim" do percurso sem `NULL`
- [ ] Inserção/remoção mantendo o ciclo consistente
- [ ] Diferença entre versão circular simples e circular dupla

## Anotações
