## Void


### O que é o tal do `void *`?
Em C, um ponteiro `int *` só aponta para inteiros. Um `float *` só para floats. 
O `void *` é o **ponteiro universal**. Ele aponta para um endereço de memória, mas não diz o que tem lá. É como uma caixa etiquetada apenas com "Conteúdo", sem especificar se tem um livro ou uma maçã dentro.

### Por que "Genérica"?
Imagine que você criou uma lista para guardar `int`. Se amanhã você precisar de uma lista para guardar `Alunos`, você teria que reescrever todo o código da lista. 
Com a lista **genérica**, você escreve o código **uma vez só**. A lista guarda o endereço (`void *`) de qualquer coisa.
