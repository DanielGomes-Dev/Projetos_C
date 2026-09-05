# Resumo dos Livros — 2. Gerência de Memória

## Celes — Introdução a Estruturas de Dados (Cap. 4 e Cap. 5)
> Livro em PDF digitalizado sem texto pesquisável; conteúdo abaixo obtido via extração OCR (`Livros/00 - celes extracao google.md`) e conferido no texto corrido — ver [[2.1 ALOCAÇÃO ESTÁTICA/Resumo dos Livros|2.1]], [[2.2 LOCAÇÃO DINÂMICA/Resumo dos Livros|2.2]] e [[2.3 PONTEIROS/Resumo dos Livros|2.3]] para o detalhamento seção por seção.

Correção: não há um único "capítulo 3 de Ponteiros e Alocação Dinâmica" isolado — Celes introduz ponteiros dentro do **Cap. 4** ("Funções", motivado pelo problema de uma função devolver mais de um resultado ao chamador) e só formaliza alocação dinâmica no **Cap. 5** ("Vetores e alocação dinâmica"), conectando-a diretamente ao problema de vetores de tamanho fixo. A biblioteca usada é mais enxuta que a do resumo genérico anterior sugeria: Celes cobre apenas `malloc`/`free` (não `calloc`/`realloc`) — mas com bastante peso em diagramas de memória (pilha vs. área de alocação dinâmica) e nos dois erros mais comuns: esquecer o `free` (vazamento) e acessar a memória após liberá-la.

## K&R — C: A Linguagem de Programação (Cap. 5)

## K&R — C: A Linguagem de Programação (Cap. 5)
Esta é uma síntese geral; os trechos específicos do capítulo 5 (Apontadores e Arranjos) são detalhados nos resumos dos subtópicos [2.2 Locação Dinâmica](<2.2 LOCAÇÃO DINÂMICA/Resumo dos Livros.md>) e [2.3 Ponteiros](<2.3 PONTEIROS/Resumo dos Livros.md>). Em linhas gerais, o capítulo 5 trata apontadores como o mecanismo central de C para endereçar memória — seja ela estática (variáveis e vetores comuns) ou dinâmica (blocos obtidos por um alocador, como o `aloca`/`libera` que o próprio livro implementa como exemplo pedagógico, análogo ao `calloc`/`cfree` da biblioteca padrão). É descrito no livro como "o aspecto mais característico e ao mesmo tempo mais problemático da linguagem" quando usado sem disciplina, mas também como o que dá a C sua eficiência e proximidade com a máquina.

## Síntese
Celes organiza o assunto de forma gradual em dois capítulos (ponteiros no Cap. 4, motivados por passagem de parâmetro; alocação dinâmica no Cap. 5, motivada pela limitação de vetores estáticos), enquanto K&R trata ponteiros como o fio condutor de todo o capítulo 5, do qual a alocação dinâmica é uma aplicação central. Os dois livros concordam no ponto-chave: entender ponteiros é pré-requisito para entender alocação dinâmica, que por sua vez é pré-requisito para estruturas de dados encadeadas ([[../7 TIPOS ABSTRATOS DE DADOS/7.3 LISTA SIMPLESMENTE ENCADEADA/Resumo dos Livros|7.3]]).
