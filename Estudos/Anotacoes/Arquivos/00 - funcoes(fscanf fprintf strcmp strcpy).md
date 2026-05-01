Para entender como essas funções manipulam arquivos, é importante lembrar que, em C, um arquivo é tratado como um **fluxo (stream)** e o controle de onde estamos lendo ou escrevendo é feito por um **cursor** (apontador interno), como mencionado no seu material de apoio.

Aqui está o detalhamento de cada uma:

---

## 1. `fscanf` (File Scan Formatted)
É a função de **leitura**. Ela funciona de forma muito parecida com o `scanf`, mas em vez de ler do teclado, ela lê de um arquivo.

* **Como funciona:** Ela busca dados no arquivo seguindo um formato específico (como `%s` para strings ou `%d` para inteiros).
* **O Cursor:** Quando o `fscanf` lê uma palavra, o cursor do arquivo "anda" e para logo após o último caractere lido.
* **Comportamento com espaços:** Ao usar `%s`, o `fscanf` lê caracteres até encontrar um "espaço em branco" (espaço, tabulação ou quebra de linha). Isso a torna ideal para ler o arquivo palavra por palavra.
* **Retorno:** Ela retorna o número de itens lidos com sucesso. Se chegar ao fim do arquivo, retorna a constante `EOF`.

---

## 2. `fprintf` (File Print Formatted)
É a função de **escrita**. É a versão do `printf` para arquivos.

* **Como funciona:** Ela envia uma string formatada para o fluxo do arquivo apontado por `FILE *fp`.
* **O Cursor:** A cada escrita, o cursor avança para o final do que foi escrito, permitindo que a próxima chamada do `fprintf` adicione conteúdo logo em seguida.
* **Uso no exercício:** No código, usamos `fprintf(fpOut, " %s", atual)`. O espaço antes do `%s` é essencial para que as palavras não fiquem grudadas no arquivo de saída, já que o `fscanf` removeu os espaços originais ao ler.

---

## 3. `strcmp` (String Compare)
Esta função pertence à biblioteca `<string.h>` e é usada para comparar o **conteúdo** de duas strings (vetores de caracteres).

* **Por que não usar `==`?** Em C, se você fizer `if (string1 == string2)`, você estará comparando o endereço de memória onde elas começam, e não o texto em si.
* **Funcionamento:** Ela compara caractere por caractere (baseado na tabela ASCII).
* **Retorno:**
    * `0`: Se as strings forem exatamente **iguais**.
    * Valor diferente de `0`: Se forem diferentes.
* **No exercício:** Usamos `if (strcmp(atual, anterior) != 0)` para verificar se a palavra que acabamos de ler é diferente da que lemos antes.



---

## 4. `strcpy` (String Copy)
Também da biblioteca `<string.h>`, ela é usada para copiar o conteúdo de uma string para outra.

* **Sintaxe:** `strcpy(destino, origem);`
* **Funcionamento:** Ela copia todos os caracteres da string de "origem" para o vetor de "destino", incluindo o caractere nulo (`\0`) que marca o fim da string.
* **No exercício:** Após escrevermos uma palavra no arquivo de saída, usamos `strcpy(anterior, atual)`. Isso faz com que a palavra que era a "atual" passe a ser a "anterior" para a próxima rodada do laço `while`.

---

## Como elas trabalham juntas no fluxo do arquivo?

Imagine o arquivo como uma fita magnética:

1.  O **`fscanf`** puxa uma palavra da fita para a memória (variável `atual`).
2.  O **`strcmp`** verifica se essa palavra é igual à "foto" que tiramos da palavra passada (`anterior`).
3.  Se for diferente, o **`fprintf`** carimba essa palavra em uma nova fita (arquivo de saída).
4.  O **`strcpy`** atualiza a nossa "foto" (`anterior`) para que possamos comparar com a próxima rodada.
5.  O processo se repete até o **`fscanf`** perceber que a fita acabou.



Ficou claro como o cursor se movimenta enquanto essas funções são executadas, ou gostaria de ver um exemplo de como o cursor se comporta caractere por caractere?