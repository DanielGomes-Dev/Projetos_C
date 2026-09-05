Conforme solicitado, procederei com a transcrição fiel dos tópicos apresentados, removendo as redundâncias das animações e consolidando os casos do algoritmo.

---

## Operações básicas: retirada

* Mais complicada que a inserção: chave pode ser eliminada de qualquer nó (não só folha)
* Retirada em um nó interno: filhos podem ser reorganizados porque não se pode violar o limite inferior de chaves em uma árvore B
* Deve-se garantir que nenhum nó terá menos que t – 1 chaves, exceto a raiz
* Algoritmo de retirada é chamado recursivamente em um nó x, com no mínimo t chaves
* A condição supracitada exige, pelo menos, 1 chave a mais que o mínimo

### Algoritmo de retirada

* **CASO 1:** se a chave k está em x, e x é folha, elimine k de x
* **CASO 2:** se a chave k está em x:
* **CASO 2A:** se o filho y que precede k no nó x tem, ao menos, t chaves, então encontre o predecessor k’ de k na árvore com raiz em y. Elimine recursivamente k’ e substitua k por k’ em x
* **CASO 2B:** se o filho z que sucede k no nó x tem, ao menos, t chaves, então encontre o sucessor k’ de k na árvore com raiz em z. Elimine recursivamente k’ e substitua k por k’ em x
* **CASO 2C:** se tanto y e z têm apenas t – 1 chaves, faça a intercalação de k com todas as chaves de z em y, de modo que x perca a chave k e o ponteiro z. Assim, y terá 2t – 1 chaves. A seguir retire recursivamente k de y.


* **CASO 3:** se a chave k não está em x, descubra qual é o filho f onde k pode estar. Se f tiver t – 1 chaves, faça ou o CASO 3A, ou o CASO 3B.
* Essa ação é necessária para garantir que desceremos até um nó contendo, ao menos, t chaves. Em seguida, execute a recursão sobre o filho apropriado de x
* **CASO 3A:** se a subárvore onde k deve estar tiver somente t – 1 chaves, mas possuir um irmão com t chaves, forneça ao pai uma chave do irmão, e retire o ponteiro associado a chave emprestada, caso este ponteiro exista
* **CASO 3B:** se o filho f (que pode conter k) de x tem t - 1 chaves e todos os seus irmãos imediatos têm t – 1 chaves também, faça a intercalação de f com um de seus irmãos, o que envolve mover uma chave do pai para o novo nó intercalado



> **Nota:** CASOS 2C e 3B são as únicas operações que podem causar o decremento da altura da árvore

### Considerações finais

* Maioria das chaves estão armazenadas nas folhas
* Algoritmo continua ser de uma passagem
* Mesmo nos CASOS 2A e 2B, onde se substitui chaves (ou pelo predecessor, ou pelo sucessor, respectivamente)

---

