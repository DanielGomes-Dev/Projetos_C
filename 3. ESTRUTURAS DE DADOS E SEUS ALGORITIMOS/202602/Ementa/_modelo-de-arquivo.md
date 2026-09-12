# _modelo-de-arquivo (não é um exercício — é o gabarito de formatação)

> Adaptado do modelo de Cálculo 2 (`_modelo-de-arquivo.md`) para exercícios de Estruturas
> de Dados. Use ao criar/melhorar um arquivo dentro de uma pasta `Passo a Passo Lista/`
> (uma por lista já resolvida em `ListasExercicios/` ou em `202602/Ementa/.../lista0X-EDA/`).
>
> A solução em código (`Qx/claude/main.c`) **já existe e já foi testada** — este arquivo
> não resolve de novo, ele **explica** a solução existente, devagar, seguindo o método do
> professor sempre que o enunciado/PDF trouxer um método específico.

---

# `<Qx>` — `<título curto: o que se pede>`

> **Origem:** `<PDF da lista, questão N>` · **Código resolvido:** `[[../Qx/claude/main.c]]`
> **Antes disto, veja:** [[Teoria 0Y - ...]] (na pasta `Teoria - passo a passo/` do subtópico)

## 1. O que o exercício pede

Enunciado transcrito exatamente como está no PDF da lista. Depois, uma tradução em
português claro: "Ou seja, precisamos construir / verificar / calcular ..."

## 2. A ideia geral (o mapa antes da viagem)

1 a 3 parágrafos curtos:
- Que **tipo** de problema é este? Como reconhecer isso numa prova?
- Qual a **estratégia**? Se o PDF/aula usa um método específico do professor, é esse que
  vai aqui — "o professor gosta que a resolução seja feita igual ao texto" (ver
  `prompts/explica.md`).
- **Por quê** essa estratégia funciona, em 1 frase.

## 3. Resolução passo a passo

### Passo 1 — `<nome do passo>`

Texto explicando o que vamos fazer e por quê. Depois o trecho de código correspondente
(recorte de `Qx/claude/main.c`) e o que ele faz **nesta entrada específica**:

```c
<trecho relevante>
```

Regras de ouro deste bloco:
- Ponteiro mudou? Desenhe o **antes/depois** (setas, campos), não só descreva em palavras.
- Estrutura de dados mudou de estado (árvore rotacionou, elemento entrou no heap, hash
  colidiu)? Desenhe o **antes/depois** da estrutura inteira, não só do nó afetado.
- Loop ou recursão? Mostre uma **tabela de trace**: iteração/chamada → valores das
  variáveis relevantes → o que decide continuar ou parar.

### Passo 2 — `<...>`

...

## 4. Resultado final

Estrutura final (desenhada) ou saída do programa.

**Conferindo (quando fizer sentido):** rode o código mentalmente com um segundo caso
pequeno, ou verifique uma invariante da estrutura (ex.: BST: percurso em-ordem está
crescente? AVL: todos os fatores de balanceamento estão em {-1,0,1}? Árvore B: todas as
folhas na mesma profundidade?).

## 5. Habilidades necessárias

- [ ] `<habilidade>` — `<1 linha do que é>` → [[Teoria 0Y - ...]]
- [ ] `<habilidade>` — ...

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — `<a mesma ideia, entrada mínima (1-3 nós/elementos)>`

Trace completo, bem curto, à mão (sem precisar do código).

### Aquecimento 2 — `<um degrau abaixo do exercício real>`

Trace completo.

---

## Notas de formatação

- Uma pasta `Passo a Passo Lista/` por lista (`lista01-EDA/Passo a Passo Lista/`,
  `lista02-EDA/Passo a Passo Lista/`, ...), com um arquivo por questão (`Q1 - <título>.md`,
  `Q2 - <título>.md`, ...) e um `README.md` de índice (mesmo papel do README de subtópico
  em `01 - EDOs de 1ª ordem/1.1 - .../README.md` no projeto de Cálculo 2).
- O código-fonte (`Qx/claude/main.c`) não muda — é conteúdo já testado. Este arquivo é
  **documentação/explicação nova**, não correção de código.
- Se o exercício pede rotação/split/rehash manual "no papel" (sem código, tipo prova),
  a "Resolução passo a passo" é só o desenho — não force trecho de código onde não há.
