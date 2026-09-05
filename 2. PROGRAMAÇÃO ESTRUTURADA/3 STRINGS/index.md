# 3. Strings

## Resumo
Em C, uma string é um vetor de `char` terminado pelo caractere nulo `'\0'` — não existe tipo string nativo. Cobre: literais de string, declaração (`char s[]` vs. `char *s`), leitura/escrita (`scanf("%s")`, `fgets`, `puts`), e as funções de `string.h`: `strlen`, `strcpy`/`strncpy`, `strcat`, `strcmp`, `strchr`, `strstr`. Armadilha central: `strcpy`/`strcat` não checam limites do buffer de destino (risco de buffer overflow).

## Onde estudar
- **K&R** — cap. 5, seção 5.5 (Arranjos de Caracteres) e Apêndice B, seção B.3 (Funções de String).
- **Celes** — cap. 7 ("Cadeias de caracteres"), capítulo dedicado — reimplementa `strlen`/`strcpy`/`strcat`/`strcmp` (iterativa e recursivamente) antes de recomendar usar as de `string.h`.

## Checklist
- [ ] String = vetor de `char` + `'\0'`
- [ ] `char s[]` (aloca) vs. `char *s = "..."` (aponta para literal, não deve ser modificado)
- [ ] Principais funções de `string.h` e suas assinaturas
- [ ] Risco de overflow com `strcpy`/`strcat`/`gets`

## Anotações
