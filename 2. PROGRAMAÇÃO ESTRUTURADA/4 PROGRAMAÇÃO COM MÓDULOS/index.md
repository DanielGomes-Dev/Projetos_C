# 4. Programação com Módulos

## Resumo
Organização de um programa C em múltiplos arquivos-fonte (`.c`) e cabeçalhos (`.h`): separação entre interface (protótipos, `struct`, `#define` em `.h`) e implementação (código em `.c`); `#include` com `""` (arquivos locais) vs. `<>` (biblioteca padrão); guardas de inclusão (`#ifndef`/`#define`/`#endif`) para evitar inclusão duplicada; `extern` para compartilhar variáveis globais entre módulos; compilação separada e *linkagem* (cada `.c` compilado a um `.o`, depois ligados).

## Onde estudar
- **Celes** — cap. 9 ("Tipos abstratos de dados"), seção "Módulos e compilação em separado" — referência principal deste tópico: exemplo completo com comandos `gcc -c`/`gcc -o` reais, e o padrão `.h` público / `.c` privado usado em todo TAD do resto do livro (ver [[../7 TIPOS ABSTRATOS DE DADOS/7.1 CONCEITOS/index|7.1]]).
- **K&R** — cap. 4, seção 4.5 (Cabeçalhos) e a discussão de organização multi-arquivo espalhada no capítulo; o pré-processador está no cap. 4/Apêndice A.

## Checklist
- [ ] Separar interface (`.h`) de implementação (`.c`)
- [ ] Guardas de inclusão (`#ifndef`)
- [ ] `extern` para variáveis globais compartilhadas
- [ ] Como funciona a compilação separada + linkagem

## Anotações
