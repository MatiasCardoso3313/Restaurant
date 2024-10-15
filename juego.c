#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "restaurant.h"

/* ESTADO DE JUEGO (MAIN)*/
const int JUEGO_EN_CURSO_MAIN=0;
const int JUEGO_PERDIDO_MAIN=-1;
const int JUEGO_GANADO_MAIN=1;
/* ACCIONES VALIDAS */
const char ACCION_DERECHA_MAIN='D';
const char ACCION_IZQUIERDA_MAIN='A';
const char ACCION_ARRIBA_MAIN='W';
const char ACCION_ABAJO_MAIN='S';
const char AGARRA_O_SOLTAR_MOPA_MAIN='O';

int main(){
    srand((unsigned)time(NULL));
    system("clear");
    juego_t juego;
    inicializar_juego(&juego);

    mostrar_juego(juego);
    while (estado_juego(juego) == JUEGO_EN_CURSO_MAIN){
        char accion=' ';
        printf("HAZ UNA ACCIóN ⟹ ");
        scanf(" %c", &accion);
        system("clear");
        realizar_jugada(&juego,accion);

        while ((accion!= ACCION_ABAJO_MAIN && accion!= ACCION_ARRIBA_MAIN && accion!=ACCION_DERECHA_MAIN && accion!=ACCION_IZQUIERDA_MAIN && accion!=AGARRA_O_SOLTAR_MOPA_MAIN)){
            mostrar_juego(juego);
            printf("\t\t******-ALERTA-******\n-NO SE HA HECHO UNA ACCIÓN VALIDA\n-VUELVE A INTRODUCIR UNA ACCIÓN ⟹ ");
            scanf(" %c", &accion);
            system("clear");
        }
        mostrar_juego(juego);
    }if (estado_juego(juego) == JUEGO_GANADO_MAIN){
        system("clear");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t-|G A N A S T E|-\n");
        printf("     * se ha llegado al objetivo de dinero *\n\n\n\n\n\n\n\n\n\n\n");
    }else if(estado_juego(juego) == JUEGO_PERDIDO_MAIN){
        system("clear");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t-|P E R D I S T E|-\n");
        printf("            * se ha terminado el dia *\n\n\n\n\n\n\n\n\n\n\n");

    }
    return 0;
}
