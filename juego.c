#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "restaurant.h"
#include "complemento.h"

/* ESTADO DE JUEGO (MAIN)*/
const int JUEGO_EN_CURSO_MAIN=0;
const int JUEGO_PERDIDO_MAIN=-1;
const int JUEGO_GANADO_MAIN=1;


int main(){
    srand((unsigned)time(NULL));
    system("clear");
    juego_t juego;
    inicializar_juego(&juego);

    mostrar_juego(juego);
    while (estado_juego(juego) == JUEGO_EN_CURSO_MAIN){
        char accion=' ';
        obtener_accion(&accion);
        validacion_accion_ingresada(&accion, juego);
        realizar_jugada(&juego,accion);
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
    destruir_juego(&juego);

    return 0;
}
