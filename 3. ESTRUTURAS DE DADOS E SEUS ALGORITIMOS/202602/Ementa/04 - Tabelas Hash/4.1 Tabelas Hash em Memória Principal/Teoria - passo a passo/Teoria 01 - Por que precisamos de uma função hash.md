# Teoria 01 — Por que precisamos de uma função hash

> **Onde isto entra:** é a motivação de todo o módulo — sem entender o problema que a
> tabela hash resolve, os métodos de tratamento de colisão (Teorias 02–04) parecem
> arbitrários.
> **Antes:** nenhum pré-requisito além de vetor/array em C.
> **Fonte:** CE (Celes, Cerqueira e Rangel — *Introdução a Estruturas de Dados*), Cap. 18
> "Tabelas de dispersão", pág. 271–274.

## 1. A ideia em uma frase

Uma função hash pega uma chave (ex.: um número de matrícula) e calcula, na hora, **em qual
posição de um vetor pequeno** aquele dado deveria morar — sem precisar de um vetor do
tamanho de todos os valores possíveis.

## 2. O problema real que motiva isso (exemplo do livro)

O livro usa este exemplo: uma disciplina quer guardar dados de alunos, cada um identificado
por uma matrícula de 7 dígitos úteis (ex.: `9711234`, de `9711234-4` — o último dígito, após
o hífen, é só controle e não conta). O aluno é representado por:

```c
struct aluno {
  int mat;
  char nome[81];
  char email[41];
  char turma;
};
typedef struct aluno Aluno;
```

**Primeira ideia (ingênua): usar a matrícula direto como índice do vetor.**

```c
#define MAX 10000000
Aluno vet[MAX];
```

Assim, `vet[mat].nome` acessa o aluno na hora — O(1) de verdade, sem busca nenhuma. Mas
repare no tamanho: matrícula de 7 dígitos vai de `0` a `9999999`, então o vetor precisa de
**10 milhões de posições**, mesmo que a turma real tenha uns 50 alunos.

> **Conferindo o custo:** cada `struct aluno` ocupa uns 127 bytes. `10.000.000 × 127 ≈ 1,27
> GB` de memória — para guardar informação de **50 pessoas**. Trocando o vetor por
> ponteiros (`Aluno* vet[MAX]`, alocando só os alunos que existem), o gasto cai para
> `10.000.000 × 4 bytes ≈ 40 MB` (só os ponteiros) — melhor, mas ainda um desperdício
> gigantesco para 50 registros reais.

## 3. A ideia central: usar só a parte que importa da chave

O livro observa (Fig. 18.1 do PDF): nem todo dígito da matrícula ajuda a distinguir alunos
**dentro de uma turma**. Os primeiros dígitos (ano/período de ingresso) tendem a se repetir
entre colegas de turma — não ajudam a diferenciar. Os **últimos dígitos** (sequencial de
matrícula) são os que realmente variam de aluno para aluno.

> 📖 **A jogada:** em vez de guardar a matrícula inteira como índice, guarda-se só uma
> tabela pequena (ex.: 100 posições) e usa-se **os 2 últimos dígitos** da matrícula como
> índice — via `mat % 100`.

```c
Aluno *tab[100];
// acessar: tab[mat % 100]->nome
```

## 4. A função hash — lida devagar

```c
static int hash(int mat) {
  return (mat % 100);
}
```

> 📖 **Lendo devagar:**
> 1. `mat % 100` — resto da divisão de `mat` por 100. Isso **sempre** devolve um número
>    entre `0` e `99` — não importa quão grande `mat` seja, o resultado sempre cabe no
>    vetor de 100 posições.
> 2. É exatamente isso que faz `hash` ser uma **função hash**: ela mapeia um universo grande
>    de chaves (matrículas de 7 dígitos) para um intervalo pequeno e fixo de índices
>    (`0..99`).
> 3. Generalizando para uma tabela de tamanho `N` qualquer: `hash(mat) = mat % N`.

**Conferindo com números concretos:** matrícula `9711234` numa tabela `N = 100`:
`9711234 % 100 = 34`. Matrícula `9805534` na mesma tabela: `9805534 % 100 = 34` **também** —
os dois alunos caem na mesma posição, mesmo sendo pessoas diferentes.

## 5. O preço de encolher a tabela: colisão

> **Colisão:** quando duas chaves diferentes produzem o mesmo índice via `hash`.

O exemplo da seção 4 já mostrou uma: `9711234` e `9805534` colidem na posição `34`. Isso
**sempre pode acontecer** quando o universo de chaves (milhões de matrículas possíveis) é
maior que o tamanho da tabela (100 posições) — é matemática, não falha de implementação.
O que se pode controlar é: (a) minimizar quantas colisões acontecem (função hash "boa") e
(b) ter uma estratégia para lidar com as que acontecem (Teorias 02–04).

## 6. Letra miúda: o que faz uma função hash "boa"

O livro lista duas propriedades desejáveis:

- **Eficiente de calcular** — `mat % N` é uma conta trivial; se calcular o hash fosse mais
  lento que simplesmente procurar o elemento, perderíamos a vantagem toda.
- **Espalha bem as chaves** — evitar que muitas chaves caiam sempre nas mesmas poucas
  posições. O livro dá um contra-exemplo: usar **os primeiros dígitos** da matrícula como
  índice seria uma função hash **ruim** aqui, porque alunos da mesma turma compartilham
  esses dígitos — quase todo mundo colidiria nas mesmas 3–4 posições.

**Regra empírica do livro:** a tabela não deve passar de ~75% de ocupação (acima disso, o
número de colisões cresce descontroladamente); ~50% costuma dar bom resultado; abaixo de
~25%, começa a desperdiçar memória sem ganho real.

## 7. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| `mat % N` | comprimo um número grande (matrícula) num intervalo pequeno e fixo (índices do vetor) |
| escolher quais dígitos usar | decido quais partes da chave realmente **diferenciam** os elementos, ignorando as que se repetem |
| aceitar que colisão vai acontecer | troco "acesso garantido sem nenhum choque" (o vetor gigante) por "acesso rápido na prática, com plano B para os raros choques" |

## 8. Exercícios de fixação

1. Calcule `hash(mat) = mat % 100` para as matrículas `1234567`, `1234500` e `987654`.
   Alguma colide com outra?
2. Por que usar os **primeiros** dígitos da matrícula (em vez dos últimos) seria uma função
   hash pior, neste contexto específico de "alunos de uma turma"?
3. Se a tabela tem `N = 50` posições e já tem 40 alunos cadastrados, qual é a taxa de
   ocupação? Isso está dentro da regra empírica do livro (~75% no máximo)?
4. Por que trocar `Aluno vet[MAX]` (vetor de structs) por `Aluno* vet[MAX]` (vetor de
   ponteiros) já reduz o desperdício de memória, mesmo **antes** de reduzir o tamanho `MAX`
   do vetor?

### Gabarito

1. `1234567 % 100 = 67`; `1234500 % 100 = 0`; `987654 % 100 = 54`. Nenhuma colide — os três
   restos são diferentes (`67`, `0`, `54`).
2. Porque, dentro de uma turma, muitos alunos entraram no mesmo ano/período — os primeiros
   dígitos da matrícula se repetem entre eles. Usar esses dígitos como índice faria vários
   alunos diferentes caírem nas mesmíssimas poucas posições — o oposto de "espalhar bem".
3. Taxa de ocupação = `40/50 = 0,8 = 80%`. Isso **ultrapassa** os 75% recomendados pelo
   livro — sinal de que a tabela deveria crescer (ver rehashing, Teoria 05).
4. Porque um ponteiro ocupa um tamanho fixo pequeno (tipicamente 4 ou 8 bytes), enquanto
   `struct aluno` ocupa ~127 bytes. Com vetor de ponteiros, as posições **sem aluno
   cadastrado** custam só o tamanho do ponteiro (e valem `NULL`), em vez do tamanho da
   struct inteira desperdiçada.

## Resumo

- Função hash: mapeia uma chave (potencialmente de um universo enorme) para um índice
  dentro de um vetor pequeno e fixo — normalmente via `chave % N`.
- Isso resolve o desperdício de memória de "usar a chave direto como índice", ao custo de
  poder haver **colisão** (duas chaves diferentes, mesmo índice).
- Uma boa função hash é rápida de calcular e espalha bem as chaves reais do seu problema —
  "bem" depende do contexto (o exemplo mostrou que usar dígitos diferentes da mesma
  matrícula pode ser bom ou ruim, dependendo de quais dígitos realmente variam).

**Próximo:** [[Teoria 02 - Colisões — tratamento por posição livre (endereçamento aberto)]].
