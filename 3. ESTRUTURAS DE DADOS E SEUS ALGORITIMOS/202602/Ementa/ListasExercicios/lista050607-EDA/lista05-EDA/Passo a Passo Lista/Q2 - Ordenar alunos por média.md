# Q2 — Ordenar arquivo de alunos por média crescente

> **Origem:** `lista05-EDA.pdf`, questão 2 · **Código resolvido:** [[../Q2/claude/main.c]]
> **Antes disto, veja:** [[Q1 - Remover palavras repetidas consecutivas]] (leitura de arquivo texto).

## 1. O que o exercício pede

> Receba um arquivo texto com nome do aluno e duas notas (uma linha por aluno) e gere um
> arquivo de saída ordenado em ordem crescente pela média do aluno —
> `void media(char *ArqEnt, char *ArqSaida)`.

Formato adotado (a partir do exemplo do enunciado): cada linha é `nome/nota1/nota2`; saída
é `nome/media`, uma linha por aluno, já ordenada.

## 2. A ideia geral

Diferente de Q1 (que processava palavra por palavra sem guardar nada), aqui é preciso
**carregar todos os alunos em memória** antes de poder ordenar — não dá pra saber a posição
final de ninguém sem ver todo mundo primeiro. Três etapas: (1) ler e converter cada linha
num registro `(nome, média)`, (2) ordenar esse vetor, (3) escrever o vetor ordenado.

## 3. Resolução passo a passo

### Passo 1 — separar nome das notas com `strrchr`

O nome pode conter espaços (ex.: `"P C"`), então não dá pra separar por espaço. A solução
usa `strrchr` (busca a **última** ocorrência de um caractere, da direita pra esquerda) duas
vezes:

```c
char *barra2 = strrchr(linha, '/');   // última '/' -> separa nota2
*barra2 = '\0';                        // corta a string ali (linha vira "nome/n1")
char *barra1 = strrchr(linha, '/');   // penúltima '/' -> separa nota1
*barra1 = '\0';                        // linha vira só "nome"
```

> 📖 **Lendo devagar:** `*barra2 = '\0'` não apaga nada do arquivo — só escreve um terminador
> de string **na cópia em memória** (`linha`), fazendo `linha` "parecer" terminar ali para
> qualquer função que a leia depois (como `printf` ou `snprintf`). É a técnica de "cortar
> uma string no lugar" sem alocar uma nova.

**Conferindo com a linha `"P C/10.0/10.0"`:**
- 1ª `strrchr` acha a última `/` (antes do segundo `10.0`) → corta → `linha = "P C/10.0"`,
  `barra2+1` aponta para `"10.0"`.
- 2ª `strrchr` acha a `/` restante (antes do primeiro `10.0`) → corta → `linha = "P C"`,
  `barra1+1` aponta para `"10.0"`.
- Resultado: nome = `"P C"`, nota1 = nota2 = `10.0`, média = `10.0`.

### Passo 2 — ordenar com insertion sort

```c
for (int i = 1; i < n; i++) {
    Aluno chave = v[i];
    int j = i - 1;
    while (j >= 0 && v[j].media > chave.media) {
        v[j + 1] = v[j];      // empurra pra direita quem é maior que 'chave'
        j--;
    }
    v[j + 1] = chave;          // insere 'chave' na posição correta
}
```

**Tabela de trace**, com médias `[10.0, 3.5, 7.0, 1.0, 5.5]` (na ordem lida do arquivo):

| `i` | `chave` | Estado do vetor **depois** desta iteração |
|---|---|---|
| 1 | 3.5 | `[3.5, 10.0, 7.0, 1.0, 5.5]` |
| 2 | 7.0 | `[3.5, 7.0, 10.0, 1.0, 5.5]` |
| 3 | 1.0 | `[1.0, 3.5, 7.0, 10.0, 5.5]` |
| 4 | 5.5 | `[1.0, 3.5, 5.5, 7.0, 10.0]` |

Cada `chave` "afunda" para a esquerda até achar um vizinho `≤` ela — exatamente a mesma
lógica de "inserir carta na mão já ordenada" do jogo de cartas.

### Passo 3 — escrever o resultado

```c
fprintf(fs, "%s/%.1f\n", v[i].nome, v[i].media);
```

`%.1f` formata com 1 casa decimal, igual ao gabarito (`10.0`, não `10` nem `10.00`).

## 4. Resultado final

```
A A/1.0
J J/3.5
I I/5.5
G G/7.0
P C/10.0
```

**Conferindo:** cada média na saída é `≥` a anterior — a invariante de ordenação crescente.

## 5. Habilidades necessárias

- [ ] `strrchr` para separar campos por um delimitador, da direita para a esquerda.
- [ ] Insertion sort (ordenação em memória — ver módulo de ordenação em memória principal,
      fora do escopo deste módulo de arquivos).
- [ ] Structs em C (`Aluno`) — revisar KR se necessário.

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — dois alunos, já ordenados

Entrada: `"X/5.0/5.0\nY/8.0/8.0"`. Médias: X=5.0, Y=8.0 — já crescente, insertion sort não
move nada. Saída: `"X/5.0\nY/8.0"`.

### Aquecimento 2 — dois alunos, invertidos

Entrada: `"X/9.0/9.0\nY/2.0/2.0"`. Médias: X=9.0, Y=2.0. No passo `i=1`, `chave=2.0` é menor
que `v[0]=9.0`, então `9.0` desloca para a direita e `2.0` assume a posição 0. Saída:
`"Y/2.0\nX/9.0"`.
