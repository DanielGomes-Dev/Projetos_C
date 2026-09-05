# 7.3 Lista Simplesmente Encadeada

## Resumo
Lista onde cada nó (`struct` alocada dinamicamente — ver [2.2](<../../2 GERÊNCIA DE MEMÓRIA/2.2 LOCAÇÃO DINÂMICA/index.md>) e [2.3](<../../2 GERÊNCIA DE MEMÓRIA/2.3 PONTEIROS/index.md>)) guarda um dado e um ponteiro `next` para o próximo nó; o último aponta para `NULL`. Inserção/remoção no início é O(1); acesso a uma posição arbitrária é O(n) (não há indexação direta — é preciso percorrer a partir da cabeça). Operações típicas a implementar: inserir no início/fim, remover, buscar, percorrer, liberar a lista inteira (evitando memory leak).

## Onde estudar
- **Szwarcfiter** — seção 2.7.1 (Listas simplesmente encadeadas), dentro de 2.6–2.7 (Alocação Encadeada).
- **Cormen** — cap. 10, seção 10.2 (Listas Ligadas).
- **Celes** — cap. 10 ("Listas encadeadas"), capítulo dedicado — TAD `Lista` completo (`lst_cria`/`lst_insere`/`lst_busca`/`lst_retira`/`lst_libera`).

## Checklist
- [ ] Estrutura do nó (`struct nó { tipo dado; struct nó *next; }`)
- [ ] Inserção/remoção no início, no fim e no meio
- [ ] Percurso e liberação completa da lista (sem leaks)
- [ ] Caso especial da lista vazia e de um único elemento

## Anotações
