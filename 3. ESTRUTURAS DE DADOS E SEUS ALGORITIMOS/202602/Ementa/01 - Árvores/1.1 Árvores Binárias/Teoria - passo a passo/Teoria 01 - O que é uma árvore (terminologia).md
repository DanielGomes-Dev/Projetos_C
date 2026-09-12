# Teoria 01 — O que é uma árvore, e o vocabulário básico

> **Onde isto entra:** antes de falar de árvore *binária* especificamente, você precisa do
> vocabulário que vale para qualquer árvore (raiz, folha, altura, nível...) — esse
> vocabulário aparece em todo o curso, não só neste subtópico.
> **Antes:** nenhum pré-requisito de estruturas de dados; só é preciso saber o que é um
> ponteiro (revisão em `KR`, caps. 5–6, se precisar).
> **Fonte:** `lista01-EDA/04_Arvores.pdf` (slides da Profa. Vanessa Braganholo, baseados no
> livro de Celes/Cerqueira/Rangel).

## 1. A ideia em uma frase

Uma árvore é um jeito de organizar dados **em hierarquia**: existe um elemento no topo (a
**raiz**), e cada elemento pode ter vários "elementos-filho" abaixo dele — nunca um filho
que aponta de volta para cima nem para o lado.

## 2. De onde vem / por que essa estrutura existe

Pense num sistema de arquivos: uma pasta contém arquivos e outras pastas, que por sua vez
contêm mais arquivos e pastas. Isso **não é uma sequência** (como um array ou uma lista) —
é uma hierarquia. O PDF da aula usa exatamente esse exemplo (uma pasta `noworkflow` com
subpastas `docx2tex`, `perfil`, `workspace`, etc.) para motivar a estrutura antes de definir
qualquer coisa formalmente. Outros exemplos do mesmo PDF: a árvore de derivação que um
compilador monta para entender a expressão `(a * b) + (c / (d + e))`, e uma árvore que
guarda números em ordem (o embrião da BST, que você vê em 1.2).

## 3. O vocabulário — lido devagar, peça por peça

Considere esta árvore concreta, tirada do PDF (slide 3):

```
              A
          /  |  \
         B   C   D
         |  / \   |
         E F   G  H
              / | \
             I  J  K
```

> 📖 **Lendo devagar — cada termo, um de cada vez:**
>
> 1. **Raiz** — o único nó sem "pai" (aqui, `A`). É por onde qualquer acesso à árvore
>    começa — nunca se entra "pelo meio".
> 2. **Filho** de um nó — o que está diretamente abaixo, ligado a ele. Filhos de `A`: `B`,
>    `C`, `D`. Filhos de `H`: `I`, `J`, `K`.
> 3. **Pai** de um nó — o inverso: quem está diretamente acima. Pai de `H` é `D`.
> 4. **Irmãos** — nós com o mesmo pai. `B`, `C`, `D` são irmãos entre si (todos filhos de
>    `A`). `I`, `J`, `K` também são irmãos entre si (todos filhos de `H`).
> 5. **Grau de um nó** — quantos filhos ele tem. Grau de `A` = 3 (tem `B`,`C`,`D`). Grau de
>    `C` = 2 (tem `F`,`G`). Grau de `E` = 0.
> 6. **Grau da árvore** — o maior grau entre todos os nós. Nesta árvore, é 3 (por causa de
>    `A`).
> 7. **Nó interno** — grau maior que zero (tem pelo menos um filho): `A`, `B`, `C`, `D`, `H`.
> 8. **Nó folha** (ou terminal) — grau igual a zero (não tem filho nenhum): `E`, `F`, `G`,
>    `I`, `J`, `K`.
> 9. **Caminho** — uma sequência de nós ligados, sem repetir nenhum, entre dois nós. Existe
>    **exatamente um** caminho entre a raiz e qualquer outro nó (é uma das coisas que torna
>    árvore diferente de grafo genérico — em árvore não há "outro jeito de chegar lá").
> 10. **Comprimento do caminho** — quantas ligações (arestas) esse caminho tem, não quantos
>     nós. O caminho `A → D → H → K` tem 3 ligações, então comprimento 3 (mesmo passando por
>     4 nós).
> 11. **Nível de um nó** — comprimento do caminho da raiz até ele. `A` está no nível 0
>     (raiz sempre nível 0). `B`, `C`, `D` estão no nível 1. `E`, `F`, `G`, `H` no nível 2.
>     `I`, `J`, `K` no nível 3.
> 12. **Altura da árvore** — o maior nível que existe, ou seja, o comprimento do caminho
>     mais longo entre a raiz e uma folha. Aqui, altura = 3 (por causa de `I`, `J`, `K`).
> 13. **Floresta** — simplesmente um conjunto de árvores (não precisam estar ligadas entre
>     si).

## 4. Conferindo com a árvore concreta acima

**Afirmação:** todo nó, exceto a raiz, tem exatamente um pai; a raiz não tem pai nenhum.
**Conferindo:** `H` tem pai `D` (só um). `A` — procure quem aponta pra ele: ninguém. `A` é
raiz. ✔

**Afirmação:** altura da árvore = maior nível entre todos os nós.
**Conferindo:** níveis presentes: 0 (`A`), 1 (`B,C,D`), 2 (`E,F,G,H`), 3 (`I,J,K`). O maior
é 3. Altura = 3. ✔ (bate com "comprimento do caminho mais longo": `A→D→H→K`, 3 ligações.)

## 5. Letra miúda

**E aquele "altura de nó folha é 0"?** É convenção, não teorema. Alguns livros/professores
definem altura de um nó *folha isolado* como 0, e altura de árvore *vazia* como −1. Você vai
ver essa segunda convenção usada no código de `TAB_altura` (Teoria 05) — ali, `altura(NULL)
= -1` é exatamente o que faz a fórmula funcionar sem caso especial para folha. Não decore
"o número certo" — decore que **é preciso conferir a convenção usada** antes de uma prova.

## 6. Exercícios de fixação

Usando a árvore do PDF (a mesma do começo deste arquivo):

1. Qual é o grau do nó `D`?
2. `F` e `G` são irmãos? Por quê?
3. Qual o nível do nó `E`?
4. Existe mais de um caminho entre `A` e `K`? Por quê (ou por que não)?
5. Se essa árvore e outra árvore isolada `X — Y` (só dois nós) estivessem juntas no mesmo
   desenho, sem nenhuma ligação entre as duas, como se chama essa coisa (árvore + árvore
   separada)?

### Gabarito

1. Grau de `D` = 1 (só tem o filho `H`).
2. Sim — ambos são filhos do mesmo nó (`C`), que é a definição de irmãos.
3. Nível de `E`: caminho `A → B → E`, 2 ligações → nível 2.
4. Não. Em árvore, o caminho entre a raiz e qualquer nó é único — é uma propriedade
   estrutural (não existe um "atalho" alternativo). Caminho `A → D → H → K`.
5. Uma **floresta** (conjunto de árvores, sem exigir que estejam ligadas).

## Resumo

- Árvore = hierarquia: uma raiz, e cada nó tem filhos (nunca aponta "pra trás" ou "pro
  lado").
- Vocabulário essencial: pai/filho/irmão, grau (do nó e da árvore), nó interno vs. folha.
- Caminho é único entre raiz e qualquer nó; comprimento do caminho conta **ligações**, não
  nós.
- Nível = distância da raiz até o nó; altura = o maior nível que existe na árvore.

**Próximo:** [[Teoria 02 - Árvore binária (definição e por que esquerda-direita importa)]].
