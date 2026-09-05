# 1.8 Escopo e Variáveis Globais

## Resumo
Regras de visibilidade e tempo de vida de variáveis: locais (automáticas, vivem na pilha da função), globais/externas (`extern`, visíveis no arquivo todo e possivelmente em outros via [4 Programação com Módulos](<../../4 PROGRAMAÇÃO COM MÓDULOS/index.md>)), e `static` (vida útil do programa inteiro, mas escopo restrito — ver também [2.1 Alocação Estática](<../../2 GERÊNCIA DE MEMÓRIA/2.1 ALOCAÇÃO ESTÁTICA/index.md>)). Cuidado: variáveis globais facilitam efeitos colaterais difíceis de rastrear — usar com moderação.

## Onde estudar
- **Celes** — cap. 4 ("Funções"), seções "Variáveis globais" e "Variáveis estáticas" — mostra `somaprod` reescrita com globais só para, na sequência, recomendar evitá-las; `static` local é motivado por um exemplo concreto (função que "lembra" quantas vezes já foi chamada).
- **K&R** — cap. 4, seções 4.4–4.6 (Variáveis Externas, Regras de Escopo, Variáveis Estáticas).

## Checklist
- [ ] Escopo de bloco vs. escopo de arquivo
- [ ] `extern` para compartilhar globais entre arquivos
- [ ] `static` em variável local (vida útil) vs. em variável global (visibilidade restrita ao arquivo)

## Anotações
