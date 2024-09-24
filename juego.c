#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "restaurant.h"

/* ESTADO DE JUEGO (MAIN)*/
const int JUEGO_EN_CURSO=0;
const int JUEGO_PERDIDO=-1;
const int JUEGO_GANADO=1;

int main(){
    srand((unsigned)time(NULL));
    system("clear");
    juego_t juego;
    inicializar_juego(&juego);

    mostrar_juego(juego);
    while (estado_juego(juego) == JUEGO_EN_CURSO){
        char accion=' ';
        printf("HAZ UNA ACCION=>");
        scanf(" %c", &accion);
        system("clear");
        realizar_jugada(&juego,accion);
        mostrar_juego(juego);
    }if (estado_juego(juego) == JUEGO_GANADO){
        system("clear");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n               -|G A N A S T E|-\n\n\n\n\n\n\n\n\n\n\n\n");
    }else if(estado_juego(juego) == JUEGO_PERDIDO){
        system("clear");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n               -|P E R D I S T E|-\n\n\n\n\n\n\n\n\n\n\n\n");

    }
    return 0;
}
