# 7.6 Fila e Pilha

## Resumo
Dois TADs lineares com disciplina de acesso restrita:
- **Pilha (stack)**: LIFO (*last in, first out*) — inserção e remoção só pelo topo. Operações: `push`, `pop`, `top`/`peek`. Usada implicitamente em toda chamada de função recursiva (ver [5 Recursividade](<../../5 RECURSIVIDADE/index.md>)), em avaliação de expressões e em desfazer/refazer (undo).
- **Fila (queue)**: FIFO (*first in, first out*) — inserção no fim (`enqueue`), remoção no início (`dequeue`). Usada em filas de espera, buffers e busca em largura.

Ambas podem ser implementadas sobre vetor ([7.2](<../7.2 LISTA LINEAR SEQUENCIAL (VETORES)/index.md>)) ou lista encadeada ([7.3](<../7.3 LISTA SIMPLESMENTE ENCADEADA/index.md>)/[7.4](<../7.4 LISTA DUPLAMENTE ENCADEADA/index.md>)) — a lista encadeada evita o problema de "fila cheia" por deslocamento que o vetor simples tem.

## Onde estudar
- **Szwarcfiter** — seção 2.4 (Pilhas e Filas, alocação sequencial) e 2.7.2 (Pilhas e filas, alocação encadeada); 2.5 traz a aplicação clássica de pilha em Notação Polonesa.
- **Cormen** — cap. 10, seção 10.1 (Pilhas e Filas).
- **Celes** — cap. 11 (Pilhas) e cap. 12 (Filas), dedicados — cada um com implementação sobre vetor e sobre lista, mais a aplicação da calculadora pós-fixada (pilha) e a fila circular via aritmética modular (`% N`).

## Checklist
- [ ] Implementar pilha e fila sobre vetor e sobre lista encadeada
- [ ] `push`/`pop`/`top` e `enqueue`/`dequeue`/`front`
- [ ] Tratar os casos de estrutura vazia (underflow) e cheia (overflow, se sobre vetor)
- [ ] Aplicação de pilha na avaliação de expressões (notação polonesa/pós-fixa)

## Anotações
