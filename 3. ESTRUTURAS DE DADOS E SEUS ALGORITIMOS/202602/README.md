# Estruturas de Dados e seus Algoritmos — 202602

Índice mestre do curso. A estrutura de pastas segue o sumário do livro-base (Szwarcfiter), e cada pasta tem um `README.md` com roteiro de leitura + notas de estudo elaboradas.

## Estrutura da pasta

- **`Ementa/`** — o conteúdo teórico organizado pelo sumário do livro-base: 5 módulos, 15 subtópicos, cada um com seu `README.md` (roteiro de leitura, notas de estudo, exemplos em C, pontos de atenção).
- **`Livros/`** — os 4 livros-texto em PDF (ver tabela abaixo).
- **`ListasExercicios/`** — listas de exercícios do curso já resolvidas: PDF do enunciado + solução em C por questão (`Qx/claude/main.c`), organizadas em `lista01-EDA`, `lista02-EDA`, `lista03-EDA` e listas de revisão temáticas. Algumas trazem implementações genéricas reutilizadas nos exemplos em C da `Ementa/` (ex.: `TAB`, `TABB`, `TAVL` → árvores binárias, BST e AVL).

## Os 4 livros e o papel de cada um

| # | Livro | Papel no curso |
|---|---|---|
| 📘 **SZ** | Jayme Luiz Szwarcfiter — *Estruturas de Dados e Seus Algoritmos*, 3ª ed. ([`Livros/02 - Estruturas de dados e seus algoritmos (3a. ed.). (Jayme Luiz Szwarcfiter) AVL.pdf`](Livros/02%20-%20Estruturas%20de%20dados%20e%20seus%20algoritmos%20(3a.%20ed.).%20(Jayme%20Luiz%20Szwarcfiter)%20AVL.pdf)) | **Livro-base do curso.** O sumário dele é a origem da árvore de pastas deste curso — segue ele como espinha dorsal de leitura, na ordem 1→5. |
| 📗 **CO** | Thomas H. Cormen et al. — *Algoritmos: Teoria e Prática*, 3ª ed. ([`Livros/01 Algoritmos - Teoria e Prática 3ed-thomas-cormen.pdf`](Livros/01%20Algoritmos%20-%20Teoria%20e%20Pr%C3%A1tica%203ed-thomas-cormen.pdf)) | **Aprofundamento teórico.** Prova de corretude, análise de complexidade rigorosa (notação assintótica), e as estruturas mais avançadas (árvores rubro-negras, heaps binomiais/Fibonacci) quando o Szwarcfiter for mais raso. Usar depois de entender o conceito pelo SZ. |
| 📙 **CE** | Waldemar Celes et al. — *Introdução a Estruturas de Dados* ([`Livros/00 - introduao-a-estrutura-de-dados-waldemar-celes-5-pdf-free.pdf`](Livros/00%20-%20introduao-a-estrutura-de-dados-waldemar-celes-5-pdf-free.pdf)) | **Implementação prática em C.** Foco em como programar cada estrutura (structs, ponteiros, malloc/free) — usar quando for para a fase de codar. |
| 📕 **KR** | Kernighan & Ritchie — *C: A Linguagem de Programação* ([`Livros/04 - C a linguagem de programação (Brian W. Kernighan, Dennis M. Ritchie).pdf`](Livros/04%20-%20C%20a%20linguagem%20de%20programa%C3%A7%C3%A3o%20(Brian%20W.%20Kernighan%2C%20Dennis%20M.%20Ritchie).pdf)) | **Referência transversal de C.** Não é sobre estruturas de dados — é onde consultar dúvidas pontuais de ponteiros, structs, alocação dinâmica, arrays que aparecem *implementando* qualquer estrutura. Sem capítulo fixo por tópico. |

> Nota: não foi possível abrir os PDFs para conferir a paginação exata nesta máquina (falta `poppler`/`pdftoppm`). Os capítulos/seções citados nos roteiros de cada pasta são os capítulos padrão dessas edições consolidadas — confira a página exata ao abrir o PDF e ajuste se a edição específica divergir.

## Roteiro geral

| Módulo | Subtópicos | Pasta | Livros principais |
|---|---|---|---|
| 1. Árvores | Binárias · Binárias de Busca · AVL · B · B+ | `Ementa/01 - Árvores/` | SZ (base) · CO (teoria/prova) · CE (implementação em C) |
| 2. Grafos | Conceitos e Representações · Algoritmos em Grafos | `Ementa/02 - Grafos/` | SZ (base) · CO (algoritmos clássicos: BFS/DFS, MST, caminhos mínimos) |
| 3. Arquivos e Ordenação Externa | Arquivos Binários e Texto · Geração de Partições · Intercalação | `Ementa/03 - Arquivos e Ordenação Externa/` | SZ (base, único com foco em memória secundária) |
| 4. Tabelas Hash | Memória Principal · Memória Secundária | `Ementa/04 - Tabelas Hash/` | SZ (base) · CO (teoria de hashing) · CE (implementação em C) |
| 5. Heaps e Listas de Prioridade | Memória Principal · Memória Secundária · Listas de Prioridade | `Ementa/05 - Heaps e Listas de Prioridade/` | SZ (base) · CO (heapsort, heaps binomiais/Fibonacci) |

## Ordem de estudo sugerida

Segue a numeração das pastas (1 → 5), que já reflete uma progressão didática: estruturas em memória principal com foco crescente em complexidade (árvores simples → balanceadas → grafos) e depois os tópicos de "escala" (memória secundária, hashing, heaps/filas de prioridade). Dentro de cada módulo, siga a ordem numérica das subpastas (x.1 → x.2 → ...).

## Como cada `README.md` de tópico (dentro de `Ementa/`) está organizado

1. **Objetivo de aprendizagem**
2. **Roteiro de leitura** — SZ / CO / CE / KR (só os que se aplicam ao tópico)
3. **Notas de estudo elaboradas** — conceitos, invariantes, complexidade, comparações, passo a passo de exemplos concretos
4. **Exemplos em C** — código comentado da(s) operação(ões) central(is) do tópico; para Árvores Binárias/BST/AVL (1.1-1.3), trechos reais reaproveitados de `ListasExercicios/lista0X-EDA/T.../`
5. **Pontos de atenção / pegadinhas comuns de prova**
6. **Anotações pessoais** (vazio, pra você preencher)
7. **Exercícios resolvidos** (vazio, pra você preencher)
