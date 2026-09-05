# 8. Busca em Lista

## Resumo
Localizar um elemento numa coleção. Dois algoritmos centrais:
- **Busca sequencial (linear)**: percorre a lista do início ao fim comparando cada elemento — O(n), funciona em qualquer lista (ordenada ou não), inclusive nas encadeadas do [bloco 7](<../7 TIPOS ABSTRATOS DE DADOS/index.md>).
- **Busca binária**: só funciona em vetor **ordenado** ([7.2](<../7 TIPOS ABSTRATOS DE DADOS/7.2 LISTA LINEAR SEQUENCIAL (VETORES)/index.md>)) com acesso O(1) por índice; compara o elemento do meio, descarta metade do espaço de busca a cada passo — O(log n). É naturalmente recursiva (ver [5 Recursividade](<../5 RECURSIVIDADE/index.md>)), embora também tenha versão iterativa.

## Onde estudar
- **Cormen** — busca sequencial aparece como exemplo introdutório no cap. 2; busca binária é tratada como exercício/aplicação de divisão e conquista.
- **Szwarcfiter** — trata busca sequencial e binária junto com o capítulo de listas lineares (cap. 2).
- **Celes** — cap. 17 ("Busca"), capítulo dedicado, logo depois de ordenação (cap. 16) — inclui `bsearch` da biblioteca padrão e alerta explicitamente que busca binária não funciona em lista encadeada (não há acesso O(1) por índice), antes de partir para árvores de busca (fora do escopo deste curso).

## Checklist
- [ ] Implementar busca sequencial e busca binária (iterativa e recursiva)
- [ ] Por que busca binária exige vetor ordenado com acesso indexado (não funciona bem em lista encadeada)
- [ ] Complexidade: O(n) vs. O(log n) — quando cada uma compensa

## Anotações
