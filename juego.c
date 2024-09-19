#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include "restaurant.h"
#include "complemento.h"
int main(){
    srand((unsigned)time(NULL));
    system("clear");
    juego_t juego;
    inicializar_juego(&juego);

    while (estado_juego(juego)==0){
    char accion=' ';
    printf("HAZ UNA ACCION=>");
    scanf(" %c", &accion);
    while ((accion!= ACCION_ABAJO && accion!= ACCION_ARRIBA && accion!=ACCION_DERECHA && accion!=ACCION_IZQUIERDA && accion!=AGARRA_O_SOLTAR_MOPA)){
        printf("NO SE HA HECHO UNA ACCIÓN VALIDA, VUELVE A INTRODUCIR UNA ACCIÓN =>");
        scanf(" %c", &accion);
    }
    system("clear");
    realizar_jugada(&juego,accion);
    mostrar_juego(juego);
    }
    return 0;
}
