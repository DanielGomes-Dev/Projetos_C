Para estruturar o desenvolvimento desse projeto de EDA de forma organizada e sem pular etapas, dividi o trabalho em **7 fases lógicas**. Como o prazo final de entrega é dia **17/06/2026** , seguir esse passo a passo ajudará o seu grupo a distribuir as tarefas e garantir que os requisitos de arquivos binários sejam cumpridos.

---

## 🛠️ Fase 1: Modelagem e Arquitetura de Dados (No Papel)

Antes de escrever qualquer linha de código, vocês precisam definir o tamanho fixo dos registros para manipulação em disco.

* **Tarefa 1.1:** Definir a estrutura `RegistroPessoa`, `RegistroFilme` e `RegistroRelacionamento` com strings de tamanho fixo (`char[]`), garantindo que possam ser gravadas e lidas diretamente com `fwrite` e `fread`.

* **Tarefa 1.2:** Projetar a estrutura do **Nó Interno** da Árvore B+ (chaves de busca em string e *offsets* de arquivo para os filhos).

* **Tarefa 1.3:** Projetar a estrutura do **Nó Folha**, incluindo o array de dados (chaves + ID da entidade), tipo ('P' ou 'F') e os inteiros para encadeamento (`proxima_folha`, `folha_anterior`).



---

## 📥 Fase 2: Parser dos Arquivos de Entrada e Geração dos Dados

O programa precisa transformar os arquivos de texto em arquivos binários estruturados.

* 
**Tarefa 2.1:** Criar um módulo para ler `Nodes.txt` linha por linha. Tratar as quebras de linha e identificar se o registro é *Movie* ou *Person*.


* **Tarefa 2.2:** Salvar esses dados em dois arquivos de registros binários sequenciais: `pessoas.dat` e `filmes.dat`. Ao salvar, gere um ID sequencial único para cada um (ex: Pessoa 1, Pessoa 2...).
* 
**Tarefa 2.3:** Criar o parser para o `Relationships.txt`. Como ele usa nomes para associar as pessoas aos filmes , crie um arquivo binário temporário `relacoes_bruto.dat` armazenando os nomes de texto e os papéis.



---

## 🌲 Fase 3: O Mecanismo da Árvore B+ em Disco

Esta é a parte central e mais complexa do trabalho. Toda a manipulação deve ser em memória secundária.

* 
**Tarefa 3.1:** Implementar a função de criação do **Arquivo Único de Índice** (onde ficarão os nós internos) e a lógica de criação de arquivos separados para cada folha (ex: `f0.dat`, `f1.dat`).


* 
**Tarefa 3.2:** Desenvolver a função de **Busca por Nome** na Árvore B+. Ela deve ler a raiz do índice único, navegar pelos nós internos e abrir o arquivo binário da folha correspondente para retornar o ID.


* 
**Tarefa 3.3:** Implementar a **Inserção** na Árvore B+ levando em conta o grau mínimo $t$ definido pelo usuário. Lembre-se de codificar o *Split* (cisão) de nós internos e o *Split* especial de nós folhas.


* **Tarefa 3.4:** Popular a Árvore B+ inserindo os nomes de `pessoas.dat` e `filmes.dat`.
* 
**Tarefa 3.5:** Ler o arquivo `relacoes_bruto.dat`, usar a Árvore B+ para traduzir os nomes de pessoas e filmes em seus respectivos IDs, e salvar o resultado definitivo em `relacionamentos.dat`.



---

## 💻 Fase 4: Interface e Operações Estruturais

Construir a base do programa que o usuário irá interagir.

* 
**Tarefa 4.1:** Criar o menu principal capturando o parâmetro de grau mínimo $t$ na inicialização.


* 
**Tarefa 4.2:** Implementar a função de **Imprimir a Árvore** de forma visual/hierárquica na tela (mostrando as chaves dos nós internos e indicando os arquivos das folhas).


* 
**Tarefa 4.3:** Implementar as funções de inserção avulsa em tempo de execução (Inserir Ator, Diretor, Filme), atualizando os arquivos `.dat` e a Árvore B+.


* 
**Tarefa 4.4:** Implementar o algoritmo de **Remoção** da Árvore B+ (tratando *borrow* e *merge* de folhas e nós internos) para dar suporte às exclusões.



---

## 📊 Fase 5: Implementação das Consultas (O Coração do Menu)

Com os arquivos `pessoas.dat`, `filmes.dat` e `relacionamentos.dat` totalmente indexados, implemente os relatórios solicitados. Dica: dividam essas consultas igualmente entre os membros do grupo.

* 
**Tarefa 5.1 (Cruzamento de Equipes):** Desenvolver as funções para listar parcerias: Geral (a) , Atores+Diretores (b) e Atores+Atores (c).


* 
**Tarefa 5.2 (Filtros por Década):** Criar a lógica de agrupamento por décadas (anos de 0 a 9) para responder às perguntas (d) , (e) e (l).


* 
**Tarefa 5.3 (Estatísticas de Máximos e Mínimos):** Criar algoritmos de contagem para identificar quem mais/menos atuou (f, g) , dirigiu (h, i) e produziu (j, k).


* 
**Tarefa 5.4 (Validações Específicas):** Criar as rotinas para buscar continuações (m) , anos de nascimento (n, t) e acúmulo de funções pelo mesmo artista no mesmo filme (r, s) ou em filmes diferentes (o, p).



---

## 🧪 Fase 6: Testes Extremos e Validação de Arquivos

Garantir que as regras rígidas do professor Rosseti foram seguidas à risca.

* 
**Tarefa 6.1:** Verificar no diretório do programa se o arquivo de índice é estritamente **único** e se novos arquivos `.dat` surgem ou desaparecem conforme folhas são criadas/removidas.


* 
**Tarefa 6.2:** Testar o programa alterando o valor de $t$ no menu (ex: testar com $t=2$, $t=5$, $t=10$) para ver se a paginação continua funcionando perfeitamente.


* 
**Tarefa 6.3:** Testar o comportamento do sistema ao remover todos os integrantes de um filme (q) e validar se a árvore B+ se reorganiza corretamente sem corromper os arquivos das folhas.



---

## 📦 Fase 7: Preparação para a Entrega e Apresentação

O trabalho não termina no código; a apresentação prática com o professor define a nota.

* **Tarefa 7.1:** Revisar o código para garantir que não há vazamento de memória (Memory Leaks) e que todos os arquivos abertos com `fopen` sejam devidamente fechados com `fclose`.
* 
**Tarefa 7.2:** Preparar o e-mail de entrega para o endereço especificado dentro do prazo estabelecido.


* 
**Tarefa 7.3:** Alinhamento do grupo: garantam que todos os integrantes saibam explicar detalhadamente como o código manipula os ponteiros de arquivos binários e como ocorrem os splits/merges na Árvore B+, pois isso será arguido nos dias de apresentação.