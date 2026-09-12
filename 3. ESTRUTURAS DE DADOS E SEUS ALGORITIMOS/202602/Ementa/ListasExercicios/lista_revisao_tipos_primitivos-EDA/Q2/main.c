#include <stdio.h>
#include <stdbool.h>


/*
Q2) Implemente um programa que, infinitamente, receba, como parâmetro de entrada, um número
n e retorne os n primeiros números primos existentes depois de n. Por exemplo, se n = 2, a
resposta será os primos 3 e 5. É necessário salientar que n não precisa ser primo. Seu programa
para quando n for menor ou igual a zero.
*/




int verifica_primo(int n){
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }

    return true;
}

int verifica_primo_recursiva(int n, int divisor){
    
    if(n <= 1) return 0;
    if(divisor == 1) return 1;
    if(n % divisor == 0 && n != divisor) return 0;
    return verifica_primo_recursiva(n, divisor - 1);
}


int main (){

    int n;

    do {
        printf("Digite o numero para verificar se e primo: \n");
        scanf("%d", &n);
        // printf("%d esta sendo verificado\n", n);
        int count = 0;
        int aux = n;

        while (count != n){

            if(verifica_primo(aux)){
            // if(verifica_primo_recursiva(i, i)){

                printf("%d e Primo\n", aux);
                ++count;
                // printf("%d=%d %d e count\n", count, n, (count != n));

            }else {
                // printf("Não e primo");
            }
            ++aux;
        }

        printf("N\n: %d", n);
    } while (n>=0);

    return 0;
}