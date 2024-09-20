#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "restaurant.h"
int main(){
    srand((unsigned)time(NULL));
    system("clear");
    juego_t juego;
    inicializar_juego(&juego);

    mostrar_juego(juego);
    while (estado_juego(juego)==0){
        char accion=' ';
        printf("HAZ UNA ACCION=>");
        scanf(" %c", &accion);
        system("clear");
        realizar_jugada(&juego,accion);
        mostrar_juego(juego);
    };
}
