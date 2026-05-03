Esta é uma explicação detalhada de como o código foi desenvolvido e como ele se fundamenta nos conceitos teóricos de manipulação de arquivos fornecidos no seu material.

---

## 1. Fundamentos Teóricos Aplicados
De acordo com o texto base, o exercício utiliza os seguintes conceitos:

* **Tipo de Arquivo:** Trabalhamos com **Arquivos de Texto**, onde os dados são representados como caracteres e organizados sequencialmente.
* **Fluxo (Stream):** O programa cria um caminho para que os dados saiam da memória secundária (disco) para a memória principal (RAM) via `fscanf` e retornem via `fprintf`.
* **Cursor e Buffer:** Ao ler cada palavra com `fscanf`, o **cursor** do arquivo é incrementado automaticamente, apontando para a próxima palavra. Ao usar `fclose`, garantimos que o **buffer** seja descarregado, salvando os dados corretamente no disco.

---

## 2. Análise Detalhada das Funções Utilizadas

O código utiliza as operações da biblioteca `stdio.h` mencionadas no material:

* **`fopen(nome, modo)`**:
    * `fopen(ArqEnt, "r")`: Abre o arquivo de entrada para **leitura**. O material especifica que o arquivo deve existir previamente.
    * `fopen(ArqSaida, "w")`: Abre o arquivo de saída para **gravação**. Se já existir, o conteúdo é destruído; se não, é criado.
* **`fscanf(fp, "%s", variável)`**: Utilizado para ler "palavra por palavra". O especificador `%s` para strings para automaticamente em espaços, tabulações ou quebras de linha, o que é ideal para isolar palavras consecutivas.
* **`fprintf(fp, formato, dados)`**: Escreve a palavra processada no arquivo de destino.
* **`fclose(fp)`**: Fecha os fluxos, essencial para evitar perda de dados (descarregar o buffer).

---

## 3. Lógica de Resolução do Problema

A estratégia para resolver a remoção de duplicatas consecutivas (como "texto texto") segue este passo a passo lógico:

### Passo 1: Inicialização e Verificação
O procedimento recebe os nomes dos arquivos e tenta abri-los. Seguindo o exemplo do material (`if(!fp1)`), verificamos se os ponteiros são `NULL`. Se houver erro, o programa encerra a função para evitar falhas de segmentação.

### Passo 2: O Ponto de Partida
Para comparar palavras consecutivas, precisamos de uma base. O código lê a **primeira palavra** do arquivo separadamente:
```c
if (fscanf(fpIn, "%s", anterior) == 1) {
    fprintf(fpOut, "%s", anterior); // Grava a primeira palavra obrigatoriamente
}
```
Aqui, a variável `anterior` armazena a palavra que acabou de ser processada.

### Passo 3: O Laço de Comparação (Sequencialidade)
Como o material define arquivos texto como organizados **sequencialmente**, usamos um laço `while` para percorrer o arquivo até o fim:
1.  O `fscanf` lê a próxima palavra (`atual`).
2.  O `strcmp` (da `string.h`) compara `atual` com `anterior`.
3.  **Se forem diferentes:** A palavra `atual` não é uma repetição imediata. Ela é gravada no arquivo de saída precedida por um espaço.
4.  **Atualização:** A palavra `atual` torna-se a nova `anterior` para a próxima iteração.
5.  **Se forem iguais:** O programa simplesmente não faz nada (não grava no arquivo), saltando para a próxima leitura.



---

## 4. Conclusão
O exercício foi resolvido transformando o arquivo em um **acesso sequencial** (conforme a classificação do texto). A eficiência se dá pelo uso do **cursor**: nunca precisamos carregar o arquivo inteiro na memória, apenas duas palavras por vez (`atual` e `anterior`), respeitando a limitação de memória principal e utilizando o mecanismo de **Stream** de forma eficaz.