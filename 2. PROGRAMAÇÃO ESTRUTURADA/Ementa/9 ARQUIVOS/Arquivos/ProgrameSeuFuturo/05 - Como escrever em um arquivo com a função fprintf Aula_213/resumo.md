Este vídeo apresenta a função **`fprintf`** na linguagem C, que permite gravar dados formatados diretamente em arquivos, funcionando de maneira muito semelhante ao conhecido `printf`.

Abaixo, apresento um resumo detalhado dos pontos principais abordados:

---

## 1. O que é a função `fprintf`?
A letra **'f'** no início da função vem de *file* (arquivo). Enquanto o `printf` imprime dados na tela (saída padrão), o `fprintf` imprime dados dentro de um arquivo.
* **Sintaxe:** `fprintf(ponteiro_do_arquivo, "formatação", variáveis);`
* **Vantagem:** Ela permite salvar diferentes tipos de dados (strings, inteiros, floats) de forma organizada e legível em um arquivo de texto (`.txt`).

---

## 2. Estrutura do Código e Variáveis
No exemplo prático, o instrutor utiliza um procedimento chamado `escrever` que recebe o nome do arquivo. Dentro dele, são definidas três variáveis para capturar dados do usuário:
* `char nome[100]` (String)
* `int idade` (Inteiro)
* `float altura` (Real)

### Captura de Dados com `scanf`
Para ler o nome completo ou evitar problemas com espaços, utiliza-se uma máscara específica no `scanf`:
`scanf("%100[^\n]", nome);` — Isso diz ao programa para ler até 100 caracteres ou até que a tecla **Enter** (`\n`) seja pressionada.

---

## 3. Gravando no Arquivo
Após abrir o arquivo com `fopen` (usando o modo `"w"` para escrita ou `"a"` para anexar), a gravação é feita assim:

```c
fprintf(file, "%s %d %.2f\n", nome, idade, altura);
```
* `%s`: Grava a string (nome).
* `%d`: Grava o inteiro (idade).
* `%.2f`: Grava o float (altura) limitado a duas casas decimais.
* `\n`: Garante que, ao adicionar um novo registro, ele comece em uma linha nova.

---

## 4. Criando um Loop de Cadastro (Menu)
Para permitir que o usuário insira múltiplos registros sem fechar o programa, o código é envolvido em uma estrutura **`do-while`**:
1.  O programa pede os dados.
2.  Grava no arquivo usando `fprintf`.
3.  Pergunta ao usuário: "Digite 1 para inserir outro registro".
4.  Se a opção for `1`, o laço repete; caso contrário, o arquivo é fechado com `fclose`.

---

## 5. Dica Técnica: Limpando o Buffer do Teclado
Um problema comum em C acontece quando lemos um número (`scanf("%d", &opcao)`) e logo em seguida tentamos ler uma string. O caractere "Enter" fica "preso" no buffer do teclado e faz com que a próxima leitura de texto seja pulada.

**Solução apresentada:**
O instrutor utiliza um `scanf("%c");` (ou uma leitura de caractere simples) logo após ler a opção do menu para "consumir" esse Enter residual antes da próxima iteração do laço.

---

### Resumo Visual da Diferença
| Função | Destino da Saída | Exemplo |
| :--- | :--- | :--- |
| `printf` | Monitor (Console) | `printf("Olá Mundo");` |
| `fprintf` | Arquivo físico no disco | `fprintf(arq, "Olá Mundo");` |

> **Nota:** No final do vídeo, é mostrado o arquivo `.txt` gerado, contendo os nomes, idades e alturas formatados exatamente como foram digitados, prontos para serem lidos por outro programa posteriormente.