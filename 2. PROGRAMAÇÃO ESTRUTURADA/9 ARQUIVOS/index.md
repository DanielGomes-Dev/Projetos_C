# 9. Arquivos

## Resumo
Persistência de dados em disco via `stdio.h`: abrir (`fopen`, com modos `"r"`, `"w"`, `"a"`, `"r+"` etc.), ler/escrever (`fscanf`/`fprintf` para texto formatado, `fread`/`fwrite` para binário, `fgets`/`fputs` para linhas), reposicionar (`fseek`/`rewind`/`ftell`) e fechar (`fclose` — essencial para garantir que o buffer seja gravado em disco). Distinção central: **arquivo texto** (portável, legível, cada valor precisa ser formatado/parseado) vs. **arquivo binário** (grava a representação em memória diretamente, mais rápido e compacto, mas não portável entre arquiteturas nem legível por humanos).

## Onde estudar
- **Celes** — cap. 15 ("Arquivos"), capítulo dedicado — mais completo que o K&R neste ponto: cobre modo texto, modo binário (`fread`/`fwrite`) **e** acesso aleatório (`fseek`), com exemplos completos (contar linhas, converter para maiúsculas, salvar/carregar vetor de structs).
- **K&R** — cap. 7 (Entrada e Saída), seção 7.5 (Acesso a Arquivos) em diante (7.6 Tratamento de Erros, 7.7 Argumentos de Linha de Comando).
- **K&R** — cap. 8 (Interface com o Sistema UNIX) para o nível mais baixo (`open`/`read`/`write`/`close`), se o curso for além da `stdio.h` padrão.

## Checklist
- [ ] Abrir/fechar arquivo corretamente e checar se `fopen` retornou `NULL`
- [ ] Diferença entre modos de abertura (`"r"`, `"w"`, `"a"`, `"r+"`...)
- [ ] Ler/escrever em modo texto vs. binário (`fscanf`/`fprintf` vs. `fread`/`fwrite`)
- [ ] Reposicionamento com `fseek`/`ftell`/`rewind`

## Anotações
