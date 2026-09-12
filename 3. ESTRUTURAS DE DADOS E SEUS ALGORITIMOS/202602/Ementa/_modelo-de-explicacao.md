# _modelo-de-explicação (não é conteúdo — é o guia de como explicar teoria)

> Adaptado do modelo usado em `3. CÁLCULO 2\00 - Ementa\_modelo-de-explicacao.md` para o
> contexto de Estruturas de Dados (código C, ponteiros, complexidade, algoritmos).
> Irmão do [[_modelo-de-arquivo]]. Aquele é para **resolver exercício de lista**; este é
> para **explicar um conceito de teoria** (arquivos `Teoria 0X - ...` dentro de
> `Teoria - passo a passo/`).
>
> **Leia a seção 1 antes de escrever qualquer explicação nova.**

---

## 1. Perfil do leitor e dificuldades a contornar

Mesmo perfil de dificuldade documentado para o Daniel em Cálculo 2 (ver a memória
`daniel-explicacoes-matematica`), traduzido para o domínio de algoritmos e código:

| # | Dificuldade | O que isso exige da explicação aqui |
|---|---|---|
| D1 | Dificuldade em ler notação nova "de primeira" | Toda notação nova — $O(\log n)$, `->`, `*ptr`, `&x`, pseudocódigo do livro — é **falada em voz alta** e traduzida na 1ª aparição. Nada de assumir que "é óbvio". |
| D2 | "Sei de forma medíocre, não consigo entender" | Não assumir pré-requisito como sabido. Reconstruir em 1-2 linhas o conceito anterior (recursão, ponteiro, struct) antes de usá-lo. |
| D3 | Ilusão de entendimento que desaba | Toda afirmação abstrata sobre um algoritmo ("isso é O(log n)", "isso mantém a árvore balanceada") vem seguida de uma **execução concreta**: uma estrutura de dados pequena e real, desenhada, passo a passo. |
| D4 | Se perde **dentro** de expressão/chamada composta | Chamada recursiva composta (`TAB_busca(a->esq, elem)` dentro de outra chamada, ou `no->filhos[i-(meio+1)]`) é lida **de dentro pra fora**, pedaço por pedaço, antes de avançar. |
| D5 | Qualificador técnico vago fica "solto" | Toda condição técnica ("para árvore não-vazia", "supondo m ímpar", "amortizado") ganha **frase própria**: o que é, por que está ali, se pode ser ignorada na prática do curso. |
| D6 | "Executo o algoritmo mas não sei o que estou fazendo" | Todo procedimento mecânico (rotação, split, hashing, percurso) vem com uma tabela **"o que você está REALMENTE fazendo"**: passo mecânico → significado. |
| D7 | Teoria empilhada e abstrata trava a leitura | **Um conceito por arquivo.** Título = a pergunta que o arquivo responde. Nunca misturar "definição" + "algoritmo A" + "algoritmo B" no mesmo arquivo. |
| D8 | Enunciado/definição com muita condição junta | Separar visualmente: "o que é livre" (o dado, a entrada) → "a regra/invariante" → "a letra miúda" (casos especiais, limites). |

### Regra-mãe

> **Se uma frase não pode ser dita em voz alta como português comum, ou não pode ser
> conferida numa estrutura de dados concreta (desenhada), ela ainda não está pronta.**

### Regra específica deste curso: exemplo tem que vir de fonte real

Diferente de Cálculo 2 (onde o "livro-base" é implícito no material do professor), aqui
há **4 livros + PDFs de aula** disponíveis em `202602/Ementa/Livros/` e em cada
`lista0X-EDA/*.pdf`. Toda explicação nova deve:

1. **Puxar pelo menos um exemplo concreto de uma fonte real** — PDF de aula (slide) ou um
   dos 4 livros (SZ, CO, CE, KR) — e **citar a origem** (`PDF, slide N` ou `Livro, cap./seção`).
   Quando a fonte não tiver paginação abrível na máquina, cite o nome do arquivo e a seção
   pelo título, e diga isso explicitamente (ver nota em `202602/Ementa/README.md`).
2. Quando a fonte usa um algoritmo/notação diferente do que o professor usa em aula
   (comum entre SZ ↔ CO), **avisar a diferença numa frase curta** em vez de escolher uma
   e esconder a outra — o Daniel precisa saber que existe mais de uma convenção.
3. Se um exemplo do PDF/livro for bom mas incompleto (ex.: só mostra a árvore final, não o
   passo a passo de construção), a explicação aqui **completa o passo a passo**, mas deixa
   claro que o dado de entrada veio da fonte.

---

## 2. Estrutura de um arquivo de explicação

```
# Teoria 0X — <título = a pergunta que este arquivo responde>

> **Onde isto entra:** <1 linha: o que este arquivo destrava>
> **Antes:** [[Teoria 0(X-1) - ...]] · <pré-requisito, se houver>
> **Fonte:** <PDF/slide N ou Livro, cap./seção — de onde vem o exemplo principal>

## 1. A ideia em uma frase (sem notação, sem código)

## 2. De onde vem / por que fazemos assim
   - motivação ANTES do código/fórmula, nunca depois
   - "eu quero uma estrutura/algoritmo que... o que resolve isso?"

## 3. A definição / o algoritmo — lido pedaço por pedaço
   - caixa "Lendo devagar:" quebrando notação ou código de dentro pra fora (D4)
   - LOGO em seguida: execução numa estrutura concreta, desenhada (D3)

## 4. Casos / variações, cada um com seu exemplo concreto

## 5. Letra miúda — cada qualificador técnico com frase própria (D5)

## 6. 📌 O que você está REALMENTE fazendo   ← obrigatório se ensina um procedimento (D6)
   | passo mecânico | o que ele significa |

## 7. Exercícios de fixação
   ### Gabarito
   (resolução completa, com o desenho/trace, no próprio arquivo)

## Resumo
   - 3 a 5 bullets

**Próximo:** [[Teoria 0(X+1) - ...]]
```

---

## 3. Como escrever cada parte (específico de código/algoritmos)

### Introduzir notação/sintaxe (D1, D4)

Na primeira aparição de qualquer símbolo ou construção de C:

> `no->esq` — lê-se "esq de no" ou "campo esq do nó apontado por no": `no` é um **ponteiro**
> para um struct; `->` é o jeito de acessar um campo **através de um ponteiro** (equivalente
> a `(*no).esq`, mas ninguém escreve assim). `esq` é o campo que guarda o ponteiro para a
> subárvore esquerda.

Para uma chamada/expressão composta, quebrar numa lista numerada, de dentro pra fora:

> `TAB_busca(a->esq, elem)` dentro de `if (resp) return resp;` se lê assim:
> 1. `a->esq` — pegue o ponteiro para a subárvore **esquerda** de `a`;
> 2. `TAB_busca(a->esq, elem)` — chame a **mesma função**, agora com essa subárvore como
>    entrada — isso é a **chamada recursiva**;
> 3. o resultado dessa chamada é guardado (implicitamente, no `resp` de fora) para decidir
>    se já achou ou se precisa tentar a direita.

### Verificar com estrutura concreta (D3) — a parte que não pode faltar

Toda afirmação sobre comportamento/complexidade é seguida de uma execução pequena e
fechada, numa estrutura desenhada (árvore em ASCII, array, lista):

> **Afirmação:** a busca em BST desce um nível a cada comparação, então o custo é
> proporcional à **altura** da árvore, não ao número de nós.
> **Conferindo:** na BST `[10 esq=5 dir=[20 esq=15 dir=25]]`, buscar `15` visita
> `10 → 20 → 15`: 3 comparações, e a altura da árvore é 2 (3 níveis) — bate.

### Motivar antes de mostrar (D6, D7)

Ordem sempre: **problema → por que a ideia surge → o algoritmo/estrutura → conferir**.
Nunca começar por "considere a struct `no_avl` com campo `fb`". Começar por "toda vez que
insiro um nó numa BST comum ela pode virar uma lista encadeada disfarçada (pior caso O(n))
— que estrutura garante que isso nunca aconteça?".

### Qualificador técnico (D5)

Errado: "...para uma árvore B de ordem m (com m ≥ 3, ímpar por convenção neste curso): ..."

Certo — seção curta:

> **E aquele "m ≥ 3"?** É letra miúda. Ordem `m=2` faria cada nó ter no máximo 1 chave —
> isso degenera numa lista encadeada, perde a vantagem da árvore B. Na prática deste curso
> os exercícios usam m pequeno (3, 4, 5) só pra caber no papel; **pode assumir m ≥ 3**.

### "O que você está REALMENTE fazendo" (D6)

Tabela de duas colunas. Coluna 1 = o passo mecânico (o comando, a linha de código, a regra
do algoritmo). Coluna 2 = o significado.

| O passo mecânico | O que ele realmente é |
|---|---|
| "calculo fb = altura(dir) - altura(esq)" | meço o quanto a árvore está "pesada" pra um lado |
| "se \|fb\| > 1, faço uma rotação" | troco a forma da árvore sem mudar o que ela representa (a busca em-ordem continua igual) |
| "rotação simples vs dupla" | escolho a cirurgia certa dependendo de **onde** o desequilíbrio está |

### Exercícios de fixação (D3)

- 5 a 10 itens curtos, crescentes.
- Misturar tipos: "leia este trecho de código em voz alta", "desenhe o resultado", "ache o
  erro num código quase certo", "calcule a complexidade".
- **Gabarito logo abaixo, no mesmo arquivo**, com o desenho/trace feito — não só a resposta.

---

## 4. Checklist antes de dar por pronto

- [ ] Tem pelo menos um exemplo com origem citada (PDF/slide ou livro)? (regra específica)
- [ ] Cada símbolo/sintaxe nova foi falada em voz alta na 1ª aparição? (D1)
- [ ] Cada chamada/expressão composta foi lida de dentro pra fora? (D4)
- [ ] Toda ideia abstrata tem uma execução concreta (desenhada) logo depois? (D3)
- [ ] A motivação vem **antes** do código/definição? (D6, D7)
- [ ] Cada qualificador técnico tem frase própria dizendo se pode ser ignorado? (D5)
- [ ] Se ensina um procedimento, tem a tabela "o que você está REALMENTE fazendo"? (D6)
- [ ] É **um** conceito só neste arquivo? (D7)
- [ ] Tem exercícios + gabarito com o trace/desenho no próprio arquivo? (D3)
- [ ] Dá pra ler o arquivo inteiro em voz alta sem travar em nenhum símbolo ou linha de código?

---

## 5. Diferença chave em relação ao modelo de Cálculo 2

- Lá, "conferir com número" é uma conta. Aqui, "conferir com estrutura concreta" é **um
  desenho** (árvore, lista, tabela hash com buckets, grafo com vértices/arestas) ou um
  **trace de execução** (estado das variáveis a cada iteração/chamada recursiva).
- Aqui, todo procedimento tem, além da tabela "o que você está REALMENTE fazendo", uma
  seção de **complexidade** (melhor/pior caso) sempre que fizer sentido — é parte do que
  o curso cobra e é abstrato o suficiente pra precisar da mesma tradução que uma fórmula.
- Código é mostrado **com comentário de linha explicando o "porquê"**, não só o "o quê"
  (o nome da função e as variáveis já dizem o "o quê" — ver convenção do projeto em
  `CLAUDE.md`/instruções gerais sobre comentários, mas aqui, excepcionalmente, comentar o
  "porquê" de cada linha de um algoritmo novo é o objetivo pedagógico do arquivo).
