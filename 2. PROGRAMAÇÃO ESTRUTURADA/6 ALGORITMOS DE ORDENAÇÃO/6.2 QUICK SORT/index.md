# 6.2 Quick Sort

## Resumo
Algoritmo de ordenação por divisão e conquista: escolhe um elemento *pivô*, particiona o vetor em "menores que o pivô" / "maiores que o pivô" (o pivô já fica em sua posição final), e recursivamente ordena as duas partições. Complexidade média **O(n log n)**, mas pior caso **O(n²)** (ocorre com má escolha de pivô, ex.: vetor já ordenado + pivô sempre no extremo). Ordena in-place (memória O(log n) da pilha de recursão), mas **não é estável** na forma clássica.

## Onde estudar
- **Celes** — cap. 16 ("Ordenação"), seção "Ordenação rápida" — pivô fixo no primeiro elemento, desenvolvido passo a passo sobre um vetor de exemplo; conecta ao `qsort` real de `stdlib.h` ao final.
- **Szwarcfiter** — seção 7.5 (Ordenação Rápida / Quicksort), com 7.5.1 (análise do algoritmo).
- **Cormen** — cap. 7 (Quicksort), com análise detalhada de melhor/médio/pior caso e estratégias de escolha de pivô (aleatorizado, mediana de três).

## Checklist
- [ ] Implementar partição (esquema de Lomuto ou Hoare) + recursão
- [ ] Por que o pior caso é O(n²) e como evitá-lo na prática (pivô aleatório)
- [ ] Comparar com [Merge Sort](<../6.1 MERGE SORT/index.md>): estabilidade, memória, garantia de caso

## Anotações
