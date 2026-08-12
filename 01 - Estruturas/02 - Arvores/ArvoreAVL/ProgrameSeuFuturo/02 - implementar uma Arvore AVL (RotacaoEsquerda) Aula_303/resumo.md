Este vídeo explica detalhadamente o funcionamento lógico e a implementação da **Rotação à Esquerda** em uma Árvore AVL (Árvore Binária de Busca Balanceada). O objetivo dessa operação é restaurar o equilíbrio da árvore quando ela se torna "pesada" à direita.

Aqui está o resumo detalhado dos pontos principais:

---

## 1. Identificando a Necessidade da Rotação
A rotação à esquerda ocorre quando um nó (que chamaremos de **R**) fica desbalanceado para a direita. Isso é identificado pelo **Fator de Balanceamento (FB)**:
* **Cálculo:** $FB = \text{altura\_esquerda} - \text{altura\_direita}$
* **Sintoma:** Se o $FB = -2$, a subárvore direita é significativamente maior que a esquerda, indicando que a árvore "pendue" para a direita (formato sequencial).



---

## 2. A Lógica da Rotação (Passo a Passo)
O professor utiliza dois ponteiros auxiliares para não perder a referência dos nós durante a movimentação:

1.  **Ponteiro Y:** Aponta para o filho à direita da raiz desbalanceada (**R->direita**). Este nó **Y** será a nova raiz da subárvore.
2.  **Ponteiro F:** Aponta para o filho à esquerda de **Y** (**Y->esquerda**). Este nó é crucial porque ele precisará mudar de pai.

### As Mudanças de Conexão:
* **Promoção de Y:** O nó **Y** sobe para o lugar de **R**.
* **Descida de R:** O nó **R** torna-se o novo filho à **esquerda** de **Y**.
* **Realocação de F:** Como o lugar à esquerda de **Y** agora está ocupado por **R**, o antigo filho **F** (que estava à esquerda de Y) passa a ser o novo filho à **direita** de **R**.
    * *Lógica:* Isso mantém a propriedade da Árvore Binária de Busca, pois **F** é maior que **R**, mas menor que **Y**.

---

## 3. Implementação do Código e Atualização de Alturas
Após mover os ponteiros, a estrutura física da árvore mudou, o que significa que as alturas dos nós foram alteradas.

* **Recálculo de Altura:** É necessário chamar uma função auxiliar para atualizar a altura de **R** e depois a de **Y** (nesta ordem, pois a altura de Y depende da nova altura de R).
* **Fórmula da Altura:** $Altura = 1 + \max(\text{altura\_esquerda}, \text{altura\_direita})$
* **Retorno:** A função deve retornar o ponteiro para **Y**, informando à função principal qual é a nova raiz daquela subárvore.

---

## 4. Dica Didática
O professor enfatiza que, devido às sutilezas dos ponteiros e da lógica de "sobe e desce" dos nós, a melhor forma de fixar o conteúdo é:
* **Desenhar no papel:** Simular os ponteiros mudando de lugar manualmente.
* **Atenção à Ordem:** Salvar os filhos em variáveis auxiliares antes de sobrescrever os ponteiros para não causar perda de dados (memory leak ou perda de nós da árvore).

> **Próximo Passo:** O vídeo encerra preparando o terreno para a **Rotação à Direita**, que segue a lógica inversa para árvores desbalanceadas à esquerda ($FB = +2$).


---

Com certeza! Esse código é a implementação clássica de uma **rotação simples à esquerda** em uma Árvore AVL. Essa operação é usada quando a árvore fica desbalanceada para a direita (quando inserimos um elemento maior que o filho da direita).

Vamos analisar linha a linha, focando na lógica dos ponteiros.

---

## 1. Variáveis Auxiliares
```c
No *y, *f;
```
* **`r`**: É o nó que está desbalanceado (a raiz da subárvore atual).
* **`y`**: Será o nó que "subirá" para se tornar a nova raiz.
* **`f`**: É o "filho órfão". Como `y` vai ganhar um novo filho à esquerda (o `r`), se ele já tivesse um filho à esquerda, esse filho precisaria ser movido.



---

## 2. Preparando o Terreno
```c
y = r->direito;
f = y->esquerdo;
```
Aqui o código identifica quem é quem:
1.  O nó à direita de `r` é promovido (`y`).
2.  O filho à esquerda de `y` é guardado em `f`. **Por que?** Porque na Árvore Binária de Busca, tudo à esquerda de `y` é maior que `r` e menor que `y`. Por isso, ele terá que ser encaixado em `r` depois.

---

## 3. Realizando a Rotação
```c
y->esquerdo = r;
r->direito = f;
```
Esta é a "mágica" da rotação:
* **`y->esquerdo = r`**: O nó desbalanceado (`r`) desce e se torna filho à esquerda da nova raiz (`y`).
* **`r->direito = f`**: O antigo filho de `y` (`f`) agora é adotado como filho à direita de `r`. Isso mantém a ordem numérica da árvore correta.

---

## 4. Atualização das Alturas
```c
r->altura = maior(alturaNo(r->esquerdo), alturaNo(r->direito)) + 1;
y->altura = maior(alturaNo(y->esquerdo), alturaNo(y->direito)) + 1;
```
Como a estrutura física mudou, as alturas antigas estão erradas. 
* **Importante**: Você deve atualizar a altura de `r` **primeiro**, porque agora ele está abaixo de `y`. A altura de `y` depende da altura atualizada de seus filhos (um dos quais é o próprio `r`).
* A fórmula é: $Altura = \max(alt\_esq, alt\_dir) + 1$.

> **Nota:** No seu código original, havia um pequeno erro de parênteses no cálculo da altura (o `+1` estava dentro do `maior`). O correto é somar 1 ao resultado da função `maior`, como corrigi acima.

---

## 5. O Retorno
```c
return y;
```
A função retorna `y` porque ele é a **nova raiz** dessa subárvore. Quem chamou essa função (geralmente a função de inserção) precisa atualizar o ponteiro do pai para apontar agora para `y`, e não mais para o antigo `r`.

### Resumo Visual da Mudança:
Antes da rotação, tínhamos uma linha: `r -> y -> (algum nó)`.
Depois da rotação, temos um triângulo: `y` no topo, com `r` à sua esquerda.