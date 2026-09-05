## Mapeamento e Identificação

O exercício proposto consiste na construção de uma **Árvore B** clássica por meio da inserção sequencial de chaves em um nó folha inicial. O tópico abordado pertence à área de Algoritmos e Estruturas de Dados (Indexação e Organização de Arquivos).

A resolução baseia-se estritamente no **Algoritmo de Uma Passagem (Preemptivo)**. Seguindo a metodologia do texto, o algoritmo realiza uma estratégia descendente a partir da raiz e, de maneira preventiva, realiza a operação de **divisão** em qualquer nó completo que for encontrado no percurso, de modo a garantir que o nó pai correspondente nunca estará cheio quando uma chave precisar ser deslocada para o nível superior.

---

## Transcrição Fiel

> (Q1) Dada uma árvore B que é uma folha com a informação {20, 50, 60} e t = 2:
> (a) insira os elementos {1, 64, 12, 18, 66, 38, 95, 58, 59, 70, 68, 39, 62, 7, 55, 43, 16, 67, 34, 35} nesta árvore, indicando as rotações necessárias;

(Nota metodológica: Embora o enunciado use o termo comum "rotações", o material do texto define explicitamente que o tratamento para balanceamento e controle na Árvore B baseia-se unicamente em **divisões de nós** e subida de chaves medianas. Portanto, essa é a operação demonstrada a cada passo).

---

## Parâmetros da Estrutura ($t = 2$)

Com base nas definições formais encontradas na documentação do texto:

* 
**Grau mínimo:** $t = 2$ 


* 
**Número mínimo de chaves** por nó (exceto raiz): $t - 1 = 2 - 1 = 1 \text{ chave}$ 


* 
**Número máximo de chaves** por nó: $2t - 1 = 2(2) - 1 = 3 \text{ chaves}$ 


* 
**Gatilho de Divisão:** Qualquer nó que atinja exatamente $3 \text{ chaves}$ é considerado um **nó completo** e deve sofrer a operação de divisão preemptiva antes que novas inserções avancem por ele.



---

## Resolução Passo a Passo Detalhada

### Estado Inicial

A árvore inicia-se com um único nó raiz que também é folha, contendo as 3 chaves:


$$\text{Raiz Inicial: } [20, 50, 60]$$

---

### Inserção de 1

* **Análise de Entrada:** O algoritmo inicia o percurso descendente na raiz. O nó atual é $[20, 50, 60]$.
* 
**Justificativa do Texto:** *"À medida que se desce na árvore... divide-se cada nó completo encontrado (incluindo-se a raiz)"*. Como o número de chaves é $3$, o nó está completo ($2t - 1$).


* 
**Operação de Divisão (Raiz Completa):** Segundo a regra do texto, cria-se uma nova raiz vazia $S$, tornando a raiz antiga seu primeiro filho para que ela possa ser dividida.


* Elementos a dividir: $[20, 50, 60]$. A chave mediana para $t = 2$ localiza-se na posição do índice $t - 1$, ou seja, índice 1 (o valor central $50$).


* O valor $50$ é extraído e deslocado para o nó pai.


* As chaves restantes são distribuídas de maneira simétrica: o nó original retém as chaves anteriores a $50$, e um novo nó irmão $z$ recebe as chaves posteriores.


* Filho Esquerdo: $[20]$
* Filho Direito: $[60]$


* 
**Inserção Efetiva:** Após a modificação estrutural da árvore , descemos para o filho correto comparando o valor a ser inserido ($1$) com as chaves do nó interno pai $[50]$. Como $1 < 50$, o algoritmo direciona o fluxo para o filho esquerdo $[20]$. O nó $[20]$ é folha e não está completo, logo a inserção ocorre de maneira local e ordenada.


* **Resultado:**

```
      [ 50 ]
     /      \
[ 1, 20 ]  [ 60 ]

```

---

### Inserção de 64

* 
**Análise de Entrada:** Iniciamos na raiz $[50]$, que possui 1 chave (não está completa). Avaliamos as chaves para descer: como $64 > 50$, o fluxo de execução segue para o ponteiro à direita.


* **Inserção Efetiva:** Alcançamos o nó folha $[60]$. Ele possui 1 chave (não está completo). Inserimos o valor $64$ ordenadamente na folha.


* **Resultado:**

```
      [ 50 ]
     /      \
[ 1, 20 ]  [ 60, 64 ]

```

---

### Inserção de 12

* **Análise de Entrada:** Iniciamos na raiz $[50]$ (não completa). Comparamos: $12 < 50$, direcionando a busca para o filho esquerdo $[1, 20]$.


* 
**Inserção Efetiva:** O nó folha $[1, 20]$ possui 2 chaves (não completo). Inserimos o valor $12$ em sua posição ordenada entre $1$ e $20$.


* **Resultado:**

```
        [ 50 ]
       /      \
[ 1, 12, 20 ] [ 60, 64 ]

```

---

### Inserção de 18

* **Análise de Entrada:** Iniciamos na raiz $[50]$ (não completa). Comparamos: $18 < 50$, o que define o caminho de descida em direção ao filho esquerdo $[1, 12, 20]$.


* **Justificativa do Texto (Gatilho de Divisão):** Antes de prosseguir para o filho esquerdo, o algoritmo verifica seu estado. Como o nó $[1, 12, 20]$ possui 3 chaves, ele está completo e deve ser dividido preventivamente.


* **Operação de Divisão:** O conjunto de chaves é $[1, 12, 20]$. O elemento mediano é o $12$. Ele é deslocado para cima, sendo inserido de forma ordenada no nó pai $[50]$, que passa a conter $[12, 50]$.


* Filho esquerdo resultante da divisão: $[1]$ 


* Filho direito resultante da divisão: $[20]$ 




* 
**Inserção Efetiva:** Com a estrutura corrigida no nível intermediário, o algoritmo decide por qual ponteiro descer a partir da raiz atualizada $[12, 50]$. Como $12 \le 18 < 50$, o ponteiro selecionado nos leva ao nó folha $[20]$. O nó $[20]$ não está completo, logo inserimos $18$ ordenadamente.


* **Resultado:**

```
          [ 12, 50 ]
         /    |     \
  [ 1 ]    [ 18, 20 ]  [ 60, 64 ]

```

---

### Inserção de 66

* **Análise de Entrada:** Iniciamos na raiz $[12, 50]$ (não completa). Comparamos as chaves para descida: como $66 > 50$, o algoritmo aponta para o nó da extrema direita: $[60, 64]$.


* 
**Inserção Efetiva:** O nó folha $[60, 64]$ possui 2 chaves (não completo). O elemento $66$ é adicionado de forma ordenada ao final do nó.


* **Resultado:**

```
             [ 12, 50 ]
            /    |     \
  [ 1 ]    [ 18, 20 ]  [ 60, 64, 66 ]

```

---

### Inserção de 38

* **Análise de Entrada:** Iniciamos na raiz $[12, 50]$ (não completa). Avaliamos o caminho de descida para a chave $38$. Como $12 \le 38 < 50$, o algoritmo seleciona o ponteiro correspondente ao filho central, que aponta para o nó $[18, 20, 66]$? Não, aponta para o nó $[18, 20, 66]$? Não, o nó original era $[18, 20]$ do passo anterior, que após a última inserção de 66 permaneceu inalterado. O nó do meio é $[18, 20]$.
* **Gatilho de Divisão:** O nó $[18, 20]$ possui 2 chaves, portanto não está completo. Podemos prosseguir com a descida diretamente para ele.


* 
**Inserção Efetiva:** No nó folha $[18, 20]$, inserimos o elemento $38$ ordenadamente. O nó passa a conter 3 elementos.


* **Resultado:**

```
             [ 12, 50 ]
            /    |     \
  [ 1 ]    [ 18, 20, 38 ]  [ 60, 64, 66 ]

```

---

### Inserção de 95

* **Análise de Entrada:** Iniciamos na raiz $[12, 50]$ (não completa). Comparamos o elemento: $95 > 50$, direcionando a busca para o filho à extrema direita, que é o nó $[60, 64, 66]$.


* 
**Justificativa do Texto (Gatilho de Divisão):** O nó de descida $[60, 64, 66]$ possui 3 chaves, caracterizando um nó completo. Executa-se a divisão preventiva antes de acessar a folha.


* **Operação de Divisão:** Conjunto de chaves: $[60, 64, 66]$. O elemento mediano é $64$. Ele é deslocado para cima, integrando-se ordenadamente à raiz $[12, 50]$, transformando-a em $[12, 50, 64]$.


* Filho esquerdo resultante da divisão: $[60]$ 


* Filho direito resultante da divisão: $[66]$ 




* 
**Inserção Efetiva:** A partir da raiz modificada $[12, 50, 64]$, reavaliamos o percurso para $95$. Como $95 > 64$, descemos pelo ponteiro à extrema direita que nos leva à folha $[66]$. Nele, inserimos $95$ de maneira ordenada.


* **Resultado:**

```
                 [ 12, 50, 64 ]
               /    /    \     \
         [ 1 ] [ 18, 20, 38 ] [ 60 ] [ 66, 95 ]

```

---

### Inserção de 58

* **Análise de Entrada:** Iniciamos na raiz $[12, 50, 64]$.
* 
**Justificativa do Texto (Gatilho de Divisão na Raiz):** O nó raiz possui exatamente 3 chaves, caracterizando um nó completo ($2t - 1$). Segundo as regras de uma passagem para a raiz, ela deve ser dividida imediatamente no início do percurso.


* 
**Operação de Divisão da Raiz:** Cria-se uma nova raiz temporária e vazia acima de $[12, 50, 64]$. O valor mediano (posição índice 1, valor $50$) é promovido para se tornar a nova raiz única do topo.


* Nova Raiz Suprema: $[50]$ 


* Novo Filho Interno Esquerdo: $[12]$  (herda os ponteiros das folhas $[1]$ e $[18, 20, 38]$)


* Novo Filho Interno Direito: $[64]$  (herda os ponteiros das folhas $[60]$ e $[66, 95]$)




* **Retomada do Percurso:** A partir da nova raiz absoluta $[50]$, comparamos o elemento a ser inserido ($58$). Como $58 > 50$, o fluxo de execução é direcionado para o nó interno direito $[64]$. No nó $[64]$, comparamos novamente: $58 < 64$, determinando a descida para o filho esquerdo de $64$, que corresponde ao nó folha $[60]$.


* **Inserção Efetiva:** O nó folha $[60]$ não está completo. Adicionamos o valor $58$ de forma ordenada.


* **Resultado:**

```
                     [ 50 ]
                   /        \
            [ 12 ]            [ 64 ]
           /    \            /    \
     [ 1 ]   [ 18, 20, 38 ] [ 58, 60 ] [ 66, 95 ]

```

---

### Inserção de 59

* 
**Análise de Entrada:** Da raiz $[50]$, como $59 > 50$, descemos para o nó interno $[64]$. No nó $[64]$, como $59 < 64$, o ponteiro aponta para o filho esquerdo, correspondente ao nó folha $[58, 60]$.


* 
**Inserção Efetiva:** A folha $[58, 60]$ possui 2 chaves (não completa). Inserimos o valor $59$ ordenadamente entre $58$ e $60$.


* **Resultado:**

```
                     [ 50 ]
                   /        \
            [ 12 ]            [ 64 ]
           /    \            /    \
     [ 1 ]   [ 18, 20, 38 ] [ 58, 59, 60 ] [ 66, 95 ]

```

---

### Inserção de 70

* 
**Análise de Entrada:** Da raiz $[50]$, como $70 > 50$, descemos para o nó interno $[64]$. No nó $[64]$, como $70 > 64$, o caminho indica o filho direito, que é a folha $[66, 95]$.


* 
**Inserção Efetiva:** A folha $[66, 95]$ possui espaço disponível (2 chaves). Inserimos o valor $70$ ordenadamente.


* **Resultado:**

```
                     [ 50 ]
                   /        \
            [ 12 ]            [ 64 ]
           /    \            /    \
     [ 1 ]   [ 18, 20, 38 ] [ 58, 59, 60 ] [ 66, 70, 95 ]

```

---

### Inserção de 68

* 
**Análise de Entrada:** Da raiz $[50]$, $68 > 50 \rightarrow$ descemos para o nó interno $[64]$. No nó $[64]$, como $68 > 64$, o percurso indica a folha $[66, 70, 95]$.


* 
**Justificativa do Texto (Gatilho de Divisão):** O nó folha $[66, 70, 95]$ contém 3 chaves, estando em seu limite máximo de capacidade. Executa-se a divisão preventiva.


* **Operação de Divisão:** Conjunto de chaves: $[66, 70, 95]$. O valor mediano é $70$. Ele é promovido para o pai $[64]$, modificando-o para $[64, 70]$.


* Filho esquerdo resultante da divisão: $[66]$ 


* Filho direito resultante da divisão: $[95]$ 




* 
**Inserção Efetiva:** A partir do nó interno atualizado $[64, 70]$, reavaliamos a posição da chave $68$. Como $64 \le 68 < 70$, descemos pelo ponteiro central que leva à folha $[66]$. O nó não está completo, logo inserimos o $68$ de forma ordenada.


* **Resultado:**

```
                     [ 50 ]
                   /        \
            [ 12 ]            [ 64, 70 ]
           /    \            /    |     \
     [ 1 ]   [ 18, 20, 38 ] [ 58, 59, 60 ] [ 66, 68 ] [ 95 ]

```

---

### Inserção de 39

* 
**Análise de Entrada:** Da raiz $[50]$, como $39 < 50$, descemos para o nó interno esquerdo $[12]$. No nó $[12]$, como $39 > 12$, somos direcionados para o seu filho direito, correspondente à folha $[18, 20, 38]$.


* 
**Justificativa do Texto (Gatilho de Divisão):** O nó de descida $[18, 20, 38]$ está completo com 3 chaves. Executa-se o procedimento de divisão preventiva.


* **Operação de Divisão:** Conjunto de chaves: $[18, 20, 38]$. O valor mediano $20$ é promovido ao nó pai $[12]$, alterando-o para $[12, 20]$.


* Filho esquerdo resultante da divisão: $[18]$ 


* Filho direito resultante da divisão: $[38]$ 




* 
**Inserção Efetiva:** No nó pai atualizado $[12, 20]$, comparamos a chave de busca $39$. Como $39 > 20$, seguimos o ponteiro à extrema direita em direção à folha $[38]$. Inserimos o $39$ ordenadamente na folha.


* **Resultado:**

```
                     [ 50 ]
                   /        \
            [ 12, 20 ]        [ 64, 70 ]
           /    |     \      /    |     \
     [ 1 ]   [ 18 ] [ 38, 39 ] [ 58, 59, 60 ] [ 66, 68 ] [ 95 ]

```

---

### Inserção de 62

* 
**Análise de Entrada:** Da raiz $[50]$, como $62 > 50$, descemos para o nó interno direito $[64, 70]$. No nó $[64, 70]$, avaliamos: $62 < 64$, indicando que devemos seguir o ponteiro à esquerda para a folha $[58, 59, 60]$.


* 
**Justificativa do Texto (Gatilho de Divisão):** A folha $[58, 59, 60]$ está completa. Realiza-se a divisão preventiva.


* **Operação de Divisão:** Conjunto de chaves: $[58, 59, 60]$. O valor mediano $59$ é promovido para o pai $[64, 70]$, que passa a conter as chaves $[59, 64, 70]$.


* Filho esquerdo resultante da divisão: $[58]$ 


* Filho direito resultante da divisão: $[60]$ 




* 
**Inserção Efetiva:** No nó pai modificado $[59, 64, 70]$, reavaliamos o percurso para $62$. Como $59 \le 62 < 64$, descemos pelo ponteiro correspondente ao intervalo intermediário, que nos direciona para a folha $[60]$. Adicionamos o valor $62$ de forma ordenada.


* **Resultado:**

```
                     [ 50 ]
                   /        \
            [ 12, 20 ]        [ 59, 64, 70 ]
           /    |     \      /    /    \    \
     [ 1 ]   [ 18 ] [ 38, 39 ] [ 58 ] [ 60, 62 ] [ 66, 68 ] [ 95 ]

```

---

### Inserção de 7

* 
**Análise de Entrada:** Da raiz $[50]$, como $7 < 50$, o fluxo de execução desce para o nó interno esquerdo $[12, 20]$. No nó $[12, 20]$, como $7 < 12$, o caminho de descida leva à folha da extrema esquerda, que é o nó $[1]$.


* 
**Inserção Efetiva:** O nó folha $[1]$ possui apenas 1 chave (não completo). Inserimos o valor $7$ de forma ordenada após o $1$.


* **Resultado:**

```
                     [ 50 ]
                   /        \
            [ 12, 20 ]        [ 59, 64, 70 ]
           /    |     \      /    /    \    \
  [ 1, 7 ]   [ 18 ] [ 38, 39 ] [ 58 ] [ 60, 62 ] [ 66, 68 ] [ 95 ]

```

---

### Inserção de 55

* 
**Análise de Entrada:** Da raiz $[50]$, como $55 > 50$, o algoritmo desce para o nó interno direito $[59, 64, 70]$.


* 
**Justificativa do Texto (Gatilho de Divisão em Nó Interno):** O nó intermediário $[59, 64, 70]$ possui 3 chaves, configurando um nó completo. Ele precisa ser dividido preventivamente.


* **Operação de Divisão:** Conjunto de chaves: $[59, 64, 70]$. O elemento mediano é o $64$. Ele é promovido para a raiz $[50]$, transformando-a em $[50, 64]$.


* Nó interno esquerdo resultante: $[59]$  (gerencia as folhas $[58]$ e $[60, 62]$)


* Nó interno direito resultante: $[70]$  (gerencia as folhas $[66, 68]$ e $[95]$)




* 
**Retomada do Percurso:** A partir da raiz modificada $[50, 64]$, analisamos a chave $55$. Como $50 \le 55 < 64$, descemos pelo ponteiro central em direção ao nó interno $[59]$. No nó $[59]$, como $55 < 59$, somos direcionados para o seu filho esquerdo, que é a folha $[58]$.


* **Inserção Efetiva:** A folha $[58]$ possui espaço. Adicionamos o valor $55$ ordenadamente.


* **Resultado:**

```
                           [ 50, 64 ]
                        /      |       \
            [ 12, 20 ]       [ 59 ]     [ 70 ]
           /    |     \     /    \     /    \
  [ 1, 7 ]   [ 18 ] [ 38, 39 ] [ 55, 58 ] [ 60, 62 ] [ 66, 68 ] [ 95 ]

```

---

### Inserção de 43

* 
**Análise de Entrada:** Da raiz $[50, 64]$, como $43 < 50$, descemos para o nó interno esquerdo $[12, 20]$. No nó $[12, 20]$, como $43 > 20$, seguimos o ponteiro à direita para a folha $[38, 39]$.


* 
**Inserção Efetiva:** A folha $[38, 39]$ possui 2 chaves (não completa). Inserimos o valor $43$ ordenadamente ao final do nó.


* **Resultado:**

```
                           [ 50, 64 ]
                        /      |       \
            [ 12, 20 ]       [ 59 ]     [ 70 ]
           /    |     \     /    \     /    \
  [ 1, 7 ]   [ 18 ] [ 38, 39, 43 ] [ 55, 58 ] [ 60, 62 ] [ 66, 68 ] [ 95 ]

```

---

### Inserção de 16

* 
**Análise de Entrada:** Da raiz $[50, 64]$, como $16 < 50$, descemos para o nó interno esquerdo $[12, 20]$. No nó $[12, 20]$, avaliamos: $12 \le 16 < 20$, direcionando a descida pelo ponteiro central para a folha $[18]$.


* 
**Inserção Efetiva:** O nó folha $[18]$ possui espaço livre. Inserimos o valor $16$ de forma ordenada antes de $18$.


* **Resultado:**

```
Folhas afetadas no ramo esquerdo: ... [ 1, 7 ] -> [ 16, 18 ] -> [ 38, 39, 43 ] ...

```

---

### Inserção de 67

* 
**Análise de Entrada:** Da raiz $[50, 64]$, como $67 > 64$, descemos para o nó interno da extrema direita $[70]$. No nó $[70]$, como $67 < 70$, o caminho indica o seu filho esquerdo, correspondente à folha $[66, 68]$.


* 
**Inserção Efetiva:** A folha $[66, 68]$ possui espaço disponível (2 chaves). Adicionamos o valor $67$ ordenadamente entre $66$ e $68$.


* **Resultado:**

```
Folhas afetadas no ramo direito: ... [ 60, 62 ] -> [ 66, 67, 68 ] -> [ 95 ]

```

---

### Inserção de 34

* 
**Análise de Entrada:** Da raiz $[50, 64]$, como $34 < 50$, descemos para o nó interno esquerdo $[12, 20]$. No nó $[12, 20]$, como $34 > 20$, a rota indica a folha $[38, 39, 43]$.


* 
**Justificativa do Texto (Gatilho de Divisão):** A folha de destino $[38, 39, 43]$ está completa com 3 chaves. Realiza-se a divisão preventiva.


* **Operação de Divisão:** Conjunto de chaves: $[38, 39, 43]$. O valor mediano $39$ é promovido para o nó pai $[12, 20]$, transformando-o em um nó com 3 chaves: $[12, 20, 39]$.


* Filho esquerdo resultante da divisão: $[38]$ 


* Filho direito resultante da divisão: $[43]$ 




* 
**Inserção Efetiva:** No nó pai modificado $[12, 20, 39]$, reavaliamos o percurso para a chave $34$. Como $20 \le 34 < 39$, o ponteiro correto nos direciona para o nó folha $[38]$. Adicionamos o $34$ de forma ordenada na folha.


* **Resultado:**

```
                           [ 50, 64 ]
                        /      |       \
          [ 12, 20, 39 ]     [ 59 ]     [ 70 ]
         /    /    \    \   /    \     /    \
  [1, 7] [16, 18] [34, 38] [43] [55, 58] [60, 62] [66, 67, 68] [95]

```

---

### Inserção de 35

* 
**Análise de Entrada:** Da raiz $[50, 64]$, como $35 < 50$, o algoritmo seleciona o caminho em direção ao nó interno esquerdo $[12, 20, 39]$.


* 
**Justificativa do Texto (Gatilho de Divisão em Nó Interno):** O nó intermediário $[12, 20, 39]$ possui 3 chaves, atingindo o limite máximo e tornando-se um nó completo. Seguindo a lógica preemptiva, ele deve ser dividido.


* **Operação de Divisão:** Conjunto de chaves: $[12, 20, 39]$. O elemento mediano é o $20$. Ele é promovido para compor o nó pai raiz $[50, 64]$, modificando-o para $[20, 50, 64]$.


* Filho esquerdo resultante no nível intermediário: $[12]$  (gerencia as folhas $[1, 7]$ e $[16, 18]$)


* Filho direito resultante no nível intermediário: $[39]$  (gerencia as folhas $[34, 38]$ e $[43]$)




* 
**Retomada do Percurso:** Na raiz atualizada $[20, 50, 64]$, reavaliamos o direcionamento para a chave $35$. Como $20 \le 35 < 50$, o algoritmo direciona o fluxo pelo ponteiro intermediário, levando ao nó interno $[39]$. No nó $[39]$, como $35 < 39$, seguimos para o seu filho esquerdo, correspondente à folha $[34, 38]$.


* 
**Inserção Efetiva:** A folha $[34, 38]$ não está completa. Inserimos o valor $35$ ordenadamente entre $34$ e $38$.



---

## Formato de Resposta Final (Estrutura da Árvore B Concluída)

Abaixo é apresentada a árvore final estruturada exatamente conforme a especificação do texto (representando os nós internos como índices/ponteiros e os elementos distribuídos de forma balanceada).

### Índices por Níveis de Nós

$$\text{Nível 0 (Raiz Principal): } [20, 50, 64]$$

$$\text{Nível 1 (Nós Internos Intermediários):}$$

* Filho à esquerda de 20: $[12]$
* Filho entre 20 e 50: $[39]$
* Filho entre 50 e 64: $[59]$
* Filho à direita de 64: $[70]$

---

### Nível das Folhas (Nós de Dados)

Mapeamento de cada ponteiro de folha associado ordenadamente aos seus respectivos nós internos pais:

* **Filhos do nó $[12]$:**
* Ponteiro à esquerda de 12 $\rightarrow$ **$[1, 7]$**
* Ponteiro à direita de 12 $\rightarrow$ **$[16, 18]$**


* **Filhos do nó $[39]$:**
* Ponteiro à esquerda de 39 $\rightarrow$ **$[34, 35, 38]$**
* Ponteiro à direita de 39 $\rightarrow$ **$[43]$**


* **Filhos do nó $[59]$:**
* Ponteiro à esquerda de 59 $\rightarrow$ **$[55, 58]$**
* Ponteiro à direita de 59 $\rightarrow$ **$[60, 62]$**


* **Filhos do nó $[70]$:**
* Ponteiro à esquerda de 70 $\rightarrow$ **$[66, 67, 68]$**
* Ponteiro à direita de 70 $\rightarrow$ **$[95]$**