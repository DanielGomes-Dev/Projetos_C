## Mapeamento e Identificação

O exercício proposto consiste na construção de uma **Árvore $B^+$** por meio de inserções sucessivas de elementos, partindo de um nó folha inicial. O tópico abordado pertence à área de Estruturas de Dados (Indexação e Organização de Arquivos/Bancos de Dados).

A resolução exige a aplicação do **Algoritmo de Inserção de Uma Passagem** descrito no material. À medida que descemos na estrutura em busca da folha correta para a inserção, qualquer nó que for encontrado **completo** (com a capacidade máxima de chaves atingida) deve ser dividido preventivamente. Isso garante que o nó pai nunca estará cheio quando uma divisão no nível inferior precisar empurrar uma chave para cima.

---

## Transcrição Fiel

> (Q1) Dada uma árvore B+ que é uma folha com a informação {20, 50, 60} e t = 2:
> (a) insira os elementos {1, 64, 12, 18, 66, 38, 95, 58, 59, 70, 68, 39, 62, 7, 55, 43, 16, 67, 34, 35} nesta árvore, indicando as rotações necessárias;

(Nota de consistência metodológica: Embora o enunciado use o termo comum "rotações", o material didático oficial define explicitamente que o tratamento para a árvore $B^+$ baseia-se em **divisões de nós** e subida de chaves, metodologia estritamente adotada nesta resolução passo a passo).

---

## Parâmetros da Estrutura ($t = 2$)

Com base na definição e na estrutura em C fornecida no texto:

* **Ordem (grau mínimo):** $t = 2$
* **Número máximo de chaves por nó:** $2t - 1 = 2(2) - 1 = 3 \text{ chaves}$
* **Capacidade máxima:** Um nó está considerado **completo** quando possui exatamente $3 \text{ chaves}$. Encontrar um nó com 3 chaves durante o percurso descendente dispara o gatilho de **divisão**.

---

## Resolução Passo a Passo Detalhada

### Estado Inicial

A árvore começa with um único nó folha contendo 3 chaves:

$$\text{Folha Inicial: } [20, 50, 60]$$

---

### Inserção de 1

* **Análise:** O algoritmo inicia na raiz. A raiz atual é uma folha que contém as chaves $\{20, 50, 60\}$.
* **Regra do Texto:** *"À medida que se desce na árvore... divide-se cada nó completo encontrado (incluindo-se a raiz)"*. Como o nó está completo ($3 \text{ chaves}$), ele precisa ser dividido **antes** de realizarmos a inserção.
* **Operação de Divisão (Nó Heterogêneo - Raiz Folha):** De acordo com a regra da árvore $B^+$, a chave mediana sobe para criar um novo nó interno (pai), mas, por ser uma divisão de folha, ela **também permanece na folha direita**.
* Elementos a dividir: $[20, 50, 60]$. O elemento mediano é o $50$.
* Nova Raiz (Nó Interno): $[50]$
* Filho Esquerdo (Folha): $[20]$
* Filho Direito (Folha): $[50, 60]$
* *Encadeamento:* As folhas são ligadas via ponteiro `prox`: $[20] \rightarrow [50, 60]$.
* **Inserção Efetiva:** Agora descemos para o nó folha correspondente ao elemento $1$. Como $1 < 50$, descemos para o filho esquerdo $[20]$. O nó $[20]$ possui espaço. Inserimos de forma ordenada.
* **Resultado:**

```
      [ 50 ]
     /      \
[ 1, 20 ] -> [ 50, 60 ]

```

---

### Inserção de 64

* **Análise:** Iniciamos na raiz $[50]$, que possui 1 chave (não está completa). Comparamos: $64 > 50$, logo descemos para o filho direito: $[50, 60]$.
* **Inserção Efetiva:** O nó folha $[50, 60]$ possui 2 chaves (espaço disponível). Adicionamos o $64$ ordenadamente.
* **Resultado:**

```
      [ 50 ]
     /      \
[ 1, 20 ] -> [ 50, 60, 64 ]

```

---

### Inserção de 12

* **Análise:** Iniciamos na raiz $[50]$. Não está completa. Comparamos: $12 < 50$, descemos para o filho esquerdo: $[1, 20]$.
* **Inserção Efetiva:** O nó folha $[1, 20]$ possui 2 chaves (espaço disponível). Adicionamos o $12$ ordenadamente entre $1$ e $20$.
* **Resultado:**

```
        [ 50 ]
       /      \
[ 1, 12, 20 ] -> [ 50, 60, 64 ]

```

---

### Inserção de 18

* **Análise:** Iniciamos na raiz $[50]$ (não está completa). Comparamos: $18 < 50$, determinando que o caminho de descida é o filho esquerdo $[1, 12, 20]$.
* **Gatilho do Algoritmo:** O filho esquerdo $[1, 12, 20]$ está **completo** (3 chaves). Devemos dividi-lo preventivamente antes de avançar.
* **Operação de Divisão:** Elementos $[1, 12, 20]$. O elemento mediano é o $12$. Ele sobe para o pai $[50]$ e permanece no início da nova folha da direita.
* Pai atualizado: $[12, 50]$
* Folha Esquerda resultante: $[1]$
* Folha Direita resultante: $[12, 20]$
* *Encadeamento atualizado:* $[1] \rightarrow [12, 20] \rightarrow [50, 60, 64]$.
* **Inserção Efetiva:** A estrutura da árvore foi modificada abaixo da raiz. Repetimos a decisão de descida a partir da raiz atualizada $[12, 50]$. Como $12 \le 18 < 50$, o ponteiro correto nos direciona para a folha $[12, 20]$. Inserimos o $18$ ordenadamente.
* **Resultado:**

```
          [ 12, 50 ]
         /    |     \
  [ 1 ] -> [ 12, 18, 20 ] -> [ 50, 60, 64 ]

```

---

### Inserção de 66

* **Análise:** Iniciamos na raiz $[12, 50]$ (possui 2 chaves, não está completa). Como $66 > 50$, avalia-se o filho da extrema direita: $[50, 60, 64]$.
* **Gatilho do Algoritmo:** O nó $[50, 60, 64]$ está **completo** (3 chaves). Efetuamos a divisão preventiva.
* **Operação de Divisão:** Elementos $[50, 60, 64]$. O valor mediano é $60$. Ele sobe para a raiz e replica-se na folha direita.
* Pai updated: $[12, 50, 60]$
* Nova Folha Esquerda: $[50]$
* Nova Folha Direita: $[60, 64]$
* *Encadeamento atualizado:* $[1] \rightarrow [12, 18, 20] \rightarrow [50] \rightarrow [60, 64]$.
* **Inserção Efetiva:** A partir da raiz reestruturada $[12, 50, 60]$, comparamos o valor $66$. Como $66 > 60$, somos direcionados para o nó da extrema direita, que agora é a folha $[60, 64]$. Adicionamos o $66$ ordenadamente.
* **Resultado:**

```
             [ 12, 50, 60 ]
            /    /    \    \
  [ 1 ] -> [ 12, 18, 20 ] -> [ 50 ] -> [ 60, 64, 66 ]

```

---

### Inserção de 38

* **Análise:** Iniciamos na raiz $[12, 50, 60]$.
* **Gatilho do Algoritmo:** A raiz possui 3 chaves e está **completa**. Ela deve ser dividida imediatamente antes de qualquer descida.
* **Operação de Divisão (Nó Interno Puro):** Elementos $[12, 50, 60]$. O elemento mediano é o $50$.
* *Regra do Texto para Nós Internos:* Diferente do que ocorre com as folhas, o elemento mediano que sobe para criar a nova raiz **NÃO permanece** nos nós filhos internos resultantes (não há duplicação em divisões de nós puramente internos).
* Nova Raiz Suprema: $[50]$
* Novo Filho Interno Esquerdo: $[12]$
* Novo Filho Interno Direito: $[60]$
* *Distribuição dos subfilhos existentes:*
* O nó $[12]$ herda os ponteiros para as folhas $[1]$ e $[12, 18, 20]$.
* O nó $[60]$ herda os ponteiros para as folhas $[50]$ e $[60, 64, 66]$.


* **Decisão de Descida:** Com a árvore reestruturada em níveis mais altos, buscamos inserir o elemento $38$ a partir da nova raiz $[50]$. Como $38 < 50$, descemos para o nó interno $[12]$. Comparamos $38 > 12$, descendo para a folha $[12, 18, 20]$.
* **Inserção Efetiva:** O nó $[12, 18, 20]$ possui exatamente 3 chaves, logo está completo. Ele deve ser dividido.
* **Divisão da Folha $[12, 18, 20]$:** O valor mediano é $18$. Ele sobe para o seu pai atual ($[12]$) e duplica-se na folha direita.
* Nó pai atualizado: $[12, 18]$
* Folha Esquerda: $[12]$
* Folha Direita: $[18, 20]$
* **Inserção Efetiva de 38:** A partir de $[12, 18]$, como $38 > 18$, descemos para a folha $[18, 20]$. Adicionamos o $38$ de forma ordenada.
* **Resultado:**

```
                    [ 50 ]
                   /        \
            [ 12, 18 ]       [ 60 ]
           /    |     \     /      \
  [ 1 ] -> [ 12 ] -> [ 18, 20, 38 ] -> [ 50 ] -> [ 60, 64, 66 ]

```

---

### Inserção de 95

* **Análise:** Da raiz $[50]$ ($1$ chave $\rightarrow$ ok), $95 > 50 \rightarrow$ descemos para o nó interno $[60]$ ($1$ chave $\rightarrow$ ok). Como $95 > 60$, direcionamo-nos para a folha $[60, 64, 66]$.
* **Gatilho do Algoritmo:** A folha $[60, 64, 66]$ está **completa** (capacidade máxima de 3 chaves). Divisão preventiva realizada.
* **Operação de Divisão:** Elementos $[60, 64, 66]$. O mediano é $64$. Sobe para o pai $[60]$ e repete-se na folha direita.
* Nó pai atualizado: $[60, 64]$
* Folha Esquerda: $[60]$
* Folha Direita: $[64, 66]$
* **Inserção Efetiva:** No nó pai atualizado $[60, 64]$, como $95 > 64$, descemos para a folha $[64, 66]$. Adicionamos $95$ de forma ordenada.
* **Resultado:**

```
                    [ 50 ]
                   /        \
            [ 12, 18 ]       [ 60, 64 ]
           /    |     \     /    |     \
  [ 1 ] -> [ 12 ] -> [ 18, 20, 38 ] -> [ 50 ] -> [ 60 ] -> [ 64, 66, 95 ]

```

---

### Inserção de 58

* **Análise:** Da raiz $[50]$, $58 > 50 \rightarrow$ descemos para o nó interno $[60, 64]$. Como $58 < 60$, a rota de descida indica a folha apontada pelo ponteiro à esquerda de 60, que é a folha $[50]$.
* **Inserção Efetiva:** O nó folha $[50]$ possui apenas uma chave (espaço livre). Adicionamos $58$ ordenadamente.
* **Resultado:**

```
                    [ 50 ]
                   /        \
            [ 12, 18 ]       [ 60, 64 ]
           /    |     \     /    |     \
  [ 1 ] -> [ 12 ] -> [ 18, 20, 38 ] -> [ 50, 58 ] -> [ 60 ] -> [ 64, 66, 95 ]

```

---

### Inserção de 59

* **Análise:** Da raiz $[50]$, $59 > 50 \rightarrow$ descemos para o nó interno $[60, 64]$. Como $59 < 60$, a rota aponta para a folha $[50, 58]$.
* **Inserção Efetiva:** O nó folha $[50, 58]$ possui duas chaves (ainda há espaço para mais uma). Adicionamos $59$ ordenadamente.
* **Resultado:**

```
                    [ 50 ]
                   /        \
            [ 12, 18 ]       [ 60, 64 ]
           /    |     \     /    |     \
  [ 1 ] -> [ 12 ] -> [ 18, 20, 38 ] -> [ 50, 58, 59 ] -> [ 60 ] -> [ 64, 66, 95 ]

```

---

### Inserção de 70

* **Análise:** Da raiz $[50]$, $70 > 50 \rightarrow$ descemos para o nó interno $[60, 64]$. O nó possui duas chaves (espaço livre $\rightarrow$ ok). Como $70 > 64$, direcionamo-nos para a folha da extrema direita: $[64, 66, 95]$.
* **Gatilho do Algoritmo:** A folha $[64, 66, 95]$ está **completa**. Realizamos a divisão preventiva.
* **Operação de Divisão da Folha:** Elementos $[64, 66, 95]$. O mediano é $66$. Sobe para o pai $[60, 64]$ e replica-se na folha direita.
* Nó pai atualizado: $[60, 64, 66]$
* Folha Esquerda: $[64]$
* Folha Direita: $[66, 95]$
* **Inserção Efetiva:** No pai atualizado $[60, 64, 66]$, avaliamos $70$. Como $70 > 66$, descemos para a nova folha da direita $[66, 95]$. Adicionamos $70$ de forma ordenada.
* **Resultado:**

```
                    [ 50 ]
                   /        \
            [ 12, 18 ]       [ 60, 64, 66 ]
           /    |     \     /    |    |    \
  [ 1 ] -> [ 12 ] -> [ 18, 20, 38 ] -> [ 50, 58, 59 ] -> [ 60 ] -> [ 64 ] -> [ 66, 70, 95 ]

```

---

### Inserção de 68

* **Análise:** Da raiz $[50]$, $68 > 50 \rightarrow$ descemos para o nó interno $[60, 64, 66]$.
* **Gatilho do Algoritmo (Nó Interno Completo):** O nó intermediário $[60, 64, 66]$ está com 3 chaves. Realizamos a divisão preventiva de nó interno puro antes de prosseguir.
* **Operação de Divisão:** Elementos $[60, 64, 66]$. O elemento mediano é $64$. Ele sobe para compor a raiz principal $[50]$, que passa a ser $[50, 64]$.
* Raiz atualizada: $[50, 64]$
* Novo nó interno esquerdo: $[60]$ (que herda os ponteiros para as folhas $[50, 58, 59]$ e $[60]$)
* Novo nó interno direito: $[66]$ (que herda os ponteiros para as folhas $[64]$ e $[66, 70, 95]$)
* **Decisão de Descida Atualizada:** A partir da nova raiz $[50, 64]$, avaliamos $68$. Como $68 > 64$, descemos para o nó interno direito $[66]$. Nele, como $68 > 66$, prosseguimos para a folha $[66, 70, 95]$.
* **Gatilho na Folha:** A folha $[66, 70, 95]$ está completa. Realizamos a divisão da folha.
* **Operação de Divisão da Folha:** Elementos $[66, 70, 95]$. O mediano é $70$. Sobe para o pai $[66]$ e replica-se na folha direita.
* Nó pai atualizado: $[66, 70]$
* Folha Esquerda: $[66]$
* Folha Direita: $[70, 95]$
* **Inserção Efetiva:** No pai $[66, 70]$, como $66 \le 68 < 70$, descemos para a folha da esquerda $[66]$. Adicionamos $68$ de forma ordenada.
* **Resultado:**

```
                                [ 50, 64 ]
                            /       |       \
               [ 12, 18 ]        [ 60 ]        [ 66, 70 ]
              /    |     \      /      \      /    |     \
  [ 1 ] -> [ 12 ] -> [ 18, 20, 38 ] -> [ 50, 58, 59 ] -> [ 60 ] -> [ 64 ] -> [ 66, 68 ] -> [ 70, 95 ]

```

---

### Inserção de 39

* **Análise:** Da raiz $[50, 64]$, $39 < 50 \rightarrow$ descemos para o nó interno $[12, 18]$. Como $39 > 18$, o caminho indica a folha $[18, 20, 38]$.
* **Gatilho do Algoritmo:** A folha $[18, 20, 38]$ está completa. Efetuamos a divisão.
* **Operação de Divisão:** Elementos $[18, 20, 38]$. O mediano é $20$. Sobe para o pai $[12, 18]$ e repete-se na folha direita.
* Nó pai atualizado: $[12, 18, 20]$
* Folha Esquerda: $[18]$
* Folha Direita: $[20, 38]$
* **Inserção Efetiva:** No pai $[12, 18, 20]$, como $39 > 20$, descemos para a folha $[20, 38]$. Adicionamos $39$ ordenadamente.
* **Resultado:**

```
                                [ 50, 64 ]
                            /       |       \
            [ 12, 18, 20 ]       [ 60 ]        [ 66, 70 ]
           /    /    \    \     /      \      /    |     \
  [ 1 ] -> [ 12 ] -> [ 18 ] -> [ 20, 38, 39 ] -> [ 50, 58, 59 ] -> [ 60 ] -> [ 64 ] -> [ 66, 68 ] -> [ 70, 95 ]

```

---

### Inserção de 62

* **Análise:** Da raiz $[50, 64]$, como $50 \le 62 < 64$, descemos para o nó interno intermediário, que é o $[60]$. No nó $[60]$, avaliamos as folhas: se $62 > 60$, a rota indica a folha $[60]$.
* **Inserção Efetiva:** A folha $[60]$ possui espaço livre. Adicionamos o $62$ ordenadamente.
* **Resultado:**

```
                                [ 50, 64 ]
                            /       |       \
            [ 12, 18, 20 ]       [ 60 ]        [ 66, 70 ]
           /    /    \    \     /      \      /    |     \
  [ 1 ] -> [ 12 ] -> [ 18 ] -> [ 20, 38, 39 ] -> [ 50, 58, 59 ] -> [ 60, 62 ] -> [ 64 ] -> [ 66, 68 ] -> [ 70, 95 ]

```

---

### Inserção de 7

* **Análise:** Da raiz $[50, 64]$, $7 < 50 \rightarrow$ descemos para o nó interno $[12, 18, 20]$.
* **Gatilho do Algoritmo:** O nó interno $[12, 18, 20]$ está completo. Realiza-se a divisão preventiva de nó interno.
* **Operação de Divisão:** Elementos $[12, 18, 20]$. O mediano é $18$. Sobe para compor a raiz principal $[50, 64]$.
* A raiz principal tem espaço livre (2 chaves). Adicionamos o $18$ nela.
* Raiz atualizada: $[18, 50, 64]$
* Os nós intermediários deste ramo passam a ser $[12]$ (com as folhas $[1]$ e $[12]$) e $[20]$ (com as folhas $[18]$ e $[20, 38, 39]$).
* **Decisão de Descida Atualizada para o elemento 7:** A partir da raiz atualizada $[18, 50, 64]$, como $7 < 18$, descemos para o nó interno intermediário $[12]$. No nó $[12]$, como $7 < 12$, prosseguimos para a folha $[1]$.
* **Inserção Efetiva:** O nó folha $[1]$ tem espaço livre. Adicionamos o $7$ de forma ordenada.
* **Resultado:**

```
                                [ 18, 50, 64 ]
                            /       /     \       \
                      [ 12 ]    [ 20 ]   [ 60 ]    [ 66, 70 ]
                     /    \    /    \   /    \    /    |     \
  [ 1, 7 ] -> [ 12 ] -> [ 18 ] -> [ 20, 38, 39 ] -> [ 50, 58, 59 ] -> [ 60, 62 ] -> [ 64 ] -> [ 66, 68 ] -> [ 70, 95 ]

```

---

### Inserção de 55

* **Análise:** Da raiz $[18, 50, 64]$, como $18 \le 55 < 50$ é falso, avaliamos $50 \le 55 < 64$. Descemos para o nó interno correspondente, que é o $[60]$. No nó $[60]$, como $55 < 60$, a rota indica a folha $[50, 58, 59]$.
* **Gatilho do Algoritmo:** A folha $[50, 58, 59]$ está **completa**. Realizamos a divisão preventiva.
* **Operação de Divisão da Folha:** Elementos $[50, 58, 59]$. O mediano é $58$. Sobe para o pai $[60]$ e permanece na folha direita.
* Nó pai atualizado: $[58, 60]$
* Folha Esquerda: $[50]$
* Folha Direita: $[58, 59]$
* **Inserção Efetiva:** No pai atualizado $[58, 60]$, avaliamos $55$. Como $50 \le 55 < 58$, descemos para a folha da esquerda $[50]$. Adicionamos o $55$ ordenadamente.
* **Resultado:**

```
                                [ 18, 50, 64 ]
                            /       /     \       \
                      [ 12 ]    [ 20 ]   [ 58, 60 ]  [ 66, 70 ]
                     /    \    /    \   /    |    \ /    |     \
  [ 1, 7 ] -> [ 12 ] -> [ 18 ] -> [ 20, 38, 39 ] -> [ 50, 55 ] -> [ 58, 59 ] -> [ 60, 62 ] -> [ 64 ] -> [ 66, 68 ] -> [ 70, 95 ]

```

---

### Inserção de 43

* **Análise:** Da raiz $[18, 50, 64]$, como $18 \le 43 < 50$, descemos para o nó interno $[20]$. No nó $[20]$, $43 > 20 \rightarrow$ descemos para a folha $[20, 38, 39]$.
* **Gatilho do Algoritmo:** A folha $[20, 38, 39]$ está completa. Divisão preventiva realizada.
* **Operação de Divisão:** Elementos $[20, 38, 39]$. O mediano é $38$. Sobe para o pai $[20]$ e permanece na folha direita.
* Nó pai atualizado: $[20, 38]$
* Folha Esquerda: $[20]$
* Folha Direita: $[38, 39]$
* **Inserção Efetiva:** No pai atualizado $[20, 38]$, como $43 > 38$, descemos para a folha $[38, 39]$. Adicionamos o $43$ ordenadamente.
* **Resultado:**

```
                                [ 18, 50, 64 ]
                            /       /     \       \
                      [ 12 ]  [ 20, 38 ] [ 58, 60 ]  [ 66, 70 ]
                     /    \    /   |   \ /    |    \ /    |     \
  [ 1, 7 ] -> [ 12 ] -> [ 18 ] -> [ 20 ] -> [ 38, 39, 43 ] -> [ 50, 55 ] -> [ 58, 59 ] -> [ 60, 62 ] -> [ 64 ] -> [ 66, 68 ] -> [ 70, 95 ]

```

---

### Inserção de 16

* **Análise:** Da raiz $[18, 50, 64]$, $16 < 18 \rightarrow$ descemos para o nó interno $[12]$. Nele, como $16 > 12$, somos direcionados para o seu filho direito, que é a folha $[18]$.
* **Inserção Efetiva:** A folha $[18]$ possui espaço livre. Adicionamos o $16$ ordenadamente.
* **Resultado:**

```
Folhas afetadas no ramo intermediário: ... -> [ 12 ] -> [ 16, 18 ] -> [ 20 ] -> ...

```

---

### Inserção de 67

* **Análise:** Da raiz $[18, 50, 64]$, $67 > 64 \rightarrow$ descemos para o nó interno $[66, 70]$. Nele, como $66 \le 67 < 70$, a rota indica a folha central de seu ramo, que é a $[66, 68]$.
* **Inserção Efetiva:** A folha $[66, 68]$ possui espaço livre. Adicionamos o $67$ de forma ordenada.
* **Resultado:**

```
Folhas afetadas no ramo intermediário: ... -> [ 64 ] -> [ 66, 67, 68 ] -> [ 70, 95 ]

```

---

### Inserção de 34

* **Análise:** Da raiz $[18, 50, 64]$, como $18 \le 34 < 50$, descemos para o nó interno $[20, 38]$. Como $20 \le 34 < 38$, a rota direciona a descida para a folha intermediária $[38, 39, 43]$.
* **Gatilho do Algoritmo:** A folha $[38, 39, 43]$ está completa. Divisão preventiva aplicada.
* **Operação de Divisão:** Elementos $[38, 39, 43]$. O mediano é $39$. Sobe para o pai $[20, 38]$ e permanece na folha direita.
* Nó pai atualizado: $[20, 38, 39]$
* Folha Esquerda: $[38]$
* Folha Direita: $[39, 43]$
* **Inserção Efetiva:** No pai atualizado $[20, 38, 39]$, como $34 < 38$, descemos para a folha $[38]$. Adicionamos o $34$ ordenadamente.
* **Resultado:**

```
                                [ 18, 50, 64 ]
                            /       /     \       \
                      [ 12 ] [ 20, 38, 39 ] [ 58, 60 ] [ 66, 70 ]

```

*(Visualização resumida das folhas associadas ao ramo central: $\dots \rightarrow [ 20 ] \rightarrow [ 34, 38 ] \rightarrow [ 39, 43 ] \rightarrow \dots$)*

---

### Inserção de 35

* **Análise:** Da raiz $[18, 50, 64]$, como $18 \le 35 < 50$, descemos para o nó interno $[20, 38, 39]$.
* **Gatilho do Algoritmo (Nó Interno Completo):** O nó interno $[20, 38, 39]$ está completo. Devemos realizar a divisão preventiva de nó interno puro.
* **Operação de Divisão:** Elementos $[20, 38, 39]$. O mediano é $38$. Sobe para o pai $[18, 50, 64]$.
* **Gatilho Crítico na Raiz Suprema:** A raiz principal $[18, 50, 64]$ está completa e receberia o $38$. Seguindo o algoritmo de uma única passagem, a **raiz principal deve ser dividida primeiro**, antes de propagar a divisão para o nó interno.
* **Divisão da Raiz Suprema:** Elementos $[18, 50, 64]$. O mediano é $50$. Ele sobe criando uma nova raiz isolada no topo.
* Nova Raiz Absoluta: $[50]$
* Novo Filho Interno Esquerdo da Raiz: $[18]$
* Novo Filho Interno Direito da Raiz: $[64]$
* **Finalização da Divisão do nó interno $[20, 38, 39]$:** Agora que a sub-árvore foi reestruturada e o nó $[18]$ possui espaço livre, o elemento $38$ (proveniente da divisão de $[20, 38, 39]$) pode subir para ele.
* Nó $[18]$ passa a ser: $[18, 38]$
* Os nós intermediários divididos passam a ser $[20]$ (com as folhas $[16, 18]$ e $[20]$) e $[39]$ (com as folhas $[34, 38]$ e $[39, 43]$).
* **Decisão de Descida Atualizada para o elemento 35:** A partir da nova raiz absoluta $[50]$, como $35 < 50$, descemos para o nó interno esquerdo $[18, 38]$. Nele, como $18 \le 35 < 38$, descemos para o nó interno $[20]$. No nó $[20]$, como $35 > 20$, prosseguimos para a sua folha direita, que é a folha $[34, 38]$.
* **Inserção Efetiva:** A folha $[34, 38]$ possui espaço livre. Adicionamos o $35$ ordenadamente.

---

## Estrutura da Árvore $B^+$ Concluída (Estado Final)

### Estrutura de Nós Internos (Índices)

$$Nível 0 (Raiz): [50]$$

$$\text{Nível 1 (Esquerda): } [18, 38] \quad \lvert \quad \text{Nível 1 (Direita): } [64]$$

$$\text{Nível 2 (Sub-ramos de Índices):}$$

* Filhos de $[18, 38] \rightarrow [12], [20], [39]$
* Filhos de $[64] \rightarrow [58, 60], [66, 70]$

---

### Nível das Folhas (Dados Encadeados de Forma Linear)

```
[ 1, 7 ] -> [ 12 ] -> [ 16, 18 ] -> [ 20 ] -> [ 34, 35, 38 ] -> [ 39, 43 ] -> [ 50, 55 ] -> [ 58, 59 ] -> [ 60, 62 ] -> [ 64 ] -> [ 66, 67, 68 ] -> [ 70, 95 ]

```