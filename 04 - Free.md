# Free

O `free` é o parceiro inseparável do `malloc`. Para entender como ele funciona, imagine que a memória do seu computador é um **grande estacionamento**.

### 1. O `malloc` reserva a vaga
Quando você usa o `malloc` (como mostrado no slide 7 para criar um nó), você está dizendo ao computador: *"Por favor, reserve um espaço para mim, vou colocar dados aqui"*. O sistema operacional marca aquela "vaga" como ocupada e te dá o endereço.

### 2. O `free` libera a vaga
A memória do computador é finita. Se você criar milhares de nós (usando `malloc`) e nunca avisar que terminou de usá-los, a memória vai acabar (isso é o que chamamos de **Memory Leak** ou vazamento de memória).

O `free(ponteiro)` diz ao sistema: *"Pode liberar essa vaga! Não vou mais usar o que está neste endereço"*.

### Como ele funciona na prática (Regras de Ouro):

1.  **Só libere o que você alocou:** Você só deve usar `free` em ponteiros que receberam um valor via `malloc`, `calloc` ou `realloc`.
2.  **Cuidado com o "Ponteiro Zumbi":** Depois que você faz `free(arv)`, o ponteiro `arv` ainda guarda o endereço de memória, mas você não tem mais permissão para olhar o que está lá. É como ter a chave de um quarto de hotel depois de ter feito o check-out: a chave pode até abrir a porta, mas o quarto não é mais seu e pode ter outra pessoa lá dentro.
3.  **Não libere o que você ainda vai usar:** No exercício da árvore, note que primeiro nós salvamos os filhos do nó em variáveis auxiliares ou re-penduramos as subárvores, e **só depois** damos o `free`. Se você der o `free` primeiro, perde o acesso aos filhos do nó.

### Exemplo visual no seu exercício:

```c
TAB *aux = arv->esq; // 1. Primeiro guardamos o endereço dos filhos
free(arv);            // 2. Agora o nó atual (a raiz) pode sumir
return aux;           // 3. Mas a subárvore que estava guardada em aux continua viva
```



### Por que isso é vital na questão (Q6)?
Se você apenas remover o valor par mudando o ponteiro, mas não usar o `free`, o nó par continuará existindo "fantasma" na memória do computador, ocupando espaço inutilmente até o programa ser fechado. Em sistemas que rodam por muito tempo (como um servidor), isso pode travar o computador.

Ficou clara a analogia do estacionamento?