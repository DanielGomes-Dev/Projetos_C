# 7.7 Matriz

## Resumo
Vetor multidimensional (tipicamente 2D — `int m[LINHAS][COLUNAS]`), armazenado em C em ordem *row-major* (uma linha inteira ocupa posições contíguas antes da próxima começar). Pode ser declarada estaticamente (tamanho fixo em tempo de compilação) ou alocada dinamicamente (vetor de ponteiros, cada um apontando para uma linha alocada separadamente — combina [2.2 Alocação dinâmica](<../../2 GERÊNCIA DE MEMÓRIA/2.2 LOCAÇÃO DINÂMICA/index.md>) com [2.3 Ponteiros](<../../2 GERÊNCIA DE MEMÓRIA/2.3 PONTEIROS/index.md>)). Passagem para funções exige indicar o número de colunas (para o compilador calcular deslocamentos), a menos que se use o esquema de vetor de ponteiros.

## Onde estudar
- **K&R** — cap. 5, seção 5.9 (Ponteiros e Arranjos Multidimensionais).
- **Celes** — cap. 6 ("Matrizes"), capítulo dedicado — cobre matriz estática, dois esquemas de matriz dinâmica (vetor simples linearizado `i*n+j`, e vetor de ponteiros) e ainda a representação compacta de matriz simétrica.

## Checklist
- [ ] Declarar e percorrer uma matriz estática
- [ ] Alocar dinamicamente uma matriz (vetor de ponteiros para linhas)
- [ ] Passar matriz para função corretamente (estática vs. dinâmica)
- [ ] Entender ordem row-major e seu impacto em performance de cache

## Anotações
