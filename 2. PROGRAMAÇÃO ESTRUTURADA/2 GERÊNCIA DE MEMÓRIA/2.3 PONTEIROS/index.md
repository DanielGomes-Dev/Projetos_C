# 2.3 Ponteiros

## Resumo
Um ponteiro guarda o endereço de memória de outra variável. Operadores centrais: `&` (endereço de) e `*` (desreferenciação/valor apontado). Relação estreita e frequentemente confusa entre ponteiros e vetores (o nome de um vetor decai para um ponteiro ao seu primeiro elemento); aritmética de ponteiros (`p+1` avança `sizeof(tipo)` bytes); ponteiros para `struct` (`->`); ponteiros para ponteiros; ponteiro `NULL`.

## Onde estudar
- **K&R** — cap. 5 (Apontadores e Arranjos), completo — o capítulo mais denso e importante do livro para este bloco.
- **Celes** — fundamentos (`&`/`*`) no cap. 4 ("Funções"), seção "Ponteiro de variáveis"; relação com vetores no cap. 5 ("Vetores e alocação dinâmica").

## Checklist
- [ ] Diferença entre `&x` e `*p`
- [ ] Relação ponteiro ↔ vetor (`v[i]` ≡ `*(v+i)`)
- [ ] Aritmética de ponteiros
- [ ] Ponteiro para `struct` e o operador `->`
- [ ] Ponteiro `NULL` e por que checar antes de desreferenciar

## Anotações
