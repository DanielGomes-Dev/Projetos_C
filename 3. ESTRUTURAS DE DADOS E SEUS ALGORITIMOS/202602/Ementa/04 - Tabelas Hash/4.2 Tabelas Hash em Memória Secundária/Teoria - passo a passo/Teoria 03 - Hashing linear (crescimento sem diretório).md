# Teoria 03 — Hashing linear (crescimento sem diretório)

> **Onde isto entra:** segundo método pro mesmo problema da Teoria 01 — resolve a mesma
> necessidade (crescer a estrutura sem reindexar tudo), mas **sem** a estrutura auxiliar de
> diretório da Teoria 02.
> **Antes:** [[Teoria 02 - Hashing extensível (diretório e buckets)]].
> **Fonte:** SZ (Szwarcfiter) é o livro-base — **PDF não pôde ser aberto nesta máquina**
> (mesma limitação da Teoria 02). Exemplo numérico abaixo construído para esta explicação,
> fiel ao mecanismo descrito no `README.md` deste subtópico.

## 1. A ideia em uma frase

Em vez de um diretório que aponta pro bucket certo, hashing linear cresce **um bucket por
vez, em ordem previsível** — usando um "ponteiro de divisão" que percorre os buckets
sequencialmente, e permitindo que um bucket cheio guarde temporariamente o excesso numa
lista extra (overflow), até chegar sua vez de dividir.

## 2. Por que um método sem diretório

O diretório da Teoria 02 tem uma desvantagem: em cenários ruins, ele pode crescer
**exponencialmente** (dobra de tamanho inteira, mesmo que só um bucket tenha estourado).
Hashing linear elimina essa estrutura auxiliar por completo — o preço é que a divisão de
buckets acontece numa ordem fixa e previsível, **não necessariamente** no bucket que
acabou de estourar.

## 3. Vocabulário novo — lido devagar

> 📖 **Duas funções hash de "nível" consecutivo:** `h_i(k) = k mod (2^i · N₀)`, onde `N₀` é
> o número de buckets inicial e `i` é o **nível atual**. Ao passar do nível `i` pro `i+1`, o
> número de posições possíveis **dobra** (`2^i · N₀` → `2^(i+1) · N₀`), exatamente como o
> diretório dobrava na Teoria 02 — só que aqui isso não exige uma estrutura à parte, é só
> trocar qual função hash está em uso.
>
> **Ponteiro de divisão (`p`)** — aponta para o **próximo bucket a ser dividido**, entre `0`
> e o número de buckets do nível atual. Cresce de 1 em 1, e volta a 0 quando o nível muda.

## 4. Conferindo com um exemplo concreto, passo a passo

`N₀ = 2` buckets iniciais, capacidade 2 chaves cada, nível `i = 0` (então `h_0(k) = k mod
2`), ponteiro de divisão `p = 0`:

```
Bucket 0 (h=0): [ ]
Bucket 1 (h=1): [ ]
p = 0   (próximo a dividir: Bucket 0)
```

Inserindo, nesta ordem, as chaves `4, 6, 3, 8`:

> **Passo 1 — insere `4`:** `4 mod 2 = 0` → Bucket 0. `Bucket 0 = [4]`.
>
> **Passo 2 — insere `6`:** `6 mod 2 = 0` → Bucket 0. `Bucket 0 = [4, 6]` — cheio, sem
> overflow ainda.
>
> **Passo 3 — insere `3`:** `3 mod 2 = 1` → Bucket 1. `Bucket 1 = [3]`.
>
> **Passo 4 — insere `8`:** `8 mod 2 = 0` → Bucket 0, que **já está cheio**. **Overflow!**

### A divisão — não necessariamente no bucket que estourou

Diferente da Teoria 02, hashing linear **não** divide imediatamente o Bucket 0 (quem
estourou). Em vez disso, `8` entra numa **lista de overflow** temporária ligada ao Bucket 0:

```
Bucket 0: [4, 6] → overflow: [8]
```

E o algoritmo divide o bucket **apontado por `p`** — que, neste momento, também é o Bucket
0 (`p = 0`). Usando a próxima função hash do nível seguinte, `h_1(k) = k mod (2·2) = k mod
4`, redistribui-se **todo o conteúdo de Bucket 0 + sua lista de overflow** (`4, 6, 8`) entre
o Bucket 0 antigo e um **novo** Bucket 2 (criado agora):

```
h_1(4) = 4 mod 4 = 0 → fica no Bucket 0
h_1(6) = 6 mod 4 = 2 → vai pro novo Bucket 2
h_1(8) = 8 mod 4 = 0 → fica no Bucket 0
```

```
Bucket 0: [4, 8]
Bucket 1: [3]           (não foi tocado)
Bucket 2: [6]           (novo, criado pela divisão)
p = 1   (avança para o próximo bucket do nível atual)
```

> **Se o ponteiro `p` tivesse percorrido todos os buckets do nível 0** (aqui, só faltaria
> `p=1`), o nível incrementaria (`i` vira 1) e `p` voltaria a `0` — recomeçando o ciclo com
> `h_1` valendo agora como a função "atual", e uma nova `h_2` esperando o próximo ciclo.

## 5. 📌 O que você está REALMENTE fazendo

| O passo mecânico | O que ele realmente é |
|---|---|
| lista de overflow temporária no bucket que estourou | absorvo o excesso sem precisar dividir **imediatamente** o bucket certo — aceito um acesso extra a disco por um tempo, em troca de crescimento previsível |
| dividir sempre o bucket apontado por `p`, não o que estourou | mantenho uma ordem fixa e simples de crescimento — sem precisar de estrutura auxiliar pra "decidir" quem divide |
| usar `h_i` e `h_{i+1}` (nível atual e seguinte) | permito que a tabela cresça gradualmente, um bucket de cada vez, sem duplicar tudo de uma vez como o diretório fazia |

## 6. Letra miúda: o preço de não ter diretório

Enquanto o bucket que estourou (aqui, Bucket 0) **ainda não foi alcançado** pelo ponteiro de
divisão, uma busca por uma chave que caiu na lista de overflow pode custar **mais de 1**
acesso a disco (o bucket principal + a lista de overflow). Isso é o trade-off central:
hashing linear tem estrutura mais simples e crescimento mais suave, mas **não garante** o
"no máximo 2 acessos" que hashing extensível garante — pode variar, dependendo de quão perto
o ponteiro de divisão está de alcançar o bucket problemático.

## 7. Exercícios de fixação

1. No estado final da seção 4 (`p = 1`), para qual bucket vai uma nova chave `5`
   (`h_1(5) = 5 mod 4 = 1`)?
2. Se o Bucket 1 agora estourasse, ele seria dividido imediatamente? Por quê (ou por que
   não)?
3. Depois que `p` percorrer também o Bucket 1 (dividindo-o, se necessário) e não sobrar
   mais nenhum bucket do nível 0, o que acontece com `i` e `p`?
4. Compare: no hashing extensível (Teoria 02), o overflow de um bucket sempre dispara sua
   divisão imediata. Aqui, isso pode não acontecer. Qual é a vantagem prática de aceitar
   esse atraso?

### Gabarito

1. `h_1(5) = 1` → Bucket 1 (`[3, 5]`).
2. Sim — porque `p = 1` aponta exatamente pro Bucket 1 neste momento; ele é o "próximo da
   fila" a ser dividido, então um overflow nele coincide com o bucket que já seria dividido
   de qualquer forma.
3. `i` incrementa (nível 0 → 1) e `p` volta a `0` — reinicia o ciclo de divisão no nível
   seguinte, agora usando `h_1` como função "corrente" e `h_2` como a "próxima".
4. A vantagem é **não precisar de uma estrutura auxiliar** (o diretório) que poderia crescer
   exponencialmente em cenários ruins — o custo é aceitar que, por um tempo limitado, um
   bucket que estourou pode custar mais de 1 acesso (via sua lista de overflow) até que o
   ponteiro de divisão o alcance na ordem natural.

## Resumo

- Hashing linear cresce um bucket por vez, numa ordem fixa (`p`, o ponteiro de divisão),
  sem diretório auxiliar.
- Overflow não dispara divisão imediata do bucket afetado — usa-se uma lista de overflow
  temporária, e quem divide é sempre o bucket apontado por `p`.
- Trade-off central vs. hashing extensível (Teoria 02): estrutura mais simples e
  crescimento mais suave, mas sem garantia fixa de "no máximo 2 acessos" por busca.

---

Isso fecha a teoria de 4.2 e do módulo 04 inteiro. Próximo módulo da ementa:
[[../../../05 - Árvore B e B+/README|05 - Árvore B e B+]].
