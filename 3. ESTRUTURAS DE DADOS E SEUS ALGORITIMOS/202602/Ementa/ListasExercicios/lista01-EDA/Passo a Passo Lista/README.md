# Passo a Passo Lista — lista01-EDA (1.1 Árvores Binárias)

Explicação devagar de cada questão já resolvida em `Qx/claude/main.c`. Ver o guia de
formatação em [[../../../_modelo-de-arquivo]] e, para a teoria de base, [[../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/README|1.1 Teoria - passo a passo]].

1. [[Q1 - Cópia de uma árvore]] — recursão que constrói uma árvore nova, nó a nó.
2. [[Q2 - Espelho de uma árvore]] — mesma recursão de Q1, trocando esquerda ↔ direita.
3. [[Q3 - Maior elemento da árvore]] — busca por força bruta (árvore sem ordenação).
4. [[Q4 - Menor elemento da árvore]] — espelho de Q3 (troca o sentido da comparação).
5. [[Q5 - Testando se duas árvores são iguais]] — recursão que compara duas árvores em paralelo.
6. [[Q6 - Retirar elementos pares da árvore]] — pós-ordem + realocação dos filhos do nó removido (a questão mais delicada da lista).
7. [[Q7 - Colorindo uma árvore balanceada (vermelho-preto)]] — colorir por paridade de nível numa árvore perfeita.
8. [[Q8 - Quantidade de nós internos]] — grau > 0.
9. [[Q9 - Quantidade de nós folha]] — grau = 0 (espelho de Q8).
