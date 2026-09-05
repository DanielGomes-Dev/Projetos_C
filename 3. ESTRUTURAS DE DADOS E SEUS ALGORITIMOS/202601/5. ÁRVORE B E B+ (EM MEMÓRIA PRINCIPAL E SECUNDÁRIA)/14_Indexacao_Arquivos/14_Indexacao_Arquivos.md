## 1. INDEXAÇÃO DE ARQUIVOS

### CONSULTA A ARQUIVOS BINÁRIOS GRANDES

→ **Arquivos binários grandes**

* Busca sequencial é muito custosa
* Se arquivo estiver ordenado pode-se fazer busca binária, mas para arquivos grandes ainda não é eficiente o suficiente

→ **É possível acelerar a busca usando duas técnicas:**

* Acesso via cálculo do endereço do registro (**hashing**)
* Acesso via estrutura de dados auxiliar (**índice**)

### ÍNDICE

→ **Índice é uma estrutura de dados que serve para localizar registros no arquivo de dados**

→ **Cada entrada do índice contém**

* Valor da chave
* Ponteiro para o arquivo de dados

→ **Pode-se pensar então em dois arquivos: de índice e de dados**

→ **Isso é eficiente?**

### EXEMPLO DE ÍNDICE PLANO

| CHAVE | PONTEIRO |  | COD | NOME |
| --- | --- | --- | --- | --- |
| 0 | 3 |  | 0 | 23 JOSE |
| 1 | 5 |  | 1 | 10 MARIO |
| 2 | 10 |  | 2 | 5 ANA |
| 3 | 15 |  | 3 | 15 MARCIA |
| 4 | 16 |  | 4 | 3 JULIO |
| 5 | 21 |  | 5 | 16 BEATRIZ |
| 6 | 23 |  | 6 | 21 CAMILA |
| **Arquivo de Índice** |  |  | **Arquivo de Dados** |  |

### ÍNDICE

→ **Se tivermos que percorrer o arquivo de índice sequencialmente para encontrar uma determinada chave, o índice não terá muita utilidade**

* busca um pouco mais eficiente (ex. busca binária), se o arquivo de índice estiver ordenado, mas...

→ **Para resolver este problema:**

* os índices não são estruturas sequenciais, e sim hierárquicas
* os índices não apontam para um registro específico, mas para um bloco de registros
* No bloco é feita busca sequencial: registros ordenados dentro de um bloco

### ÍNDICE HIERÁRQUICO

* **NÍVEL 1**
* **NÍVEL 2**
* **ÍNDICES**
* **DADOS**

### HIERARQUIA LEMBRA ÁRVORE...

→ **A maioria das estruturas de índice é implementada por árvores de busca**

* Árvores de Busca Binária
* Árvores AVL
* Árvores de Múltiplos Caminhos

### ÁRVORE DE BUSCA BINÁRIA

→ Todas as chaves da subárvore da esquerda de T têm valores menores que a chave do nó raiz de T

→ Todas as chaves da subárvore da direita de T têm valores maiores que a chave do nó raiz de T

→ As subárvores esquerda e direita de T também são árvores de busca binária

### ÁRVORES DE BUSCA BINÁRIAS

→ Altura tende a ser muito grande

→ Inclusão de chaves ordenadas: degradação da árvore (lista encadeada)

### ÁRVORES AVL

→ **São árvores binárias balanceadas**

* para qualquer um de seus nós, o módulo da diferença entre as alturas de suas subárvores esquerda e direita é, no máximo, 1.

**Ainda são excessivamente altas para uso eficiente como estrutura de índice**

### SOLUÇÃO: ÁRVORES DE MÚLTIPLOS CAMINHOS

→ **Características**

* Cada nó contém n-1 chaves
* Cada nó contém n filhos
* As chaves dentro do nó estão ordenadas
* As chaves dentro do nó funcionam como separadores para os ponteiros para os filhos do nó

### EXEMPLO

### VANTAGENS

→ Têm altura bem menor que as árvores binárias

→ Ideais para uso como índice de arquivos em disco

→ Como as árvores são baixas, são necessários poucos acessos em disco até chegar ao ponteiro para o bloco que contém o registro desejado

### EXEMPLOS DE ÁRVORES MÚLTIPLOS CAMINHOS

→ Árvore B
→ Árvore B+

---