# Q2 — Buscar cliente por CPF sem carregar o arquivo inteiro

> **Origem:** `lista06-EDA.pdf`, questão 2 · **Código resolvido:** [[../Q2/claude/main.c]]
> **Antes disto, veja:** [[Q1 - Produto cartesiano de dois arquivos binários]].

## 1. O que o exercício pede

> Receba um arquivo binário de clientes e, **sem ler todos os registros para memória**,
> permita consultar os dados de um cliente pelo CPF. Registro: `nome (char[40])`,
> `CPF (char[11])`, `conta_corrente (int)`, `agencia (int)`, `saldo (float)`.

## 2. A ideia geral

"Sem ler todos para memória" não significa "sem ler o arquivo todo do disco" — significa
nunca ter **mais de 1 registro por vez na RAM**. A estratégia é busca sequencial: ler um
registro, comparar o CPF, e só continuar se não bateu — parando assim que achar (ou ao
esgotar o arquivo).

## 3. Resolução passo a passo

### Passo 1 — o struct do registro

```c
typedef struct {
    char  nome[40];
    char  cpf[11];
    int   conta_corrente;
    int   agencia;
    float saldo;
} Cliente;
```

Struct de tamanho **fixo** (mesma ideia da árvore B+ e do heap: registros de tamanho
conhecido permitem calcular posições por aritmética — ver 3.1, Teoria 03).

### Passo 2 — ler um registro por vez, comparando

```c
Cliente c;
while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
    if (memcmp(c.cpf, cpf_alvo, TAM_CPF) == 0) {
        // achou: imprime e retorna
    }
}
// terminou sem achar
```

> 📖 **Por que `memcmp`, não `strcmp`:** `c.cpf` tem exatamente 11 bytes e **não há garantia
> de `'\0'`** no final (o enunciado descreve 11 dígitos, sem terminador). `strcmp` pararia
> na primeira ocorrência de um byte `0`, que pode nem existir aí — `memcmp` compara
> exatamente os 11 bytes, sem depender de terminador.

**Trace**, buscando CPF `"33333333333"` num arquivo com 4 clientes (CPFs terminados em
`1,2,3,4`):

| Registro lido (posição) | CPF comparado | Igual ao alvo? | Ação |
|---|---|---|---|
| 0 | `...1` | não | continua |
| 1 | `...2` | não | continua |
| 2 | `...3` | **sim** | imprime dados, retorna |

Nunca chega a ler o registro 3 — parou assim que achou.

## 4. Resultado final

```
CPF 33333333333 encontrado (registro 2):
   nome           : Carla Dias
   conta_corrente : 1003
   agencia        : 77
   saldo          : 9800.75
```

**Conferindo:** buscar um CPF inexistente (ex.: `"99999999999"`) deve percorrer **todos** os
registros e terminar com "não encontrado" — o pior caso da busca sequencial, O(N).

## 5. Habilidades necessárias

- [ ] `fread` de um struct inteiro de uma vez (`sizeof(Cliente)` como tamanho do registro).
- [ ] `memcmp` vs. `strcmp` — quando o dado não tem terminador de string garantido.

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — CPF é o primeiro registro

Busca encontra na primeira iteração — só 1 leitura, melhor caso.

### Aquecimento 2 — CPF não existe, arquivo com 1 registro

1 leitura, não bate, `fread` na próxima chamada retorna 0 (fim do arquivo) — `while` para,
imprime "não encontrado".

---

**Próximo:** [[Q3 - Gerar arquivo de índices ordenado por saldo]].
