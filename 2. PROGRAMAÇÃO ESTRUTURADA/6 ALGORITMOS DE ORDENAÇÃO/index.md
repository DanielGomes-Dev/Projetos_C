# 6. Algoritmos de Ordenação

## Resumo
Algoritmos para reorganizar uma coleção de elementos em ordem (crescente ou decrescente). O curso foca nos dois algoritmos de divisão e conquista — [6.1 Merge Sort](<6.1 MERGE SORT/index.md>) e [6.2 Quick Sort](<6.2 QUICK SORT/index.md>) — que usam [recursividade](<../5 RECURSIVIDADE/index.md>) diretamente. Vale contextualizar com os métodos simples (bolha, inserção, seleção — O(n²)) para entender por que os métodos O(n log n) são preferidos em coleções maiores.

## Onde estudar nos livros
- **Szwarcfiter** — cap. 7 (Algoritmos de Ordenação): 7.2 Bolha, 7.3 Inserção, 7.4 Mergesort, 7.5 Quicksort, 7.6 Heapsort, 7.7 limite inferior teórico.
- **Cormen** — Parte II (Ordenação e estatísticas de ordem, cap. 6–9): tratamento formal com análise de complexidade rigorosa.
- **Celes** — cap. 16 ("Ordenação") — só bolha e quicksort (**não cobre merge sort nem seleção/inserção**); ver [[6.1 MERGE SORT/Resumo dos Livros|6.1]] para o aviso completo. Traz um desenvolvimento único e valioso: generalização do bubble sort para qualquer tipo via `void*` + ponteiro de função, no mesmo espírito de `qsort`/`bsearch` da biblioteca padrão.

## Checklist
- [ ] Complexidade de cada método (melhor/médio/pior caso)
- [ ] Estabilidade (mergesort é estável; quicksort tradicional não é)
- [ ] Ordenação in-place vs. com memória auxiliar

## Anotações
