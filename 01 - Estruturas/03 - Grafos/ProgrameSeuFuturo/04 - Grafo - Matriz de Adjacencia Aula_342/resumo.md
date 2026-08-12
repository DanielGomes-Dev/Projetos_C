Este vídeo apresenta um guia prático de como implementar um **Grafo** em linguagem **C** utilizando uma **Matriz de Adjacência**. Abaixo, apresento um resumo detalhado estruturado por tópicos, cobrindo desde a teoria básica até a lógica do código.

---

## 1. Conceito de Matriz de Adjacência
A matriz de adjacência é uma representação matemática de um grafo onde:
* As **linhas** e **colunas** representam os vértices.
* O valor **1** na intersecção $(linha, coluna)$ indica que existe uma aresta entre esses dois vértices.
* O valor **0** indica a ausência de conexão.
* Em **grafos não direcionados** (foco da aula), a matriz é **simétrica**: se existe uma aresta entre 0 e 1, deve haver um "1" tanto na posição $[0][1]$ quanto na $[1][0]$.



---

## 2. Estrutura e Definições (O Código)
O professor utiliza uma abordagem organizada com constantes e `structs`:

* **Constante (`#define`):** Define o tamanho máximo do grafo (ex: `QTD_VERTICES 4`). Isso facilita a manutenção: mudar o tamanho aqui atualiza todo o código.
* **Struct `Grafo`:**
    * `int matriz[QTD_VERTICES][QTD_VERTICES]`: A matriz quadrada que armazena as conexões.
    * `int num_vertices`: Um contador para saber quantos vértices já foram adicionados.

---

## 3. Principais Operações Implementadas

### A. Inicialização
Antes de usar, é necessário "limpar" a matriz. O procedimento `inicializarGrafo` percorre todas as posições da matriz atribuindo **zero** a cada célula e define o contador de vértices como zero. Isso evita "lixo de memória".

### B. Adicionar Vértices
Como a matriz tem um tamanho fixo (definido pela constante), o código verifica se o limite foi atingido. Se houver espaço, o vértice é "adicionado" (incrementando o contador); caso contrário, exibe um erro de limite atingido.

### C. Adicionar e Remover Arestas
Estas funções recebem dois vértices ($V1$ e $V2$) e realizam as seguintes validações:
1.  **Existência:** Uma função auxiliar verifica se os índices $V1$ e $V2$ são válidos (maiores que zero e menores que o máximo).
2.  **Inserção:** Para adicionar, coloca-se `1` em `matriz[V1][V2]` e `matriz[V2][V1]`.
3.  **Remoção:** Para remover, coloca-se `0` nas mesmas posições.

### D. Exibição da Matriz
Um procedimento simples com dois laços de repetição (`for`) que imprime a matriz no console, facilitando a visualização visual das conexões para conferência do programador.

---

## 4. Exemplo de Execução
No teste final, o professor demonstra:
1.  A criação de 4 vértices ($0, 1, 2, 3$).
2.  A tentativa de criar um 5º vértice (que falha devido ao limite).
3.  A criação de arestas formando um ciclo entre os vértices.
4.  A inserção de uma aresta inválida (vértice 5), que o código bloqueia corretamente.
5.  A remoção de uma aresta e a atualização imediata na exibição da matriz.

---

## Resumo Técnico (Destaques)
| Funcionalidade | Lógica Principal |
| :--- | :--- |
| **Grafo Não Direcionado** | Exige simetria na matriz ($[i][j]$ e $[j][i]$). |
| **Uso de Ponteiros** | As funções recebem `Grafo *g` para que as alterações persistam na `main`. |
| **Vértices Inválidos** | Proteção contra acessos fora dos limites do array da matriz. |
| **Flexibilidade** | O uso de `#define` permite escalar o grafo facilmente antes da compilação. |

Essa estrutura serve como base para algoritmos mais complexos que virão a seguir, como as buscas em largura (BFS) e profundidade (DFS), ou algoritmos de menor caminho como Dijkstra.

---

Para entender esse código, primeiro precisamos de uma analogia: imagine um mapa de cidades. As cidades são os **Vértices** e as estradas que as conectam são as **Arestas**. Este código cria um "mapa digital" usando uma tabela de números chamada **Matriz de Adjacência**.

Aqui está a explicação detalhada, passo a passo:

---

## 1. O Esqueleto (Definições e Estrutura)

No início, o código define as regras do jogo:

* **`#define QTD_VERTICES 4`**: Aqui dizemos que nosso mapa terá, no máximo, 4 cidades (vértices).
* **`struct Grafo`**: É a "caixa" que guarda tudo. Dentro dela temos:
    * `matriz[4][4]`: Uma tabela de 4 linhas e 4 colunas cheia de números.
    * `num_vertices`: Um contador para sabermos quantas cidades já "construímos" no mapa.



---

## 2. Limpando o Terreno (`inicializarGrafo`)

Quando o computador reserva espaço para a matriz, ele pode vir com "lixo" (números aleatórios). 
* Esta função percorre cada quadradinho da tabela (linha por linha, coluna por coluna) e coloca o número **0**. 
* **O que o 0 significa?** Significa que não existe estrada ali.
* Ela também define que ainda temos **0** cidades adicionadas.

---

## 3. Criando Cidades (`adicionarVertice`)

Não podemos conectar cidades que não existem. 
* Cada vez que chamamos essa função, o contador `num_vertices` aumenta. 
* Se tentarmos colocar 5 cidades num mapa que só cabe 4, o código avisa que o limite foi atingido. É uma trava de segurança.

---

## 4. Construindo Estradas (`adicionarAresta`)

Aqui é onde a mágica acontece. Para conectar a Cidade A com a Cidade B:
1.  **`verticeExiste`**: Primeiro, o código checa se essas cidades realmente foram criadas.
2.  **Simetria**: Como é um grafo **não direcionado** (a estrada vai e volta), o código coloca o número **1** em dois lugares da tabela:
    * Na linha da Cidade A, coluna da Cidade B.
    * Na linha da Cidade B, coluna da Cidade A.
* **O que o 1 significa?** Significa "Existe uma conexão aqui!".



---

## 5. Destruindo Estradas (`removerAresta`)

É o inverso da função anterior. Se decidirmos que não há mais passagem entre a Cidade A e B, o código simplesmente volta os valores naqueles endereços da tabela para **0**.

---

## 6. Mostrando o Mapa (`exibirMatriz`)

Esta função "desenha" a tabela na tela para nós. Se você vir algo como:
```text
          0 1 2 3
Vertice 0: 0 1 0 0 
Vertice 1: 1 0 0 0
```
Isso te diz visualmente que o **Vértice 0** está conectado ao **Vértice 1** (porque tem um `1` ali), mas não está conectado ao 2 nem ao 3.

---

## 7. O Maestro (`main`)

A função `main` é onde a execução acontece na prática:
1.  Cria o grafo e limpa a matriz.
2.  Adiciona 4 cidades (0, 1, 2 e 3).
3.  Cria estradas entre elas (formando um quadrado de conexões).
4.  Mostra a matriz na tela.
5.  Apaga a estrada entre a cidade 0 e a 3.
6.  Mostra a matriz novamente para provar que a estrada sumiu.

### Resumo Visual da Lógica
* **0** na tabela = Sem estrada.
* **1** na tabela = Com estrada.
* **Linha/Coluna** = Qual cidade estamos olhando.

Dessa forma, o computador consegue processar mapas e conexões complexas apenas lendo uma tabela de zeros e uns!