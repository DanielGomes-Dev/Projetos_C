# Teoria - passo a passo — 5.2 Árvores B+

Um conceito por arquivo, expandindo em passo a passo o conteúdo já sintetizado no
`README.md` deste subtópico. Ver o guia completo em [[../../../_modelo-de-explicacao]].

## Ordem de leitura

1. [[Teoria 01 - As duas diferenças estruturais entre B e B+]] — dados só em folha; folhas
   encadeadas; por que isso importa (nós internos mais "gordos", menor altura).
2. [[Teoria 02 - Busca por igualdade numa árvore B+]] — por que a busca sempre termina na
   folha, mesmo achando a chave num nó interno como separador antes.
3. [[Teoria 03 - Busca por intervalo (range query)]] — a operação que justifica a árvore
   B+ existir: descida única + percurso pela lista de folhas.
4. [[Teoria 04 - Complexidade e quando usar B vs. B+]] — tabela comparativa e critério de
   decisão baseado no padrão de uso (igualdade vs. intervalo).

Isso fecha a teoria do módulo 05 (Árvore B e B+). Próximo módulo:
[[../../../06 - Heaps e Listas de Prioridade/README|06 - Heaps e Listas de Prioridade]].
