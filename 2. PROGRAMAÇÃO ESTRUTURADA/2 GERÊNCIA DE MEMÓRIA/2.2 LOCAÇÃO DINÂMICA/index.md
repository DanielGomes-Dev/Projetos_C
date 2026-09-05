# 2.2 Alocação Dinâmica

## Resumo
Alocação de memória em tempo de execução, no heap, via `malloc`/`calloc`/`realloc` (biblioteca `stdlib.h`) e liberação com `free`. É o que permite estruturas que crescem/encolhem em tempo de execução — todas as listas encadeadas do bloco [7 Tipos Abstratos de Dados](<../../7 TIPOS ABSTRATOS DE DADOS/index.md>) dependem disso. Erros clássicos a evitar: esquecer `free` (memory leak), usar ponteiro após `free` (dangling pointer), `free` duplo, e não checar se `malloc` retornou `NULL`.

## Onde estudar
- **K&R** — cap. 5 (Apontadores e Arranjos), seção 5.4 (Ponteiros e Arranjos) e Apêndice B (Biblioteca Padrão, `malloc`/`free`).
- **Celes** — cap. 5 ("Vetores e alocação dinâmica"), seção "Alocação dinâmica" — cobre só `malloc`/`free` (não `calloc`/`realloc`), com bom detalhamento visual da diferença entre o ponteiro (pilha) e a área apontada (heap).

## Checklist
- [ ] `malloc` vs. `calloc` vs. `realloc`
- [ ] Sempre `free` o que foi `malloc`ado
- [ ] Checar retorno `NULL` de `malloc`
- [ ] Entender memory leak e dangling pointer

## Anotações
