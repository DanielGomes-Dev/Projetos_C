# 1.4 Árvore Número Variável de Filhos

> **Aprendendo do zero?** Comece por [[Teoria - passo a passo/README|Teoria - passo a passo/]]
> — um conceito por arquivo, devagar, com o trace completo de inserção/impressão/liberação
> no final. Este README é a referência rápida (roteiro de leitura + notas + código).

## Objetivo de aprendizagem

- Explicar por que uma árvore binária (no máximo 2 filhos) não serve para representar
  hierarquias com número arbitrário de filhos (diretórios, organogramas, HTML/XML).
- Definir a representação por "lista de filhos" (2 ponteiros por nó: primeiro filho e
  próximo irmão) e sua definição recursiva ("árvore = raiz + zero ou mais subárvores").
- Implementar, em C, as 4 operações pedidas em `conteudo.md`: criação de nó, busca em
  profundidade, inserção (com o pai já existente na árvore) e impressão/liberação em
  profundidade.
- Justificar por que a liberação de memória precisa ser pós-ordem (filhos antes do pai),
  diferente da impressão, que é pré-ordem.

## Roteiro de leitura

- **CE (Celes):** cap. 13, seção "Árvores com número variável de filhos" (págs. 196-205) —
  é a referência principal desta pasta: motiva a representação por lista de filhos,
  apresenta a struct `arvvar` (`prim`/`prox`) e implementa `arvv_cria`, `arvv_insere`,
  `arvv_imprime`, `arvv_pertence`, `arvv_libera` e `arvv_altura`. A implementação real em
  `TAVAR/` usa os mesmos 2 ponteiros com nomes por extenso (`prim_filho`, `prox_irmao`) e
  muda o comportamento de `TAV_insere` (busca o pai **pelo valor**, em vez de receber o
  ponteiro do pai já pronto como o Celes faz em `arvv_insere`).
- **CO (Cormen):** seção 10.4, "Representação de árvores enraizadas" — descreve a mesma
  ideia com o nome **"filho-esquerda, irmão-direita"** e prova por que ela usa `O(n)` de
  memória (contra `O(n²)` no pior caso de reservar um campo de ponteiro por filho possível).
- **SZ (Szwarcfiter):** seção 3.5, "Conversão de uma Floresta" — chega à mesma
  representação por outro caminho: convertendo qualquer árvore geral `T` (ou floresta) numa
  árvore binária `B(T)`, onde o filho esquerdo de `B(v)` é o primeiro filho de `v` em `T`, e
  o filho direito é o irmão seguinte de `v` em `T`. Também nota que o percurso **em-ordem**
  não faz sentido para árvores com número variável de filhos (só pré-ordem, pós-ordem e em
  largura generalizam).
- **KR:** não se aplica capítulo específico além do já citado em ponteiros/structs (1.1) —
  a struct `TAV` e as chamadas recursivas usam só `malloc`/`free`/`->` já vistos ali.

## Notas de estudo elaboradas

### A representação por 2 ponteiros

Em vez de reservar um campo de ponteiro por filho possível (o que exigiria saber um limite
máximo de filhos por nó, e desperdiçaria memória quando esse limite é grande mas pouco
usado), cada nó guarda só 2 ponteiros: `prim_filho` (o primeiro filho) e `prox_irmao` (o
próximo filho do mesmo pai). Um nó com N filhos vira uma lista encadeada de N nós, começando
em `prim_filho`. Isso garante `O(n)` de memória total, não importa quantos filhos cada nó
tenha (detalhe completo: [[Teoria - passo a passo/Teoria 01 - Motivação para árvores com número variável de filhos|Teoria 01]]
e [[Teoria - passo a passo/Teoria 02 - Definição por lista de filhos (prim_filho e prox_irmao)|Teoria 02]]).

### As 4 operações e suas complexidades

| Operação | Função | Complexidade | Observação |
|---|---|---|---|
| Criar nó | `TAV_cria` | O(1) | nasce como folha isolada (`prim_filho == prox_irmao == NULL`) |
| Buscar valor | `TAV_busca` | O(n) pior caso | sem propriedade de ordenação — não é O(log n) como numa BST (1.2) |
| Inserir | `TAV_insere` | O(n) (dominado pela busca do pai) | insere sempre no início da lista de filhos do pai — O(1) depois de achar o pai |
| Imprimir | `TAV_imprime` | O(n) | pré-ordem: mostra o nó, depois entra nos filhos |
| Liberar | `TAV_libera` | O(n) | pós-ordem: libera todos os filhos antes do próprio nó — guarda o próximo irmão **antes** de destruir o atual |

Detalhe passo a passo de cada uma: [[Teoria - passo a passo/Teoria 03 - Criação de nó e busca em profundidade|Teoria 03]],
[[Teoria - passo a passo/Teoria 04 - Inserção na árvore variável|Teoria 04]],
[[Teoria - passo a passo/Teoria 05 - Impressão e liberação em profundidade|Teoria 05]].

### Diferença de convenção: `TAV_insere` vs. `arvv_insere` do Celes

O Celes implementa `void arvv_insere (ArvVar* a, ArvVar* sa)`: recebe **dois ponteiros já
existentes** e só liga `sa` como novo primeiro filho de `a` — quem já tem o ponteiro do pai
na mão não precisa buscar nada. Já `TAV_insere(TAV* a, int pai, int info)` recebe o valor do
pai (não o ponteiro) e faz a busca internamente (`TAV_busca`) antes de criar e ligar o novo
nó — é essa busca embutida que torna `TAV_insere` O(n) em vez de O(1). As duas abordagens
resolvem o mesmo problema; a escolhida aqui é mais conveniente para o `main` interativo de
`TAVAR/teste_arv_gen.c`, que só tem os **valores** digitados pelo usuário, não ponteiros.

## Exemplos em C

Trecho principal, de `TAVAR/TAV.h` e `TAVAR/TAV.c` (código completo, compilado com
`gcc -Wall -Wextra -std=c11` sem erros):

```c
// TAV.h
typedef struct arv_var{
  int info;
  struct arv_var *prim_filho, *prox_irmao;
}TAV;

TAV* TAV_cria (int elem);
TAV* TAV_busca (TAV *a, int info);
void TAV_insere (TAV* a, int pai, int info);
void TAV_imprime (TAV *a);
void TAV_libera (TAV *a);
```

```c
// TAV.c — inserção: busca o pai pelo valor, encaixa o novo nó na frente da lista de filhos
void TAV_insere (TAV* a, int pai, int info){
  TAV *meu_pai = TAV_busca(a, pai);
  if(!meu_pai) return;              // pai não existe: no-op silencioso (ver Teoria 04)
  TAV *novo = TAV_cria(info);
  novo->prox_irmao = meu_pai->prim_filho;
  meu_pai->prim_filho = novo;
}
```

Código completo (as 5 funções + o `main` interativo) em `TAVAR/TAV.h`, `TAVAR/TAV.c` e
`TAVAR/teste_arv_gen.c`.

## Pontos de atenção / pegadinhas comuns de prova

- **Ordem de impressão dos filhos não é a ordem de inserção** — cada `TAV_insere` encaixa
  na frente da lista (`prim_filho`), então os filhos aparecem impressos na ordem **inversa**
  de quando foram inseridos.
- **`TAV_insere` com um `pai` inexistente não dá erro** — é um no-op silencioso
  (`if(!meu_pai) return;`), fácil de não perceber ao testar/depurar.
- **`TAV_libera` não pode ser escrito como um `for` simples igual ao `TAV_imprime`** — é
  preciso guardar `p->prox_irmao` numa variável **antes** de chamar `TAV_libera(p)`, porque
  essa chamada desaloca `p`; ler `p->prox_irmao` depois disso é acessar memória já liberada.
- **Esta árvore não é uma árvore de busca** — não existe propriedade de ordenação entre os
  filhos de um nó, então `TAV_busca` é O(n), não O(log n).

## Anotações pessoais

## Exercícios resolvidos
