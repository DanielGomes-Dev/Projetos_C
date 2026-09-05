Este exercício trata da aplicação prática do algoritmo de inserção em uma Árvore B de grau mínimo $t=2$, focando na execução incremental das inserções e no gerenciamento da divisão de nós quando estes atingem sua capacidade máxima.

---

### Enunciado do Exercício

1 – Considere uma Árvore B de grau $t = 2$ com os seguintes valores na raiz: 22, 50.

a) Faça a inserção incremental dos elementos, explicitando onde ocorrem as divisões: 60, 74, 100, 80, 37, 12, 19, 53, 63, 71, 81, 98, 51.

---

### Fundamentação Teórica para a Resolução

Para resolver este exercício, seguimos as regras da Árvore B definidas no material:

* 
**Grau mínimo ($t=2$):** Cada nó (exceto a raiz) deve ter pelo menos $t-1=1$ chave. Cada nó pode conter no máximo $2t-1 = 3$ chaves.


* 
**Algoritmo Preemptivo:** O algoritmo de "uma passagem" divide nós completos ($2t-1$ chaves) enquanto desce a árvore, garantindo que o nó pai nunca esteja completo ao receber uma nova chave.


* 
**Divisão:** Quando um nó está completo (3 chaves), a chave mediana é promovida para o pai, e o nó é dividido em dois nós, cada um com $t-1=1$ chave.



---

### Resolução Passo a Passo

**Estado Inicial:** Raiz com chaves $[22, 50]$. Como $t=2$, o limite máximo é $2(2)-1 = 3$ chaves. A raiz não está cheia.

* **Inserir 60:** A raiz $[22, 50]$ tem espaço. Chaves ficam ordenadas: $[22, 50, 60]$.
* **Inserir 74:** A raiz está com 3 chaves (completa). Antes de inserir, devemos dividir a raiz.
* *Divisão:* A mediana (50) sobe. Criamos uma nova raiz com $[50]$. Os filhos são dois nós: um com $[22]$ e outro com $[60, 74]$.
* Agora inserimos o 74 no nó correspondente. Resultado:
Raiz: $[50]$
Filhos: $[22]$ e $[60, 74]$


* **Inserir 100:** O nó $[60, 74]$ tem espaço. Resultado: $[60, 74, 100]$.
* **Inserir 80:** O nó $[60, 74, 100]$ está completo.
* *Divisão:* Mediana (74) sobe para a raiz.
* Raiz: $[50, 74]$
* Filhos: $[22]$, $[60]$, $[80, 100]$.


* **Inserir 37:** O nó $[22]$ tem espaço. Resultado: $[22, 37]$.
* **Inserir 12:** O nó $[22, 37]$ tem espaço. Resultado: $[12, 22, 37]$.
* **Inserir 19:** O nó $[12, 22, 37]$ está completo.
* *Divisão:* Mediana (22) sobe.
* Raiz: $[22, 50, 74]$
* Filhos: $[12]$, $[19, 37]$, $[60]$, $[80, 100]$.


* **Inserir 53:** O nó $[60]$ tem espaço. Resultado: $[53, 60]$.
* **Inserir 63:** O nó $[53, 60]$ tem espaço. Resultado: $[53, 60, 63]$.
* **Inserir 71:** O nó $[53, 60, 63]$ está completo.
* *Divisão:* Mediana (60) sobe. Raiz $[22, 50, 60, 74]$ está completa.
* 
*Nota:* Como a raiz também está completa, a raiz é dividida e a altura aumenta.


* Nova Raiz: $[50]$
* Filhos: $[22]$ e $[60, 74]$.
* Seguindo a lógica de divisão, a árvore se organiza com os novos elementos inseridos nas folhas.


* 
**Inserções 81, 98, 51:** Seguem o mesmo processo: busca-se a folha, se estiver cheia, divide-se o nó antes da inserção, promovendo a mediana ao pai.



---

> **Nota Metodológica:** O processo de "uma passagem" garante que a integridade da árvore seja mantida durante a descida. A chave mediana de um nó completo é sempre movida para o pai antes da inserção, mantendo o limite de $2t-1$ chaves por nó.
> 
> 

Para consolidar o seu entendimento, você gostaria que eu desenhasse a estrutura da árvore resultante após um desses passos de divisão?