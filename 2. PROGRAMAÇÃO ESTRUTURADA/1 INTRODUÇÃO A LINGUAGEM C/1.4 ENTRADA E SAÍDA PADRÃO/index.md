# 1.4 Entrada e Saída Padrão

## Resumo
Funções de I/O da biblioteca padrão `stdio.h`: `printf`/`scanf` (formatadas, com especificadores `%d %f %c %s` etc.), `getchar`/`putchar` (caractere a caractere), `gets`/`fgets` e `puts` (linha a linha). Cuidado recorrente: `scanf("%d", &x)` exige o `&`; misturar `scanf("%d")` com leitura de string/char deixa `\n` no buffer.

Guia completo de referência (tabelas de especificadores, `\n` residual, `%[...]`, `fgets`+`sscanf`, exemplos): **[[Guia - scanf e printf]]**.

## Onde estudar
- **Celes** — Cap. 2 ("Expressões"), seção "Entrada e saída básicas" — introduz `printf`/`scanf` de forma direta, com o exemplo de conversão de altura (metros → pés/polegadas) como primeiro programa completo do livro que usa as duas funções juntas.
- **K&R** — cap. 7 (Entrada e Saída), seções 7.1–7.4; cap. 1, seção 1.5 (Entrada e Saída de Caracteres) para a introdução via `getchar`/`putchar`.

## Checklist
- [ ] Especificadores de formato de `printf`/`scanf` (int, unsigned, float vs. double, char, string, hex/octal)
- [ ] Diferença `getchar`/`putchar` vs. `scanf`/`printf`
- [ ] Por que `scanf` exige `&` (endereço) e `printf` não
- [ ] Problema do `\n` residual no buffer de entrada — e as 3 formas de resolver
- [ ] Uso do valor de retorno de `scanf` para validar entrada
- [ ] `%[...]` para ler texto com espaços (linha inteira via `scanf`)
- [ ] `fgets` como alternativa segura a `gets` (e a `%s` sem limite de largura)

## Anotações
- `%s` em `scanf` **não tem limite de tamanho por padrão** — sempre usar `%Ns` (ex. `%49s` para um `char buf[50]`), do contrário é um buffer overflow clássico (a mesma classe de bug do `gets`, que foi removida do C11).
- `scanf("%f", &x)` e `scanf("%lf", &x)` **não são intercambiáveis**: `float` exige `%f`, `double` exige `%lf`. Em `printf`, ao contrário, `%f` serve para os dois (o `float` é promovido a `double` ao ser passado como argumento variádico).
- Regra prática para o `\n` residual: sempre que um `%c` (ou `%[...]`) vier **depois** de um `%d`/`%f`/`%u` no mesmo programa, colocar um espaço antes do `%c` no formato (`" %c"`) resolve o problema na maioria dos casos.
