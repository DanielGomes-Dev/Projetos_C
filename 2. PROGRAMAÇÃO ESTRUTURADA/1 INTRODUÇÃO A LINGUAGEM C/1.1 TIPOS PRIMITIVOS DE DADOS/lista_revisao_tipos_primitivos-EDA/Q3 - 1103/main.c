#include <stdio.h>
#include <stdbool.h>


/*

Q3) [Problema 1103 do URI Online Judge] Daniela é enfermeira em um grande hospital, e tem
os horários de trabalho muito variáveis. Para piorar, ela tem sono pesado, e uma grande
dificuldade para acordar com relógios despertadores. Recentemente ela ganhou de presente um
relógio digital, com alarme com vários tons, e tem esperança que isso resolva o seu problema. No
entanto, ela anda muito cansada e quer aproveitar cada momento de descanso. Por isso, carrega
seu relógio digital despertador para todos os lugares, e sempre que tem um tempo de descanso
procura dormir, programando o alarme despertador para a hora em que tem que acordar. No
entanto, com tanta ansiedade para dormir, acaba tendo dificuldades para adormecer e aproveitar
o descanso.

*/

void get_time_from_user(int *H1, int *M1, int *H2, int *M2){
    // printf("%p", &H1);

    scanf("%d", H1);
    scanf("%d", M1);
    scanf("%d", H2);
    scanf("%d", M2);

    // if( *H1 < 0 || *H1 > 23 || *H2 < 0 || *H2 > 23) 
        // printf("Hora invalida");
    // if( *M1 < 0 || *M1 > 59 || *M2 < 0 || *M2 > 59) 
        // printf("Minutos invalidos");
    // if( *H1 == 0 && *M1 == 0 && *H2 == 0 && *M2 == 0) 
        // printf("Finalizando programa");

}

int calcula_minutos(int H1, int M1, int H2, int M2){
    int hora, minutos;
    if(M2 >= M1){
        minutos = M2 - M1;
    }

    if(M2 < M1){
        minutos = M2 - M1 + 60;
    }

    if(H2 > H1){
        hora = H2 - H1;
    }
    if(H2 < H1) {
        hora = H2 - H1 + 23;
    } 

    if(H2 == H1 && M2 < M1 ){
        hora = 23;
        minutos = M2 - M1 + 60;

    }

    if (H2 - H1 == 1 && M2 < M1){
        hora = 0;
        minutos = M2 - M1 + 60;

    }


    int minutos_totais = (hora*60)+minutos;

    // printf("%d:%d\n", hora, minutos);
    // printf("Minutos: %d\n", minutos_totais);
    return minutos_totais;
}

int main (){
    int rodando = 1;

    int H1, M1, H2, M2;
    
    while (rodando == 1)
    {
        get_time_from_user(&H1, &M1, &H2, &M2);
        if( H1 == 0 && M1 == 0 && H2 == 0 && M2 == 0) 
            return rodando = 0;
        int minutos_totais = calcula_minutos(H1, M1, H2, M2);
        printf("%d\n", minutos_totais);
    }
    
   

    
    // printf("%p\n", &H1);
    // printf("Exibindo: \n");
    // printf("%d:%d %d:%d\n", H1, M1, H2, M2);

    return 0;
}