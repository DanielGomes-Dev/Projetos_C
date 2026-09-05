# 7.1 Conceitos

## Resumo
Um TAD (Tipo Abstrato de Dados) especifica **o que** uma estrutura faz (as operações e seu contrato), sem expor **como** é implementada internamente — o usuário do TAD só interage com a interface. Em C, isso é aproximado com `struct` + um conjunto de funções que operam sobre ponteiros para essa `struct`, geralmente separadas em `.h` (interface) e `.c` (implementação) — ver [4 Programação com Módulos](<../../4 PROGRAMAÇÃO COM MÓDULOS/index.md>). Vantagem central: a implementação pode mudar (ex.: trocar vetor por lista encadeada) sem afetar quem usa o TAD, desde que a interface seja mantida.

## Onde estudar
- **Celes** — cap. 9 ("Tipos abstratos de dados") — introduz o conceito (com o TAD `Ponto` como exemplo completo) antes de entrar nas implementações concretas dos capítulos seguintes.

## Checklist
- [ ] Diferenciar interface (contrato) de implementação
- [ ] Por que encapsular a representação interna importa (ocultação de informação)
- [ ] Como C aproxima TADs sem suporte nativo a classes

## Anotações
