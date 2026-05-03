Para resolver a **Questão 5 (Q5)**, precisamos adaptar a estrutura original para comportar informações de figuras geométricas e modificar a lógica de comparação para utilizar a **área** como chave de busca.

Abaixo, apresento o código completo com as operações de criação, cálculo de área, inserção e impressão simétrica.

---

### Implementação em C

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição dos tipos de figuras
typedef enum { QUADRADO, TRIANGULO, RETANGULO, TRAPEZIO } T_FIG;

// Estrutura para armazenar as dimensões e o tipo da figura
typedef struct {
    T_FIG tipo;
    float d1, d2, d3; // d1: base/lado, d2: altura/base_menor, d3: base_maior (trapézio)
    float area;
} TFIGURA;

// Estrutura da ABB adaptada
typedef struct ab {
    TFIGURA fig;
    struct ab *esq, *dir;
} TABB;

// Função para calcular a área com base no tipo da figura
float calcula_area(T_FIG tipo, float d1, float d2, float d3) {
    switch (tipo) {
        case QUADRADO:  return d1 * d1;
        case TRIANGULO: return (d1 * d2) / 2.0;
        case RETANGULO: return d1 * d2;
        case TRAPEZIO:  return ((d1 + d3) * d2) / 2.0;
        default: return 0;
    }
}

// Operação Básica: Criação de Nó
TABB* cria_no(T_FIG tipo, float d1, float d2, float d3) {
    TABB *novo = (TABB*)malloc(sizeof(TABB));
    novo->fig.tipo = tipo;
    novo->fig.d1 = d1;
    novo->fig.d2 = d2;
    novo->fig.d3 = d3;
    novo->fig.area = calcula_area(tipo, d1, d2, d3);
    novo->esq = novo->dir = NULL;
    return novo;
}

// Operação Básica: Inserção (Baseada na ÁREA)
TABB* insere_ABB_fig(TABB *a, T_FIG tipo, float d1, float d2, float d3) {
    float area_nova = calcula_area(tipo, d1, d2, d3);
    
    if (!a) return cria_no(tipo, d1, d2, d3);
    
    if (area_nova < a->fig.area)
        a->esq = insere_ABB_fig(a->esq, tipo, d1, d2, d3);
    else if (area_nova > a->fig.area)
        a->dir = insere_ABB_fig(a->dir, tipo, d1, d2, d3);
        
    return a;
}

// Função auxiliar para traduzir o enum para texto
const char* nome_figura(T_FIG tipo) {
    switch (tipo) {
        case QUADRADO:  return "Quadrado";
        case TRIANGULO: return "Triangulo";
        case RETANGULO: return "Retangulo";
        case TRAPEZIO:  return "Trapezio";
        default: return "Desconhecido";
    }
}

// Operação Básica: Impressão Simétrica (In-order)
void imprime_simetrico(TABB *a) {
    if (a) {
        imprime_simetrico(a->esq);
        
        printf("Figura: %-10s | Area: %7.2f | Dims: [%.1f, %.1f, %.1f]\n", 
               nome_figura(a->fig.tipo), 
               a->fig.area, 
               a->fig.d1, a->fig.d2, a->fig.d3);
               
        imprime_simetrico(a->dir);
    }
}

int main() {
    TABB *raiz = NULL;

    // Inserindo figuras variadas
    raiz = insere_ABB_fig(raiz, QUADRADO, 4, 0, 0);       // Area: 16
    raiz = insere_ABB_fig(raiz, TRIANGULO, 10, 5, 0);    // Area: 25
    raiz = insere_ABB_fig(raiz, RETANGULO, 2, 3, 0);     // Area: 6
    raiz = insere_ABB_fig(raiz, TRAPEZIO, 4, 5, 6);      // Area: 25 (Não insere se duplicado ou vai p/ dir)

    printf("ABB de Figuras Geometricas (Ordem Simetrica por Area):\n");
    imprime_simetrico(raiz);

    return 0;
}
```

---

### Explicação Técnica das Mudanças

1.  **A Chave de Busca:** Conforme solicitado, a variável `info` foi substituída por `TFIGURA fig`. A lógica de decisão nos `if` da inserção agora utiliza `a->fig.area` em vez de um inteiro simples.
2.  **Cálculo Dinâmico:** A função `calcula_area` encapsula as fórmulas matemáticas de cada figura. Isso garante que a árvore mantenha a integridade da ordem de busca (ABB) definida no **Slide 4** do seu material.
3.  **Dimensões Flexíveis:** Utilizamos três campos genéricos (`d1, d2, d3`). Para um quadrado, apenas `d1` importa; para um trapézio, os três são usados (bases e altura).
4.  **Impressão Simétrica:** Seguindo a regra de percurso (Esquerda -> Raiz -> Direita), a função `imprime_simetrico` exibirá as figuras da menor área para a maior área.



> **Nota:** Se duas figuras tiverem áreas exatamente iguais, a lógica atual de ABB (Slide 9) ignora a inserção ou você pode adaptar para inserir na subárvore direita. Aqui, seguimos o padrão de chaves únicas do material.


----

Este código é uma adaptação de uma **Árvore Binária de Busca (ABB)** clássica para um sistema que gerencia figuras geométricas. A principal mudança conceitual é que a "chave" de ordenação (que determina quem vai para a esquerda ou direita) deixou de ser um simples número inteiro e passou a ser a **área da figura**.

Aqui está a explicação detalhada dividida por partes:

---

### 1. Definição de Dados (Enums e Structs)
Para lidar com diferentes figuras em uma mesma árvore, o código utiliza:
* **`typedef enum`**: Cria o tipo `T_FIG`, que associa nomes (QUADRADO, etc.) a números inteiros. Isso facilita a leitura do código.
* **`TFIGURA`**: É um "pacote" que guarda o tipo da figura, suas dimensões (`d1, d2, d3`) e o resultado do cálculo da sua área.
* **`TABB`**: O nó da árvore foi adaptado. Agora ele contém uma `TFIGURA` inteira dentro dele. 
    * *Nota:* No seu código, você manteve o `int info`. Nas adaptações de ABB de figuras, esse `info` costuma ser descartado, pois a **área** assume o papel de chave principal.

---

### 2. O Motor de Cálculo: `calcula_area`
Esta função é o coração da adaptação. Ela aplica as fórmulas geométricas dependendo do tipo da figura:
* **Quadrado**: $Lado^2$ (`d1 * d1`).
* **Triângulo**: $(Base \times Altura) / 2$ (`(d1 * d2) / 2`).
* **Retângulo**: $Base \times Altura$ (`d1 * d2`).
* **Trapézio**: $((BaseMaior + BaseMenor) \times Altura) / 2$.

---

### 3. Adaptação das Operações de ABB
As funções foram modificadas para respeitar a **Definição de ABB** (Slide 4 do seu material): *"Chaves da subárvore esquerda são menores que a raiz; chaves da subárvore direita são maiores"*.

#### `cria_no`
Ao criar um nó, o código já chama `calcula_area`. Isso é fundamental porque a área precisa estar disponível imediatamente para que as funções de inserção saibam para onde mandar o nó.

#### `insere_ABB_fig` (A Grande Mudança)
Diferente da `insere_ABB` tradicional que compara `info`, esta função:
1.  Calcula a área da nova figura que você quer inserir (`area_nova`).
2.  Compara com a área da figura que já está no nó atual (`a->fig.area`).
3.  Decide o caminho (esquerda ou direita) com base nesse valor flutuante.



---

### 4. Impressão Simétrica (`imprime_simetrico`)
O exercício pede que a impressão seja em **ordem simétrica**. 
* **Como funciona:** O código visita primeiro a subárvore esquerda (menores áreas), depois a raiz (figura atual), e por fim a subárvore direita (maiores áreas).
* **Resultado:** As figuras aparecerão no seu terminal listadas da **menor área para a maior área**, independentemente da ordem em que foram inseridas.
* **Detalhamento:** Além da área, o `printf` usa `nome_figura` para imprimir o nome legível em vez do número do `enum`.



---

### 5. O Fluxo no `main`
No seu `main`, as inserções criam a seguinte lógica:
1.  **Quadrado (Area 16)**: Torna-se a raiz.
2.  **Triângulo (Area 25)**: 25 > 16, vai para a **direita** do Quadrado.
3.  **Retângulo (Area 6)**: 6 < 16, vai para a **esquerda** do Quadrado.
4.  **Trapézio (Area 25)**: Como a área é 25 e já existe uma área 25 (o triângulo), o código não insere (ou insere na direita, dependendo da implementação), mantendo a árvore íntegra.

### Resumo das Adaptações Realizadas:
| Recurso | ABB Clássica (Seu Material) | ABB de Figuras (Este Código) |
| :--- | :--- | :--- |
| **Chave de Ordenação** | `int info` | `float area` |
| **Conteúdo do Nó** | Valor Inteiro | Estrutura `TFIGURA` (Tipo + Dimensões) |
| **Inserção** | Comparação simples de inteiros | Comparação de áreas calculadas por funções |
| **Impressão** | Apenas o valor numérico | Nome da figura, dimensões e área |

Essa estrutura permite que você busque figuras não por nome, mas por "tamanho" (espaço ocupado), o que é muito eficiente para sistemas de CAD ou jogos.