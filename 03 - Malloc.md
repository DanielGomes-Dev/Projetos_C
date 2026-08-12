# Malloc

`TAB *novo = (TAB *)malloc(sizeof(TAB));`

Com certeza! Essa é a linha que mais "assusta" quem está começando em C, mas ela é fundamental. Vamos quebrá-la em quatro partes, como se estivéssemos fazendo uma compra em uma loja de materiais de construção.

Para facilitar, imagine que a memória do seu computador é um **estacionamento gigante** com milhares de vagas numeradas.

---

### 1. `sizeof(TAB)` (A Medida)
Antes de pedir espaço, você precisa saber o tamanho do que quer guardar. 
* O `sizeof` é um operador que pergunta ao computador: "Quantos bytes ocupa uma estrutura do tipo `TAB`?".
* Ele olha para a sua `struct` (que tem um `int` e dois ponteiros) e calcula o total (ex: 20 bytes).

### 2. `malloc(...)` (O Pedido de Reserva)
A função `malloc` (Memory Allocation) é o "manobrista" do estacionamento.
* Quando você faz `malloc(20)`, você está dizendo: "Ei, encontre um lugar vazio nesse estacionamento que caiba exatamente 20 bytes seguidos".
* O `malloc` vai lá, reserva o espaço para você não ser atropelado por outros dados e **retorna o endereço** (o número da vaga) de onde esse espaço começa.

### 3. `(TAB *)` (O "Crachá" ou Cast)
O `malloc` é uma função genérica; ele entrega o espaço, mas não sabe o que você vai colocar lá. Ele retorna um "ponteiro para o nada" (`void *`).
* O `(TAB *)` entre parênteses é o que chamamos de **Typecast**.
* Você está dizendo ao compilador: "Olha, trate esse endereço de memória que o `malloc` me deu como o início de uma estrutura do tipo `TAB`". É como colocar uma placa na vaga dizendo: **"Reservado para Árvore Binária"**.

### 4. `TAB *novo` (A Variável de Controle)
Aqui você está criando a variável `novo`, que é um **ponteiro**.
* Note que `novo` **não é o nó em si**, ele é apenas um papel onde você anotou o endereço que o `malloc` te deu.
* Através desse endereço, você consegue chegar no nó real e usar a "setinha" (`->`) para mexer no conteúdo.

---

### Resumo Visual do Processo

Imagine a execução dessa linha acontecendo assim:

1.  **Cálculo:** "Preciso de 20 bytes." (`sizeof`)
2.  **Busca:** "Achei um espaço livre no endereço 0x500." (`malloc`)
3.  **Etiqueta:** "Esse espaço agora é oficialmente uma `TAB`." (`cast`)
4.  **Registro:** "Guarde o endereço 0x500 dentro da variável `novo`."



### Por que não fazer apenas `TAB novo;`?
Se você declarasse apenas `TAB novo;` (sem ponteiro e sem malloc), o C criaria o nó na **Stack** (pilha). O problema é que variáveis na Stack são destruídas assim que a função termina. 
Usando `malloc`, o nó é criado no **Heap** (monte), que é uma memória permanente. Ele só deixará de existir se você usar o comando `free(novo)` ou se o programa fechar. Para uma árvore que cresce e diminui, o `malloc` é indispensável!

Ficou mais claro agora o papel de cada "peça" dessa linha? Se quiser, posso te explicar o que acontece se o `malloc` não encontrar espaço (o famoso erro de memória).