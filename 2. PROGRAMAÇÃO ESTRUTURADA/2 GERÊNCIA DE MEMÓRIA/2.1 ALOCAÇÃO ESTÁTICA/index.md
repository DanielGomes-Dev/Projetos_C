# 2.1 Alocação Estática

## Resumo
Memória cujo tamanho e tempo de vida são conhecidos em tempo de compilação: variáveis locais comuns (pilha/stack), variáveis globais e `static` (segmento de dados), e vetores de tamanho fixo declarados como `int v[10]`. Vantagem: acesso rápido, sem overhead de gerência; limitação: tamanho precisa ser conhecido antecipadamente, ao contrário da [2.2 Alocação dinâmica](<../2.2 LOCAÇÃO DINÂMICA/index.md>).

## Onde estudar
- **K&R** — cap. 4, seção 4.6 (Variáveis Estáticas); cap. 1 (vetores de tamanho fixo).

## Checklist
- [ ] Diferença entre memória de pilha (stack) e segmento de dados estático
- [ ] Por que `int v[n]` com `n` variável em tempo de execução não é alocação estática pura em C padrão

## Anotações
