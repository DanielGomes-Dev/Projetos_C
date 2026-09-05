# 7.2 Lista Linear Sequencial (Vetores)

## Resumo
Implementação de uma lista usando um vetor: elementos ficam em posições contíguas de memória, com um contador de tamanho atual separado da capacidade alocada. Acesso a qualquer posição é O(1) (indexação direta), mas inserção/remoção no meio exige deslocar os elementos seguintes — O(n). Contrasta diretamente com a [7.3 Lista simplesmente encadeada](<../7.3 LISTA SIMPLESMENTE ENCADEADA/index.md>), que tem o trade-off oposto.

## Onde estudar
- **Szwarcfiter** — seções 2.2–2.3 (Alocação Sequencial; Listas Lineares em Alocação Sequencial).
- **Celes** — cap. 5 ("Vetores e alocação dinâmica") — fundamentos de C sobre vetores (declaração, limites, equivalência com ponteiro, passagem para função); não codifica um algoritmo genérico de inserção/remoção com deslocamento.

## Checklist
- [ ] Implementar inserção/remoção/busca numa lista baseada em vetor
- [ ] Complexidade de cada operação (acesso O(1), inserção/remoção O(n))
- [ ] Estratégia de realocação quando o vetor enche (ex.: dobrar capacidade)

## Anotações
