#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------------------ *
 * Q5) Reescreva as operacoes basicas da ABB para armazenar as
 * figuras geometricas quadrado, triangulo, retangulo e trapezio.
 * A AREA da figura e a chave: define esquerda (menor area) e direita
 * (maior area). A impressao e em ordem simetrica e, alem da area,
 * mostra as dimensoes da figura.
 *
 * Cada no guarda uma Figura (tipo + dimensoes + area calculada).
 * Areas:
 *   quadrado  (lado)                  -> lado * lado
 *   triangulo (base, altura)          -> base * altura / 2
 *   retangulo (base, altura)          -> base * altura
 *   trapezio  (base maior, base menor, altura) -> (B + b) * h / 2
 * ------------------------------------------------------------------ */

typedef enum { QUADRADO, TRIANGULO, RETANGULO, TRAPEZIO } TipoFig;

typedef struct {
    TipoFig tipo;
    double d1, d2, d3;               /* dimensoes (d3 so no trapezio) */
    double area;
} Figura;

typedef struct no {
    Figura fig;
    struct no *esq, *dir;
} TABBF;

/* ---- construcao de figuras ---- */
static Figura fig_quadrado(double lado) {
    Figura f = { QUADRADO, lado, 0, 0, lado * lado };
    return f;
}
static Figura fig_triangulo(double base, double altura) {
    Figura f = { TRIANGULO, base, altura, 0, base * altura / 2.0 };
    return f;
}
static Figura fig_retangulo(double base, double altura) {
    Figura f = { RETANGULO, base, altura, 0, base * altura };
    return f;
}
static Figura fig_trapezio(double B, double b, double h) {
    Figura f = { TRAPEZIO, B, b, h, (B + b) * h / 2.0 };
    return f;
}

/* ---- operacoes basicas da ABB (chave = area) ---- */
static TABBF *abbf_inicializa(void) {
    return NULL;
}

static TABBF *abbf_cria(Figura fig) {
    TABBF *n = malloc(sizeof(TABBF));
    n->fig = fig;
    n->esq = n->dir = NULL;
    return n;
}

static TABBF *abbf_insere(TABBF *a, Figura fig) {
    if (!a)
        return abbf_cria(fig);
    if (fig.area < a->fig.area)
        a->esq = abbf_insere(a->esq, fig);
    else
        a->dir = abbf_insere(a->dir, fig);   /* areas iguais vao a direita */
    return a;
}

static TABBF *abbf_busca(TABBF *a, double area) {
    if (!a || a->fig.area == area)
        return a;
    if (area < a->fig.area)
        return abbf_busca(a->esq, area);
    return abbf_busca(a->dir, area);
}

static void abbf_libera(TABBF *a) {
    if (a) {
        abbf_libera(a->esq);
        abbf_libera(a->dir);
        free(a);
    }
}

static void imprime_figura(const Figura *f) {
    switch (f->tipo) {
        case QUADRADO:
            printf("quadrado  (lado=%.1f)", f->d1);
            break;
        case TRIANGULO:
            printf("triangulo (base=%.1f, altura=%.1f)", f->d1, f->d2);
            break;
        case RETANGULO:
            printf("retangulo (base=%.1f, altura=%.1f)", f->d1, f->d2);
            break;
        case TRAPEZIO:
            printf("trapezio  (B=%.1f, b=%.1f, h=%.1f)", f->d1, f->d2, f->d3);
            break;
    }
    printf(" -> area = %.2f\n", f->area);
}

static void abbf_imp_sim(TABBF *a) {
    if (!a)
        return;
    abbf_imp_sim(a->esq);
    imprime_figura(&a->fig);
    abbf_imp_sim(a->dir);
}

int main(void) {
    TABBF *a = abbf_inicializa();

    a = abbf_insere(a, fig_retangulo(4, 5));      /* 20.00 */
    a = abbf_insere(a, fig_quadrado(3));          /*  9.00 */
    a = abbf_insere(a, fig_triangulo(6, 4));      /* 12.00 */
    a = abbf_insere(a, fig_trapezio(5, 3, 4));    /* 16.00 */
    a = abbf_insere(a, fig_quadrado(6));          /* 36.00 */
    a = abbf_insere(a, fig_triangulo(3, 2));      /*  3.00 */

    printf("figuras em ordem simetrica (por area crescente):\n");
    abbf_imp_sim(a);

    double alvo = 16.0;
    TABBF *achou = abbf_busca(a, alvo);
    printf("\nbusca por area %.2f: %s\n", alvo,
           achou ? "encontrada" : "nao encontrada");

    abbf_libera(a);
    return 0;
}
