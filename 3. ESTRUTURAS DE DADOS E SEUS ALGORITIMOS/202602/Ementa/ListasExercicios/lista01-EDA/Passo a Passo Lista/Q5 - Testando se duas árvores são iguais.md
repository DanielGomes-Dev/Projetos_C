# Q5 — Testando se duas árvores são iguais

> **Origem:** `lista01-EDA.pdf`, item (Q5) · **Código resolvido:** [[../Q5/claude/main.c]]
> **Antes disto, veja:** [[../Q1/claude/main.c|Q1 - Cópia de uma árvore]] (mesma forma de recursão, aqui comparando em vez de construindo)

## 1. O que o exercício pede

> Uma função que, dadas duas árvores, testa se são iguais: `int igual (TAB* a1, TAB* a2);`
> Retorna 1 se são iguais, 0 caso contrário.

"Iguais" aqui significa **mesma forma e mesmos valores nas mesmas posições** — não só "têm
os mesmos números em algum lugar".

## 2. A ideia geral

Duas árvores são iguais se: (a) as duas são vazias, **ou** (b) as duas têm raiz com o
**mesmo valor**, **e** as subárvores esquerdas são iguais entre si, **e** as subárvores
direitas são iguais entre si. É uma comparação que anda **em paralelo** pelas duas árvores,
node a nó.

## 3. Resolução passo a passo

### Passo 1 — os casos de parada

```c
int igual(TAB *a1, TAB *a2) {
    if (!a1 && !a2)
        return 1;
    if (!a1 || !a2)
        return 0;
```

> 📖 **Lendo devagar:**
> 1. `!a1 && !a2` — **as duas** são vazias ao mesmo tempo → iguais (caso base positivo).
> 2. `!a1 || !a2` — **só uma** é vazia (se chegou aqui, a primeira condição já falhou, então
>    não podem ser as duas vazias) → uma tem nó e a outra não, formas diferentes → não são
>    iguais.
> 3. Repare a ordem: testar `!a1 && !a2` **antes** de `!a1 || !a2` é essencial — se
>    trocasse a ordem, `!a1 || !a2` seria verdadeiro também quando as duas são vazias,
>    dando o resultado errado (`0` em vez de `1`).

### Passo 2 — o caso recursivo

```c
    return a1->info == a2->info
        && igual(a1->esq, a2->esq)
        && igual(a1->dir, a2->dir);
}
```

Se chegou aqui, **nenhuma** das duas é `NULL` — dá pra acessar `a1->info` e `a2->info` com
segurança. A comparação só é verdadeira se as três condições (valor igual, subárvore
esquerda igual, subárvore direita igual) forem todas verdadeiras — o `&&` do C já para de
avaliar (*short-circuit*) assim que uma condição falha, então uma diferença é detectada o
mais cedo possível.

### Passo 3 — conferindo com os três testes do `main`

Árvore-modelo (variando só a raiz `r`):
```
        r
       / \
      2   3
     /     \
    1       4
```

| Chamada | O que muda | Resultado |
|---|---|---|
| `igual(a, b)` | `a` e `b` são a mesma árvore (`r=10` nas duas) | `1` — mesma forma, mesmos valores |
| `igual(a, c)` | `c` tem `r=99` em vez de `10` | `0` — falha em `a1->info == a2->info` já na raiz |
| `igual(a, d)` | `d` é só um nó `10`, sem filhos | `0` — falha em `!a1 || !a2` ao comparar `a->esq` (existe) com `d->esq` (`NULL`) |

## 4. Resultado final

`igual(a,b)=1`, `igual(a,c)=0`, `igual(a,d)=0` — os três casos batem com o esperado.

**Conferindo:** troque `igual(a1,a2)` por `igual(a2,a1)` (inverta a ordem dos argumentos) —
o resultado deveria ser o mesmo nos três casos, porque "ser igual" é uma relação simétrica.

## 5. Habilidades necessárias

- [ ] Recursão que compara duas estruturas em paralelo (não só percorre uma) → [[../../../../01 - Árvores/1.1 Árvores Binárias/Teoria - passo a passo/Teoria 04 - Percursos em profundidade (pré-ordem, em-ordem, pós-ordem)|1.1 Teoria 04]]
- [ ] Curto-circuito de `&&`/`||` em C → `KR`, cap. 2.

## 6. Exemplos mais simples (aquecimento)

### Aquecimento 1 — duas árvores vazias

`igual(NULL, NULL)`: cai direto em `!a1 && !a2` → `1`.

### Aquecimento 2 — uma folha contra uma árvore vazia

`igual(TAB_cria(5,NULL,NULL), NULL)`: `!a1` é falso (a1 existe), `!a2` é verdadeiro → a
primeira condição (`!a1 && !a2`) é falsa; a segunda (`!a1 || !a2`) é verdadeira (`!a2`) →
retorna `0`.
