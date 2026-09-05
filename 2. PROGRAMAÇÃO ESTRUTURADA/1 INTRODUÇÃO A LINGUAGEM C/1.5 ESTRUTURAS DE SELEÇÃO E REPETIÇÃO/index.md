# 1.5 Estruturas de Seleção e Repetição

## Resumo
Controle de fluxo: `if`/`else`/`else if`, `switch`/`case` (com `break` e fall-through), e os três laços `while`, `do-while` e `for`. Também `break`/`continue`/`goto`. Ponto de atenção clássico: esquecer `break` num `case` do `switch` causa fall-through silencioso; `for` em C é apenas açúcar sintático para um `while` com inicialização/incremento explícitos.

## Onde estudar
- **Celes** — cap. 3 ("Controle de fluxo"), capítulo dedicado — reimplementa o cálculo de fatorial em `while`/`for`/`do-while` lado a lado, e traz um alerta valioso: `continue` dentro de `while` pode pular o incremento e travar o laço num loop infinito (não acontece em `for`).
- **K&R** — cap. 3 (Fluxo de Controle), completo.

## Checklist
- [ ] Equivalência entre `for` e `while`
- [ ] Fall-through em `switch` e uso correto de `break`
- [ ] Diferença `while` (testa antes) vs. `do-while` (testa depois)
- [ ] Uso (e riscos) de `goto`

## Anotações
