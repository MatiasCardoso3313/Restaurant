#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"restaurant.h"
/* ACCIONES VALIDAS */
const char ACCION_DERECHA_COMP='D';
const char ACCION_IZQUIERDA_COMP='A';
const char ACCION_ARRIBA_COMP='W';
const char ACCION_ABAJO_COMP='S';
const char AGARRA_O_SOLTAR_MOPA_COMP='O';

bool no_es_accion_valida(char accion){
    return (accion!= ACCION_ABAJO_COMP && accion!= ACCION_ARRIBA_COMP && accion!=ACCION_DERECHA_COMP && accion!=ACCION_IZQUIERDA_COMP && accion!=AGARRA_O_SOLTAR_MOPA_COMP);
}

void validacion_accion_ingresada(char* accion, juego_t juego){
    while (no_es_accion_valida(*accion)){
            mostrar_juego(juego);
            printf("\t\t******-ALERTA-******\n-NO SE HA HECHO UNA ACCIÓN VALIDA\n-VUELVE A INTRODUCIR UNA ACCIÓN ⟹ ");
            scanf(" %c", accion);
            system("clear");
        }
}

void obtener_accion(char* accion){
    printf("HAZ UNA ACCIóN ⟹ ");
    scanf(" %c", accion);
    system("clear");
}

