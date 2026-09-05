# 1.7 Passagem de Parâmetros por Valor e por Referência

## Resumo
Em C, todo parâmetro é passado **por valor** — a função recebe uma cópia. "Passagem por referência" em C é simulada passando um **ponteiro** para a variável original, permitindo que a função altere o valor apontado (`void f(int *x) { *x = 10; }`). Vetores são um caso especial: o nome do vetor já "decai" para um ponteiro ao ser passado, então a função sempre pode alterar o conteúdo do vetor original.

## Onde estudar
- **Celes** — cap. 4 ("Funções"), seções "Ponteiro de variáveis" e "Passando ponteiros para funções" — ponto mais insistido do livro, com a função `somaprod` mostrada errada (sem ponteiro) e depois corrigida, e o exemplo canônico `troca`, quase idêntico ao do K&R.
- **K&R** — cap. 5 (Apontadores e Arranjos), seção 5.2 (Ponteiros e Argumentos de Funções); cap. 1, seção 1.8 (Argumentos — Chamada por Valor).

## Checklist
- [ ] Por que `void f(int x)` nunca altera o valor original
- [ ] Como usar `int *p` para simular passagem por referência
- [ ] Por que vetores "se comportam" como passados por referência

## Anotações
