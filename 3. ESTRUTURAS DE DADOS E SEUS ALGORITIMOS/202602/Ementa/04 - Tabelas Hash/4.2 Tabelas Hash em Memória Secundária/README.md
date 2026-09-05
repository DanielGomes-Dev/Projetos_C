# 4.2 Tabelas Hash em Memória Secundária

## Objetivo de aprendizagem

- Entender por que hashing em disco precisa de uma estratégia diferente do hashing em memória principal (minimizar acessos a disco, não comparações).
- Dominar o funcionamento do hashing extensível (diretório + buckets, duplicação de diretório).
- Dominar o funcionamento do hashing linear (crescimento incremental sem diretório).
- Comparar os trade-offs entre os dois métodos.

## Roteiro de leitura

- **SZ (livro-base):** capítulo sobre tabelas de espalhamento, seção de memória secundária — única fonte dos 4 livros com cobertura direta de hashing extensível e linear. *(conferir página exata)*
- **CO (Cormen):** o CLRS cobre hashing em profundidade no cap. 11, mas com foco em memória principal — não trata hashing extensível/linear como tópico central. Pode ser consultado para relembrar os fundamentos de função hash e análise de colisão, mas não é referência para este subtópico específico.
- **CE (Celes):** não cobre hashing em memória secundária (o livro é focado em estruturas de memória principal). Não há capítulo de implementação de referência aqui.
- **KR:** não diretamente relevante — hashing em disco é mais um problema de projeto de estrutura de dados/sistemas que de sintaxe de C.

## Notas de estudo elaboradas

### Por que memória secundária muda o problema

Em memória principal, o custo dominante é o número de comparações/acessos a memória RAM. Em disco, cada acesso a um bloco custa ordens de magnitude mais (milissegundos vs nanossegundos) — o objetivo central passa a ser **minimizar o número de acessos a disco**, exatamente como no módulo de Árvores B (1.4). A ideia geral: usar a função hash para decidir em qual **bucket** (bloco de disco, capaz de armazenar vários registros) uma chave deve estar, e organizar o crescimento da tabela sem precisar reescrever todo o arquivo a cada inserção.

### Hashing extensível (extendible hashing)

Estrutura de duas camadas:
- Um **diretório** em memória principal, indexado pelos primeiros `d` bits do hash da chave (`d` = profundidade global).
- Um conjunto de **buckets** em disco, cada um com sua própria profundidade local `d_local ≤ d`.

Quando um bucket estoura (fica cheio na inserção):
1. Se `d_local` do bucket == `d` (profundidade global), o **diretório dobra de tamanho** (duplica todas as entradas), incrementando `d`.
2. O bucket cheio é dividido em dois, incrementando seu `d_local`; as entradas do diretório que apontavam para ele são redistribuídas entre os dois novos buckets conforme mais um bit do hash.

Vantagem: acesso a qualquer registro custa **no máximo 2 acessos a disco** (1 para o diretório, se ele não estiver em memória — geralmente está —, e 1 para o bucket). Desvantagem: o diretório pode crescer exponencialmente em cenários de distribuição ruim das chaves, e uma duplicação de diretório é uma operação relativamente cara (ainda que rara).

### Hashing linear (linear hashing)

Não usa diretório. Cresce **um bucket por vez**, em ordem previsível, usando um ponteiro de divisão (`split pointer`) que percorre os buckets sequencialmente. Usa duas funções hash de níveis consecutivos (`h_i` e `h_{i+1}`, tipicamente `h_i(k) = k mod (2^i · N)`), e mantém um contador de nível.

Quando qualquer bucket estoura (não necessariamente o que a chave está sendo inserida), o bucket apontado pelo ponteiro de divisão é dividido em dois usando `h_{i+1}`; o ponteiro avança. Quando o ponteiro percorre todos os buckets do nível atual, o nível incrementa e o ponteiro volta ao início.

Vantagem: sem diretório, sem duplicação abrupta de estrutura — crescimento suave e previsível, menor overhead de memória. Desvantagem: como a divisão nem sempre ocorre no bucket que estourou, pode ser necessário usar uma lista de overflow temporária para esse bucket até que ele seja alcançado pelo ponteiro de divisão — acesso pode custar mais de 1 bucket nesse ínterim.

### Comparação

| | Hashing extensível | Hashing linear |
|---|---|---|
| Estrutura auxiliar | Diretório (pode crescer exponencialmente) | Nenhuma (só ponteiro de divisão + nível) |
| Acessos a disco por busca | ≤ 2 (garantido) | Pode variar (overflow até o bucket ser dividido) |
| Crescimento | Duplicação abrupta do diretório quando necessário | Incremental, um bucket por vez |
| Complexidade de implementação | Maior (gerenciar diretório) | Menor |

### Exemplo passo a passo: crescimento do hashing extensível

Suponha buckets com capacidade **2 chaves**, e que já convertemos as chaves para seus bits de hash mais significativos (é só o que importa para decidir o bucket). Estado inicial: profundidade global `d = 2` → diretório com `2^2 = 4` entradas (00, 01, 10, 11), cada uma apontando pra um bucket vazio com profundidade local `d_local = 2`:

```
Diretório (d=2)      Buckets
00 ──┐
     ├──► Bucket A (d_local=2): [ ]
01 ──┘
10 ──┐
     ├──► Bucket B (d_local=2): [ ]
11 ──┘
```

(Aqui cada bucket já está associado a 2 entradas do diretório porque, ao inicializar com poucos buckets, é comum começar com `d_local < d` — vamos assumir isso pra tornar o exemplo didático.)

Inserindo uma chave cujo hash começa em `101...` (prefixo `10`): vai para o Bucket B. Bucket B agora tem 1 chave. Inserindo outra chave com prefixo `11`: também vai pro Bucket B (mesmo bucket, já que `d_local` do B é 2 mas ele está associado às entradas 10 e 11 igualmente nesse cenário simplificado — na prática real cada entrada aponta pro bucket certo por igualdade total dos `d_local` bits, então seria mais comum começar com `d_local = d` para todo bucket; manteremos o exemplo simples assumindo isso).

Simplificando para o caso mais didático (todo bucket com `d_local = d = 2` desde o início, um bucket por entrada):

```
00 ──► Bucket 00 (d_local=2): [ ]
01 ──► Bucket 01 (d_local=2): [ ]
10 ──► Bucket 10 (d_local=2): [ ]
11 ──► Bucket 11 (d_local=2): [ ]
```

Inserindo duas chaves com prefixo `10`: o Bucket `10` enche (capacidade 2) → `[chave_a, chave_b]`.

Inserindo uma terceira chave com prefixo `10`: o Bucket `10` **estoura**. Como `d_local` do bucket (2) == `d` do diretório (2), é preciso **duplicar o diretório** primeiro:

```
Diretório dobra: d = 3 → 8 entradas (000..111)
Cada entrada antiga vira duas nas novas (000 e 100 apontam pro que era "00", etc.)
```

Depois da duplicação, o bucket que estourou (agora endereçado por `100` e `101`, já que passamos a olhar 3 bits) é **dividido em dois** novos buckets com `d_local = 3`: um recebe as chaves cujo 3º bit é 0, outro as que têm 3º bit 1. As entradas `100` e `101` do diretório agora apontam para buckets diferentes; as demais entradas (`000`, `001`, `010`, `011`, `110`, `111`) continuam apontando para os buckets originais (que não mudaram, só passaram a ser referenciados por duas entradas cada, já que `d_local` deles continua 2 < novo `d` = 3).

Esse é o ponto central do método: **a duplicação do diretório é O(diretório atual)**, mas a divisão do bucket em si só mexe nas chaves daquele bucket — o resto da tabela nem é tocado.

## Exemplos em C

### Estruturas de dados: diretório + buckets

```c
#include <stdio.h>
#include <stdlib.h>

#define CAP_BUCKET 4  // quantas chaves cabem em um bucket (um "bloco de disco")

typedef struct {
    int chaves[CAP_BUCKET];
    int n;          // quantas chaves o bucket tem no momento
    int d_local;    // profundidade local desse bucket
} Bucket;

typedef struct {
    int d_global;     // profundidade global do diretório (diretório tem 2^d_global entradas)
    Bucket **buckets;  // vetor de ponteiros: diretório[i] aponta pro bucket responsável pela entrada i
} DiretorioHash;

// Extrai os d bits mais significativos do hash da chave, usados para indexar o diretório
int bits_hash(int chave, int d) {
    unsigned int h = (unsigned int) chave;  // hash simplificado: a própria chave
    return h & ((1 << d) - 1);  // pega os d bits menos significativos do hash (convenção deste exemplo)
}

DiretorioHash *diretorio_inicializa(int d_inicial) {
    DiretorioHash *dir = (DiretorioHash *) malloc(sizeof(DiretorioHash));
    int tamanho = 1 << d_inicial;  // 2^d_inicial
    int i;
    dir->d_global = d_inicial;
    dir->buckets = (Bucket **) malloc(tamanho * sizeof(Bucket *));
    for (i = 0; i < tamanho; i++) {
        dir->buckets[i] = (Bucket *) malloc(sizeof(Bucket));
        dir->buckets[i]->n = 0;
        dir->buckets[i]->d_local = d_inicial;
    }
    return dir;
}

// Busca: no máximo 1 acesso ao diretório (em memória) + 1 acesso ao bucket (em disco)
int bucket_busca(DiretorioHash *dir, int chave) {
    int indice = bits_hash(chave, dir->d_global);
    Bucket *b = dir->buckets[indice];
    int i;
    for (i = 0; i < b->n; i++)
        if (b->chaves[i] == chave) return 1;  // encontrada
    return 0;  // não encontrada
}

// Inserção simplificada: assume que há espaço (o split de bucket cheio,
// e a eventual duplicação do diretório quando d_local == d_global,
// seguem a lógica descrita no exemplo passo a passo acima — a reestruturação
// completa envolve realocar o vetor `buckets`, copiar ponteiros duplicados
// e redistribuir as chaves do bucket dividido conforme mais um bit do hash).
int bucket_insere(DiretorioHash *dir, int chave) {
    int indice = bits_hash(chave, dir->d_global);
    Bucket *b = dir->buckets[indice];
    if (b->n < CAP_BUCKET) {
        b->chaves[b->n] = chave;
        b->n++;
        return 1;
    }
    return 0;  // bucket cheio -> aqui entraria a lógica de split/duplicação de diretório
}
```

A função `bits_hash` é o coração do método: ela decide, olhando só os `d_global` bits mais significativos (ou menos significativos, dependendo da convenção adotada) do hash, qual entrada do diretório — e portanto qual bucket — é responsável por aquela chave. Quando `d_global` cresce (duplicação), essa mesma função passa a olhar um bit a mais, o que naturalmente refina a distribuição sem precisar recalcular o hash de cada chave já armazenada.

## Pontos de atenção / pegadinhas comuns de prova

- Hashing extensível cresce o **diretório**; hashing linear cresce **buckets diretamente**, sem diretório — não confundir qual estrutura duplica em qual método.
- Profundidade local (`d_local`) de um bucket pode ser menor que a profundidade global (`d`) do diretório — isso é o que permite que múltiplas entradas do diretório apontem pro mesmo bucket.
- No hashing linear, o bucket que estoura **não é necessariamente** o bucket dividido nesse momento — quem divide é sempre o bucket apontado pelo ponteiro de divisão.
- O objetivo de otimização aqui é **acessos a disco**, não comparações em memória — é o mesmo princípio das árvores B, vale revisar os dois módulos em conjunto.

## Anotações pessoais

## Exercícios resolvidos
