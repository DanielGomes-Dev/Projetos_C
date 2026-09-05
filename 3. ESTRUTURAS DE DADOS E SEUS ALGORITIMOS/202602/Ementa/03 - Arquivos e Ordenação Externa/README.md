# Módulo 3 — Arquivos e Ordenação Externa

Quando o volume de dados excede a memória RAM disponível, as técnicas de estruturas de dados "em memória" (árvores, hash, heaps como vistos nos módulos 1, 4 e 5 quando aplicados apenas em memória principal) deixam de bastar — é preciso organizar e ordenar dados que vivem em disco, minimizando o número de acessos (I/O), que é ordens de magnitude mais lento que acesso à RAM. Este módulo cobre exatamente isso: como representar arquivos em C, como gerar partições ordenadas maiores que a memória disponível, e como intercalar essas partições até obter o arquivo totalmente ordenado.

**Pré-requisitos:** noções de E/S em C (`fopen`/`fread`/`fwrite`), heaps (módulo 5 — a seleção por substituição usa heap), e a ideia de merge sort (intercalação de duas sequências ordenadas).

## Subtópicos

- **[3.1 Arquivos Binários e Texto](3.1%20Arquivos%20Bin%C3%A1rios%20e%20Texto/README.md)** — como C representa e manipula arquivos texto vs binário, registros fixos vs variáveis, acesso sequencial vs direto.
- **[3.2 Geração de Partições Classificadas](3.2%20Gera%C3%A7%C3%A3o%20de%20Parti%C3%A7%C3%B5es%20Classificadas/README.md)** — como quebrar um arquivo grande em partições (runs) já ordenadas, incluindo a técnica de seleção por substituição.
- **[3.3 Intercalação de Partições](3.3%20Intercala%C3%A7%C3%A3o%20de%20Parti%C3%A7%C3%B5es/README.md)** — como combinar as partições geradas em 3.2 até chegar ao arquivo ordenado final, balanceada vs polifásica.
