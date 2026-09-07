# Conceitos — Tipos Abstratos de Dados (TAD)

## A ideia em uma frase

Um TAD descreve um tipo pela **finalidade** dele e pelas **operações** que oferece, sem
revelar como ele é implementado por dentro — quem usa só conhece o "o quê", nunca o "como".

## O conceito

"Abstrato" aqui quer dizer *esquecida a forma de implementação*. Um TAD é:

- um **tipo** novo (ex.: `Pilha`, `Lista`, `Conta`);
- mais um **conjunto de operações** sobre ele (ex.: `empilha`, `desempilha`, `topo`);
- com a **representação interna escondida**.

Em C isso se monta com [[../../4 PROGRAMAÇÃO COM MÓDULOS/Conceitos|módulos]]:

- o `.h` exporta só o **nome do tipo** e os **protótipos** — é a *interface*;
- o `.c` é o único arquivo que conhece os campos da `struct` — é a *implementação*.

Duas consequências que são o motivo de tudo isso existir:

1. **O cliente não acessa os campos.** Ele chama `pilha_topo(p)`, nunca `p->v[p->n-1]`.
2. **A implementação pode trocar inteira** (de vetor para lista encadeada, por exemplo) e
   nenhum código cliente muda, desde que a interface continue igual.

**Invariante:** cada TAD mantém regras internas sempre verdadeiras (ex.: numa pilha com
vetor, `0 <= n <= capacidade`). As operações são escritas para nunca quebrar o invariante;
por isso o cliente não pode mexer nos campos direto — ele poderia violá-lo.

**Convenção:** prefixe as funções com o nome do tipo (`pilha_`, `lista_`), porque C não
tem sobrecarga e dois TADs no mesmo programa teriam nomes colidindo.

## Exemplo passo a passo — um TAD `Conta` em 3 arquivos

**`conta.h` — a interface:**

```c
#ifndef CONTA_H
#define CONTA_H

typedef struct conta Conta;      // tipo opaco: campos não aparecem aqui

Conta *conta_cria(double saldo_inicial);
int    conta_saca(Conta *c, double valor);   // 1 = ok, 0 = saldo insuficiente
void   conta_deposita(Conta *c, double valor);
double conta_saldo(Conta *c);
void   conta_libera(Conta *c);

#endif
```

**`conta.c` — a implementação (a `struct` só existe aqui):**

```c
#include <stdlib.h>
#include "conta.h"

struct conta {
    double saldo;      // INVARIANTE: saldo nunca fica negativo
};

Conta *conta_cria(double saldo_inicial) {
    Conta *c = malloc(sizeof(Conta));
    if (c != NULL) c->saldo = (saldo_inicial > 0) ? saldo_inicial : 0;
    return c;
}

void conta_deposita(Conta *c, double valor) {
    if (valor > 0) c->saldo += valor;
}

int conta_saca(Conta *c, double valor) {
    if (valor <= 0 || valor > c->saldo) return 0;   // protege o invariante
    c->saldo -= valor;
    return 1;
}

double conta_saldo(Conta *c) { return c->saldo; }
void   conta_libera(Conta *c) { free(c); }
```

**`main.c` — o cliente:**

```c
#include <stdio.h>
#include "conta.h"

int main(void) {
    Conta *c = conta_cria(100.0);
    conta_deposita(c, 50.0);
    printf("saldo: %.2f\n", conta_saldo(c));       // 150.00

    if (!conta_saca(c, 500.0))
        printf("saque negado\n");                   // saldo insuficiente
    printf("saldo: %.2f\n", conta_saldo(c));       // 150.00

    // c->saldo = 1e9;  <- ERRO de compilação: struct conta é incompleta aqui
    conta_libera(c);
    return 0;
}
```

**Passo a passo:**

1. `conta_cria(100)` aloca a struct e garante saldo ≥ 0.
2. `conta_deposita(c, 50)` → saldo 150.
3. `conta_saca(c, 500)` vê `500 > 150`, devolve `0` sem alterar nada — o invariante
   "saldo ≥ 0" fica protegido.
4. O cliente **não consegue** fazer `c->saldo = ...` — o tipo é opaco. A única porta de
   entrada são as funções.

**O que observar:** troque o `double saldo` por um histórico de transações e recalcule o
saldo a cada consulta — `main.c` continua idêntico.

## Erros comuns / pegadinhas

- **Expor a `struct` completa no `.h`** — o cliente passa a depender dos campos, e você
  perde a liberdade de mudar a implementação.
- **Cliente acessando `p->campo`** — quebra o encapsulamento e pode violar o invariante.
- **Operações que não protegem o invariante** — ex.: `conta_saca` sem checar o saldo.
- **Esquecer a função de liberação** (`_libera`) — vazamento, já que o TAD costuma usar
  `malloc`.
- **Nomes de função sem prefixo** — colidem com os de outro TAD no mesmo programa.

## Resumo / checklist

- [ ] Sei definir TAD: tipo + operações + representação escondida
- [ ] Sei montar o par `.h` (interface, tipo opaco) / `.c` (implementação)
- [ ] Sei o que é um invariante e por que as operações o protegem
- [ ] Entendo por que o cliente não pode acessar os campos
- [ ] Uso prefixo de tipo nas funções
- [ ] Toda estrutura dos tópicos 7.2–7.7 segue este molde
