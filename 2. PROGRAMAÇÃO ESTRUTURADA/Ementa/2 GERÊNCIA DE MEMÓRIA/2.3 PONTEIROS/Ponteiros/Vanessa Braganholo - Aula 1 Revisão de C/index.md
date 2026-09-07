# Resumo da Aula: Estruturas de Dados e Algoritmos em C

Vou organizar a transcrição em tópicos principais e explicar cada um detalhadamente:

---

## 1. **PONTEIROS E MANIPULAÇÃO DE MEMÓRIA**

### O que são ponteiros?
Ponteiros são variáveis especiais que armazenam **endereços de memória**. Para cada tipo de dado (int, float, etc), existe um tipo de ponteiro correspondente.

**Declaração:**
```c
int a;        // variável inteira comum
int *p;       // ponteiro para inteiro
```

### Operadores principais:

| Operador | Símbolo | Significado |
|----------|---------|-------------|
| **Address-of** | `&` | Obtém o endereço de memória de uma variável |
| **Dereference** | `*` | Acessa o conteúdo armazenado no endereço apontado |

**Exemplo prático:**
```c
int a = 5;
int *p;
p = &a;        // p aponta para o endereço de a
*p = 6;        // muda o valor de a para 6 (através do ponteiro)
```

### Perigo comum:
❌ **Nunca faça:**
```c
int *p;
*p = 10;  // ERRO! p não aponta para nada (tem "lixo")
```

✅ **Faça assim:**
```c
int c;
int *p = &c;  // Agora p aponta para c
*p = 10;      // Seguro!
```

---

## 2. **PASSAGEM DE PARÂMETROS COM PONTEIROS**

### Sem ponteiros (passagem por valor):
Alterações dentro da função **não afetam** a variável original.

```c
void troca(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
}

int main() {
    int a = 5, b = 7;
    troca(a, b);  // a e b NÃO são trocados!
}
```

### Com ponteiros (passagem por referência):
Alterações dentro da função **afetam** a variável original.

```c
void troca(int *px, int *py) {
    int temp = *px;
    *px = *py;
    *py = temp;
}

int main() {
    int a = 5, b = 7;
    troca(&a, &b);  // Agora a=7 e b=5 ✓
    printf("a=%d, b=%d\n", a, b);  // Saída: a=7, b=5
}
```

---

## 3. **VETORES E PONTEIROS**

### Vetores são ponteiros!
Na verdade, um vetor é um **ponteiro para o primeiro elemento** alocado em posições contíguas de memória.

```c
int v[10];  // Vetor de 10 inteiros
            // v aponta para v[0]
            // v+1 aponta para v[1], etc.
```

**Aritmética de ponteiros:**
```c
v[0]   ≡   *v        (primeiro elemento)
v[1]   ≡   *(v+1)    (segundo elemento)
v[9]   ≡   *(v+9)    (décimo elemento)
```

### Vetores como parâmetros:
Quando você passa um vetor para uma função, qualquer alteração é **refletida** no programa principal (porque é ponteiro!).

```c
void incrementaVetor(int *v, int n) {
    for(int i = 0; i < n; i++) {
        v[i]++;  // Modifica o vetor original
    }
}

int main() {
    int v[3] = {1, 3, 5};
    incrementaVetor(v, 3);
    // v agora é {2, 4, 6}
}
```

---

## 4. **ALOCAÇÃO DINÂMICA DE MEMÓRIA**

### Por que usar alocação dinâmica?
- Tamanho do vetor desconhecido em tempo de compilação
- Usar mais eficientemente a memória disponível
- Liberar memória quando não for mais necessária

### Função `malloc()`:

```c
#include <stdlib.h>

int *v = (int*) malloc(10 * sizeof(int));
//     ↑       ↑      ↑  ↑
//  tipo de  função  tamanho em bytes
//  retorno
```

**O que acontece:**
1. Aloca 10 × 4 bytes = 40 bytes na memória
2. Retorna um ponteiro para esse espaço
3. Se falhar, retorna `NULL`

### Função `sizeof()`:
Retorna o tamanho em bytes de um tipo:
```c
sizeof(int)     // geralmente 4 bytes
sizeof(float)   // geralmente 4 bytes
sizeof(double)  // geralmente 8 bytes
```

### Função `free()`:
Libera a memória alocada dinamicamente:

```c
int *v = (int*) malloc(10 * sizeof(int));
// ... use o vetor ...
free(v);  // Libera a memória
v = NULL; // Boa prática
```

### Exemplo completo:

```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    int n;
    printf("Tamanho do vetor: ");
    scanf("%d", &n);
    
    // Aloca vetor dinamicamente
    int *v = (int*) malloc(n * sizeof(int));
    
    // Verifica se alocação foi bem-sucedida
    if (v == NULL) {
        printf("Erro: memória insuficiente!\n");
        return 1;
    }
    
    // Usa o vetor
    for(int i = 0; i < n; i++) {
        v[i] = i * 2;
    }
    
    // Libera a memória
    free(v);
    return 0;
}
```

---

## 5. **TIPOS ESTRUTURADOS (STRUCTS)**

### O que é uma struct?
Uma forma de agrupar vários tipos de dados em **uma única estrutura complexa**.

**Exemplo simples:**
```c
struct Ponto2D {
    float x;
    float y;
};

int main() {
    struct Ponto2D p;
    p.x = 10.5;
    p.y = 20.3;
    printf("Ponto: (%.1f, %.1f)\n", p.x, p.y);
}
```

### Usando `typedef` (simplifica a sintaxe):

```c
typedef struct {
    float x;
    float y;
} Ponto2D;

// Agora não precisa escrever "struct" toda vez
Ponto2D p;
p.x = 10;
```

### Acessando campos através de ponteiros:

```c
Ponto2D p = {5, 10};
Ponto2D *pp = &p;

// Duas formas equivalentes:
(*pp).x = 15;    // Desreferencia depois acessa
pp->x = 15;      // Acessa diretamente (mais legível)
```

---

## 6. **LISTAS ENCADEADAS**

### Estrutura de um nó:
```c
typedef struct No {
    int info;          // valor armazenado
    struct No *proximo; // ponteiro para próximo nó
} No;

typedef No* Lista;  // A lista é um ponteiro para nó
```

### Criar lista vazia:
```c
Lista criaListaVazia(void) {
    return NULL;  // Lista vazia aponta para NULL
}
```

### Inserir no início:
```c
Lista insereInicio(Lista l, int x) {
    No *novo = (No*) malloc(sizeof(No));
    novo->info = x;
    novo->proximo = l;
    return novo;  // Retorna o novo início
}
```

**Visualização:**
```
Antes:  l → [3] → [5] → [2] → NULL

Inserir 4:  novo = [4]
            novo->proximo = l

Depois: l → [4] → [3] → [5] → [2] → NULL
```

### Inserir no final:
```c
Lista insereFim(Lista l, int x) {
    No *novo = (No*) malloc(sizeof(No));
    novo->info = x;
    novo->proximo = NULL;
    
    if (l == NULL) {
        return novo;  // Lista vazia
    }
    
    No *p = l;
    while (p->proximo != NULL) {
        p = p->proximo;  // Percorre até o último
    }
    p->proximo = novo;  // Conecta o novo
    return l;
}
```

### Inserir em ordem:
```c
Lista insereOrdenado(Lista l, int x) {
    No *novo = (No*) malloc(sizeof(No));
    novo->info = x;
    
    if (l == NULL || l->info > x) {
        novo->proximo = l;
        return novo;
    }
    
    No *p = l;
    while (p->proximo != NULL && p->proximo->info < x) {
        p = p->proximo;
    }
    novo->proximo = p->proximo;
    p->proximo = novo;
    return l;
}
```

### Imprimir a lista:
```c
void imprimeList(Lista l) {
    No *p = l;
    while (p != NULL) {
        printf("%d ", p->info);
        p = p->proximo;  // Avança para o próximo
    }
    printf("\n");
}
```

---

## 7. **RECURSÃO**

### Conceito:
Uma função que **chama a si mesma**, com um **critério de parada** claro.

**Estrutura básica:**
```c
TipoRetorno funcaoRecursiva(parametros) {
    // 1. Critério de parada (base da recursão)
    if (condicao_parada) {
        return valor_base;
    }
    
    // 2. Caso recursivo
    return funcaoRecursiva(parametros_modificados);
}
```

### Exemplo 1: Fatorial
```c
int fatorial(int n) {
    if (n == 0 || n == 1) {
        return 1;  // Caso base
    }
    return n * fatorial(n - 1);  // Caso recursivo
}

// fatorial(5) = 5 * fatorial(4)
//             = 5 * 4 * fatorial(3)
//             = 5 * 4 * 3 * fatorial(2)
//             = 5 * 4 * 3 * 2 * fatorial(1)
//             = 5 * 4 * 3 * 2 * 1 = 120
```

### Exemplo 2: Inserir no final recursivamente
```c
Lista insereFimRecursivo(Lista l, int x) {
    No *novo = (No*) malloc(sizeof(No));
    novo->info = x;
    novo->proximo = NULL;
    
    if (l == NULL) {
        return novo;  // Caso base: lista vazia
    }
    
    if (l->proximo == NULL) {
        l->proximo = novo;  // Caso base: chegou no fim
        return l;
    }
    
    // Caso recursivo: continua procurando o fim
    l->proximo = insereFimRecursivo(l->proximo, x);
    return l;
}
```

### Exemplo 3: Inserir ordenado recursivamente
```c
Lista insereOrdenadoRecursivo(Lista l, No *anterior, int x) {
    No *novo = (No*) malloc(sizeof(No));
    novo->info = x;
    
    if (l == NULL) {
        novo->proximo = NULL;
        return novo;
    }
    
    if (l->info > x) {
        novo->proximo = l;
        return novo;
    }
    
    if (l->proximo == NULL) {
        l->proximo = novo;
        return l;
    }
    
    // Recursão: continua procurando posição
    l->proximo = insereOrdenadoRecursivo(l->proximo, l, x);
    return l;
}
```

---

## **RESUMO DOS CONCEITOS PRINCIPAIS**

| Conceito | Uso | Exemplo |
|----------|-----|---------|
| **Ponteiros** | Armazenar endereços | `int *p = &x;` |
| **Malloc** | Alocar memória dinamicamente | `malloc(10 * sizeof(int))` |
| **Free** | Liberar memória | `free(v);` |
| **Struct** | Agrupar dados | `struct Pessoa { int idade; }` |
| **Lista Encadeada** | Armazenar dados com ordem flexível | `No *lista = NULL;` |
| **Recursão** | Resolver problema dividindo em partes | `fatorial(n-1)` |

---

Essa aula fornece a **base fundamental** necessária para trabalhar com estruturas de dados mais complexas! 🚀