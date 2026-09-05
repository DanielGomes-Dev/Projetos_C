# 7.4 Lista Duplamente Encadeada

## Resumo
Extensão da [7.3 Lista simplesmente encadeada](<../7.3 LISTA SIMPLESMENTE ENCADEADA/index.md>): cada nó guarda ponteiros para o **próximo** (`next`) *e* o **anterior** (`prev`). Vantagem: percurso nos dois sentidos e remoção de um nó em O(1) quando já se tem o ponteiro para ele (não precisa percorrer para achar o anterior). Custo: mais memória por nó (dois ponteiros em vez de um) e mais cuidado ao manter os dois links consistentes em toda inserção/remoção.

## Onde estudar
- **Szwarcfiter** — seção 2.7.4 (Listas duplamente encadeadas).
- **Celes** — cap. 10 ("Listas encadeadas"), seção "Listas duplamente encadeadas".

## Checklist
- [ ] Estrutura do nó com `prev` e `next`
- [ ] Atualizar corretamente os dois ponteiros em toda inserção/remoção
- [ ] Comparar com lista simples: quando compensa o custo extra de memória

## Anotações
