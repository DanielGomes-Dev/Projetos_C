# Ementa — Estruturas de Dados e seus Algoritmos (202602)

Conteúdo teórico organizado pelo sumário do livro-base (Szwarcfiter): 5 módulos, 15
subtópicos. Cada subtópico tem um `README.md` (roteiro de leitura + notas de estudo) e,
sendo construído progressivamente, uma pasta `Teoria - passo a passo/` — um conceito por
arquivo, explicado devagar, com exemplos tirados dos PDFs de aula e dos 4 livros-base.

> **Organização espelha o projeto de Cálculo 2** (`3. CÁLCULO 2\00 - Ementa\`): pasta por
> capítulo, subpasta por subitem, e o par de arquivos-modelo abaixo tem o mesmo papel lá e
> aqui — só adaptados de matemática para código/algoritmos.

## Modelos (guias de formatação — ler antes de escrever conteúdo novo)

- [[_modelo-de-explicacao]] — guia de como **explicar um conceito de teoria** (arquivos
  `Teoria 0X - ...` dentro de `Teoria - passo a passo/`). Lista as dificuldades do Daniel
  (mesmas de Cálculo 2, traduzidas para código/algoritmos) e a regra específica deste
  curso: todo exemplo precisa vir de um PDF de aula ou de um dos 4 livros, com a origem
  citada.
- [[_modelo-de-arquivo]] — guia de como **explicar a resolução de uma questão de lista já
  resolvida em código**, dentro de uma pasta `Passo a Passo Lista/` (uma por lista, ver
  abaixo). O código (`Qx/claude/main.c`) não é reescrito — só ganha uma explicação passo a
  passo ao lado.

## Onde ficam os PDFs e as listas resolvidas

> **`Ementa/ListasExercicios/`** é a pasta única e atualizada com todos os PDFs de aula e
> todas as listas já resolvidas (`lista0X-EDA/Qx/claude/main.c`). A antiga `202602/ListasExercicios/`
> (fora de `Ementa/`) ficou desatualizada — não usar como fonte.

Mapeamento lista → subtópico:

| Lista | Subtópico(s) |
|---|---|
| `lista01-EDA` | 1.1 Árvores Binárias |
| `lista02-EDA` | 1.2 Árvores Binárias de Busca |
| `lista03-EDA` | 1.3 Árvores AVL |
| `lista04-EDA` | 2.1–2.2 Grafos |
| `lista050607-EDA` | 3.1–3.3 Arquivos e Ordenação Externa |
| `lista_revisao_TLSE-EDA`, `lista_revisao_tipos_primitivos-EDA`, `lista_revisao_vetor-EDA` | Revisão/pré-requisitos (fora da ementa numerada, análogo a `00 - Pré-requisitos` em Cálculo 2) |

Módulos 4 (Tabelas Hash), 5 (Árvore B e B+) e 6 (Heaps) ainda não têm lista própria em
`ListasExercicios/`.

## Como usar

1. Siga a ordem dos módulos (1 → 6) e, dentro de cada um, a ordem numérica dos subtópicos.
2. Antes de cada lista de exercícios do subtópico, estude a teoria:
   - **Aprendendo do zero:** `Teoria - passo a passo/` (quando existir).
   - **Revisando rápido / referência de código:** o `README.md` do subtópico (roteiro de
     leitura + notas de estudo + exemplos em C).
3. Cada lista já resolvida em `ListasExercicios/lista0X-EDA/` ganha uma pasta
   `Passo a Passo Lista/` com a explicação de cada questão, feita a partir do código já
   testado em `Qx/claude/main.c`.
4. Os 4 livros-base estão em `Ementa/Livros/` — ver a tabela de papéis no `202602/README.md`
   (raiz do curso).

## Estado do projeto

| Módulo | Subtópicos | `Teoria - passo a passo/` | `Passo a Passo Lista/` |
|---|---|---|---|
| 1 — Árvores | 1.1–1.3 | 🚧 em construção (1.1) | 🚧 a fazer (lista01–03) |
| 2 — Grafos | 2.1–2.2 | 🚧 a fazer | 🚧 a fazer (lista04) |
| 3 — Arquivos e Ordenação Externa | 3.1–3.3 | 🚧 a fazer | 🚧 a fazer (lista050607) |
| 4 — Tabelas Hash | 4.1–4.2 | 🚧 a fazer | — (sem lista própria ainda) |
| 5 — Árvore B e B+ | 5.1–5.2 | 🚧 a fazer | — (sem lista própria ainda) |
| 6 — Heaps e Listas de Prioridade | 6.1–6.3 | 🚧 a fazer | — (sem lista própria ainda) |

Se achar um erro de conta, um exemplo com origem errada, ou um link quebrado, é só avisar.
