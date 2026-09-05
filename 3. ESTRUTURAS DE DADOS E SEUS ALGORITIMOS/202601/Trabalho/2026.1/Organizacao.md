Esse é um trabalho clássico, denso e muito interessante de **Estruturas de Dados** (provavelmente da UFF, dado o e-mail do professor Rosseti). Ele exige não apenas a implementação de uma estrutura de dados avançada, mas também a manipulação rigorosa de arquivos em disco (memória secundária) e a elaboração de algoritmos de busca complexos que lembram consultas de um banco de dados relacional.

Para ajudar você e seu grupo a se organizarem, destrinchei o escopo do projeto em blocos lógicos.

---

## 1. O Coração do Projeto: A Árvore em Memória Secundária

A exigência mais crítica e difícil do trabalho é a forma como os dados devem ser armazenados. Você não pode guardar tudo na memória RAM; deve simular o comportamento de um SGBD (Sistema Gerenciador de Banco de Dados).

* **A Escolha da Árvore:** O professor dá a opção entre Árvore B ou Árvore B+. **Recomendação:** Escolha a **Árvore B+**. Em uma B+, todos os dados reais ficam nas folhas e os nós internos servem apenas como "guias" de roteamento. Isso facilita enormemente a implementação das restrições exigidas e acelera consultas em lote (como as buscas por década).
* **A Restrição dos Arquivos:**
* Você terá **1 arquivo binário de índice**: Este arquivo guardará a raiz e os nós internos da árvore.
* **Múltiplos arquivos binários para as folhas**: Cada nó folha da árvore deve ser salvo em um arquivo `.bin` (ou similar) separado no disco. Se um nó folha sofrer *split* (divisão por estar cheio), um novo arquivo binário deverá ser criado no disco.


* **O Grau Mínimo ($t$):** A árvore deve ser parametrizável. O usuário define o grau mínimo $t$, o que significa que cada nó interno terá entre $t$ e $2t$ filhos, e as folhas terão uma capacidade proporcional.

## 2. Modelagem dos Dados (O Desafio da "Árvore Única")

O enunciado pede **"uma única árvore B ou B+"**. Como você precisa armazenar filmes, pessoas (atores, diretores, produtores, escritores) e as relações entre eles na mesma estrutura, você precisará de uma modelagem inteligente:

* **Registro Genérico:** Cada registro na árvore precisa de um identificador (chave) e um "tipo" (ex: `1` para Filme, `2` para Pessoa, `3` para Relacionamento).
* **A Chave de Busca:** Como o menu exige buscar pelo nome (Operação 4), a chave primária de ordenação da árvore provavelmente será uma *string* (o nome da pessoa ou título do filme) ou um hash desse nome.
* **Estrutura do Nó:** Dentro da folha (o arquivo binário), o registro de um "Ator" pode conter: Nome, Ano de Nascimento e uma lista de IDs de Filmes (ou ponteiros para os registros de relacionamento).

## 3. Classificação das Consultas (Questões de "a" a "t")

O volume de consultas exigidas é enorme. Para não se perder, agrupe-as na hora de programar. Elas se dividem basicamente nestas categorias:

* **Cruzamento de Relacionamentos (Grafo Bipartido):** Consultas `(a)`, `(b)`, `(c)` e `(q)`. Exigem que você busque uma pessoa, veja em quais filmes ela trabalhou e, em seguida, busque quem mais estava naqueles mesmos filmes.
* **Estatísticas de Volume (Top/Bottom):** Consultas `(f)`, `(g)`, `(h)`, `(i)`, `(j)` e `(k)`. Você precisará varrer todas as folhas da árvore B+ (sequencialmente) contando o tamanho das listas de filmes de cada profissional para descobrir quem trabalhou mais ou menos.
* **Filtro Temporal (Por Década ou Ano):** Consultas `(d)`, `(e)`, `(l)`, `(n)` e `(t)`. Exigem um filtro no ano de lançamento do filme ou no ano de nascimento da pessoa. Exemplo: Para a "década de 90", você só contabiliza relacionamentos onde `filme.ano >= 1990` e `filme.ano <= 1999`.
* **Sobreposição de Papéis (O Faz-Tudo):** Consultas `(o)`, `(p)`, `(r)` e `(s)`. Simples de resolver se o cadastro da pessoa tiver *flags* booleanas (`is_actor`, `is_director`, etc.) ou se houver registros de relacionamento para cada cargo.
* **Metadados de Filmes:** Consulta `(m)`. Filmes que são continuações (provavelmente mapeados no arquivo de relacionamentos).

## 4. O Menu e as Operações Base

Antes de fazer as consultas complexas, o sistema deve ser capaz de existir e se automanter. Suas prioridades de desenvolvimento devem ser na seguinte ordem:

1. **Operação (1):** Iniciar o sistema e ler/definir o grau $t$.
2. **Operação (2):** Algoritmo de Inserção. Lê os arquivos brutos (txt/csv) fornecidos pelo professor e insere um a um na árvore. Precisa tratar o limite de disco e fazer *split* das folhas gerando novos arquivos.
3. **Operação (5):** Imprimir a árvore. **Faça isso o quanto antes.** Você só consegue debugar a árvore se conseguir visualizar a estrutura dela.
4. **Operação (4):** Busca simples (achar um nó no disco a partir da raiz).
5. **Operação (3):** Remoção. (Geralmente a parte mais difícil da Árvore B/B+, por causa dos *merges* e redistribuições. Deixe por último nas operações base).

## Dicas Práticas de Implementação

* **Linguagem C/C++:** É o padrão para essa disciplina. Use `fopen`, `fread`, `fwrite`, `fseek` e `ftell` pesado.
* **Evite o "Ponteiro C":** Na memória secundária, ponteiros tradicionais (`*node`) não existem. Os "ponteiros" para os filhos em um nó de Árvore B no disco são, na verdade, **nomes de arquivos** (ex: `folha_12.bin`) ou **offsets** (bytes de deslocamento no arquivo de índice).
* **Abstraia o I/O:** Crie funções como `le_no_do_disco(id)` e `salva_no_no_disco(no, id)`. Deixe a lógica da árvore trabalhar com os nós em RAM, usando essas funções para puxar e empurrar do disco apenas quando necessário.
* **Trabalho em Equipe:** Dividam as tarefas. Um foca puramente nas operações da Árvore B+ (inserir/dividir/salvar), enquanto o outro escreve a lógica de parseamento dos arquivos texto iniciais e o "motor" das consultas (as regras de negócio para responder de *a* até *t*).

Dada a data de entrega (17/06), vocês precisam começar a implementar a estrutura do nó no disco e a lógica de *split* imediatamente, pois as consultas exigirão tempo para testes. Boa sorte!