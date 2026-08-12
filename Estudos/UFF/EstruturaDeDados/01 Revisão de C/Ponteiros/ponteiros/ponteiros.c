#include <stdio.h>

int ponteiro_variavel_1(){
/* 
& retorna o endereco de uma variavel
* retorna o conteudo de um endereco
*/

    int x = 10;      // Uma variável normal.
    int *p;          // Declarando um ponteiro (o '*' aqui diz: 'p vai guardar endereços').
    p = &x;          // p agora guarda o ENDEREÇO de x (ex: 0x7ffd).
    printf("%d\n", *p); // O '*' aqui diz: "Vá ao endereço guardado em p e mostre o valor".
    return 0;
}

int ponteiro_variavel_2(){
/* 
& retorna o endereco de uma variavel
* retorna o conteudo de um endereco
*/

    int a, *p, c;  
    a = 5;             // a recebe o valor 5
    p = &a;            // "p" agora guarda o ENDEREÇO de a (ex: 0x7ffd).
    *p = 2;         // No endereço de memoria de p eu coloco 2
    c = *p;            // c recebe o valor armazenado na posicao de memoria apostada por p
                       // p tem o endereco de memoria

    
    printf("%d\n", c); 
    return 0;
}

int ponteiro_erro(){
    int a, b, *p;
    a = 2;
    // int c;
    // p = &c;
    *p = 3; // p aqui nao foi atribuido a nenhum valor de memoria
    b = a + (*p);
    printf("$d", b);

    return 0;
}

int ponteiros(){
    printf("# Ponteiros\n\n");

    ponteiro_variavel_1();
    ponteiro_variavel_2();

    printf("# -----------------\n\n");

}
