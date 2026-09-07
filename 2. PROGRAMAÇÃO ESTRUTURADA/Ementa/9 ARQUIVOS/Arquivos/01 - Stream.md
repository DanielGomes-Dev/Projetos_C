Para explicar o conceito de **Fluxo (Stream)** detalhadamente, vamos usar a analogia da **"Linha de Montagem"** ou de um **"Cano de Água"**, que é exatamente como o seu material descreve o "caminho atravessado por dados".

No seu exercício, o fluxo é o que conecta o arquivo no disco rígido (memória secundária) ao seu programa (memória principal/RAM).

---

## 1. O Conceito de Abstração
Em C, o programa não "toca" no arquivo físico diretamente. Ele interage com uma **abstração** chamada `FILE *`. 
* Imagine o arquivo no disco como um reservatório de água.
* O **Stream** é o cano que conecta esse reservatório à sua torneira (o programa).
* Você não precisa saber como o reservatório funciona, apenas como abrir e fechar a torneira.



---

## 2. A Direção do Fluxo
O texto menciona que programas interagem com fontes distintas (DVD, Pen-drive, etc.). O Stream padroniza isso em duas direções:

* **Input Stream (Fluxo de Entrada):** Os dados "fluem" da fonte para o programa. No seu código, o `fscanf` é a bomba que puxa os dados do arquivo de entrada para a variável `atual`.
* **Output Stream (Fluxo de Saída):** Os dados "fluem" do programa para o destino. O `fprintf` empurra os dados da variável para o arquivo de saída.

---

## 3. O Papel do Cursor no Fluxo
Como o material explica, o **cursor** indica a próxima posição a ser lida ou gravada. Imagine o Stream como uma esteira rolante:
1.  O cursor começa na posição `0`.
2.  Quando o `fscanf` lê uma palavra, a esteira anda. 
3.  O cursor agora aponta exatamente para o início da próxima palavra.
4.  O programa não precisa "voltar" ou "pular"; ele apenas consome o que o fluxo traz sequencialmente.

---

## 4. O Fluxo e o Buffer (A importância do `fclose`)
Esta é a parte mais técnica do seu material. O fluxo não envia os dados caractere por caractere para o disco imediatamente, pois isso seria muito lento.

* **O Buffer:** É como um "balde" no meio do cano. O `fprintf` vai enchendo esse balde na memória RAM.
* **O Despejo (Flush):** Quando o balde enche, ou quando você chama o `fclose`, o conteúdo é despejado de uma vez só no arquivo físico.
* **Por que o código usa `fclose`?** Se o seu programa acabar (ou travar com `abort()`) antes do `fclose`, o "balde" (buffer) pode ser jogado fora e os dados que você escreveu com `fprintf` nunca chegarão ao arquivo final.



---

## Resumo no seu Exercício:
No seu procedimento `RetRepet`:
1.  **Abertura:** Você instala dois canos (`fpIn` e `fpOut`).
2.  **Processamento:** Você deixa a água (palavras) correr pelo primeiro cano, filtra as repetições na memória, e bombeia o que sobrou para o segundo cano.
3.  **Fechamento:** Você fecha as torneiras (`fclose`), garantindo que a última gota de dados que estava no "balde" (buffer) caia no arquivo de saída.

Ficou mais claro como os dados "viajam" entre o disco e as variáveis do seu código?