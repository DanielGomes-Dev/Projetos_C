# 6.1 Merge Sort

## Resumo
Algoritmo de ordenação por divisão e conquista: divide o vetor ao meio recursivamente até sobrarem subvetores de tamanho 1 (trivialmente ordenados), depois intercala (*merge*) os subvetores ordenados dois a dois de volta. Complexidade **O(n log n)** garantida em todos os casos (melhor, médio e pior) — sua principal vantagem sobre o Quick Sort. É **estável** (mantém a ordem relativa de elementos iguais), mas usa memória auxiliar O(n) para a intercalação.

## Onde estudar
- ⚠️ **Celes não cobre merge sort** (confirmado na extração OCR do livro — cap. 16 tem só bolha e quicksort). Use Szwarcfiter/Cormen como referência principal deste subtópico.
- **Szwarcfiter** — seção 7.4 (Ordenação por Intercalação / Mergesort), com 7.4.1 (análise do algoritmo).
- **Cormen** — cap. 2 (Introdução, usa mergesort como primeiro exemplo de divisão e conquista) e Parte II para análise formal de recorrências (T(n) = 2T(n/2) + O(n)).

## Checklist
- [ ] Implementar a divisão recursiva + a função de intercalação (merge)
- [ ] Recorrência T(n) = 2T(n/2) + O(n) → O(n log n)
- [ ] Por que é estável e por que gasta memória O(n) extra

## Anotações
