# Passo a Passo Lista — lista04-EDA (Grafos)

Explicação devagar de cada questão já resolvida em `Qx/claude/main.c`, feita a partir do
código testado — ver o guia em [[../../../_modelo-de-arquivo]]. Teoria de apoio em
`02 - Grafos/2.1 .../Teoria - passo a passo/` e `2.2 .../Teoria - passo a passo/`.

1. [[Q1 - Quantidade de nós]] — `nn`, percurso simples da lista de vértices.
2. [[Q2 - Quantidade de arestas]] — `na`, soma de graus / 2 (grafo não orientado desta lista).
3. [[Q3 - Verificando coloração válida]] — `nao_tem_mesma_cor`, curto-circuito numa
   verificação universal.
4. [[Q4 - Grafo k-regular]] — `testek`, mesmo padrão de curto-circuito.
5. [[Q5 - Testando se dois grafos são iguais]] — `ig`, dupla inclusão fechada com
   comparação de grau.
