#include<stdio.h>
#include<stdbool.h>
#include "restaurant.h"

void inicializar_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS], int tope){
    for(int fila, fila<MAX_FILAS  ,fila++)
      for(int columna, columna<MAX_COLUMNAS  , columna++)
        terreno[fila][columna]=' ';
}

void reemplazar_elemento(char terreno[MAX_FILAS][MAX_COLUMNAS], coordenada_t posicion, char elemento){
    terreno[posicion.fila][posicion.columna]=elemento;    
}

void colocar_mesas(){
}

void inicializar_juego(juego_t *juego){
    juego->cocina.posicion.fil;
    juego->cocina.posicion.col;

}
void mostrar_juego(juego_t juego){
}