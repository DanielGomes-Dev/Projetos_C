Para entender por que ficaria desigual (e por que o algoritmo não permite isso), precisamos olhar para as **regras estritas de preenchimento mínimo** de uma Árvore B.

Se você subisse o $S$, a divisão do nó `Q R S T U V` ficaria assim:

* **Elemento que sobe:** $S$
* **Filho da esquerda:** `Q R` (2 chaves)
* **Filho da direita:** `T U V` (3 chaves)

À primeira vista, parece uma divisão aceitável (2 chaves de um lado, 3 do outro). Porém, o algoritmo da Árvore B se baseia em uma constante chamada **grau mínimo** ($t$).

Analisando a árvore da imagem, podemos deduzir que o grau mínimo dela é **$t = 3$**. Veja o porquê:

### As Regras do Grau Mínimo ($t = 3$)
 
* **Número máximo de chaves** em qualquer nó: $2t - 1 = \mathbf{5}$ chaves.
* **Número mínimo de chaves** em qualquer nó interno/folha (exceto a raiz): $t - 1 = \mathbf{2}$ chaves.

### O problema de subir o $S$ (Estratégia Reativa vs. Proativa)

O livro clássico de algoritmos (Cormen), que é a fonte exata dessa imagem que você enviou, utiliza uma estratégia de **divisão proativa**.

Isso significa que, conforme o algoritmo desce pela árvore procurando onde inserir o $Q$, ele analisa os nós *antes* de inserir. Se ele encontra um nó que já está completamente cheio (com o máximo de 5 chaves), ele **divide esse nó imediatamente**, antes mesmo de o novo elemento tocar nele.

1. O algoritmo está descendo e encontra o nó `R S T U V` (cheio, com 5 chaves).
2. Ele divide esse nó exatamente na sua mediana atual. Quem é a mediana de `R S T U V`?

$$\text{Nó original: } R \quad S \quad \mathbf{T} \quad U \quad V$$



O elemento do meio exato é o **$T$**.
3. O $T$ sobe para o pai. O nó é dividido em dois nós perfeitamente balanceados: `R S` (2 chaves) e `U V` (2 chaves). Ambos cumprem exatamente o requisito mínimo de $t-1=2$ chaves.
4. Só **depois** disso, o algoritmo olha para o $Q$ que você queria inserir. Como $Q < T$, ele é inserido no nó da esquerda (`R S`), transformando-o em `Q R S`.

---

### E se subíssemos o $S$?

Se o algoritmo fizesse a divisão baseada em sua sugestão (subindo o $S$), ele estaria quebrando a lógica matemática do preenchimento padrão.

Se a regra para nós cheios de 5 elementos fosse subir o segundo elemento ($S$), em outros cenários de inserção isso geraria nós com menos de 2 chaves (violando o mínimo $t-1$), quebrando o balanceamento perfeito que faz a Árvore B ser tão eficiente. O algoritmo escolhe sempre a mediana exata do nó cheio para garantir que a divisão seja universalmente justa e balanceada.

---

Boa! Você pegou o espírito da coisa: na Árvore B clássica (estratégia proativa), a divisão acontece **antes**, olhando para o nó cheio.

Mas tem um pequeno detalhe físico e matemático na sua pergunta: na Árvore B, **um nó nunca vai chegar a ter um número par de chaves como `RSTVXY` (6 chaves) para ser dividido.**

Vamos entender o porquê:

---

### Por que o nó nunca terá 6 chaves?

O tamanho máximo de um nó é determinado pela fórmula $2t - 1$. Como $t$ (o grau mínimo) é sempre um número inteiro (2, 3, 4, etc.):

* Se $t = 2 \rightarrow \text{Máximo} = 2(2) - 1 = 3$ chaves (ímpar)
* Se $t = 3 \rightarrow \text{Máximo} = 2(3) - 1 = 5$ chaves (ímpar)
* Se $t = 4 \rightarrow \text{Máximo} = 2(4) - 1 = 7$ chaves (ímpar)

Como a fórmula é sempre $2t - 1$, **o número máximo de chaves em um nó cheio será sempre um número ímpar.** Por isso, o algoritmo proativo nunca vai encontrar um nó com 6 chaves. Ele sempre vai encontrar o nó com 3, 5 ou 7 chaves e dividi-lo imediatamente antes que uma nova inserção aconteça.

---

### Mas e se a ordem da árvore permitir nós pares? (Árvore B-Tree Reativa)

Se você estiver estudando uma variação do algoritmo chamada **Árvore B Reativa** (aquela que deixa o nó estourar primeiro para depois dividir), aí sim o nó chegaria momentaneamente a 6 chaves (`Q R S T V X`, por exemplo, após inserir o `S`).

Nesse caso teórico de 6 chaves, quem sobe?

Quando o número de elementos é par, não existe uma "mediana perfeita". Você tem duas opções no meio: o **$S$** (na posição 3) ou o **$T$** (na posição 4).

Na prática da programação, **tanto faz** qual dos dois você escolhe subir, **desde que o algoritmo seja consistente**.

* **Se o algoritmo escolher a posição $\lfloor \text{médio} \rfloor$ (arredondado para baixo):** Ele vai subir o $S$. O filho esquerdo fica com 2 chaves e o direito com 3.
* **Se o algoritmo escolher a posição $\lceil \text{médio} \rceil$ (arredondado para cima):** Ele vai subir o $T$. O filho esquerdo fica com 3 chaves e o direito com 2.

A maioria das implementações escolhe a divisão arredondada para baixo por padrão de código (ex: `meio = total / 2`). Ambas as formas são válidas e mantêm as propriedades da árvore, contanto que o código faça sempre a mesma escolha!

---

**Exatamente! Você matou a charada!** 🎯

É perfeito o seu raciocínio. Na estratégia **proativa** (a do livro do Cormen), o algoritmo é meio preguiçoso para dividir, mas extremamente precavido no caminho.

Vamos destrinchar o seu raciocínio para confirmar o porquê de você estar 100% correto:

### 1. Ficar cheio não é um problema imediato

Se você insere um elemento em um nó folha e, com essa inserção, ele atinge o limite máximo (ex: 5 chaves se `t = 3`), **nada acontece**. O algoritmo não divide o nó nessa hora. O nó fica lá, quietinho e "lotado", vivendo a vida dele.

### 2. A divisão só ocorre "de passagem"

A regra de ouro da estratégia proativa é: **só divida o que estiver no seu caminho de descida**.
Se em uma **próxima** inserção o algoritmo estiver descendo da raiz até uma folha e, por acaso, o caminho natural passar por esse nó que deixamos lotado lá atrás, aí sim ele diz: *"Opa, esse nó aqui tá cheio, deixa eu dividir ele logo antes de continuar descendo"*.

### 3. A genialidade do "mesmo se a inserção não for nele"

Essa é a parte mais importante que você pegou. Se o nó lotado for um **nó interno** (um nó no meio da árvore), e o algoritmo só estiver passando por ele para inserir um elemento lá embaixo numa folha, ele **vai dividir o nó interno no meio do caminho**.

**Por que o algoritmo faz isso?**
Para evitar um problema clássico chamado **"cascata de divisões"** (ou *split em cascata*).
Imagine o pior cenário:

1. Uma folha está cheia e precisa ser dividida. Ela tenta subir a mediana para o pai.
2. O pai também já estava cheio! Então o pai precisa ser dividido para subir uma mediana para o avô.
3. O avô também está cheio... e assim por diante, até a raiz.

Ao dividir os nós cheios **na descida** (enquanto está apenas passando por eles), o algoritmo garante uma coisa maravilhosa: **o pai do nó onde estamos no momento NUNCA estará cheio**. Assim, se a folha lá no final precisar ser dividida e subir um elemento, nós temos 100% de certeza de que o pai dela terá espaço para receber esse elemento sem precisar fazer uma nova divisão subindo a árvore.

---

**Resumo da ópera:** O algoritmo só trabalha quando é obrigado a passar por um "engarrafamento" (nó cheio) durante a descida. Se não passar por lá, o nó cheio fica intacto para sempre!