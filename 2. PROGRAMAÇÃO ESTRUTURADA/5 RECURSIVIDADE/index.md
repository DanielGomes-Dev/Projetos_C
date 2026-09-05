# 5. Recursividade

## Resumo
Uma função que chama a si mesma para resolver um problema decompondo-o em subproblemas menores do mesmo tipo. Todo algoritmo recursivo precisa de: (1) caso(s) base — condição de parada — e (2) passo recursivo, que reduz o problema em direção ao caso base. Internamente, cada chamada empilha um novo *frame* na pilha de chamadas; recursão sem caso base ou que não converge causa *stack overflow*. Exemplos canônicos: fatorial, Fibonacci, busca binária, percursos em árvore, e os algoritmos de ordenação por divisão e conquista do bloco [6 Algoritmos de Ordenação](<../6 ALGORITMOS DE ORDENAÇÃO/index.md>) (Merge Sort, Quick Sort).

## Onde estudar
- **Celes** — cap. 4 ("Funções"), seção "Recursividade" — distingue recursão direta/indireta e reimplementa o fatorial (já visto em `while`/`for`) na forma recursiva.
- **K&R** — cap. 4, seção 4.10 (Recursão).
- **Szwarcfiter** — cap. 1 (Preliminares), seção 1.3 (Recursividade) — tratamento mais formal, incluindo relação com complexidade de algoritmos.

## Checklist
- [ ] Identificar caso base e passo recursivo em qualquer função recursiva
- [ ] Traçar a pilha de chamadas manualmente (ex.: `fatorial(4)`)
- [ ] Entender por que falta de caso base causa stack overflow
- [ ] Recursão vs. iteração: quando cada uma é mais natural/eficiente

## Anotações
