#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"restaurant.h"

#define REINICIO_COLOR "\033[0m"
#define AZUL_COLOR "\033[34m"
#define AMARILLO_COLOR "\033[33m"
#define TEXTO_NEGRITA "\033[1m"

/* ACCIONES VALIDAS */
const char ACCION_DERECHA_COMP='D';
const char ACCION_IZQUIERDA_COMP='A';
const char ACCION_ARRIBA_COMP='W';
const char ACCION_ABAJO_COMP='S';
const char AGARRA_O_SOLTAR_MOPA_COMP='O';
const char TOMAR_PEDIDO_COMP='T';
const char USAR_PATIN_COMP='P';

bool no_es_accion_valida(char accion){
    return (accion!= ACCION_ABAJO_COMP && accion!= ACCION_ARRIBA_COMP && accion!=ACCION_DERECHA_COMP && accion!=ACCION_IZQUIERDA_COMP && accion!=AGARRA_O_SOLTAR_MOPA_COMP && accion!=TOMAR_PEDIDO_COMP && accion!=USAR_PATIN_COMP);
}

void validacion_accion_ingresada(char* accion, juego_t juego){
    while (no_es_accion_valida(*accion)){
            printf(AMARILLO_COLOR"\t\t******-ALERTA-******\n-\tNO SE HA HECHO UNA ACCIÓN VALIDA"TEXTO_NEGRITA);
            mostrar_juego(juego);
            printf(AMARILLO_COLOR"-VUELVE A INTRODUCIR UNA ACCIÓN ⟹ "TEXTO_NEGRITA);
            scanf(" %c", accion);
            system("clear");
        }
}

void obtener_accion(char* accion){
    printf(AZUL_COLOR"HAZ UNA ACCIóN ⟹ "TEXTO_NEGRITA);
    scanf(" %c", accion);
    system("clear");
}

